#include "stdafx.h"
#include "UIEvent.h"

//////////////////////////////////////////////////////////////////////////

static void __stdcall TimerFunc(HWND, UINT, UINT_PTR, DWORD)
{
	EvtDispatcher::GetEvtDispatcher()->PostIdleEvent();
}

#if 0

//////////////////////////////////////////////////////////////////////////
///UIEvtObjecter

UIEvtDispatcher* UIEvtObjecter::s_pDispatcher = NULL;

void UIEvtObjecter::SetEvtDispatcher(UIEvtDispatcher* pDispatcher)
{
	s_pDispatcher = pDispatcher;
}

UIEvtDispatcher* UIEvtObjecter::GetEvtDispatcher()
{
	return s_pDispatcher;
}

UIEvtObjecter::UIEvtObjecter()
{
	
}

UIEvtObjecter::~UIEvtObjecter()
{
	
}

long UIEvtObjecter::SendEvent(Event& evt)
{
	return EvtObjecter::SendEvent(evt);
}

long UIEvtObjecter::SendEvent(EvtObjecter* dst, Event& evt)
{
	return EvtObjecter::SendEvent(dst,evt);
}

long UIEvtObjecter::SendEvent(EvtObjecter* dst, long evt, long value, ObjectPtr objPtr)
{
	return EvtObjecter::SendEvent(dst, evt, value, objPtr);
}

long UIEvtObjecter::SendEvent(long evt, long value, ObjectPtr objPtr)
{
	return EvtObjecter::SendEvent(evt, value, objPtr);
}

long UIEvtObjecter::PostEvent(Event& evt)
{
	if (!evt.dst) {
		ASSERT(0);
		evt.dst = this;
	}
	ASSERT(s_pDispatcher);
	return s_pDispatcher->PostEvent(evt);
}

long UIEvtObjecter::PostEvent(EvtObjecter* dst, Event& evt)
{
	return EvtObjecter::PostEvent(dst,evt);
}

long UIEvtObjecter::PostEvent(EvtObjecter* dst, long evt, long value, ObjectPtr objPtr)
{
	return EvtObjecter::PostEvent(dst, evt, value, objPtr);
}

long UIEvtObjecter::PostEvent(long evt, long value, ObjectPtr objPtr)
{
	return EvtObjecter::PostEvent(evt, value, objPtr);
}

//////////////////////////////////////////////////////////////////////////
///UIEvtDispatcher

UIEvtDispatcher::UIEvtDispatcher()
{
	m_ThreadId = GetCurrentThreadId();
}

UIEvtDispatcher::~UIEvtDispatcher()
{
	m_ThreadId = 0;
}

void UIEvtDispatcher::SetThreadId(unsigned long ThreadId)
{
	m_ThreadId = ThreadId;
}

unsigned long UIEvtDispatcher::GetThreadId()
{
	return m_ThreadId;
}

long UIEvtDispatcher::PostEvent(Event & evt)
{
	if(EvtDispatcher::PostEvent(evt) == RLT_TRUE) {
		::PostThreadMessage(m_ThreadId, WM_POSTEVENTMSG, 0, 0L);
	}
	return RLT_TRUE;
	return RLT_FALSE;
}

BOOL UIEvtDispatcher::OnWork()
{
	Event evt;
	if(GetEvent(NULL, evt) > 0) {
		if(!PreTranslateEvent(evt)) {
			DispatchEvent(evt);
		}
		return TRUE;
	} else {
		
	}
	return FALSE;
}

#else

#ifndef _AFX

UIEvtMessageLoop::UIEvtMessageLoop()
{
	m_ThreadId = Thread::GetCurrentThreadId();
}

long UIEvtMessageLoop::PostEvent(Event& evt)
{
	long rlt = EvtDispatcher::PostEvent(evt);
	if(rlt>0) {
		::PostThreadMessage(m_ThreadId, WM_POSTEVENTMSG, 0, 0L);
	} else {
		ASSERT(0);
	}
	return rlt;
}

long UIEvtMessageLoop::Run(bool bJoin)
{
	if (!bJoin) {
		return EvtDispatcher::Run(bJoin);
		//return 0;
	}

	BOOL bDoIdle = TRUE;
	int nIdleCount = 0;
	BOOL bRet;

	UINT_PTR uIdleTimer = ::SetTimer(NULL, 0, 50, (TIMERPROC)TimerFunc);
	ASSERT(uIdleTimer);

	for(;;)
	{
		while(bDoIdle && !::PeekMessage(&m_msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!OnIdle(nIdleCount++))
				bDoIdle = FALSE;
		}

		bRet = ::GetMessage(&m_msg, NULL, 0, 0);

		if(bRet == -1)
		{
			ATLTRACE2(atlTraceUI, 0, _T("::GetMessage returned -1 (error)\n"));
			continue;   // error, don't process
		}
		else if(!bRet)
		{
			ATLTRACE2(atlTraceUI, 0, _T("CMessageLoop::Run - exiting\n"));
			break;   // WM_QUIT, exit message loop
		}

		if(!PreTranslateMessage(&m_msg))
		{
			::TranslateMessage(&m_msg);
			::DispatchMessage(&m_msg);
		}

		if(IsIdleMessage(&m_msg))
		{
			bDoIdle = TRUE;
			nIdleCount = 0;
		}
	}

	::KillTimer(NULL,uIdleTimer);
	uIdleTimer = 0;

	OnQuit();

	return m_msg.wParam;
}

