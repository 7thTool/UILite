
#pragma once

#ifndef _H_UISKIN_H_
#define _H_UISKIN_H_

#include "UIWnd.h"
#include "UITheme.h"

#ifndef _AFX

#include "UICtrl.h"

enum RC_TYPE
{
	RC_BACKGROUND = 0,
	RC_FOREGROUND,
	RC_BORDER,
	RC_NORMAL,
	RC_FOCUS,
	RC_SELECT,
	RC_GRAYED,
};
#define MAKERCID(id,rctype)	MAKELONG(id,rctype)

template<class T>
class UISkinMap : public UIOwnerDraw<T>, public UIID2GdiManager
{
public:
	BEGIN_MSG_MAP_EX(UISkinMap)
		COMMAND_RANGE_HANDLER_EX(0, (UINT)-1, OnCommand)
		CHAIN_MSG_MAP(UIOwnerDraw<T>)
	END_MSG_MAP()

	void OnCommand(UINT uCode, int nCtrlID, HWND hwndCtrl)
	{
		T* pT = static_cast<T*>(this);
		if (pT->GetHDC()) {
			if (::GetWindowLong(hwndCtrl, GWL_EXSTYLE) & WS_EX_TRANSPARENT) {
				TCHAR szClassName[MAX_PATH] = {0};
				if (uCode == EN_CHANGE && ::GetClassName(hwndCtrl, szClassName, MAX_PATH)) {
					if (_tcsicmp(UIEdit::GetWndClassName(), szClassName) == 0) {
						//::InvalidateRect(hwndCtrl, NULL, FALSE);
						//::UpdateWindow(hwndCtrl);
						::RedrawWindow(hwndCtrl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
						return;
					}
				}
			}
		}
		SetMsgHandled(FALSE);
	}

	HBRUSH OnCtlColor(HDC hdc, HWND hWnd, UINT nCtlColor)
	{  
		T* pT = static_cast<T*>(this);
		BOOL bTransparent = FALSE;
		INT nBkMode = GetBkMode(hdc);
		if (nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN) {
			bTransparent = TRUE;
			nBkMode = TRANSPARENT;
		} else {
			if (::GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_TRANSPARENT) {
				bTransparent = TRUE;
				if (nCtlColor == CTLCOLOR_EDIT) {
					nBkMode = TRANSPARENT;
				}
			}
		}
		::SetBkMode(hdc, nBkMode);
		if (bTransparent) {
			HDC hSrcDC = pT->GetHDC();
			if (hSrcDC) {
				RECT rcWnd;
				::GetWindowRect(hWnd, &rcWnd);
				pT->ScreenToClient(&rcWnd);
				HBRUSH hbr = (HBRUSH)UIgdi::CreateBrushFromDC(hSrcDC, &rcWnd);
				pT->SetHBRUSH(::GetDlgCtrlID(hWnd), hbr);
				return hbr;
			}
			return GetStockBrush(HOLLOW_BRUSH);
		}
		return UIOwnerDraw<T>::OnCtlColor(hdc, hWnd, nCtlColor);
	}

	//OwnerDraw
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		switch(lpDrawItemStruct->CtlType)
		{
		case ODT_BUTTON: //Owner-drawn button
			{
				/*T* pT = static_cast<T*>(this);
				UIWnd UICtrl(lpDrawItemStruct->hwndItem);
				UINT CtlID		= lpDrawItemStruct->CtlID;
				RECT rcItem		= lpDrawItemStruct->rcItem;
				HDC hdc			= lpDrawItemStruct->hDC;
				UINT nItemAction= lpDrawItemStruct->itemAction;
				UINT nItemState	= lpDrawItemStruct->itemState;
				DWORD dwStyle	= pT->GetStyle();

				//1, Draw background
				if (nItemAction & ODA_DRAWENTIRE) {
				RECT rcWnd;
				UICtrl.GetWindowRect(&rcWnd);
				pT->ScreenToClient(&rcWnd);
				HBRUSH hbr = (HBRUSH)m_hDC.CreateBrushFromRect(&rcWnd);
				pT->SetHBRUSH(CtlID, hbr);
				::FillRect(hdc, &rcItem, hbr);
				//return;
				}

				//2, Draw button
				long Id = 0;
				if ((nItemState & ODS_DISABLED)) {
				Id = MAKERCID(CtlID,RC_GRAYED);
				} else if ((nItemState & ODS_SELECTED) || (nItemAction & ODA_SELECT)) {
				Id = MAKERCID(CtlID,RC_SELECT);
				} else if((nItemState & ODS_FOCUS) || (nItemState & ODS_HOTLIGHT) || (nItemAction & ODS_FOCUS)) {
				Id = MAKERCID(CtlID,RC_FOCUS);
				} else {
				Id = MAKERCID(CtlID,RC_NORMAL);
				}
				Image* pImg	= pT->GetImage(Id);
				if (pImg == NULL) {
				pImg = pT->GetImage(MAKERCID(CtlID,RC_NORMAL));
				}
				if (pImg) {
				Graphics graphics(hdc);
				graphics.DrawImage(pImg, 
				rcItem.left, rcItem.top, 0, 0, rcItem.right-rcItem.left, rcItem.bottom-rcItem.top, UnitPixel);
				} else {
				UINT uStyle = DFCS_BUTTONPUSH;
				if ((nItemState & ODS_SELECTED) || (nItemAction & ODA_SELECT))
				uStyle |= DFCS_PUSHED;
				::DrawFrameControl(hdc, &rcItem, DFC_BUTTON, uStyle);
				}
				//Draw Lable
				CString strWindowText;
				UICtrl.GetWindowText(strWindowText);
				if (!strWindowText.IsEmpty()) {
				::SetBkMode(hdc, TRANSPARENT);
				HFONT hFont = 
				(HFONT)::SelectObject(hdc, pT->GetHFONT(Id, UICtrl.GetFont()));
				COLORREF Color = 
				(COLORREF)::SetTextColor(lpDrawItemStruct->hDC, pT->GetCOLORREF(Id,::GetTextColor(hdc)));
				UINT nFormat = DT_VCENTER | DT_VCENTER 
				| (dwStyle&BS_MULTILINE)?0:DT_SINGLELINE
				| (dwStyle&BS_LEFT)?DT_LEFT:0
				| (dwStyle&BS_RIGHT)?DT_RIGHT:0
				| DT_VCENTER | DT_PATH_ELLIPSIS;
				::DrawText(hdc, strWindowText, strWindowText.GetLength(), &rcItem, nFormat);
				::SetTextColor(lpDrawItemStruct->hDC, Color);
				::SelectObject(lpDrawItemStruct->hDC, hFont);
				}
				return;*/
			}
			break;
		case ODT_COMBOBOX: //Owner-drawn combo box
			{

			}
			break;
		case ODT_LISTBOX: //Owner-drawn list box
			{

			}
			break;
		case ODT_LISTVIEW: //List-view control
			{

			}
			break;
		case ODT_MENU: //Owner-drawn menu item
			{

			}
			break;
		case ODT_STATIC: //Owner-drawn static control
			{

			}
			break;
		case ODT_TAB: //Tab control
			{

			}
			break;
		default:
			break;
		}
		return UIOwnerDraw<T>::DrawItem(lpDrawItemStruct);
	}
};

template<class T, class TBase = UIWnd, class TWinTraits = CControlWinTraits>
class UIAlphaWndImpl : public UIWndImpl<T, TBase, TWinTraits>
{
	typedef UIAlphaWndImpl<T, TBase, TWinTraits> This;
	typedef UIWndImpl<T, TBase, TWinTraits> Base;
public:
	UIAlphaWndImpl() : m_pbitmap(0) {}
	~UIAlphaWndImpl() {m_pbitmap = 0;}

	//HDC GetHDC() { return m_hmemdc; }
	void SetBitmap(Image* pbitmap) { m_pbitmap = pbitmap;  }
	Image* GetBitmap() { return m_pbitmap; }

	void Render()
	{
		if (!m_pbitmap) {
			return ;
		}
		CRect rcWnd;
		GetWindowRect(&rcWnd);
		CRect rcClient;
		GetClientRect(&rcClient);
		if (!m_memdc) {
			HDC hdc = GetDC();
			m_memdc.CreateCompatibleDC(hdc, &rcClient);
			ReleaseDC(hdc);
		}
		Graphics graph((HDC)m_memdc);
		//graph.SetSmoothingMode(SmoothingModeHighQuality);
		graph.DrawImage(m_pbitmap, 0, 0, rcClient.Width(), rcClient.Height());
		BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
		POINT ptDst = {rcWnd.left, rcWnd.top};
		POINT ptSrc = {0, 0};
		UpdateLayeredWindow(m_hWnd, NULL, &ptDst, &rcClient.Size(), (HDC)m_memdc, &ptSrc, 0, &blend, ULW_ALPHA);
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		ModifyStyle(WS_CAPTION, WS_POPUP);
#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED           0x00080000
#endif//WS_EX_LAYERED
		ModifyStyleEx(0, WS_EX_LAYERED);
		return bHandled;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (wParam != SIZE_MINIMIZED && lParam != 0) {
			m_memdc.DeleteDC();
			Render();
		}
		return bHandled;
	}

protected:
	CMemDC m_memdc;
	Image* m_pbitmap;
};

class UIBkgndWnd : public UIAlphaWndImpl<UIBkgndWnd>
{
	typedef UIAlphaWndImpl<UIBkgndWnd> Base;
protected:
	HWND m_hHost;
public:
	UIBkgndWnd(HWND hHost = NULL) : m_hHost(hHost) {}
	~UIBkgndWnd() {}

	void SetHost(HWND hHost) { m_hHost = hHost; }
	HWND GetHost() { return m_hHost; }

	BEGIN_MSG_MAP(Border)
		MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, SendMessageToHost)
		MESSAGE_HANDLER(WM_CONTEXTMENU, SendMessageToHost)
		MESSAGE_HANDLER(WM_SETFOCUS, SendMessageToHost)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT SendMessageToHost(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_hHost) {
			return ::SendMessage(m_hHost, uMsg, wParam, lParam);
		}
		return bHandled;
	}
};

// template<class T, class TBase, class TBkgnd = UIBkgndWnd>
// class UIDBPopupWndImpl : public TBase
// {
// 	typedef UIDBPopupWndImpl<T, TBase> This;
// 	typedef TBase Base;
// public:
// 	TBkgnd m_Bkgnd;
// 	SIZE m_szOffset;
// public:
// 	UIDBPopupWndImpl() 
// 	{ 
// 		m_szOffset.cx = 0;
// 		m_szOffset.cy = 0;
// 	}
// 
// 	HWND Create(HWND hWndParent, _U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
// 		DWORD dwStyle = 0, DWORD dwExStyle = 0, _U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
// 	{
// 		m_Bkgnd.Create(hWndParent, rect, szWindowName
// 			, WS_POPUP | (dwStyle & WS_VISIBLE) ? WS_VISIBLE : 0
// 			, WS_EX_LAYERED | WS_EX_TOOLWINDOW
// 			);
// 		HWND hWnd = Base::Create(m_Bkgnd, rect, szWindowName, dwStyle, dwExStyle, MenuOrID, lpCreateParam);
// 
// 		ASSERT(m_hWnd);
// 		m_Bkgnd.SetHost(m_hWnd);
// 
// 		RECT rcWnd;
// 		GetWindowRect(&rcWnd);
// 		RECT rcBkgnd;
// 		m_Bkgnd.GetWindowRect(&rcBkgnd);
// 		m_szOffset.cx = rcWnd.left - rcBkgnd.left;
// 		m_szOffset.cy = rcWnd.top - rcBkgnd.top;
// 
// 		return hWnd;
// 	}
// 
// 	void UpdateLayout()
// 	{
// 		ASSERT(IsWindow() && m_Bkgnd.IsWindow());
// 		RECT rcWnd;
// 		GetWindowRect(&rcWnd);
// 		RECT rcBkgnd;
// 		m_Bkgnd.GetWindowRect(&rcBkgnd);
// 		RECT rcNewBkgnd = rcBkgnd;
// 		rcNewBkgnd.left = rcWnd.left - m_szOffset.cx;
// 		rcNewBkgnd.top = rcWnd.top - m_szOffset.cy;
// 		rcNewBkgnd.right = rcNewBkgnd.left + (rcBkgnd.right - rcBkgnd.left);
// 		rcNewBkgnd.bottom = rcNewBkgnd.top + (rcBkgnd.bottom - rcBkgnd.top);
// 		m_Bkgnd.MoveWindow(&rcNewBkgnd, TRUE);
// 	}
// 
// 	void SetWindowOffset(int cx, int cy)
// 	{
// 		m_szOffset.cx = cx;
// 		m_szOffset.cy = cy;
// 		UpdateLayout();
// 	}
// 
// 	void SetWindowOffset(LPSIZE lpSize)
// 	{
// 		SetWindowOffset(lpSize->cx, lpSize->cy);
// 	}
// 
// //  	BOOL SetWindowPos(HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags)
// //  	{
// //  		ATLASSERT(::IsWindow(m_hWnd));
// //  		m_Bkgnd.SetWindowPos(hWndInsertAfter, lpRect, nFlags);
// //  		return Base::SetWindowPos(hWndInsertAfter, lpRect, nFlags);
// //  	}
// 
// 	BEGIN_MSG_MAP(This)
// 		//MESSAGE_HANDLER(WM_CREATE, OnCreate)
// 		MESSAGE_HANDLER(WM_CLOSE, OnClose)
// 		//MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
// 		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
// 		MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanged)
// 		MESSAGE_HANDLER(WM_ENABLE, OnEnable)
// 		CHAIN_MSG_MAP(Base)
// 	END_MSG_MAP()
// 
// 	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
// 	{
// 		bHandled = FALSE;
// 		/*T* pT = static_cast<T*>(this);
// 		ASSERT(m_hWnd);
// 		m_Bkgnd.SetHost(m_hWnd);
// 
// 		RECT rcWnd;
// 		pT->GetWindowRect(&rcWnd);
// 		RECT rcBorder;
// 		m_Bkgnd.GetWindowRect(&rcBorder);
// 		int nXOffset = rcWnd.left - rcBorder.left;
// 		int nYOffset = rcWnd.top - rcBorder.top;*/
// 
// 		return bHandled;
// 	}
// 
// 	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
// 	{
// 		bHandled = FALSE;
// 		m_Bkgnd.SetHost(NULL);
// 		m_Bkgnd.PostMessage(uMsg, wParam, lParam);
// 		return bHandled;
// 	}
// 
// // 	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
// // 	{
// // 		bHandled = FALSE;
// // 		T* pT = static_cast<T*>(this);
// // 		m_Bkgnd.SetHost(NULL);
// // 		m_Bkgnd.DestroyWindow();
// // 		return bHandled;
// // 	}
// 
// 	LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
// 	{
// 		bHandled = FALSE;
// 		m_Bkgnd.ShowWindow(wParam);
// 		return bHandled;
// 	}
// 
// 	LRESULT OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
// 	{
// 		bHandled = FALSE;
// 		UpdateLayout();
// 		return bHandled;
// 	}
// 
// 	LRESULT OnEnable(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
// 	{
// 		bHandled = FALSE;
// 		m_Bkgnd.EnableWindow(wParam);
// 		return bHandled;
// 	}
// };
// 
// template <class T, class TBase  = UIWnd, class TWinTraits = CControlWinTraits>
// class UISkinWndExImpl : public UIDBPopupWndImpl<T, UISkinWndImpl<T, TBase, TWinTraits>>
// {
// 	typedef UISkinWndExImpl<T, TBase, TWinTraits> This;
// 	typedef UIDBPopupWndImpl<T, UISkinWndImpl<T, TBase, TWinTraits>> Base;
// public:
// 	UISkinWndExImpl() : Base()
// 	{
// 
// 	}
// 
// 	void DrawBackgnd(HDC hdc)
// 	{
// 		T* pT = static_cast<T*>(this);
// 		Base::DrawBackgnd(hdc);
// 		Image* pImage = m_Bkgnd.GetBitmap();
// 		if (pImage) {
// 			//RECT rcBkgnd;
// 			//m_Bkgnd.GetWindowRect(&rcBkgnd);
// 			Graphics graphics(hdc);
// 			graphics.DrawImage(pImage, 0, 0, 
// 				m_szOffset.cx, m_szOffset.cy, 
// 				pImage->GetWidth() - m_szOffset.cx, pImage->GetHeight() - m_szOffset.cy, UnitPixel);
// 			graphics.ReleaseHDC(hdc);
// 		}
// 	}
// 
// 	BEGIN_MSG_MAP(This)
// 		CHAIN_MSG_MAP(Base)
// 	END_MSG_MAP()
// };

