/////////////////////////////////////////////////////////////////////////////
//	���ݴ洢��ͷ�ļ� DataStorage.h
////////////////////////////////////////////////////////////////////////////
#ifndef __DEIRLYM_DATA_STORAGE_HEAD_FILE__
#define __DEIRLYM_DATA_STORAGE_HEAD_FILE__

#include "localdef.h"

////////////////////////////////////////////////////////////////////////////
//struct tagDataHead
//{
//	WORD							wIdentifier;
//	WORD							wChannelID;
//	WORD							wDataSize;
//	DWORD							dwTimeSpan;
//};
//
//struct tagDataBuffer
//{
//	WORD							wDataSize;
//	WORD							wBufferSize;
//	BYTE							*pDataBuffer;
//};

//////////////////////////////////////////////////////////////////////////
//���ݴ洢��
class CDataStorage
{
	//���ݱ���
protected:
	DWORD							m_dwDataSize;						//���ݴ�С
	DWORD							m_dwBufferSize;						//����������
	DWORD							m_dwInsertPos;						//���ݲ���λ
	DWORD							m_dwTerminalPos;					//���ݽ���λ
	DWORD							m_dwDataQueryPos;					//���ݲ�ѯλ
	DWORD							m_dwDataPacketCount;				//���ݰ���Ŀ
	BYTE							*m_pDataStorageBuffer;				//����ָ��

	//��������
public:
	//���캯��
	CDataStorage(void);
	//��������
	virtual ~CDataStorage(void);

	//���ܺ���
public:
	//������Ϣ
	bool GetBurthenInfo(tagBurthenInfo & BurthenInfo);
	//��������
	bool AddData(WORD wIdentifier,WORD wChannelID,DWORD dwTime, void * const pBuffer, WORD wDataSize);
	//��ȡ����
	bool GetData(tagDataHead & DataHead, void * pBuffer, WORD wBufferSize);
	//ɾ������
	void RemoveData(bool bFreeMemroy);

private:
	//�����ڴ�
	bool RenewDataBuffer(WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////

#endif	//__DEIRLYM_DATA_STORAGE_HEAD_FILE__
