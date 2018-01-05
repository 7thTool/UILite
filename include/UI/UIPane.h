
#pragma once

#ifndef _H_UIPANE_H_
#define _H_UIPANE_H_

#include "UIWnd.h"

template<class T>
class UINode
{
protected:
	T* m_pPrev;
	T* m_pNext;
	T* m_pChild;
	T* m_pParent;
public:
	UINode() : m_pNext(0),m_pChild(0),m_pPrev(0),m_pParent(0)
	{ 
	}
	~UINode() 
	{ 
		T* pT = static_cast<T*>(this);
		pT->Empty();
		pT->Free();
	}

	//清理子节点
	void Empty()
	{
		while (T* pC = Child()) 
		{
			pC->Empty();
			pC->Free();
		}
	}

	//自由，从节点链中分离出来
	void Free()
	{
		T* pT = static_cast<T*>(this);
		if (pT->m_pParent) {
			if (pT->m_pParent->m_pChild == pT) {
				pT->m_pParent->m_pChild = pT->m_pPrev ? pT->m_pPrev : pT->m_pNext;
			}
			pT->m_pParent = NULL;
		}
		if (pT->m_pPrev || pT->m_pNext) {
			if(pT->m_pPrev) {
				pT->m_pPrev->m_pNext = pT->m_pNext;
			}
			if (pT->m_pNext) {
				pT->m_pNext->m_pPrev = pT->m_pPrev;
			}
			pT->m_pPrev = NULL;
			pT->m_pNext = NULL;
		}
	}

	T* Prev()
	{
		return m_pPrev;
	}

	T* Next()
	{
		return m_pNext;
	}

	BOOL IsFirst()
	{
		return m_pPrev == NULL ? TRUE : FALSE;
	}

	BOOL IsLast()
	{
		return m_pNext == NULL ? TRUE : FALSE;
	}

	T* Child()
	{
		return m_pChild;
	}

	T* Parent()
	{
		return m_pParent;
	}

	T* Root()
	{
		if (m_pParent == NULL) {
			return static_cast<T*>(this);
		}
		return m_pParent->Root();
	}

	BOOL IsRoot()
	{
		return m_pParent == NULL ? TRUE : FALSE;
	}

	BOOL IsLeaf()
	{
		return m_pChild == NULL ? TRUE : FALSE;
	}

	T* Prev(T* pP)
	{
		T* pT = static_cast<T*>(this);
		pP->m_pParent = m_pParent;
		if (m_pPrev) {
			m_pPrev->m_pNext = pP;
		}
		pP->m_pPrev = m_pPrev;
		pP->m_pNext = pT;
		m_pPrev = pP;
		return m_pPrev;
	}

	T* Next(T* pP)
	{
		T* pT = static_cast<T*>(this);
		pP->m_pParent = m_pParent;
		if(m_pNext) {
			m_pNext->m_pPrev = pP;
		}
		pP->m_pPrev = pT;
		pP->m_pNext = m_pNext;
		m_pNext = pP;
		return m_pNext;
	}

	T* Child(T* pP)
	{
		T* pT = static_cast<T*>(this);
		pP->m_pParent = pT;
		if(m_pChild) {
			m_pChild->Prev(pP);
		}
		m_pChild = pP;
		return m_pChild;
	}

	T* First()
	{
		T* pT = static_cast<T*>(this);
		if (m_pPrev) {
			T* pPrev = m_pPrev;
			while(pPrev->m_pPrev)
			{
				pPrev = pPrev->m_pPrev;
			}
			return pPrev;
		}
		return pT;
	}

	T* First(T* pP)
	{
		T* pT = static_cast<T*>(this);
		return pT->First()->Prev(pP);
	}

	T* Last()
	{
		T* pT = static_cast<T*>(this);
		if (m_pNext) {
			T* pNext = m_pNext;
			while(pNext->m_pNext)
			{
				pNext = pNext->m_pNext;
			}
			return pNext;
		}
		return pT;
	}

	T* Last(T* pP)
	{
		T* pT = static_cast<T*>(this);
		return pT->Last()->Next(pP);
	}

	T* FirstChild()
	{
		if (m_pChild) {
			return m_pChild->First();
		}
		return NULL;
	}

	T* FirstChild(T* pP)
	{
		T* pT = static_cast<T*>(this);
		if (m_pChild) {
			m_pChild->First(pP);
		} else {
			return Child(pP);
		}
	}

	T* LastChild()
	{
		if (m_pChild) {
			return m_pChild->Last();
		}
		return NULL;
	}

	T* LastChild(T* pP)
	{
		T* pT = static_cast<T*>(this);
		if (m_pChild) {
			return m_pChild->Last(pP);
		} else {
			return Child(pP);
		}
	}
};

enum
{
	PANEL_STYLE_LR			= 0X00000001,		//左右布局
	PANEL_STYLE_TB			= 0X00000002,		//上下布局

	PANEL_STYLE_LR_SCALE	= 0X00000004,		//左右为自适应
	PANEL_STYLE_TB_SCALE	= 0X00000008,		//上下为自适应
	//自适应
	PANEL_STYLE_SCALE		= (PANEL_STYLE_LR_SCALE|PANEL_STYLE_TB_SCALE),

	PANEL_STYLE_L_SIZED		= 0X00000010,		//左为可调整
	PANEL_STYLE_R_SIZED		= 0X00000020,		//右为可调整
	PANEL_STYLE_T_SIZED		= 0X00000040,		//上为可调整
	PANEL_STYLE_B_SIZED		= 0X00000080,		//下为可调整
	//可调整
	PANEL_STYLE_SIZED		= (PANEL_STYLE_L_SIZED|PANEL_STYLE_R_SIZED|PANEL_STYLE_T_SIZED|PANEL_STYLE_B_SIZED),

	PANEL_STYLE_HIDE		= 0X00004000,		//可见
	PANEL_STYLE_DISABLE		= 0X00008000,		//可用

	PANEL_STYLE_MASK		= 0X0000FFFF,
	PANEL_SCALE_MASK		= 0XFFFF0000,
};

#define PANEL_STYLE_VALUE(x)	((x)&PANEL_STYLE_MASK)
#define PANEL_SCALE_WIDTH(x)	HIBYTE(HIWORD(x))
#define PANEL_SCALE_HEIGHT(x)	LOBYTE(HIWORD(x))

template<class T, class TBase = UIWnd>
class UIPaneT : public TBase, public UINode<T>
{
	typedef UIPaneT<T,TBase> This;
	typedef TBase Base;
	typedef UINode<T> Node;
public:
	static long GetHBorder() { return 1; }
	static long GetVBorder() { return 1; }

protected:
	RECT m_Rect;
	unsigned long m_Style;
public:
	UIPaneT(HWND hWnd = NULL) 
#ifndef _AFX
		: Base(hWnd), Node()
#else
		: Base(), Node()
#endif//
	{
#ifdef _AFX
		Base::m_hWnd = hWnd;
#endif//
		memset(&m_Rect, 0, sizeof(m_Rect));
		m_Style = 0;
	}

	~UIPaneT()
	{ 
		
	}

	void SetStyle(unsigned long Style)
	{
		m_Style = Style;
	}

	long GetStyle()
	{
		return m_Style;
	}

