#include "stdafx.h"
#include "UIXSkinModule.h"

#include "detours.h"
#pragma comment(lib,"detours.lib")

#include <skinsb.h>
#ifdef _DEBUG
#pragma comment(lib,"skinsbd.lib")
#else
#pragma comment(lib,"skinsb.lib")
#endif

//////////////////////////////////////////////////////////////////////////

// 申明钩子
#if 1
DETOUR_TRAMPOLINE(int   WINAPI SetScrollInfoT(HWND, int, LPCSCROLLINFO, BOOL), SetScrollInfo)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollInfoT(HWND, int, LPSCROLLINFO), GetScrollInfo)
DETOUR_TRAMPOLINE(int   WINAPI SetScrollPosT(HWND, int, int, BOOL), SetScrollPos)
DETOUR_TRAMPOLINE(int   WINAPI GetScrollPosT(HWND, int), GetScrollPos)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollRangeT(HWND, int, LPINT, LPINT), GetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI SetScrollRangeT(HWND, int, int, int, BOOL), SetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI ShowScrollBarT(HWND, int, BOOL), ShowScrollBar)
DETOUR_TRAMPOLINE(BOOL  WINAPI EnableScrollBarT(HWND, UINT, UINT), EnableScrollBar)
#else
int   (WINAPI *SetScrollInfoT)(HWND, int, LPCSCROLLINFO, BOOL) = SetScrollInfo;
BOOL  (WINAPI *GetScrollInfoT)(HWND, int, LPSCROLLINFO) = GetScrollInfo;
int   (WINAPI *SetScrollPosT)(HWND, int, int, BOOL) = SetScrollPos;
int   (WINAPI *GetScrollPosT)(HWND, int) = GetScrollPos;
BOOL  (WINAPI *GetScrollRangeT)(HWND, int, LPINT, LPINT) = GetScrollRange;
BOOL  (WINAPI *SetScrollRangeT)(HWND, int, int, int, BOOL) = SetScrollRange;
BOOL  (WINAPI *ShowScrollBarT)(HWND, int, BOOL) = ShowScrollBar;
BOOL  (WINAPI *EnableScrollBarT)(HWND, UINT, UINT) = EnableScrollBar;
#endif//

int WINAPI SetScrollInfoD(HWND hwnd, int fnBar, LPCSCROLLINFO lpsi, BOOL bRedraw)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_SetScrollInfo(hwnd, fnBar, lpsi, bRedraw);
	else
		return SetScrollInfoT(hwnd, fnBar, lpsi, bRedraw);
}

BOOL WINAPI GetScrollInfoD(HWND hwnd, int fnBar, LPSCROLLINFO lpsi)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_GetScrollInfo(hwnd, fnBar, lpsi);
	else
		return GetScrollInfoT(hwnd, fnBar, lpsi);
}

int WINAPI SetScrollPosD(HWND hwnd, int nBar, int nPos, BOOL bRedraw)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_SetScrollPos(hwnd, nBar, nPos, bRedraw);
	else
		return SetScrollPosT(hwnd, nBar, nPos, bRedraw);
}

int WINAPI GetScrollPosD(HWND hwnd, int nBar)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_GetScrollPos(hwnd, nBar);
	else
		return GetScrollPosT(hwnd, nBar);
}

BOOL WINAPI SetScrollRangeD(HWND hwnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_SetScrollRange(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
	else
		return SetScrollRangeT(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
}

BOOL WINAPI GetScrollRangeD(HWND hwnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_GetScrollRange(hwnd, nBar, lpMinPos, lpMaxPos);
	else
		return GetScrollRangeT(hwnd, nBar, lpMinPos, lpMaxPos);
}

BOOL WINAPI ShowScrollBarD(HWND hwnd, int nBar, BOOL bShow)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_ShowScrollBar(hwnd, nBar, bShow);
	else
		return ShowScrollBarT(hwnd, nBar, bShow);
}

BOOL WINAPI EnableScrollBarD(HWND hwnd, UINT wSBflags, UINT wArrows)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_EnableScrollBar(hwnd, wSBflags, wArrows);
	else
		return EnableScrollBarT(hwnd, wSBflags, wArrows);
}

//////////////////////////////////////////////////////////////////////////

UISkinManager* g_pUISkinManager = NULL;

UISkinManager* getUISkinManager()
{
	return g_pUISkinManager;
}

UIXSkinModule::UIXSkinModule()
{
	

}

UIXSkinModule::~UIXSkinModule()
{
	
}

