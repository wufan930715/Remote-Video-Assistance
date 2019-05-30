////////////////////////////////////////////////////////////////////////////////////
//			ý��������ʵ���ļ� MediaDataManage.cpp
//			2016-08-13 Bowen.hu
/////////////////////////////////////////////////////////////////////////////////////
#include "MediaDataManage.h"
#include "SockClientSink.h"

/////////////////////////////////////////////////////////////////////////////////////
CMediaDataManage::CMediaDataManage(void)
{
	m_pIMediaDataSink=NULL;
	m_pIKernelDataSink=NULL;
	m_dwAudioSeqID=0;
	#ifdef ANDROID_OS
	m_pIAudioManager=NULL;
	m_VideoData.wDataSize=0;
	m_VideoData.wBufferSize=65535;
	m_VideoData.pDataBuffer=(BYTE*)::malloc(m_VideoData.wBufferSize);
	#endif
}

CMediaDataManage::~CMediaDataManage(void)
{
	#ifdef ANDROID_OS
	sem_destroy(&m_semt);
	if(m_VideoData.pDataBuffer!=NULL)
	{
		free(m_VideoData.pDataBuffer);
		m_VideoData.pDataBuffer=NULL;
		m_VideoData.wBufferSize=0;
	}
	#endif
}

//��ʼ��ý�����
bool CMediaDataManage::InitMediaManage()
{
	#ifdef ANDROID_OS
	IMediaDataManage *pIMediaDataManage=(IMediaDataManage *)this;
	m_AndroidVideoData.InitAndroidVideoData(pIMediaDataManage);
	#endif

	return true;
}

//��������ӿ�
bool CMediaDataManage::SetKernelDataSink(IKernelDataSink *pIKernelDataSink)
{
	m_pIKernelDataSink = pIKernelDataSink;
	return true;
}

//��ʼý��������
bool CMediaDataManage::StartMediaManage()
{
	bool bSuccess=true;
	#ifdef ANDROID_OS
	int nRet=sem_init(&m_semt,0,0);
    if(nRet!=0) return false;
	bSuccess=StartThread();
	#endif

	return bSuccess;
}
//ֹͣý��������
bool CMediaDataManage::StopMediaManage()
{
	#ifdef ANDROID_OS
	m_bRun=false;
	sem_post(&m_semt);
	StopThread(1);
	#endif

	return true;
}

//���úڰ����ݻص��ӿ�
bool CMediaDataManage::SetMediaDataSink(IMediaDataSink *pIMediaDataSink)
{
	m_pIMediaDataSink=pIMediaDataSink;
	return (m_pIMediaDataSink!=NULL);
}

#ifdef ANDROID_OS
//������Ƶ����ӿ�
bool CMediaDataManage::SetAudioManage(IAudioManager *pIAudioManager)
{
	m_pIAudioManager=pIAudioManager;
	return (m_pIAudioManager!=NULL);
}

//������Ƶ�����С(nType=0 ΪRGB����,nType=1ΪYUV����)
bool CMediaDataManage::SetVideoEncodeSize(int cx,int cy,int nType)
{
	return m_AndroidVideoData.SetEncodeVideoSize(cx,cy,nType);
}

//��ʼ��Ƶ����
bool CMediaDataManage::StartVideoEncode()
{
	return m_AndroidVideoData.StartEncodeThread();
}

//ֹͣ��Ƶ����
bool CMediaDataManage::StopVideoEncode()
{
	return m_AndroidVideoData.StopEncodeThread();
}

//����Ӳ���Ƶ����
int CMediaDataManage::AddVideoData(const void *pVideoData,int nDataSize)
{
	return m_AndroidVideoData.AddVideoRgbData(pVideoData,nDataSize);
}

#endif
//��Ƶ����
bool __cdecl CMediaDataManage::OnAudioRTData(const void *pAudioData,DWORD dwDataSize,DWORD dwTimeStamp)
{
	#ifdef ANDROID_OS
	if(m_pIAudioManager!=NULL)
		m_pIAudioManager->PlayAacAudioData(pAudioData,(int)dwDataSize);
	#else
	if(m_dwAudioSeqID>65535)
		m_dwAudioSeqID=0;

	if(m_pIMediaDataSink!=NULL)
		m_pIMediaDataSink->OnAudioRTData(pAudioData,dwDataSize,m_dwAudioSeqID);

	m_dwAudioSeqID++;
	#endif
	return true;
}

