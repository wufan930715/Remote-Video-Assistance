#ifndef MUL_TIMER_H_H
#define MUL_TIMER_H_H

#define MUL_TIMER_RESET_SEC 30000//��ʱ������ʱ���ʼִ��
#define TIMER_UNIT 1//���ζ�ʱ������ʱ��


#include <list>
#include <stdio.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "localdef.h"

using namespace std;
//��ʱ������ָ������
typedef bool (*timer_proc) (void*);
//�źź���ָ������
typedef void(*sigfunc) (int);
//��ʱ�¼���Ϣ
typedef struct timer_info{
	int interval;//��ʱʱ��
	int elapse;//�ۼ�
	timer_proc proc;
	void *pObj;
}Timer_info,*timer_handle_t;
//���ж�ʱ������������ݽṹ
typedef struct _timer_manage{
	list<Timer_info*> timer_info_list;
	sigfunc old_sigfunc;
	sigfunc new_sigfunc;
	struct itimerval value,ovalue;
}Timer_manager_t;

typedef list<Timer_info*>				CTimeInfoList;
typedef list<Timer_info*>::iterator		CTimeInfoListIt;

//�ඨʱ��������
class CMulTimer{
public:
	static CMulTimer* GetMulTimerInstance(){
		if(m_instance==NULL)
			m_instance = new CMulTimer();
		return m_instance;
	}
	static void ReleaseMulTimerInstance(){
		if(m_instance!=NULL){
			delete m_instance;
			m_instance = NULL;
		}
	}

	/**
	 * ����һ����ʱ��
	 */
	timer_handle_t StartTimer(int interval,timer_proc proc,void* pObj);
	/**
	 * ����һ����ʱ��
	 */
	bool StopTimer(timer_handle_t handle,bool bLocked=false);
	/**
	 * ֹͣ���ж�ʱ��
	 */
	bool StopAllTimer();
private:
	CMulTimer();
	~CMulTimer();
	/**
	 * ��ʱ���Ļص�����
	 */
	static void sig_func(int signo);
	//����ʱ��
	bool OnProcTimer();

private:
	static CMulTimer* m_instance;
	Timer_manager_t m_TimerManager;
	CTimeInfoList	m_freeList;
	CThreadLock		m_ThreadLock;
};

#endif
