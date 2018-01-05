// WTLVC6.cpp : main source file for WTLVC6.exe
//

#include "stdafx.h"

#include "resource.h"

#include "WTLVC6View.h"
#include "webappView.h"
#include "aboutdlg.h"
#include "ChildFrm.h"
#include "MainFrm.h"

WTLVC6Module _Module;

#include <XLib/UIXModule.h>

class WTLVC6SkinModule : public UIXModuleT<WTLVC6SkinModule>
{

};

WTLVC6SkinModule _UxModule;

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

#include <time.h>

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));

	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	XLibInit::Init();

	_UxModule.Init();

	CurrentDirectory curdir;
	curdir.SetCurrentDirectory(_T("./default"));
	_UxModule.LoadSkin(_T("theme.xml"));
	curdir.RestoreCurrentDirectory();

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_UxModule.Term();

	XLibInit::Release();

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
