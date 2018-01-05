
#pragma once

#ifndef _H_UISKIN2_H_
#define _H_UISKIN2_H_

#include <UI/UISkin.h>
#include "UILite.h"

//////////////////////////////////////////////////////////////////////////

UILITE_API UISkinManager* getUISkinManager();
#define _pUISkinManager getUISkinManager()
//extern UILITE_API UISkinManager* _pUISkinManager;

//////////////////////////////////////////////////////////////////////////
//HypeLink2
enum
{
	HYP_TEXT = 1,
};

enum
{
	HYTS_NORMAL = 1,
	HYTS_HOT,
	HYTS_DISABLED,
};

typedef struct tagHypeLink2_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[3];
	HFONT hStateFont[3];
	COLORREF crStateText[3];
}HYPELINK2_PARTSTATEINFO,*PHYPELINK2_PARTSTATEINFO;
typedef struct tagHypeLink2_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	HYPELINK2_PARTSTATEINFO Part[1];
}HYPELINK2_MAXPARTSTATEINFO,*PHYPELINK2_MAXPARTSTATEINFO;

template<class T, class TBase = UISkinRes>
class UIHypeLink2SkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UIHypeLink2SkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
protected:
	static HYPELINK2_MAXPARTSTATEINFO _MaxPartStateInfo;

public:
	HFONT GetHFONT(int nPartID, int nStateID)
	{ 
		if (nPartID > 0) {
			if (nStateID > 0) {
				return _MaxPartStateInfo.Part[nPartID-1].hStateFont[nStateID-1];
			}
		}
		return NULL;
	}
	COLORREF GetCOLORREF(int nPartID, int nStateID)
	{ 
		if (nPartID > 0) {
			if (nStateID > 0) {
				return _MaxPartStateInfo.Part[nPartID-1].crStateText[nStateID-1];
			}
		}
		return CLR_INVALID;
	}
	UINT GetMaxStateID(int nPartID)
	{
		return 3;
	}
};
template<class T,class TBase>
__declspec(selectany) HYPELINK2_MAXPARTSTATEINFO UIHypeLink2SkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{
		{
			_T("TEXT")
			,{_T("NORMAL"),_T("HOT"),_T("DISABLED")}
			,{NULL,NULL,NULL}
			,{CLR_INVALID,CLR_INVALID,CLR_INVALID}
		}
	}
};

template<class T>
class UIHypeLink2SkinDrawMap : public UISkinDrawMap<T>
{
public:
	UINT GetPartID() 
	{
		return HYP_TEXT;
	}
	UINT GetStateID()
	{
		T* pT = static_cast<T*>(this);
		if(!pT->IsWindowEnabled()) {
			return HYTS_DISABLED;
		} else {
			DWORD dwState = pT->GetState();
			if (dwState) {
				return HYTS_HOT;
			}
		}
		return HYTS_NORMAL;
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

		//DWORD dwStyle = pT->GetStyle();
		//DWORD dwExStyle = pT->GetExStyle();
		int nPartID = pT->GetPartID();
		int nStateID = pT->GetStateID();
		DWORD dwTextFlags = pT->GetTextFlags();

		RECT rcClient = {0};
		pT->GetClientRect(&rcClient);

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
//EP_EDITTEXT	ETS_NORMAL 
//				ETS_HOT
//EP_CARET

typedef struct tagEdit_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[2];
	HFONT hFont;
	Image* pImageEdge;
	Image* pStateImageEdge[2];
}EDIT_PARTSTATEINFO,*PEDIT_PARTSTATEINFO;
typedef struct tagEdit_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	RECT rcMargin;
	TCHAR PasswordChar;
	EDIT_PARTSTATEINFO Part[2];
}EDIT_MAXPARTSTATEINFO,*PEDIT_MAXPARTSTATEINFO;

template<class T,class TBase = UISkinRes>
class UIEditSkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UIEditSkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
protected:
	static EDIT_MAXPARTSTATEINFO _MaxPartStateInfo;
	
