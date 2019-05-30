///////////////////////////////////////////////////////////////////////
//		����ģ����ͷ�ļ� Array.h
//		��ģ�����û���������������������
///////////////////////////////////////////////////////////////////////
#ifndef __DEIRLYM_ARRAY_HREAD_FILE__
#define __DEIRLYM_ARRAY_HREAD_FILE__

#ifndef AFX_INLINE
#define AFX_INLINE inline
#endif
#ifndef ASSERT_VALID
#define ASSERT_VALID(x)
#endif
#ifndef ASSERT
#define ASSERT(x) assert(x)
#endif
////////////////////////////////////////////////////////////////////////
//����ģ����
template<class TYPE,class ARG_TYPE=const TYPE &>
class CArrayTemplate
{
	//��������
protected:
	TYPE					*m_pData;						//����ͷָ��
	INT_PTR					m_nMaxCount;					//���������Ŀ
	INT_PTR					m_nGrowCount;					//������Ŀ
	INT_PTR					m_nElementCount;				//Ԫ�ظ���

	//��������
public:
	//���캯��
	CArrayTemplate();
	//��������
	virtual ~CArrayTemplate();

	//����
public:
	//�Ƿ������
	bool IsEmpty()const;
	//��ȡ��Ŀ
	INT_PTR GetCount()const;
	//��ȡ����
	INT_PTR GetUpperBound()const;

	//���ܺ���
public:
	//��ȡ����
	TYPE * GetData();
	//��ȡ����
	const TYPE * GetData()const;
	//�ͷ�ԭ�ڴ�,���������¿ռ�
	void FreeExtra();
	//����Ԫ��
	INT_PTR Add(ARG_TYPE newElement);
	//��������
	void Copy(const CArrayTemplate & Src);
	//׷������
	INT_PTR Append(const CArrayTemplate & Src);
	//��ȡԪ��
	TYPE & GetAt(INT_PTR nIndex);
	//��ȡԪ��
	const TYPE & GetAt(INT_PTR nIndex)const;
    //ö��Ԫ��
	TYPE & ElementAt(INT_PTR nIndex);
	//ö��Ԫ��
	const TYPE & ElementAt(INT_PTR nIndex)const;
	
	//��������
public:
	//���ô�С
	void SetSize(INT_PTR nNewSize);
	//����Ԫ��
	void SetAt(INT_PTR nIndex,ARG_TYPE newElement);
	//����Ԫ��
	void SetAtGrow(INT_PTR nIndex,ARG_TYPE newElement);
	//��������
	void InsertAt(INT_PTR nIndex,const CArrayTemplate & Src);
	//��������
	void InsertAt(INT_PTR nIndex,ARG_TYPE newElement,INT_PTR cCount=1);
	//ɾ������
	void RemoveAt(INT_PTR nIndex,INT_PTR nCount=1);
	//ɾ������Ԫ��
	void RemoveAll();

	//���ز�����
public:
	//����[]
	TYPE & operator[](INT_PTR nIndex);
	//����[]
	const TYPE & operator[](INT_PTR nIndex)const;

	//�ڲ�����
private:
	//�����ڴ�
	void AllocMemory(INT_PTR nNewCount);
};