#else
//
#endif//_AFX

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIBkgndSkinDrawMap : public UIBkgnd<T>, public UIPaintFF<T>
{
public:

	BOOL EraseBkgnd(HDC hdc)
	{
		T* pT = static_cast<T*>(this);

		CRect rcClient;
		pT->GetClientRect(&rcClient);
		pT->PaintBkgnd(hdc,&rcClient);

		return TRUE;
	}
};

//////////////////////////////////////////////////////////////////////////

#define MAKESKINRESID3(wId,iPartId,iStateId)	MAKELONG(wId,MAKEWORD(iPartId,iStateId))
#define MAKESKINRESID2(wId,wType)				MAKELONG(wId,MAKEWORD(LOWORD(wType),HIWORD(wType))) 
#define MAKESKINRESID(wId)						(wId)

#define MAKESKINSTRRESID3(wId,iPartId,iStateId) ((wId)+CString(_T("_"))+(iPartId)+CString(_T("_"))+iStateId)
#define MAKESKINSTRRESID2(wId,wType)			((wId)+CString(_T("_"))+wType) 
#define MAKESKINSTRRESID(wId)					(wId)

class UISkinManager : public UIStr2GdiManager
{
/*private:
	static UISkinManager* ms_pInstance;
public:
	static UISkinManager* Instance()
    {
        if (!ms_pInstance)
            ms_pInstance = new UISkinManager;
        return ms_pInstance;
    }
	static void Release() 
	{
		if (ms_pInstance) {
			delete ms_pInstance;
		}
		ms_pInstance = NULL;
	}*/
	
protected:
	UINT m_nId;
	CString m_strName;
	CString m_strSkinPath;
	CString m_strDescription;
	typedef std::map<CString,UIStr2GdiManager*,CStringNoCaseLess> CLASS2pGDIManager;
	CLASS2pGDIManager m_Class2pGDIManager;
public:
	UISkinManager() { }
	~UISkinManager() { Clear(); }

	void SetInfo(UINT nId, LPCTSTR lpszName, LPCTSTR lpszSkinPath, LPCTSTR lpszDescription)
	{
		m_nId = nId;
		m_strName = lpszName;
		m_strSkinPath = lpszSkinPath;
		m_strDescription = lpszDescription;
	}

	UINT GetID() { return m_nId; }

	LPCTSTR GetName() { return m_strName; }

	LPCTSTR GetSkinPath() { return m_strSkinPath; }

	LPCTSTR GetDescription() { return m_strDescription; }

	UIStr2GdiManager* FindGDIManager(LPCTSTR lpszClassName, BOOL bCreate = FALSE)
	{
		if (lpszClassName==NULL || lpszClassName[0]==0 || _tcsicmp(lpszClassName,_T("global"))==0) {
			return this;
		}
		if (lpszClassName) {
			CString strClassName(lpszClassName);
			CLASS2pGDIManager::iterator it = m_Class2pGDIManager.find(strClassName);
			if ((it==m_Class2pGDIManager.end() || !it->second)) {
				if (bCreate) {
					UIStr2GdiManager* pGDIManager = new UIStr2GdiManager();
					m_Class2pGDIManager[strClassName] = pGDIManager;
					return pGDIManager;
				}
			} else {
				return it->second;
			}
		}
		return NULL;
	}

	void Clear()
	{
		CLASS2pGDIManager::iterator it = m_Class2pGDIManager.begin();
		for (; it != m_Class2pGDIManager.end(); ++it)
		{
			UIStr2GdiManager* pGDIManager = it->second;
			if (pGDIManager) {
				pGDIManager->Clear();
				delete pGDIManager;
				pGDIManager = NULL;
			}
		}
		m_Class2pGDIManager.clear();
		UIStr2GdiManager::Clear();
	}

	void SetImageList(const CString &id, HIMAGELIST imagelist, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName, TRUE);
		if (pGDIManager) {
			pGDIManager->SetImageList(id, imagelist);
		}
	}
	void SetImage(const CString &id, Image* image, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName, TRUE);
		if (pGDIManager) {
			pGDIManager->SetImage(id, image);
		}
	}
	void SetHBITMAP(const CString &id, HBITMAP bitmap, LPCTSTR lpszClassName = NULL)
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName, TRUE);
		if (pGDIManager) {
			pGDIManager->SetHBITMAP(id, bitmap);
		}
	}
	void SetHBRUSH(const CString &id, HBRUSH brush, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName, TRUE);
		if (pGDIManager) {
			pGDIManager->SetHBRUSH(id, brush);
		} 
	}
	void SetHFONT(const CString &id, HFONT font, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName, TRUE);
		if (pGDIManager) {
			pGDIManager->SetHFONT(id, font);
		} 
	}
	void SetCOLORREF(const CString &id, COLORREF color, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName, TRUE);
		if (pGDIManager) {
			pGDIManager->SetCOLORREF(id, color);
		} 
	}
	void SetRECT(const CString &id, RECT rect, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName, TRUE);
		if (pGDIManager) {
			pGDIManager->SetRECT(id, rect);
		} 
	}
	void SetString(const CString &id, LPCTSTR lpszStr, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName, TRUE);
		if (pGDIManager) {
			pGDIManager->SetString(id, lpszStr);
		} 
	}
	HIMAGELIST GetImageList(const CString &id, HIMAGELIST Default = NULL, LPCTSTR lpszClassName = NULL)
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName);
		if (pGDIManager) {
			return pGDIManager->GetImageList(id, Default);
		} 
		return Default;
	}
	Image* GetImage(const CString &id, Image* Default = 0, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName);
		if (pGDIManager) {
			return pGDIManager->GetImage(id, Default);
		} 
		return Default;
	}
	HBITMAP GetHBITMAP(const CString &id, HBITMAP Default = NULL, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName);
		if (pGDIManager) {
			return pGDIManager->GetHBITMAP(id, Default);
		} 
		return Default;
	}
	HBRUSH GetHBRUSH(const CString &id, HBRUSH Default = NULL, LPCTSTR lpszClassName = NULL) 
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName);
		if (pGDIManager) {
			return pGDIManager->GetHBRUSH(id, Default);
		} 
		return Default;
	}
	HFONT GetHFONT(const CString &id, HFONT Default = NULL, LPCTSTR lpszClassName = NULL)
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName);
		if (pGDIManager) {
			return pGDIManager->GetHFONT(id, Default);
		} 
		return Default;
	}
	COLORREF GetCOLORREF(const CString &id, COLORREF Default = CLR_INVALID, LPCTSTR lpszClassName = NULL)
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName);
		if (pGDIManager) {
			return pGDIManager->GetCOLORREF(id, Default);
		} 
		return Default;
	}
	BOOL GetRECT(const CString &id, LPRECT pRect, LPCTSTR lpszClassName = NULL)
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName);
		if (pGDIManager) {
			return pGDIManager->GetRECT(id, pRect);
		} 
		return FALSE;
	}
	LPCTSTR GetString(const CString &id, LPCTSTR Default = NULL, LPCTSTR lpszClassName = NULL)
	{ 
		UIStr2GdiManager* pGDIManager = FindGDIManager(lpszClassName);
		if (pGDIManager) {
			return pGDIManager->GetString(id, Default);
		} 
		return Default;
	}
};

//__declspec(selectany) UISkinManager* UISkinManager::ms_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////

class UISkinRes
{
public:
	UISkinRes()
	{

	}

	Image* GetImage(int nPartID, int nStateID) 
	{ 
		return NULL;
	}
	Image* GetImageEdge(int nPartID, int nStateID) 
	{ 
		return NULL;
	}
	HBITMAP GetHBITMAP(int nPartID, int nStateID) 
	{ 
		return NULL;
	}
	HBRUSH GetHBRUSH(int nPartID, int nStateID) 
	{ 
		return NULL;
	}
	HFONT GetHFONT(int nPartID, int nStateID)
	{ 
		return NULL;
	}
	COLORREF GetCOLORREF(int nPartID, int nStateID)
	{ 
		return CLR_INVALID;
	}
	UINT GetMaxStateID(int nPartID)
	{
		return 1;
	}
	BOOL IsStateIDHorizontal(int nPartID)
	{
		return TRUE;
	}
	BOOL GetContentMargin(int nPartID, int nStateID, LPRECT pRect)
	{
		ATLASSERT (pRect);
		memset(pRect, 0, sizeof(RECT));
		return TRUE;
	}
};

template<class T, class TBase = UISkinRes>
class UISkinResImpl : public TBase
{
public:

	HFONT GetHFONT(int nPartID, int nStateID)
	{ 
		T* pT = static_cast<T*>(this);
		return (HFONT)pT->SendMessage(WM_GETFONT, 0, 0);
		return NULL;
	}
};

//////////////////////////////////////////////////////////////////////////

#define HSKINTHEME	((HTHEME)-1)

class UISkinTheme : public UITheme
{
	typedef UISkinTheme This;
	typedef UITheme Base;
public:
	UISkinTheme()
	{

	}

	HTHEME OpenThemeData(HWND hWnd, LPCWSTR pszClassList)
	{
		//DirectUI的pszClassList=NULL
		if (pszClassList) {
			Base::OpenThemeData(hWnd, pszClassList);
		} else {
			m_hTheme = HSKINTHEME;
		}
		return m_hTheme;
	}
	
	HRESULT CloseThemeData(HWND hWnd = NULL)
	{
		if (HSKINTHEME != m_hTheme) {
			return Base::CloseThemeData();
		}
		return S_OK;
	}

