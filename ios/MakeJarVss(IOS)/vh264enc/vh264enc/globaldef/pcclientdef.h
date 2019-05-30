//////////////////////////////////////////////////////////////////////////////////////////
//		PC�ͻ���ȫ�ֶ���ͷ�ļ� pcclientdef.h
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DEIRLYM_PC_CLIENT_GLOBAL_DEFINE_HEAD_FILE__
#define __DEIRLYM_PC_CLIENT_GLOBAL_DEFINE_HEAD_FILE__

//////////////////////////////////////////////////////////////////////////
//�Ի��򱳾�ɫ
#define PROCESS_IMG_SIZE	50							//����ͼƬ��С
#define DLG_BG_COLOR		RGB(128,128,128)
#define TOOLBAR_BG_COLOR	RGB(247,247,247)			//����������
#define	TOOLBAR_LINE_COLOR	RGB(161,161,161)			//����������ɫ
#define WND_BG_COLOR		RGB(200,200,200)			//���ڱ���ɫ
#define NOLOGIN_USER_COLOR	RGB(128,128,128)			//δ��¼��ɫ
#define LOGIN_USER_COLOR	RGB(64,64,255)				//��¼����ɫ
#define MSG_WND_BG_COLOR	RGB(0,0,0)					//�ı���Ϣ���ڱ���ɫ
#define LOGIN_LINE_COLOR	RGB(206,214,218)			//��¼��������ɫ
#define DEFAULT_FONT_SIZE	40							//Ĭ�������С

#define MSG_WND_TOP_OFFSET	3							//��Ϣ״̬����topƫ����
#define MSG_ITEM_WIDTH		980							//�������
#define MSG_ITEM_HEIGHT		85							//�������
#define MSG_ITEM_SAPCE		10							//���Լ��
#define LINE_POS_SPACE		2.0							//�ߵ��������С����

////////////////////////////////////////////////////////////////////
#define WND_BORDER			6							//�߿��
#define MAIN_GB_COLOR		RGB(114,161,195)			//�����ڱ���ɫ
///////Tab�������� //////////////////////////////////////////////////////////
#define TAB_LEFT_CX			1				//TAB������߾�
#define TAB_SPACE			1				//TAB����
#define CLASS_MAXTAB_NUM	8				//�Ͽ����TAB��
#define MSG_TAB_COUNT		2				//��ϢTAB��
#define SEL_TXT_COLOR		RGB(8,74,108)		//ѡ�����ı���ɫ
#define NOR_TXT_COLOR		RGB(255,255,255)	//�������ı���ɫ
#define HAVE_TXT_COLOR		RGB(98,200,240)		//��ͣ���ı���ɫ
#define MID_BG_COLOR		RGB(238,238,238)	//�м䱳��ɫ
#define RE_TEXT_COLOR		RGB(0,28,0)			//RichEdit �ı���������ɫ
#define RE_WARING_COLOR		RGB(128,128,24)		//������ɫ
#define RE_EXCEPT_COLOR		RGB(128,24,24)		//�쳣��ɫ
#define RE_DEBUG_COLOR		RGB(24,128,24)		//������ɫ
#define RE_HIGH_COLOR		RGB(128,128,255)	//������ɫ
#define VIDEO_BG_COLOR		RGB(28,28,28)		//��Ƶ����ɫ
#define LIST_TXT_COLOR		RGB(254,254,254)
#define TEMP_DLG_BG_COLOR	RGB(42,102,148)		//ģ��Ի��򱳾�ɫ
#define TIMER_TXT_COLOR		RGB(255,255,0)		//ʱ���ı�ɫ
#define TITLE_TXT_COLOR		RGB(64,64,64)		//�����ı�ɫ
////////////////////////////////////////////////////////////////////
//�Զ�����Ϣ
#define WM_CLOSE_STATUSWND			(WM_USER + 97)			//�ر�״̬����
#define WM_START_IN_ROOM			(WM_USER + 98)			//��ʼ�������
#define WM_START_LOGIN				(WM_USER + 99)			//��ʼ��¼��Ϣ
#define WM_LINE_PARAM_CHANGE		(WM_USER + 100)			//�����������
#define WM_BOARD_OPT_EVENT			(WM_USER + 101)			//�ڰ�����¼�
#define WM_USER_OPT_EVENT			(WM_USER + 102)			//�û������¼�

#define WM_SHOW_ASK_BOARD			(WM_USER + 103)			//��ʾ�����
#define WM_SHOW_WRITE_BOARD			(WM_USER + 104)			//��ʾ��д��

#define WM_CLOSE_PROCESS_DLG		(WM_USER + 106)			//�رս��ȶԻ�����Ϣ
#define WM_STUDENT_LIST_CLOSE		(WM_USER + 107)			//ѧ�������б�ر���Ϣ
#define WM_USER_SETUP_OPT			(WM_USER + 108)			//�û�������Ϣ
#define WM_BEGIN_CLASS				(WM_USER + 109)			//��ʼ�Ͽ���Ϣ
#define WM_TXT_CHAT_MSG				(WM_USER + 111)			//�ı�������Ϣ
#define WM_DOWNLOAD_FINISH			(WM_USER + 112)			//�����ļ����
#define WM_UPFILE_PROCESS			(WM_USER + 113)			//�ϴ�ͼƬ������Ϣ
#define WM_ROOM_EVENT_MSG			(WM_USER + 114)			//�����¼���Ϣ
#define WM_NEW_REPLY_MSG			(WM_USER + 116)			//�½���ظ�������Ϣ
#define WM_REPLY_DLG_CLOSE			(WM_USER + 117)			//�ظ����ԶԻ���ر���Ϣ
#define WM_MSG_PAGE_CHANGE			(WM_USER + 118)			//���Է�ҳ��Ϣ
#define WM_ROOM_PAGE_CHANGE			(WM_USER + 119)			//���ҷ�ҳ��Ϣ
#define WM_FLASH_BUTTON				(WM_USER + 120)			//��ť��˸��Ϣ
#define WM_UPDATE_VER				(WM_USER + 120)			//�汾������Ϣ
#define WM_SHOW_NOTIFY_MSG			(WM_USER + 121)			//��ʾ֪ͨ��Ϣ����
#define	WM_LOAD_ROOM_MSG			(WM_USER + 122)			//�������ؽ�����Ϣ
#define WM_UPDATE_GIFT_NUM			(WM_USER + 123)			//������Ʒ����Ϣ
#define WM_TOOLBAR_OPT_MSG			(WM_USER + 124)			//������������Ϣ
#define WM_MPLAY_PROGRESS			(WM_USER + 125)			//ý�岥�������Ϣ
#define WM_PAGE_NUM_CHANGE			(WM_USER + 126)			//ҳ���ı���Ϣ
#define WM_DOWN_CR_RES				(WM_USER + 127)			//���ؽ�����Դ��Ϣ
#define WM_TAB_SWITCH				(WM_USER + 128)			//tab�л���Ϣ
#define WM_CW_PROC_END_MSG			(WM_USER+129)			//�μ��������֪ͨ��Ϣ
#define WM_ADD_CW_TO_LIST			(WM_USER+130)			//��ӿμ����б�
#define WM_LOAD_DATA_FINISHED		(WM_USER+131)			//�������������Ϣ
#define WM_USE_CW_TO_CLASS			(WM_USER+132)			//ʹ�ÿμ������Ͽ���Ϣ
#define WM_SWITCH_BB_OR_BROWSER		(WM_USER+133)			//�л��ڰ�������
#define WM_ADD_PPTIMG_TO_BOARD		(WM_USER+134)			//���pptͼƬ���ڰ�
#define WM_END_CLASS				(WM_USER+135)			//�¿���Ϣ
#define WM_SNAP_BTN_MSG				(WM_USER+136)			//������ť��Ϣ