long UIXSkinModule::Init()
{
	g_pUISkinManager = this;

	// 加载钩子
#if 1
	DetourFunctionWithTrampoline((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
	DetourFunctionWithTrampoline((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
	DetourFunctionWithTrampoline((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
	DetourFunctionWithTrampoline((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
	DetourFunctionWithTrampoline((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
	DetourFunctionWithTrampoline((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
	DetourFunctionWithTrampoline((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
	DetourFunctionWithTrampoline((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);
#else
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	// HOOK 函数列表
	DetourAttach((PVOID*)&SetScrollInfoT, SetScrollInfoD);
	DetourAttach((PVOID*)&GetScrollInfoT, GetScrollInfoD);
	DetourAttach((PVOID*)&SetScrollPosT, SetScrollPosD);
	DetourAttach((PVOID*)&GetScrollPosT, GetScrollPosD);
	DetourAttach((PVOID*)&SetScrollRangeT, SetScrollRangeD);
	DetourAttach((PVOID*)&GetScrollRangeT, GetScrollRangeD);
	DetourAttach((PVOID*)&ShowScrollBarT, ShowScrollBarD);
	DetourAttach((PVOID*)&EnableScrollBarT, EnableScrollBarD);
	DetourTransactionCommit();
#endif//

	return RLT_OK;
}

void UIXSkinModule::Term()
{
	g_pUISkinManager = NULL;

	// 卸载钩子
#if 1
	DetourRemove((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
	DetourRemove((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
	DetourRemove((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
	DetourRemove((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
	DetourRemove((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
	DetourRemove((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
	DetourRemove((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
	DetourRemove((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);
#else
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	// 取消 HOOK 函数列表
	DetourDetach((PVOID*)&SetScrollInfoT, SetScrollInfoD);
	DetourDetach((PVOID*)&SetScrollPosT, SetScrollPosD);
	DetourDetach((PVOID*)&GetScrollInfoT, GetScrollInfoD);
	DetourDetach((PVOID*)&GetScrollPosT, GetScrollPosD);
	DetourDetach((PVOID*)&SetScrollRangeT, SetScrollRangeD);
	DetourDetach((PVOID*)&GetScrollRangeT, GetScrollRangeD);
	DetourDetach((PVOID*)&ShowScrollBarT, ShowScrollBarD);
	DetourDetach((PVOID*)&EnableScrollBarT, EnableScrollBarD);
	DetourTransactionCommit();
#endif

	UISkinManager::Clear();
}

BOOL UIXSkinModule::LoadSkin(LPCTSTR lpszXml, UINT XmlFlag, LPCTSTR lpszRoot)
{
	Clear();

	if (XmlFlag & XML_FLAG_FILE) {
		TCHAR szPath[_MAX_PATH];
		_tfullpath(szPath, lpszXml, _MAX_PATH);
		TCHAR szDrive[_MAX_DRIVE], szDir[_MAX_PATH], szName[_MAX_FNAME], szExt[_MAX_EXT];
		_tsplitpath(szPath, szDrive, szDir, szName, szExt);
		int len = _tcslen(szDir);
		if (_tcschr(_T("\\/"), szDir[len-1])) {
			len = len - 1;
			szDir[len] = 0;
		}
		TCHAR* pbrk = _tcsnrbrk(&szDir[len-1], len, _T("\\/"));
		ASSERT(pbrk);
		_tcscpy(szName,pbrk+1);
		_tmakepath(szPath, szDrive, szDir, NULL, NULL);
		SetInfo(_tcsihashlong(szName), szName, szPath, NULL);
	} else {
		TCHAR szDir[_MAX_PATH], szName[_MAX_FNAME];
		CurrentDirectory curdir;
		_tcscpy(szDir,curdir.GetCurrentDirecttory());
		int len = _tcslen(szDir);
		if (_tcschr(_T("\\/"), szDir[len-1])) {
			len = len - 1;
			szDir[len] = 0;
		}
		TCHAR* pbrk = _tcsnrbrk(&szDir[len-1], len, _T("\\/"));
		ASSERT(pbrk);
		_tcscpy(szName,pbrk+1);
		SetInfo(_tcsihashlong(szName), szName, szDir, NULL);
	}

	BEGIN_XML_MAP(lpszRoot)
		BEGIN_XML_ELEMENT_LOOP()
			CHAIN_XML_ELEMENT_HANDLER(LoadElement)
		END_XML_ELEMENT_LOOP()
	END_XML_MAP()

	return TRUE;
}

BOOL UIXSkinModule::LoadElement(LPCTSTR lpszElement, LPCTSTR lpszXml, UINT XmlFlag)
{
	BOOL bOk = FALSE;
	BEGIN_XML_MAP(lpszElement)
		CString strName;
		BEGIN_XML_ATTRIBUTE_LOOP()
			ATTRIBUTE_STRING(_T("name"),strName)
			{
				if (strName.IsEmpty()) {
					LoadAttribute(lpszElement,NULL,lpszAttr,lpszValue);
				} else {
					LoadAttribute(lpszElement,strName,lpszAttr,lpszValue);
				}
			}
		END_XML_ATTRIBUTE_LOOP()
	END_XML_MAP()
	return bOk;
}

BOOL UIXSkinModule::LoadAttribute(LPCTSTR lpszElement, LPCTSTR lpszName, LPCTSTR lpszAttr, LPCTSTR lpszValue)
{
	BOOL bOk = TRUE;
	int nResType = 0;
	if(ParseSkinResType(lpszAttr, nResType)) {
		switch(nResType)
		{
		case UX_RES_IMAGELIST:
			break;
		case UX_RES_IMAGE:
			{
				USES_CONVERSION;
				_pUISkinManager->SetImage(((lpszName&&lpszName[0])?(lpszName+CString(_T("."))+lpszAttr):lpszAttr), new Image(T2CW(lpszValue)), lpszElement);
			}
			break;
		case UX_RES_BITMAP:
			{
				_pUISkinManager->SetHBITMAP(((lpszName&&lpszName[0])?(lpszName+CString(_T("."))+lpszAttr):lpszAttr), UIgdi::BitmapFromFile(lpszValue), lpszElement);
			}
			break;
		case UX_RES_BRUSH:
			{
				_pUISkinManager->SetHBRUSH(((lpszName&&lpszName[0])?(lpszName+CString(_T("."))+lpszAttr):lpszAttr), CreateSolidBrush(_RGB(lpszValue)), lpszElement);
			}
			break;
		case UX_RES_FONT:
			{
				LOGFONT lgfont = _LOGFONT(lpszValue);
				_pUISkinManager->SetHFONT(((lpszName&&lpszName[0])?(lpszName+CString(_T("."))+lpszAttr):lpszAttr), CreateFontIndirect(&lgfont), lpszElement);
			}
			break;
		case UX_RES_COLORREF:
			_pUISkinManager->SetCOLORREF(((lpszName&&lpszName[0])?(lpszName+CString(_T("."))+lpszAttr):lpszAttr), _RGB(lpszValue), lpszElement);
			break;
		case UX_RES_RECT:
			_pUISkinManager->SetRECT(((lpszName&&lpszName[0])?(lpszName+CString(_T("."))+lpszAttr):lpszAttr), _RECT(lpszValue), lpszElement);
			break;
		case UX_RES_STRING:
			_pUISkinManager->SetString(((lpszName&&lpszName[0])?(lpszName+CString(_T("."))+lpszAttr):lpszAttr), lpszValue, lpszElement);
			break;
		}
	}
	return bOk;
}

BOOL UIXSkinModule::ParseSkinResType(LPCTSTR lpszString, int& nResType)
{
	nResType = UX_RES_NONE;
	TCHAR* pNext = (TCHAR*)lpszString;
	if (pNext) {
		if (_tcsnicmp(pNext,_T("ImageList"), 9) == 0) {
			nResType = UX_RES_IMAGELIST;
		} else if (_tcsnicmp(pNext,_T("Image"), 5) == 0) {
			nResType = UX_RES_IMAGE;
		} else if (_tcsnicmp(pNext,_T("Bitmap"), 6) == 0) {
			nResType = UX_RES_BITMAP;
		} else if (_tcsnicmp(pNext,_T("Brush"), 5) == 0) {
			nResType = UX_RES_BRUSH;
		} else if (_tcsnicmp(pNext,_T("Font"), 4) == 0) {
			nResType = UX_RES_FONT;
		} else if (_tcsnicmp(pNext,_T("Color"), 5) == 0) {
			nResType = UX_RES_COLORREF;
		} else if (_tcsnicmp(pNext,_T("Rect"), 4) == 0) {
			nResType = UX_RES_RECT;
		} else if (_tcsnicmp(pNext,_T("Text"), 4) == 0) {
			nResType = UX_RES_STRING;
		}
	}
	return nResType;
}
