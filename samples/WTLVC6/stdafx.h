// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__123BF4A9_6F34_453F_8D72_3E91E0F9A633__INCLUDED_)
#define AFX_STDAFX_H__123BF4A9_6F34_453F_8D72_3E91E0F9A633__INCLUDED_

// Change these values to use different versions
#define WINVER		0x0501
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200

// This is required for hosting browser in ATL7
//#define _ATL_DLL

// TODO: 在此处引用程序需要的其他头文件

#include <XLib/UILite.h>

#include <ShlObj.h>
#include <Shlwapi.h>
#include <ShellAPI.h>
#include <Psapi.h>
//#pragma comment(lib, "ShlObj.lib")
#pragma comment(lib, "Shlwapi.lib")
//#pragma comment(lib, "ShellAPI.lib")
#pragma comment(lib, "Psapi.lib")

#include <UI/UIApp.h>
class WTLVC6Module : public UIAppModule
{

};
extern WTLVC6Module _Module;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__123BF4A9_6F34_453F_8D72_3E91E0F9A633__INCLUDED_)
