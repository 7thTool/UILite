
#pragma once

#ifndef _H_UIBASE_H_
#define _H_UIBASE_H_

//MS VC++ 14.0 _MSC_VER = 1900 (Visual Studio 2015)
//MS VC++ 12.0 _MSC_VER = 1800 (VisualStudio 2013)
//MS VC++ 11.0 _MSC_VER = 1700 (VisualStudio 2012)
//MS VC++ 10.0 _MSC_VER = 1600(VisualStudio 2010)
//MS VC++ 9.0 _MSC_VER = 1500(VisualStudio 2008)
//MS VC++ 8.0 _MSC_VER = 1400(VisualStudio 2005)
//MS VC++ 7.1 _MSC_VER = 1310(VisualStudio 2003)
//MS VC++ 7.0 _MSC_VER = 1300(VisualStudio.NET)
//MS VC++ 6.0 _MSC_VER = 1200(VisualStudio 98)
//MS VC++ 5.0 _MSC_VER = 1100(VisualStudio 97)

//====为EXE工程加入ATL/WTL支持=========================================   
//1.在工程的stdafx.h中除去#include   <windows.h>,加上   
//#include   <atlbase.h>   
//#include   <atlapp.h>   
//extern   CComModule   _Module;或extern   CAppModule   _Module;   
//2.在工程主cpp(即main所处的文件中加入:   
//CComModule   _Module;   或CAppModule   _Module;   
//3.在main入口中模块加载处加入:   
//_Module.Init(NULL,   HINSTANCE(hModule));   
//4.在main入口模块撤载处加入   
//_Module.Term();   
//
//====为VC6   ATL   DLL工程加入WTL支持=========================================   
//1.在工程的stdafx.h中的加上   
//#include   <atlapp.h>   
//将extern   CComModule   _Module;改为extern   CAppModule   _Module;   
//2.在工程主cpp,即main所处的文件中改为:   
//CAppModule   _Module;   
//
//====为VC.NET2003   ATL工程工程加入WTL支持=========================================   
//1.在工程的stdafx.h的#include   <atlbase.h>后   
//加入#include   <atlapp.h>   
//去掉#include   <atltypes.h>   
//
//====为将MFC工程加入ATL/WTL支持===============================================   
//1.在工程的stdafx.h中尾部加入   
//#define   _WTL_NO_AUTOMATIC_NAMESPACE   
//#include   <atlbase.h>   
//#include   <atlapp.h>   
//extern   WTL::CAppModule   _Module;   
//2.在工程theApp声明下加入:   
//WTL::CAppModule   _Module;   
//3.在InitInstance中部加入   
//_Module.Init(NULL,   theApp.m_hInstance);   
//4.在ExitInstance中加入   
//_Module.Term();   
//5.必须使用WTL   namespace.

#include <vector>
#include <deque>
#include <queue>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <ostream>
#include <fstream>
#include <sstream>
#include <ios>
#include <iomanip>

#include <algorithm>
#include <functional>
using namespace std;

#ifndef STRICT
#define STRICT
#endif//
#if _MSC_VER<=1200
#else
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif//
#endif//

#ifndef _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的
#endif//

#if _MSC_VER<=1200
#else
#ifndef _WTL_NO_WTYPES
#define _WTL_NO_WTYPES
#endif//
#ifndef _WTL_NO_CSTRING
#define _WTL_NO_CSTRING
#endif//
#ifdef _AFX
#define _CSTRING_NS
#endif//
#endif//

#include <atlbase.h>
#include <atlcoll.h>
//#include <atlcom.h>
//#include <atlhost.h>
//#include <atlwin.h>
//#include <atlctl.h>
//#include <atlconv.h>
#if _MSC_VER<=1200
#else
#include <atlstr.h>
#include <atlenc.h>
#include <atlimage.h>
#endif//

#include <wtl/atlapp.h>
#include <wtl/atlcrack.h>
#include <wtl/atlmisc.h>
//#include <atlgdi.h>
//#ifdef _WIN32_WCE
//#include <atlresce.h>
//#endif//
//#include <atlframe.h>
//#include <atlctrls.h>
//#include <atldlgs.h>
//#include <atlctrlw.h>
//#include <atlctrlx.h>
//#include <atlsplit.h>

#if _MSC_VER > 1500 // Visual Studio 2008
#ifndef _WTL_USE_VSSYM32
#define _WTL_USE_VSSYM32
#endif//_WTL_USE_VSSYM32
#endif
#if defined(_WTL_USE_VSSYM32) || (defined(NTDDI_VERSION) && (NTDDI_VERSION >= NTDDI_LONGHORN))
#include <vssym32.h>
#else
#ifndef TMSCHEMA_H
#include <tmschema.h>
#endif
#endif

