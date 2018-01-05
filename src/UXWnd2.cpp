#include "stdafx.h"
#include "UXWnd2.h"

#include "UXWnd.h"
#include "UIXCtrl2.h"

IMPLEMENT_DYNCCREATE_FACTORY(UXWnd2)

class UXWnd2Creater : public UXWnd2Map<UXWnd2Creater>
{

};

UXWnd2Creater _UXWnd2Creater;

HWND UXWnd2Factory::CreateControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag)
{
	HWND hWndCtrl = _UXWnd2Creater.CreateControl(hWndParent, lpszWndClass, lpszCtrlName, nID, lpszXml, XmlFlag);
	if (!hWndCtrl) {
		hWndCtrl = UXWndFactory::CreateControl(hWndParent, lpszWndClass, lpszCtrlName, nID, lpszXml, XmlFlag);
	}
	return hWndCtrl;
}

class UXStatic2
	: public UXStatic2Impl<UXStatic2>
	, public UIStatic2Map<UXStatic2>
	, public UIXStaticSkinMap<UXStatic2>
{
	typedef UXStatic2 This;
	typedef UXStatic2Impl<UXStatic2> Base;
	typedef UIStatic2Map<UXStatic2> FuncMap;
	typedef UIXStaticSkinMap<UXStatic2> SkinMap;
public:
	DECLARE_DYNCREATE_WND_OBJECTER(UXStatic2,UXWnd2)

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXStatic2,UXWnd2)

class UXHypeLink2
	: public UXCtrl2Impl<UXHypeLink2>
	, public UIHypeLink2Map<UXHypeLink2>
	, public UIXHypeLinkSkinMap<UXHypeLink2>
{
	typedef UXHypeLink2 This;
	typedef UXCtrl2Impl<UXHypeLink2> Base;
	typedef UIHypeLink2Map<UXHypeLink2> FuncMap;
	typedef UIXHypeLinkSkinMap<UXHypeLink2> SkinMap;
public:
	DECLARE_XMLWND_CLASS(_T("HypeLink"))
	DECLARE_DYNCREATE_WND_OBJECTER(UXHypeLink2,UXWnd2)

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_STRING_HANDLER(_T("hypelink"), SetHypeLink)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXHypeLink2,UXWnd2)

class UXEdit2 
	: public UXEdit2Impl<UXEdit2>
	, public UIEdit2Map<UXEdit2>
	, public UIXEdit2SkinMap<UXEdit2>
{
	typedef UXEdit2 This;
	typedef UXEdit2Impl<UXEdit2> Base;
	typedef UIEdit2Map<UXEdit2> FuncMap;
	typedef UIXEdit2SkinMap<UXEdit2> SkinMap;
public:
	DECLARE_DYNCREATE_WND_OBJECTER(UXEdit2,UXWnd2)

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXEdit2,UXWnd2)

class UXProgressBarCtrl2 
	: public UXProgressBarCtrl2Impl<UXProgressBarCtrl2>
	, public UIProgressBarCtrl2Map<UXProgressBarCtrl2>
	, public UIXProgressBarCtrlSkinMap<UXProgressBarCtrl2>
{
	typedef UXProgressBarCtrl2 This;
	typedef UXProgressBarCtrl2Impl<UXProgressBarCtrl2> Base;
	typedef UIProgressBarCtrl2Map<UXProgressBarCtrl2> FuncMap;
	typedef UIXProgressBarCtrlSkinMap<UXProgressBarCtrl2> SkinMap;
public:
	DECLARE_DYNCREATE_WND_OBJECTER(UXProgressBarCtrl2,UXWnd2)

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXProgressBarCtrl2,UXWnd2)

class UXButton2 
	: public UXButton2Impl<UXButton2>
	, public UIButton2Map<UXButton2>
	, public UIXButtonSkinMap<UXButton2>
{
	typedef UXButton2 This;
	typedef UXButton2Impl<UXButton2> Base;
	typedef UIXButtonSkinMap<UXButton2> SkinMap;
	typedef UIButton2Map<UXButton2> FuncMap;
public:
	DECLARE_DYNCREATE_WND_OBJECTER(UXButton2,UXWnd2)

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXButton2,UXWnd2)

class UXSysButton2
	: public UXButton2Impl<UXSysButton2>
	, public UISysButton2Map<UXSysButton2>
	, public UIXSysButtonSkinMap<UXSysButton2>
{
	typedef UXSysButton2 This;
	typedef UXButton2Impl<UXSysButton2> Base;
	typedef UIXSysButtonSkinMap<UXSysButton2> SkinMap;
	typedef UISysButton2Map<UXSysButton2> FuncMap;
public:
	DECLARE_XMLWND_CLASS(_T("SYSBUTTON"))
	DECLARE_DYNCREATE_WND_OBJECTER(UXSysButton2,UXWnd2)

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXSysButton2,UXWnd2)

class UXTabCtrl2 
	: public UXTabCtrl2Impl<UXTabCtrl2>
	, public UITabCtrl2Map<UXTabCtrl2>
	, public UIXTabCtrlSkinMap<UXTabCtrl2>
{
	typedef UXTabCtrl2 This;
	typedef UXTabCtrl2Impl<UXTabCtrl2> Base;
	typedef UITabCtrl2Map<UXTabCtrl2> FuncMap;
	typedef UIXTabCtrlSkinMap<UXTabCtrl2> SkinMap;
public:
	DECLARE_DYNCREATE_WND_OBJECTER(UXTabCtrl2,UXWnd2)

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXTabCtrl2,UXWnd2)

