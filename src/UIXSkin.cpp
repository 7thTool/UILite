#include "stdafx.h"
#include "UIXSkin.h"

#include <skinsb.h>

//UISkinManager* _pUISkinManager = NULL;

//////////////////////////////////////////////////////////////////////////

HTHEME UIXSkinTheme::OpenThemeData(HWND hWnd, LPCWSTR pszClassList)
{
	if (::IsWindow(hWnd)) {
		BOOL bHasScrollBar = FALSE;
		UIWnd wnd;
		wnd.m_hWnd = hWnd;
		DWORD dwStyle = wnd.GetStyle();
		if (dwStyle&(WS_HSCROLL|WS_VSCROLL)) {
			bHasScrollBar = TRUE;
		}
		wnd.m_hWnd = NULL;
		if (bHasScrollBar) {
			SkinSB_Init(hWnd,_pUISkinManager->GetHBITMAP(MAKESKINSTRRESID2(_T("Bitmap"),_T("Scrollbar")),NULL,_T("Scrollbar")));
		}
	}
	return UISkinTheme::OpenThemeData(hWnd,pszClassList);
}

HRESULT UIXSkinTheme::CloseThemeData(HWND hWnd)
{
	if (::IsWindow(hWnd)) {
		SkinSB_Uninit(hWnd);
	}
	return UISkinTheme::CloseThemeData(hWnd);
}
