#ifndef _H_UIXMLSKIN_H_
#define _H_UIXMLSKIN_H_

#include "UILite.h"
#include "UISkin2.h"
#include <XLib/XXml.h>

class UILITE_API UIXSkinTheme : public UISkinTheme
{
public:
	HTHEME OpenThemeData(HWND hWnd, LPCWSTR pszClassList);
	HRESULT CloseThemeData(HWND hWnd = NULL);
};

template <class T, class TBase = UIXSkinTheme>
class UIXSkinThemeImpl : public UISkinThemeImpl<T,TBase>
{
	typedef UIXSkinThemeImpl<T,TBase> This;
	typedef UISkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);
		return Base::OpenThemeData();
	}
	
	HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}

	HRESULT SetWindowTheme(LPCWSTR pszSubAppName, LPCWSTR pszSubIDList)
	{
		return S_FALSE;
	}

	HTHEME GetWindowTheme() const
	{
		return NULL;
	}

	HRESULT EnableThemeDialogTexture(DWORD dwFlags)
	{
		return S_FALSE;
	}

	BOOL IsThemeDialogTextureEnabled() const
	{
		return FALSE;
	}

	HRESULT DrawThemeParentBackground(HDC hDC, const RECT* pRect = NULL)
	{
		return S_FALSE;
	}

#ifdef _WTL_NEW_UXTHEME
	HRESULT SetWindowThemeAttribute(WINDOWTHEMEATTRIBUTETYPE type, PVOID pvAttribute, DWORD cbAttribute)
	{
		return S_FALSE;
	}

	HRESULT SetWindowThemeNonClientAttributes(DWORD dwAttributes, DWORD dwMask)
	{
		return S_FALSE;
	}

	HRESULT DrawThemeParentBackgroundEx(HDC hDC, DWORD dwFlags, const RECT* lpRect = NULL)
	{
		return S_FALSE;
	}
