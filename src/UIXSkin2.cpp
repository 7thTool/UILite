#include "stdafx.h"
#include "UIXSkin2.h"
//#include "UIXWnd2.h"

//#include <skinsb.h>

//////////////////////////////////////////////////////////////////////////

HTHEME UIXSkin2Theme::OpenThemeData(HWND hWnd, LPCWSTR pszClassList)
{
	/*if (!_pUIWnd2Manager->IsDirectUI(hWnd)) {
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
	}*/
	return UIXSkinTheme::OpenThemeData(hWnd,pszClassList);
}

HRESULT UIXSkin2Theme::CloseThemeData(HWND hWnd)
{
	/*if (!_pUIWnd2Manager->IsDirectUI(hWnd)) {
		SkinSB_Uninit(hWnd);
	}*/
	return UIXSkinTheme::CloseThemeData(hWnd);
}
