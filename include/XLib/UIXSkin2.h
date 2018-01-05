#ifndef _H_UIXMLSKIN2_H_
#define _H_UIXMLSKIN2_H_

#include "UILite.h"
#include "UIXSkin.h"

class UILITE_API UIXSkin2Theme : public UIXSkinTheme
{
public:
	HTHEME OpenThemeData(HWND hWnd, LPCWSTR pszClassList);
	HRESULT CloseThemeData(HWND hWnd);
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase=UIXSkin2Theme>
class UIXSysButton2SkinThemeImpl : public UIXSkinThemeImpl<T,TBase>, public UISysButtonSkinResImpl<T>
{
	typedef UIXSysButton2SkinThemeImpl<T,TBase> This;
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
class UIXSysButton2SkinMap : public UIXSysButton2SkinThemeImpl<T>, public UISysButtonSkinDrawMap<T>
{
	typedef UIXSysButton2SkinMap<T> This;
	typedef UIXSysButton2SkinThemeImpl<T> SkinTheme;
	typedef UISysButtonSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIXStatic2SkinMap : public UIXStaticSkinThemeImpl<T>, public UIStaticSkinDrawMap<T>
{
	typedef UIXStatic2SkinMap<T> This;
	typedef UIXStaticSkinThemeImpl<T> SkinTheme;
	typedef UIStaticSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIXHypeLink2SkinMap : public UIXHypeLinkSkinThemeImpl<T>, public UIHypeLink2SkinDrawMap<T>
{
	typedef UIXHypeLink2SkinMap<T> This;
	typedef UIXHypeLinkSkinThemeImpl<T> SkinTheme;
	typedef UIHypeLink2SkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIXEdit2SkinMap : public UIXEditSkinThemeImpl<T>, public UIEdit2SkinDrawMap<T>
{
	typedef UIXEdit2SkinMap<T> This;
	typedef UIXEditSkinThemeImpl<T> SkinTheme;
	typedef UIEdit2SkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIXProgressBarCtrl2SkinMap : public UIXProgressBarCtrlSkinThemeImpl<T>, public UIProgressBarCtrlSkinDrawMap<T>
{
	typedef UIXProgressBarCtrl2SkinMap<T> This;
	typedef UIXProgressBarCtrlSkinThemeImpl<T> SkinTheme;
	typedef UIProgressBarCtrlSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIXButton2SkinMap : public UIXButtonSkinThemeImpl<T>, public UIButtonSkinDrawMap<T>
{
	typedef UIXButton2SkinMap<T> This;
	typedef UIXButtonSkinThemeImpl<T> SkinTheme;
	typedef UIButtonSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIXTabCtrl2SkinMap : public UIXTabCtrlSkinThemeImpl<T>, public UITabCtrlSkinDrawMap<T>
{
	typedef UIXTabCtrl2SkinMap<T> This;
	typedef UIXTabCtrlSkinThemeImpl<T> SkinTheme;
	typedef UITabCtrlSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIXHeaderCtrl2SkinMap : public UIXHeaderCtrlSkinThemeImpl<T>, public UIHeaderCtrlSkinDrawMap<T>
{
	typedef UIXHeaderCtrl2SkinMap<T> This;
	typedef UIXHeaderCtrlSkinThemeImpl<T> SkinTheme;
	typedef UIHeaderCtrlSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIXScrollBar2SkinMap : public UIXScrollBarSkinThemeImpl<T>, public UIScrollBarSkinDrawMap<T>
{
	typedef UIXScrollBar2SkinMap<T> This;
	typedef UIXScrollBarSkinThemeImpl<T> SkinTheme;
	typedef UIScrollBarSkinDrawMap<T> SkinDrawMap;
public:
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDrawMap)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif//_H_UIXMLSKIN2_H_