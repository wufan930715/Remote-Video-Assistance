//////////////////////////////////////////////////////////////////////////////////////////
//		�������ݶ���ͷ�ļ� globaldef.h
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DEIRLYM_VIDEO_CAPTURE_LOCAL_DEFINE_HEAD_FILE__
#define __DEIRLYM_VIDEO_CAPTURE_LOCAL_DEFINE_HEAD_FILE__

#include <list>
#include <map>
#include <vector>
#include "IUnknownEx.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned __int64 UNDWORD;

///////////////////////////////
//�汾��
#define MAKEVER(m,s)	((m<<8)|(s))	//���ɰ汾��
//����汾1.2
#define DVR_CAP_VER		MAKEVER(1,2)	//DVR �汾
#define CURR_NET_VER	MAKEVER(1,4)	//��ǰ����汾

//��������ά��
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))
//�����ַ�����
#define CountString(String) ((UINT)((lstrlen(String)+1)*sizeof(TCHAR)))

//Э���ͷ�ṹ
typedef struct CMD_Head
{
	DWORD					dwTotalLength;						//���ݰ��ܳ�
	union
	{
		DWORD					dwCommandID;					//������
		struct
		{
			WORD				wMainCmd;						//������
			WORD				wSubCmd;						//������
		};
	};
	DWORD					dwSequenceID;						//���к�

}CMDHEAD;

//����ṹ
typedef struct CMD_Command
{
	union
	{
		DWORD					dwCommandID;					//������
		struct
		{
            WORD				wMainCmd;						//������
			WORD				wSubCmd;						//������
		};
	};
	DWORD					dwSequenceID;						//���к�

}CMDCOMMAND;

//////////////////////////////////////////////////////////////////////////////////////////
//	�������ݶ���
#define SOCKET_VER					2									//���ݰ��汾
#define SOCKET_PACKAGE				(1024*10)    						//����������ݰ�
#define SOCKET_BUFFER				(SOCKET_PACKAGE+sizeof(CMD_Head))	//���绺���С

#define SOCKVALUE(v,i,r) {(v)=(i);(v)<<=16;(v)|=(r);}
#define SOCKINDEX(v,i,r) {(i)=(WORD)((v)>>16);(r)=(WORD)(v);}
////////////////////////////////////////////////////////////////////////////////////////
//��������������
//��������
#define ALL_MAIN_CMD				0x5000						//ͨ��������
#define LOGIN_MAIN_CMD				0x5001						//��¼����������
#define CTRL_MAIN_CMD				0x5002						//���Ʒ���������
#define TEACH_MAIN_CMD				0x5003						//��ѧ����������

//////////////////////////////////////////////////////////////////////////////////////////
//�������
//�������������������
#define ACITVE_TEST					0x0000						//��������������
#define ACITVE_TEST_RESP			0x1000						//��������������

///////////////////////////////////////////////////////////////////////////
//��¼������������
#define LSVR_TEACHER_LOGIN			0x0001						//��ʦ��¼����¼������
#define LSVR_TEACHER_LOGIN_RESP		0x1001						//��ʦ��¼����¼������Response
#define LSVR_STUDENT_LOGIN			0x0002						//�û���¼��������
#define LSVR_STUDENT_LOGIN_RESP		0x1002						//�û���¼��������Response
#define LSVR_ROOMCLASS_DATA			0x0003						//��������
#define LSVR_ROOMCLASS_DATA_RESP	0x1003						//��������Response

//���Ʒ�����������
#define CSVR_TEACHER_LOGIN			0x0101						//��ʦ��¼�����Ʒ�����
#define CSVR_TEACHER_LOGIN_RESP		0x1101						//��ʦ��¼�����Ʒ�����Response
#define CSVR_STUDENT_LOGIN			0x0102						//ѧ����¼�����Ʒ�����
#define CSVR_STUDENT_LOGIN_RESP		0x1102						//ѧ����¼�����Ʒ�����
#define CSVR_CTRLCMD_TRANS			0x0103						//����ָ���
#define CSVR_CTRLCMD_TRANS_RESP		0x1103						//����ָ���Response
#define CSVR_SLOGIN_NOTIFY			0x0104						//ѧ����¼֪ͨ
#define CSVR_SLOGIN_NOTIFY_RESP		0x1104						//ѧ����¼֪ͨ

