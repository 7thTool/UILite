// UIDesigner.cpp : main source file for UIDesigner.exe
//

#include "stdafx.h"
#include "Module.h"
#include "Platform.h"

#include "ChildView.h"
#include "AboutDlg.h"
#include "ChildFrm.h"
#include "MainFrm.h"

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	//使用RICHEDIT需要显示加载它
	HMODULE hMod = LoadLibrary(_T("riched20.dll"));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	::InitCommonControls();

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);	// add flags to support other controls

	AtlAxWinInit();

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	XLibInit::Init();

	_Platform.Init();

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Platform.Term();

	XLibInit::Release();

	_Module.Term();

	FreeLibrary(hMod);

	::CoUninitialize();

	return nRet;
}