///////////////////////////////////////////////////////////////////////
//��ʱ��ID
#define IDT_CONN_SERVER					0x0001					//���Ӷ���¼��������ʱ��ID
#define IDT_SVR_CLOSE					0x0002					//�������Ͽ�(�ر�)
#define IDT_STATUS_ANIMATION			0x0003					//״̬���ڶ�����ʱ��
#define IDT_START_AUDIO					0x0004					//������Ƶ��ʱ��
#define IDT_READ_AACDATA				0x0005					//��ȡAAC����
#define IDT_SHOWSTUDENTLISTWND			0x0006					//��ʾѧ���б��ڶ�ʱ��ID
#define IDT_ANSWER_STATUS_ID			0x0007					//�����ش�״̬��ʱ��
#define IDT_SHOE_ERRMSG_ID				0x0008					//��ʾ������Ϣ��ʱ��
#define IDT_AUDIO_GRAPHICS				0x0009					//����ͼ��
#define IDT_SHOW_CHAT_ROOM				0x000A					//��ʾ���촰�ڶ�ʱ��
#define IDT_UPLOAD_BBCW					0x000B					//�ϴ��μ��ڰ�ҳ��ʱ��
#define IDT_ADD_BBC_IMG					0x000C					//��ӿμ��ڰ�ҳͼƬ��ʱ��
#define IDT_UPLOAD_COURSE_FILE			0x000D					//�ϴ��μ��ļ���ʱ��
#define IDT_UPLOAD_COURSE_FILE1			0x000E					//�ϴ��μ��ļ���ʱ��
#define IDT_DOWNLOAD_IMAGE				0x000F					//����ͼƬ��ʱ��
#define IDT_LOOP_PLAY_CW				0x0010					//ѭ�����ſμ�
#define IDT_MSG_CONN_TEST				0x0011					//��Ϣ���������Ӳ��Զ�ʱ��
#define IDT_TEACH_CONN_TEST				0x0012					//��ѧ���������Ӳ��Զ�ʱ��
#define IDT_LOADING_ANIMATE				0x0013					//���ض�����ʱ��
#define IDT_CLASS_DURATION				0x0014					//�Ͽ�ʱ����ʱ��
#define IDT_AUTO_INROOM					0x0015					//�Զ�������Ҷ�ʱ��
#define IDT_SNAPSHOT_SHOW				0x0016					//����������ʾ��ʱ��
#define IDT_LINK_TIMEOUT				0x0017					//���ӳ�ʱ��ʱ��
#define IDT_DOWN_CR_RES					0x0018					//���ؽ�����Դ
#define IDT_EDIT_PAGE_SYNC				0x0019					//����ҳ��ͬ�����ݼ�¼
#define IDT_DOWNLOAD_CW_FILE			0x001A					//���ؿμ��ļ���ʱ��

//Http API ָ��
#define HAPI_COURSE_LIST				10001					//���ؿγ��б�
#define HAPI_STUDENT_LIST				10002					//����ѧ���б�
#define HAPI_TEACH_CW_LIST				10003					//��ȡ��ʦ�μ��б�
#define HAPI_CW_BG_IMG_LIST				10004 					//��ȡ�μ�����ͼ�б�
#define HAPI_TEACH_RES_LIST				10005			 		//��ȡ��ʦ��Դ�б�
#define HAPI_ADD_CW_BG_IMG				10006 					//��ӿμ�����ͼ
#define HAPI_ADD_CW_FILE				10007 					//��ӿμ��ӿ�
#define HAPI_ADD_TRES_FILE				10008			 		//��ӽ�ʦ��Դ�ļ�
#define HAPI_DEL_TRES_FILE				10009			 		//ɾ����ʦ��Դ
#define HAPI_UPDATE_CW_DATA				10010					//���¿μ���¼����
#define HAPI_DEL_CW_BG_IMG				10011					//ɾ���μ�����ͼƬ
#define HAPI_DEL_CW_REC_DATA			10012					//ɾ���μ���¼
#define HAPI_ADD_PREPARE_BG_ULR			10013					//��ӿ�ǰ׼��ͼƬ����url
#define HAPI_EDIT_PAGE_SYNC				10014					//�޸�ҳ����ͬ����¼ָ��
#define HAPI_EDIT_CW_LOCAL_PATH			10016					//�޸Ŀμ�����·��
#define HAPI_GET_UESR_CW_LIST			10017					//��ȡѧ���μ��б�

////////////////////////////////////////////////////////////////////////////////////////
//��ťID����
enum emToolButtonID
{
	BTN_BASE =	32767,
	BTN_MIN_ID,				//��С����ť
	BTN_MAX_ID,				//��󻯰�ť
	BTN_MAX2_ID,			//�ָ���ť
	BTN_CLOSE_ID,			//�رհ�ť
	BTN_INROOM_ID,			//������Ұ�ť
	BTN_ADDTOROOM_ID,		//������Ұ�ť
	
	BTN_LOGIN_CLOSE_ID,		//��¼���ڹرհ�ť
	BTN_LOGIN_ID,			//��¼��ť
	BTN_SAVEPWD_ID,			//�������밴ť

	BTN_SLW_ID,				//�����߿�ť
	BTN_SLC_ID,				//��������ɫ��ť
	BTN_SBGC_ID,			//���ñ���ɫ��ť
	BTN_UNDO_ID,			//������ť
	BTN_CLEAR_ID,			//�����ť

	BTN_CLASSES_INROOM,		//�������
	BTN_CLASSES_BEGIN,		//��ʼ�Ͽ�
	BTN_FINISH_CLASS,		//�¿�

	BTN_CLASS_PAUSE_ID,		//�Ͽ���ͣ��ť

	BTN_SHAREFILE_ID,		//�����ļ���ť
	BTN_SHARESCREEN_ID,		//������Ļ��ť

	BTN_QUESTION_END_ID,	//��ʦ��������
	BTN_HANDSASK_ID,		//���ֻش�ť
	BTN_ROOMCHAT_ID,		//�������찴ť
	BTN_ASK_FINISH_ID,		//�ش���ɰ�ť
	BTN_SUHL_CLOSE,			//���ֽ���رհ�ť
	BTN_S_REQUESTION_ID,	//ѧ�����ʰ�ťID
	BTN_S_MUTE_ID,			//ѧ��������ťID
	

	BTN_ROOM_CLOSE_ID,		//����رհ�ť
	BTN_ROOM_CONNECT_ID,	//�������Ӱ�ť

	BTN_PROCESS_CANCEL_ID,	//���ȶԻ���ȡ����ť

	BTN_INPUT_ENTER_ID,		//�ı�����ȷ����ť
	BTN_HIDE_CHAT_WND_ID,	//�������촰�ڰ�ťID
	BTN_CHAT_NOTIFY_ID,		//������Ϣ֪ͨ��ťID	
	BTN_COURSE_LIST_ID,		//�μ��б�ťID

	IDC_INPUT_TEXT_EDIT,	//�ı�����ؼ�ID

	BTN_PAGE_FIST_ID,		//��һҳ��ťID
	BTN_PAGE_PREV_ID,		//��ҳ��һҳ��ťID
	BTN_PAGE_NEXT_ID,		//��ҳ��һҳ��ťID
	BTN_PAGE_LAST_ID,		//���һҳ��ťID
	BTN_PAGE_ADD_ID,		//���ҳ��ťID

	CBB_PAGE_GOTO_ID,		//��ҳת��ҳ������ID
	BTN_MSG_LIST_WND_ID,	//�����б��ڰ�ťID
	BTN_NEW_QUESTION_ID,	//�½����԰�ťID
	BTN_ROOM_PREV_PAGE_ID,	//������һҳ��ťID
	BTN_ROOM_NEXT_PAGE_ID,	//������һҳ��ťID
	BTN_BACK_ID,			//���ذ�ťID
	BTN_STUDENT_LIST_ID,	//ѧ���б�ťID
	BTN_ROOM_CATEGORY_ID,	//�������ťID