class UXScrollBar2 
	: public UXScrollBar2Impl<UXScrollBar2>
	, public UIScrollBar2Map<UXScrollBar2>
	, public UIXScrollBarSkinMap<UXScrollBar2>
{
	typedef UXScrollBar2 This;
	typedef UXScrollBar2Impl<UXScrollBar2> Base;
	typedef UIScrollBar2Map<UXScrollBar2> FuncMap;
	typedef UIXScrollBarSkinMap<UXScrollBar2> SkinMap;
public:
	DECLARE_DYNCREATE_WND_OBJECTER(UXScrollBar2,UXWnd2)

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXScrollBar2,UXWnd2)


namespace UITextServ
{
#define cInitTextMax ((32*1024)-1)

	EXTERN_C const IID IID_ITextServices = { // 8d33f740-cf58-11ce-a89d-00aa006cadc5
		0x8d33f740,
		0xcf58,
		0x11ce,
		{0xa8, 0x9d, 0x00, 0xaa, 0x00, 0x6c, 0xad, 0xc5}
	};

	EXTERN_C const IID IID_ITextHost = { /* c5bdd8d0-d26e-11ce-a89e-00aa006cadc5 */
		0xc5bdd8d0,
		0xd26e,
		0x11ce,
		{0xa8, 0x9e, 0x00, 0xaa, 0x00, 0x6c, 0xad, 0xc5}
	};

#ifndef LY_PER_INCH
#define LY_PER_INCH 1440
#endif//

#ifndef HIMETRIC_PER_INCH
#define HIMETRIC_PER_INCH 2540
#endif//

#include <textserv.h>

	template<class T>
	class UITextHost : public ITextHost
	{
	private:
		T *m_pT;
		ULONG	cRefs;					// Reference Count
		ITextServices	*pserv;		    // pointer to Text Services object
		// Properties

		DWORD		dwStyle;				// style bits

		unsigned	fEnableAutoWordSel	:1;	// enable Word style auto word selection?
		unsigned	fWordWrap			:1;	// Whether control should word wrap
		unsigned	fAllowBeep			:1;	// Whether beep is allowed
		unsigned	fRich				:1;	// Whether control is rich text
		unsigned	fSaveSelection		:1;	// Whether to save the selection when inactive
		unsigned	fInplaceActive		:1; // Whether control is inplace active
		unsigned	fTransparent		:1; // Whether control is transparent
		unsigned	fTimer				:1;	// A timer is set
		unsigned    fCaptured           :1;
		unsigned    fShowCaret          :1;
		unsigned    fNeedFreshCaret     :1; // 修正改变大小后点击其他位置原来光标不能消除的问题

		INT         iCaretWidth;
		INT         iCaretHeight;
		INT         iCaretLastWidth;
		INT         iCaretLastHeight;
		LONG		lSelBarWidth;			// Width of the selection bar
		LONG  		cchTextMost;			// maximum text size
		DWORD		dwEventMask;			// DoEvent mask to pass on to parent window
		LONG		icf;
		LONG		ipf;
		RECT		rcClient;				// Client Rect for this control
		SIZEL		sizelExtent;			// Extent array
		CHARFORMAT2W cf;					// Default character format
		PARAFORMAT2	pf;					    // Default paragraph format
		LONG		laccelpos;				// Accelerator position
		WCHAR		chPasswordChar;		    // Password character
	public:
		UITextHost(T* pT, const CREATESTRUCT *pcs):m_pT(pT)
		{
			::ZeroMemory(&cRefs, sizeof(UITextHost) - offsetof(UITextHost, cRefs));
			cchTextMost = cInitTextMax;
			laccelpos = -1;

			IUnknown *pUnk;
			HRESULT hr;

			// Initialize Reference count
			cRefs = 1;

			// Create and cache CHARFORMAT for this control
			if(FAILED(InitDefaultCharFormat(&cf, m_pT->GetFont(), GetSysColor(COLOR_WINDOWTEXT))))
				goto err;

			// Create and cache PARAFORMAT for this control
			if(FAILED(InitDefaultParaFormat(&pf)))
				goto err;

			// edit controls created without a window are multiline by default
			// so that paragraph formats can be
			dwStyle = ES_MULTILINE;

			// edit controls are rich by default
			fRich = true;

			cchTextMost = m_pT->GetLimitText();

			if (pcs )
			{
				dwStyle = pcs->style;

				if ( !(dwStyle & (ES_AUTOHSCROLL | WS_HSCROLL)) )
				{
					fWordWrap = TRUE;
				}
			}

			if( !(dwStyle & ES_LEFT) )
			{
				if(dwStyle & ES_CENTER)
					pf.wAlignment = PFA_CENTER;
				else if(dwStyle & ES_RIGHT)
					pf.wAlignment = PFA_RIGHT;
			}

			fInplaceActive = TRUE;

			// Create Text Services component
			//if(FAILED(CreateTextServices(NULL, this, &pUnk)))
			//    goto err;

			PCreateTextServices TextServicesProc;
			HMODULE hmod = LoadLibrary(_T("msftedit.dll"));
			if (hmod)
			{
				TextServicesProc = (PCreateTextServices)GetProcAddress(hmod,"CreateTextServices");
			}

			if (TextServicesProc)
			{
				HRESULT hr = TextServicesProc(NULL, this, &pUnk);
			}

			hr = pUnk->QueryInterface(IID_ITextServices,(void **)&pserv);

			// Whether the previous call succeeded or failed we are done
			// with the private interface.
			pUnk->Release();

			if(FAILED(hr))
			{
				goto err;
			}

			// Set window text
			if(pcs && pcs->lpszName)
			{
#ifdef _UNICODE		
				if(FAILED(pserv->TxSetText((TCHAR *)pcs->lpszName)))
					goto err;
#else
				size_t iLen = _tcslen(pcs->lpszName);
				LPWSTR lpText = new WCHAR[iLen + 1];
				::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
				::MultiByteToWideChar(CP_ACP, 0, pcs->lpszName, -1, (LPWSTR)lpText, iLen) ;
				if(FAILED(pserv->TxSetText((LPWSTR)lpText))) {
					delete[] lpText;
					goto err;
				}
				delete[] lpText;
#endif
			}
			//
err:
			if (pserv) {
				pserv->Release();
				pserv = NULL;
			}
		}