	long ModifyStyle(unsigned long addStyle, unsigned long delStyle)
	{
		m_Style |= addStyle;
		m_Style &= ~delStyle;
		return m_Style;
	}

	void SetRect(int left, int top, int right, int bottom)
	{
		m_Rect.left = left;
		m_Rect.top = top;
		m_Rect.right = right;
		m_Rect.bottom = bottom;
	}

	void SetRect(LPCRECT lpRect) 
	{
		SetRect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	void GetRect(LPRECT lpRect) 
	{
		lpRect->left = m_Rect.left;
		lpRect->top = m_Rect.top;
		lpRect->right = m_Rect.right;
		lpRect->bottom = m_Rect.bottom;
	}

	void Show(BOOL bShow = TRUE)
	{
		T* pT = static_cast<T*>(this);
		pT->ModifyStyle(bShow?0:PANEL_STYLE_HIDE, bShow?PANEL_STYLE_HIDE:0);
		if (*pT) {
			pT->ShowWindow(bShow);
		} else {
			T* pC = pT->FirstChild();
			for (; pC; pC = pC->Next())
			{
				if (*pC) {
					if (pC->GetStyle()&PANEL_STYLE_HIDE) {
					} else {
						pC->ShowWindow(bShow?SW_RESTORE:SW_HIDE);
					}
				}
			}
		}
	}

	void ShowChild(BOOL bShow = TRUE)
	{
		T* pT = static_cast<T*>(this);
		T* pC = pT->FirstChild();
		for (; pC; pC = pC->Next())
		{
			pC->Show(bShow);
		}
	}

	void Enable(BOOL bEnable = TRUE)
	{
		T* pT = static_cast<T*>(this);
		pT->ModifyStyle(bEnable?0:PANEL_STYLE_DISABLE, bEnable?PANEL_STYLE_DISABLE:0);
		if (*pT) {
			pT->EnableWindow(bEnable);
		} else {
			T* pC = pT->FirstChild();
			for (; pC; pC = pC->Next())
			{
				if (*pC) {
					pC->Enable(bEnable);
				}
			}
		}
	}

	T* PaneFromPoint(POINT pt)
	{
		T* pT = static_cast<T*>(this);
		RECT rcC;
		pT->GetRect(&rcC);
		if (::PtInRect(&rcC, pt)) {
			T* pP = NULL;
			T* pC = pT->FirstChild();
			for (; pC; pC = pC->Next())
			{
				pP = pC->PaneFromPoint(pt);
				if (pP) {
					break;
				}
			}
			return (pP ? pP : pT);
		}
		return NULL;
	}

	T* PaneFromWindow(HWND hWnd)
	{
		T* pT = static_cast<T*>(this);
		if ((HWND)*pT != hWnd) {
			T* pP = NULL;
			T* pC = pT->FirstChild();
			for (; pC; pC = pC->Next())
			{
				pP = pC->PaneFromWindow(hWnd);
				if (pP) {
					break;
				}
			}
			return pP;
		} else {
			return pT;
		}
		return NULL;
	}

	T* ChildPaneFromPos(UINT Pos)
	{
		T* pT = static_cast<T*>(this);
		T* pC = pT->FirstChild();
		for (; Pos>0&&pC; --Pos,pC=pC->Next())
		{
			;
		}
		return (Pos>0 ? NULL : pC);
	}

	HWND ChildWindowFromPos(UINT Pos)
	{
		T* pT = static_cast<T*>(this);
		T* pP = pT->ChildPaneFromPos(Pos);
		if (pP) {
			return *pP;
		}
		return NULL;
	}

	T* ChildPaneFromPoint(POINT pt)
	{
		T* pT = static_cast<T*>(this);
		RECT rcC;
		pT->GetRect(&rcC);
		if (::PtInRect(&rcC, pt)) {
			T* pP = NULL;
			T* pC = pT->FirstChild();
			for (; pC; pC = pC->Next())
			{
				pC->GetRect(&rcC);
				if (::PtInRect(&rcC, pt)) {
					pP = pC;
					break;
				}
			}
			return (pP ? pP : pT);
		}
		return NULL;
	}

	HWND ChildWindowFromPoint(POINT pt)
	{
		T* pT = static_cast<T*>(this);
		T* pP = pT->ChildPaneFromPoint(pt);
		if (pP) {
			return *pP;
		}
		return NULL;
	}

	T* ChildPaneFromWindow(HWND hWnd)
	{
		T* pT = static_cast<T*>(this);
		T* pP = NULL;
		T* pC = pT->FirstChild();
		for (; pC; pC = pC->Next())
		{
			if ((HWND)*pC == hWnd) {
				pP = pC;
				break;
			}
		}
		return pP;
		return NULL;
	}

	void Insert(T* pP, T* pN)
	{
		T* pT = static_cast<T*>(this);
		if (pP) {
			RECT rc;
			pT->GetRect(&rc);
			unsigned long Style = pT->GetStyle();
			RECT rcP;
			pP->GetRect(&rcP);
			SIZE szP = {rcP.right-rcP.left+T::GetVBorder(), rcP.bottom-rcP.top+T::GetHBorder()};
			T* pC = NULL;
			RECT rcC = {0};
			SIZE szOffset = {0, 0};
			SIZE szScale = {0, 0};
			SIZE szPad = {0, 0};
			if (Style&PANEL_STYLE_LR) { //水平布局
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					pC->GetRect(&rcC);
					if (pC->GetStyle()&PANEL_STYLE_LR_SCALE) {
						szScale.cx += (rcC.right-rcC.left);
					}
					if(pC->IsLast()) { //最后一个PANE
						szPad.cx = max(0, rc.right-rcC.right);
					}
				}
				ASSERT(szScale.cx>szP.cx);
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					if (pC == pN) {
						T* pPrev = pN->Prev();
						if (!pPrev) {
							rcC = rc;
							rcC.right = rc.left+szP.cx-T::GetVBorder();
						} else {
							rcC.left = rcC.right+T::GetVBorder();
							rcC.right = rcC.left+szP.cx-T::GetVBorder();
						}
						rcC.top = rc.top;
						rcC.bottom = rc.bottom;

						szOffset.cx += szP.cx;
					} 

					pC->GetRect(&rcC);
					::OffsetRect(&rcC, szOffset.cx, 0);
					unsigned long StyleC = pC->GetStyle();
					if (StyleC&PANEL_STYLE_LR_SCALE) {
						LONG cxOffset = ::MulDiv(szP.cx, (rcC.right-rcC.left), szScale.cx);
						szOffset.cx -= cxOffset;
						rcC.right -= cxOffset;
					}
					if(pC->IsLast() && pN) { //最后一个PANE
						rcC.right = rc.right-szPad.cx;
					}
					pC->Relayout(&rcC);
				}

				if(pN) {
					pN->GetRect(&rcC);
					rcC.left = rcC.left-szP.cx;
					rcC.right = rcC.left+(szP.cx-T::GetVBorder());
					pN->Prev(pP);
				} else {
					rcC = rc;
					rcC.left = rc.right-szPad.cx;
					rcC.left = rcC.left-(szP.cx-T::GetVBorder());
					rcC.right = rcC.left+(szP.cx-T::GetVBorder());
					pT->LastChild(pP);
				}
				rcC.top = rc.top;
				rcC.bottom = rc.bottom;
				pP->Relayout(&rcC);

			}
			if (Style&PANEL_STYLE_TB) {
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					pC->GetRect(&rcC);
					if(pC->GetStyle()&PANEL_STYLE_TB_SCALE) {
						szScale.cy += (rcC.bottom-rcC.top);
					}
					if(pC->IsLast()) { //最后一个PANE
						szPad.cy = max(0,rc.bottom-rcC.bottom);
					}
				}
				ASSERT(szScale.cy>szP.cy);
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					if (pC == pN) {
						szOffset.cy += szP.cy;
					}

					pC->GetRect(&rcC);
					::OffsetRect(&rcC, 0, szOffset.cy);
					unsigned long StyleC = pC->GetStyle();
					if (StyleC&PANEL_STYLE_TB_SCALE) {
						LONG cyOffset = ::MulDiv(szP.cy, (rcC.bottom-rcC.top), szScale.cy);
						szOffset.cy -= cyOffset;
						rcC.bottom -= cyOffset;
					}
					if(pC->IsLast() && pN) { //最后一个PANE
						rcC.bottom = rc.bottom-szPad.cy; 
					}
					pC->Relayout(&rcC);
				}

