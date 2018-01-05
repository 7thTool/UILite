
// mfcdlg.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "Platform.h"

// CmfcdlgApp:
// See mfcdlg.cpp for the implementation of this class
//

#ifndef CWinAppEx
typedef CWinApp CWinAppEx;
#endif//CWinAppEx

class CmfcdlgApp 
	: public CWinAppEx
{
public:
	CmfcdlgApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CmfcdlgApp theApp;