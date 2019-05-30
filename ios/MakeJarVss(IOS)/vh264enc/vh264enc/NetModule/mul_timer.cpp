/*
 * mul_timer.cpp
 *
 *  Created on: 2014年6月25日
 *      Author: caiyu
 */
#include "mul_timer.h"
#include <stdlib.h>
#include "custom_log.h"

CMulTimer* CMulTimer::m_instance = NULL;

CMulTimer::CMulTimer(){
	memset(&m_TimerManager.value,0,sizeof(m_TimerManager.value));
	memset(&m_TimerManager.ovalue,0,sizeof(m_TimerManager.ovalue));
	if((m_TimerManager.old_sigfunc = signal(SIGALRM,sig_func))==SIG_ERR){
		return;
	}
	m_TimerManager.new_sigfunc = sig_func;
	m_TimerManager.value.it_value.tv_sec = 0;
	m_TimerManager.value.it_value.tv_usec = MUL_TIMER_RESET_SEC;
	m_TimerManager.value.it_interval.tv_sec = 0;
	m_TimerManager.value.it_interval.tv_usec = MUL_TIMER_RESET_SEC;
	int ret = setitimer(ITIMER_REAL, &m_TimerManager.value, &m_TimerManager.ovalue);

	LOGD("---------Timer setitimer result:%d",ret);
}

CMulTimer::~CMulTimer(){
	StopAllTimer();

	signal(SIGALRM, m_TimerManager.old_sigfunc);
	setitimer(ITIMER_REAL, &m_TimerManager.ovalue, &m_TimerManager.value);
}
void CMulTimer::sig_func(int signo){

	CMulTimer::m_instance->OnProcTimer();
}

//处理定时器
bool CMulTimer::OnProcTimer()
{
	CThreadLockHandle LockHandle(&m_ThreadLock);
	if(m_TimerManager.timer_info_list.size()==0)
		return true;
	Timer_info * pTimerInfo=NULL;
	list<Timer_info*>::iterator it;
	LOGD("---------Timer proc function:%d",m_TimerManager.timer_info_list.size());
	for(it=m_TimerManager.timer_info_list.begin();it!=m_TimerManager.timer_info_list.end();it++){
		pTimerInfo = *it;
		pTimerInfo->elapse++;
		if(pTimerInfo->elapse>=pTimerInfo->interval){
			pTimerInfo->elapse = 0;
			bool bResult=pTimerInfo->proc(pTimerInfo->pObj);
			if(bResult==false)	//添加删除列表
			{
				m_TimerManager.timer_info_list.erase(it);
				m_freeList.push_back(pTimerInfo);
				break;
			}
		}
	}

	return true;
}

timer_handle_t CMulTimer::StartTimer(int interval,timer_proc proc,void* pObj){
	if(proc==NULL||interval<=0)
		return NULL;
	CThreadLockHandle LockHandle(&m_ThreadLock);
	Timer_info* timerInfo=NULL;
	if(m_freeList.size()>0)
	{
		timerInfo=m_freeList.front();
		m_freeList.pop_front();
	}
	if(timerInfo==NULL)
	{
		timerInfo =(Timer_info*)malloc(sizeof(Timer_info));
		if(timerInfo==NULL) return NULL;
	}
	timerInfo->elapse = 0;
	timerInfo->interval = interval;
	timerInfo->proc = proc;
	timerInfo->pObj = pObj;
	m_TimerManager.timer_info_list.push_back(timerInfo);

	return timerInfo;
}

bool CMulTimer::StopTimer(timer_handle_t handle,bool bLocked){
	if(handle==NULL)
		return false;

	bool ret  = true;
	if(bLocked)
		m_ThreadLock.Lock();
	Timer_info * pTimerInfo=NULL;
	list<Timer_info*>::iterator it;
	for(it=m_TimerManager.timer_info_list.begin();it!=m_TimerManager.timer_info_list.end();){
		pTimerInfo = *it;
		if(pTimerInfo==handle)
		{
			m_TimerManager.timer_info_list.erase(it);
			m_freeList.push_back(pTimerInfo);
			break;
		}
	}
	if(bLocked)
		m_ThreadLock.UnLock();
	return ret;
}

bool CMulTimer::StopAllTimer(){

	CThreadLockHandle LockHandle(&m_ThreadLock);
	list<Timer_info*>::iterator it;
	if(m_TimerManager.timer_info_list.size()==0)
		return false;
	Timer_info * pTimerInfo;
	for(it=m_TimerManager.timer_info_list.begin();it!=m_TimerManager.timer_info_list.end();it++){
		pTimerInfo = *it;
		free(pTimerInfo);
	}
	m_TimerManager.timer_info_list.clear();

	for(it=m_freeList.begin();it!=m_freeList.end();it++){
		pTimerInfo = *it;
		free(pTimerInfo);
	}
	m_freeList.clear();

	return true;
}