//��ѧ������������
#define TSVR_TEACHER_LOGIN			0x0201						//��ʦ��¼����ѧ������
#define TSVR_TEACHER_LOGIN_RESP		0x1201						//��ʦ��¼����ѧ������Response
#define TSVR_STUDENT_LOGIN			0x0202						//ѧ����¼����ѧ������
#define TSVR_STUDENT_LOGIN_RESP		0x1202						//ѧ����¼����ѧ������Response
#define TSVR_TEACHER_TRACK			0x0203						//��ʦ��д�켣����
#define TSVR_TEACHER_TRACK_RESP		0x1203						//��ʦ��д�켣����Response
#define TSVR_STUDEND_TRACK			0x0204						//ѧ��д�켣
#define TSVR_STUDEND_TRACK_RESP		0x1204						//ѧ��д�켣Response
#define TSVR_TEACHER_AUDIO			0x0205						//��ʦ��Ƶ
#define TSVR_TEACHER_AUDIO_RESP		0x1205						//��ʦ��ƵResponse
#define TSVR_STUDENT_AUDIO			0x0206						//ѧ����Ƶ
#define TSVR_STUDENT_AUDIO_RESP		0x1206						//ѧ����ƵResponse


//���ؾ��������������
#define LBS_REQUEST_SVRIP			0x0301						//����IP��ַ
#define LBS_REQUEST_SVRIP_RESP		0x1301						//����IP��ַResponse
#define LBS_SVR_LB_DATA				0x0302						//��������������
#define LBS_SVR_LB_DATA_RESP		0x1302						//��������������Response
#define LBS_BSVR_REGISTER			0x0303						//ҵ�������ע��
#define LBS_BSVR_REGISTER_RESP		0x1303						//ҵ�������ע��Response

///////////////////////////////////////////////////////////////////////////////////////
//������
#define DB_SVR_EXPECT				-1							//�������쳣
#define NAME_PASS_ERR				-2							//�û������������
#define CTRL_LOGIN_ERR				-3							//���Ʒ�������֤����
#define ADD_BSVR_FAILD				-4							//���ҵ�������ʧ��
#define CREATE_ROOM_FAILD			-5							//��������ʧ��
#define ADD_TO_ROOM_FAILD			-6							//��ӵ�����ʧ��

/////////////////////////////////////////////////////////////////////////////////////////
#ifndef AfxDebugBreak
#ifndef MYASSERT
#define MYASSERT
#define AfxDebugBreak()    _asm { int 3 }
#define ASSERT(f) \
	if (!(f)) \
		AfxDebugBreak();
#define VERIFY(f)          ASSERT(f)
#endif
#endif

//////////////////////////////////////////////////////////////
#define RECTWIDTH(rc) (rc.right-rc.left)
#define RECTHEIGHT(rc) (rc.bottom-rc.top)
/////////////////////////////////////////////////////////////////////
//�ַ����ṹ
struct my_str_t
{
	int      len;
    BYTE     *data;
};

#define CLEAR_MY_STR(str) {(str).data=NULL;(str).len=0;}
#define FREE_MY_STR(str) {if(str.data!=NULL){delete []str.data;str.data=NULL;str.len=0;}}
#define NEW_MY_STR(str,size) {if(str.len<size){if(str.data!=NULL){delete[] str.data;str.data=NULL;	\
	str.len=0;}str.data=new BYTE[size];if(str.data==NULL) return; str.len=size;}}