	HRESULT DrawThemeBackground(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, LPCRECT pClipRect = NULL)
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::DrawThemeBackground(hDC, nPartID, nStateID, pRect, pClipRect);
	}

	HRESULT DrawThemeBackgroundEx(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, const DTBGOPTS* pOptions = NULL)
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::DrawThemeBackgroundEx(hDC, nPartID, nStateID, pRect, pOptions);
	}

	HRESULT DrawThemeText(HDC hDC, int nPartID, int nStateID, LPCTSTR pszText, int nCharCount, DWORD dwTextFlags, DWORD dwTextFlags2, LPCRECT pRect)
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		//::DrawText(hDC, pszText, nCharCount, (LPRECT)pRect, dwTextFlags);
		//return S_OK;
		return Base::DrawThemeText(hDC, nPartID, nStateID, pszText, nCharCount, dwTextFlags, dwTextFlags2, pRect);
	}

	HRESULT GetThemeBackgroundContentRect(HDC hDC, int nPartID, int nStateID,  LPCRECT pBoundingRect, LPRECT pContentRect) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeBackgroundContentRect(hDC, nPartID, nStateID,  pBoundingRect, pContentRect);
	}

	HRESULT GetThemeBackgroundExtent(HDC hDC, int nPartID, int nStateID, LPCRECT pContentRect, LPRECT pExtentRect) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeBackgroundExtent(hDC, nPartID, nStateID, pContentRect, pExtentRect);
	}

	HRESULT GetThemePartSize(HDC hDC, int nPartID, int nStateID, LPRECT pRect, enum THEMESIZE eSize, LPSIZE pSize) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemePartSize(hDC, nPartID, nStateID, pRect, eSize, pSize);
	}

	HRESULT GetThemeTextExtent(HDC hDC, int nPartID, int nStateID, LPCTSTR pszText, int nCharCount, DWORD dwTextFlags, LPCRECT  pBoundingRect, LPRECT pExtentRect) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		//return S_OK;
		return Base::GetThemeTextExtent(hDC, nPartID, nStateID, pszText, nCharCount, dwTextFlags, pBoundingRect, pExtentRect);
	}

	HRESULT GetThemeTextMetrics(HDC hDC, int nPartID, int nStateID, PTEXTMETRICW pTextMetric) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeTextMetrics(hDC, nPartID, nStateID, pTextMetric);
	}

	HRESULT GetThemeBackgroundRegion(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, HRGN* pRegion) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeBackgroundRegion(hDC, nPartID, nStateID, pRect, pRegion);
	}

	HRESULT HitTestThemeBackground(HDC hDC, int nPartID, int nStateID, DWORD dwOptions, LPCRECT pRect, HRGN hrgn, POINT ptTest, WORD* pwHitTestCode) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::HitTestThemeBackground(hDC, nPartID, nStateID, dwOptions, pRect, hrgn, ptTest, pwHitTestCode);
	}

	HRESULT DrawThemeEdge(HDC hDC, int nPartID, int nStateID, LPCRECT pDestRect, UINT uEdge, UINT uFlags, LPRECT pContentRect = NULL)
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::DrawThemeEdge(hDC, nPartID, nStateID, pDestRect, uEdge, uFlags, pContentRect);
	}

	HRESULT DrawThemeIcon(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, HIMAGELIST himl, int nImageIndex)
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::DrawThemeIcon(hDC, nPartID, nStateID, pRect, himl, nImageIndex);
	}

	BOOL IsThemePartDefined(int nPartID, int nStateID) const
	{
		if (m_hTheme==HSKINTHEME) {
			return FALSE;
		}
		return Base::IsThemePartDefined(nPartID, nStateID);
	}

	BOOL IsThemeBackgroundPartiallyTransparent(int nPartID, int nStateID) const
	{
		if (m_hTheme==HSKINTHEME) {
			return FALSE;
		}
		return Base::IsThemeBackgroundPartiallyTransparent(nPartID, nStateID);
	}

	HRESULT GetThemeColor(int nPartID, int nStateID, int nPropID, COLORREF* pColor) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeColor(nPartID, nStateID, nPropID, pColor);
	}

	HRESULT GetThemeMetric(HDC hDC, int nPartID, int nStateID, int nPropID, int* pnVal)
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeMetric(hDC, nPartID, nStateID, nPropID, pnVal);
	}

	HRESULT GetThemeString(int nPartID, int nStateID, int nPropID, LPTSTR pszBuff, int cchMaxBuffChars) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		//return S_OK;
		return Base::GetThemeString(nPartID, nStateID, nPropID, pszBuff, cchMaxBuffChars);
	}

	HRESULT GetThemeBool(int nPartID, int nStateID, int nPropID, BOOL* pfVal) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeBool(nPartID, nStateID, nPropID, pfVal);
	}

	HRESULT GetThemeInt(int nPartID, int nStateID, int nPropID, int* pnVal) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeInt(nPartID, nStateID, nPropID, pnVal);
	}

	HRESULT GetThemeEnumValue(int nPartID, int nStateID, int nPropID, int* pnVal) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeEnumValue(nPartID, nStateID, nPropID, pnVal);
	}

	HRESULT GetThemePosition(int nPartID, int nStateID, int nPropID, LPPOINT pPoint) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemePosition(nPartID, nStateID, nPropID, pPoint);
	}

	// deprecated
	HRESULT GetThemeFont(int nPartID, HDC hDC, int nStateID, int nPropID, LOGFONTW* pFont) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeFont(hDC, nPartID, nStateID, nPropID, pFont);
	}

	HRESULT GetThemeFont(HDC hDC, int nPartID, int nStateID, int nPropID, LOGFONTW* pFont) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeFont(hDC, nPartID, nStateID, nPropID, pFont);
	}

	HRESULT GetThemeRect(int nPartID, int nStateID, int nPropID, LPRECT pRect) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeRect(nPartID, nStateID, nPropID, pRect);
	}

	HRESULT GetThemeMargins(HDC hDC, int nPartID, int nStateID, int nPropID, LPRECT pRect, PMARGINS pMargins) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeMargins(hDC, nPartID, nStateID, nPropID, pRect, pMargins);
	}

	HRESULT GetThemeIntList(int nPartID, int nStateID, int nPropID, INTLIST* pIntList) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeIntList(nPartID, nStateID, nPropID, pIntList);
	}

	HRESULT GetThemePropertyOrigin(int nPartID, int nStateID, int nPropID, enum PROPERTYORIGIN* pOrigin) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemePropertyOrigin(nPartID, nStateID, nPropID, pOrigin);
	}

	HRESULT GetThemeFilename(int nPartID, int nStateID, int nPropID, LPTSTR pszThemeFileName, int cchMaxBuffChars) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		//return S_OK;
		return Base::GetThemeFilename(nPartID, nStateID, nPropID, pszThemeFileName, cchMaxBuffChars);
	}

	COLORREF GetThemeSysColor(int nColorID) const
	{
		if (m_hTheme==HSKINTHEME) {
			return ::GetSysColor(nColorID);
		}
		return Base::GetThemeSysColor(nColorID);
	}

	HBRUSH GetThemeSysColorBrush(int nColorID) const
	{
		if (m_hTheme==HSKINTHEME) {
			return ::GetSysColorBrush(nColorID);
		}
		return Base::GetThemeSysColorBrush(nColorID);
	}

	int GetThemeSysSize(int nSizeID) const
	{
		if (m_hTheme==HSKINTHEME) {
			return 0;
		}
		return Base::GetThemeSysSize(nSizeID);
	}

	BOOL GetThemeSysBool(int nBoolID) const
	{
		if (m_hTheme==HSKINTHEME) {
			return FALSE;
		}
		return Base::GetThemeSysBool(nBoolID);
	}

	HRESULT GetThemeSysFont(int nFontID, LOGFONTW* plf) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeSysFont(nFontID, plf);
	}

	HRESULT GetThemeSysString(int nStringID, LPTSTR pszStringBuff, int cchMaxStringChars) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		//return S_OK;
		return Base::GetThemeSysString(nStringID, pszStringBuff, cchMaxStringChars);
	}

	HRESULT GetThemeSysInt(int nIntID, int* pnValue) const
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeSysInt(nIntID, pnValue);
	}

#if (_WIN32_WINNT >= 0x0600)
	HRESULT GetThemeBitmap(int nPartID, int nStateID, int nPropID, ULONG uFlags, HBITMAP& hBitmap)
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
#if _MSC_VER <= 1200
		return Base::GetThemeBitmap(nPartID, nStateID, nPropID, uFlags, &hBitmap);
#else
		return Base::GetThemeBitmap(nPartID, nStateID, nPropID, uFlags, hBitmap);
#endif//
	}

	HRESULT GetThemeStream(int nPartID, int nStateID, int nPropID, VOID** ppvStream, DWORD* pcbStream, HINSTANCE hInstance)
	{
		if (m_hTheme==HSKINTHEME) {
			return S_FALSE;
		}
		return Base::GetThemeStream(nPartID, nStateID, nPropID, ppvStream, pcbStream, hInstance);
	}
#endif // (_WIN32_WINNT >= 0x0600)
};