public:
	Image* GetImageEdge(int nPartID, int nStateID)
	{
		if (nPartID > 0) {
			if (nStateID > 0) {
				return _MaxPartStateInfo.Part[nPartID-1].pStateImageEdge[nStateID-1];
			} else {
				return _MaxPartStateInfo.Part[nPartID-1].pImageEdge;
			}
		}
		return NULL;
	}
	HFONT GetHFONT(int nPartID, int nStateID)
	{ 
		return _MaxPartStateInfo.Part[nPartID-1].hFont;
	}
	UINT GetMaxStateID(int nPartID)
	{
		switch(nPartID)
		{
		case EP_EDITTEXT:
			{ 
				return 2;
			}
			break;
		case EP_CARET:
			{ 
				return 0;
			}
			break;
		}
		return 0;
	}
	BOOL GetContentMargin(int nPartID, int nStateID, LPRECT pRect)
	{
		ATLASSERT(nPartID > 0);
		*pRect = _MaxPartStateInfo.rcMargin;
		return TRUE;
	}
	TCHAR GetContentPasswordChar()
	{
		return _MaxPartStateInfo.PasswordChar;
	}
};
template<class T,class TBase>
__declspec(selectany) EDIT_MAXPARTSTATEINFO UIEditSkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{0}
	,0
	,{
		{
			_T("EDIT")
			,{_T("NORMAL"),_T("HOT")}
			,NULL
			,NULL
			,{NULL,NULL}
		}
		,{
			_T("CARET")
			,{NULL,NULL}
			,NULL
			,NULL
			,{NULL,NULL}
		}
	}
};

template<class T>
class UIEdit2SkinDrawMap : public UISkinDrawMap<T>
{
	typedef UIEdit2SkinDrawMap<T> This;
	typedef UISkinDrawMap<T> SkinDraw;
public:
	UIEdit2SkinDrawMap() { }
	
	UINT GetPartID() 
	{
		return EP_EDITTEXT;
	}

	UINT GetStateID()
	{
		T* pT = static_cast<T*>(this);
		if (!pT->IsWindowEnabled()) {
			return ETS_DISABLED;
		}/* else if(T::GetFocus() == *pT) {
			return ETS_FOCUSED;
		} */else {
			return ETS_NORMAL;
		}
		return 0;
	}
	