	BTN_TOPBAR_AUDIO_ID,	//��Ƶ���ð�ť
	BTN_TOPBAR_VIDEO_ID,	//��Ƶ���ð�ť
	BTN_TOPBAR_MYCOUSRE_ID,	//�ҵĿμ���ťID
	BTN_TOPBAR_RECORD_ID,	//¼�ƿμ���ťID
	BTN_TOPBAR_HOMEWORK_ID,	//��ҵ��ťID
	BTN_TOPBAR_REST_ID,		//��Ϣ��ťID
	BTN_TOPBAR_SCREENSHARE_ID,//��Ļ����
	BTN_TOPBAR_CLASS_ID,	//���¿ΰ�ťID

	BTN_ALL_NO_SPEAK_ID,	//ȫ�����԰�ťID
	BTN_ALL_INPUT_MSG_ID,	//ȫ�������밴ťID
	BTN_ONLINE_REQUESTION_ID,//�������ʰ�ť
	BTN_CLASS_PREPARE_ID,	//��ǰ׼��

	BTN_PLAY_ID,			//���Ű�ťid
	BTN_STOP_ID,			//ֹͣ��ťid

	BTN_ID_MAX_VALUE,		//��ť���ID��
};

//������������
typedef enum emLeaveMsgType
{
	MT_TEXT,			//����
	MT_IMAGE,			//ͼƬ
	MT_AUDIO,			//��Ƶ
	MT_VIDEO,			//��Ƶ
}LEAVEMSGTYPE;

//�����ļ�����
typedef enum emDownFileType
{
	DFT_NETIMG=1,			//�������ͼƬ
	DFT_CWFILE,				//�μ��ļ�
	DFT_PPTFILE,			//PPT�ļ�
}DOWNFILETYPE;

//�˵�idö��
enum emMenuItemID
{
	IDM_PLAY_COURSEWARE=BTN_ID_MAX_VALUE+1,	//���ſμ�
	IDM_LOOP_PLAY_COURSEWARE,				//ѭ�����ſμ�
	IDM_INSERT_PLAY_COURSEWARE,				//�岥�μ�
	IDM_PAUSE_COURSEWARE,					//��ͣ���ſμ�
	IDM_RESUME_COURSEWARE,					//�ָ����ſμ�
	IDM_STOP_COURSEWARE,					//ֹͣ����
	IDM_UPLOAD_VIDEOCOURSEWARE,				//�ϴ���Ƶ�μ�
	IDM_INSERT_IMAGE,						//����ͼƬ
	IDM_INSERT_SNAP_IMG,					//������Ļ��ͼͼƬ
	IDM_DEL_IMAGE,							//ɾ��ͼƬ
	IDM_ZOOM_IMAGE,							//����ͼƬ
	IDM_ZOOM_FINISH,						//�������
	IDM_SCREEN_SNAPSHOT,					//��Ļ��ͼ
	IDM_OPEN_OTHER_FILE,					//�������ļ�

	IDM_REFRESH_CW,							//ˢ�¿μ�
	IDM_ADD_MY_CW,							//����ҵĿμ�
	IDM_EDIT_CW_PPT,						//�޸Ŀμ�PPT
	IDM_ADD_CW_PPT,							//��ӿμ�PPT
	IDM_DELETE_CW,							//ɾ���μ�
	IDM_UPLOAD_CW_FILE,						//�ϴ��μ��ļ�
	IDM_USE_CW_PPT,							//ʹ��PPT�Ͽ�
	IDM_PLAY_CW_FILE,						//���ſμ�

	IDM_ADD_CLASS_RES,						//����Ͽ���Դ
	IDM_DEL_CLASS_RES,						//ɾ���Ͽ���Դ
	IDM_CLIENT_PLAY,						//�ͻ��˲���
	IDM_BBOARD_PLAY,						//�ڰ��ϲ���

	IDM_DELETE_COURSE,						//ɾ���μ��˵���
	IDM_INPUT_FONT_SIZE,					//���������С
	IDM_ALLOW_VOICE,						//��������ͨ��
	IDM_FORBID_VOICE,						//��ֹ����ͨ��
	IDM_ADD_PPT_FILE,						//����PPT�ļ�
	IDM_OPEN_COURSE_DIR,					//�򿪿μ�Ŀ¼
	IDM_ANSWERBB_SNAPSHOT,					//������ͼ
	IDM_ANSWERBB_REVIEWS,					//��������
	IDM_ADD_MP3_FILE,						//����mp3��Ƶ�ļ�
	IDM_SET_TIME_PLAY,						//���ö�ʱ���Ų˵�
	IDM_INSERT_NEW_PAGE,					//�����¿հ�ҳ
};