				rcC.left = rc.left;
				rcC.right = rc.right;
				if(pN) {
					pN->GetRect(&rcC);
					rcC.top = rcC.top-szP.cy;
					rcC.bottom = rcC.top+(szP.cy-T::GetHBorder());
					pN->Prev(pP);
				} else {
					rcC = rc;
					rcC.top = rc.bottom-szPad.cy;
					rcC.top = rcC.top-(szP.cy-T::GetVBorder());
					rcC.bottom = rcC.top+(szP.cy-T::GetVBorder());
					pT->LastChild(pP);
				}
				pP->Relayout(&rcC);
			}
		}
	}

	void Remove(T* pP)
	{
		T* pT = static_cast<T*>(this);
		if (pP) {
			RECT rc;
			pT->GetRect(&rc);
			unsigned long Style = pT->GetStyle();
			RECT rcP;
			pP->GetRect(&rcP);
			SIZE szP = {rcP.right-rcP.left+T::GetVBorder(), rcP.bottom-rcP.top+T::GetHBorder()};
			T* pC = NULL;
			RECT rcC = {0};
			SIZE szOffset = {0, 0};
			SIZE szScale = {0, 0};
			SIZE szPad = {0, 0};
			if (Style&PANEL_STYLE_LR) { //水平布局
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					pC->GetRect(&rcC);
					if (pC!=pP) {
						if (pC->GetStyle()&PANEL_STYLE_LR_SCALE) {
							szScale.cx += (rcC.right-rcC.left);
						}
					}
					if(pC->IsLast()) { //最后一个PANE
						szPad.cx = max(0, rc.right-rcC.right);
					}
				}
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					if (pC==pP) {
						szOffset.cx -= szP.cx;
					} else {
						pC->GetRect(&rcC);
						::OffsetRect(&rcC, szOffset.cx, 0);
						unsigned long StyleC = pC->GetStyle();
						if (StyleC&PANEL_STYLE_LR_SCALE) {
							LONG cxOffset = ::MulDiv(szP.cx, (rcC.right-rcC.left), szScale.cx);
							szOffset.cx += cxOffset;
							rcC.right += cxOffset;
						}
						pC->Relayout(&rcC);
					}
				}
				pP->Free();
				pC = pT->LastChild();
				if (pC) {
					pC->GetRect(&rcC);
					rcC.right = rc.right-szPad.cx;
					pC->Relayout(&rcC);
				}
			}
			if (Style&PANEL_STYLE_TB) {
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					pC->GetRect(&rcC);
					if (pC!=pP) {
						if(pC->GetStyle()&PANEL_STYLE_TB_SCALE) {
							szScale.cy += (rcC.bottom-rcC.top);
						}
					}
					if(pC->IsLast()) { //最后一个PANE
						szPad.cy = max(0,rc.bottom-rcC.bottom);
					}
				}
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					if (pC==pP) {
						szOffset.cy -= szP.cy;
					} else {
						pC->GetRect(&rcC);
						::OffsetRect(&rcC, 0, szOffset.cy);
						unsigned long StyleC = pC->GetStyle();
						if (StyleC&PANEL_STYLE_TB_SCALE) {
							LONG cyOffset = ::MulDiv(szP.cy, (rcC.bottom-rcC.top), szScale.cy);
							szOffset.cy += cyOffset;
							rcC.bottom += cyOffset;
						}
						pC->Relayout(&rcC);
					}
				}
				pP->Free();
				pC = pT->LastChild();
				if (pC) {
					pC->GetRect(&rcC);
					rcC.bottom = rc.bottom-szPad.cy; 
					pC->Relayout(&rcC);
				}
			}
		}
	}

	void GetMinMaxInfo(LPMINMAXINFO lpMMInfo)
	{
		T* pT = static_cast<T*>(this);
		ASSERT(lpMMInfo);
		if (pT->m_hWnd) {
			pT->SendMessage(WM_GETMINMAXINFO, (WPARAM)0, (LPARAM)lpMMInfo);
		} 
		unsigned long Style = pT->GetStyle();
		//if (Style&(PANEL_STYLE_SCALE|PANEL_STYLE_SIZED)) {
		//} else {
			T* pC = pT->FirstChild();
			if (pC) {
				SIZE sz = {0,0};
				if (Style&PANEL_STYLE_LR) {
					for (pC = pT->FirstChild(); pC; pC = pC->Next())
					{
						MINMAXINFO MMInfoC = {0};
						pC->GetMinMaxInfo(&MMInfoC);
						sz.cx += MMInfoC.ptMinTrackSize.x;
						sz.cy = max(sz.cy,MMInfoC.ptMinTrackSize.y);
					}
				} 
				if (Style&PANEL_STYLE_TB) {
					for (pC = pT->FirstChild(); pC; pC = pC->Next())
					{
						MINMAXINFO MMInfoC = {0};
						pC->GetMinMaxInfo(&MMInfoC);
						sz.cx = max(sz.cx,MMInfoC.ptMinTrackSize.x);
						sz.cy += MMInfoC.ptMinTrackSize.y;
					}
				}
				lpMMInfo->ptMinTrackSize.x = max(sz.cx,lpMMInfo->ptMinTrackSize.x);
				lpMMInfo->ptMinTrackSize.y = max(sz.cy,lpMMInfo->ptMinTrackSize.y);
			}
			//lpMMInfo->ptMinTrackSize.x = max(m_Rect.right-m_Rect.left,lpMMInfo->ptMinTrackSize.x);
			//lpMMInfo->ptMinTrackSize.y = max(m_Rect.bottom-m_Rect.top,lpMMInfo->ptMinTrackSize.y);
		//}
	}

	void Relayout(LPCRECT lpRect, BOOL bRelayoutWindow = FALSE)
	{
		T* pT = static_cast<T*>(this);
		T* pC = NULL;

		ATLASSERT(lpRect);

		RECT rc;
		pT->GetRect(&rc);
		if (!::EqualRect(lpRect, &rc)) {
			//计算偏移和增量
			RECT rcOffset = { 
				lpRect->left-rc.left,								//偏移CX
				lpRect->top-rc.top,									//偏移CY
				(lpRect->right-lpRect->left)-(rc.right-rc.left),	//新增CX
				(lpRect->bottom-lpRect->top)-(rc.bottom-rc.top)	//新增CY
			};	
			if (rcOffset.left || rcOffset.right || rcOffset.top || rcOffset.bottom) {
				//调整每一个PANE
				pC = pT->FirstChild();
				if (pC) {
					unsigned long Style = pT->GetStyle();
					if (Style&PANEL_STYLE_LR) { //水平布局
						//计算SCALE CX CY
						SIZE szScale = {0, 0};
						SIZE szPad = {0, 0};
						for (pC = pT->FirstChild(); pC; pC = pC->Next())
						{
							RECT rcC;
							pC->GetRect(&rcC);
							if (pC->GetStyle()&PANEL_STYLE_LR_SCALE) {
								szScale.cx += (rcC.right-rcC.left);
							}
							if(pC->IsLast()) { //最后一个PANE
								szPad.cx = max(0, rc.right-rcC.right);
							}
						}
						for (pC = pT->FirstChild(); pC; pC = pC->Next())
						{
							RECT rcC;
							pC->GetRect(&rcC);
							::OffsetRect(&rcC, rcOffset.left, rcOffset.top);
							unsigned long StyleC = pC->GetStyle();
							if (StyleC&PANEL_STYLE_LR_SCALE && szScale.cx) {
								LONG cxOffset = ::MulDiv(rcOffset.right, (rcC.right-rcC.left), szScale.cx);
								rcOffset.left += cxOffset;
								rcC.right += cxOffset;
							}
							if(StyleC&PANEL_STYLE_TB_SCALE) {
								rcC.bottom += rcOffset.bottom;
							}
							if(pC->IsLast()) { //最后一个PANE
								rcC.right = lpRect->right-szPad.cx;
							}
							pC->Relayout(&rcC);
						}
					}
					if (Style&PANEL_STYLE_TB) {
						//计算SCALE CX CY
						SIZE szScale = {0, 0};
						SIZE szPad = {0, 0};
						for (pC = pT->FirstChild(); pC; pC = pC->Next())
						{
							RECT rcC;
							pC->GetRect(&rcC);
							if(pC->GetStyle()&PANEL_STYLE_TB_SCALE) {
								szScale.cy += (rcC.bottom-rcC.top);
							}
							if(pC->IsLast()) { //最后一个PANE
								szPad.cy = max(0,rc.bottom-rcC.bottom);
							}
						}
						for (pC = pT->FirstChild(); pC; pC = pC->Next())
						{
							RECT rcC;
							pC->GetRect(&rcC);
							::OffsetRect(&rcC, rcOffset.left, rcOffset.top);
							unsigned long StyleC = pC->GetStyle();
							if(StyleC&PANEL_STYLE_TB_SCALE && szScale.cy) {
								LONG cyOffset = ::MulDiv(rcOffset.bottom, (rcC.bottom-rcC.top), szScale.cy);
								rcOffset.top += cyOffset;
								rcC.bottom += cyOffset;
							}
							if (StyleC&PANEL_STYLE_LR_SCALE) {
								rcC.right += rcOffset.right;
							}
							if(pC->IsLast()) { //最后一个PANE
								rcC.bottom = lpRect->bottom-szPad.cy; 
							}
							pC->Relayout(&rcC);
						}
					}
				}
			}
			//保存新的RECT
			pT->SetRect(lpRect);
		}

		if (bRelayoutWindow) {
			//获取新的RECT
			pT->GetRect(&rc);
			//根据每个窗格的MINMAXINFO调整窗格尺寸，这里只调整PANE尺寸小于最小尺寸的情况
			pC = pT->FirstChild();
			if (pC) {
				unsigned long Style = pT->GetStyle();
				if (Style&PANEL_STYLE_LR) { //水平布局
					SIZE szMinSize = {0, 0};
					SIZE szOffset = {0, 0};
					SIZE szPad = {rc.right-rc.left, 0};
					//计算高度扩展
					for (pC = pT->FirstChild(); pC; pC = pC->Next()) 
					{
						RECT rcC;
						pC->GetRect(&rcC);
						MINMAXINFO MMInfoC = {0};
						pC->GetMinMaxInfo(&MMInfoC);
						//szMinSize.cx += MMInfoC.ptMinTrackSize.x;
						//szMinSize.cy = max(szMinSize.cy,MMInfoC.ptMinTrackSize.y);
						SIZE szChg = {MMInfoC.ptMinTrackSize.x-(rcC.right-rcC.left), MMInfoC.ptMinTrackSize.y-(rcC.bottom-rcC.top)};
						if (szChg.cy > 0) {
							szOffset.cy = max(szOffset.cy, szChg.cy);
						}
						szPad.cx -= rcC.right-rcC.left;
					}
					//处理水平移动扩展，和处理高度扩展
					SIZE szScale = {(rc.right-rc.left-szPad.cx)-szMinSize.cx, (rc.bottom-rc.top-szPad.cy)-szMinSize.cy};
					for (pC = pT->FirstChild(); pC; pC = pC->Next())
					{
						RECT rcC;
						pC->GetRect(&rcC);
						::OffsetRect(&rcC, szOffset.cx, 0);
						MINMAXINFO MMInfoC = {0};
						pC->GetMinMaxInfo(&MMInfoC);
						SIZE szChg = {MMInfoC.ptMinTrackSize.x-(rcC.right-rcC.left), MMInfoC.ptMinTrackSize.y-(rcC.bottom-rcC.top)};
						if (szChg.cy > 0) {
							rcC.bottom = rcC.bottom + szOffset.cy;
						}
						if (szChg.cx > 0) {
							szOffset.cx += szChg.cx;
							rcC.right = rcC.left + MMInfoC.ptMinTrackSize.x;
						}
						else if (pC->GetStyle()&PANEL_STYLE_LR_SCALE) {
							//自适应的话，本来准备直接缩小szOffset.cy，如果缩小后小于最小大小MMInfoC.ptMinTrackSize.x，就要按最小大小缩小
							if ((rcC.right-rcC.left-szOffset.cx)<MMInfoC.ptMinTrackSize.x) {
								szOffset.cx -= (rcC.right-rcC.left)-MMInfoC.ptMinTrackSize.x;
								rcC.right = rcC.left+MMInfoC.ptMinTrackSize.x;
							} else {
								rcC.right -= szOffset.cx;
							}
						}
						int xScale = (rcC.right-rcC.left)-MMInfoC.ptMinTrackSize.x;
						ASSERT(xScale>=0);
						if (xScale>0) {
							if (xScale>szScale.cx) {
								szOffset.cx -= xScale-szScale.cx;
								rcC.right -= xScale-szScale.cx;
								szScale.cx = 0;
							} else {
								szScale.cx -= xScale;
							}
						}
						if(pC->IsLast()) { //最后一个PANE
							/*if (rcC.right > rc.right) {
							ASSERT(0);
							rcC.right = rc.right;
							}*/
						}
						pC->Relayout(&rcC,TRUE);
					}
				}
				if (Style&PANEL_STYLE_TB) {
					SIZE szMinSize = {0, 0};
					SIZE szOffset = {0, 0};
					SIZE szPad = {0, rc.bottom-rc.top};
					//计算水平扩展
					for (pC = pT->FirstChild(); pC; pC = pC->Next())
					{
						RECT rcC;
						pC->GetRect(&rcC);
						MINMAXINFO MMInfoC = {0};
						pC->GetMinMaxInfo(&MMInfoC);
						szMinSize.cx = max(szMinSize.cx,MMInfoC.ptMinTrackSize.x);
						szMinSize.cy += MMInfoC.ptMinTrackSize.y;
						SIZE szChg = {MMInfoC.ptMinTrackSize.x-(rcC.right-rcC.left), MMInfoC.ptMinTrackSize.y-(rcC.bottom-rcC.top)};
						if (szChg.cx > 0) {
							szOffset.cx = max(szOffset.cx, szChg.cx);
						}
						szPad.cy -= rcC.bottom-rcC.top;
					}
					//处理高度移动扩展，和处理水平扩展
					SIZE szScale = {(rc.right-rc.left-szPad.cx)-szMinSize.cx, (rc.bottom-rc.top-szPad.cy)-szMinSize.cy};
					for (pC = pT->FirstChild(); pC; pC = pC->Next())
					{
						RECT rcC;
						pC->GetRect(&rcC);
						::OffsetRect(&rcC, 0, szOffset.cy);
						MINMAXINFO MMInfoC = {0};
						pC->GetMinMaxInfo(&MMInfoC);
						SIZE szChg = {MMInfoC.ptMinTrackSize.x-(rcC.right-rcC.left), MMInfoC.ptMinTrackSize.y-(rcC.bottom-rcC.top)};
						if (szChg.cx > 0) {
							rcC.right = rcC.right + szOffset.cx;
						}
						if (szChg.cy > 0) {
							szOffset.cy += szChg.cy;
							rcC.bottom = rcC.top + MMInfoC.ptMinTrackSize.y;
						} 
						else if (pC->GetStyle()&PANEL_STYLE_TB_SCALE) {
							//自适应的话，本来准备直接缩小szOffset.cy，如果缩小后小于最小大小MMInfoC.ptMinTrackSize.x，就要按最小大小缩小
							if ((rcC.bottom-rcC.top-szOffset.cy)<MMInfoC.ptMinTrackSize.y) {
								szOffset.cy -= (rcC.bottom-rcC.top)-MMInfoC.ptMinTrackSize.y;
								rcC.bottom = rcC.top+MMInfoC.ptMinTrackSize.y;
							} else {
								rcC.bottom -= szOffset.cy;
							}
						}
						int yScale = (rcC.bottom-rcC.top)-MMInfoC.ptMinTrackSize.y;
						ASSERT(yScale>=0);
						if (yScale>0) {
							if (yScale>szScale.cy) {
								szOffset.cy -= yScale-szScale.cy;
								rcC.bottom -= yScale-szScale.cy;
								szScale.cy = 0;
							} else {
								szScale.cy -= yScale;
							}
						}
						if(pC->IsLast()) { //最后一个PANE

						}
						pC->Relayout(&rcC,TRUE);
					}
				}
			}
			//移动窗口
			if (pT->m_hWnd) {
				//RECT rcWindow;
				//pT->GetWindowRect(&rcWindow);
				//if(!::EqualRect(&rcWindow, &rc)) {
				pT->MoveWindow(rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
				//}
			}
		}
	}

	void RelayoutWindow()
	{
		T* pT = static_cast<T*>(this);
		T* pC = NULL;

		RECT rc;
		pT->GetRect(&rc);
#if 0
		//根据每个窗格的MINMAXINFO调整窗格尺寸，这里只调整PANE尺寸小于最小尺寸的情况
		pC = pT->FirstChild();
		if (pC) {
			unsigned long Style = pT->GetStyle();
			if (Style&PANEL_STYLE_LR) { //水平布局
				SIZE szMinSize = {0, 0};
				SIZE szOffset = {0, 0};
				//计算高度扩展
				for (pC = pT->FirstChild(); pC; pC = pC->Next()) 
				{
					RECT rcC;
					pC->GetRect(&rcC);
					MINMAXINFO MMInfoC = {0};
					pC->GetMinMaxInfo(&MMInfoC);
					szMinSize.cx += MMInfoC.ptMinTrackSize.x;
					szMinSize.cy = max(szMinSize.cy,MMInfoC.ptMinTrackSize.y);
					SIZE szChg = {MMInfoC.ptMinTrackSize.x-(rcC.right-rcC.left), MMInfoC.ptMinTrackSize.y-(rcC.bottom-rcC.top)};
					if (szChg.cy > 0) {
						szOffset.cy = max(szOffset.cy, szChg.cy);
					}
				}
				//处理水平移动扩展，和处理高度扩展
				SIZE szScale = {(rc.right-rc.left)-szMinSize.cx, (rc.bottom-rc.top)-szMinSize.cy};
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					RECT rcC;
					pC->GetRect(&rcC);
					::OffsetRect(&rcC, szOffset.cx, 0);
					MINMAXINFO MMInfoC = {0};
					pC->GetMinMaxInfo(&MMInfoC);
					SIZE szChg = {MMInfoC.ptMinTrackSize.x-(rcC.right-rcC.left), MMInfoC.ptMinTrackSize.y-(rcC.bottom-rcC.top)};
					if (szChg.cx > 0) {
						szOffset.cx += szChg.cx;
						rcC.right = rcC.left + MMInfoC.ptMinTrackSize.x;
					}
					if (szChg.cy > 0) {
						rcC.bottom = rcC.bottom + szOffset.cy;
					}
					if (pC->GetStyle()&PANEL_STYLE_LR_SCALE) {
						//自适应的话，本来准备直接缩小szOffset.cy，如果缩小后小于最小大小MMInfoC.ptMinTrackSize.x，就要按最小大小缩小
						if ((rcC.right-rcC.left-szOffset.cx)<MMInfoC.ptMinTrackSize.x) {
							szOffset.cx -= (rcC.right-rcC.left)-MMInfoC.ptMinTrackSize.x;
							rcC.right = rcC.left+MMInfoC.ptMinTrackSize.x;
						} else {
							rcC.right -= szOffset.cx;
						}
					}
					int xScale = (rcC.right-rcC.left)-MMInfoC.ptMinTrackSize.x;
					ASSERT(xScale>=0);
					if (xScale>0) {
						if (xScale>szScale.cx) {
							szOffset.cx -= xScale-szScale.cx;
							rcC.right -= xScale-szScale.cx;
							szScale.cx = 0;
						} else {
							szScale.cx -= xScale;
						}
					}
					if(pC->IsLast()) { //最后一个PANE
						/*if (rcC.right > rc.right) {
							ASSERT(0);
							rcC.right = rc.right;
						}*/
					}
					pC->Relayout(&rcC,TRUE);
				}
			}
			if (Style&PANEL_STYLE_TB) {
				SIZE szMinSize = {0, 0};
				SIZE szOffset = {0, 0};
				//计算水平扩展
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					RECT rcC;
					pC->GetRect(&rcC);
					MINMAXINFO MMInfoC = {0};
					pC->GetMinMaxInfo(&MMInfoC);
					szMinSize.cx = max(szMinSize.cx,MMInfoC.ptMinTrackSize.x);
					szMinSize.cy += MMInfoC.ptMinTrackSize.y;
					SIZE szChg = {MMInfoC.ptMinTrackSize.x-(rcC.right-rcC.left), MMInfoC.ptMinTrackSize.y-(rcC.bottom-rcC.top)};
					if (szChg.cx > 0) {
						szOffset.cx = max(szOffset.cx, szChg.cx);
					}
				}
				//处理高度移动扩展，和处理水平扩展
				SIZE szScale = {(rc.right-rc.left)-szMinSize.cx, (rc.bottom-rc.top)-szMinSize.cy};
				for (pC = pT->FirstChild(); pC; pC = pC->Next())
				{
					RECT rcC;
					pC->GetRect(&rcC);
					::OffsetRect(&rcC, 0, szOffset.cy);
					MINMAXINFO MMInfoC = {0};
					pC->GetMinMaxInfo(&MMInfoC);
					SIZE szChg = {MMInfoC.ptMinTrackSize.x-(rcC.right-rcC.left), MMInfoC.ptMinTrackSize.y-(rcC.bottom-rcC.top)};
					if (szChg.cx > 0) {
						rcC.right = rcC.right + szOffset.cx;
					}
					if (szChg.cy > 0) {
						szOffset.cy += szChg.cy;
						rcC.bottom = rcC.top + MMInfoC.ptMinTrackSize.y;
					}
					if (pC->GetStyle()&PANEL_STYLE_TB_SCALE) {
						//自适应的话，本来准备直接缩小szOffset.cy，如果缩小后小于最小大小MMInfoC.ptMinTrackSize.x，就要按最小大小缩小
						if ((rcC.bottom-rcC.top-szOffset.cy)<MMInfoC.ptMinTrackSize.y) {
							szOffset.cy -= (rcC.bottom-rcC.top)-MMInfoC.ptMinTrackSize.y;
							rcC.bottom = rcC.top+MMInfoC.ptMinTrackSize.y;
						} else {
							rcC.bottom -= szOffset.cy;
						}
					}
					int yScale = (rcC.bottom-rcC.top)-MMInfoC.ptMinTrackSize.y;
					ASSERT(yScale>=0);
					if (yScale>0) {
						if (yScale>szScale.cy) {
							szOffset.cy -= yScale-szScale.cy;
							rcC.bottom -= yScale-szScale.cy;
							szScale.cy = 0;
						} else {
							szScale.cy -= yScale;
						}
					}
					if(pC->IsLast()) { //最后一个PANE

					}
					pC->Relayout(&rcC,TRUE);
				}
			}
		}
