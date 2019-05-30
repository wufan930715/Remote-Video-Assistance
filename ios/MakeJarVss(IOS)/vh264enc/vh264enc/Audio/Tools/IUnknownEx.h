// //////////////////////////////////////////////////////////////////////////////////////////
//  Module Interface  parent interface head file IUnknownEx.h
//  Other all interface parent interface
//  Author : deirlym
//  time:   2008-08-13
//  Version: 2.0
// ////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DEIRLYM_IUNKNOWN_EX_HEAD_FILE__
#define __DEIRLYM_IUNKNOWN_EX_HEAD_FILE__

#ifndef WIN32
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <string>
    #include <assert.h>
    #include <dlfcn.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/wait.h>
    #include <arpa/inet.h>
    #include <sys/time.h>
    #include <semaphore.h>
    #include <sys/ipc.h>
    #include <signal.h>
    #include <errno.h>
    #include <stdarg.h>
    #include <time.h>
	#include <netdb.h>
	#include <sys/types.h>

//#define _DEBUG
// ///////////////////////////////////////////////////////////////////////////////////////////
    typedef unsigned short WORD;
    typedef unsigned int DWORD;
    typedef unsigned int UINT;
    typedef long	DDWORD;
    typedef unsigned long long UDWORD;
    typedef unsigned long long ULONGLONG;
    typedef long long INT64;
    typedef long long LONGLONG;
    typedef int   INT;
	typedef UDWORD UNDWORD;
	typedef long	LONG;

    #define MAX_PATH                    260

    typedef unsigned char BYTE;
    typedef  const char * LPCTSTR;
	typedef LPCTSTR			LPCSTR;
    typedef char *            LPTSTR;
    typedef char *            LPSTR;
    typedef char              TCHAR;
    typedef long              LONG;
	typedef int               MYBOOL;
    typedef int               INT;
    typedef int               MYBOOL;
    typedef unsigned char     UCHAR;
    typedef WORD            WTCHAR; 
	typedef TCHAR			CHAR;	
	typedef short			__int16;
	typedef short			SHORT;
	typedef int				__int32;
	
    typedef int INT_PTR, *PINT_PTR;
    typedef unsigned int UINT_PTR, *PUINT_PTR;
    typedef long LONG_PTR, *PLONG_PTR;
    typedef unsigned long ULONG_PTR,*PULONG_PTR;

    typedef UINT_PTR            WPARAM;
    typedef LONG_PTR            LPARAM;
    typedef LONG_PTR            LRESULT;

	typedef void *		HWND;
    typedef void *      HANDLE;                     //handle
    typedef void *      HINSTANCE;                  //instance handle
    typedef unsigned int         SOCKET;                     
    #define INVALID_SOCKET      (SOCKET)(~0)
    #define TRUE            1
    #define FALSE           0

    #define STRARRAY(str) (sizeof(str)/sizeof(str[0]));
    #define ZeroMemory(objPtr,nSize) (memset(objPtr,0,nSize));

    #ifndef CONTAINING_RECORD
    #define CONTAINING_RECORD(address,type,field) \
        ((type*)((char *)(address)-(ULONG_PTR)(&((type*)0)->field)))
    #endif

    #define TEXT(quote) quote

    typedef struct sockaddr SOCKADDR;
    typedef struct sockaddr_in SOCKADDR_IN;
    #define closesocket(s) close(s)
    #define SOCKET_ERROR              (-1)

    #define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD)(a) & 0xff)) | ((WORD)((BYTE)((DWORD)(b) & 0xff))) << 8))
    #define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD)(b) & 0xffff))) << 16))
    #define LOWORD(l)           ((WORD)((DWORD)(l) & 0xffff))
    #define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))
    #define LOBYTE(w)           ((BYTE)((DWORD)(w) & 0xff))
    #define HIBYTE(w)           ((BYTE)((DWORD)(w) >> 8))

    // ///////////////////////////////////////////////////////////////////////////////////////////
    //time struct define
    typedef struct tagSystemTime
    {
        WORD                              wYear;
        WORD                              wMonth;
        WORD                              wDay;
        WORD                              wHour;
        WORD                              wMinute;
        WORD                              wSecond;           
    }SYSTEMTIME,*PSYSTEMTIME;

	#define BUILD_VERSION(a,b,c,d)	((a)<<24)|((b)<<16)|((c)<<8)|(d)
	#define GET_VERSION(dest,ver)	dest[0]=(ver>>24);dest[1]=(ver>>16)&0x000000FF;dest[2]=(ver>>8)&0x000000FF;dest[3]=ver&0x000000FF;

	//ģ����Ϣ�ṹ
	typedef struct tagModuleInfo
	{
		DWORD							dwVersion;						//�汾��
		DWORD							dwMouleCode;					//ģ����
		DWORD							dwProperty;						//ģ������ֵ
		TCHAR							szInterfaceName[32];			//ʵ�ֽӿ���
		TCHAR							szName[64];						//ģ������
		SYSTEMTIME						stCreateTime;					//����ʱ��
		SYSTEMTIME						stUpdateTime;					//����ʱ��
        TCHAR							szDescribe[128];				//���		
	}MODULEINFO,*PMODULEINFO;

	//��֤ģ��汾
	#define CHECK_MODULE_VER(pIUnknownExEx,dwVer)														\
			MODULEINFO *_pcheckModuleInfo=(MODULEINFO *)pIUnknownExEx->GetModuleInfo();					\
			if(_pcheckModuleInfo->dwVersion<dwVer)														\
			{																							\
				BYTE cbVer[4];																			\
				GET_VERSION(cbVer,dwVersion);															\
				printf("ģ��[%s]�汾̫�ͣ������ܼ������У���ʹ��[%d.%d.%d.%d]���ϵİ汾��\n",		\
				_pcheckModuleInfo->szName,cbVer[0],cbVer[1],cbVer[2],cbVer[3]);								\
				exit(1);																				\
			}	

	//д�浽��־
	#define WRITE_VERSION(pLogInterface,szInfo,szVer)				\
			TCHAR		_writeVerMsg[256]="";					\
			snprintf(_writeVerMsg,sizeof(_writeVerMsg),"*******************  %s %s ********************",szInfo,szVer);	\
			pLogInterface->WriteString(_writeVerMsg);

    // build time
    #define __max(a,b) ((a>b)?a:b)
    #define __min(a,b) ((a<b)?a:b)

    #ifdef _DEBUG
        #define ASSERT(a) assert(a)
        #define myprintf(str) printf(str)
    #else
        #define ASSERT(a) ((void)0)
        #define myprintf(str) ((void)0)
    #endif 

    #define lstrcpy(dest,src) strcpy(dest,src)
    #define lstrlen(str) (int)strlen(str)
    #define lstrcat(dest,str) strcat(dest,str)
    #define lstrcmp(str1,str2) strcmp(str1,str2)

    //�¼��ṹ��
    typedef struct tagEventHandle
    {
        sem_t							semt;
        struct tagEventHandle          *pPrev;
        struct tagEventHandle          *pNext;
    }*EVENTHANDLE;

   #define INFINITE            0xFFFFFFFF  // Infinite timeout