		~UITextHost()
		{
			if(pserv) {
				pserv->OnTxInPlaceDeactivate();
				pserv->Release();
				pserv = NULL;
			}
		}

		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject)
		{
			HRESULT hr = E_NOINTERFACE;
			*ppvObject = NULL;

			if (IsEqualIID(riid, IID_IUnknown) 
				|| IsEqualIID(riid, IID_ITextHost)) 
			{
				AddRef();
				*ppvObject = (ITextHost *) this;
				hr = S_OK;
			}

			return hr;
		}

		virtual ULONG STDMETHODCALLTYPE AddRef(void)
		{
			return ++cRefs;
		}

		virtual ULONG STDMETHODCALLTYPE Release(void)
		{
			ULONG c_Refs = --cRefs;

			if (c_Refs == 0)
			{
				delete this;
			}

			return c_Refs;
		}

		// Convert Pixels on the X axis to Himetric
		LONG DXtoHimetricX(LONG dx, LONG xPerInch)
		{
			return (LONG) MulDiv(dx, HIMETRIC_PER_INCH, xPerInch);
		}

		// Convert Pixels on the Y axis to Himetric
		LONG DYtoHimetricY(LONG dy, LONG yPerInch)
		{
			return (LONG) MulDiv(dy, HIMETRIC_PER_INCH, yPerInch);
		}

		HRESULT InitDefaultCharFormat(CHARFORMAT2W* pcf, HFONT hFont, COLORREF crTextColor)
		{
			memset(pcf, 0, sizeof(CHARFORMAT2W));
			LOGFONTW lf;
			::GetObjectW(hFont, sizeof(LOGFONT), &lf);

			pcf->cbSize = sizeof(CHARFORMAT2W);
			pcf->crTextColor = crTextColor;
			HDC hdc = m_pT->GetDC();
			LONG yPixPerInch = GetDeviceCaps(hdc, LOGPIXELSY);
			m_pT->ReleaseDC(hdc);
			pcf->yHeight = -lf.lfHeight * LY_PER_INCH / yPixPerInch;
			pcf->yOffset = 0;
			pcf->dwEffects = 0;
			pcf->dwMask = CFM_SIZE | CFM_OFFSET | CFM_FACE | CFM_CHARSET | CFM_COLOR | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE;
			if(lf.lfWeight >= FW_BOLD)
				pcf->dwEffects |= CFE_BOLD;
			if(lf.lfItalic)
				pcf->dwEffects |= CFE_ITALIC;
			if(lf.lfUnderline)
				pcf->dwEffects |= CFE_UNDERLINE;
			pcf->bCharSet = lf.lfCharSet;
			pcf->bPitchAndFamily = lf.lfPitchAndFamily;
			_tcscpy(pcf->szFaceName, lf.lfFaceName);

			return S_OK;
		}

		HRESULT InitDefaultParaFormat(PARAFORMAT2* ppf) 
		{	
			memset(ppf, 0, sizeof(PARAFORMAT2));
			ppf->cbSize = sizeof(PARAFORMAT2);
			ppf->dwMask = PFM_ALL;
			ppf->wAlignment = PFA_LEFT;
			ppf->cTabCount = 1;
			ppf->rgxTabs[0] = lDefaultTab;

			return S_OK;
		}

		ITextServices* GetTextServices(void) { return pserv; }

		HIMC TxImmGetContext(void)
		{
			return NULL;
		}

		void TxImmReleaseContext(HIMC himc)
		{
			//::ImmReleaseContext( hwnd, himc );
		}

		HDC TxGetDC()
		{
			return m_pT->GetDC();
		}

		int TxReleaseDC(HDC hdc)
		{
			return m_pT->ReleaseDC(hdc);
		}

		BOOL TxShowScrollBar(INT fnBar, BOOL fShow)
		{
			m_pT->ShowScrollBar(fnBar,fShow);
			return TRUE;
		}

		BOOL TxEnableScrollBar (INT fuSBFlags, INT fuArrowflags)
		{
			m_pT->EnableScrollBar(fuSBFlags,fuArrowflags);
			return TRUE;
		}

		BOOL TxSetScrollRange(INT fnBar, LONG nMinPos, INT nMaxPos, BOOL fRedraw)
		{
			return m_pT->SetScrollRange(fnBar,nMinPos,nMaxPos,fRedraw);
		}

		BOOL TxSetScrollPos (INT fnBar, INT nPos, BOOL fRedraw)
		{
			//m_pT->SetScrollPos(fnBar,nPos,fRedraw);
			return TRUE;
		}

		void TxInvalidateRect(LPCRECT prc, BOOL fMode)
		{
			m_pT->InvalidateRect(prc,fMode);
		}

		void TxViewChange(BOOL fUpdate) 
		{
			m_pT->Invalidate();
		}