template <class T, class TBase=UISkinTheme>
class UISkinThemeImpl : public UIThemeImpl<T,TBase>
{
	typedef UISkinThemeImpl<T,TBase> This;
	typedef UIThemeImpl<T,TBase> Base;
public:
	UISkinThemeImpl()
	{

	}
	~UISkinThemeImpl()
	{
		
	}

public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);
		//ATLASSERT(::IsWindow(pT->m_hWnd));
		//ATLASSERT(m_lpstrThemeClassList != NULL);
		//if(m_lpstrThemeClassList == NULL)
		//	return NULL;
		CloseThemeData();
		return TBase::OpenThemeData(pT->m_hWnd, m_lpstrThemeClassList);
		//return Base::OpenThemeData();
	}
	
	HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}

	HRESULT CloseThemeData()
	{
		T* pT = static_cast<T*>(this);
		return Base::CloseThemeData(pT->m_hWnd);
	}

	HRESULT DrawThemeBackground(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, LPCRECT pClipRect = NULL)
	{
		if (m_hTheme==HSKINTHEME) {
			T* pT = static_cast<T*>(this);
			Image* pImage = pT->GetImage(nPartID, nStateID);
			if (pImage) {
				Graphics graphics(hDC);
				graphics.DrawImage(pImage, pRect->left, pRect->top, pRect->right-pRect->left, pRect->bottom-pRect->top);
				return S_OK;
			}
			if (nStateID > 0) {
				pImage = pT->GetImage(nPartID, 0);
				if (pImage) {
					Graphics graphics(hDC);
					RectF destRect(pRect->left, pRect->top, pRect->right-pRect->left, pRect->bottom-pRect->top);
					if (pT->IsStateIDHorizontal(nPartID)) {
						REAL srcWidth = pImage->GetWidth()/pT->GetMaxStateID(nPartID);
						REAL srcHeight = pImage->GetHeight();
						REAL srcX = srcWidth*(nStateID-1);
						REAL srcY = 0;
						graphics.DrawImage(pImage, destRect, srcX, srcY, srcWidth, srcHeight, UnitPixel);
					} else {
						REAL srcWidth = pImage->GetWidth();
						REAL srcHeight = pImage->GetHeight()/pT->GetMaxStateID(nPartID);
						REAL srcX = 0;
						REAL srcY = srcWidth*(nStateID-1);
						graphics.DrawImage(pImage, destRect, srcX, srcY, srcWidth, srcHeight, UnitPixel);
					}
					return S_OK;
				}
			}
			//UIgdi::FillSolidRect(hDC, pRect, nPartID*100+nStateID);
		}
		return Base::DrawThemeBackground(hDC, nPartID, nStateID, pRect, pClipRect);
	}

	HRESULT DrawThemeBackgroundEx(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, const DTBGOPTS* pOptions = NULL)
	{
		if (m_hTheme==HSKINTHEME) {
			return DrawThemeBackground(hDC, nPartID, nStateID, pRect);
		}
		return Base::DrawThemeBackgroundEx(hDC, nPartID, nStateID, pRect, pOptions);
	}

	HRESULT DrawThemeText(HDC hDC, int nPartID, int nStateID, LPCTSTR pszText, int nCharCount, DWORD dwTextFlags, DWORD dwTextFlags2, LPCRECT pRect)
	{
		if (m_hTheme==HSKINTHEME) {
			T* pT = static_cast<T*>(this);
			COLORREF crText = pT->GetCOLORREF(nPartID, nStateID);
			HFONT hFont = pT->GetHFONT(nPartID, nStateID);
			UIgdi::DrawText(hDC, pszText, nCharCount, (LPRECT)pRect, dwTextFlags, crText, hFont);
			return S_OK;
		}
		return Base::DrawThemeText(hDC, nPartID, nStateID, pszText, nCharCount, dwTextFlags, dwTextFlags2, pRect);
	}

	HRESULT DrawThemeEdge(HDC hDC, int nPartID, int nStateID, LPCRECT pDestRect, UINT uEdge, UINT uFlags, LPRECT pContentRect = NULL)
	{
		if (m_hTheme==HSKINTHEME) {
			T* pT = static_cast<T*>(this);
			int x = 0, y = 0, nWidth = 0, nHeight = 0;
			Image* pImage = pT->GetImageEdge(nPartID, nStateID);
			if (nStateID > 0 && pImage == NULL) {
				pImage = pT->GetImageEdge(nPartID, 0);
				if (pImage) {
					if (pT->IsStateIDHorizontal(nPartID)) {
						nWidth = pImage->GetWidth()/pT->GetMaxStateID(nPartID);
						nHeight = pImage->GetHeight();
						x = nWidth * (nStateID-1);
					} else {
						nWidth = pImage->GetWidth();
						nHeight = pImage->GetHeight()/pT->GetMaxStateID(nPartID);
						y = nHeight * (nStateID-1);
					}
				}
			} else {
				if (pImage) {
					nWidth = pImage->GetWidth();
					nHeight = pImage->GetHeight();
				}
			}
			if (pImage) {
				int nWidthPerPice = nWidth/3;
				int nHeightPerPice = nHeight/3;
				Graphics graphics(hDC);
				
				if (uFlags & BF_LEFT|BF_TOP) {
					// 左上角
					graphics.DrawImage(pImage
						, RectF(pDestRect->left, pDestRect->top, nWidthPerPice, nHeightPerPice)
						, x, y, nWidthPerPice, nHeightPerPice, UnitPixel);
				}
				if (uFlags & BF_LEFT) {
					// 左中边框
					graphics.DrawImage(pImage
						, RectF(pDestRect->left, pDestRect->top+nHeightPerPice, nWidthPerPice, pDestRect->bottom-pDestRect->top-2*nHeightPerPice)
						, x, y+nHeightPerPice, nWidthPerPice, nHeightPerPice, UnitPixel);
				}
				if (uFlags & BF_LEFT|BF_BOTTOM) {
					// 左下角
					graphics.DrawImage(pImage
						, RectF(pDestRect->left, pDestRect->bottom - nHeightPerPice, nWidthPerPice, nHeightPerPice)
						, x, y+nHeight-nHeightPerPice, nWidthPerPice, nHeightPerPice, UnitPixel);
				}
				if (uFlags & BF_TOP) {
					// 上中边框
					graphics.DrawImage(pImage
						, RectF(pDestRect->left+nWidthPerPice, pDestRect->top, pDestRect->right-pDestRect->left-2*nWidthPerPice, nHeightPerPice)
						, x+nWidthPerPice, y, nWidthPerPice, nHeightPerPice, UnitPixel);
				}
				if (uFlags & BF_RIGHT|BF_TOP) {
					// 右上角
					graphics.DrawImage(pImage
						, RectF(pDestRect->right-nWidthPerPice, pDestRect->top, nWidthPerPice, nHeightPerPice)
						, x+nWidth-nWidthPerPice, y, nWidthPerPice, nHeightPerPice, UnitPixel);
				}
				if (uFlags & BF_RIGHT) {
					// 右中边框
					graphics.DrawImage(pImage
						, RectF(pDestRect->right-nWidthPerPice, pDestRect->top+nHeightPerPice, nWidthPerPice, pDestRect->bottom-pDestRect->top-2*nHeightPerPice)
						, x+nWidth-nWidthPerPice, y+nHeightPerPice, nWidthPerPice, nHeightPerPice, UnitPixel);
				}
				if (uFlags & BF_RIGHT|BF_BOTTOM) {
					// 右下角
					graphics.DrawImage(pImage
						, RectF(pDestRect->right-nWidthPerPice, pDestRect->bottom-nHeightPerPice, nWidthPerPice, nHeightPerPice)
						, x+nWidth-nWidthPerPice, y+nHeight-nHeightPerPice, nWidthPerPice, nHeightPerPice, UnitPixel);		
				}
				if (uFlags & BF_BOTTOM) {
					// 下中边框
					graphics.DrawImage(pImage
						, RectF(pDestRect->left+nWidthPerPice, pDestRect->bottom-nHeightPerPice, pDestRect->right-pDestRect->left-2*nWidthPerPice, nHeightPerPice)
						, x+nWidthPerPice, y+nHeight-nHeightPerPice, nWidthPerPice, nHeightPerPice, UnitPixel);	
				}
				if (uFlags & BF_MIDDLE) {
					// 中间
					graphics.DrawImage(pImage
						, RectF(pDestRect->left+nWidthPerPice, pDestRect->top+nHeightPerPice, pDestRect->right-pDestRect->left-2*nWidthPerPice, pDestRect->bottom-pDestRect->top-2*nHeightPerPice)
						, x+nWidthPerPice, y+nHeightPerPice, nWidthPerPice, nHeightPerPice, UnitPixel);
				}
				return S_OK;
			}
			return S_FALSE;
		} else {
			return Base::DrawThemeEdge(hDC, nPartID, nStateID, pDestRect, uEdge, uFlags, pContentRect);
		}
	}

	HRESULT DrawThemeIcon(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, HIMAGELIST himl, int nImageIndex)
	{
		if (m_hTheme==HSKINTHEME) {
			ImageList_Draw(himl, nImageIndex, hDC, pRect->left, pRect->top, ILD_NORMAL|ILD_TRANSPARENT);
		} else {
			return Base::DrawThemeIcon(hDC, nPartID, nStateID, pRect, himl, nImageIndex);
		}
		return S_OK;
	}

	HRESULT GetThemeBackgroundContentRect(HDC hDC, int nPartID, int nStateID,  LPCRECT pBoundingRect, LPRECT pContentRect)// const
	{
		if (m_hTheme==HSKINTHEME) {
			T* pT = static_cast<T*>(this);
			RECT rcOffset;
			if(pT->GetContentMargin(nPartID, nStateID, &rcOffset) || (nStateID > 0 && pT->GetContentMargin(nPartID, 0, &rcOffset))) {
				pContentRect->left = pBoundingRect->left + rcOffset.left;
				pContentRect->top = pBoundingRect->top + rcOffset.top;
				pContentRect->right = pBoundingRect->right - rcOffset.right;
				pContentRect->bottom = pBoundingRect->bottom - rcOffset.bottom;
			} else {
				*pContentRect = *pBoundingRect;
			}
			return S_OK;
		} else {
			return Base::GetThemeBackgroundContentRect(hDC, nPartID, nStateID, pBoundingRect, pContentRect);
		}
	}

	HRESULT GetThemeColor(int nPartID, int nStateID, int nPropID, COLORREF* pColor)// const
	{
		if (m_hTheme==HSKINTHEME) {
			T* pT = static_cast<T*>(this);
			*pColor = pT->GetCOLORREF(nPartID, nStateID);
			return S_OK;
		}
		return Base::GetThemeColor(nPartID, nStateID, nPropID, pColor);
	}

	HRESULT GetThemeMetric(HDC hDC, int nPartID, int nStateID, int nPropID, int* pnVal)
	{
		if (m_hTheme==HSKINTHEME) {
			T* pT = static_cast<T*>(this);
			Image* pImage = pT->GetImage(nPartID, nStateID);
			if (pImage) {
				switch(nPropID)
				{
				case TMT_HEIGHT:
					*pnVal = pImage->GetHeight();
					break;
				case  TMT_WIDTH:
					*pnVal = pImage->GetWidth();
					break;
				}
				return S_OK;
			} 
			if (nStateID > 0) {
				pImage = pT->GetImage(nPartID, 0);
				if (pImage) {
					switch(nPropID)
					{
					case TMT_HEIGHT:
						if(pT->IsStateIDHorizontal(nPartID)) {
							*pnVal = pImage->GetHeight();
						} else {
							*pnVal = pImage->GetHeight()/pT->GetMaxStateID(nPartID);
						}
						break;
					case  TMT_WIDTH:
						if(pT->IsStateIDHorizontal(nPartID)) {
							*pnVal = pImage->GetWidth()/pT->GetMaxStateID(nPartID);
						} else {
							*pnVal = pImage->GetWidth();
						}
						break;
					}
					return S_OK;
				} 
			}
		}
		return Base::GetThemeMetric(hDC, nPartID, nStateID, nPropID, pnVal);
	}
};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UISkinDrawMap : public UIPaintF<T>//, public UIBkgnd<T>
{
	typedef UISkinDrawMap<T> This;
	typedef UIPaintF<T> PaintMap;
public:

	BOOL IsTransparent()
	{
		return FALSE;
	}

	void Draw(HDC hdc)
	{
#ifdef _DEBUG
		T* pT = static_cast<T*>(this);
		CString strText;
		pT->GetWindowText(strText);
		WTL::CDCHandle dc(hdc);
		dc.SetBkMode(TRANSPARENT);
		CRect rc;
		pT->GetClientRect(rc);
		dc.FillSolidRect(&rc, RGB(rand()%255,rand()%255,rand()%255));
		dc.TextOut(5,5, strText);
#endif//
	}

	void Paint(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		CRect rcClient;
		pT->GetClientRect(&rcClient);
		::SetBkMode(hdc,TRANSPARENT);
		//if (!pT->PaintBkgnd(hdc,&rcClient)) {
		if(!pT->IsDirectUI()) {
			if (pT->IsTransparent()) {
#ifndef _AFX
				WTL::CDCHandle dc(hdc);
				CWindow wndParent = pT->GetParent();
				CPoint pt(0, 0);
				pT->MapWindowPoints(wndParent, &pt, 1);
				pt = dc.OffsetWindowOrg(pt.x, pt.y);
				LRESULT lResult = wndParent.SendMessage(WM_PAINT, (WPARAM)(HDC)dc, 0L);
				dc.SetWindowOrg(pt.x, pt.y);
#else
				CDC* pDC = CDC::FromHandle(hdc);
				CWnd* pParent = pT->GetParent();
				CPoint pt(0, 0);
				pT->MapWindowPoints(pParent, &pt, 1);
				pt = pDC->OffsetWindowOrg(pt.x, pt.y);
				LRESULT lResult = pParent->SendMessage(WM_PAINT, (WPARAM)pDC->GetSafeHdc(), 0L);
				pDC->SetWindowOrg(pt.x, pt.y);
#endif//
			}
		}
		//}
		pT->Draw(hdc);
	}

	void OnPaint(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		if (!pT->IsDirectUI()) {
			PaintMap::OnPaint(hdc);
		} else {
			pT->Paint(hdc);
		}
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(PaintMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
//WINDOW 
// WP_CAPTION						CS_ACTIVE, CS_DISABLED, CS_INACTIVE 
// WP_CAPTIONSIZINGTEMPLATE  
// WP_CLOSEBUTTON					CBS_DISABLED, CBS_HOT, CBS_NORMAL, CBS_PUSHED 
// WP_DIALOG  
// WP_FRAME							FS_ACTIVE, FS_INACTIVE 
// WP_FRAMEBOTTOM  
// WP_FRAMEBOTTOMSIZINGTEMPLATE  
// WP_FRAMELEFT  
// WP_FRAMELEFTSIZINGTEMPLATE  
// WP_FRAMERIGHT  
// WP_FRAMERIGHTSIZINGTEMPLATE  
// WP_HELPBUTTON					HBS_DISABLED, HBS_HOT, HBS_NORMAL, HBS_PUSHED 
// WP_HORZSCROLL					HSS_DISABLED, HSS_HOT, HSS_NORMAL, HSS_PUSHED 
// WP_HORZTHUMB						HTS_DISABLED, HTS_HOT, HTS_NORMAL, HTS_PUSHED 
// WP_MAXBUTTON						MAXBS_DISABLED, MAXBS_HOT, MAXBS_NORMAL, MAXBS_PUSHED 
// WP_MAXCAPTION					MXCS_ACTIVE, MXCS_DISABLED, MXCS_INACTIVE 
// WP_MDICLOSEBUTTON  
// WP_MDIHELPBUTTON  
// WP_MDIMINBUTTON  
// WP_MDIRESTOREBUTTON  
// WP_MDISYSBUTTON  
// WP_MINBUTTON						MINBS_DISABLED, MINBS_HOT, MINBS_NORMAL, MINBS_PUSHED 
// WP_MINCAPTION					MNCS_ACTIVE, MNCS_DISABLED, MNCS_INACTIVE 
// WP_RESTOREBUTTON					RBS_DISABLED, RBS_HOT, RBS_NORMAL, RBS_PUSHED 
// WP_SMALLCAPTION  
// WP_SMALLCAPTIONSIZINGTEMPLATE  
// WP_SMALLCLOSEBUTTON  
// WP_SMALLFRAMEBOTTOM  
// WP_SMALLFRAMEBOTTOMSIZINGTEMPLATE  
// WP_SMALLFRAMELEFT  
// WP_SMALLFRAMELEFTSIZINGTEMPLATE  
// WP_SMALLFRAMERIGHT  
// WP_SMALLFRAMERIGHTSIZINGTEMPLATE  
// WP_SMALLMAXCAPTION  
// WP_SMALLMINCAPTION  
// WP_SYSBUTTON						SBS_DISABLED, SBS_HOT, SBS_NORMAL, SBS_PUSHED 
// WP_VERTSCROLL					VSS_DISABLED, VSS_HOT, VSS_NORMAL, VSS_PUSHED 
// WP_VERTTHUMB						VTS_DISABLED, VTS_HOT, VTS_NORMAL, VTS_PUSHED 

typedef struct tagWindow_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[4];
	Image* pImage;
	Image* pStateImage[4];
}WINDOW_PARTSTATEINFO,*PWINDOW_PARTSTATEINFO;
typedef struct tagWindow_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	WINDOW_PARTSTATEINFO Part[38];
}WINDOW_MAXPARTSTATEINFO,*PWINDOW_MAXPARTSTATEINFO;

template<class T,class TBase = UISkinRes>
class UIWindowSkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UIWindowSkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
public:
	static WINDOW_MAXPARTSTATEINFO _MaxPartStateInfo;

public:
	Image* GetImage(int nPartID, int nStateID) 
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].pStateImage[nStateID-1];
		}
		return _MaxPartStateInfo.Part[nPartID-1].pImage;
	}
	UINT GetMaxStateID(int nPartID)
	{
		return 4;
		return 0;
	}
};
template<class T,class TBase>
__declspec(selectany) WINDOW_MAXPARTSTATEINFO UIWindowSkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{
		{
			_T("CAPTION")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLCAPTION")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{

			_T("MINCAPTION")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLMINCAPTION")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("MAXCAPTION")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLMAXCAPTION")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("FRAMELEFT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("FRAMERIGHT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("FRAMEBOTTOM")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLFRAMELEFT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLFRAMERIGHT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLFRAMEBOTTOM")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SYSBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("MDISYSBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("MINBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("WP_MDIMINBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("MAXBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("CLOSEBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLCLOSEBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("MDICLOSEBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("RESTOREBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("MDIRESTOREBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("HELPBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("MDIHELPBUTTON")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("HORZSCROLL")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("HORZTHUMB")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("VERTSCROLL")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("VERTTHUMB")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("DIALOG")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("CAPTIONSIZINGTEMPLATE")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLCAPTIONSIZINGTEMPLATE")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("FRAMELEFTSIZINGTEMPLATE")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLFRAMELEFTSIZINGTEMPLATE")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("FRAMERIGHTSIZINGTEMPLATE")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLFRAMERIGHTSIZINGTEMPLATE")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("FRAMEBOTTOMSIZINGTEMPLATE")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("SMALLFRAMEBOTTOMSIZINGTEMPLATE")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("WP_FRAME")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
				,{NULL,NULL,NULL,NULL}
		}
	}
};

template<class T>
class UIWindowSkinDrawMap : public UINcPaintF<T>
{
	typedef UIWindowSkinDrawMap<T> This;
	typedef UINcPaintF<T> PaintMap;
public:

	/*UINT GetPartID()
	{
		ASSERT(0);
		return 0;
	}*/

	UINT GetStateID()
	{
		T* pT = static_cast<T*>(this);
		UINT uStateID = 1;
		if (!pT->IsWindowEnabled()) {
			uStateID = 4;
		} else if (::GetActiveWindow()==*pT) {
			uStateID = 2;
		} else if (::GetFocus()==*pT) {
			uStateID = 2;
		}
		return uStateID;
	}

	void DrawNcBackgnd(HDC hdc, RECT & rect)
	{
		T* pT = static_cast<T*>(this);
		if(S_OK != pT->DrawThemeBackground(hdc, WP_DIALOG, GetStateID(), &rect)) {
			::DrawFrameControl(hdc, &rect, DFC_CAPTION, 0);
		}
	}

	void DrawNcCaption(HDC hdc, RECT & rect)
	{
		T* pT = static_cast<T*>(this);
		CRect rcIcon = rect;
		HICON hIcon = pT->GetIcon(FALSE);
		if (!hIcon) {
			hIcon = pT->GetIcon(TRUE);
		}
		if (hIcon) {
			//rcIcon.right = rcIcon.left + (rcIcon.Height()-16)/2;
			//rcIcon.top = (rcIcon.Height()-16)/2;
			//::DrawIconEx(hdc, rcIcon.left, rcIcon.top, hIcon, 16, 16, 0, NULL, 0);
		}
		CRect rcText = rect;
		rcText.left += rcText.Height();
		CString strText;
		pT->GetWindowText(strText);
		pT->DrawThemeText(hdc,
			WP_CAPTION, GetStateID(), strText, strText.GetLength(), DT_LEFT|DT_VCENTER, 0, &rcText);
	}

	INT  DrawNcButton(HDC hdc, HTBUTTON & button)
	{
		T* pT = static_cast<T*>(this);
		UINT nPartID = 0;
		UINT nStateID = 1;
		RECT rcButton = button.rc;
		switch(button.Command)
		{
		case SC_MINIMIZE:
			nPartID = WP_MINBUTTON;
			break;
		case SC_MAXIMIZE:
			nPartID = WP_MAXBUTTON;
			break;
		case SC_RESTORE:
			nPartID = WP_RESTOREBUTTON;
			break;
		case SC_CLOSE:
			nPartID = WP_CLOSEBUTTON;
			break;
		default:
			break;
		}
		if (button.State == HTBSTATE::Pushed) {
			nStateID = 3;
		} else if (button.State == HTBSTATE::Hover) {
			nStateID = 2;
		} else if (button.State == HTBSTATE::Disabled) {
			nStateID = 4;
		} else {
			nStateID = 1;
		}
		pT->DrawThemeBackground(hdc, nPartID, nStateID, &rcButton);
		return 1;
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(PaintMap)
	END_MSG_MAP()
};

template<class T, class TBase=UISkinTheme>
class UIWindowSkinThemeImpl : public UISkinThemeImpl<T,TBase>, public UIWindowSkinResImpl<T>
{
	typedef UIWindowSkinThemeImpl<T,TBase> This;
	typedef UISkinThemeImpl<T,TBase> Base;
public:
};

template<class T>
class UIWindowSkinMap 
	: public UIWindowSkinThemeImpl<T>
	, public UIWindowSkinDrawMap<T>
{
	typedef UIWindowSkinMap<T> This;
	typedef UIWindowSkinThemeImpl<T> SkinTheme;
	typedef UIWindowSkinDrawMap<T> SkinDrawMap;
public:

	BOOL OnNcPaint() 
	{
		return SkinDrawMap::OnNcPaint();
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
//#define DFCS_CAPTIONCLOSE       0x0000
//#define DFCS_CAPTIONMIN         0x0001
//#define DFCS_CAPTIONMAX         0x0002
//#define DFCS_CAPTIONRESTORE     0x0003
//#define DFCS_CAPTIONHELP        0x0004
//PART
enum
{
	SBP_CLOSE = 1,			//WP_CLOSEBUTTON
	SBP_MIN,				//WP_MINBUTTON
	SBP_MAX,				//WP_MAXBUTTON	
	SBP_RESTORE,			//WP_RESTOREBUTTON
	SBP_HELP,				//WP_HELPBUTTON
};
//STATE 和 PUSHBUTTON一样，只不过少了一个Default
//_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")

typedef struct tagSysButton_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[4];
	Image* pImage;
	Image* pStateImage[4];
}SYSBUTTON_PARTSTATEINFO,*PSYSBUTTON_PARTSTATEINFO;
typedef struct tagSysButton_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	SYSBUTTON_PARTSTATEINFO Part[5];
}SYSBUTTON_MAXPARTSTATEINFO,*PSYSBUTTON_MAXPARTSTATEINFO;

template<class T,class TBase = UISkinRes>
class UISysButtonSkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UISysButtonSkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
public:
	static SYSBUTTON_MAXPARTSTATEINFO _MaxPartStateInfo;
	
public:
	Image* GetImage(int nPartID, int nStateID) 
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].pStateImage[nStateID-1];
		}
		return _MaxPartStateInfo.Part[nPartID-1].pImage;
	}
	UINT GetMaxStateID(int nPartID)
	{
		return 4;
		return 0;
	}
};
template<class T,class TBase>
__declspec(selectany) SYSBUTTON_MAXPARTSTATEINFO UISysButtonSkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{
		{
			_T("CLOSE")
			,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
			,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("MIN")
			,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
			,{NULL,NULL,NULL,NULL}
		}
		,{
			
			_T("MAX")
			,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
			,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("RESTORE")
			,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
			,{NULL,NULL,NULL,NULL}
		}
		,{
			_T("HELP")
			,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED")}
			,NULL
			,{NULL,NULL,NULL,NULL}
		}
	}
};