	DWORD GetTextFlags()
	{
		T* pT = static_cast<T*>(this);
		DWORD dwTextFlags = DT_EDITCONTROL;
		DWORD dwStyle = pT->GetStyle();
		if (dwStyle & ES_CENTER) {
			dwTextFlags |= DT_CENTER;
		} else if (dwStyle & ES_RIGHT) {
			dwTextFlags |= DT_RIGHT;
		} else {
			dwTextFlags |= DT_LEFT;
		}
		if (dwStyle & ES_MULTILINE) {
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

		RECT rcClient;
		pT->GetClientRect(&rcClient);
		//::FillRect(hdc, &rcClient, ::GetSysColorBrush(COLOR_WINDOW));
		pT->DrawThemeEdge(hdc, nPartID, nStateID, &rcClient, 0, BF_RECT|BF_MIDDLE);

		CString strText;
		pT->GetWindowText(strText);
		RECT rcText = {0};
		pT->GetThemeBackgroundContentRect(hdc, nPartID, nStateID, &rcClient, &rcText);
		pT->DrawThemeText(hdc,
				nPartID, nStateID, strText, strText.GetLength(), dwTextFlags, 0, &rcText);
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinDraw)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UISkinTheme>
class UIButtonSkinTheme2Impl : public UISkinThemeImpl<T,TBase>, public UIButtonSkinResImpl<T>
{
	typedef UIButtonSkinTheme2Impl<T,TBase> This;
	typedef UISkinThemeImpl<T,TBase> Base;
public:
};

template<class T>
class UIButton2SkinMap : public UIButtonSkinTheme2Impl<T>, public UIButtonSkinDrawMap<T>
{
	typedef UIButton2SkinMap<T> This;
	typedef UIButtonSkinTheme2Impl<T> SkinTheme;
	typedef UIButtonSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};


//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UISkinTheme>
class UITabCtrlSkinTheme2Impl : public UISkinThemeImpl<T,TBase>, public UITabCtrlSkinResImpl<T>
{
	typedef UITabCtrlSkinTheme2Impl<T,TBase> This;
	typedef UISkinThemeImpl<T,TBase> Base;
public:
};

template<class T>
class UITabCtrl2SkinMap : public UITabCtrlSkinTheme2Impl<T>, public UITabCtrlSkinDrawMap<T>
{
	typedef UITabCtrl2SkinMap<T> This;
	typedef UITabCtrlSkinTheme2Impl<T> SkinTheme;
	typedef UITabCtrlSkinDrawMap<T> SkinDrawMap;
public:

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
//Head2
enum
{
	HDP_BACKGROUND = 1,
	HDP_TEXT,
	HDP_SPLIT,
};

enum
{
	HDS_NORMAL = 1,
	HDS_HOT,
	HDS_DISABLED,
};

typedef struct tagHead2_PartStateInfo
{
	LPCTSTR pszName;
	LPCTSTR pszStateName[3];
	HFONT hStateFont[3];
	COLORREF crStateText[3];
	Image* pStateImage[3];
}HEAD2_PARTSTATEINFO,*PHEAD2_PARTSTATEINFO;
typedef struct tagHead2_MaxPartStateInfo
{
	UINT nID; //和SKINMANAGER保持一致,用于换肤比较是否要重新加载皮肤
	HEAD2_PARTSTATEINFO Part[1];
}HEAD2_MAXPARTSTATEINFO,*PHEAD2_MAXPARTSTATEINFO;

template<class T, class TBase = UISkinRes>
class UIHead2SkinResImpl : public UISkinResImpl<T,TBase>
{
	typedef UIHead2SkinResImpl<T,TBase> This;
	typedef UISkinResImpl<T,TBase> Base;
protected:
	static HEAD2_MAXPARTSTATEINFO _MaxPartStateInfo;

public:
	HFONT GetHFONT(int nPartID, int nStateID)
	{ 
		if (nPartID > 0) {
			if (nStateID > 0) {
				return _MaxPartStateInfo.Part[nPartID-1].hStateFont[nStateID-1];
			}
		}
		return NULL;
	}
	COLORREF GetCOLORREF(int nPartID, int nStateID)
	{ 
		if (nPartID > 0) {
			if (nStateID > 0) {
				return _MaxPartStateInfo.Part[nPartID-1].crStateText[nStateID-1];
			}
		}
		return CLR_INVALID;
	}
	UINT GetMaxStateID(int nPartID)
	{
		return 3;
	}
};
template<class T,class TBase>
__declspec(selectany) HEAD2_MAXPARTSTATEINFO UIHead2SkinResImpl<T,TBase>::_MaxPartStateInfo = 
{
	0
	,{
		{
			_T("TEXT")
			,{_T("NORMAL"),_T("HOT"),_T("DISABLED")}
			,{NULL,NULL,NULL}
			,{CLR_INVALID,CLR_INVALID,CLR_INVALID}
			,{NULL,NULL,NULL}
		}
	}
};

template<class T>
class UIHead2SkinDrawMap : public UISkinDrawMap<T>
{
public:
	UINT GetStateID()
	{
		T* pT = static_cast<T*>(this);
		if(!pT->IsWindowEnabled()) {
			return HDS_DISABLED;
		} else {
			DWORD dwState = pT->GetState();
			if (dwState) {
				return HDS_HOT;
			}
		}
		return HYTS_NORMAL;
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

		//DWORD dwStyle = pT->GetStyle();
		//DWORD dwExStyle = pT->GetExStyle();
		//int nPartID = pT->GetPartID();
		/*int nStateID = pT->GetStateID();
		DWORD dwTextFlags = pT->GetTextFlags();

		RECT rcClient = {0};
		pT->GetClientRect(&rcClient);

		CString strText;
		pT->GetWindowText(strText);
		if (!strText.IsEmpty()) {
			RECT rcText = {0};
			pT->GetThemeBackgroundContentRect(hdc, nPartID, nStateID, &rcClient, &rcText);
			pT->DrawThemeText(hdc,
				nPartID, nStateID, strText, strText.GetLength(), dwTextFlags, 0, &rcText);
		}*/
	}
};

#endif//_H_UISKIN2_H_