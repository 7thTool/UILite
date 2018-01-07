
#pragma once

#ifndef _H_UIEVENT_H_
#define _H_UIEVENT_H_

#include "UILite.h"
#include <XLib/XEvent.h>
#include <UI/UIApp.h>

#if 0

class UIEvtDispatcher;

//////////////////////////////////////////////////////////////////////////
///实现每个UIEvtObjecter都知道属于某个线程

class UILITE_API UIEvtObjecter : virtual public EvtObjecter
{
protected:
	static UIEvtDispatcher* s_pDispatcher;
public:
	static void SetEvtDispatcher(UIEvtDispatcher* pDispatcher);
	static UIEvtDispatcher* GetEvtDispatcher();

public:
	UIEvtObjecter();
	virtual ~UIEvtObjecter();

	virtual long SendEvent(Event& evt);
	long SendEvent(EvtObjecter* dst, Event& evt);
	long SendEvent(EvtObjecter* dst, long evt, long value = 0, ObjectPtr objPtr = 0);
	long SendEvent(long evt, long value = 0, ObjectPtr objPtr = 0);
	virtual long PostEvent(Event& evt);
	long PostEvent(EvtObjecter* dst, Event& evt);
	long PostEvent(EvtObjecter* dst, long evt, long value = 0, ObjectPtr objPtr = 0);
	long PostEvent(long evt, long value = 0, ObjectPtr objPtr = 0);
};

typedef EvtHandlerT<UIEvtObjecter> UIEvtHandler;
typedef EvtListenerT<UIEvtHandler,UIEvtObjecter> UIEvtListener;

//////////////////////////////////////////////////////////////////////////
///UIEvtDispatcher实现应用层和数据层的数据交换只在主线程处理

class UILITE_API UIEvtDispatcher : public EvtDispatcher
{
protected:
	unsigned long m_ThreadId;
public:
	UIEvtDispatcher();
	virtual ~UIEvtDispatcher();

	void SetThreadId(unsigned long ThreadId);
	unsigned long GetThreadId();

	//virtual long SendEvent(Event& evt);
	virtual long PostEvent(Event& evt);

public:
	virtual BOOL OnWork();
};

template<class T>
class UIEvtMessageFilter : public UIMessageFilter<T>
{
	typedef UIMessageFilter<T> Base;
public:
	void OnPostEventMsg()
	{
		T* pT = static_cast<T*>(this);
		pT->OnWork();
	}

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		ASSERT(pMsg);
		switch(pMsg->message)
		{
		case WM_POSTEVENTMSG:
			{
				T* pT = static_cast<T*>(this);
				if (!pMsg->hwnd) {
					pT->OnPostEventMsg();
					return TRUE;
				}
			}
			break;
		}
		return Base::PreTranslateMessage(pMsg);
	}
};

template<class T>
class UIEvtIdleHandler : public CIdleHandler
{
public:
	virtual BOOL OnIdle()
	{
		T* pT = static_cast<T*>(this);
		return pT->OnWork();
	}
};

template<class T, class TBase = UIEvtDispatcher>
class UIEvtDispatcherImpl 
	: public TBase
	, public UIEvtMessageFilter<T>
	, public UIEvtIdleHandler<T>
{
	typedef UIEvtDispatcherImpl<T,TBase> This;
	typedef TBase Base;
public:

	UIEvtDispatcherImpl()
	{
		UIEvtObjecter::SetEvtDispatcher(this);
	}

	~UIEvtDispatcherImpl()
	{
		UIEvtObjecter::SetEvtDispatcher(NULL);
	}

	long Instance()
	{
		T* pT = static_cast<T*>(this);

		SetThreadId(GetCurrentThreadId());

		// register object for message filtering
		UIMessageLoop* pLoop = _Module.GetMessageLoop(GetThreadId());
		ATLASSERT(pLoop != NULL);
		pLoop->AddIdleHandler(pT);
		pLoop->AddMessageFilter(pT);

		return RLT_OK;
	}

	void Release()
	{
		T* pT = static_cast<T*>(this);

		// unregister message filtering
		UIMessageLoop* pLoop = _Module.GetMessageLoop(GetThreadId());
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(pT);
		pLoop->RemoveIdleHandler(pT);
	}
};

//////////////////////////////////////////////////////////////////////////
//同时是UIEvtDispatcher和UIEvtObjecter

template<class TObjecter = UIEvtObjecter, class TBase = UIEvtDispatcher>
class UIEvtRunner
	: public TBase
	, public TObjecter
{
	typedef TBase Base;
public:
	UIEvtRunner()
	{
		UIEvtObjecter::SetEvtDispatcher(this);
	}

	~UIEvtRunner()
	{
		UIEvtObjecter::SetEvtDispatcher(NULL);
	}

	virtual long SendEvent(Event& evt)
	{
		return TObjecter::SendEvent(evt);
	}
	long SendEvent(EvtObjecter* dst, Event& evt)
	{
		return TObjecter::SendEvent(dst,evt);
	}
	long SendEvent(EvtObjecter* dst, long evt, long value = 0, ObjectPtr objPtr = 0)
	{
		return TObjecter::SendEvent(dst,evt,value,objPtr);
	}
	long SendEvent(long evt, long value = 0, ObjectPtr objPtr = 0)
	{
		return TObjecter::SendEvent(evt,value,objPtr);
	}

	virtual long PostEvent(Event& evt)
	{
		return Base::PostEvent(evt);
	}
	long PostEvent(EvtObjecter* dst, Event& evt)
	{
		return TObjecter::PostEvent(dst,evt);
	}
	long PostEvent(EvtObjecter* dst, long evt, long value = 0, ObjectPtr objPtr = 0)
	{
		return TObjecter::PostEvent(dst,evt,value,objPtr);
	}
	long PostEvent(long evt, long value = 0, ObjectPtr objPtr = 0)
	{
		return TObjecter::PostEvent(evt,value,objPtr);
	}
};

