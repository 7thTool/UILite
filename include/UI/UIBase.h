
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

//====ΪEXE���̼���ATL/WTL֧��=========================================   
//1.�ڹ��̵�stdafx.h�г�ȥ#include   <windows.h>,����   
//#include   <atlbase.h>   
//#include   <atlapp.h>   
//extern   CComModule   _Module;��extern   CAppModule   _Module;   
//2.�ڹ�����cpp(��main�������ļ��м���:   
//CComModule   _Module;   ��CAppModule   _Module;   
//3.��main�����ģ����ش�����:   
//_Module.Init(NULL,   HINSTANCE(hModule));   
//4.��main���ģ�鳷�ش�����   
//_Module.Term();   
//
//====ΪVC6   ATL   DLL���̼���WTL֧��=========================================   
//1.�ڹ��̵�stdafx.h�еļ���   
//#include   <atlapp.h>   
//��extern   CComModule   _Module;��Ϊextern   CAppModule   _Module;   
//2.�ڹ�����cpp,��main�������ļ��и�Ϊ:   
//CAppModule   _Module;   
//
//====ΪVC.NET2003   ATL���̹��̼���WTL֧��=========================================   
//1.�ڹ��̵�stdafx.h��#include   <atlbase.h>��   
//����#include   <atlapp.h>   
//ȥ��#include   <atltypes.h>   
//
//====Ϊ��MFC���̼���ATL/WTL֧��===============================================   
//1.�ڹ��̵�stdafx.h��β������   
//#define   _WTL_NO_AUTOMATIC_NAMESPACE   
//#include   <atlbase.h>   
//#include   <atlapp.h>   
//extern   WTL::CAppModule   _Module;   
//2.�ڹ���theApp�����¼���:   
//WTL::CAppModule   _Module;   
//3.��InitInstance�в�����   
//_Module.Init(NULL,   theApp.m_hInstance);   
//4.��ExitInstance�м���   
//_Module.Term();   
//5.����ʹ��WTL   namespace.

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
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��
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

//�������STL֮ǰ
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
	WM_BACKWARDMSG,								//����WM_FORWARDMSG,�����պ��෴
	WM_POSTDIRECTUIMSG,							//DirectUI Post��Ϣ
	WM_PAINTEFFECTMSG,							//OnPaint����֮����Ϣ������ʵ�ֶ�����Ч
	WM_POSTEVENTMSG,							//�¼� Post��Ϣ
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
	ID_PANE_CREATE,								//����һ��Pane
	//
	ID_COMMAND_UIUSER	= ID_COMMAND_UI + 50,
};


#endif//_H_UIBASE_H_