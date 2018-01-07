#ifndef _H_UILITE_H_
#define _H_UILITE_H_

#include <XLib/XLib.h>

#ifndef UILITE_DLL
#ifdef XLIB_DLL
#define UILITE_DLL
#endif//
#endif//

#ifdef UILITE_DLL
#ifdef UILITE_EXPORTS
#define UILITE_API __declspec(dllexport)
#else
#define UILITE_API __declspec(dllimport)
#ifdef _AFX
#pragma comment(lib, "MFCLite.lib")
#else
#if _MSC_VER<=1200
#pragma comment(lib, "UILiteVC6.lib")
#else
#pragma comment(lib, "UILite.lib")
#endif//
#endif//_AFX
#endif//UILITE_EXPORTS
#else
#define	UILITE_API 
#endif//UILITE_DLL

#endif//_H_UILITE_H_