template<class T>
class UISysButtonSkinDrawMap : public UISkinDrawMap<T>
{
public:

	BOOL IsTransparent()
	{
		return TRUE;
	}

	UINT GetPartID(LPCTSTR lpszPart)
	{
		UINT i,j;
		for (i = 0, j = _countof(T::_MaxPartStateInfo.Part); i < j; i++)
		{
			if (_tcsicmp(T::_MaxPartStateInfo.Part[i].pszName,lpszPart) == 0)
			{
				break;
			}
		}
		return i + 1;
	}

	UINT GetStateID()
	{
		T* pT = static_cast<T*>(this);
		UINT uStateID = 1;
		UINT uState = pT->GetState();
		if (!pT->IsWindowEnabled()) {
			uStateID = PBS_DISABLED;
		} else if (uState & BST_PUSHED) {
			uStateID = PBS_PRESSED;
		} else if (uState & BST_FOCUS) {
			uStateID = PBS_HOT;
		}
		return uStateID;
	}

	void Draw(HDC hdc)
	{
		T* pT = static_cast<T*>(this);

		DWORD dwStyle = pT->GetStyle();
		//DWORD dwExStyle = pT->GetExStyle();
		CString strText;
		pT->GetWindowText(strText);
		int nPartID = pT->GetPartID(strText);
		int nStateID = pT->GetStateID();
		//DWORD dwTextFlags = pT->GetTextFlags();
		
		RECT rcClient = {0};
		pT->GetClientRect(&rcClient);
		if(S_OK != pT->DrawThemeBackground(hdc, nPartID, nStateID, &rcClient)) {
			::DrawFrameControl(hdc, &rcClient, DFC_CAPTION, nPartID-1);
		}
	}
};

//////////////////////////////////////////////////////////////////////////
//STATIC

typedef struct tagStatic_PartStateInfo
{
	LPCTSTR pszName;
}STATIC_PARTSTATEINFO,*PSTATIC_PARTSTATEINFO;
typedef struct tagStatic_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	HFONT hFont;
	COLORREF crText;
}STATIC_MAXPARTSTATEINFO,*PSTATIC_MAXPARTSTATEINFO;

template<class T,class TBase = UISkinRes>
class UIStaticSkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UIStaticSkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
public:
	static STATIC_MAXPARTSTATEINFO _MaxPartStateInfo;
protected:
	Image* m_pImage;

public:
	UIStaticSkinResImpl()
	{
		m_pImage = NULL;
	}

	Image* GetImage(int nPartID, int nStateID) 
	{ 
		return m_pImage;
	}
	HFONT GetHFONT(int nPartID, int nStateID)
	{ 
		HFONT hFont = NULL;
		if (!hFont) {
			hFont = Base::GetHFONT(nPartID,nStateID);
		}
		if (!hFont) {
			hFont = _MaxPartStateInfo.hFont;
		}
		return hFont;
	}
	COLORREF GetCOLORREF(int nPartID, int nStateID)
	{ 
		return _MaxPartStateInfo.crText;
	}
	UINT GetMaxStateID(int nPartID)
	{
		return 0;
	}
};
template<class T,class TBase>
__declspec(selectany) STATIC_MAXPARTSTATEINFO UIStaticSkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,NULL
	,CLR_INVALID
};

template<class T>
class UIStaticSkinDrawMap : public UISkinDrawMap<T>
{
public:

	BOOL IsTransparent()
	{
		return TRUE;
	}

	UINT GetPartID() 
	{
		T* pT = static_cast<T*>(this);
		return 1;
	}
	UINT GetStateID()
	{
		return 0;
	}
	DWORD GetTextFlags()
	{
		T* pT = static_cast<T*>(this);
		DWORD dwTextFlags = 0;
		DWORD dwStyle = pT->GetStyle();
		if (dwStyle & SS_CENTER) {
			dwTextFlags |= DT_CENTER;
		} else if (dwStyle & SS_RIGHT) {
			dwTextFlags |= DT_RIGHT;
		} else {
			dwTextFlags |= DT_LEFT;
		}
		if (dwStyle & SS_SIMPLE) {
			dwTextFlags |= DT_SINGLELINE;
		} else {
			dwTextFlags |= DT_WORDBREAK;
		}
		if (dwStyle & SS_ENDELLIPSIS) {
			dwTextFlags |= DT_END_ELLIPSIS;
		}
		if (dwStyle & SS_PATHELLIPSIS) {
			dwTextFlags |= DT_PATH_ELLIPSIS;
		}
		if (dwStyle & SS_WORDELLIPSIS) {
			dwTextFlags |= DT_WORD_ELLIPSIS;
		}
		dwTextFlags |= DT_NOPREFIX;
		return dwTextFlags;
	}

	void Draw(HDC hdc)
	{
		T* pT = static_cast<T*>(this);

		DWORD dwStyle = pT->GetStyle();
		//DWORD dwExStyle = pT->GetExStyle();
		int nPartID = pT->GetPartID();
		int nStateID = pT->GetStateID();
		DWORD dwTextFlags = pT->GetTextFlags();

		RECT rcClient = {0};
		pT->GetClientRect(&rcClient);
		
		pT->DrawThemeBackground(hdc, nPartID, nStateID, &rcClient);

		pT->DrawThemeEdge(hdc, nPartID, nStateID, &rcClient, 0, BF_RECT);

		if(dwStyle&SS_BITMAP) {
			HBITMAP hBitmap = pT->GetBitmap();
			if (hBitmap) {
				UIgdi::DrawBitmap(hdc, rcClient.left, 
					rcClient.top, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top, hBitmap, 0, 0);
			}
		} else if(dwStyle&SS_ICON) {
			HICON hIcon = pT->GetIcon();
			if (hIcon) {
				DrawIcon(hdc, rcClient.left, rcClient.top, hIcon);
			}
			HCURSOR hCursor = pT->GetCursor();
			if (hCursor) {
				DrawIcon(hdc, rcClient.left, rcClient.top, (HICON)hCursor);
			}
		} else if(dwStyle&SS_ENHMETAFILE) {
			HENHMETAFILE hmf = pT->GetEnhMetaFile();
			if(hmf) {
				PlayEnhMetaFile(hdc, hmf, &rcClient);
			}
		} else {
			//
		}
		
		CString strText;
		pT->GetWindowText(strText);
		if (!strText.IsEmpty()) {
			RECT rcText = {0};
			pT->GetThemeBackgroundContentRect(hdc, nPartID, nStateID, &rcClient, &rcText);
			pT->DrawThemeText(hdc,
				nPartID, nStateID, strText, strText.GetLength(), dwTextFlags, 0, &rcText);
		}
	}
};


//////////////////////////////////////////////////////////////////////////
//Button Control 
//Part IDs			State Ids
// BP_PUSHBUTTON	PBS_NORMAL 
// 					PBS_HOT
// 					PBS_PRESSED
// 					PBS_DISABLED 
// 					PBS_DEFAULTED 
// BP_GROUPBOX		GBS_NORMAL 
//					GBS_DISABLED
// BP_RADIOBUTTON	RBS_UNCHECKEDNORMAL 
// 					RBS_UNCHECKEDHOT 
// 					RBS_UNCHECKEDPRESSED 
// 					RBS_UNCHECKEDDISABLED 
// 					RBS_CHECKEDNORMAL 
// 					RBS_CHECKEDHOT 
// 					RBS_CHECKEDPRESSED 
// 					RBS_CHECKEDDISABLED 
// BP_CHECKBOX		CBS_UNCHECKEDNORMAL 
// 					CBS_UNCHECKEDHOT 
// 					CBS_UNCHECKEDPRESSED 
// 					CBS_UNCHECKEDDISABLED 
// 					CBS_CHECKEDNORMAL 
// 					CBS_CHECKEDHOT 
// 					CBS_CHECKEDPRESSED 
// 					CBS_CHECKEDDISABLED 
// 					CBS_MIXEDNORMAL 
// 					CBS_MIXEDHOT 
// 					CBS_MIXEDPRESSED 
// 					CBS_MIXEDDISABLED 

typedef struct tagButton_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[12];
	Image* pImage;
	Image* pStateImage[12];
	HFONT  hFont;
	HFONT  hStateFont[12];
	COLORREF crText;
	COLORREF crStateText[12];
}BUTTON_PARTSTATEINFO,*PBUTTON_PARTSTATEINFO;
typedef struct tagButton_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	BUTTON_PARTSTATEINFO Part[4];
}BUTTON_MAXPARTSTATEINFO,*PBUTTON_MAXPARTSTATEINFO;

template<class T,class TBase = UISkinRes>
class UIButtonSkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UIButtonSkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
public:
	static BUTTON_MAXPARTSTATEINFO _MaxPartStateInfo;
protected:
	BUTTON_PARTSTATEINFO m_PartStateInfo;
	