///////////////////////////////////////////////////////////////////////
// ����ģ��ʵ��
///////////////////////////////////////////////////////////////////////
//���캯��
template<class TYPE,class ARG_TYPE>
CArrayTemplate<TYPE,ARG_TYPE>::CArrayTemplate()
{
	m_pData=NULL;
	m_nMaxCount=0;
	m_nGrowCount=0;
	m_nElementCount=0;
}
//��������
template<class TYPE,class ARG_TYPE>
CArrayTemplate<TYPE,ARG_TYPE>::~CArrayTemplate()
{
	if(m_pData!=NULL)
	{
		for(INT_PTR i=0;i<m_nElementCount;i++)(m_pData+i)->~TYPE();
		delete[] (BYTE*)m_pData;
		m_pData=NULL;
	}
}
//�Ƿ������
template<class TYPE,class ARG_TYPE>
AFX_INLINE bool CArrayTemplate<TYPE,ARG_TYPE>::IsEmpty()const
{
	ASSERT_VALID(this);
	return (m_nElementCount==0);
}
//��ȡ��Ŀ
template<class TYPE,class ARG_TYPE>
AFX_INLINE INT_PTR CArrayTemplate<TYPE,ARG_TYPE>::GetCount()const
{
	ASSERT_VALID(this);
	return m_nElementCount;
}
//��ȡ����
template<class TYPE,class ARG_TYPE>
AFX_INLINE INT_PTR CArrayTemplate<TYPE,ARG_TYPE>::GetUpperBound()const
{
	ASSERT_VALID(this);
	return m_nMaxCount-1;
}
//��ȡ����
template<class TYPE,class ARG_TYPE>
TYPE * CArrayTemplate<TYPE,ARG_TYPE>::GetData()
{
	ASSERT_VALID(this);
	return m_pData;
}
//��ȡ����
template<class TYPE,class ARG_TYPE>
const TYPE * CArrayTemplate<TYPE,ARG_TYPE>::GetData()const
{
	ASSERT_VALID(this);
	return m_pData;
}
//�ͷ�ԭ�ڴ�,���������¿ռ�
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::FreeExtra()
{
	ASSERT_VALID(this);
	if(m_nElementCount!=m_nMaxCount)
	{
		TYPE * pNewData=NULL;
		if(m_nElementCont!=0)
		{
			//��������ռ�
			pNewData=(TYPE *)new BYTE[m_nElementCount*sizeof(TYPE)];
			ASSERT(pNewData);
			memcpy(pNewData,m_pData,m_nElementCount*sizeof(TYPE));			
		}
        delete [] (BYTE *)m_pData;
		m_pData=pNewData;
		m_nMaxCount=m_nElementCount;
	}
}
//����Ԫ��
template<class TYPE,class ARG_TYPE>
AFX_INLINE INT_PTR CArrayTemplate<TYPE,ARG_TYPE>::Add(ARG_TYPE newElement)
{
    INT_PTR nIndex=m_nElementCount;
	SetAtGrow(nIndex,newElement);
	return m_nElementCount;
}
//��������
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::Copy(const CArrayTemplate & Src)
{
    //Ч�����
	ASSERT_VALID(this);
	ASSERT(this!=&Src);
	if(this==&Src) return;

	//��������
	AllocMemory(Src.m_nElementCount);	//�����ڴ�
	if(m_nElementCount>0)
	{
        for(INT_PTR i=0;i<m_nElementCount;i++)
			(m_pData+i)->~TYPE();
		memset(m_pData,0,m_nElementCount*sizeof(TYPE));
	}
	for(INT_PTR i=0;i<Src.m_nElementCount;i++)
		m_pData[i]=Src.m_pData[i];
	m_nElementCount=Src.m_nElementCount;
}
//׷������
template<class TYPE,class ARG_TYPE>
INT_PTR CArrayTemplate<TYPE,ARG_TYPE>::Append(const CArrayTemplate & Src)
{
	//Ч�����
	ASSERT_VALID(this);
	ASSERT(this!=&Src);
	if(this==&Src) throw("���ݴ���");

	//��������
	if(Src.m_nElementCount>0)
	{
		INT_PTR nOldCount=m_nElementCount;
		AllocMemory(m_nElementCount+Src.m_nElementCount);  //���������ڴ�
		for(INT_PTR i=0;i<Src.m_nElementCount;i++)
			m_pData[m_nElementCount+i]=Src.m_pData[i];

		m_nElementCount+=Src.m_nElementCount;
	}
	return m_nElementCount;
}
//��ȡԪ��
template<class TYPE,class ARG_TYPE>
TYPE & CArrayTemplate<TYPE,ARG_TYPE>::GetAt(INT_PTR nIndex)
{
	//Ч�����
	ASSERT((nIndex>=0) && (nIndex<m_nElementCount));
	if((nIndex>=0) && (nIndex<m_nElementCount)) return m_pData[nIndex];
	throw("��ȡԪ�أ������Ƿ�1");
}
//��ȡԪ��
template<class TYPE,class ARG_TYPE>
const TYPE & CArrayTemplate<TYPE,ARG_TYPE>::GetAt(INT_PTR nIndex)const
{
	//Ч�����
	ASSERT((nIndex>=0) && (nIndex<m_nElementCount));
	if((nIndex>=0) && nIndex<m_nElementCount) return m_pData[nIndex];
	throw("��ȡԪ�أ������Ƿ�2");
}
//ö��Ԫ��
template<class TYPE,class ARG_TYPE>
TYPE & CArrayTemplate<TYPE,ARG_TYPE>::ElementAt(INT_PTR nIndex)
{
	//Ч�����
	ASSERT((nIndex>=0) && (nIndex<m_nElementCount));
	if((nIndex>=0) && nIndex<m_nElementCount) return m_pData[nIndex];
	throw("ö��Ԫ�أ������Ƿ�1");
}
//ö��Ԫ��
template<class TYPE,class ARG_TYPE>
const TYPE & CArrayTemplate<TYPE,ARG_TYPE>::ElementAt(INT_PTR nIndex)const
{
	//Ч�����
	ASSERT((nIndex>=0) && (nIndex<m_nElementCount));
	if((nIndex>=0) && nIndex<m_nElementCount) return m_pData[nIndex];
	throw("ö��Ԫ�أ������Ƿ�1");
}
//���ô�С
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::SetSize(INT_PTR nNewSize)
{
	//Ч�����
	ASSERT_VALID(this);
	ASSERT(nNewSize>=0);
	if(nNewSize<0) throw("���ô�С�����ݴ�С�Ƿ�");

	//���ô�С
	AllocMemory(nNewSize);
	if(nNewSize>m_nElementCount)
	{
#pragma push_macro("new")		//��ʹ��MFC new ������
#undef new
		for(INT_PTR i=m_nElementCount;i<nNewSize;i++)::new((void*)(m_pData+i))TYPE();
#pragma pop_macro("new")
	}
	else if(nNewSize<m_nElementCount)
	{
        for(INT_PTR i=nNewSize;i<m_nElementCount;i++)(m_pData+i)->~TYPE();
		memset(m_pData+nNewSize,0,(m_nElementCount-nNewSize)*sizeof(TYPE));
	}
	m_nElementCount=nNewSize;
}
//����Ԫ��
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::SetAt(INT_PTR nIndex,ARG_TYPE newElement)
{
	//Ч�����
	ASSERT_VALID(this);
	ASSERT(nIndex>=0 && nIndex<m_nElementCount);
	if(nIndex>=0 && nIndex<m_nElementCount) m_pData[nIndex]=newElement;
	throw("����Ԫ�أ������Ƿ�1");
}
//����Ԫ��
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::SetAtGrow(INT_PTR nIndex,ARG_TYPE newElement)
{
	//Ч�����
	ASSERT(this);
	ASSERT(nIndex>=0);
	if(nIndex<0) throw("����Ԫ�أ������Ƿ�1");

	//����Ԫ��
	if(nIndex>=m_nElementCount) SetSize(nIndex+1);
	m_pData[nIndex]=newElement;
}
//��������
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::InsertAt(INT_PTR nIndex,const CArrayTemplate & Src)
{
	//Ч�����
	ASSERT_VALID(this);
	ASSERT(nIndex>=0);
	if(nIndex<0) throw("�������ݣ������Ƿ�1");

	if(Src.m_nElementCount>0)
	{
		INT_PTR nCount=Src.m_nElementCount;
		if(nIndex<m_nElementCount)
		{
			INT_PTR nOldCount=m_nElementCount;
			SetSize(m_nElementCount+Src.m_nElementCount);			
			for(INT_PTR i=0;i<nCount;i++)
				(m_pData+nOldCount+i)->~TYPE();
			//�ƶ��ڴ�
			memmove(m_pData+nIndex+nCount,m_pData+nIndex,(nOldCount-nIndex)*sizeof(TYPE));
			memset(m_pData+nIndex,0,Src.m_nElementCount*sizeof(TYPE));
#pragma push_macro("new")
#undef new
			for(INT_PTR i=0;i<Src.m_nElementCount;i++)
				::new(m_pData+nIndex+i) TYPE();
#pragma pop_macro("new")
		}
		else
		{
			SetSize(nIndex+nCount);
		}
		//��������
		ASSERT(nIndex+Src.m_nElementCount<=m_nElementCount);
		for(INT_PTR i=0;i<nCount;i++)		
			m_pData[nIndex++]=Src.m_pData[i];					
	}
}
//��������
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::InsertAt(INT_PTR nIndex,ARG_TYPE newElement,INT_PTR nCount)
{
    //Ч�����
	ASSERT_VALID(this);
	ASSERT(nIndex>=0);
	ASSERT(nCount>0);
	if(nIndex<0 || nCount<=0) throw("�������ݣ������Ƿ�2");

	//��������
	if(nIndex<m_nElementCount)
	{
		INT_PTR nOldCount=m_nElementCount;
		SetSize(m_nElementCount+nCount);
		for(INT_PTR i=0;i<nCount;i++)(m_pData+nOldCount+i)->~TYPE();
		//�ƶ��ڴ�
		memmove(m_pData+nIndex+nCount,m_pData+nIndex,(nOldCount-nIndex)*sizeof(TYPE));
		memset(m_pData+nIndex,0,sizeof(TYPE)*nCount);
#pragma push_macro("new")
#undef new
		for(INT_PTR i=0;i<nCount;i++)::new (m_pData+nIndex+i)TYPE();
#pragma pop_macro("new")
	}
	else SetSize(nIndex+nCount);

	//��������
	ASSERT(nIndex+nCount<=m_nElementCount);
	while(nCount--)m_pData[nIndex++]=newElement;
}
//ɾ������
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::RemoveAt(INT_PTR nIndex,INT_PTR nCount)
{
	//Ч�����
	ASSERT_VALID(this);
	ASSERT(nIndex>=0);
	ASSERT(nCount>=0);
	ASSERT(nIndex+nCount<=m_nElementCount);
	if(nIndex<0 || nCount<0 || (nIndex+nCount>m_nElementCount)) throw("ɾ�����ݣ������Ƿ�1");

	//ɾ��Ԫ��
	INT_PTR nMoveCount=m_nElementCount-(nIndex+nCount);
	for(INT_PTR i=0;i<nCount;i++)(m_pData+nIndex+i)->~TYPE();
	if(nMoveCount>0) memmove(m_pData+nIndex,m_pData+nIndex+nCount,nMoveCount*sizeof(TYPE));
	m_nElementCount-=nCount;
}
//ɾ������Ԫ��
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::RemoveAll()
{
	ASSERT_VALID(this);
	if(m_nElementCount>0)
	{
		for(INT_PTR i=0;i<m_nElementCount;i++)(m_pData+i)->~TYPE();
		memset(m_pData,0,m_nElementCount*sizeof(TYPE));
		m_nElementCount=0;
	}
}
//����[]
template<class TYPE,class ARG_TYPE>
AFX_INLINE TYPE & CArrayTemplate<TYPE,ARG_TYPE>::operator[](INT_PTR nIndex)
{
	return ElementAt(nIndex);
}
//����[]
template<class TYPE,class ARG_TYPE>
AFX_INLINE const TYPE & CArrayTemplate<TYPE,ARG_TYPE>::operator[](INT_PTR nIndex)const
{
	return GetAt(nIndex);
}
//�����ڴ�
template<class TYPE,class ARG_TYPE>
void CArrayTemplate<TYPE,ARG_TYPE>::AllocMemory(INT_PTR nNewCount)
{
	//Ч�����
	ASSERT_VALID(this);
	ASSERT(nNewCount>=0);
	
	if(nNewCount>m_nMaxCount)
	{
		INT_PTR nGrowCount=m_nGrowCount;  //�ڴ�������
		if(nGrowCount==0)
		{
			nGrowCount=m_nElementCount/8;
			nGrowCount=(nGrowCount<4)?4:(nGrowCount>1024)?1024:nGrowCount;
		}
		nNewCount+=nGrowCount;

		//�����ڴ�
		TYPE * pNewData=(TYPE*)new BYTE[nNewCount*sizeof(TYPE)];
		//�����ڴ�
		memcpy(pNewData,m_pData,m_nElementCount*sizeof(TYPE));
		memset(pNewData+m_nElementCount,0,(nNewCount-m_nElementCount)*sizeof(TYPE));
		delete [] (BYTE*)m_pData;
		//���ñ���
		m_pData=pNewData;
		m_nMaxCount=nNewCount;
	}
}

#endif //__DEIRLYM_ARRAY_HREAD_FILE__