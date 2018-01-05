#ifndef _H_UILITE_H_
#define _H_UILITE_H_

#include <XLib/XLib.h>

#ifdef UILITE_DLL
#ifdef UILITE_EXPORTS
#define UILITE_API __declspec(dllexport)
#else
#define UILITE_API __declspec(dllimport)
#endif//UILITE_EXPORTS
#else
#define	UILITE_API 
#ifdef UILITE_EXPORTS
#else
#endif//
#endif//UILITE_DLL

#ifndef UILITE_EXPORTS
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

#endif//_H_UILITE_H_