public:
	UIButtonSkinResImpl()
	{
		memset(&m_PartStateInfo, 0, sizeof(m_PartStateInfo));
	}

	Image* GetImage(int nPartID, int nStateID) 
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			if (m_PartStateInfo.pStateImage[nStateID-1]) {
				return m_PartStateInfo.pStateImage[nStateID-1];
			}
			return _MaxPartStateInfo.Part[nPartID-1].pStateImage[nStateID-1];
		}
		if (m_PartStateInfo.pImage) {
			return m_PartStateInfo.pImage;
		}
		return _MaxPartStateInfo.Part[nPartID-1].pImage;
	}
	HFONT GetHFONT(int nPartID, int nStateID)
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			if (m_PartStateInfo.hStateFont[nStateID-1]) {
				return m_PartStateInfo.hStateFont[nStateID-1];
			}
			return _MaxPartStateInfo.Part[nPartID-1].hStateFont[nStateID-1];
		}
		HFONT hFont = NULL;
		if (m_PartStateInfo.hFont) {
			hFont = m_PartStateInfo.hFont;
		}
		if (!hFont) {
			hFont = _MaxPartStateInfo.Part[nPartID-1].hFont;
		}
		return hFont;
	}
	COLORREF GetCOLORREF(int nPartID, int nStateID)
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			if (m_PartStateInfo.crStateText[nStateID-1]!=CLR_INVALID) {
				return m_PartStateInfo.crStateText[nStateID-1];
			}
			return _MaxPartStateInfo.Part[nPartID-1].crStateText[nStateID-1];
		}
		if (m_PartStateInfo.crText!=CLR_INVALID) {
			return m_PartStateInfo.crText;
		}
		return _MaxPartStateInfo.Part[nPartID-1].crText;
	}
	UINT GetMaxStateID(int nPartID)
	{
		switch(nPartID)
		{
		case BP_CHECKBOX:
			{ 
				return 12;
			}
			break;
		case BP_RADIOBUTTON:
			{ 
				return 8;
			}
			break;
		case BP_GROUPBOX:
			{ 
				return 2;
			}
			break;
		case BP_PUSHBUTTON:
			{ 
				return 5;
			}
			break;
		}
		return 0;
	}
};
template<class T,class TBase>
__declspec(selectany) BUTTON_MAXPARTSTATEINFO UIButtonSkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{
		{
			_T("BUTTON")
			,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED"),_T("DEFAULTED"),NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("RADIOBOX")
			,{_T("UNCHECKEDNORMAL"),_T("UNCHECKEDHOT"),_T("UNCHECKEDPRESSED"),_T("UNCHECKEDDISABLED"),_T("CHECKEDNORMAL"),_T("CHECKEDHOT"),_T("CHECKEDPRESSED"),_T("CHECKEDDISABLED"),NULL,NULL,NULL,NULL}
			,NULL
			,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("CHECKBOX")
			,{_T("UNCHECKEDNORMAL"),_T("UNCHECKEDHOT"),_T("UNCHECKEDPRESSED"),_T("UNCHECKEDDISABLED"),_T("CHECKEDNORMAL"),_T("CHECKEDHOT"),_T("CHECKEDPRESSED"),_T("CHECKEDDISABLED"),_T("MIXEDNORMAL"),_T("MIXEDHOT"),_T("MIXEDPRESSED"),_T("MIXEDDISABLED")}
			,NULL
			,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("GROUPBOX")
			,{_T("NORMAL"),_T("DISABLED"),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
			,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
	}
};


template<class T>
class UIButtonSkinDrawMap : public UISkinDrawMap<T>
{
public:

	BOOL IsTransparent()
	{
		return TRUE;
	}

	UINT GetPartID() 
	{
		T* pT = static_cast<T*>(this);
		DWORD dwStyle = pT->GetStyle();
		if((dwStyle&BS_CHECKBOX)==BS_CHECKBOX
			|| (dwStyle&BS_AUTOCHECKBOX)==BS_AUTOCHECKBOX) {
			return BP_CHECKBOX;
		} else if((dwStyle&BS_RADIOBUTTON)==BS_RADIOBUTTON) {
			return BP_RADIOBUTTON;
		} else if((dwStyle&BS_GROUPBOX)==BS_GROUPBOX) {
			return BP_GROUPBOX;
		} else {
			return BP_PUSHBUTTON;
		}
	}

	UINT GetStateID()
	{
		T* pT = static_cast<T*>(this);
		UINT uStateID = 1;
		UINT uState = pT->GetState();
		switch(pT->GetPartID())
		{
		case BP_CHECKBOX:
			{ 
				if (!pT->IsWindowEnabled()) {
					if (uState & BST_CHECKED) {
						uStateID = CBS_CHECKEDDISABLED;
					} else if(uState & BST_INDETERMINATE) {
						uStateID = CBS_MIXEDDISABLED;
					} else {
						uStateID = CBS_UNCHECKEDDISABLED;
					}
				} else if (uState & BST_PUSHED) {
					if (uState & BST_CHECKED) {
						uStateID = CBS_CHECKEDPRESSED;
					} else if(uState & BST_INDETERMINATE) {
						uStateID = CBS_MIXEDPRESSED;
					} else {
						uStateID = CBS_UNCHECKEDPRESSED;
					}
				} else if (uState & BST_FOCUS) {
					if (uState & BST_CHECKED) {
						uStateID = CBS_CHECKEDHOT;
					} else if(uState & BST_INDETERMINATE) {
						uStateID = CBS_MIXEDHOT;
					} else {
						uStateID = CBS_UNCHECKEDHOT;
					}
				} else {
					if (uState & BST_CHECKED) {
						uStateID = CBS_CHECKEDNORMAL;
					} else if(uState & BST_INDETERMINATE) {
						uStateID = CBS_MIXEDNORMAL;
					} else {
						uStateID = CBS_UNCHECKEDNORMAL;
					}
				}
			}
			break;
		case BP_RADIOBUTTON:
			{ 
				if (!pT->IsWindowEnabled()) {
					if (uState & BST_CHECKED) {
						uStateID = RBS_CHECKEDDISABLED;
					} else {
						uStateID = RBS_UNCHECKEDDISABLED;
					}
				} else if (uState & BST_PUSHED) {
					if (uState & BST_CHECKED) {
						uStateID = RBS_CHECKEDPRESSED;
					} else {
						uStateID = RBS_UNCHECKEDPRESSED;
					}
				} else if (uState & BST_FOCUS) {
					if (uState & BST_CHECKED) {
						uStateID = RBS_CHECKEDHOT;
					} else {
						uStateID = RBS_UNCHECKEDHOT;
					}
				} else {
					if (uState & BST_CHECKED) {
						uStateID = RBS_CHECKEDNORMAL;
					} else {
						uStateID = RBS_UNCHECKEDNORMAL;
					}
				}
			}
			break;
		case BP_GROUPBOX:
			{ 
				if (!pT->IsWindowEnabled()) {
					uStateID = GBS_DISABLED;
				}
			}
			break;
		case BP_PUSHBUTTON:
			{ 
				if (!pT->IsWindowEnabled()) {
					uStateID = PBS_DISABLED;
				} else if (uState & BST_PUSHED) {
					uStateID = PBS_PRESSED;
				} else if (uState & BST_FOCUS) {
					uStateID = PBS_HOT;
				}
			}
			break;
		default:
			ATLASSERT(0);
			break;
		}
		return uStateID;
	}

	DWORD GetTextFlags()
	{
		T* pT = static_cast<T*>(this);
		DWORD dwTextFlags = 0;
		DWORD dwStyle = pT->GetStyle();
		if (dwStyle & BS_LEFT) {
			dwTextFlags |= DT_LEFT;
		} else if (dwStyle & BS_RIGHT) {
			dwTextFlags |= DT_RIGHT;
		} else {
			dwTextFlags |= DT_CENTER;
		}
		if (dwStyle & BS_TOP) {
			dwTextFlags |= DT_TOP;
		} else if (dwStyle & BS_BOTTOM) {
			dwTextFlags |= DT_BOTTOM;
		} else {
			dwTextFlags |= DT_VCENTER;
		}
		if (dwStyle & BS_MULTILINE) {
			dwTextFlags |= DT_WORDBREAK;
		} else {
			dwTextFlags |= DT_SINGLELINE;
		}
		dwTextFlags |= DT_NOPREFIX;
		return dwTextFlags;
	}

	void Draw(HDC hdc)
	{
		T* pT = static_cast<T*>(this);

		DWORD dwStyle = pT->GetStyle();
		//DWORD dwExStyle = pT->GetExStyle();
		int nPartID = pT->GetPartID();
		int nStateID = pT->GetStateID();
		DWORD dwTextFlags = pT->GetTextFlags();
		
		RECT rcClient = {0};
		pT->GetClientRect(&rcClient);
		if (dwStyle & (BS_CHECKBOX|BS_RADIOBUTTON)) {
			int nMetric = 15;
			pT->GetThemeMetric(hdc, nPartID, nStateID, TMT_HEIGHT, &nMetric);
			RECT rcBox = { rcClient.left
				, rcClient.top + ((rcClient.bottom-rcClient.top)-nMetric)/2
				, 0
				, 0
			};
			rcBox.right = rcBox.left + nMetric;
			rcBox.bottom = rcBox.top + nMetric;
			pT->DrawThemeBackground(hdc, nPartID, nStateID, &rcBox);
			
			CString strText;
			pT->GetWindowText(strText);
			RECT rcText = { rcBox.right + nMetric/3, rcClient.top, rcClient.right, rcClient.bottom };
			pT->DrawThemeText(hdc,
				nPartID, nStateID, strText, strText.GetLength(), dwTextFlags & ~(DT_CENTER|DT_RIGHT), 0, &rcText);
		} else {
			pT->DrawThemeBackground(hdc, nPartID, nStateID, &rcClient);
			
			CString strText;
			pT->GetWindowText(strText);
			RECT rcText = {0};
			pT->GetThemeBackgroundContentRect(hdc, nPartID, nStateID, &rcClient, &rcText);
			pT->DrawThemeText(hdc,
				nPartID, nStateID, strText, strText.GetLength(), dwTextFlags, 0, &rcText);
		}
	}
};

template<class T, class TBase=UISkinTheme>
class UIButtonSkinThemeImpl : public UISkinThemeImpl<T,TBase>, public UIButtonSkinResImpl<T>
{
	typedef UIButtonSkinThemeImpl<T,TBase> This;
	typedef UISkinThemeImpl<T,TBase> Base;
public:
};

template<class T>
class UIButtonSkinMap 
	: public UIButtonSkinThemeImpl<T>
	, public UIButtonSkinDrawMap<T>
{
	typedef UIButtonSkinMap<T> This;
	typedef UIButtonSkinThemeImpl<T> SkinTheme;
	typedef UIButtonSkinDrawMap<T> SkinDrawMap;
public:

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};


//////////////////////////////////////////////////////////////////////////
//PROGRESS

//PROGRESS	PP_BAR  
//			PP_BARVERT  
//			PP_CHUNK  
//			PP_CHUNKVERT  
//			PP_FILL					PBFS_ERROR, PBFS_NORMAL, PBFS_PARTIAL, PBFS_PAUSED 
//			PP_FILLVERT				PBFVS_ERROR, PBFVS_NORMAL, PBFVS_PARTIAL, PBFVS_PAUSED 
//			PP_MOVEOVERLAY  
//			PP_MOVEOVERLAYVERT  
//			PP_PULSEOVERLAY  
//			PP_PULSEOVERLAYVERT  
//			PP_TRANSPARENTBAR		PBBS_NORMAL, PBBS_PARTIAL 
//			PP_TRANSPARENTBARVERT	PBBVS_NORMAL, PBBVS_PARTIAL 

typedef struct tagProgressBarCtrl_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[2];
	Image* pStateImage[2];
	COLORREF crStateColor[2];
}PROGRESSBARCTRL_PARTSTATEINFO,*PPROGRESSBARCTRL_PARTSTATEINFO;
typedef struct tagProgressBarCtrl_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	PROGRESSBARCTRL_PARTSTATEINFO Part[12];
}PROGRESSBARCTRL_MAXPARTSTATEINFO,*PPROGRESSBARCTRL_MAXPARTSTATEINFO;

template<class T, class TBase=UISkinRes>
class UIProgressBarCtrlSkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UIProgressBarCtrlSkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
protected:
	static PROGRESSBARCTRL_MAXPARTSTATEINFO _MaxPartStateInfo;

public:
	Image* GetImage(int nPartID, int nStateID) 
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].pStateImage[nStateID-1];
		}
		return NULL;
	}
	
	COLORREF GetCOLORREF(int nPartID, int nStateID)
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].crStateColor[nStateID-1];
		}
		return CLR_INVALID;
	}
	UINT GetMaxStateID(int nPartID)
	{
		return 2;
	}
};
template<class T,class TBase>
__declspec(selectany) PROGRESSBARCTRL_MAXPARTSTATEINFO UIProgressBarCtrlSkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{
		{
			_T("BAR")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("BARVERT")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("CHUNK")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("CHUNKVERT")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("FILL")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("FILLVERT")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("MOVEOVERLAY")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("MOVEOVERLAYVERT")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("PULSEOVERLAY")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("PULSEOVERLAYVERT")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("TRANSPARENTBAR")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("TRANSPARENTBARVERT")
			,{_T("NORMAL"),_T("PARTIAL")}
			,{NULL,NULL}
			,{CLR_INVALID,CLR_INVALID}
		}
	}
};

template<class T>
class UIProgressBarCtrlSkinDrawMap : public UISkinDrawMap<T>
{
public:
	UINT GetPartID() 
	{
		return 0;
	}
	UINT GetStateID()
	{
		return 0;
	}
	DWORD GetTextFlags()
	{
		return 0;
	}

	void Draw(HDC hdc)
	{
		/*T* pT = static_cast<T*>(this);

		DWORD dwStyle = pT->GetStyle();
		//DWORD dwExStyle = pT->GetExStyle();
		BOOL bVertical = dwStyle & PBS_VERTICAL;
		int nPos = pT->GetPos();
		int nMinRange = 0, nMaxRange = 0;
		pT->GetRange(nMinRange,nMaxRange);

		double nPercent = nPos/((double)(nMaxRange-nMinRange));

		RECT rcClient = {0};
		pT->GetClientRect(&rcClient);
		int nWidth = rcClient.right - rcClient.left;
		int nHeight = rcClient.bottom - rcClient.top;
		if (bVertical) {
			pT->DrawThemeBackground(hdc, PP_BARVERT, PBBS_NORMAL, &rcClient);
			RECT rcFill, rcTransparent;
			rcFill = rcTransparent = rcClient;
			rcFill.top = rcFill.bottom - nWidth*nPercent;
			rcTransparent.bottom = rcFill.top;
			pT->DrawThemeBackground(hdc, (dwStyle & PBS_SMOOTH) ? PP_FILLVERT : PP_CHUNKVERT, PBBS_NORMAL, &rcFill);
			pT->DrawThemeBackground(hdc, PP_TRANSPARENTBARVERT, PBBS_NORMAL, &rcTransparent);
		} else {
			pT->DrawThemeBackground(hdc, PP_BAR, PBBS_NORMAL, &rcClient);
			RECT rcFill, rcTransparent;
			rcFill = rcTransparent = rcClient;
			rcFill.right = rcFill.left + nWidth*nPercent;
			rcTransparent.left = rcFill.right;
			pT->DrawThemeBackground(hdc, (dwStyle & PBS_SMOOTH) ? PP_FILL : PP_CHUNK, PBBS_NORMAL, &rcFill);
			pT->DrawThemeBackground(hdc, PP_TRANSPARENTBAR, PBBS_NORMAL, &rcTransparent);
		}*/
	}
};

//////////////////////////////////////////////////////////////////////////
//Tab Control 
//Part IDs			
//enum TABPARTS {
//	TABP_TABITEM = 1,
//	TABP_TABITEMLEFTEDGE = 2,
//	TABP_TABITEMRIGHTEDGE = 3,
//	TABP_TABITEMBOTHEDGE = 4,
//	TABP_TOPTABITEM = 5,
//	TABP_TOPTABITEMLEFTEDGE = 6,
//	TABP_TOPTABITEMRIGHTEDGE = 7,
//	TABP_TOPTABITEMBOTHEDGE = 8,
//	TABP_PANE = 9,
//	TABP_BODY = 10,
//	TABP_AEROWIZARDBODY = 11,
//};
//State Ids
//enum TABITEMSTATES {
//	TIS_NORMAL = 1,
//	TIS_HOT = 2,
//	TIS_SELECTED = 3,
//	TIS_DISABLED = 4,
//	TIS_FOCUSED = 5,
//};
//enum TABITEMLEFTEDGESTATES {
//	TILES_NORMAL = 1,
//	TILES_HOT = 2,
//	TILES_SELECTED = 3,
//	TILES_DISABLED = 4,
//	TILES_FOCUSED = 5,
//};
//enum TABITEMRIGHTEDGESTATES {
//	TIRES_NORMAL = 1,
//	TIRES_HOT = 2,
//	TIRES_SELECTED = 3,
//	TIRES_DISABLED = 4,
//	TIRES_FOCUSED = 5,
//};
//enum TABITEMBOTHEDGESTATES {
//	TIBES_NORMAL = 1,
//	TIBES_HOT = 2,
//	TIBES_SELECTED = 3,
//	TIBES_DISABLED = 4,
//	TIBES_FOCUSED = 5,
//};
//enum TOPTABITEMSTATES {
//	TTIS_NORMAL = 1,
//	TTIS_HOT = 2,
//	TTIS_SELECTED = 3,
//	TTIS_DISABLED = 4,
//	TTIS_FOCUSED = 5,
//};
//enum TOPTABITEMLEFTEDGESTATES {
//	TTILES_NORMAL = 1,
//	TTILES_HOT = 2,
//	TTILES_SELECTED = 3,
//	TTILES_DISABLED = 4,
//	TTILES_FOCUSED = 5,
//};
//enum TOPTABITEMRIGHTEDGESTATES {
//	TTIRES_NORMAL = 1,
//	TTIRES_HOT = 2,
//	TTIRES_SELECTED = 3,
//	TTIRES_DISABLED = 4,
//	TTIRES_FOCUSED = 5,
//};
//enum TOPTABITEMBOTHEDGESTATES {
//	TTIBES_NORMAL = 1,
//	TTIBES_HOT = 2,
//	TTIBES_SELECTED = 3,
//	TTIBES_DISABLED = 4,
//	TTIBES_FOCUSED = 5,
//};


typedef struct tagTabCtrl_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[5];
	Image* pImage;
	Image* pStateImage[5];
	HFONT  hFont;
	HFONT  hStateFont[5];
	COLORREF crText;
	COLORREF crStateText[5];
}TABCTRL_PARTSTATEINFO,*PTABCTRL_PARTSTATEINFO;
typedef struct tagTabCtrl_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	TABCTRL_PARTSTATEINFO Part[11];
}TABCTRL_MAXPARTSTATEINFO,*PTABCTRL_MAXPARTSTATEINFO;

template<class T,class TBase = UISkinRes>
class UITabCtrlSkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UITabCtrlSkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
public:
	static TABCTRL_MAXPARTSTATEINFO _MaxPartStateInfo;

