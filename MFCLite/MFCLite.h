// MFCLite.h : main header file for the MFCLite DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCLiteApp
// See MFCLite.cpp for the implementation of this class
//

class CMFCLiteApp : public CWinApp
{
public:
	CMFCLiteApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance(); // default will 'delete this'

	DECLARE_MESSAGE_MAP()
};