#define SET_MY_STR(str,dat,size) {if(str.data!=NULL){	delete []str.data;	str.data=NULL;str.len=0;} \
	str.data=new BYTE[size+1];if(str.data!=NULL){str.len=size; memcpy(str.data,dat,size);str.data[size]=0;}}

//////////////////////////////////////////////////////////////////////////////////////////

#ifndef INVALID_DATA_DFINE
#define INVALID_DATA_DFINE
#define INVALID_WORD				((WORD)(-1))						//��ЧWORD ����
#define INVALID_DWORD				((DWORD)(-1))						//��ЧDWORD ����
#endif

//64bit�����ֽ����������
UNDWORD htonl64(UNDWORD ulSrc);
UNDWORD ntohl64(UNDWORD ulSrc);
int EncCheckCode(LPCSTR pszUserName,int nLength,CHAR * pCheckCode,int nMonth,int nDay,int nHour,int nMinute,int nSecond);
int EncCheckCode(LPCSTR pszUserName,int nLength,CHAR * pCheckCode);
int EncCheckCode(DWORD dwID,LPCSTR pszUserName,int nLength,CHAR * pCheckCode);
void EncCheckCode(UNDWORD undwMobile,CHAR * pCheckCode);
void DecCheckCode(const CHAR * pCheckCode,UNDWORD &undwMobile);
bool DecCheckCode(const CHAR * pCheckCode,LPSTR pszUserName);
bool DecCheckCode(DWORD dwID,const CHAR * pCheckCode,LPSTR pszUserName);

//UTF8 תΪ GBK
int UTF8ToGBK(const char * utf8Str,char * pGBKBuffer,int nGBKBuffSize);
//GBK תΪ UTF8
int GBKToUTF8(const char * gbkStr,char *pUTF8Buffer,int nUTF8Size);

void OutTextByColor(LPCTSTR lpszText,WORD wColor);
////////// ���Ͷ��� /////////////////////////////////////////////////////////////////////////////
typedef map<UNDWORD,DWORD>							CUNDwordMap;					//�������б�
typedef map<UNDWORD,DWORD>::iterator				CUNDwordMapIt;					//�������б�

#define NAME_LEN				32
#define CHECKCODE_MAXLEN		128		
#define BUFF_SIZE				64
///////////////////////////////////////////////////////////////////////
#define SHARE_MEM_NAME		TEXT("deir_ite_app_share")
#define MAX_BUFF_SIZE		1356

/////////////////////////////////////////////////////////////////////
//����������
typedef enum enIteServerType
{
	ST_LOGINSVR,				//��¼������
	ST_CTRLSVR,					//���Ʒ�����
	ST_TEACHSVR,				//��ѧ������
	ST_MAX_SVR,					//����������
}ITESERVERTYPE;

//�ͻ�������
typedef enum emIteClientType
{
	CT_UNKNOWN = 0,					//δ֪�ͻ���
	CT_TEACH = 1,					//��ѧ�ͻ���
	CT_STUDENT = 2,					//ѧ��PC�ͻ���
	CT_STUDENT_IOS = 4,				//ѧ��ios�ͻ���
	CT_STUDENT_ANDR = 8,			//ѧ��ANDROID�ͻ���
	CT_STUCENT_ALL = (CT_STUDENT | CT_STUDENT_IOS | CT_STUDENT_ANDR),
	
}ITECLIENTTYPE;

//����״̬
typedef enum emIteRoomStatus
{
	RS_INVALID,				//��Ч
	RS_VALID,				//��Ч
}ITEROOMSTATUC;