#else
		for (pC = pT->FirstChild(); pC; pC = pC->Next()) 
		{
			pC->RelayoutWindow();
		}
#endif//
		//移动窗口
		if (pT->m_hWnd) {
			//RECT rcWindow;
			//pT->GetWindowRect(&rcWindow);
			//if(!::EqualRect(&rcWindow, &rc)) {
				pT->MoveWindow(rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
			//}
		}
	}
};

template <class T, class TPane>
class UIPaneSplitterImpl
{
	typedef UIPaneSplitterImpl<T,TPane> This;
	typedef TPane Pane;
protected:
	Pane*	m_pP;			//顶级根Pane
	POINT	m_ptOrgin;		//鼠标按下的位置
	POINT	m_ptPreCapture;	//鼠标前一个位置
	POINT	m_ptCapture;	//捕获鼠标位置
	RECT	m_rcCapture;	//边框
	Pane*	m_pP1;			//前一个Pane
	Pane*	m_pP2;			//后一个Pane
	BOOL	m_bCapture;		//是否捕获Border

public:
	UIPaneSplitterImpl()
	{
		m_pP = NULL;
		memset(&m_ptOrgin, 0, sizeof(m_ptOrgin));
		memset(&m_ptPreCapture, 0, sizeof(m_ptPreCapture));
		memset(&m_ptCapture, 0, sizeof(m_ptCapture));
		memset(&m_rcCapture, 0, sizeof(m_rcCapture));
		m_pP1 = NULL;
		m_pP2 = NULL;
		m_bCapture = FALSE;
	}

// 	~UIPaneSplitterImpl()
// 	{
// 	}