public:
	Image* GetImage(int nPartID, int nStateID) 
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].pStateImage[nStateID-1];
		}
		return _MaxPartStateInfo.Part[nPartID-1].pImage;
	}
	HFONT GetHFONT(int nPartID, int nStateID)
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].hStateFont[nStateID-1];
		}
		HFONT hFont = _MaxPartStateInfo.Part[nPartID-1].hFont;
		return hFont;
	}
	COLORREF GetCOLORREF(int nPartID, int nStateID)
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].crStateText[nStateID-1];
		}
		return _MaxPartStateInfo.Part[nPartID-1].crText;
	}
	UINT GetMaxStateID(int nPartID)
	{
		return 5;
	}
};
template<class T,class TBase>
__declspec(selectany) TABCTRL_MAXPARTSTATEINFO UITabCtrlSkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{
		{
			_T("TABITEM")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("TABITEMLEFTEDGE")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("TABITEMRIGHTEDGE")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("TABITEMBOTHEDGE")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("TOPTABITEM")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("TOPTABITEMLEFTEDGE")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("TOPTABITEMRIGHTEDGE")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("TOPTABITEMBOTHEDGE")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("PANE")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("BODY")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("AEROWIZARDBODY")
				,{_T("NORMAL"),_T("HOT"),_T("SELECTED"),_T("DISABLED"),_T("FOCUSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
	}
};


template<class T>
class UITabCtrlSkinDrawMap : public UISkinDrawMap<T>
{
public:
	UINT GetPartID() 
	{
		ATLASSERT(0);
		return 0;
	}

	UINT GetStateID()
	{
		T* pT = static_cast<T*>(this);
		UINT uStateID = 1;
		if (!pT->IsWindowEnabled()) {
			uStateID = 4;
		}
		return uStateID;
	}

	DWORD GetTextFlags()
	{
		T* pT = static_cast<T*>(this);
		DWORD dwTextFlags = 0;
		DWORD dwStyle = pT->GetStyle();
		
		dwTextFlags |= DT_CENTER;

		dwTextFlags |= DT_VCENTER;
	
		if (dwStyle & TCS_MULTILINE) {
			dwTextFlags |= DT_WORDBREAK;
		} else {
			dwTextFlags |= DT_SINGLELINE;
		}

		dwTextFlags |= DT_NOPREFIX;

		return dwTextFlags;
	}

	void Draw(HDC hdc)
	{
		T* pT = static_cast<T*>(this);

		DWORD dwStyle = pT->GetStyle();
		//DWORD dwExStyle = pT->GetExStyle();
		DWORD dwTextFlags = pT->GetTextFlags();

		HIMAGELIST hImageList = pT->GetImageList();
		int nCount	= pT->GetItemCount();
		int nFocus	= pT->GetCurFocus();
		int nCurSel = pT->GetCurSel();

		RECT rcClient = {0};
		pT->GetClientRect(&rcClient);
		//	TABP_TABITEM = 1,
		//	TABP_TABITEMLEFTEDGE = 2,
		//	TABP_TABITEMRIGHTEDGE = 3,
		//	TABP_TABITEMBOTHEDGE = 4,
		//	TABP_TOPTABITEM = 5,
		//	TABP_TOPTABITEMLEFTEDGE = 6,
		//	TABP_TOPTABITEMRIGHTEDGE = 7,
		//	TABP_TOPTABITEMBOTHEDGE = 8,
		//	TABP_PANE = 9,
		//	TABP_BODY = 10,
		//	TABP_AEROWIZARDBODY = 11,
		//pT->DrawThemeBackground(hdc, TABP_AEROWIZARDBODY, pT->GetStateID(), &rcClient);
		pT->DrawThemeBackground(hdc, TABP_BODY, pT->GetStateID(), &rcClient);
		pT->DrawThemeBackground(hdc, TABP_PANE, pT->GetStateID(), &rcClient);
		while (nCount--) {
			TCHAR szText[MAX_PATH] = {0};
			TCITEM tcItem = {0};
			tcItem.mask = TCIF_IMAGE|TCIF_STATE|TCIF_TEXT;
			tcItem.pszText = szText;
			tcItem.cchTextMax = MAX_PATH;
			pT->GetItem(nCount, &tcItem);
			RECT rcItem;
			pT->GetItemRect(nCount, &rcItem);
			if (RectVisible(hdc, &rcItem)) {
				int nPartID = TABP_TABITEM;
				int nStateID = TIS_NORMAL;
				if(dwStyle & TCS_VERTICAL) {
					nPartID += 4;
				}
				if (nCount == nCurSel) {
					nStateID = TIS_SELECTED;
				} else if (nCount == nFocus) {
					nStateID = TIS_HOT;
				}
				if (hImageList && tcItem.iImage >= 0) {
					pT->DrawThemeIcon(hdc, nPartID, nStateID, &rcItem, hImageList, tcItem.iImage);
				}
				pT->DrawThemeText(hdc,
					nPartID, nStateID, szText, _tcslen(szText), dwTextFlags, 0, &rcItem);
			}
		}
	}
};

template<class T, class TBase=UISkinTheme>
class UITabCtrlSkinThemeImpl : public UISkinThemeImpl<T,TBase>, public UITabCtrlSkinResImpl<T>
{
	typedef UITabCtrlSkinThemeImpl<T,TBase> This;
	typedef UISkinThemeImpl<T,TBase> Base;
public:
};

template<class T>
class UITabCtrlSkinMap 
	: public UITabCtrlSkinThemeImpl<T>
	, public UITabCtrlSkinDrawMap<T>
{
	typedef UITabCtrlSkinMap<T> This;
	typedef UITabCtrlSkinThemeImpl<T> SkinTheme;
	typedef UITabCtrlSkinDrawMap<T> SkinDrawMap;
public:

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
//Header Control 
//Part IDs	
//enum HEADERPARTS {
//	HP_HEADERITEM = 1,
//	HP_HEADERITEMLEFT = 2,
//	HP_HEADERITEMRIGHT = 3,
//	HP_HEADERSORTARROW = 4,
//	HP_HEADERDROPDOWN = 5,
//	HP_HEADERDROPDOWNFILTER = 6,
//	HP_HEADEROVERFLOW = 7,
//};
//State Ids
//enum HEADERSTYLESTATES {
//	HBG_DETAILS = 1,
//	HBG_ICON = 2,
//};
//
//enum HEADERITEMSTATES {
//	HIS_NORMAL = 1,
//	HIS_HOT = 2,
//	HIS_PRESSED = 3,
//	HIS_SORTEDNORMAL = 4,
//	HIS_SORTEDHOT = 5,
//	HIS_SORTEDPRESSED = 6,
//	HIS_ICONNORMAL = 7,
//	HIS_ICONHOT = 8,
//	HIS_ICONPRESSED = 9,
//	HIS_ICONSORTEDNORMAL = 10,
//	HIS_ICONSORTEDHOT = 11,
//	HIS_ICONSORTEDPRESSED = 12,
//};
//
//enum HEADERITEMLEFTSTATES {
//	HILS_NORMAL = 1,
//	HILS_HOT = 2,
//	HILS_PRESSED = 3,
//};
//
//enum HEADERITEMRIGHTSTATES {
//	HIRS_NORMAL = 1,
//	HIRS_HOT = 2,
//	HIRS_PRESSED = 3,
//};
//
//enum HEADERSORTARROWSTATES {
//	HSAS_SORTEDUP = 1,
//	HSAS_SORTEDDOWN = 2,
//};
//
//enum HEADERDROPDOWNSTATES {
//	HDDS_NORMAL = 1,
//	HDDS_SOFTHOT = 2,
//	HDDS_HOT = 3,
//};
//
//enum HEADERDROPDOWNFILTERSTATES {
//	HDDFS_NORMAL = 1,
//	HDDFS_SOFTHOT = 2,
//	HDDFS_HOT = 3,
//};
//
//enum HEADEROVERFLOWSTATES {
//	HOFS_NORMAL = 1,
//	HOFS_HOT = 2,
//};



typedef struct tagHeaderCtrl_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[12];
	Image* pImage;
	Image* pStateImage[12];
	HFONT  hFont;
	HFONT  hStateFont[12];
	COLORREF crText;
	COLORREF crStateText[12];
}HEADERCTRL_PARTSTATEINFO,*PHEADERCTRL_PARTSTATEINFO;
typedef struct tagHeaderCtrl_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	HEADERCTRL_PARTSTATEINFO Part[7];
}HEADERCTRL_MAXPARTSTATEINFO,*PHEADERCTRL_MAXPARTSTATEINFO;

template<class T,class TBase = UISkinRes>
class UIHeaderCtrlSkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UIHeaderCtrlSkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
public:
	static HEADERCTRL_MAXPARTSTATEINFO _MaxPartStateInfo;

public:
	Image* GetImage(int nPartID, int nStateID) 
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].pStateImage[nStateID-1];
		}
		return _MaxPartStateInfo.Part[nPartID-1].pImage;
	}
	HFONT GetHFONT(int nPartID, int nStateID)
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].hStateFont[nStateID-1];
		}
		HFONT hFont = _MaxPartStateInfo.Part[nPartID-1].hFont;
		return hFont;
	}
	COLORREF GetCOLORREF(int nPartID, int nStateID)
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].crStateText[nStateID-1];
		}
		return _MaxPartStateInfo.Part[nPartID-1].crText;
	}
	UINT GetMaxStateID(int nPartID)
	{
		return 12;
	}
};
template<class T,class TBase>
__declspec(selectany) HEADERCTRL_MAXPARTSTATEINFO UIHeaderCtrlSkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{
		{
			_T("HEADERITEM")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("SORTEDNORMAL"),_T("SORTEDHOT"),_T("SORTEDPRESSED"),_T("ICONNORMAL"),_T("ICONHOT"),_T("ICONPRESSED"),_T("ICONSORTEDNORMAL"),_T("ICONSORTEDHOT"),_T("ICONSORTEDPRESSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("HP_HEADERITEMLEFT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("SORTEDNORMAL"),_T("SORTEDHOT"),_T("SORTEDPRESSED"),_T("ICONNORMAL"),_T("ICONHOT"),_T("ICONPRESSED"),_T("ICONSORTEDNORMAL"),_T("ICONSORTEDHOT"),_T("ICONSORTEDPRESSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("HP_HEADERITEMRIGHT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("SORTEDNORMAL"),_T("SORTEDHOT"),_T("SORTEDPRESSED"),_T("ICONNORMAL"),_T("ICONHOT"),_T("ICONPRESSED"),_T("ICONSORTEDNORMAL"),_T("ICONSORTEDHOT"),_T("ICONSORTEDPRESSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("HP_HEADERSORTARROW")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("SORTEDNORMAL"),_T("SORTEDHOT"),_T("SORTEDPRESSED"),_T("ICONNORMAL"),_T("ICONHOT"),_T("ICONPRESSED"),_T("ICONSORTEDNORMAL"),_T("ICONSORTEDHOT"),_T("ICONSORTEDPRESSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("HP_HEADERDROPDOWN")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("SORTEDNORMAL"),_T("SORTEDHOT"),_T("SORTEDPRESSED"),_T("ICONNORMAL"),_T("ICONHOT"),_T("ICONPRESSED"),_T("ICONSORTEDNORMAL"),_T("ICONSORTEDHOT"),_T("ICONSORTEDPRESSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("HP_HEADERDROPDOWNFILTER")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("SORTEDNORMAL"),_T("SORTEDHOT"),_T("SORTEDPRESSED"),_T("ICONNORMAL"),_T("ICONHOT"),_T("ICONPRESSED"),_T("ICONSORTEDNORMAL"),_T("ICONSORTEDHOT"),_T("ICONSORTEDPRESSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
		,{
			_T("HP_HEADEROVERFLOW")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("SORTEDNORMAL"),_T("SORTEDHOT"),_T("SORTEDPRESSED"),_T("ICONNORMAL"),_T("ICONHOT"),_T("ICONPRESSED"),_T("ICONSORTEDNORMAL"),_T("ICONSORTEDHOT"),_T("ICONSORTEDPRESSED")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
	}
};


template<class T>
class UIHeaderCtrlSkinDrawMap : public UISkinDrawMap<T>
{
public:
	UINT GetPartID() 
	{
		ATLASSERT(0);
		return 0;
	}

	UINT GetStateID()
	{
		T* pT = static_cast<T*>(this);
		UINT uStateID = 1;
		if (!pT->IsWindowEnabled()) {
			uStateID = 4;
		}
		return uStateID;
	}

	DWORD GetTextFlags(LPHDITEM* lpHeaderItem)
	{
		T* pT = static_cast<T*>(this);
		DWORD dwTextFlags = 0;
		DWORD dwStyle = pT->GetStyle();
	
		dwTextFlags |= DT_VCENTER;

		if (lpHeaderItem) {
			if (lpHeaderItem->fmt & HDF_CENTER) {
				dwTextFlags |= DT_CENTER;
			} else if(lpHeaderItem->fmt & HDF_RIGHT) {
				dwTextFlags |= DT_RIGHT;
			}
		}

		dwTextFlags |= DT_NOPREFIX;

		return dwTextFlags;
	}

	void Draw(HDC hdc)
	{
		T* pT = static_cast<T*>(this);

		DWORD dwStyle = pT->GetStyle();
		//DWORD dwExStyle = pT->GetExStyle();
		DWORD dwTextFlags = 0;

		HIMAGELIST hImageList = pT->GetImageList();
		int nCount	= pT->GetItemCount();
		//int nFocus	= pT->GetFocusedItem();

		RECT rcClient = {0};
		pT->GetClientRect(&rcClient);
	}
};

template<class T, class TBase=UISkinTheme>
class UIHeaderCtrlSkinThemeImpl : public UISkinThemeImpl<T,TBase>, public UIHeaderCtrlSkinResImpl<T>
{
	typedef UIHeaderCtrlSkinThemeImpl<T,TBase> This;
	typedef UISkinThemeImpl<T,TBase> Base;
public:
};

template<class T>
class UIHeaderCtrlSkinMap 
	: public UIHeaderCtrlSkinThemeImpl<T>
	, public UIHeaderCtrlSkinDrawMap<T>
{
	typedef UIHeaderCtrlSkinMap<T> This;
	typedef UIHeaderCtrlSkinThemeImpl<T> SkinTheme;
	typedef UIHeaderCtrlSkinDrawMap<T> SkinDrawMap;
public:

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
//ScrollBar Control 
//Part IDs	
//enum SCROLLBARPARTS {
//	SBP_ARROWBTN = 1,
//	SBP_THUMBBTNHORZ = 2,
//	SBP_THUMBBTNVERT = 3,
//	SBP_LOWERTRACKHORZ = 4,
//	SBP_UPPERTRACKHORZ = 5,
//	SBP_LOWERTRACKVERT = 6,
//	SBP_UPPERTRACKVERT = 7,
//	SBP_GRIPPERHORZ = 8,
//	SBP_GRIPPERVERT = 9,
//	SBP_SIZEBOX = 10,
//};
//
//enum ARROWBTNSTATES {
//	ABS_UPNORMAL = 1,
//	ABS_UPHOT = 2,
//	ABS_UPPRESSED = 3,
//	ABS_UPDISABLED = 4,
//	ABS_DOWNNORMAL = 5,
//	ABS_DOWNHOT = 6,
//	ABS_DOWNPRESSED = 7,
//	ABS_DOWNDISABLED = 8,
//	ABS_LEFTNORMAL = 9,
//	ABS_LEFTHOT = 10,
//	ABS_LEFTPRESSED = 11,
//	ABS_LEFTDISABLED = 12,
//	ABS_RIGHTNORMAL = 13,
//	ABS_RIGHTHOT = 14,
//	ABS_RIGHTPRESSED = 15,
//	ABS_RIGHTDISABLED = 16,
//	ABS_UPHOVER = 17,
//	ABS_DOWNHOVER = 18,
//	ABS_LEFTHOVER = 19,
//	ABS_RIGHTHOVER = 20,
//};
//
//enum SCROLLBARSTYLESTATES {
//	SCRBS_NORMAL = 1,
//	SCRBS_HOT = 2,
//	SCRBS_PRESSED = 3,
//	SCRBS_DISABLED = 4,
//	SCRBS_HOVER = 5,
//};
//
//enum SIZEBOXSTATES {
//	SZB_RIGHTALIGN = 1,
//	SZB_LEFTALIGN = 2,
//	SZB_TOPRIGHTALIGN = 3,
//	SZB_TOPLEFTALIGN = 4,
//	SZB_HALFBOTTOMRIGHTALIGN = 5,
//	SZB_HALFBOTTOMLEFTALIGN = 6,
//	SZB_HALFTOPRIGHTALIGN = 7,
//	SZB_HALFTOPLEFTALIGN = 8,
//};


typedef struct tagScrollBar_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[20];
	Image* pImage;
	Image* pStateImage[20];
}SCROLLBARCTRL_PARTSTATEINFO,*PSCROLLBARCTRL_PARTSTATEINFO;
typedef struct tagScrollBar_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	SCROLLBARCTRL_PARTSTATEINFO Part[10];
}SCROLLBARCTRL_MAXPARTSTATEINFO,*PSCROLLBARCTRL_MAXPARTSTATEINFO;

template<class T,class TBase = UISkinRes>
class UIScrollBarSkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UIScrollBarSkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
public:
	static SCROLLBARCTRL_MAXPARTSTATEINFO _MaxPartStateInfo;

public:
	Image* GetImage(int nPartID, int nStateID) 
	{ 
		ATLASSERT(nPartID > 0);
		if (nStateID > 0) {
			return _MaxPartStateInfo.Part[nPartID-1].pStateImage[nStateID-1];
		}
		return _MaxPartStateInfo.Part[nPartID-1].pImage;
	}
	UINT GetMaxStateID(int nPartID)
	{
		switch(nPartID)
		{
		case SBP_ARROWBTN:
			return 16; //暂时不支持HOVER状态
			break;
		case SBP_THUMBBTNHORZ:
			return 4;
			break;
		case SBP_THUMBBTNVERT:
			return 4;
			break;
		case SBP_LOWERTRACKHORZ:
			return 4;
			break;
		case SBP_UPPERTRACKHORZ:
			return 4;
			break;
		case SBP_LOWERTRACKVERT:
			return 4;
			break;
		case SBP_UPPERTRACKVERT:
			return 4;
			break;
		case SBP_GRIPPERHORZ:
			return 4;
			break;
		case SBP_GRIPPERVERT:
			return 4;
			break;
		case SBP_SIZEBOX:
			return 4;
			break;
		}
		return 4;
	}
};
template<class T,class TBase>
__declspec(selectany) SCROLLBARCTRL_MAXPARTSTATEINFO UIScrollBarSkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{
		{
			_T("ARROWBTN")
				,{_T("UPNORMAL"),_T("UPHOT"),_T("UPPRESSED"),_T("UPDISABLED"),_T("UPHOVER"),_T("DOWNNORMAL"),_T("DWONHOT"),_T("DOWNPRESSED"),_T("DOWNDISABLED"),_T("DOWNHOVER"),_T("LEFTNORMAL"),_T("LEFTHOT"),_T("LEFTPRESSED"),_T("LEFTDISABLED"),_T("LEFTHOVER"),_T("RIGHTNORMAL"),_T("RIGHTHOT"),_T("RIGHTPRESSED"),_T("RIGHTDISABLED"),_T("RIGHTHOVER")}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
		,{
			_T("THUMBBTNHORZ")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED"),_T("HOVER"),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
		,{
			_T("THUMBBTNVERT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED"),_T("HOVER"),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
		,{
			_T("LOWERTRACKHORZ")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED"),_T("HOVER"),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
		,{
			_T("UPPERTRACKHORZ")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED"),_T("HOVER"),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
		,{
			_T("LOWERTRACKVERT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED"),_T("HOVER"),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
		,{
			_T("UPPERTRACKVERT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED"),_T("HOVER"),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
		,{
			_T("GRIPPERHORZ")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED"),_T("HOVER"),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
		,{
			_T("GRIPPERVERT")
				,{_T("NORMAL"),_T("HOT"),_T("PRESSED"),_T("DISABLED"),_T("HOVER"),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
		,{
			_T("SIZEBOX")
				,{_T("RIGHTALIGN"),_T("LEFTALIGN"),_T("TOPRIGHTALIGN"),_T("TOPLEFTALIGN"),_T("HALFBOTTOMRIGHTALIGN"),_T("HALFBOTTOMLEFTALIGN"),_T("HALFTOPRIGHTALIGN"),_T("HALFTOPLEFTALIGN"),NULL,NULL,NULL,NULL,NULL,NULL,NULL}
			,NULL
				,{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
		}
	}
};


template<class T>
class UIScrollBarSkinDrawMap : public UISkinDrawMap<T>
{
public:
	UINT GetPartID() 
	{
		ATLASSERT(0);
		return 0;
	}

	UINT GetStateID(int nBar, UINT uPartID, BOOL bUpLeft = TRUE)
	{
		T* pT = static_cast<T*>(this);
		UINT uStateID = SCRBS_NORMAL;
		if (!pT->IsWindowEnabled()) {
			uStateID = SCRBS_DISABLED;
		} else {
			if(pT->GetCapture()==*pT) {
				uStateID = SCRBS_PRESSED;
			}/* else if (pT->GetFocus()==*pT) {
				uStateID = SCRBS_HOT;
			}*/ else if (pT->GetHover()==*pT) {
				uStateID = SCRBS_HOT;//SCRBS_HOVER;
			}
		}
		//if (uStateID!=SCRBS_HOVER) {
			if (nBar==SB_HORZ) {
				if (uPartID==SBP_ARROWBTN) {
					if (bUpLeft) {
						uStateID = uStateID+8;
					} else {
						uStateID = uStateID+12;
					}
				}
			} else {
				if (uPartID==SBP_ARROWBTN) {
					if (bUpLeft) {
						//
					} else {
						uStateID = uStateID+4;
					}
				}
			}
		/*} else {
			if (nBar==SB_HORZ) {
				if (uPartID==SBP_ARROWBTN) {
					if (bUpLeft) {
						uStateID = ABS_LEFTHOVER;
					} else {
						uStateID = ABS_RIGHTHOVER;
					}
				}
			} else {
				if (uPartID==SBP_ARROWBTN) {
					if (bUpLeft) {
						uStateID = ABS_UPHOVER;
					} else {
						uStateID = ABS_DOWNHOVER;
					}
				}
			}
		}*/
		return uStateID;
	}

	LRESULT PaintScrollBar(HDC hdc, int nBar, LPSCROLLINFO lpScrollInfo, PSCROLLBARINFO pScrollBarInfo)
	{
		T* pT = static_cast<T*>(this);

		//WTL::CDCHandle dc(hdc);

		if (nBar==SB_HORZ) {
			CRect rc = pScrollBarInfo->rcScrollBar;

			UINT uArrowBtnState1 = pT->GetStateID(nBar,SBP_ARROWBTN)
				,uLowerTrackState = pT->GetStateID(nBar,SBP_LOWERTRACKHORZ)
				,uThumbBtnState = pT->GetStateID(nBar,SBP_THUMBBTNHORZ)
				,uGripperState = pT->GetStateID(nBar,SBP_GRIPPERHORZ)
				,uUpperTrackState = pT->GetStateID(nBar,SBP_UPPERTRACKHORZ)
				,uArrowBtnState2 = pT->GetStateID(nBar,SBP_ARROWBTN,FALSE)
				;

			SIZE xyGripper = {rc.Height(),rc.Height()};
			pT->GetThemeMetric(hdc,SBP_GRIPPERHORZ,uGripperState,TMT_WIDTH,(int*)&xyGripper.cx);
			pT->GetThemeMetric(hdc,SBP_GRIPPERVERT,uGripperState,TMT_HEIGHT,(int*)&xyGripper.cy);
			
			CRect rcArrowBtn1 = rc;
			rcArrowBtn1.left = rc.left;
			rcArrowBtn1.right = rcArrowBtn1.left+pScrollBarInfo->dxyLineButton;
			pT->DrawThemeBackground(hdc, SBP_ARROWBTN, uArrowBtnState1, &rcArrowBtn1);
			
			if (pScrollBarInfo->xyThumbTop==pScrollBarInfo->xyThumbBottom) {
				CRect rcTrack = rc;
				rcTrack.left = rc.left+pScrollBarInfo->dxyLineButton;
				rcTrack.right = rc.right-pScrollBarInfo->dxyLineButton;
				pT->DrawThemeBackground(hdc, SBP_LOWERTRACKHORZ, uLowerTrackState, &rcTrack);
			} else {
				CRect rcLowerTrack = rc;
				rcLowerTrack.left = rc.left+pScrollBarInfo->dxyLineButton;
				rcLowerTrack.right = rcLowerTrack.left+pScrollBarInfo->xyThumbTop;
				pT->DrawThemeBackground(hdc, SBP_LOWERTRACKHORZ, uLowerTrackState, &rcLowerTrack);

				if (pScrollBarInfo->xyThumbTop<pScrollBarInfo->xyThumbBottom) {
					CRect rcThumbBtn = rc;
					rcThumbBtn.left = rc.left+pScrollBarInfo->xyThumbTop;
					rcThumbBtn.right = rc.left+pScrollBarInfo->xyThumbBottom;
					pT->DrawThemeBackground(hdc, SBP_THUMBBTNHORZ, uThumbBtnState, &rcThumbBtn);
					CRect rcGripper = rcThumbBtn;
					if (rcThumbBtn.Width()>xyGripper.cx) {
						rcGripper.left += (rcThumbBtn.Width()-xyGripper.cx)/2;
						rcGripper.right = rcGripper.left+xyGripper.cx;
					}
					pT->DrawThemeBackground(hdc, SBP_GRIPPERHORZ, uGripperState, &rcGripper);
				}

				CRect rcUpperTrack = rc;
				rcUpperTrack.left = rc.left+pScrollBarInfo->xyThumbBottom;
				rcUpperTrack.right = rc.right-pScrollBarInfo->dxyLineButton;
				pT->DrawThemeBackground(hdc, SBP_UPPERTRACKHORZ, uUpperTrackState, &rcUpperTrack);
			}

			CRect rcArrowBtn2 = rc;
			rcArrowBtn2.left = rc.right-pScrollBarInfo->dxyLineButton;
			rcArrowBtn2.right = rc.right;
			pT->DrawThemeBackground(hdc, SBP_ARROWBTN, uArrowBtnState2, &rcArrowBtn2);
		} else {
			CRect rc = pScrollBarInfo->rcScrollBar;

			UINT uArrowBtnState1 = pT->GetStateID(nBar,SBP_ARROWBTN)
				,uLowerTrackState = pT->GetStateID(nBar,SBP_LOWERTRACKVERT)
				,uThumbBtnState = pT->GetStateID(nBar,SBP_THUMBBTNVERT)
				,uGripperState = pT->GetStateID(nBar,SBP_GRIPPERVERT)
				,uUpperTrackState = pT->GetStateID(nBar,SBP_UPPERTRACKVERT)
				,uArrowBtnState2 = pT->GetStateID(nBar,SBP_ARROWBTN,FALSE)
				;

			SIZE xyGripper = {rc.Width(),rc.Width()};
			pT->GetThemeMetric(hdc,SBP_GRIPPERHORZ,uGripperState,TMT_WIDTH,(int*)&xyGripper.cx);
			pT->GetThemeMetric(hdc,SBP_GRIPPERVERT,uGripperState,TMT_HEIGHT,(int*)&xyGripper.cy);

			CRect rcArrowBtn1 = rc;
			rcArrowBtn1.top = rc.top;
			rcArrowBtn1.bottom = rcArrowBtn1.top+pScrollBarInfo->dxyLineButton;
			pT->DrawThemeBackground(hdc, SBP_ARROWBTN, uArrowBtnState1, &rcArrowBtn1);

			if (pScrollBarInfo->xyThumbTop==pScrollBarInfo->xyThumbBottom) {
				CRect rcTrack = rc;
				rcTrack.top = rc.top+pScrollBarInfo->dxyLineButton;
				rcTrack.bottom = rc.bottom-pScrollBarInfo->dxyLineButton;
				pT->DrawThemeBackground(hdc, SBP_LOWERTRACKVERT, uLowerTrackState, &rcTrack);
			} else {
				CRect rcLowerTrack = rc;
				rcLowerTrack.top = rc.top+pScrollBarInfo->dxyLineButton;
				rcLowerTrack.bottom = rcLowerTrack.top+pScrollBarInfo->xyThumbTop;
				pT->DrawThemeBackground(hdc, SBP_LOWERTRACKVERT, uLowerTrackState, &rcLowerTrack);

				if (pScrollBarInfo->xyThumbTop<pScrollBarInfo->xyThumbBottom) {
					CRect rcThumbBtn = rc;
					rcThumbBtn.top = rc.top+pScrollBarInfo->xyThumbTop;
					rcThumbBtn.bottom = rc.top+pScrollBarInfo->xyThumbBottom;
					pT->DrawThemeBackground(hdc, SBP_THUMBBTNVERT, uThumbBtnState, &rcThumbBtn);
					CRect rcGripper = rcThumbBtn;
					if (rcThumbBtn.Height()>xyGripper.cy) {
						rcGripper.top += (rcThumbBtn.Height()-xyGripper.cy)/2;
						rcGripper.bottom = rcGripper.top+xyGripper.cy;
					}
					pT->DrawThemeBackground(hdc, SBP_GRIPPERVERT, uGripperState, &rcGripper);
				}

				CRect rcUpperTrack = rc;
				rcUpperTrack.top = rc.top+pScrollBarInfo->xyThumbBottom;
				rcUpperTrack.bottom = rc.bottom-pScrollBarInfo->dxyLineButton;
				pT->DrawThemeBackground(hdc, SBP_UPPERTRACKVERT, uUpperTrackState, &rcUpperTrack);
			}

			CRect rcArrowBtn2 = rc;
			rcArrowBtn2.top = rc.bottom-pScrollBarInfo->dxyLineButton;
			rcArrowBtn2.bottom = rc.bottom;
			pT->DrawThemeBackground(hdc, SBP_ARROWBTN, uArrowBtnState2, &rcArrowBtn2);
		}
		return 0L;
	}

	void Draw(HDC hdc)
	{
		T* pT = static_cast<T*>(this);

		DWORD dwStyle = pT->GetStyle();
		
		//RECT rcClient;
		//pT->GetClientRect(&rcClient);

		SCROLLINFO ScrollInfo = {0};
		SCROLLBARINFO ScrollBarInfo = {0};
		pT->GetScrollInfo(&ScrollInfo);
		pT->GetScrollBarInfo(&ScrollBarInfo);
		pT->PaintScrollBar(hdc,SBS_VERT&dwStyle?SB_VERT:SB_HORZ, &ScrollInfo, &ScrollBarInfo);
	}
};

template<class T, class TBase=UISkinTheme>
class UIScrollBarSkinThemeImpl : public UISkinThemeImpl<T,TBase>, public UIScrollBarSkinResImpl<T>
{
	typedef UIScrollBarSkinThemeImpl<T,TBase> This;
	typedef UISkinThemeImpl<T,TBase> Base;
public:
};

template<class T>
class UIScrollBarSkinMap 
	: public UIScrollBarSkinThemeImpl<T>
	, public UIScrollBarSkinDrawMap<T>
{
	typedef UIScrollBarSkinMap<T> This;
	typedef UIScrollBarSkinThemeImpl<T> SkinTheme;
	typedef UIScrollBarSkinDrawMap<T> SkinDrawMap;
public:

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};


#endif//_H_UISKIN_H_