//�������ݽṹ
typedef struct tagMsgData
{
	UNDWORD		nMsgID;						//����ID
	UNDWORD		nRoomID;					//����ID
	UNDWORD		nTeacherID;					//��ʦID
	UNDWORD		nStudentID;					//ѧ��ID
	int			nQtype;						//��������
	int			nAtype;						//�ش�����
	int			nMsgUserType;				//�����û�����(0=ѧ��,1=��ʦ)
	char		szRoomName[BUFF_SIZE];		//��������
	char		szTeacherName[BUFF_SIZE];	//��ʦ����
	char		szStudentName[BUFF_SIZE];	//ѧ������
	char		szQTime[NAME_LEN];			//����ʱ��
	char		szATime[NAME_LEN];			//��ʱ��
	int			nQLength;					//�������ݳ�
	char		*pQuestion;					//��������
	int			nALength;					//�ش����ݳ�
	char		*pAnswer;					//������
}MSGDATA;

typedef struct tagEditMsgData
{
	UNDWORD		nMsgID;						//����ID
	UNDWORD		nRoomID;					//����ID
	UNDWORD		nUserID;					//�û�ID
	int			nQLength;					//���ʳ�
	TCHAR		*pQuestion;					//����������

}EDITMSGDATA;

typedef struct tagChatMsgItem
{
	WORD		wMsgType;					//��Ϣ����
	int			nItemHeight;				//���
	DWORD		dwUserID;					//�û�ID��
	TCHAR		szUserName[64];
	TCHAR		szTime[32];
	TCHAR		szMsgContent[MSG_MAX_SIZE];
}CHATMSGITEM;

#ifdef _WIN32
//�������Ͷ���
typedef CMemManage<CHATMSGITEM>				CTxtMsgMem;				//�ı�������Ϣ�ڴ����
#endif

//���ز����ṹ
typedef struct tagDownParam
{
	WPARAM				wParam;
	my_str_t			mJson;
	int					ldt;
	void				*pIHttpEventSink;
	CHAR				szDownUrl[URL_LEN];
}DOWNPARAM;

//�γ�����(�γ̱��Ͽα���--Ŀ¼)
typedef struct tagCourseData
{
	DWORD				dwCourseID;				//�γ�ID
	DWORD				dwRoomID;				//����ID
	int					nPeriodNum;				//��ʱ
	DWORD				dwStartTime;			//��ʼʱ��
	DWORD				dwEndTime;				//����ʱ��
	TCHAR				szPeriodName[URL_LEN];	//��ʱ����
}COURSEDATA;

//��ʦ�Ͽομ�����
typedef struct tagCoursewareData
{
	DWORD				dwCWID;					//�μ�ID
	DWORD				dwRoomID;				//����ID
	int					nPeriodNum;				//��ʱ
	BOOL				bHavePpt;				//�Ƿ���PPT
	int					nStatus;				//�μ�״̬(0=�½���1=���Ͽ�(��ppt)��2=�ɲ���(�пμ�))
	DWORD				dwCreateTime;			//����ʱ��
	TCHAR				szRoomName[NAME_LEN];	//��������
	TCHAR				szCwName[NAME_LEN];		//�μ���
	CHAR				szCWFileUrl[URL_LEN];	//�μ��ļ�URL
	CHAR				szCWLocalPath[MAX_PATH];	//�μ�����·��
}COURSEWAREDATA;

//�μ�����ͼ����
typedef struct tagCWBGImage
{
	int					nImgCount;				//ͼƬ��
	DWORD				dwCWID;					//�μ�ID
	int					nPageIndex;				//ҳ����
	CHAR				szResUrl[URL_LEN];		//��ԴURL
	CHAR				szLocalPath[MAX_PATH];	//����URL
}CWBGIMAGE;