	Pane* GetRoot()
	{
		return m_pP;
	}

	Pane* GetPane()
	{
		return m_pP1;
	}

	Pane* SetPane(Pane* pPane = NULL)
	{
		Pane* pOldPane = pPane;
		m_pP1 = pPane;
		if (m_pP1) {
			m_pP2 = m_pP1->Next();
		} else {
			m_pP2 = NULL;
		}
		return pOldPane;
	}

	long GetHBorder()
	{
		return Pane::GetHBorder();
	}

	long GetVBorder()
	{
		return Pane::GetVBorder();
	}

	Pane* PaneFromPoint(POINT pt, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if(pP) {
			return pP->PaneFromPoint(pt);
		}
		return NULL;
	}

	Pane* PaneFromWindow(HWND hWnd, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if(pP) {
			return pP->PaneFromWindow(hWnd);
		}
		return NULL;
	}

	Pane* ChildPaneFromPos(UINT Pos, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if(pP) {
			return pP->ChildPaneFromPos(Pos);
		}
		return NULL;
	}

	HWND ChildWindowFromPos(UINT Pos, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if (pP) {
			return pP->ChildWindowFromPos(Pos);
		}
		return NULL;
	}

	Pane* ChildPaneFromPoint(POINT pt, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if(pP) {
			return pP->ChildPaneFromPoint(pt);
		}
		return NULL;
	}

