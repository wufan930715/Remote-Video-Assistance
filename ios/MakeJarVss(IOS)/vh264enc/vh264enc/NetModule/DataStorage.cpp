///////////////////////////////////////////////////////////////////////////
//		 DataStorage.cpp
///////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DataStorage.h"
#include "custom_log.h"

#define VIDEO_BUFFER_SIZE		1024*1024*10
//BYTE g_cbVideoBuffer[VIDEO_BUFFER_SIZE];
#define CopyMemory	memcpy
//////////////////////////////////////////////////////////////////////////

//���캯��
CDataStorage::CDataStorage(void)
{
	m_dwDataSize=0;
	m_dwBufferSize=0;
	m_dwInsertPos=0;
	m_dwTerminalPos=0;
	m_dwDataQueryPos=0;
	m_dwDataPacketCount=0;
	m_pDataStorageBuffer=NULL;
}

//��������
CDataStorage::~CDataStorage(void)
{
	SafeDeleteArray(m_pDataStorageBuffer);
	return;
}

//������Ϣ
bool CDataStorage::GetBurthenInfo(tagBurthenInfo & BurthenInfo)
{
	//���ñ���
	BurthenInfo.dwDataSize=m_dwDataSize;
	BurthenInfo.dwBufferSize=m_dwBufferSize;
	BurthenInfo.dwDataPacketCount=m_dwDataPacketCount;

	return true;
}

//�����ڴ�
bool CDataStorage::RenewDataBuffer(WORD wDataSize)
{
	try
	{
		//�����ڴ�
		DWORD dwNewBufferSize=m_dwBufferSize+(wDataSize+sizeof(tagDataHead))*2L;
		BYTE * pNewQueueServiceBuffer=new BYTE [dwNewBufferSize];
		if (pNewQueueServiceBuffer==NULL) return false;

		//��������
		if (m_pDataStorageBuffer!=NULL) 
		{
			ASSERT(m_dwTerminalPos>=m_dwDataSize);
			ASSERT(m_dwTerminalPos>=m_dwDataQueryPos);
			DWORD dwPartOneSize=m_dwTerminalPos-m_dwDataQueryPos;
			if (dwPartOneSize>0L) CopyMemory(pNewQueueServiceBuffer,m_pDataStorageBuffer+m_dwDataQueryPos,dwPartOneSize);
			if (m_dwDataSize>dwPartOneSize) 
			{
				ASSERT((m_dwInsertPos+dwPartOneSize)==m_dwDataSize);
				CopyMemory(pNewQueueServiceBuffer+dwPartOneSize,m_pDataStorageBuffer,m_dwInsertPos);
			}
		}

		//��������
		m_dwDataQueryPos=0L;
		m_dwInsertPos=m_dwDataSize;
		m_dwTerminalPos=m_dwDataSize;
		m_dwBufferSize=dwNewBufferSize;
		SafeDeleteArray(m_pDataStorageBuffer);
		m_pDataStorageBuffer=pNewQueueServiceBuffer;

		return true;
	}
	catch (...)
	{}

	return false; 
}

