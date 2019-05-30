////////////////////////////////////////////////////////////////////////////////////
//			ý��������ͷ�ļ� MediaDataManage.h
//			2016-08-13 Bowen.hu
/////////////////////////////////////////////////////////////////////////////////////
#ifndef __BOWEN_HU_MEDIA_DATA_MANAGE_HEAD_FILE__
#define __BOWEN_HU_MEDIA_DATA_MANAGE_HEAD_FILE__

#include "AndroidVideoData.h"
#include "DataStorage.h"
#ifdef ANDROID_OS
#include "../AudioModule/voice_engine/AudioManager.h"
#else
#include <dispatch/dispatch.h>
#include <dispatch/semaphore.h>
#endif

enum emAVTYPE
{
	AVT_AUDIO,				//��Ƶ����
	AVT_VIDEO,				//��Ƶ����
};
///////////////////////////////////////////////////////////////////////////////
class CMediaDataManage: 
#ifdef ANDROID_OS
	public CServiceThread,
#endif
	public IMediaDataManage
{
private:
	DWORD						m_dwAudioSeqID;				//��Ƶ����ID
	IMediaDataSink				*m_pIMediaDataSink;			//ý�����ݻص��ӿ�
	IKernelDataSink				*m_pIKernelDataSink;		//��Ϣ�ص��ӿ�

private:
	#ifdef ANDROID_OS
	IAudioManager				*m_pIAudioManager;			//��Ƶ����ӿ�
	#endif	

#ifdef ANDROID_OS
private:
	CDataStorage				m_DataStorage;				//���ݻ���
	tagDataBuffer				m_VideoData;				//��Ƶ���ݴ�С
	CThreadLock					m_DataLock;					//������

private:
	sem_t						m_semt;						//�ź���
	CAndroidVideoData			m_AndroidVideoData;			//Android��Ƶ����
#endif

public:
	CMediaDataManage(void);
	~CMediaDataManage(void);

public:
	//��ʼ��ý�����
	bool InitMediaManage();
	//���ú��Ļص��ӿ�
	bool SetKernelDataSink(IKernelDataSink *pIKernelDataSink);
	//���úڰ����ݻص��ӿ�
    bool SetMediaDataSink(IMediaDataSink *pIMediaDataSink);
	#ifdef ANDROID_OS
	//������Ƶ����ӿ�
	bool SetAudioManage(IAudioManager *pIAudioManager);
	#endif
	//��ʼý��������
	bool StartMediaManage();
	//ֹͣý��������
	bool StopMediaManage();

public:
	#ifdef ANDROID_OS
	//������Ƶ�����С(nType=0 ΪRGB����,nType=1ΪYUV����)
	bool SetVideoEncodeSize(int cx,int cy,int nType);
	//��ʼ��Ƶ����
	bool StartVideoEncode();
	//ֹͣ��Ƶ����
	bool StopVideoEncode();
	//����Ӳ���Ƶ����
	int AddVideoData(const void *pVideoData,int nDataSize);
	#endif

public:
	//��Ƶ����
	virtual bool __cdecl OnAudioRTData(const void *pAudioData,DWORD dwDataSize,DWORD dwTimeStamp);
	//��ƵH264SpsPps����
	virtual bool __cdecl OnH264SpsPpsData(DWORD dwChannelID,const void * pSpsPps,DWORD dwDataSize);
	//H264��Ƶ��������
	virtual bool __cdecl OnVideoH264CodeData(DWORD dwChannelID,const void *pH264Data,DWORD dwDataSize);
	//����H264��������
	virtual bool __cdecl SendH264CodeData(const void *pH264Data,DWORD dwDataSize);
	//������ʾ��Ϣ
	virtual bool __cdecl OnErrMsgNotify(int nErrCode,LPCTSTR lpszMsgTxt);

#ifdef ANDROID_OS
protected:
	//��ʼ֪ͨ����
     virtual bool OnThreadStartEvent();
     //�߳�ֹ֪ͣͨ����
     virtual bool OnThreadStopEvent();
     
     //Inside Function
protected:
     //�߳��庯��
     virtual bool RepetitionRun();
#endif
};

#endif //__BOWEN_HU_MEDIA_DATA_MANAGE_HEAD_FILE__