	HWND ChildWindowFromPoint(POINT pt, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if (pP) {
			return pP->ChildWindowFromPoint(pt);
		}
		return NULL;
	}

	Pane* ChildPaneFromWindow(HWND hWnd, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if(pP) {
			return pP->ChildPaneFromWindow(hWnd);
		}
		return NULL;
	}

	void Insert(Pane* pPane, Pane* pBefore = NULL, Pane* pParent = NULL)
	{
		if (pBefore) {
			pParent = pBefore->Parent();
		} else if (!pParent) {
			pParent = m_pP;
		}
		if (pParent) {
			pParent->Insert(pPane, pBefore);
		} else {
			m_pP = pPane;
			m_pP1 = NULL;
			m_pP2 = NULL;
		}
	}

	void Remove(Pane* pPane)
	{
		if (pPane) {
			Pane* pParent = pPane->Parent();
			if (pParent) {
				pParent->Remove(pPane);
			} else {
				if(m_pP==pPane) {
					m_pP = NULL;
				}
			}
			//if (pPane == m_pP1 || pPane == m_pP2) {
				m_pP1 = NULL;
				m_pP2 = NULL;
			//}
		}
	}

	void Show(BOOL bShow = TRUE, Pane* pPane = NULL)
	{
		if(pPane) {
			pPane->Show(bShow);
		} else {
			if (m_pP) {
				m_pP->ShowChild(bShow);
			}
		}
	}