#ifndef __IPHONE_4_0
	#define __cdecl  
	#define interface struct
#endif

	typedef struct hostent *LPHOSTENT;

#include "DataType.h"
#else
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
typedef int               MYBOOL;

#endif //WIN32

#define CREATE_FUNC_NAME            "CreateInterfaceObject"

#define BUILDTIME(year,month,day,hour,minute,second) (((year-2000)<<28)|(month<<24)|(day<<18)|(hour<<12)|(minute<<6)|(second))
#define YEAR(value) ((value>>28)+2000)  //��ȡ��
#define MONTH(value) ((value & 0x0F000000)>>24) //��
#define DAY(value) ((value & 0x00FC0000)>>18)	//��
#define HOUR(value) ((value & 0x0003F000)>>12)	//ʱ
#define MINUTE(value) ((value & 0x00000FC0)>>6)	//��
#define SECOND(value) (value & 0x0000003F)  //��
#define BUILDSEQUENCE(day,hour,minute,second,index) (((day%16)<<28)|(hour<<23)|(minute<<17)|(second<<11)|(index))
#define INVALID_VALUE ((WORD)-1)
// ///////////////////////////////////////////////////////////////////////////////////////////
//product version
#define PRODUCT_VER                 1

//Version define
#define INTERFACE_VERSION(cbMainVer,cbSubVer)                   \
        (DWORD)(                                            \
        (((BYTE)(PRODUCT_VER))<<24)+                           \
        ((BYTE)(cbMainVer)<<16)+                                \
        ((BYTE)(cbSubVer)<<8))
       