		BOOL TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight)
		{
			iCaretWidth = xWidth;
			iCaretHeight = yHeight;
			return ::CreateCaret(m_pT->GetSafeHwnd(), hbmp, xWidth, yHeight);
		}

		BOOL TxShowCaret(BOOL fShow)
		{
			fShowCaret = fShow;
			if(fShow)
				return ::ShowCaret(m_pT->GetSafeHwnd());
			else
				return ::HideCaret(m_pT->GetSafeHwnd());
		}

		BOOL TxSetCaretPos(INT x, INT y)
		{
			POINT ptCaret = { 0 };
			::GetCaretPos(&ptCaret);
			RECT rcCaret = { ptCaret.x, ptCaret.y, ptCaret.x + iCaretLastWidth, ptCaret.y + iCaretLastHeight };
			m_pT->InvalidateRect(&rcCaret);
			rcCaret.left = x;
			rcCaret.top = y;
			rcCaret.right = x + iCaretWidth;
			rcCaret.bottom = y + iCaretHeight;
			m_pT->InvalidateRect(&rcCaret);
			iCaretLastWidth = iCaretWidth;
			iCaretLastHeight = iCaretHeight;
			return ::SetCaretPos(x, y);
		}

		BOOL TxSetTimer(UINT idTimer, UINT uTimeout)
		{
			fTimer = TRUE;
			return m_pT->SetTimer(idTimer, uTimeout);
		}

		void TxKillTimer(UINT idTimer)
		{
			m_pT->KillTimer(idTimer);
			fTimer = FALSE;
		}

		void TxScrollWindowEx (INT dx, INT dy, LPCRECT lprcScroll,	LPCRECT lprcClip,	HRGN hrgnUpdate, LPRECT lprcUpdate,	UINT fuScroll)	
		{
			m_pT->ScrollWindowEx(dx,dy,lprcScroll,lprcClip,hrgnUpdate,lprcUpdate,fuScroll);
		}

		void TxSetCapture(BOOL fCapture)
		{
			if (fCapture) m_pT->SetCapture();
			else m_pT->ReleaseCapture();
			fCaptured = fCapture;
		}

		void TxSetFocus()
		{
			m_pT->SetFocus();
		}

		void TxSetCursor(HCURSOR hcur,	BOOL fText)
		{
			::SetCursor(hcur);
		}

		BOOL TxScreenToClient(LPPOINT lppt)
		{
			return ::ScreenToClient(m_pT->GetSafeHwnd(), lppt);	
		}

		BOOL TxClientToScreen(LPPOINT lppt)
		{
			return ::ClientToScreen(m_pT->GetSafeHwnd(), lppt);
		}

		HRESULT TxActivate(LONG *plOldState)
		{
			return S_OK;
		}

		HRESULT TxDeactivate(LONG lNewState)
		{
			return S_OK;
		}

		HRESULT TxGetClientRect(LPRECT prc)
		{
			*prc = rcClient;
			GetControlRect(prc);
			return NOERROR;
		}

		HRESULT TxGetViewInset(LPRECT prc) 
		{
			prc->left = prc->right = prc->top = prc->bottom = 0;
			return NOERROR;	
		}

		HRESULT TxGetCharFormat(const CHARFORMATW **ppCF)
		{
			*ppCF = &cf;
			return NOERROR;
		}

		HRESULT TxGetParaFormat(const PARAFORMAT **ppPF)
		{
			*ppPF = &pf;
			return NOERROR;
		}

		COLORREF TxGetSysColor(int nIndex) 
		{
			return ::GetSysColor(nIndex);
		}

		HRESULT TxGetBackStyle(TXTBACKSTYLE *pstyle)
		{
			*pstyle = !fTransparent ? TXTBACK_OPAQUE : TXTBACK_TRANSPARENT;
			return NOERROR;
		}

		HRESULT TxGetMaxLength(DWORD *pLength)
		{
			*pLength = cchTextMost;
			return NOERROR;
		}

		HRESULT TxGetScrollBars(DWORD *pdwScrollBar)
		{
			*pdwScrollBar =  dwStyle & (WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | 
				ES_AUTOHSCROLL | ES_DISABLENOSCROLL);

			return NOERROR;
		}

		HRESULT TxGetPasswordChar(WCHAR *pch)
		{
			TCHAR cPasswordChar = _T('*');
#ifdef _UNICODE
			*pch = cPasswordChar;
#else
			::WideCharToMultiByte(CP_ACP, 0, &cPasswordChar, 1, pch, 1, NULL, NULL) ;
#endif
			return NOERROR;
		}

		HRESULT TxGetAcceleratorPos(LONG *pcp)
		{
			*pcp = laccelpos;
			return S_OK;
		} 										   

		HRESULT OnTxCharFormatChange(const CHARFORMATW *pcf)
		{
			return S_OK;
		}

		HRESULT OnTxParaFormatChange(const PARAFORMAT *ppf)
		{
			return S_OK;
		}

		HRESULT TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits) 
		{
			DWORD dwProperties = 0;

			if (fRich)
			{
				dwProperties = TXTBIT_RICHTEXT;
			}

			if (dwStyle & ES_MULTILINE)
			{
				dwProperties |= TXTBIT_MULTILINE;
			}

			if (dwStyle & ES_READONLY)
			{
				dwProperties |= TXTBIT_READONLY;
			}

			if (dwStyle & ES_PASSWORD)
			{
				dwProperties |= TXTBIT_USEPASSWORD;
			}

			if (!(dwStyle & ES_NOHIDESEL))
			{
				dwProperties |= TXTBIT_HIDESELECTION;
			}

			if (fEnableAutoWordSel)
			{
				dwProperties |= TXTBIT_AUTOWORDSEL;
			}

			if (fWordWrap)
			{
				dwProperties |= TXTBIT_WORDWRAP;
			}

			if (fAllowBeep)
			{
				dwProperties |= TXTBIT_ALLOWBEEP;
			}

			if (fSaveSelection)
			{
				dwProperties |= TXTBIT_SAVESELECTION;
			}

			*pdwBits = dwProperties & dwMask; 
			return NOERROR;
		}


		HRESULT TxNotify(DWORD iNotify, void *pv)
		{
			if( iNotify == EN_REQUESTRESIZE ) {
				RECT rc;
				REQRESIZE *preqsz = (REQRESIZE *)pv;
				GetControlRect(&rc);
				rc.bottom = rc.top + preqsz->rc.bottom;
				rc.right  = rc.left + preqsz->rc.right;
				SetClientRect(&rc);
				return S_OK;
			}
			//m_pT->OnTxNotify(iNotify, pv);
			return S_OK;
		}

		HRESULT TxGetExtent(LPSIZEL lpExtent)
		{
			*lpExtent = sizelExtent;
			return S_OK;
		}

		HRESULT	TxGetSelectionBarWidth (LONG *plSelBarWidth)
		{
			*plSelBarWidth = lSelBarWidth;
			return S_OK;
		}

		void SetWordWrap(BOOL fWordWrap)
		{
			fWordWrap = fWordWrap;
			pserv->OnTxPropertyBitsChange(TXTBIT_WORDWRAP, fWordWrap ? TXTBIT_WORDWRAP : 0);
		}

		BOOL IsReadOnly()
		{
			return (dwStyle & ES_READONLY) != 0;
		}

		void SetReadOnly(BOOL fReadOnly)
		{
			if (fReadOnly)
			{
				dwStyle |= ES_READONLY;
			}
			else
			{
				dwStyle &= ~ES_READONLY;
			}

			pserv->OnTxPropertyBitsChange(TXTBIT_READONLY, 
				fReadOnly ? TXTBIT_READONLY : 0);
		}

		void SetFont(HFONT hFont) 
		{
			if( hFont == NULL ) return;
			LOGFONT lf;
			::GetObject(hFont, sizeof(LOGFONT), &lf);
			LONG yPixPerInch = ::GetDeviceCaps(m_pT->GetManager()->GetPaintDC(), LOGPIXELSY);
			cf.yHeight = -lf.lfHeight * LY_PER_INCH / yPixPerInch;
			if(lf.lfWeight >= FW_BOLD) cf.dwEffects |= CFE_BOLD;
			else cf.dwEffects &= ~CFE_BOLD;
			if(lf.lfItalic) cf.dwEffects |= CFE_ITALIC;
			else cf.dwEffects &= ~CFE_ITALIC;
			if(lf.lfUnderline) cf.dwEffects |= CFE_UNDERLINE;
			else cf.dwEffects &= ~CFE_UNDERLINE;
			cf.bCharSet = lf.lfCharSet;
			cf.bPitchAndFamily = lf.lfPitchAndFamily;
#ifdef _UNICODE
			_tcscpy(cf.szFaceName, lf.lfFaceName);
#else
			//need to thunk pcf->szFaceName to a standard char string.in this case it's easy because our thunk is also our copy
			MultiByteToWideChar(CP_ACP, 0, lf.lfFaceName, LF_FACESIZE, cf.szFaceName, LF_FACESIZE) ;
#endif

			pserv->OnTxPropertyBitsChange(TXTBIT_CHARFORMATCHANGE, 
				TXTBIT_CHARFORMATCHANGE);
		}

		void SetColor(DWORD dwColor)
		{
			cf.crTextColor = RGB(GetBValue(dwColor), GetGValue(dwColor), GetRValue(dwColor));
			pserv->OnTxPropertyBitsChange(TXTBIT_CHARFORMATCHANGE, 
				TXTBIT_CHARFORMATCHANGE);
		}

		SIZEL* GetExtent() 
		{
			return &sizelExtent;
		}

		void SetExtent(SIZEL *psizelExtent) 
		{ 
			sizelExtent = *psizelExtent; 
			pserv->OnTxPropertyBitsChange(TXTBIT_EXTENTCHANGE, TXTBIT_EXTENTCHANGE);
		}

		void LimitText(LONG nChars)
		{
			cchTextMost = nChars;
			if( cchTextMost <= 0 ) cchTextMost = cInitTextMax;
			pserv->OnTxPropertyBitsChange(TXTBIT_MAXLENGTHCHANGE, TXTBIT_MAXLENGTHCHANGE);
		}

		BOOL IsCaptured()
		{
			return fCaptured;
		}

		BOOL IsShowCaret()
		{
			return fShowCaret;
		}

		void NeedFreshCaret()
		{
			fNeedFreshCaret = TRUE;
		}

		INT GetCaretWidth()
		{
			return iCaretWidth;
		}

		INT GetCaretHeight()
		{
			return iCaretHeight;
		}

		BOOL GetAllowBeep()
		{
			return fAllowBeep;
		}

		void SetAllowBeep(BOOL fAllowBeep)
		{
			fAllowBeep = fAllowBeep;

			pserv->OnTxPropertyBitsChange(TXTBIT_ALLOWBEEP, 
				fAllowBeep ? TXTBIT_ALLOWBEEP : 0);
		}

		WORD GetDefaultAlign()
		{
			return pf.wAlignment;
		}

		void SetDefaultAlign(WORD wNewAlign)
		{
			pf.wAlignment = wNewAlign;

			// Notify control of property change
			pserv->OnTxPropertyBitsChange(TXTBIT_PARAFORMATCHANGE, 0);
		}

		BOOL GetRichTextFlag()
		{
			return fRich;
		}

		void SetRichTextFlag(BOOL fNew)
		{
			fRich = fNew;

			pserv->OnTxPropertyBitsChange(TXTBIT_RICHTEXT, 
				fNew ? TXTBIT_RICHTEXT : 0);
		}

		LONG GetDefaultLeftIndent()
		{
			return pf.dxOffset;
		}

		void SetDefaultLeftIndent(LONG lNewIndent)
		{
			pf.dxOffset = lNewIndent;

			pserv->OnTxPropertyBitsChange(TXTBIT_PARAFORMATCHANGE, 0);
		}

		void SetClientRect(RECT *prc) 
		{
			rcClient = *prc;

			HDC hdc = m_pT->GetDC();
			LONG xPerInch = ::GetDeviceCaps(hdc, LOGPIXELSX); 
			LONG yPerInch =	::GetDeviceCaps(hdc, LOGPIXELSY); 
			m_pT->ReleaseDC(hdc);
			sizelExtent.cx = DXtoHimetricX(rcClient.right - rcClient.left, xPerInch);
			sizelExtent.cy = DYtoHimetricY(rcClient.bottom - rcClient.top, yPerInch);

			pserv->OnTxPropertyBitsChange(TXTBIT_VIEWINSETCHANGE, TXTBIT_VIEWINSETCHANGE);
		}

		BOOL SetSaveSelection(BOOL f_SaveSelection)
		{
			BOOL fResult = f_SaveSelection;

			fSaveSelection = f_SaveSelection;

			// notify text services of property change
			pserv->OnTxPropertyBitsChange(TXTBIT_SAVESELECTION, 
				fSaveSelection ? TXTBIT_SAVESELECTION : 0);

			return fResult;		
		}

		HRESULT	OnTxInPlaceDeactivate()
		{
			HRESULT hr = pserv->OnTxInPlaceDeactivate();

			if (SUCCEEDED(hr))
			{
				fInplaceActive = FALSE;
			}

			return hr;
		}

		HRESULT	OnTxInPlaceActivate(LPCRECT prcClient)
		{
			fInplaceActive = TRUE;

			HRESULT hr = pserv->OnTxInPlaceActivate(prcClient);

			if (FAILED(hr))
			{
				fInplaceActive = FALSE;
			}

			return hr;
		}

		BOOL DoSetCursor(RECT *prc, POINT *pt)
		{
			RECT rc = prc ? *prc : rcClient;

			// Is this in our rectangle?
			if (PtInRect(&rc, *pt))
			{
				RECT *prcClient = (!fInplaceActive || prc) ? &rc : NULL;
				pserv->OnTxSetCursor(DVASPECT_CONTENT,	-1, NULL, NULL,  m_pT->GetManager()->GetPaintDC(),
					NULL, prcClient, pt->x, pt->y);

				return TRUE;
			}

			return FALSE;
		}

		void GetControlRect(LPRECT prc)
		{
			prc->top = rcClient.top;
			prc->bottom = rcClient.bottom;
			prc->left = rcClient.left;
			prc->right = rcClient.right;
		}

		void SetTransparent(BOOL f_Transparent)
		{
			fTransparent = f_Transparent;

			// notify text services of property change
			pserv->OnTxPropertyBitsChange(TXTBIT_BACKSTYLECHANGE, 0);
		}

		LONG SetAccelPos(LONG l_accelpos)
		{
			LONG laccelposOld = l_accelpos;

			laccelpos = l_accelpos;

			// notify text services of property change
			pserv->OnTxPropertyBitsChange(TXTBIT_SHOWACCELERATOR, 0);

			return laccelposOld;
		}

		WCHAR SetPasswordChar(WCHAR ch_PasswordChar)
		{
			WCHAR chOldPasswordChar = chPasswordChar;

			chPasswordChar = ch_PasswordChar;

			// notify text services of property change
			pserv->OnTxPropertyBitsChange(TXTBIT_USEPASSWORD, 
				(chPasswordChar != 0) ? TXTBIT_USEPASSWORD : 0);

			return chOldPasswordChar;
		}

		void SetDisabled(BOOL fOn)
		{
			cf.dwMask	 |= CFM_COLOR | CFM_DISABLED;
			cf.dwEffects |= CFE_AUTOCOLOR | CFE_DISABLED;

			if( !fOn )
			{
				cf.dwEffects &= ~CFE_DISABLED;
			}

			pserv->OnTxPropertyBitsChange(TXTBIT_CHARFORMATCHANGE, 
				TXTBIT_CHARFORMATCHANGE);
		}

		LONG SetSelBarWidth(LONG l_SelBarWidth)
		{
			LONG lOldSelBarWidth = lSelBarWidth;

			lSelBarWidth = l_SelBarWidth;

			if (lSelBarWidth)
			{
				dwStyle |= ES_SELECTIONBAR;
			}
			else
			{
				dwStyle &= (~ES_SELECTIONBAR);
			}

			pserv->OnTxPropertyBitsChange(TXTBIT_SELBARCHANGE, TXTBIT_SELBARCHANGE);

			return lOldSelBarWidth;
		}

		BOOL GetTimerState()
		{
			return fTimer;
		}

		void SetCharFormat(CHARFORMAT2W &c)
		{
			cf = c;
		}

		void SetParaFormat(PARAFORMAT2 &p)
		{
			pf = p;
		}
	};
}