	void Enable(BOOL bEnable = TRUE, Pane* pPane = NULL)
	{
		if(pPane) {
			pPane->Enable(bEnable);
		} else {
			if (m_pP) {
				m_pP->Enable(bEnable);
			}
		}
	}

	BOOL OnPaneCreate(HWND hwndCtrl)
	{
		return FALSE;
	}

	BOOL OnPaneClose(HWND hwndCtrl)
	{
		return FALSE;
	}

	BOOL OnDrawBorder(BOOL bHor, UINT uMsg = 0)
	{
#ifdef _DEBUG
		T* pT = static_cast<T*>(this);
		if(uMsg == WM_LBUTTONUP) {
			pT->Invalidate();
		}
#endif//
		return FALSE;
	}

	BOOL GetLayoutRect(LPRECT lpRect)
	{
		T* pT = static_cast<T*>(this);
		pT->GetClientRect(lpRect);
		return TRUE;
	}

	void Relayout(LPCRECT lpRect = NULL)
	{
		T* pT = static_cast<T*>(this);
		if (m_pP) {
			if (lpRect) {
				m_pP->Relayout(lpRect, TRUE);
			} else {
				m_pP->RelayoutWindow();
			}
		}
	}

	BEGIN_MSG_MAP_EX(This)
		//MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_MOVE, OnMove)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		//MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		//MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		COMMAND_ID_HANDLER(ID_PANE_CREATE, OnPaneCreate)
		COMMAND_ID_HANDLER(ID_PANE_CLOSE, OnPaneClose)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (lParam != 0) {
			pT->Relayout(NULL);
		}
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (wParam != SIZE_MINIMIZED && lParam != 0) {
			RECT rect;
			pT->GetLayoutRect(&rect);
			pT->Relayout(&rect);
		}
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;