//Get product version
inline BYTE GetProductVer(DWORD dwVersion)
{
    BYTE * cbVersion=(BYTE*)&dwVersion;
    return cbVersion[0];
}  
//Get Main version
inline BYTE GetMainVer(DWORD dwVersion)
{
    BYTE * cbVersion=(BYTE*)&dwVersion;
    return cbVersion[1];
}
//Get sub version
inline BYTE GetSubVer(DWORD dwVersion)
{
    BYTE * cbVersion=(BYTE*)&dwVersion;
    return cbVersion[2];
}
//Get sub build version
inline BYTE GetBuildVer(DWORD dwVersion)
{
    BYTE * cbVersion=(BYTE *)&dwVersion;
    return cbVersion[3];
}
//Version cmp
inline bool InterfaceVersionCheck(DWORD dwQueryVer,DWORD dwInterfaceVer)
{
    if(GetProductVer(dwQueryVer)!=GetProductVer(dwInterfaceVer)) return false;
    if(GetMainVer(dwQueryVer)!=GetMainVer(dwInterfaceVer)) return false;
    if(GetSubVer(dwQueryVer)!=GetSubVer(dwInterfaceVer)) return false;
    return true;
}


// ///////////////////////////////////////////////////////////////////////////////////////////
#ifndef COUNTARRAY
#define COUNTARRAY
//Count array size
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))   
//Computer string length
#define CountString(string) ((UINT)((lstrlen(string)+1)*sizeof(TCHAR)))
#endif

//Safe delete point
#define SafeDelete(pData) {try{delete pData;}catch(...){} pData=NULL;}
#define SafeDeleteArray(pData){try{delete [] pData;}catch(...){} pData=NULL;}    


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Error info length
#define LEN_ERROR           256

