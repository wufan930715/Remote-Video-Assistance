////////////////////////////////////////////////////////////////////////////////////
//			媒体数据类头文件 MediaDataManage.h
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
	AVT_AUDIO,				//音频数据
	AVT_VIDEO,				//视频数据
};
///////////////////////////////////////////////////////////////////////////////
class CMediaDataManage: 
#ifdef ANDROID_OS
	public CServiceThread,
#endif
	public IMediaDataManage
{
private:
	DWORD						m_dwAudioSeqID;				//音频序例ID
	IMediaDataSink				*m_pIMediaDataSink;			//媒体数据回调接口
	IKernelDataSink				*m_pIKernelDataSink;		//消息回调接口

private:
	#ifdef ANDROID_OS
	IAudioManager				*m_pIAudioManager;			//音频管理接口
	#endif	

#ifdef ANDROID_OS
private:
	CDataStorage				m_DataStorage;				//数据缓冲
	tagDataBuffer				m_VideoData;				//视频数据大小
	CThreadLock					m_DataLock;					//数据锁

private:
	sem_t						m_semt;						//信号量
	CAndroidVideoData			m_AndroidVideoData;			//Android视频处理
#endif

public:
	CMediaDataManage(void);
	~CMediaDataManage(void);

public:
	//初始化媒体管理
	bool InitMediaManage();
	//设置核心回调接口
	bool SetKernelDataSink(IKernelDataSink *pIKernelDataSink);
	//设置黑板数据回调接口
    bool SetMediaDataSink(IMediaDataSink *pIMediaDataSink);
	#ifdef ANDROID_OS
	//设置音频管理接口
	bool SetAudioManage(IAudioManager *pIAudioManager);
	#endif
	//开始媒体管理服务
	bool StartMediaManage();
	//停止媒体管理服务
	bool StopMediaManage();

public:
	#ifdef ANDROID_OS
	//设置视频编码大小(nType=0 为RGB数据,nType=1为YUV数据)
	bool SetVideoEncodeSize(int cx,int cy,int nType);
	//开始视频编码
	bool StartVideoEncode();
	//停止视频编码
	bool StopVideoEncode();
	//添加视步视频数据
	int AddVideoData(const void *pVideoData,int nDataSize);
	#endif

public:
	//音频数据
	virtual bool __cdecl OnAudioRTData(const void *pAudioData,DWORD dwDataSize,DWORD dwTimeStamp);
	//视频H264SpsPps数据
	virtual bool __cdecl OnH264SpsPpsData(DWORD dwChannelID,const void * pSpsPps,DWORD dwDataSize);
	//H264视频编码数据
	virtual bool __cdecl OnVideoH264CodeData(DWORD dwChannelID,const void *pH264Data,DWORD dwDataSize);
	//发送H264编码数据
	virtual bool __cdecl SendH264CodeData(const void *pH264Data,DWORD dwDataSize);
	//错误提示信息
	virtual bool __cdecl OnErrMsgNotify(int nErrCode,LPCTSTR lpszMsgTxt);

#ifdef ANDROID_OS
protected:
	//开始通知函数
     virtual bool OnThreadStartEvent();
     //线程停止通知函数
     virtual bool OnThreadStopEvent();
     
     //Inside Function
protected:
     //线程体函数
     virtual bool RepetitionRun();
#endif
};

#endif //__BOWEN_HU_MEDIA_DATA_MANAGE_HEAD_FILE__