template<class T>
class UIRichEdit2Map
{
	typedef UIRichEdit2Map<T> This;
	typedef UITextServ::UITextHost<T> TextHost;
protected:
	TextHost* m_pTextHost;
public:
	UIRichEdit2Map():m_pTextHost(NULL)
	{
		
	}

	HRESULT TxSendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *plResult) const
	{
		if( m_pTextHost ) {
			return m_pTextHost->GetTextServices()->TxSendMessage(uMsg, wParam, lParam, plResult);
		}
		return S_FALSE;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		/*MESSAGE_HANDLER(WM_SETTEXT, OnSetText)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)*/
		MESSAGE_HANDLER(EM_GETLINECOUNT, OnGetLineCount)
		MESSAGE_HANDLER(EM_GETMODIFY, OnGetModify)
		MESSAGE_HANDLER(EM_SETMODIFY, OnSetModify)
		MESSAGE_HANDLER(EM_GETRECT, OnGetRect)
		MESSAGE_HANDLER(EM_GETOPTIONS, OnGetOptions)
		MESSAGE_HANDLER(EM_SETOPTIONS, OnSetOptions)
		MESSAGE_HANDLER(EM_GETLINE, OnGetLine)
		MESSAGE_HANDLER(EM_CANUNDO, OnCanUndo)
		MESSAGE_HANDLER(EM_CANPASTE, OnCanPaste)
		MESSAGE_HANDLER(EM_EXGETSEL, OnGetSel)
		MESSAGE_HANDLER(EM_EXSETSEL, OnSetSel)
		MESSAGE_HANDLER(EM_GETCHARFORMAT, OnGetCharFormat)
		MESSAGE_HANDLER(EM_GETEVENTMASK, OnGetEventMask)
		MESSAGE_HANDLER(EM_GETLIMITTEXT, OnGetLimitText)
		MESSAGE_HANDLER(EM_GETPARAFORMAT, OnGetParaFormat)
#if (_RICHEDIT_VER >= 0x0200)
		MESSAGE_HANDLER(EM_GETSELTEXT, OnGetSelText);
#else // !(_RICHEDIT_VER >= 0x0200)
		// RichEdit 1.0 EM_GETSELTEXT is ANSI only
		MESSAGE_HANDLER(EM_GETSELTEXT, OnGetSelText)
#endif // !(_RICHEDIT_VER >= 0x0200)
		MESSAGE_HANDLER(EM_EXGETSEL, OnExGetSel)
		MESSAGE_HANDLER(EM_SELECTIONTYPE, OnGetSelectionType)
		MESSAGE_HANDLER(EM_SETBKGNDCOLOR, OnSetBackgroundColor)
		MESSAGE_HANDLER(EM_SETCHARFORMAT, OnSetCharFormat)
		MESSAGE_HANDLER(EM_SETEVENTMASK, OnSetEventMask);
		MESSAGE_HANDLER(EM_SETPARAFORMAT, OnSetParaFormat)
		MESSAGE_HANDLER(EM_SETTARGETDEVICE, OnSetTargetDevice)
		MESSAGE_HANDLER(WM_GETTEXTLENGTH, OnGetTextLength)
		MESSAGE_HANDLER(EM_SETREADONLY, OnSetReadOnly)
		MESSAGE_HANDLER(EM_GETFIRSTVISIBLELINE, OnGetFirstVisibleLine)
		MESSAGE_HANDLER(EM_GETWORDBREAKPROCEX, OnGetWordBreakProcEx)
		MESSAGE_HANDLER(EM_SETWORDBREAKPROCEX, OnSetWordBreakProcEx)
		MESSAGE_HANDLER(EM_GETTEXTRANGE, OnGetTextRange)
#if (_RICHEDIT_VER >= 0x0200)
		MESSAGE_HANDLER(EM_GETTEXTMODE, OnGetTextMode)
		MESSAGE_HANDLER(EM_SETTEXTMODE, OnSetTextMode)
		MESSAGE_HANDLER(EM_GETUNDONAME, OnGetUndoName)
		MESSAGE_HANDLER(EM_GETREDONAME, OnGetRedoName)
		MESSAGE_HANDLER(EM_CANREDO, OnCanRedo)
		MESSAGE_HANDLER(EM_GETAUTOURLDETECT, OnGetAutoURLDetect)
		MESSAGE_HANDLER(EM_AUTOURLDETECT, OnSetAutoURLDetect)
		MESSAGE_HANDLER(EM_SETUNDOLIMIT, OnSetUndoLimit)
		MESSAGE_HANDLER(EM_SETPALETTE, OnSetPalette)
		MESSAGE_HANDLER(EM_GETTEXTEX, OnGetTextEx)
		MESSAGE_HANDLER(EM_GETTEXTLENGTHEX, OnGetTextLengthEx)
#endif // (_RICHEDIT_VER >= 0x0200)

#if (_RICHEDIT_VER >= 0x0300)
		MESSAGE_HANDLER(EM_SETTEXTEX, OnSetTextEx)
		MESSAGE_HANDLER(EM_GETEDITSTYLE, OnGetEditStyle)
		MESSAGE_HANDLER(EM_SETEDITSTYLE, OnSetEditStyle)
		MESSAGE_HANDLER(EM_SETFONTSIZE, OnSetFontSize)
		MESSAGE_HANDLER(EM_GETSCROLLPOS, OnGetScrollPos)
		MESSAGE_HANDLER(EM_SETSCROLLPOS, OnSetScrollPos)
		MESSAGE_HANDLER(EM_GETZOOM, OnGetZoom)
		MESSAGE_HANDLER(EM_SETZOOM, OnSetZoom)
		MESSAGE_HANDLER(EM_SETZOOM, OnSetZoomOff)
#endif // (_RICHEDIT_VER >= 0x0300)
		MESSAGE_HANDLER(EM_EXLIMITTEXT, OnLimitText)
		MESSAGE_HANDLER(EM_EXLINEFROMCHAR, OnLineFromChar)
		MESSAGE_HANDLER(EM_POSFROMCHAR, OnPosFromChar)
		MESSAGE_HANDLER(EM_CHARFROMPOS, OnCharFromPos)
		MESSAGE_HANDLER(EM_EMPTYUNDOBUFFER, OnEmptyUndoBuffer)
		MESSAGE_HANDLER(EM_LINEINDEX, OnLineIndex)
		MESSAGE_HANDLER(EM_LINELENGTH, OnLineLength)
		MESSAGE_HANDLER(EM_LINESCROLL, OnLineScroll)
		MESSAGE_HANDLER(EM_REPLACESEL, OnReplaceSel)
		MESSAGE_HANDLER(EM_SETRECT, OnSetRect)
		MESSAGE_HANDLER(EM_DISPLAYBAND, OnDisplayBand)
#if (_RICHEDIT_VER >= 0x0200) && defined(_UNICODE)
		MESSAGE_HANDLER(EM_FINDTEXTEXW, OnFindTextW)
#else
		MESSAGE_HANDLER(EM_FINDTEXTEX, OnFindText)
#endif
		MESSAGE_HANDLER(EM_FORMATRANGE, OnFormatRange)
		MESSAGE_HANDLER(EM_HIDESELECTION, OnHideSelection)
		MESSAGE_HANDLER(EM_PASTESPECIAL, OnPasteSpecial)
		MESSAGE_HANDLER(EM_REQUESTRESIZE, OnRequestResize)
		MESSAGE_HANDLER(EM_STREAMIN, OnStreamIn)
		MESSAGE_HANDLER(EM_STREAMOUT, OnStreamOut)
		MESSAGE_HANDLER(EM_FINDWORDBREAK, OnFindWordBreak)
		MESSAGE_HANDLER(EM_SCROLLCARET, OnScrollCaret)
		MESSAGE_HANDLER(EM_UNDO, OnUndo)
		MESSAGE_HANDLER(WM_CLEAR, OnClear)
		MESSAGE_HANDLER(WM_COPY, OnCopy)
		MESSAGE_HANDLER(WM_CUT, OnCut)
		MESSAGE_HANDLER(WM_PASTE, OnPaste)
		MESSAGE_HANDLER(EM_GETOLEINTERFACE, OnGetOleInterface)
		MESSAGE_HANDLER(EM_SETOLECALLBACK, OnSetOleCallback)
#if (_RICHEDIT_VER >= 0x0200)
		MESSAGE_HANDLER(EM_REDO, OnRedo)
		MESSAGE_HANDLER(EM_STOPGROUPTYPING, OnStopGroupTyping)
		MESSAGE_HANDLER(EM_SHOWSCROLLBAR, OnShowScrollBar)
#endif // (_RICHEDIT_VER >= 0x0200)

#if (_RICHEDIT_VER >= 0x0300)
		MESSAGE_HANDLER(EM_SETTABSTOPS, OnSetTabStops)
#endif // (_RICHEDIT_VER >= 0x0300)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;

		LPCREATESTRUCT lpCreateStruct = (LPCREATESTRUCT)lParam;

		HRESULT hr = E_FAIL;
		TextHost *pTextHost = new TextHost(pT,lpCreateStruct);
		if(pTextHost) {
			if (!pTextHost->GetTextServices()) {
				delete pTextHost;
				pTextHost = NULL;
			}
		}
		m_pTextHost = pTextHost;
		
		return bHandled;
	}

	LRESULT OnGetLineCount(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetModify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetModify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetOptions(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetOptions(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	// NOTE: first word in lpszBuffer must contain the size of the buffer!
	LRESULT OnGetLine(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnCanUndo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnCanPaste(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetSel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetSel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetCharFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetEventMask(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetLimitText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetParaFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetSelText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnExGetSel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetSelectionType(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetBackgroundColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetCharFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetEventMask(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetParaFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetTargetDevice(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetTextLength(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetReadOnly(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetFirstVisibleLine(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetWordBreakProcEx(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetWordBreakProcEx(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetTextRange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

#if (_RICHEDIT_VER >= 0x0200)
	LRESULT OnGetTextMode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetTextMode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetUndoName(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetRedoName(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnCanRedo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetAutoURLDetect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetAutoURLDetect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	// this method is deprecated, please use SetAutoURLDetect
	LRESULT OnEnableAutoURLDetect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetUndoLimit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetPalette(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetTextEx(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetTextLengthEx(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}
#endif // (_RICHEDIT_VER >= 0x0200)

#if (_RICHEDIT_VER >= 0x0300)
	LRESULT OnSetTextEx(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetEditStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetEditStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetFontSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetScrollPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetScrollPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnGetZoom(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetZoom(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetZoomOff(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}
#endif // (_RICHEDIT_VER >= 0x0300)

	// Operations
	LRESULT OnLimitText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnLineFromChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnPosFromChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnCharFromPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnEmptyUndoBuffer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnLineIndex(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnLineLength(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnLineScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnReplaceSel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnDisplayBand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnFindText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnFindTextW(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnFormatRange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnHideSelection(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnPasteSpecial(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnRequestResize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnStreamIn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnStreamOut(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnFindWordBreak(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	// Additional operations
	LRESULT OnScrollCaret(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	// Clipboard operations
	LRESULT OnUndo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnClear(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnCopy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnCut(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnPaste(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	// OLE support
	LRESULT OnGetOleInterface(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnSetOleCallback(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

#if (_RICHEDIT_VER >= 0x0200)
	LRESULT OnRedo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnStopGroupTyping(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}

	LRESULT OnShowScrollBar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}
#endif // (_RICHEDIT_VER >= 0x0200)

#if (_RICHEDIT_VER >= 0x0300)
	LRESULT OnSetTabStops(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		TxSendMessage(uMsg, wParam, lParam, &lResult);
		return (int)lResult;
	}
#endif // (_RICHEDIT_VER >= 0x0300)
};
/*
class UXRichEdit2
	: public UXRichEditCtrl2Impl<UXRichEdit2>
	, public UIRichEdit2Map<UXRichEdit2>
	, public UIXRichEdit2SkinMap<UXRichEdit2>
{
	typedef UXRichEdit2 This;
	typedef UXRichEditCtrl2Impl<UXRichEdit2> Base;
	typedef UIRichEdit2Map<UXRichEdit2> FuncMap;
	typedef UIXRichEdit2SkinMap<UXRichEdit2> SkinMap;
public:
	DECLARE_XMLWND_CLASS(_T("RICHEDIT"))
	DECLARE_DYNCREATE_WND_OBJECTER(UXRichEdit2,UXWnd2)

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXRichEdit2,UXWnd2)*/

//////////////////////////////////////////////////////////////////////////
//
//UXLayout::UXLayout()
//{
//
//}