#ifndef WIN32
    // ///////////////////////////////////////////////////////////////////////////////////////////
    // Interface define
    #define STD_METHOD (TYPE,METHOD) virtual TYPE METHOD
    // Interface module create function
    typedef void * (ModuleCreateFunc)(DWORD dwInterfaceVer);

    //base interface
    #define VER_IUnknownEx  INTERFACE_VERSION(1,1)
    class IUnknownEx
    {
    public:
        //Is validate
        virtual bool IsValid()=0;
        //Release object
        virtual bool Release()=0;
        //Interface query
        virtual void * QueryInterface(DWORD dwQueryVer)=0;
    };
	
	//��չ�����ӿ�
	#define VER_IUnknownExEx  INTERFACE_VERSION(1,2)
	class IUnknownExEx :public IUnknownEx
    {
    public:
        //��ȡģ����Ϣ
		virtual void * GetModuleInfo()=0;
    };
            
    //Interface Query
    #define QUERYINTERFACE(Interface,dwQueryVer)                     \
            if(InterfaceVersionCheck(dwQueryVer,VER_##Interface))    \
                return static_cast<Interface *>(this);

    //Query base interface
    #define QUERYINTERFACE_IUNKNOWNEX(BaseInterface,dwQueryVer)     \
            if(InterfaceVersionCheck(dwQueryVer,VER_IUnknownEx))    \
                return static_cast<IUnknownEx *>(static_cast<BaseInterface*>(this))

	//Query base interface
    #define QUERYINTERFACE_IUNKNOWNEXEX(BaseInterface,dwQueryVer)     \
            if(InterfaceVersionCheck(dwQueryVer,VER_IUnknownExEx))    \
                return static_cast<IUnknownExEx *>(static_cast<BaseInterface*>(this))
               
    //Get owner interface
    #define GET_MYSELF_INTERFACE(Interface)                                             \
        (Interface *)QueryInterface(VER_##Interface)
         
    //Get object interface
    #define GET_OBJECT_INTERFACE(Object,Interface)                                         \
        (Interface *)Object.QueryInterface(VER_##Interface)
          
    //Get object point interface
    #define GET_OBJECTPTR_INTERFACE(pObject,Interface)                                  \
        ((pObject==NULL)?NULL:((Interface*)pObject->QueryInterface(VER_##Interface)))

///////////////////////////////////////////////////////////////////////////////////////////
    // Module helper template class
    template<typename IModuleInterface>
    class CTemplateHelper
    {
    //variable define
    protected:    
        LPCTSTR                     m_pszFuncName; 
        LPCTSTR                     m_pszModuleDll;
        HINSTANCE                   m_hDllInstance; 
        const DWORD                 m_dwVersion;                  
        IModuleInterface            *m_pIModuleInterface; 
        TCHAR                       m_szErrorMsg[LEN_ERROR]; 
        
    //function define
    public:
    //construct function
        CTemplateHelper(DWORD dwVer,LPCTSTR pszModuleDll,LPCTSTR pszFuncName)
    :m_dwVersion(dwVer)
        {
            m_szErrorMsg[0]=0;        
            m_hDllInstance=NULL;
            m_pIModuleInterface=NULL;
            m_pszFuncName=pszFuncName;        
            m_pszModuleDll=pszModuleDll;        
        }        
        virtual ~CTemplateHelper()
        {
            CloseInstance();
        }
    //function
    public:
        //set member value
        bool SetModuleName(LPCTSTR pszModuleDll)
        {        
            m_pszModuleDll=pszModuleDll;      
            return true;
        }        
    //close function
        bool CloseInstance()
        {
            if(m_pIModuleInterface!=NULL)
            {
                m_pIModuleInterface->Release();
                m_pIModuleInterface=NULL;
            }
            if(m_hDllInstance!=NULL)
            {
                dlclose(m_hDllInstance);
                m_hDllInstance=NULL;
            }
            return true;
        }
    //Create function
        bool CreateInstance()
        {
            char * pszError;
            CloseInstance();
            try
            {
            //Load so
            //printf("%s\n",m_pszModuleDll);
                m_hDllInstance=dlopen(m_pszModuleDll,RTLD_LAZY);
                pszError=dlerror();            
                if(m_hDllInstance==NULL || pszError!=NULL)                                    
                {                
                    sprintf(m_szErrorMsg,"%s Module Load Faild,%s!",m_pszModuleDll,pszError);                
                    return false;                
                }
                            
            //Get enter function            
                ModuleCreateFunc * pCreateFunc=(ModuleCreateFunc*)dlsym(m_hDllInstance,m_pszFuncName);
                pszError=dlerror();
                if(pCreateFunc==NULL || pszError!=NULL)            
                {                
                    sprintf(m_szErrorMsg,"%s Module Create function %s is not found,%s!",
                            m_pszModuleDll,m_pszFuncName,pszError);
                    return false;
                }
            //Create module
                m_pIModuleInterface=(IModuleInterface*)pCreateFunc(m_dwVersion);                     
                if(m_pIModuleInterface==NULL)            
                {
                    sprintf(m_szErrorMsg,"%sModule create function %s create faild!",m_pszModuleDll,m_pszFuncName);                
                    return false;
                }
            }
            catch(...)
            {
                sprintf(m_szErrorMsg,"%s Module Create exception,%s!",
                        m_pszModuleDll,pszError);
                return false;                        
            }
            return true;
        }
    //Is valid
        bool IsValid()
        {
            if(m_pIModuleInterface==NULL) return false;
            return m_pIModuleInterface->IsValid();
        }
    //Get Error message
        LPCTSTR GetErrorMessage(){return m_szErrorMsg;}
		LPCTSTR GetDllName(){return m_pszModuleDll;}

    //Helper function
    public:
    //Reload point
        IModuleInterface * operator->(){return m_pIModuleInterface;}
    //Get Interface
        IModuleInterface * GetInterface(){return m_pIModuleInterface;}
    };

	//����IUnknownEx �ӿڸ�����
	class CIUnknownExHelper: public CTemplateHelper<IUnknownEx>
	{
	public:
		//���캯��
		CIUnknownExHelper(LPCTSTR lpszModuleName):CTemplateHelper<IUnknownEx>(VER_IUnknownEx,
			lpszModuleName,CREATE_FUNC_NAME){}
	};
#else    	
	//typedef unsigned long long UDWORD;
	typedef unsigned long int UDWORD;
	typedef unsigned __int64 UNDWORD;
    //Interface define
    #define STD_METHOD(TYPE,METHOD) virtual TYPE __cdecl METHOD
    //Interface module create function
    typedef void * (__cdecl ModuleCreateFunc)(const GUID & Guid,DWORD dwInterfaceVer);

    //���ӿ�
    #define VER_IUnknownEx INTERFACE_VERSION(1,1)
    static const GUID IID_IUnknownEx = { 0x1e7ee16a, 0x4120, 0x4c27, { 0xa8, 0x7b, 0x3e, 0x39, 0x32, 0xee, 0xf2, 0x2e } };
    struct IUnknownEx
    {
	    //�Ƿ���Ч
	    virtual bool __cdecl IsValid()=0;
	    //�ͷŶ���
	    virtual bool __cdecl Release()=0;
	    //�ӿڲ�ѯ
	    virtual void * __cdecl QueryInterface(const IID &Guid,DWORD dwQueryVer)=0;
    };

    //�ӿڲ�ѯ��
    #define QUERYINTERFACE(Interface,Guid,dwQueryVer)										\
	    if((Guid==IID_##Interface) &&(InterfaceVersionCheck(dwQueryVer,VER_##Interface)))	\
		    return static_cast<Interface *>(this);	

    //��ѯ���ӿ�
    #define QUERYINTERFACE_IUNKNOWNEX(BaseInterface,Guid,dwQueryVer)						\
	    if((Guid==IID_IUnknownEx) && (InterfaceVersionCheck(dwQueryVer,VER_IUnknownEx)))	\
		    return static_cast<IUnknownEx *>(static_cast<BaseInterface*>(this));

    //��ȡ����ӿ�
    #define GET_MYSELF_INTERFACE(Interface)													\
	    ((Interface *)QueryInterface(IID_##Interface,VER_##Interface))

    //��ȡָ������Ľӿ�
    #define GET_OBJECT_INTERFACE(Object,Interface)											\
	    ((Interface *)Object.QueryInterface(IID_##Interface,VER_##Interface))

    //��ȡ����ָ��Ľӿ�
    #define GET_OBJECTPTR_INTERFACE(pObject,Interface)										\
	    ((pObject==NULL)?NULL:((Interface *)pObject->QueryInterface(IID_##Interface,VER_##Interface)))

////////////////////////////////////////////////////////////////////////////////////////////////////////
    //��������ඨ��
    template<typename IModuleInterface>
    class CTemplateHelper
    {
	#ifdef _UNICODE
	#define mysprintfs _swprintf_p
	#else
	#define mysprintfs _snprintf_s
	#endif
	    //��������
    protected:
	    LPCSTR							m_pszFuncName;					//��������
	    LPCTSTR							m_pszModuleDll;					//�������
	    HINSTANCE						m_hDllInstance;					//DLL���
	    REFGUID							m_GuidInterface;				//�ӿڱ�ʶ
	    const DWORD						m_dwVersion;					//�ӿڰ汾
	    IModuleInterface				*m_pIModuleInterface;			//ģ��ӿ�
	    TCHAR							m_szErrorMsg[LEN_ERROR];		//������Ϣ

	    //��������
    public:
	    //���캯��
        CTemplateHelper(REFGUID refGuid,DWORD dwVer,LPCTSTR pszModuleDll,LPCSTR pszFuncName)
		    :m_GuidInterface(refGuid),m_dwVersion(dwVer)
	    {
            m_szErrorMsg[0]=0;
		    m_hDllInstance=NULL;
		    m_pIModuleInterface=NULL;
		    m_pszFuncName=pszFuncName;
		    m_pszModuleDll=pszModuleDll;
	    }
	    //��������
	    virtual ~CTemplateHelper()
	    {
		    CloseInstance();
	    }

	    //���ܺ���
    public:
	    //��������
	    bool CreateInstance()
	    {
		    CloseInstance();
		    try
		    {	
			    //����DLL
			    m_hDllInstance=LoadLibrary(m_pszModuleDll);
			    if(m_hDllInstance==NULL)
			    {
				    mysprintfs(m_szErrorMsg,sizeof(m_szErrorMsg),TEXT("%s ����ʧ��,�������: %ld !"),m_pszModuleDll,GetLastError());
				    return false;
			    }
			    //���ҵ�������
			    ModuleCreateFunc * pCreateFunc=(ModuleCreateFunc *)GetProcAddress(m_hDllInstance,m_pszFuncName);
			    if(pCreateFunc==NULL)
			    {
				    mysprintfs(m_szErrorMsg,sizeof(m_szErrorMsg),TEXT("%s ����������� %s ������,�������:%ld !"),
					    m_pszModuleDll,m_pszFuncName,GetLastError());
				    return false;
			    }
			    //�������
			    m_pIModuleInterface=(IModuleInterface *)pCreateFunc(m_GuidInterface,m_dwVersion);
			    if(m_pIModuleInterface==NULL)
			    {
				    mysprintfs(m_szErrorMsg,sizeof(m_szErrorMsg),TEXT("%s ����������� %s �������ʧ��!"),
					    m_pszModuleDll,m_pszFuncName);
				    return false;
			    }
		    }
		    catch(...)
		    {
			    mysprintfs(m_szErrorMsg,sizeof(m_szErrorMsg),TEXT("%s ����������� %s �������쳣����"),
				    m_pszModuleDll,m_pszFuncName);
                return false;
		    }

		    return true;
	    }
	    //�رպ���
	    bool CloseInstance()
	    {
		    if(m_pIModuleInterface!=NULL)
		    {
			    m_pIModuleInterface->Release();
			    m_pIModuleInterface=NULL;
		    }
		    if(m_hDllInstance!=NULL)
		    {
			    FreeLibrary(m_hDllInstance);
			    m_hDllInstance=NULL;
		    }
		    return true;
	    }
	    //�Ƿ���Ч
	    bool IsValid()
	    {
		    if(m_pIModuleInterface==NULL) return false;
		    return m_pIModuleInterface->IsValid();
	    }
	    //��ȡ����
	    LPCTSTR GetErrorMessage(){return m_szErrorMsg;}
		LPCTSTR GetDllName(){return m_pszModuleDll;}

	    //��������
    public:
	    //ָ������
	    IModuleInterface * operator->(){return m_pIModuleInterface;}
	    //��ȡ�ӿ�
	    IModuleInterface * GetInterface(){return m_pIModuleInterface;}
    };

#endif  //WIN32

#endif //__DEIRLYM_IUNKNOWN_EX_HEAD_FILE__
