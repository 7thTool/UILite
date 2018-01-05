// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "UILite.h"

#include <ShlObj.h>
#include <Shlwapi.h>
#include <ShellAPI.h>
#include <Psapi.h>
//#pragma comment(lib, "ShlObj.lib")
#pragma comment(lib, "Shlwapi.lib")
//#pragma comment(lib, "ShellAPI.lib")
#pragma comment(lib, "Psapi.lib")

#if WINVER>=0x0600 
#define USE_FILE_EX			1
#endif//

#define _WTL_NO_AUTOMATIC_NAMESPACE

#include <UI/UIApp.h>
extern UIAppModule _Module;

#define CURL_STATICLIB		1
#define CURL_DISABLE_LDAP	1
#define USE_SSLEAY			1
#define USE_OPENSSL			1
#ifdef _DEBUG
#pragma comment(lib,"ssleay32.lib")
#pragma comment(lib,"libeay32.lib")
#pragma comment(lib,"zlib.lib")
#ifdef USE_FILE_EX
#pragma comment(lib,"fileextd.lib")
#endif//
#pragma comment(lib,"ws2_32.lib")
#else
#pragma comment(lib,"ssleay32.lib")
#pragma comment(lib,"libeay32.lib")
#pragma comment(lib,"zlib.lib")
#ifdef USE_FILE_EX
#pragma comment(lib,"fileextd.lib")
#endif//
#pragma comment(lib,"ws2_32.lib")
#endif//