		return 0;
	}

	LRESULT OnPaneCreate(UINT uCode, int nCtrlID, HWND hwndCtrl, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = pT->OnPaneCreate(hwndCtrl);
		return 0;
	}

	LRESULT OnPaneClose(UINT uCode, int nCtrlID, HWND hwndCtrl, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = pT->OnPaneClose(hwndCtrl);
		return 0;
	}

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		POINTSTOPOINT(m_ptOrgin, lParam);
		m_ptPreCapture = m_ptCapture;
		m_ptCapture = m_ptOrgin;
		if(!pT->DoLButtonDown(m_pP)) {
			bHandled = FALSE;
		} 
		return 0;
	}

	LRESULT OnRButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//m_ptPreCapture = m_ptCapture;
		//m_ptCapture = m_ptOrgin;
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_ptPreCapture = m_ptCapture;
		POINTSTOPOINT(m_ptCapture, lParam);
		if(!pT->DoLButtonUp(m_pP)) {
			bHandled = FALSE;
		}
		return 0;
	}

	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_ptPreCapture = m_ptCapture;
		POINTSTOPOINT(m_ptCapture, lParam);
		if(!pT->DoMouseMove(m_pP)) {
			bHandled = FALSE;
		}
		return 0;
	}

	BOOL DoDrawBorder(BOOL bHor, UINT uMsg = 0)
	{
		T* pT = static_cast<T*>(this);
		if(pT->OnDrawBorder(bHor, uMsg)) {
			return TRUE;
		}
		switch(uMsg)
		{
		case WM_LBUTTONDOWN:
			{
				HDC hdc = ::GetDC(NULL);
				int nRop2Old = ::SetROP2(hdc, R2_NOTXORPEN);
				RECT rcBorder = m_rcCapture;
				pT->ClientToScreen(&rcBorder);
				//POINT ptPreCapture = m_ptPreCapture;
				//pT->ClientToScreen(&ptPreCapture);
				POINT ptCapture = m_ptCapture;
				pT->ClientToScreen(&ptCapture);
				if (bHor) {
					::MoveToEx(hdc, ptCapture.x, rcBorder.top, NULL);
					::LineTo(hdc, ptCapture.x, rcBorder.bottom);
				} else {
					::MoveToEx(hdc, rcBorder.left, ptCapture.y, NULL);
					::LineTo(hdc, rcBorder.right, ptCapture.y);
				}
				::SetROP2(hdc, nRop2Old);
				::ReleaseDC(NULL, hdc);
			}
			break;
		case WM_LBUTTONUP:
			{
				HDC hdc = ::GetDC(NULL);
				int nRop2Old = ::SetROP2(hdc, R2_NOTXORPEN);
				RECT rcBorder = m_rcCapture;
				pT->ClientToScreen(&rcBorder);
				POINT ptPreCapture = m_ptPreCapture;
				pT->ClientToScreen(&ptPreCapture);
				//POINT ptCapture = m_ptCapture;
				//pT->ClientToScreen(&ptCapture);
				if (bHor) {
					::MoveToEx(hdc, ptPreCapture.x, rcBorder.top, NULL);
					::LineTo(hdc, ptPreCapture.x, rcBorder.bottom);
				} else {
					::MoveToEx(hdc, rcBorder.left, ptPreCapture.y, NULL);
					::LineTo(hdc, rcBorder.right, ptPreCapture.y);
				}
				::SetROP2(hdc, nRop2Old);
				::ReleaseDC(NULL, hdc);

				pT->Invalidate();
			}
			break;
		case WM_MOUSEMOVE:
			{
				HDC hdc = ::GetDC(NULL);
				int nRop2Old = ::SetROP2(hdc, R2_NOTXORPEN);
				RECT rcBorder = m_rcCapture;
				pT->ClientToScreen(&rcBorder);
				POINT ptPreCapture = m_ptPreCapture;
				pT->ClientToScreen(&ptPreCapture);
				POINT ptCapture = m_ptCapture;
				pT->ClientToScreen(&ptCapture);
				if (bHor) {
					::MoveToEx(hdc, ptPreCapture.x, rcBorder.top, NULL);
					::LineTo(hdc, ptPreCapture.x, rcBorder.bottom);
					::MoveToEx(hdc, ptCapture.x, rcBorder.top, NULL);
					::LineTo(hdc, ptCapture.x, rcBorder.bottom);
				} else {
					::MoveToEx(hdc, rcBorder.left, ptPreCapture.y, NULL);
					::LineTo(hdc, rcBorder.right, ptPreCapture.y);
					::MoveToEx(hdc, rcBorder.left, ptCapture.y, NULL);
					::LineTo(hdc, rcBorder.right, ptCapture.y);
				}
				::SetROP2(hdc, nRop2Old);
				::ReleaseDC(NULL, hdc);
			}
			break;
		}
		return TRUE;
	}

	BOOL DoLButtonDown(Pane* pC)
	{
		T* pT = static_cast<T*>(this);
		if (pC == NULL) {
			return FALSE;
		}

		RECT rcC;
		pC->GetRect(&rcC);
		if (::PtInRect(&rcC, m_ptCapture)) {
			if (pC->Child()) {
				return DoLButtonDown(pC->FirstChild());
			} else {
				m_pP1 = pC;
				m_pP2 = pC->Next();
				//m_bCapture = FALSE;
				return FALSE;
			}
		}

		Pane* pNextC = pC->Next();
		if (pNextC) {
			unsigned long Style = pC->Parent()->GetStyle();
			unsigned long Style1 = pC->GetStyle();
			unsigned long Style2 = pNextC->GetStyle();
			if (((Style&PANEL_STYLE_LR) && (Style1&PANEL_STYLE_R_SIZED) && (Style2&PANEL_STYLE_L_SIZED)) ||
				((Style&PANEL_STYLE_TB) && (Style1&PANEL_STYLE_B_SIZED) && (Style2&PANEL_STYLE_T_SIZED))) {
					RECT rcNextC;
					pNextC->GetRect(&rcNextC);
					if (Style&PANEL_STYLE_LR) {
						m_rcCapture.left = rcC.right;
						m_rcCapture.top = rcC.top;
						m_rcCapture.right = rcNextC.left;
						m_rcCapture.bottom = rcNextC.bottom;
					} else {
						m_rcCapture.left = rcC.left;
						m_rcCapture.top = rcC.bottom;
						m_rcCapture.right = rcNextC.right;
						m_rcCapture.bottom = rcNextC.top;
					}
					if (::PtInRect(&m_rcCapture, m_ptCapture)) {
						pT->SetCapture();
						m_bCapture = TRUE;
						m_pP1 = pC;
						m_pP2 = pNextC;
						if (Style&PANEL_STYLE_LR) {
							SetCursor(LoadCursor(NULL, STRINGorID(IDC_SIZEWE)));
							DoDrawBorder(TRUE, WM_LBUTTONDOWN);
						} else {
							SetCursor(LoadCursor(NULL, STRINGorID(IDC_SIZENS)));
							DoDrawBorder(FALSE, WM_LBUTTONDOWN);
						}
						return TRUE;
					} 
			}
		}
		return DoLButtonDown(pNextC);
	}

	BOOL DoLButtonUp(Pane* pC)
	{
		T* pT = static_cast<T*>(this);
		if (m_bCapture) {
			unsigned long Style = m_pP1->Parent()->GetStyle();
			DoDrawBorder(Style&PANEL_STYLE_LR ? TRUE : FALSE, WM_LBUTTONUP);
			
			RECT rcP;
			m_pP1->Parent()->GetRect(&rcP);
			RECT rcP1;
			m_pP1->GetRect(&rcP1);
			RECT rcP2;
			if (Style&PANEL_STYLE_LR) {
				long cxOffset = m_ptCapture.x - m_ptOrgin.x;
				if (cxOffset > 0) { //向右
					if (m_pP2) {
						m_pP2->GetRect(&rcP2);
						if (cxOffset > (rcP2.right-rcP2.left)) {
							cxOffset = (rcP2.right-rcP2.left);
						}
						rcP2.left += cxOffset;
					} else {
						if (cxOffset > (rcP.right - m_ptOrgin.x)) {
							cxOffset = (rcP.right - m_ptOrgin.x);
						}
					}
					rcP1.right += cxOffset;
					m_pP1->Relayout(&rcP1,TRUE);
					if(m_pP2) {
						m_pP2->Relayout(&rcP2,TRUE);
					}
				} else { //向左
					if (-cxOffset > (rcP1.right - rcP1.left)) {
						cxOffset = -(rcP1.right - rcP1.left);
					}
					if (m_pP2) {
						m_pP2->GetRect(&rcP2);
						rcP2.left += cxOffset;
					}
					if(m_pP2) {
						m_pP2->Relayout(&rcP2,TRUE);
					}
					rcP1.right += cxOffset;
					m_pP1->Relayout(&rcP1,TRUE);
				}
			} else {
				long cyOffset = m_ptCapture.y - m_ptOrgin.y;
				if (cyOffset > 0) { //向下
					if (m_pP2) {
						m_pP2->GetRect(&rcP2);
						if (cyOffset > (rcP2.bottom - rcP2.top)) {
							cyOffset = (rcP2.bottom - rcP2.top);
						}
						rcP2.top += cyOffset;
					} else {
						if (cyOffset > (rcP.bottom - m_ptOrgin.y)) {
							cyOffset = (rcP.bottom - m_ptOrgin.y);
						}
					}
					rcP1.bottom += cyOffset;
					m_pP1->Relayout(&rcP1,TRUE);
					if(m_pP2) {
						m_pP2->Relayout(&rcP2,TRUE);
					}
				} else { //向上
					if (-cyOffset > (rcP1.bottom - rcP1.top)) {
						cyOffset = -(rcP1.bottom - rcP1.top);
					}
					if (m_pP2) {
						m_pP2->GetRect(&rcP2);
						rcP2.top += cyOffset;
					}
					if(m_pP2) {
						m_pP2->Relayout(&rcP2,TRUE);
					}
					rcP1.bottom += cyOffset;
					m_pP1->Relayout(&rcP1,TRUE);
				}
			}
			m_pP1 = NULL;
			m_pP2 = NULL;
			m_bCapture = FALSE;
			pT->ReleaseCapture();
			return TRUE;
		}
		return FALSE;
	}

	BOOL DoMouseMove(Pane* pC)
	{
		T* pT = static_cast<T*>(this);
		if (m_bCapture) {
			unsigned long Style = m_pP1->Parent()->GetStyle();
			DoDrawBorder(Style&PANEL_STYLE_LR ? TRUE : FALSE, WM_MOUSEMOVE);

			return TRUE;
		} 

		if (pC == NULL) {
			return FALSE;
		}

		RECT rcC;
		pC->GetRect(&rcC);
		if (::PtInRect(&rcC, m_ptCapture)) {
			if (pC->Child()) {
				return DoMouseMove(pC->FirstChild());
			} else {
				m_pP1 = pC;
				m_pP2 = pC->Next();
				//m_bCapture = FALSE;
				return FALSE;
			}
		}

		Pane* pNextC = pC->Next();
		if (pNextC) {
			unsigned long Style = pC->Parent()->GetStyle();
			unsigned long Style1 = pC->GetStyle();
			unsigned long Style2 = pNextC->GetStyle();
			if (((Style&PANEL_STYLE_LR) && (Style1&PANEL_STYLE_R_SIZED) && (Style2&PANEL_STYLE_L_SIZED)) ||
				((Style&PANEL_STYLE_TB) && (Style1&PANEL_STYLE_B_SIZED) && (Style2&PANEL_STYLE_T_SIZED))) {
				RECT rcNextC;
				pNextC->GetRect(&rcNextC);
				if (Style&PANEL_STYLE_LR) {
					m_rcCapture.left = rcC.right;
					m_rcCapture.top = rcC.top;
					m_rcCapture.right = rcNextC.left;
					m_rcCapture.bottom = rcNextC.bottom;
				} else {
					m_rcCapture.left = rcC.left;
					m_rcCapture.top = rcC.bottom;
					m_rcCapture.right = rcNextC.right;
					m_rcCapture.bottom = rcNextC.top;
				}
				if (::PtInRect(&m_rcCapture, m_ptCapture)) {
					if (Style&PANEL_STYLE_LR) {
						SetCursor(LoadCursor(NULL, STRINGorID(IDC_SIZEWE)));
					} else {
						SetCursor(LoadCursor(NULL, STRINGorID(IDC_SIZENS)));
					}
					return TRUE;
				}
			}
		}
		return DoMouseMove(pNextC);
	}
};

#endif//_H_UIPANE_H_