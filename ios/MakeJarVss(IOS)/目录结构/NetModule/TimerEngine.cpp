/////////////////////////////////////////////////////////////////////////
//		��ʱ��ʵ���ļ�
/////////////////////////////////////////////////////////////////////////
#include "TimerEngine.h"

//�궨��
#define NO_TIME_LEFT						DWORD(-1)				//����Ӧʱ��
//////////////////////////////////////////////////////////////////////////

//���캯��
CTimerThread::CTimerThread(void)
{
	m_dwTimerSpace=0L;
	m_pTimerEngine=NULL;
}

//��������
CTimerThread::~CTimerThread(void)
{
}

//���ú���
bool CTimerThread::InitThread(CTimerEngine * pTimerEngine, DWORD dwTimerSpace)
{
	//Ч�����
	ASSERT(dwTimerSpace>=10L);
	ASSERT(pTimerEngine!=NULL);
	if (pTimerEngine==NULL) return false;

	//���ñ���
	m_dwTimerSpace=dwTimerSpace;
	m_pTimerEngine=pTimerEngine;

	return true;
}

//���к���
bool CTimerThread::RepetitionRun()
{
	ASSERT(m_pTimerEngine!=NULL);
	MyThreadWait(m_dwTimerSpace);
	m_pTimerEngine->OnTimerThreadSink();
	return true;
}

//////////////////////////////////////////////////////////////////////////
ITimerEngine *g_pITimerEngine=NULL;			//��ʱ���ӿ�

//���캯��
CTimerEngine::CTimerEngine(void)
{
	m_bService=false;
	m_dwTimePass=0L;
	m_dwTimerSpace=25L;
	m_dwTimeLeave=NO_TIME_LEFT;

	g_pITimerEngine=(ITimerEngine *)this;
}

//��������
CTimerEngine::~CTimerEngine(void)
{
	//ֹͣ����
	StopService();
	//�����ڴ�
	tagTimerItem * pTimerItem=NULL;
	INT_PTR nCount=m_TimerItemFree.size();
	for (INT_PTR i=0;i<nCount;i++)
	{
		pTimerItem=m_TimerItemFree[i];
		ASSERT(pTimerItem!=NULL);
		delete pTimerItem;
	}
	for (CTimerItemMapIt it=m_TimerItemActive.begin();it!=m_TimerItemActive.end();it++)
	{
		pTimerItem=(*it).second;
		ASSERT(pTimerItem!=NULL);
		delete pTimerItem;
	}
	m_TimerItemFree.clear();
	m_TimerItemActive.clear();

	return;
}

//���ö�ʱ��
bool CTimerEngine::SetTimer(WORD wTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM wParam)
{
	return SetTimer(wTimerID,dwElapse,dwRepeat,wParam,NULL);
}

//���ö�ʱ��
bool CTimerEngine::SetTimer(WORD wTimerID,DWORD dwElapse,DWORD dwRepeat,WPARAM wParam,void * pTimerSink)
{
	//������Դ
	CThreadLockHandle LockHandle(&m_ThreadLock);

	//Ч�����
	ASSERT(dwRepeat>0L);
	if (dwRepeat==0) return false;
	dwElapse=(dwElapse+m_dwTimerSpace-1)/m_dwTimerSpace*m_dwTimerSpace;

	//���Ҷ�ʱ��
	bool bTimerExist=false;
	tagTimerItem * pTimerItem=NULL;

	CTimerItemMapIt it=m_TimerItemActive.find(wTimerID);
	if(it!=m_TimerItemActive.end())
	{
		bTimerExist=true;
		pTimerItem=(*it).second;
	}

	//������ʱ��
	if (bTimerExist==false)
	{
		INT_PTR nFreeCount=(INT_PTR)m_TimerItemFree.size();
		if (nFreeCount>0)
		{
			pTimerItem=m_TimerItemFree.back();
			ASSERT(pTimerItem!=NULL);
			m_TimerItemFree.pop_back();
		}
		else
		{
			try
			{
				pTimerItem=new tagTimerItem;
				ASSERT(pTimerItem!=NULL);
				if (pTimerItem==NULL) return false;
			}
			catch (...) { return false; }
		}
	}

	//���ò���
	ASSERT(pTimerItem!=NULL);
	pTimerItem->wTimerID=wTimerID;
	pTimerItem->wBindParam=wParam;
	pTimerItem->dwElapse=dwElapse;
	pTimerItem->dwRepeatTimes=dwRepeat;
	pTimerItem->dwTimeLeave=dwElapse+m_dwTimePass;
	pTimerItem->pTimerSink=pTimerSink;

	//���ʱ��
	m_dwTimeLeave=__min(m_dwTimeLeave,dwElapse);
	if (bTimerExist==false) m_TimerItemActive[wTimerID]=pTimerItem;

	return true;
}

//ɾ����ʱ��
bool CTimerEngine::KillTimer(WORD wTimerID)
{
	//������Դ
	CThreadLockHandle LockHandle(&m_ThreadLock);

	//���Ҷ�ʱ��
	tagTimerItem * pTimerItem=NULL;
	CTimerItemMapIt it=m_TimerItemActive.find(wTimerID);
	if(it==m_TimerItemActive.end()) return false;

	pTimerItem=(*it).second;
	m_TimerItemActive.erase(it);
	m_TimerItemFree.push_back(pTimerItem);
	INT nCount=(INT)m_TimerItemActive.size();
	if(nCount==0)
	{
		m_dwTimePass=0L;
		m_dwTimeLeave=NO_TIME_LEFT;
	}

	return true;
}