//�μ���������
typedef enum emCWDataType
{
	CWDT_LINE=1,			//�߶�����
	CWDT_AUDIO,				//��Ƶ����
	CWDT_VIDEO,				//��Ƶ����
	CWDT_LINEWIDTH,			//�޸��߶ο�
	CWDT_LINECOLOR,			//�޸��߶���ɫ
	CWDT_UNDO,				//�����߶�
	CWDT_CLEAR,				//�����ڰ�����
	CWDT_NEW_BB,			//�ºڰ�
	CWDT_PREV_BB,			//��һҳ�ڰ�
	CWDT_NEXT_BB,			//��һҳ�ڰ�
	CWDT_ASK_BEGIN,			//���⿪ʼ
	CWDT_ASK_END,			//�������

}CWDATATYPE;

//����ָ��ö��
typedef enum emTeachCtrlCmd
{
	TCC_UNDO_LINE = CWDT_UNDO,			//�����߻���
	TCC_CLS_BLACKBOARD =CWDT_CLEAR,		//�����ڰ�
	TCC_LINE_WIDTH =CWDT_LINEWIDTH,		//�޸��߿�
	TCC_LINE_COLOR =CWDT_LINECOLOR,		//�޸�����ɫ

}TEACHCTRLCMD;


//�������ݽṹ
typedef struct tagShareMemData
{
	HWND					hMainWnd;			//�����������ھ��
	HWND					hParentWnd;			//ie �����ھ��
	HWND					hWebWnd;			//ie����Web�����ھ��
	WORD					wDataSize;			//���ݴ�С
	BYTE					cbBuffer[MAX_BUFF_SIZE];//���ݻ�����
}SHAREMEMDATA;

//������Ϣ
struct tagBurthenInfo
{
	DWORD							dwDataSize;							//���ݴ�С
	DWORD							dwBufferSize;						//����������
	DWORD							dwDataPacketCount;					//���ݰ���Ŀ
};

//��������
typedef struct tagLoadData
{
	DWORD			dwConnCount;			//����������
	DWORD			dwRecvCount;			//�յ���¼��
	DWORD			dwTransCount;			//ת����¼��
	DWORD			dwFaildCount;			//ʧ�ܼ�¼��
}LOADDATA;

//��ʦ��������
typedef struct tagClassRoomData
{
	DWORD			dwRoomCount;		//������(1/3)
	DWORD			dwRoomID;			//����ID
	DWORD			dwTeacherID;		//��ʦID
	DWORD			dwStartTime;		//��ʼʱ��
	DWORD			dwEndTime;			//����ʱ��
	int				nTotalPeriod;		//�ܿ�ʱ
	int				nUsedPeriod;		//���ÿ�ʱ
	int				nRoomStatus;		//����״̬
	WORD			wCtrlSvrPort;		//���Ʒ������˿�
	WORD			wChatSvrPort;		//����������˿�
	CHAR			szCtrlSvrUrl[BUFF_SIZE];	//���Ʒ�����Url
	CHAR			szChatSvrUrl[BUFF_SIZE];	//���������Url
	TCHAR			szRoomName[BUFF_SIZE];		//������
	TCHAR			szTeacherName[BUFF_SIZE];	//��ʦ��
	TCHAR			szRoomDiscrible[1024];	//��������
}CLASSROOMDATA;

//��������
typedef struct tagClassRoomInfo
{
	DWORD			dwRoomID;				//����ID
	DWORD			dwTeacherID;			//��ʦID
	DWORD			wUserCount;				//�û���
	WORD			wIndex;					//��ʦSocket����
	WORD			wRoundID;				//��ʦSocket���ü���
	SIZE			blackboardSize;			//�ڰ��С
}CLASSROOMINFO;

//////////////////////////////////////////////////
#ifdef _UNICODE
#define mysprintf _swprintf_c
#else
#define mysprintf _snprintf_c
#endif
//////////////////////////////////////////////////////
//��ȡ�������ݽӿ�
struct IClassRoomData
{
	//��ȡ�û������ͽ�����
	virtual bool __cdecl GetClassRoomData(DWORD &dwUserCount,DWORD &dwRoomCount)=0;
};

#endif //__DEIRLYM_VIDEO_CAPTURE_LOCAL_DEFINE_HEAD_FILE__
