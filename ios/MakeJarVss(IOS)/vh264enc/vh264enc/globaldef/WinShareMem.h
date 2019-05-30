/////////////////////////////////////////////////////////////////////////////////
//		Windows �����ڴ���ͷ�ļ� WinShareMem.h
//		hubo 2013-10-28
//////////////////////////////////////////////////////////////////////////////////
#pragma once

class CWinShareMem
{
private:
	HANDLE				m_hShareMemory;			//�����ڴ�
	void				*m_pShareMemData;		//�����ڴ�����

public:
	CWinShareMem(void);
	virtual ~CWinShareMem(void);

protected:
	//���������ڴ�
	void * CreateShareMem(LPCTSTR lpszName,DWORD dwMemSize);
	//�򿪹����ڴ�
	void * OpenShareMem(LPCTSTR lpszName);
};

//////////////////////////////////////////////////////////////////////
//�����ڴ�ģ��
template<class TYPE,class ARG_TYPE=const TYPE &>
class CShareMemTemplate: public CWinShareMem
{
public:
	//���캯��
	CShareMemTemplate();
	//��������
	virtual ~CShareMemTemplate();

public:
	//���������ڴ�
	TYPE * CreateShareMemory(LPCTSTR lpszName);
	//�򿪹����ڴ�
	TYPE * OpenShareMemory(LPCTSTR lpszName);
};

///////////////////////////////////////////////////////////////////////
// ����ģ��ʵ��
///////////////////////////////////////////////////////////////////////
//���캯��
template<class TYPE,class ARG_TYPE>
CShareMemTemplate<TYPE,ARG_TYPE>::CShareMemTemplate()
{
}

//��������
template<class TYPE,class ARG_TYPE>
CShareMemTemplate<TYPE,ARG_TYPE>::~CShareMemTemplate()
{
}

//���������ڴ�
template<class TYPE,class ARG_TYPE>
TYPE * CShareMemTemplate<TYPE,ARG_TYPE>::CreateShareMemory(LPCTSTR lpszName)
{
	DWORD dwSize=sizeof(TYPE);
	TYPE * pMemData=(TYPE *)CreateShareMem(lpszName,dwSize);
	return pMemData;
}

//�򿪹����ڴ�
template<class TYPE,class ARG_TYPE>
TYPE * CShareMemTemplate<TYPE,ARG_TYPE>::OpenShareMemory(LPCTSTR lpszName)
{
	TYPE *pMemData=(TYPE *)OpenShareMem(lpszName);
	return pMemData;
}
