#ifndef MUL_TIMER_H_H
#define MUL_TIMER_H_H

#define MUL_TIMER_RESET_SEC 30000//定时器多少时间后开始执行
#define TIMER_UNIT 1//两次定时任务间隔时间


#include <list>
#include <stdio.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "localdef.h"

using namespace std;
//定时器函数指针类型
typedef bool (*timer_proc) (void*);
//信号函数指针类型
typedef void(*sigfunc) (int);
//定时事件信息
typedef struct timer_info{
	int interval;//定时时间
	int elapse;//累加
	timer_proc proc;
	void *pObj;
}Timer_info,*timer_handle_t;
//所有定时任务的任务数据结构
typedef struct _timer_manage{
	list<Timer_info*> timer_info_list;
	sigfunc old_sigfunc;
	sigfunc new_sigfunc;
	struct itimerval value,ovalue;
}Timer_manager_t;

typedef list<Timer_info*>				CTimeInfoList;
typedef list<Timer_info*>::iterator		CTimeInfoListIt;

//多定时器管理类
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
	 * 开启一个定时器
	 */
	timer_handle_t StartTimer(int interval,timer_proc proc,void* pObj);
	/**
	 * 结束一个定时器
	 */
	bool StopTimer(timer_handle_t handle,bool bLocked=false);
	/**
	 * 停止所有定时器
	 */
	bool StopAllTimer();
private:
	CMulTimer();
	~CMulTimer();
	/**
	 * 定时器的回调函数
	 */
	static void sig_func(int signo);
	//处理定时器
	bool OnProcTimer();

private:
	static CMulTimer* m_instance;
	Timer_manager_t m_TimerManager;
	CTimeInfoList	m_freeList;
	CThreadLock		m_ThreadLock;
};

#endif