//�޸Ŀμ�����
typedef struct tagEditCWData
{
	DWORD				dwCWID;					//�μ�ID
	int					nDataType;				//��������(1=PPT״̬,2=�μ�URL,3=���߶�ʱ)
	int					nHavePpt;				//�Ƿ���PPT
	CHAR				szCWUrl[URL_LEN];		//�μ�URL
	CHAR				szCWLocalPath[MAX_PATH];//�μ�����·��
}EDITCWDATA;

//�Ͽ�ҳ�汳��ͼ
typedef struct tagClassPageBGImg
{
	DWORD				dwUserID;				//�û�(��ʦID)
	DWORD				dwRoomID;				//����ID
	int					nPeriodNum;				//��ʱ
	int					nPageNum;				//ҳ��
	CHAR				szImgUrl[URL_LEN];		//����ͼURL
	CHAR				szLocalPath[URL_LEN];	//����ͼURL
}CLASSPAGEBGIMG;

//�Ͽ���Դ����
typedef enum emClasResType
{
	CRT_AUDIO,								//��Ƶ
	CRT_VIDEO,								//��Ƶ
	CRT_CWD,								//oit�μ�
	CRT_IMAGE,								//ͼƬ
}CLASSRESTYPE;

//��ʦ�Ͽ���Դ����
typedef struct tagClassResFile
{
	DWORD			dwResID;				//��ԴID
	DWORD			dwTeacherID;			//��ʦID
	int				nResType;				//��Դ����
	DWORD			dwCreateTime;			//����ʱ��
	TCHAR			szResName[NAME_LEN];	//��Դ����
	CHAR			szResUrl[URL_LEN];		//��Դurl
	TCHAR			szLocalPath[MAX_PATH];	//����·��
}CLASSRESFILE;

typedef struct tagPageSync
{
	DWORD				dwUserID;					//�û�ID(��ʦID)
	DWORD				dwRoomID;					//����ID
	int					nPeriodNum;					//��ǰ��ʱ
	int					nFaildCount;				//ʧ�ܴ���
	int					nPageNum;					//ҳ������
	CHAR				szbbcUrl[URL_LEN];			//ҳ���ļ�url
	CHAR				szLocalFile[MAX_PATH];		//�����ļ�
}PAGESYNC;
//////////////////////////////////////////////////////////////////////////////////////
typedef vector<POINT>					CPointVector;			//�����б���
typedef vector<POINT>::iterator			CPointVectorIt;			//�����б��������
typedef vector<DRAWELEMENT>				CElementVector;			//����Ԫ���б���
typedef vector<DRAWELEMENT>::iterator	CElementVectorIt;		//����Ԫ���б��������

/////////////////////////////////////////////////////////////////////////////////////
typedef vector<LINEINFO>				CLineInfoVec;			//������ϢVector
typedef vector<LINEINFO>::iterator		CLineInfoVecIt;			//������ϢVector������

typedef list<RECT>					CRectList;
typedef list<RECT>::iterator		CRectListIt;
///////////////////////////////////////////////////////////////////////////////////////
//������Ϣ֪ͨ�ӿ�
interface INetMsgNotify
{
	//��Ϣ֪ͨ
	virtual bool __cdecl NetMsgNotify(LPCTSTR lpszMsg,ITEOPTIONTYPE nOptType=OT_NOOPTION)=0;
	//��Ϣ֪ͨ
	virtual bool __cdecl NetMsgAutoParam(ITEOPTIONTYPE nOptType,LPCTSTR lpszFormate,...)=0;
};

//����ӿ�
interface ITxtMsgChat
{
	//��ȡ�ı���Ϣ�ڴ�
	virtual void * __cdecl GetTxtMsgItem()=0;
	//���������Ϣ
	virtual void __cdecl AddTxtMsgItem(void * pMsgItem)=0;
};


#endif //__DEIRLYM_PC_CLIENT_GLOBAL_DEFINE_HEAD_FILE__