#endif // _WTL_NEW_UXTHEME

	// Message map and handlers
	// Note: If you handle any of these messages in your derived class,
	// it is better to put CHAIN_MSG_MAP at the start of your message map.
	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_THEMECHANGED, OnThemeChanged)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		pT->OpenThemeData();
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		pT->CloseThemeData();
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnThemeChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		pT->CloseThemeData();
		pT->OpenThemeData();
		bHandled = FALSE;
		return 1;
	}
};
/*
class UIXSkinTheme : public UISkinTheme
{
	typedef UIXSkinTheme This;
	typedef UISkinTheme Base;
	
public:
	HTHEME OpenThemeData(HWND hWnd, LPCWSTR pszClassList)
	{
		return Base::OpenThemeData(hWnd, pszClassList);
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}
};*/

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkinTheme>
class UIXWindowSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UIWindowSkinResImpl<T>
{
	typedef UIXWindowSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			LPCTSTR lpszClassName = T::GetWndClassName();
			int MaxPart = _countof(_MaxPartStateInfo.Part);
			for (i = 0; i < MaxPart; i++)
			{
				WINDOW_PARTSTATEINFO& Part = _MaxPartStateInfo.Part[i];
				if (Part.pszName) {
					LPCTSTR lpszPart = Part.pszName;
					Part.pImage = _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),lpszPart),0,lpszClassName);
					{
						int MaxState = _countof(Part.pszStateName);
						for (j = 0; j < MaxState; j++)
						{
							if (!Part.pszStateName[j]) {
								break;
							}
							LPCTSTR lpszState = Part.pszStateName[j];
							Part.pStateImage[j] = _pUISkinManager->GetImage(MAKESKINSTRRESID3(_T("Image"),lpszPart,lpszState),0,lpszClassName);
						}
					}
				}
			}
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXWindowSkinMap : public UIXWindowSkinThemeImpl<T>, public UIWindowSkinDrawMap<T>
{
	typedef UIXWindowSkinMap<T> This;
	typedef UIXWindowSkinThemeImpl<T> SkinTheme;
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

template<class T, class TBase=UIXSkinTheme>
class UIXSysButtonSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UISysButtonSkinResImpl<T>
{
	typedef UIXSysButtonSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			LPCTSTR lpszClassName = T::GetWndClassName();
			int MaxPart = _countof(_MaxPartStateInfo.Part);
			for (i = 0; i < MaxPart; i++)
			{
				SYSBUTTON_PARTSTATEINFO& Part = _MaxPartStateInfo.Part[i];
				if (Part.pszName) {
					LPCTSTR lpszPart = Part.pszName;
					Part.pImage = _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),lpszPart),0,lpszClassName);
					{
						int MaxState = _countof(Part.pszStateName);
						for (j = 0; j < MaxState; j++)
						{
							if (!Part.pszStateName[j]) {
								break;
							}
							LPCTSTR lpszState = Part.pszStateName[j];
							Part.pStateImage[j] = _pUISkinManager->GetImage(MAKESKINSTRRESID3(_T("Image"),lpszPart,lpszState),0,lpszClassName);
						}
					}
				}
			}
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXSysButtonSkinMap : public UIXSysButtonSkinThemeImpl<T>, public UISysButtonSkinDrawMap<T>
{
	typedef UIXSysButtonSkinMap<T> This;
	typedef UIXSysButtonSkinThemeImpl<T> SkinTheme;
	typedef UISysButtonSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkinTheme>
class UIXStaticSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UIStaticSkinResImpl<T>
{
	typedef UIXStaticSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		LPCTSTR lpszClassName = T::GetWndClassName();
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			_MaxPartStateInfo.hFont = _pUISkinManager->GetHFONT(MAKESKINSTRRESID(_T("Font")),0,lpszClassName);
			_MaxPartStateInfo.crText = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID(_T("Color")),CLR_INVALID,lpszClassName);
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}
		CString strName = pT->GetWindowName();
		if (!strName.IsEmpty()) {
			m_pImage = _pUISkinManager->GetImage(strName+CString(_T("."))+MAKESKINSTRRESID(_T("Image")),NULL,lpszClassName);
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXStaticSkinMap : public UIXStaticSkinThemeImpl<T>, public UIStaticSkinDrawMap<T>
{
	typedef UIXStaticSkinMap<T> This;
	typedef UIXStaticSkinThemeImpl<T> SkinTheme;
	typedef UIStaticSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkinTheme>
class UIXHypeLinkSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UIHypeLink2SkinResImpl<T>
{
	typedef UIXHypeLinkSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			LPCTSTR lpszClassName = T::GetWndClassName();
			int MaxPart = _countof(_MaxPartStateInfo.Part);
			for (i = 0; i < MaxPart; i++)
			{
				HYPELINK2_PARTSTATEINFO& Part = _MaxPartStateInfo.Part[i];
				if (Part.pszName) {
					LPCTSTR lpszPart = Part.pszName;
					int MaxState = _countof(Part.pszStateName);
					for (j = 0; j < MaxState; j++)
					{
						if (!Part.pszStateName[j]) {
							break;
						}
						LPCTSTR lpszState = Part.pszStateName[j];
						Part.hStateFont[j] = _pUISkinManager->GetHFONT(MAKESKINSTRRESID3(_T("Font"),lpszPart,lpszState),0,lpszClassName);
						Part.crStateText[j] = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID3(_T("Color"),lpszPart,lpszState),CLR_INVALID,lpszClassName);
					}
				}
			}
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXHypeLinkSkinMap : public UIXHypeLinkSkinThemeImpl<T>, public UIHypeLink2SkinDrawMap<T>
{
	typedef UIXHypeLinkSkinMap<T> This;
	typedef UIXHypeLinkSkinThemeImpl<T> SkinTheme;
	typedef UIHypeLink2SkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkinTheme>
class UIXEditSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UIEditSkinResImpl<T>
{
	typedef UIXEditSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			LPCTSTR lpszClassName = T::GetWndClassName();
			_pUISkinManager->GetRECT(MAKESKINSTRRESID2(_T("Rect"),_T("MARGINS")), &_MaxPartStateInfo.rcMargin, lpszClassName);
			LPCTSTR lpszPasswordChar = _pUISkinManager->GetString(MAKESKINSTRRESID2(_T("Text"),_T("PasswordChar")),0,lpszClassName);
			if (lpszPasswordChar) {
				_MaxPartStateInfo.PasswordChar = *lpszPasswordChar;
			}
			int MaxPart = _countof(_MaxPartStateInfo.Part);
			for (i = 0; i < MaxPart; i++)
			{
				EDIT_PARTSTATEINFO& Part = _MaxPartStateInfo.Part[i];
				if (Part.pszName) {
					LPCTSTR lpszPart = Part.pszName;
					Part.hFont = _pUISkinManager->GetHFONT(MAKESKINSTRRESID2(_T("Font"),lpszPart),0,lpszClassName);
					Part.pImageEdge = _pUISkinManager->GetImage(MAKESKINSTRRESID3(_T("Image"),lpszPart,_T("Edge")),0,lpszClassName);
					{
						int MaxState = _countof(Part.pszStateName);
						for (j = 0; j < MaxState; j++)
						{
							if (!Part.pszStateName[j]) {
								break;
							}
							LPCTSTR lpszState = Part.pszStateName[j];
							Part.pStateImageEdge[j] = _pUISkinManager->GetImage(MAKESKINSTRRESID3(_T("Image"),lpszPart,CString(lpszState)+_T("Edge")),0,lpszClassName);
						}
					}
				}
			}
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXEditSkinMap : public UIXEditSkinThemeImpl<T>, public UIEdit2SkinDrawMap<T>
{
	typedef UIXEditSkinMap<T> This;
	typedef UIXEditSkinThemeImpl<T> SkinTheme;
	typedef UIEdit2SkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkinTheme>
class UIXProgressBarCtrlSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UIProgressBarCtrlSkinResImpl<T>
{
	typedef UIXProgressBarCtrlSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			LPCTSTR lpszClassName = T::GetWndClassName();
			int MaxPart = _countof(_MaxPartStateInfo.Part);
			for (i = 0; i < MaxPart; i++)
			{
				PROGRESSBARCTRL_PARTSTATEINFO& Part = _MaxPartStateInfo.Part[i];
				if (Part.pszName) {
					LPCTSTR lpszPart = Part.pszName;
					{
						int MaxState = _countof(Part.pszStateName);
						for (j = 0; j < MaxState; j++)
						{
							if (!Part.pszStateName[j]) {
								break;
							}
							LPCTSTR lpszState = Part.pszStateName[j];
							Part.pStateImage[j] = _pUISkinManager->GetImage(MAKESKINSTRRESID3(_T("Image"),lpszPart,lpszState),0,lpszClassName);
							Part.crStateColor[j] = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID3(_T("Color"),lpszPart,lpszState),CLR_INVALID,lpszClassName);
						}
					}
				}
			}
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXProgressBarCtrlSkinMap : public UIXProgressBarCtrlSkinThemeImpl<T>, public UIProgressBarCtrlSkinDrawMap<T>
{
	typedef UIXProgressBarCtrlSkinMap<T> This;
	typedef UIXProgressBarCtrlSkinThemeImpl<T> SkinTheme;
	typedef UIProgressBarCtrlSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkinTheme>
class UIXButtonSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UIButtonSkinResImpl<T>
{
	typedef UIXButtonSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		LPCTSTR lpszClassName = T::GetWndClassName();
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			int MaxPart = _countof(_MaxPartStateInfo.Part);
			for (i = 0; i < MaxPart; i++)
			{
				BUTTON_PARTSTATEINFO& Part = _MaxPartStateInfo.Part[i];
				if (Part.pszName) {
					LPCTSTR lpszPart = Part.pszName;
					Part.pImage = _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),lpszPart),0,lpszClassName);
					Part.hFont = _pUISkinManager->GetHFONT(MAKESKINSTRRESID2(_T("Font"),lpszPart),0,lpszClassName);
					Part.crText = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID2(_T("Color"),lpszPart),CLR_INVALID,lpszClassName);
					{
						int MaxState = _countof(Part.pszStateName);
						for (j = 0; j < MaxState; j++)
						{
							if (!Part.pszStateName[j]) {
								break;
							}
							LPCTSTR lpszState = Part.pszStateName[j];
							Part.pStateImage[j] = _pUISkinManager->GetImage(MAKESKINSTRRESID3(_T("Image"),lpszPart,lpszState),0,lpszClassName);
							Part.hStateFont[j] = _pUISkinManager->GetHFONT(MAKESKINSTRRESID3(_T("Font"),lpszPart,lpszState), Part.hFont,lpszClassName);
							Part.crStateText[j] = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID3(_T("Color"),lpszPart,lpszState), Part.crText,lpszClassName);
						}
					}
				}
			}
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}
		CString strName = pT->GetWindowName();
		if (!strName.IsEmpty()) {
			m_PartStateInfo = _MaxPartStateInfo.Part[pT->GetPartID()-1];
			BUTTON_PARTSTATEINFO& Part = m_PartStateInfo;
			if (Part.pszName) {
				LPCTSTR lpszPart = Part.pszName;
				Part.pImage = _pUISkinManager->GetImage(strName+CString(_T("."))+MAKESKINSTRRESID2(_T("Image"),lpszPart),0,lpszClassName);
				Part.hFont = _pUISkinManager->GetHFONT(strName+CString(_T("."))+MAKESKINSTRRESID2(_T("Font"),lpszPart),0,lpszClassName);
				Part.crText = _pUISkinManager->GetCOLORREF(strName+CString(_T("."))+MAKESKINSTRRESID2(_T("Color"),lpszPart),CLR_INVALID,lpszClassName);
				{
					int MaxState = _countof(Part.pszStateName);
					for (j = 0; j < MaxState; j++)
					{
						if (!Part.pszStateName[j]) {
							break;
						}
						LPCTSTR lpszState = Part.pszStateName[j];
						Part.pStateImage[j] = _pUISkinManager->GetImage(strName+CString(_T("."))+MAKESKINSTRRESID3(_T("Image"),lpszPart,lpszState),0,lpszClassName);
						Part.hStateFont[j] = _pUISkinManager->GetHFONT(strName+CString(_T("."))+MAKESKINSTRRESID3(_T("Font"),lpszPart,lpszState), Part.hFont,lpszClassName);
						Part.crStateText[j] = _pUISkinManager->GetCOLORREF(strName+CString(_T("."))+MAKESKINSTRRESID3(_T("Color"),lpszPart,lpszState), Part.crText,lpszClassName);
					}
				}
			}
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXButtonSkinMap : public UIXButtonSkinThemeImpl<T>, public UIButtonSkinDrawMap<T>
{
	typedef UIXButtonSkinMap<T> This;
	typedef UIXButtonSkinThemeImpl<T> SkinTheme;
	typedef UIButtonSkinDrawMap<T> SkinDrawMap;
public:

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkinTheme>
class UIXTabCtrlSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UITabCtrlSkinResImpl<T>
{
	typedef UIXTabCtrlSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			LPCTSTR lpszClassName = T::GetWndClassName();
			int MaxPart = _countof(_MaxPartStateInfo.Part);
			for (i = 0; i < MaxPart; i++)
			{
				TABCTRL_PARTSTATEINFO& Part = _MaxPartStateInfo.Part[i];
				if (Part.pszName) {
					LPCTSTR lpszPart = Part.pszName;
					Part.pImage = _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),lpszPart),0,lpszClassName);
					Part.hFont = _pUISkinManager->GetHFONT(MAKESKINSTRRESID2(_T("Font"),lpszPart),0,lpszClassName);
					Part.crText = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID2(_T("Color"),lpszPart),CLR_INVALID,lpszClassName);
					{
						int MaxState = _countof(Part.pszStateName);
						for (j = 0; j < MaxState; j++)
						{
							if (!Part.pszStateName[j]) {
								break;
							}
							LPCTSTR lpszState = Part.pszStateName[j];
							Part.pStateImage[j] = _pUISkinManager->GetImage(MAKESKINSTRRESID3(_T("Image"),lpszPart,lpszState),0,lpszClassName);
							Part.hStateFont[j] = _pUISkinManager->GetHFONT(MAKESKINSTRRESID3(_T("Font"),lpszPart,lpszState), Part.hFont,lpszClassName);
							Part.crStateText[j] = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID3(_T("Color"),lpszPart,lpszState), Part.crText,lpszClassName);
						}
					}
				}
			}
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXTabCtrlSkinMap : public UIXTabCtrlSkinThemeImpl<T>, public UITabCtrlSkinDrawMap<T>
{
	typedef UIXTabCtrlSkinMap<T> This;
	typedef UIXTabCtrlSkinThemeImpl<T> SkinTheme;
	typedef UITabCtrlSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkinTheme>
class UIXHeaderCtrlSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UIHeaderCtrlSkinResImpl<T>
{
	typedef UIXHeaderCtrlSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			LPCTSTR lpszClassName = T::GetWndClassName();
			int MaxPart = _countof(_MaxPartStateInfo.Part);
			for (i = 0; i < MaxPart; i++)
			{
				HEADERCTRL_PARTSTATEINFO& Part = _MaxPartStateInfo.Part[i];
				if (Part.pszName) {
					LPCTSTR lpszPart = Part.pszName;
					Part.pImage = _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),lpszPart),0,lpszClassName);
					Part.hFont = _pUISkinManager->GetHFONT(MAKESKINSTRRESID2(_T("Font"),lpszPart),0,lpszClassName);
					Part.crText = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID2(_T("Color"),lpszPart),CLR_INVALID,lpszClassName);
					{
						int MaxState = _countof(Part.pszStateName);
						for (j = 0; j < MaxState; j++)
						{
							if (!Part.pszStateName[j]) {
								break;
							}
							LPCTSTR lpszState = Part.pszStateName[j];
							Part.pStateImage[j] = _pUISkinManager->GetImage(MAKESKINSTRRESID3(_T("Image"),lpszPart,lpszState),0,lpszClassName);
							Part.hStateFont[j] = _pUISkinManager->GetHFONT(MAKESKINSTRRESID3(_T("Font"),lpszPart,lpszState), Part.hFont,lpszClassName);
							Part.crStateText[j] = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID3(_T("Color"),lpszPart,lpszState), Part.crText,lpszClassName);
						}
					}
				}
			}
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXHeaderCtrlSkinMap : public UIXHeaderCtrlSkinThemeImpl<T>, public UIHeaderCtrlSkinDrawMap<T>
{
	typedef UIXHeaderCtrlSkinMap<T> This;
	typedef UIXHeaderCtrlSkinThemeImpl<T> SkinTheme;
	typedef UIHeaderCtrlSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkinTheme>
class UIXScrollBarSkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UIScrollBarSkinResImpl<T>
{
	typedef UIXScrollBarSkinThemeImpl<T,TBase> This;
	typedef UIXSkinThemeImpl<T,TBase> Base;
public:
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		int i,j;
		if (_MaxPartStateInfo.nID != _pUISkinManager->GetID()) {
			LPCTSTR lpszClassName = T::GetWndClassName();
			int MaxPart = _countof(_MaxPartStateInfo.Part);
			for (i = 0; i < MaxPart; i++)
			{
				SCROLLBARCTRL_PARTSTATEINFO& Part = _MaxPartStateInfo.Part[i];
				if (Part.pszName) {
					LPCTSTR lpszPart = Part.pszName;
					Part.pImage = _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),lpszPart),0,lpszClassName);
					{
						int MaxState = _countof(Part.pszStateName);
						for (j = 0; j < MaxState; j++)
						{
							if (!Part.pszStateName[j]) {
								break;
							}
							LPCTSTR lpszState = Part.pszStateName[j];
							Part.pStateImage[j] = _pUISkinManager->GetImage(MAKESKINSTRRESID3(_T("Image"),lpszPart,lpszState),0,lpszClassName);
						}
					}
				}
			}
			_MaxPartStateInfo.nID = _pUISkinManager->GetID();
		}

		return Base::OpenThemeData();
	}
	
	/*HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return OpenThemeData();
	}
	
	HRESULT CloseThemeData()
	{
		return Base::CloseThemeData();
	}*/
};

template<class T>
class UIXScrollBarSkinMap : public UIXScrollBarSkinThemeImpl<T>, public UIScrollBarSkinDrawMap<T>
{
	typedef UIXScrollBarSkinMap<T> This;
	typedef UIXScrollBarSkinThemeImpl<T> SkinTheme;
	typedef UIScrollBarSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif//_H_UIXMLSKIN_H_