//ɾ����ʱ��
bool CTimerEngine::KillAllTimer()
{
	//������Դ
	CThreadLockHandle LockHandle(&m_ThreadLock);

	//���ñ���
	m_dwTimePass=0L;
	m_dwTimeLeave=NO_TIME_LEFT;

	//ɾ����ʱ��
	for(CTimerItemMapIt it=m_TimerItemActive.begin();it!=m_TimerItemActive.end();it++)
	{
		m_TimerItemFree.push_back((*it).second);
	}
	m_TimerItemActive.clear();

	return true;
}

//��ʼ����
bool CTimerEngine::StartService()
{
	//Ч��״̬
	if (m_bService==true) 
	{
		return true;
	}

	//û�лص�
	if (m_TimerSinkMap.size()==0)
	{
		return false;
	}

	//���ñ���
	m_dwTimePass=0L;
	m_dwTimeLeave=NO_TIME_LEFT;
	if (m_TimerThread.InitThread(this,m_dwTimerSpace)==false)
	{
		return false;
	}

	//��������
	if (m_TimerThread.StartThread()==false)
	{
		return false;
	}

	//���ñ���
	m_bService=true;

	return true;
}

//ֹͣ����
bool CTimerEngine::StopService()
{
	//���ñ���
	m_bService=false;

	//ֹͣ�߳�
	m_TimerThread.StopThread();

	KillAllTimer();

	return true;
}

//���ýӿ�
bool CTimerEngine::SetTimerEngineSink(ITimerEngineSink * pITimerEngineSink)
{
	//Ч�����
	ASSERT(pITimerEngineSink!=NULL);
	ASSERT(m_bService==false);
	if (m_bService==true) return false;
	if (pITimerEngineSink==NULL) return false;

	CThreadLockHandle LockHandle(&m_ThreadLock);
	CTimerSinkMapIt it=m_TimerSinkMap.find(pITimerEngineSink);
	if(it!=m_TimerSinkMap.end())
	{
		(*it).second++;
		return true;
	}
	m_TimerSinkMap[pITimerEngineSink]=1;
	
	return true;
}

//��ʱ��֪ͨ
void CTimerEngine::OnTimerThreadSink()
{
	//������Դ
	CThreadLockHandle LockHandle(&m_ThreadLock);

	//����ʱ��
	if (m_dwTimeLeave==NO_TIME_LEFT) 
	{
		ASSERT(m_TimerItemActive.size()==0);
		return;
	}

	//����ʱ��
	ASSERT(m_dwTimeLeave>=m_dwTimerSpace);
	m_dwTimeLeave-=m_dwTimerSpace;
	m_dwTimePass+=m_dwTimerSpace;

	//��ѯ��ʱ��
	if (m_dwTimeLeave==0)
	{
		CTimerItemMap killItemMap;
		bool bKillTimer=false;
		tagTimerItem * pTimerItem=NULL;
		DWORD dwTimeLeave=NO_TIME_LEFT;
		for(CTimerItemMapIt it=m_TimerItemActive.begin();it!=m_TimerItemActive.end();it++)
		{
			//Ч�����
			pTimerItem=(*it).second;
			ASSERT(pTimerItem!=NULL);
			ASSERT(pTimerItem->dwTimeLeave>=m_dwTimePass);

			//��ʱ������
			bKillTimer=false;
			pTimerItem->dwTimeLeave-=m_dwTimePass;
			if (pTimerItem->dwTimeLeave==0L)
			{
				//����֪ͨ
				OnTimerEventSink(pTimerItem->wTimerID,pTimerItem->wBindParam,pTimerItem->pTimerSink);
				
				//���ô���
				if (pTimerItem->dwRepeatTimes!=TIMER_REPEAT_TIMER)
				{
					ASSERT(pTimerItem->dwRepeatTimes>0);
					if (pTimerItem->dwRepeatTimes==1L)
					{
						bKillTimer=true;
						killItemMap[pTimerItem->wTimerID]=pTimerItem;
					}
					else pTimerItem->dwRepeatTimes--;
				}

				//����ʱ��
				if (bKillTimer==false) pTimerItem->dwTimeLeave=pTimerItem->dwElapse;
			}

			//��������
			if (bKillTimer==false) 
			{
				dwTimeLeave=__min(dwTimeLeave,pTimerItem->dwTimeLeave);
				ASSERT(dwTimeLeave%m_dwTimerSpace==0);
			}
		}

		//������Ӧ
		m_dwTimePass=0L;
		m_dwTimeLeave=dwTimeLeave;

		for(CTimerItemMapIt kIt=killItemMap.begin();kIt!=killItemMap.end();kIt++)
		{
			pTimerItem=(*kIt).second;
			m_TimerItemActive.erase((*kIt).first);
			m_TimerItemFree.push_back(pTimerItem);
		}
	}

	return;
}

//��ʱ���ص�
void CTimerEngine::OnTimerEventSink(WORD wTimerID,WPARAM wParam,void * pTimerSink)
{
	ITimerEngineSink *pITimerEngineSink=NULL;
	for(CTimerSinkMapIt it=m_TimerSinkMap.begin();it!=m_TimerSinkMap.end();it++)
	{
		pITimerEngineSink=(*it).first;
		ASSERT(pITimerEngineSink!=NULL);
		if(pITimerEngineSink!=NULL)
			pITimerEngineSink->OnEventTimer(wTimerID,wParam,pTimerSink);
	}
}


//////////////////////////////////////////////////////////////////////////