//��ƵH264SpsPps����
bool __cdecl CMediaDataManage::OnH264SpsPpsData(DWORD dwChannelID,const void * pSpsPps,DWORD dwDataSize)
{
	if(pSpsPps==NULL) return false;
	if(dwDataSize<2) return true;

	const BYTE *pDstData=(const BYTE *)pSpsPps;
	WORD wSpsSize=pDstData[0];
	BYTE *pSpsData=(BYTE *)pDstData+1;
	BYTE *pPpsData=pSpsData+wSpsSize;
	WORD wPpsSize=pPpsData[0];
	pPpsData+=1;
	if(wSpsSize==0 || wSpsSize>256) return false;
	if(wPpsSize==0 || wPpsSize>128) return false;

	#ifndef ANDROID_OS
	m_pIMediaDataSink->OnH264SpsPpsData((WORD)dwChannelID,pSpsData,wSpsSize);
	m_pIMediaDataSink->OnH264SpsPpsData((WORD)dwChannelID,pPpsData,wPpsSize);
	return true;
	#else
	CThreadLockHandle LockHandle(&m_DataLock);
	m_DataStorage.AddData(AVT_AUDIO,dwChannelID,0,pSpsData,wSpsSize);
	sem_post(&m_semt);
	m_DataStorage.AddData(AVT_AUDIO,dwChannelID,0,pPpsData,wPpsSize);
	sem_post(&m_semt);
	#endif
	
	NetMsgAutoParam(OT_NOOPTION,TEXT("------Add-----OnH264SpsPpsData,DataSize:%d"),dwDataSize);
	return true;
}

//H264��Ƶ��������
bool __cdecl CMediaDataManage::OnVideoH264CodeData(DWORD dwChannelID,const void *pH264Data,DWORD dwDataSize)
{
	//NetMsgAutoParam(OT_NOOPTION,TEXT("------Add-----OnVideoH264CodeData,DataSize:%d"),dwDataSize);
	//return true;
	#ifdef ANDROID_OS
	CThreadLockHandle LockHandle(&m_DataLock);
	m_DataStorage.AddData(AVT_AUDIO,dwChannelID,0,(void *const)pH264Data,(WORD)dwDataSize);
	sem_post(&m_semt);
	#else
	if(m_pIMediaDataSink!=NULL)
		m_pIMediaDataSink->OnVideoH264CodeData((WORD)dwChannelID,pH264Data,dwDataSize);
	#endif

	return true;
}

//������ʾ��Ϣ
bool __cdecl CMediaDataManage::OnErrMsgNotify(int nErrCode,LPCTSTR lpszMsgTxt)
{
	#ifdef ANDROID_OS
	TCHAR szMsg[MAX_PATH]=TEXT("");
	sprintf(szMsg,TEXT("{\"errcode\":%d,\"msg\":\"%s\"}"),nErrCode,lpszMsgTxt);
	OnJavaErrMsg(szMsg);
	#else
	if(m_pIKernelDataSink!=NULL)
        m_pIKernelDataSink->OnLoginRespNotify(0);
//		m_pIKernelDataSink->OnErrMsgNotify(nErrCode,lpszMsgTxt);
	#endif
	return true;
}

//����H264��������
bool __cdecl CMediaDataManage::SendH264CodeData(const void *pH264Data,DWORD dwDataSize)
{
	return true;
}

#ifdef ANDROID_OS
//��ʼ֪ͨ����
bool CMediaDataManage::OnThreadStartEvent()
{
	return (m_VideoData.pDataBuffer!=NULL);
}

//�߳�ֹ֪ͣͨ����
bool CMediaDataManage::OnThreadStopEvent()
{
	return true;
}

//�߳��庯��
bool CMediaDataManage::RepetitionRun()
{
	sem_wait(&m_semt); 
	if(!m_bRun) return false;
	CThreadLockHandle LockHandle(&m_DataLock);
	tagDataHead dHead={0};
	//NetMsgAutoParam(OT_NOOPTION,TEXT("------Video----Start GetData,buffer size:%d"),m_VideoData.wBufferSize);
	m_DataStorage.GetData(dHead,m_VideoData.pDataBuffer,m_VideoData.wBufferSize);
	if(dHead.wDataSize==0) return true;

	m_AndroidVideoData.OnVideoDecoderData(dHead.wChannelID,m_VideoData.pDataBuffer,dHead.wDataSize);

	return m_bRun;
}

#endif