template<class T, class TObjecter = UIEvtObjecter, class TBase = UIEvtDispatcher>
class UIEvtRunnerImpl 
	: public UIEvtDispatcherImpl<T,UIEvtRunner<TObjecter,TBase>>
	//, public TObjecter
{
	/*typedef UIEvtDispatcherImpl<T,TBase> Base;
public:
	virtual long SendEvent(Event& evt)
	{
		return TObjecter::SendEvent(evt);
	}
	long SendEvent(EvtObjecter* dst, Event& evt)
	{
		return TObjecter::SendEvent(dst,evt);
	}
	long SendEvent(EvtObjecter* dst, long evt, long value = 0, ObjectPtr objPtr = 0)
	{
		return TObjecter::SendEvent(dst,evt,value,objPtr);
	}
	long SendEvent(long evt, long value = 0, ObjectPtr objPtr = 0)
	{
		return TObjecter::SendEvent(evt,value,objPtr);
	}
	
	virtual long PostEvent(Event& evt)
	{
		return Base::PostEvent(evt);
	}
	long PostEvent(EvtObjecter* dst, Event& evt)
	{
		return TObjecter::PostEvent(dst,evt);
	}
	long PostEvent(EvtObjecter* dst, long evt, long value = 0, ObjectPtr objPtr = 0)
	{
		return TObjecter::PostEvent(dst,evt,value,objPtr);
	}
	long PostEvent(long evt, long value = 0, ObjectPtr objPtr = 0)
	{
		return TObjecter::PostEvent(evt,value,objPtr);
	}*/
};

#else

#ifndef _AFX

class UILITE_API UIEvtMessageLoop : public UIMessageLoop, public EvtDispatcher
{
protected:
	unsigned long m_ThreadId;

public:
	UIEvtMessageLoop();

	virtual long PostEvent(Event& evt);

	virtual long Run(bool bJoin = true);

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle(int nIdleCount);
};

class UILITE_API UIMultiEvtMessageLoop : public UIEvtMessageLoop
{
protected:
	unsigned long m_nThreadCount;
	HANDLE m_arrThreadHandles[64];
	BOOL m_bAutoQuit;

public:
	UIMultiEvtMessageLoop(BOOL bAutoQuit = TRUE);

	DWORD AddThread(HANDLE hThread);
	void RemoveThread(DWORD dwIndex);

	BOOL IsAutoQuit();

	virtual int Run();
};

#else

template<class T, class TBase = CWinApp, class TEvtBase = EvtDispatcher>
class UILITE_API UIEvtAppT : public TBase, public TEvtBase
{
	typedef TBase Base;
	typedef TEvtBase EvtBase;
public:
	virtual long PostEvent(Event& evt)
	{
		long rlt = EvtBase::PostEvent(evt);
		if(rlt>0) {
			PostThreadMessage(WM_POSTEVENTMSG, 0, 0L);
		} else {
			ASSERT(0);
		}
		return rlt;
	}

	long OnPostEventMsg()
	{
		Event evt;
		if(GetEvent(NULL,evt)) {
			if(!PreTranslateEvent(evt)) {
				DispatchEvent(evt);
			}
			return RLT_TRUE;
		}
		return RLT_FALSE;
	}

	virtual int Run()
	{
		T* pT = static_cast<T*>(this);
		ASSERT_VALID(pT);
		_AFX_THREAD_STATE* pState = AfxGetThreadState();

		// for tracking the idle time state
		BOOL bIdle = TRUE;
		LONG lIdleCount = 0;

		// acquire and dispatch messages until a WM_QUIT message is received.
		for (;;)
		{
			//
			if (!pT->OnPostEventMsg())
				OnIdle();
			}

			// phase1: check to see if we can do idle work
			while (bIdle &&
				!::PeekMessage(&(pState->m_msgCur), NULL, NULL, NULL, PM_NOREMOVE))
			{
				// call OnIdle while in bIdle state
				if (!OnIdle(lIdleCount++))
					bIdle = FALSE; // assume "no idle" state
			}

			// phase2: pump messages while available
			do
			{
				// pump message, but quit on WM_QUIT
				if (!PumpMessage())
					return ExitInstance();

				// reset "no idle" state after pumping "normal" message
				//if (IsIdleMessage(&m_msgCur))
				if (IsIdleMessage(&(pState->m_msgCur)))
				{
					bIdle = TRUE;
					lIdleCount = 0;
				}

			} while (::PeekMessage(&(pState->m_msgCur), NULL, NULL, NULL, PM_NOREMOVE));
		}
	}

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		ASSERT(pMsg);
		switch(pMsg->message)
		{
		case WM_POSTEVENTMSG:
			{
				T* pT = static_cast<T*>(this);
				pT->OnPostEventMsg();
				return TRUE;
			}
			break;
		default:
			break;
		}
		return Base::PreTranslateMessage(pMsg);
	}

	virtual BOOL OnIdle(int nIdleCount)
	{
		BOOL bIdle = Base::OnIdle(nIdleCount);
		if(!bIdle) {
			OnIdle();
		}
		return bIdle;
	}
};

#endif//

#endif//

#endif//_H_UIEVENT_H_