BOOL UIEvtMessageLoop::PreTranslateMessage(MSG* pMsg)
{
	ASSERT(pMsg);
	switch(pMsg->message)
	{
	case WM_POSTEVENTMSG:
		{
			Event evt;
			if(GetEvent(NULL,evt)) {
				if(!PreTranslateEvent(evt)) {
					DispatchEvent(evt);
				}
				if (!evt.dst) {
					if (evt.evt == EVT_IDLE) {
						OnIdle(GetTickCount());
					} else if (evt.evt == EVT_QUIT) {
						PostQuitMessage(0);
						break;
					}
				}
			}
			return TRUE;
		}
		break;
	default:
		break;
	}
	return UIMessageLoop::PreTranslateMessage(pMsg);
}

BOOL UIEvtMessageLoop::OnIdle(int nIdleCount)
{
	BOOL bIdle = UIMessageLoop::OnIdle(nIdleCount);
	/*if(!bIdle) {
		EvtDispatcher::OnIdle(GetTickCount());
	}*/
	return bIdle;
}

//////////////////////////////////////////////////////////////////////////

UIMultiEvtMessageLoop::UIMultiEvtMessageLoop(BOOL bAutoQuit):m_nThreadCount(0),m_bAutoQuit(bAutoQuit)
{
	
}

DWORD UIMultiEvtMessageLoop::AddThread(HANDLE hThread)
{
	ASSERT(m_nThreadCount<_countof(m_arrThreadHandles));
	m_arrThreadHandles[m_nThreadCount] = hThread;
	m_nThreadCount++;
	return m_nThreadCount;
}

void UIMultiEvtMessageLoop::RemoveThread(DWORD dwIndex)
{
	::CloseHandle(m_arrThreadHandles[dwIndex]);
	if(dwIndex != (m_nThreadCount - 1))
		m_arrThreadHandles[dwIndex] = m_arrThreadHandles[m_nThreadCount - 1];
	m_nThreadCount--;
}

BOOL UIMultiEvtMessageLoop::IsAutoQuit()
{
	return m_bAutoQuit;
}

int UIMultiEvtMessageLoop::Run()
{
	BOOL bDoIdle = TRUE;
	int nIdleCount = 0;
	BOOL bRet;
	
	DWORD dwWaitMillseconds = 0;
	unsigned long nTickCount = GetTickCount();

	for(;;)
	{
		while(bDoIdle && !::PeekMessage(&m_msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!OnIdle(nIdleCount++))
				bDoIdle = FALSE;
		}
		BOOL bHandleThread = FALSE;
		if (m_nThreadCount>0)
		{
			DWORD dwRet = ::MsgWaitForMultipleObjects(m_nThreadCount, m_arrThreadHandles, FALSE, dwWaitMillseconds, QS_ALLINPUT);
			//DWORD dwRet = WaitForMultipleObjects(m_nThreadCount, m_arrThreadHandles, FALSE, 0);

			if(dwRet == 0xFFFFFFFF)
			{
				PRINTFL("ERROR: Wait for multiple objects failed!!!");
				bHandleThread = TRUE;
			}
			else if(dwRet >= WAIT_OBJECT_0 && dwRet <= (WAIT_OBJECT_0 + m_nThreadCount - 1))
			{
				RemoveThread(dwRet - WAIT_OBJECT_0);
				bHandleThread = TRUE;
			}
		} 
		if(m_nThreadCount<=0) {
			if(m_bAutoQuit) {
				break;
			}
		}
		if (!bHandleThread) {
			bRet = ::PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE);
			if(bRet)
			{
				if(m_msg.message == WM_QUIT) {
					m_bAutoQuit = TRUE;
					continue;
				}

				if(!PreTranslateMessage(&m_msg))
				{
					::TranslateMessage(&m_msg);
					::DispatchMessage(&m_msg);
				}

				if(IsIdleMessage(&m_msg))
				{
					bDoIdle = TRUE;
					nIdleCount = 0;
				}
			}
			else
			{
				PostIdleEvent();
			}
		}
		//if()
		{
			unsigned long nLastTickCount = GetTickCount();
			dwWaitMillseconds = (nLastTickCount-nLastTickCount);
			if (dwWaitMillseconds<20) {
				dwWaitMillseconds = 20-dwWaitMillseconds;
				nTickCount = nLastTickCount;
				if (m_nThreadCount<=0) {
					Sleep(dwWaitMillseconds);
				}
			} else {
				dwWaitMillseconds = 0;
				nTickCount = nLastTickCount;
			}
		}
	}

	OnQuit();

	return (int)m_msg.wParam;
}
//int Run(LPTSTR lpstrCmdLine, int nCmdShow)
//{
//	MSG msg;
//	// force message queue to be created
//	::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
//
//	AddThread(lpstrCmdLine, nCmdShow);
//
//	int nRet = m_dwCount;
//	DWORD dwRet;
//	while(m_dwCount > 0)
//	{
//		dwRet = ::MsgWaitForMultipleObjects(m_dwCount, m_arrThreadHandles, FALSE, INFINITE, QS_ALLINPUT);
//
//		if(dwRet == 0xFFFFFFFF)
//		{
//			::MessageBox(NULL, _T("ERROR: Wait for multiple objects failed!!!"), _T("MultiThread"), MB_OK);
//		}
//		else if(dwRet >= WAIT_OBJECT_0 && dwRet <= (WAIT_OBJECT_0 + m_dwCount - 1))
//		{
//			RemoveThread(dwRet - WAIT_OBJECT_0);
//		}
//		else if(dwRet == (WAIT_OBJECT_0 + m_dwCount))
//		{
//			if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//			{
//				if(msg.message == WM_USER)
//					AddThread(_T(""), SW_SHOWNORMAL);
//			}
//		}
//		else
//		{
//			::MessageBeep((UINT)-1);
//		}
//	}
//
//	return nRet;
//}
//::PostThreadMessage(_Module.m_dwMainThreadID, WM_USER, 0, 0L);
#else

#endif//

#endif//

