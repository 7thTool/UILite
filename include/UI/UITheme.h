
#pragma once

#ifndef _H_UITHEME_H_
#define _H_UITHEME_H_

#include "UIBase.h"
#include <wtl/atltheme.h>

//#include <dwmapi.h>
//#pragma comment(lib, "dwmapi.lib")

class UITheme : public WTL::CTheme
{
	typedef UITheme This;
	typedef WTL::CTheme Base;
public:
	UITheme(HTHEME hTheme = NULL) : WTL::CTheme(hTheme)
	{	
	}
};

template <class T, class TBase = UITheme>
class UIThemeImpl : public WTL::CThemeImpl<T,TBase>
{
	typedef UIThemeImpl<T> This;
	typedef WTL::CThemeImpl<T,TBase> Base;
public:
	/*UIThemeImpl()
	{
		USES_CONVERSION;
		SetThemeClassList(T2CW(T::GetWndClassName()));
	}
	
	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsThemeNull()) {
			USES_CONVERSION;
			return OpenThemeData(m_lpstrThemeClassList ? T2CW(T::GetWndClassName()) : m_lpstrThemeClassList);
		}
		return m_hTheme;
	}
	
	HTHEME OpenThemeData(LPCWSTR pszClassList)
	{
		if(!SetThemeClassList(pszClassList))
			return NULL;
		return Base::OpenThemeData();
	}

	static int PartID2Type(LPCWSTR lpszThemeClassList, int nPartID)
	{
		if (wcsicmp(L"BUTTON", lpszThemeClassList) == 0) {
			switch (nPartID)
			{
			case BP_CHECKBOX:
			case BP_RADIOBUTTON:
			case BP_GROUPBOX:
			case BP_PUSHBUTTON:
				return DFC_BUTTON;
				break;
			}
		}
		return 0;
	}

	static int PartStateID2State(LPCWSTR lpszThemeClassList, int nPartID, int nStateID)
	{
		int nState = DFCS_TRANSPARENT;
		if (wcsicmp(L"BUTTON", lpszThemeClassList) == 0) {
			switch (nPartID)
			{
			case BP_CHECKBOX:
				{
					nState = DFCS_BUTTONCHECK | DFCS_TRANSPARENT;
					switch(nStateID)
					{
					case CBS_CHECKEDNORMAL:
						nState |= DFCS_CHECKED;
					case CBS_UNCHECKEDNORMAL:
						break;
					case CBS_CHECKEDDISABLED:
						nState |= DFCS_CHECKED;
					case CBS_UNCHECKEDDISABLED:
						nState |= DFCS_INACTIVE;
						break;
					case CBS_CHECKEDPRESSED:
						nState |= DFCS_CHECKED;
					case CBS_UNCHECKEDPRESSED:
						nState |= DFCS_PUSHED;
						break;
					case CBS_CHECKEDHOT:
						nState |= DFCS_CHECKED;
					case CBS_UNCHECKEDHOT:
						nState |= DFCS_HOT;
						break;
					}
				}
				break;
			case BP_RADIOBUTTON:
				{
					nState = DFCS_BUTTONRADIO | DFCS_TRANSPARENT;
					switch(nStateID)
					{
					case RBS_CHECKEDNORMAL:
						nState |= DFCS_CHECKED;
					case RBS_UNCHECKEDNORMAL:
						break;
					case RBS_CHECKEDDISABLED:
						nState |= DFCS_CHECKED;
					case RBS_UNCHECKEDDISABLED:
						nState |= DFCS_INACTIVE;
						break;
					case RBS_CHECKEDPRESSED:
						nState |= DFCS_CHECKED;
					case RBS_UNCHECKEDPRESSED:
						nState |= DFCS_PUSHED;
						break;
					case RBS_CHECKEDHOT:
						nState |= DFCS_CHECKED;
					case RBS_UNCHECKEDHOT:
						nState |= DFCS_HOT;
						break;
					}
				}
				break;
			case BP_GROUPBOX:
				{
					nState = DFCS_TRANSPARENT;
				}
				break;
			case BP_PUSHBUTTON:
				{
					nState = DFCS_BUTTONPUSH | DFCS_TRANSPARENT;
					switch(nStateID)
					{
					case PBS_NORMAL:
						break;
					case PBS_DISABLED:
						nState |= DFCS_INACTIVE;
						break;
					case PBS_PRESSED:
						nState |= DFCS_PUSHED;
						break;
					case PBS_HOT:
						nState |= DFCS_HOT;
						break;
					}
				}
				break;
			}
		}
		return nState;
	}

	HRESULT DrawThemeBackground(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, LPCRECT pClipRect = NULL)
	{
		T* pT = static_cast<T*>(this);
		if(!pT->OpenThemeData()) {
			::DrawFrameControl(hDC, (LPRECT)pRect, 
				PartID2Type(GetThemeClassList(),nPartID), PartStateID2State(GetThemeClassList(),nPartID, nStateID));
			return S_OK;
		}
		return Base::DrawThemeBackground(hDC, nPartID, nStateID, pRect, pClipRect);
	}
	
	HRESULT DrawThemeBackgroundEx(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, const DTBGOPTS* pOptions = NULL)
	{
		T* pT = static_cast<T*>(this);
		if(!pT->OpenThemeData()) {
			::DrawFrameControl(hDC, (LPRECT)pRect, 
				PartID2Type(GetThemeClassList(),nPartID), PartStateID2State(GetThemeClassList(),nPartID, nStateID));
			return S_OK;
		}
		return Base::DrawThemeBackgroundEx(hDC, nPartID, nStateID, pRect, pOptions);
	}*/
};

#endif//_H_UITHEME_H_