//��������
bool CDataStorage::AddData(WORD wIdentifier,WORD wChannelID,DWORD dwTime, void * const pBuffer, WORD wDataSize)
{
	//��ʼ������
	tagDataHead DataHead;
	DataHead.wDataSize=wDataSize;
	DataHead.wIdentifier=wIdentifier;	
//	DataHead.wChannelID=wChannelID;
//	DataHead.dwTimeSpan=dwTime;
	DWORD dwCopySize=sizeof(tagDataHead)+wDataSize;

	//Ч�黺����
	if ((m_dwDataSize+dwCopySize)>m_dwBufferSize)
	{
		if(!RenewDataBuffer(wDataSize)) return false;
	}
	else if((m_dwInsertPos==m_dwTerminalPos)&&((m_dwInsertPos+dwCopySize)>m_dwBufferSize)) 
	{
		if (m_dwDataQueryPos>=dwCopySize) 
		{
			m_dwInsertPos=0;
		}
		else 
		{
			if(!RenewDataBuffer(wDataSize))
				return false;
		}
	}
	else if ((m_dwInsertPos<m_dwTerminalPos)&&((m_dwInsertPos+dwCopySize)>m_dwDataQueryPos)) 
	{
		if(!RenewDataBuffer(wDataSize))
			return false;
	}	
	 
	try
	{
		//��������
		CopyMemory(m_pDataStorageBuffer+m_dwInsertPos,&DataHead,sizeof(tagDataHead));
		if (wDataSize>0) 
		{
			ASSERT(pBuffer!=NULL);
			CopyMemory(m_pDataStorageBuffer+m_dwInsertPos+sizeof(tagDataHead),pBuffer,wDataSize);
		}

		//��������
		m_dwDataPacketCount++;
		m_dwDataSize+=dwCopySize;
		m_dwInsertPos+=dwCopySize;
		m_dwTerminalPos=__max(m_dwTerminalPos,m_dwInsertPos);

		return true;
	}
	catch (...) { }

	return false;
}

//��ȡ����
bool CDataStorage::GetData(tagDataHead & DataHead, void * pBuffer, WORD wBufferSize)
{
	//Ч�����
	if (m_dwDataSize==0L) return false;
	if (m_dwDataPacketCount==0L) return false;

	//��������
	if (m_dwDataQueryPos==m_dwTerminalPos)
	{
		m_dwDataQueryPos=0L;
		m_dwTerminalPos=m_dwInsertPos;
	}

	//��ȡ����ָ��
	ASSERT(m_dwBufferSize>=(m_dwDataQueryPos+sizeof(tagDataHead)));
	BYTE *pSrcData=(BYTE *)(m_pDataStorageBuffer+m_dwDataQueryPos);
	tagDataHead * pDataHead=(tagDataHead *)pSrcData;
	ASSERT(wBufferSize>=pDataHead->wDataSize);

	//��ȡ����С
	WORD wPacketSize=sizeof(tagDataHead)+pDataHead->wDataSize;
	ASSERT(m_dwBufferSize>=(m_dwDataQueryPos+wPacketSize));

	//�жϻ���
	WORD wCopySize=0;
	ASSERT(wBufferSize>=pDataHead->wDataSize);
	if (wBufferSize>=pDataHead->wDataSize) wCopySize=pDataHead->wDataSize;

	//��������
//	DataHead.dwTimeSpan=pDataHead->dwTimeSpan;
//	DataHead.wChannelID=pDataHead->wChannelID;
	DataHead.wDataSize=pDataHead->wDataSize;
	DataHead.wIdentifier=pDataHead->wIdentifier;
	if (DataHead.wDataSize>0)
	{
		pSrcData+=sizeof(tagDataHead);
		if (wBufferSize<pDataHead->wDataSize) DataHead.wDataSize=0;
		else CopyMemory(pBuffer,pSrcData,DataHead.wDataSize);
	}

	//Ч�����
	//LOGE(TEXT("------DataStorage----GetData wPacketSize:%d,m_dwDataSize:%d,BufferSize:%d"),wPacketSize,m_dwDataSize,m_dwBufferSize);
	ASSERT(wPacketSize<=m_dwDataSize);
	ASSERT(m_dwBufferSize>=(m_dwDataQueryPos+wPacketSize));

	//���ñ���
	m_dwDataPacketCount--;
	m_dwDataSize-=wPacketSize;
	m_dwDataQueryPos+=wPacketSize;

	return true;
}

//ɾ������
void CDataStorage::RemoveData(bool bFreeMemroy)
{
	//���ñ���
	m_dwDataSize=0;
	m_dwInsertPos=0;
	m_dwTerminalPos=0;
	m_dwDataQueryPos=0;
	m_dwDataPacketCount=0;

	//ɾ���ڴ�
	if (bFreeMemroy==true) 
	{
		m_dwBufferSize=0;
		SafeDeleteArray(m_pDataStorageBuffer);
	}

	return;
}
//////////////////////////////////////////////////////////////////////////
