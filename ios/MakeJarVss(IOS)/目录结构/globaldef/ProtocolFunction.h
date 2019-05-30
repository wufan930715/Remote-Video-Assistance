///////////////////////////////////////////////////////////////////////////////////////////////
//	Э�鴦����ͷ�ļ� ProtocolFunction.h
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DEIRLYM_PROTOCOL_FUNCTION_HEAD_FILE__
#define __DEIRLYM_PROTOCOL_FUNCTION_HEAD_FILE__

#include "globaldef.h"

/////////////////////////////////////////////////////////////////////////////////////////////
//��BYTE
BYTE * ReadByte(BYTE * pData,BYTE & cbValue);
const BYTE * ReadByte(const BYTE * pData,BYTE & cbValue);
BYTE * ReadByte(BYTE * pData,BYTE & cbValue,WORD & wReadLen);
const BYTE * ReadByte(const BYTE * pData,BYTE & cbValue,WORD & wReadLen);

//дBYTE
BYTE * WriteByte(BYTE * pData,BYTE cbValue);
BYTE * WriteByte(BYTE * pData,BYTE cbValue,WORD & wWriteLen);


//����
BYTE * ReadWord(BYTE * pData,WORD & wValue);
const BYTE * ReadWord(const BYTE * pData,WORD & wValue);
BYTE * ReadWord(BYTE * pData,WORD & wValue,WORD & wReadLen);
const BYTE * ReadWord(const BYTE * pData,WORD & wValue,WORD & wReadLen);

//д��
BYTE * WriteWord(BYTE * pData,WORD wValue);
BYTE * WriteWord(BYTE * pData,WORD wValue,WORD & wWriteLen);


//��˫��
BYTE * ReadDword(BYTE * pData,DWORD & dwValue);
const BYTE * ReadDword(const BYTE * pData,DWORD & dwValue);
BYTE * ReadDword(BYTE * pData,DWORD & dwValue,WORD & wReadLen);
const BYTE * ReadDword(const BYTE * pData,DWORD & dwValue,WORD & wReadLen);

//��int16
BYTE * ReadInt16(BYTE * pData,__int16 & nValue);
const BYTE * ReadInt16(const BYTE * pData,__int16 & nValue);
BYTE * ReadInt16(BYTE * pData,__int16 & nValue,WORD & wReadLen);

//��int32
BYTE * ReadInt32(BYTE * pData,__int32 & nValue);
const BYTE * ReadInt32(const BYTE * pData,__int32 & nValue);
BYTE * ReadInt32(BYTE * pData,__int32 & nValue,WORD & wReadLen);
const BYTE * ReadInt32(const BYTE * pData,__int32 & nValue,WORD & wReadLen);

//д˫��
BYTE * WriteDword(BYTE * pData,DWORD dwValue);
BYTE * WriteDword(BYTE * pData,DWORD dwValue,WORD & wWriteLen,bool bHtohl=true);

//дint16
BYTE * WriteInt16(BYTE * pData,__int16 nValue);
BYTE * WriteInt16(BYTE * pData,__int16 nValue,WORD & wWriteLen);
//дint32
BYTE * WriteInt32(BYTE * pData,__int32 nValue);
BYTE * WriteInt32(BYTE * pData,__int32 nValue,WORD & wWriteLen);


//��64λ��
BYTE * ReadUNDword(BYTE * pData,UNDWORD & undwValue);
const BYTE * ReadUNDword(const BYTE * pData,UNDWORD & undwValue);
BYTE * ReadUNDword(BYTE * pData,UNDWORD & undwValue,WORD & wReadLen);
const BYTE * ReadUNDword(const BYTE * pData,UNDWORD & undwValue,WORD & wReadLen);

//д64λ��
BYTE * WriteUNDword(BYTE * pData,UNDWORD undwValue);
BYTE * WriteUNDword(BYTE * pData,UNDWORD undwValue,WORD & wWriteLen);

//��ȡָ������
BYTE * ReadToBuffer(BYTE * pData,void * pDest,WORD wLength);
const BYTE * ReadToBuffer(const BYTE * pData,void * pDest,WORD wLength);
BYTE * ReadToBuffer(BYTE * pData,void * pDest,WORD wLength,WORD & wReadLen);
const BYTE * ReadToBuffer(const BYTE * pData,void * pDest,WORD wLength,WORD & wReadLen);

//дָ������
BYTE * WriteFromBuffer(BYTE * pDestBuffer,const void *pSrcData,WORD wLength);
BYTE * WriteFromBuffer(BYTE * pDestBuffer,const void *pSrcData,WORD wLength,WORD & wWriteLen);

//��������
CMD_Command BuildCommand(WORD wMainCmd,WORD wSubCmd,DWORD dwSequenceID);
//����������
DWORD BuildCommandID(WORD wMainCmd,WORD wSubCmd);


#endif //__DEIRLYM_PROTOCOL_FUNCTION_HEAD_FILE__