//struct __POSITION {};
//typedef __POSITION* POSITION;

#ifdef _VC80X
// Support for VS2005 Express & SDK ATL
#define _CRT_SECURE_NO_DEPRECATE
#pragma conform(forScope, off)
#pragma comment(linker, "/NODEFAULTLIB:atlthunk.lib")
#pragma warning(disable: 4565) // redefinition; the symbol was previously declared with __declspec(noalias)
#pragma warning(disable: 4068) // unknown pragma
#endif // _VC80X

#ifdef _VC80X
// Support for VS2005 Express & SDK ATL
namespace ATL
{
	inline void * __stdcall __AllocStdCallThunk()
	{
		return ::HeapAlloc(::GetProcessHeap(), 0, sizeof(_stdcallthunk));
	}

	inline void __stdcall __FreeStdCallThunk(void *p)
	{
		::HeapFree(::GetProcessHeap(), 0, p);
	}
};
#endif // _VC80X

#if (_ATL_VER < 0x0700)
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4189) // local variable is initialized but not referenced
#endif

#ifndef ASSERT
#ifndef _AFX
#define ASSERT	ATLASSERT
#else
#include <assert.h>
#define ASSERT	assert
#endif//
#endif//
#ifndef VERIFY
#ifndef _DEBUG
#define VERIFY(f) f
#else
#define VERIFY(f) ASSERT(f)
#endif//
#endif//

class STRINGorID
{
public:
	STRINGorID(LPCTSTR lpString) : m_lpstr(lpString) { }
	STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID)) { }
	operator LPCTSTR () { return m_lpstr; }
	LPCTSTR m_lpstr;
};

#ifndef _AFX
template <class T> 
class CArray : public CSimpleArray<T>
{
public:
	int SetSize(int nSize)
	{
		if (nSize > m_nAllocSize)
		{
			T* aT;
			int nNewAllocSize = nSize;
			aT = (T*)::realloc(m_aT, nNewAllocSize * sizeof(T));
			if(aT == NULL)
				return 0;
			m_nAllocSize = nNewAllocSize;
			m_nSize = nSize;
			m_aT = aT;
		}
		return m_nSize;
	}

	int GetCount()
	{
		return GetSize();
	}

	BOOL IsEmpty() 
	{ 
		return GetSize() == 0 ? TRUE : FALSE;
	}
};
typedef CArray<CString> CStringArray;
#endif//_AFX

struct CStringLess
{
	bool operator()(const CString& x, const CString& y) const
	{
		return x.Compare(y) < 0;
	}
};

struct CStringNoCaseLess
{
	bool operator()(const CString& x, const CString& y) const
	{
		return x.CompareNoCase(y) < 0;
	}
};

#if _MSC_VER <= 1200
#define __in
#define __out
#define _Inout_
#define __in_opt
#ifndef ATL_VARIANT_TRUE
#define ATL_VARIANT_TRUE VARIANT_BOOL( -1 )
#endif//
#ifndef ATL_VARIANT_FALSE
#define ATL_VARIANT_FALSE VARIANT_BOOL( 0 )
#endif//
#endif//

//必须放在STL之前
#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

//WM
#ifndef WM_DPICHANGED
#define WM_DPICHANGED                   0x02E0
#endif//

extern UINT WM_MSG_TASKBARCREATED;

typedef struct tagPaintEffect
{
	HWND hWnd;
	HDC hDstDC;
	HDC hSrcDC;
}PAINTEFFECT,*PPAINTEFFECT;

enum
{
	WM_UIUSER_BEGIN		= WM_USER,
	WM_BACKWARDMSG,								//类似WM_FORWARDMSG,不过刚好相反
	WM_POSTDIRECTUIMSG,							//DirectUI Post消息
	WM_PAINTEFFECTMSG,							//OnPaint画完之后消息，可以实现动画特效
	WM_POSTEVENTMSG,							//事件 Post消息
	//
	WM_UIUSER			= WM_USER + 50,
};

//WM_COMMAND
#ifndef CN_UPDATE_COMMAND_UI
#define CN_UPDATE_COMMAND_UI    ((UINT)(-1))    // void (CUpdateUIBase*)
#endif//CN_UPDATE_COMMAND_UI
enum
{
	ID_COMMAND_UI		= 0XF100 + 50,			//
	ID_PANE_CREATE,								//创建一个Pane
	//
	ID_COMMAND_UIUSER	= ID_COMMAND_UI + 50,
};


#endif//_H_UIBASE_H_