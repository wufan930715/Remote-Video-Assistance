////////////////////////////////////////////////////////////////////////////////////
//			Android ��Ƶ������ͷ�ļ� AndroidVideoData.h
//			2016-08-13 Bowen.hu
/////////////////////////////////////////////////////////////////////////////////////
#ifndef __BOWEN_HU_ANDROID_VIDEO_DATA_HEAD_FILE__
#define __BOWEN_HU_ANDROID_VIDEO_DATA_HEAD_FILE__

#include "ClientModule.h"
#include "localdef.h"
#ifdef ANDROID_OS
#include "../VideoCodec/libVideoDecoder/decode2.h"
#include "../VideoCodec/libVideoEncoder/x264_encoder.h"
#endif

#define MAX_WCX			640				//�����Ƶ��
#define MAX_WCY			480				//�����Ƶ��
#define VT_RGB			0				//RGB����
#define VT_YUV			1				//YUV����
/////////////////////////////////////////////////////////////////////////////////////
class CAndroidVideoData
	#ifdef ANDROID_OS
	: public CServiceThread
	#endif
{
#ifdef ANDROID_OS
private:
	BYTE						*m_pYuvData;				//YUV����
	int							m_nYuvSize;					//Yuv���ݴ�С
	BOOL						m_bHaveKeyFrame;			//�йؼ�֡
	//CH264Decoder				m_H264Decoder;				//H264������

private:
	int							m_nDataType;				//��������
	int							m_nVideoCX;					//��Ƶ��
	int							m_nVideoCY;					//��Ƶ��
	BYTE						*m_pRgbBuffer;				//�ز���RGB����
	int							m_nRgbBuffSize;				//RGB�����С
	BYTE						*m_pH264Data;				//H264����
	//CX264Encoder				m_H264Encoder;				//H264������
	CThreadLock					m_RgbDataLock;				//��Ƶ������
	bool						m_bHaveRgbData;				//��RGB���ݱ�־
	DWORD						m_dwLastAddTime;			//���һ�����RGBʱ��
	DWORD						m_dwWaitTime;				//֡���ʱ��
	IMediaDataManage			*m_pIMediaDataManage;		//ý�����ӿ�
#endif

public:
	CAndroidVideoData(void);
	~CAndroidVideoData(void);

public:
	#ifdef ANDROID_OS
	//��ʼ��ý�����
	bool InitAndroidVideoData(IMediaDataManage *pIMediaDataManage);
	//���ñ�����Ƶ��С
	bool SetEncodeVideoSize(int cx,int cy,int nType);
	//�����ƵRGB����
	bool AddVideoRgbData(const void *pRgbData,int nDataSize);
	//��ȡSpsPps����
	int GetSpsPpsData(BYTE *pSpsPps,int nBufferSize);
	//���������߳�
	bool StartEncodeThread();
	//ֹͣ�����߳�
	bool StopEncodeThread();

protected:
	//��ʼ֪ͨ����
	virtual bool OnThreadStartEvent();
	//�߳�ֹ֪ͣͨ����
	virtual bool OnThreadStopEvent();
	//�߳��庯��
	virtual bool RepetitionRun();
	#endif

public:
	//��Ƶ����
	bool OnAudioRTData(const void *pAudioData,DWORD dwDataSize);
	//����H264��Ƶ����
	bool OnVideoDecoderData(WORD wChannelID,const void *pH264Data,DWORD dwDataSize);

};

#endif //__BOWEN_HU_ANDROID_VIDEO_DATA_HEAD_FILE__
