//////////////////////////////////////////////////////////////////////////////////////////
//		�������ݶ���ͷ�ļ� globaldef.h
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DEIRLYM_OIT_SVR_GLOBAL_DEFINE_HEAD_FILE__
#define __DEIRLYM_OIT_SVR_GLOBAL_DEFINE_HEAD_FILE__

#include "IUnknownEx.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//��ȡ�û����ݹ���ӿ�
struct IUserDataManage
{
	//��ȡ��ǰ����ע����û��б�
	virtual DWORD __cdecl GetLocalRegUserList(void * pUserList)=0;
	//��ȡ�û�����
	virtual bool __cdecl GetUserCount(DWORD &dwUserCount)=0;
	//��ӡ�û���Ϣ
	virtual void __cdecl PrintUserInfo(DWORD dwUserID)=0;
};

#endif //__DEIRLYM_OIT_SVR_GLOBAL_DEFINE_HEAD_FILE__
