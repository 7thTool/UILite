
// mfcdlg.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "mfcdlg.h"
#include "mfcdlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UIAppModule _Module;

// CmfcdlgApp

BEGIN_MESSAGE_MAP(CmfcdlgApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CmfcdlgApp construction

CmfcdlgApp::CmfcdlgApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CmfcdlgApp object

CmfcdlgApp theApp;


// CmfcdlgApp initialization

BOOL CmfcdlgApp::InitInstance()
{
	AfxOleInit();

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	AfxInitRichEdit();

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	//_CrtSetBreakAlloc(515);

	_Module.Init(NULL,theApp.m_hInstance);

	XLibInit::Init();

	_Platform = new Platform();
	_Platform->Init();

	//UXContainer* pContainer = new UXContainer;
	//pContainer->Create(NULL,strXmlFile);
	//pContainer->ShowWindow()

	CmfcdlgDlg dlg;
	m_pMainWnd = &dlg;
	CString strXmlFile;
	strXmlFile.Format(_T("%s\\mfcdlg.xml"), _Platform->GetSkinPath());
	//dlg.Create(GetActiveWindow(),_T("<mfcdlg />"), XML_FLAG_STREAM);
	//INT_PTR nResponse = dlg.DoModal(_T("<mfcdlg title=\"mfcdlg\" rect=\"0,0,800,600\" />"), XML_FLAG_STREAM);
	INT_PTR nResponse = dlg.DoModal(strXmlFile);
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	_Platform->Term();
	delete _Platform;
	_Platform = NULL;

	XLibInit::Release();

	_Module.Term();

	AfxOleTerm();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
