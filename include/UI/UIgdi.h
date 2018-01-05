
#pragma once

#ifndef _H_UIGDI_H_
#define _H_UIGDI_H_

#include <wtl/atlgdi.h>

#include "UIApp.h"

#include <map>
//using namespace std;

//////////////////////////////////////////////////////////////////////////

#define SZ_RES_XML_TYPE _T("xml")
#define SZ_RES_PNG_TYPE _T("png")

#define RGB2BGR(cr)		(((cr&268431360)>>16)|((cr&255)<<16)|(cr&65280))
#define BGR2RGB(cr)		((cr&65280)|((cr&255)<<16)|((cr&268431360)>>16))
#define RGB2WEB(cr)		RGB2BGR(cr)
#define WEB2RGB(cr)		BGR2RGB(cr)
#ifndef RGB2RGBQUAD
//#define RGB2RGBQUAD(cr)    RGB(GetBValue(cr),GetGValue(cr),GetRValue(cr))
#define RGB2RGBQUAD(cr)	RGB2BGR(cr)
#endif// 
#ifndef RGBQUAD2RGB
//#define RGBQUAD2RGB(cr)    RGB(GetRValue(cr),GetGValue(cr),GetBValue(cr)))
#define RGBQUAD2RGB(cr)	BGR2RGB(cr)
#endif// 

#ifndef CLR_INVALID
#define CLR_INVALID     0xFFFFFFFF
#endif//

/////////////////////////////////////////////////////////////////////////////
// Macros

// The GetXValue macros below are badly designed and emit
// compiler warnings e.g. when using RGB(255,255,255)...
#pragma warning(disable : 4310)

#ifndef BlendRGB
#define BlendRGB(c1, c2, factor) \
	RGB( GetRValue(c1) + ((GetRValue(c2) - GetRValue(c1)) * factor / 100L), \
	GetGValue(c1) + ((GetGValue(c2) - GetGValue(c1)) * factor / 100L), \
	GetBValue(c1) + ((GetBValue(c2) - GetBValue(c1)) * factor / 100L) )
#endif

#ifndef COLOR_INVALID
#define COLOR_INVALID  (COLORREF) CLR_INVALID
#endif

/*#ifndef SelectPen
#define SelectPen(hdc, hpen)    ((HPEN)SelectObject((hdc), (HGDIOBJ)(HPEN)(hpen)))
#endif//
#ifndef SelectBitmap
#define SelectBitmap(hdc, hbm)  ((HBITMAP)SelectObject((hdc), (HGDIOBJ)(HBITMAP)(hbm)))
#endif//
#ifndef SelectFont
#define SelectFont(hdc, hfont)  ((HFONT)SelectObject((hdc), (HGDIOBJ)(HFONT)(hfont)))
#endif//*/

namespace ATL {

#if _MSC_VER<=1200
#else
class CImageEx : public CImage
{
public:
	BOOL Load(IN LPVOID lpData, IN DWORD dwDataLen)
	{
		HGLOBAL hImage = GlobalAlloc(GMEM_FIXED, dwDataLen);
		if (hImage) {
			memcpy(GlobalLock(hImage), lpData, dwDataLen);
			CComPtr<IStream> spStm;
			CreateStreamOnHGlobal(hImage, FALSE, &spStm);
			if (spStm) {
				return SUCCEEDED(CImage::Load(spStm));
			}
			GlobalUnlock(hImage);
			GlobalFree(hImage);
		}
		return FALSE;
	}

	BOOL LoadFromResource(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszResourceType)
	{
		HRSRC hRsrc = ::FindResource(hInstance, pszResourceName, pszResourceType);
		if (hRsrc == NULL) {
			return FALSE;
		}

		BYTE* lpbyRsrc = (BYTE*)LoadResource(hInstance, hRsrc);
		if (lpbyRsrc != NULL) {
			return FALSE;
		}

		BOOL bRet = FALSE;

		DWORD dwRsrcSize = SizeofResource(hInstance, hRsrc);
		HGLOBAL hGlobal = GlobalAlloc(GMEM_FIXED, dwRsrcSize);
		if (hGlobal != NULL) {
			memcpy(GlobalLock(hGlobal), lpbyRsrc, dwRsrcSize);
			CComPtr<IStream> spStm = NULL;
			CreateStreamOnHGlobal(hGlobal, FALSE, &spStm);
			if (spStm) {
				bRet = SUCCEEDED(CImage::Load(spStm));
			}
			GlobalUnlock(hGlobal);
			GlobalFree(hGlobal);
		}
		FreeResource(lpbyRsrc);

		return bRet;
	}
};
#endif//

}

namespace Gdiplus {

class ImageEx : public Image
{
public:
	static Image* ImageFromData(
		IN void* lpdata,
		IN size_t dataLength
		)
	{
		HGLOBAL hImage = GlobalAlloc(GMEM_FIXED, dataLength);
		if (hImage) {
			memcpy(GlobalLock(hImage), lpdata, dataLength);
			CComPtr<IStream> spStm;
			CreateStreamOnHGlobal(hImage, FALSE, &spStm);
			return new Image(spStm, FALSE);
			GlobalUnlock(hImage);
			GlobalFree(hImage);
		}
		return NULL;
	}

	static Image* ImageFromResource(IN HINSTANCE hInstance, IN LPCTSTR pszResourceName, IN LPCTSTR pszResourceType)
	{
		Image* pImage = NULL;
		HRSRC hRsrc = ::FindResource(hInstance, pszResourceName, pszResourceType);
		if (hRsrc) {
			BYTE* lpbyRsrc = (BYTE*)LoadResource(hInstance, hRsrc);
			if (lpbyRsrc) {
				DWORD dwRsrcSize = SizeofResource(hInstance, hRsrc);
				pImage = ImageEx::ImageFromData(lpbyRsrc, dwRsrcSize);
				FreeResource(lpbyRsrc);
			}
		}
		return pImage;
	}
};

}

namespace WTL {

#if _WTL_VER < 0x0750

	/////////////////////////////////////////////////////////////////////////////
	// CIcon

	template< bool t_bManaged >
	class CIconT
	{
	public:
		HICON m_hIcon;

		// Constructor/destructor/operators

		CIconT(HICON hIcon = NULL) : m_hIcon(hIcon)
		{ 
		}

		~CIconT()
		{
			if( t_bManaged && m_hIcon != NULL ) ::DestroyIcon(m_hIcon);
		}

		CIconT<t_bManaged>& operator=(HICON hIcon)
		{
			m_hIcon = hIcon;
			return *this;
		}

		void Attach(HICON hIcon)
		{
			if( t_bManaged && m_hIcon != NULL ) ::DestroyIcon(m_hIcon);
			m_hIcon = hIcon;
		}  
		HICON Detach()
		{
			HICON hIcon = m_hIcon;
			m_hIcon = NULL;
			return hIcon;
		}

		operator HICON() const { return m_hIcon; }

		bool IsNull() const { return m_hIcon == NULL; }

		// Create methods

		HICON LoadIcon(_U_STRINGorID icon)
		{
			ATLASSERT(m_hIcon==NULL);
#if (_ATL_VER >= 0x0700)
			m_hIcon = ::LoadIcon(ATL::_AtlBaseModule.GetResourceInstance(), icon.m_lpstr);
#else
			m_hIcon = ::LoadIcon(_Module.GetResourceInstance(), icon.m_lpstr);
#endif
			return m_hIcon;
		}
		HICON LoadIcon(_U_STRINGorID icon, int cxDesired, int cyDesired, UINT fuLoad = 0)
		{
			ATLASSERT(m_hIcon==NULL);
#if (_ATL_VER >= 0x0700)
			m_hIcon = (HICON) ::LoadImage(ATL::_AtlBaseModule.GetResourceInstance(), icon.m_lpstr, IMAGE_ICON, cxDesired, cyDesired, fuLoad);
#else
			m_hIcon = (HICON) ::LoadImage(_Module.GetResourceInstance(), icon.m_lpstr, IMAGE_ICON, cxDesired, cyDesired, fuLoad);
#endif
			return m_hIcon;
		}
		HICON LoadOEMIcon(UINT nIDIcon) // for IDI_ types
		{
			ATLASSERT(m_hIcon==NULL);
			m_hIcon = ::LoadIcon(NULL, MAKEINTRESOURCE(nIDIcon));
			return m_hIcon;
		}
		HICON CreateIcon(int nWidth, int nHeight, BYTE cPlanes, BYTE cBitsPixel, CONST BYTE* lpbANDButs, CONST BYTE *lpbXORbits)
		{
			ATLASSERT(m_hIcon==NULL);
			ATLASSERT(lpbANDbits);
			ATLASSERT(lpbXORbits);
#if (_ATL_VER >= 0x0700)
			m_hIcon = ::CreateIcon(ATL::_AtlBaseModule.GetResourceInstance(), nWidth, nHeight, cPlanes, cBitsPixel, lpbANDbits, lpbXORbits);
#else
			m_hIcon = ::CreateIcon(_Module.GetResourceInstance(), nWidth, nHeight, cPlanes, cBitsPixel, lpbANDbits, lpbXORbits);
#endif
			return m_hIcon;
		}
		HICON CreateIconFromResource(PBYTE pBits, DWORD dwResSize, DWORD dwVersion = 0x00030000)
		{
			ATLASSERT(m_hIcon==NULL);
			ATLASSERT(pBits);
			m_hIcon = ::CreateIconFromResource(pBits, dwResSize, TRUE, dwVersion);
			return m_hIcon;
		}
		HICON CreateIconFromResourceEx(PBYTE pbBits, DWORD cbBits, DWORD dwVersion = 0x00030000, int cxDesired = 0, int cyDesired = 0, UINT uFlags = LR_DEFAULTCOLOR)
		{
			ATLASSERT(m_hIcon==NULL);
			ATLASSERT(pbBits);
			ATLASSERT(cbBits>0);
			m_hIcon = ::CreateIconFromResourceEx(pbBits, cbBits, TRUE, dwVersion, cxDesired,  cyDesired, uFlags);
			return m_hIcon;
		}
		HICON CreateIconIndirect(PICONINFO pIconInfo)
		{
			ATLASSERT(m_hIcon==NULL);
			ATLASSERT(pIconInfo);
			m_hIcon = ::CreateIconIndirect(pIconInfo);
			return m_hIcon;
		}
		HICON ExtractIcon(LPCTSTR lpszExeFileName, UINT nIconIndex)
		{
			ATLASSERT(m_hIcon==NULL);
			ATLASSERT(!::IsBadStringPtr(lpszExeFileName,-1));
#if (_ATL_VER >= 0x0700)      
			m_hIcon = ::ExtractIcon(ATL::_AtlBaseModule.GetModuleInstance(), lpszExeFileName, nIconIndex);
#else
			m_hIcon = ::ExtractIcon(_Module.GetModuleInstance(), lpszExeFileName, nIconIndex);
#endif
			return m_hIcon;
		}
		HICON ExtractAssociatedIcon(HINSTANCE hInst, LPCTSTR lpIconPath, LPWORD lpiIcon)
		{
			ATLASSERT(m_hIcon==NULL);
			ATLASSERT(!::IsBadStringPtr(lpIconPath,-1));
			ATLASSERT(lpiIcon);
			m_hIcon = ::ExtractAssociatedIcon(hInst, lpIconPath, lpiIcon);
			return m_hIcon;
		}

		// Operations

		BOOL DestroyIcon()
		{
			ATLASSERT(m_hIcon!=NULL);
			BOOL bRet = ::DestroyIcon(m_hIcon);
			if( bRet ) m_hIcon = NULL;
			return bRet;
		}
		HICON CopyIcon()
		{
			ATLASSERT(m_hIcon!=NULL);
			return ::CopyIcon(m_hIcon);
		}
		HICON DuplicateIcon()
		{
			ATLASSERT(m_hIcon!=NULL);
			return ::DuplicateIcon(NULL, m_hIcon);
		}

		BOOL DrawIcon(HDC hDC, int x, int y)
		{
			ATLASSERT(m_hIcon!=NULL);
			return ::DrawIcon(hDC, x, y, m_hIcon);
		}
		BOOL DrawIcon(HDC hDC, POINT pt)
		{
			ATLASSERT(m_hIcon!=NULL);
			return ::DrawIcon(hDC, pt.x, pt.y, m_hIcon);
		}
		BOOL DrawIconEx(HDC hDC, int x, int y, int cxWidth, int cyWidth, UINT uStepIfAniCur = 0, HBRUSH hbrFlickerFreeDraw = NULL, UINT uFlags = DI_NORMAL)
		{
			ATLASSERT(m_hIcon!=NULL);
			return ::DrawIconEx(hDC, x, y, m_hIcon, cxWidth, cyWidth, uStepIfAniCur, hbrFlickerFreeDraw, uFlags);
		}
		BOOL DrawIconEx(HDC hDC, POINT pt, SIZE size, UINT uStepIfAniCur = 0, HBRUSH hbrFlickerFreeDraw = NULL, UINT uFlags = DI_NORMAL)
		{
			ATLASSERT(m_hIcon!=NULL);
			return ::DrawIconEx(hDC, pt.x, pt.y, m_hIcon, size.cx, size.cy, uStepIfAniCur, hbrFlickerFreeDraw, uFlags);
		}

		BOOL GetIconInfo(PICONINFO pIconInfo)
		{
			ATLASSERT(m_hIcon!=NULL);
			ATLASSERT(pIconInfo);
			return ::GetIconInfo(m_hIcon, pIconInfo);
		}
	};

	typedef CIconT<true> CIcon;
	typedef CIconT<false> CIconHandle;


	/////////////////////////////////////////////////////////////////////////////
	// CCursor

	// Protect template against silly macro
#ifdef CopyCursor
#undef CopyCursor
#endif

	template< bool t_bManaged >
	class CCursorT
	{
	public:
		HCURSOR m_hCursor;

		// Constructor/destructor/operators

		CCursorT(HCURSOR hCursor = NULL) : m_hCursor(hCursor)
		{ 
		}

		~CCursorT()
		{
			if( t_bManaged && m_hCursor != NULL ) ::DestroyCursor(m_hCursor);
		}

		CCursorT<t_bManaged>& operator=(HCURSOR hCursor)
		{
			m_hCursor = hCursor;
			return *this;
		}

		void Attach(HCURSOR hCursor)
		{
			if( t_bManaged && m_hCursor != NULL ) ::DestroyCursor(m_hCursor);
			m_hCursor = hCursor;
		}
		HCURSOR Detach()
		{
			HCURSOR hCursor = m_hCursor;
			m_hCursor = NULL;
			return hCursor;
		}

		operator HCURSOR() const { return m_hCursor; }

		bool IsNull() const { return m_hCursor == NULL; }

		// Create methods

		HCURSOR LoadCursor(_U_STRINGorID cursor)
		{
			ATLASSERT(m_hCursor==NULL);
#if (_ATL_VER >= 0x0700)
			m_hCursor = ::LoadCursor(ATL::_AtlBaseModule.GetResourceInstance(), cursor.m_lpstr);
#else
			m_hCursor = ::LoadCursor(_Module.GetResourceInstance(), cursor.m_lpstr);
#endif
			return m_hCursor;
		}
		HCURSOR LoadOEMCursor(UINT nIDCursor) // for IDC_ types
		{
			ATLASSERT(m_hCursor==NULL);
			m_hCursor = ::LoadCursor(NULL, MAKEINTRESOURCE(nIDCursor));
			return m_hCursor;
		}
		HICON LoadCursor(_U_STRINGorID cursor, int cxDesired, int cyDesired, UINT fuLoad = 0)
		{
			ATLASSERT(m_hCursor==NULL);
#if (_ATL_VER >= 0x0700)
			m_hCursor = (HCURSOR) ::LoadImage(ATL::_AtlBaseModule.GetResourceInstance(), cursor.m_lpstr, IMAGE_CURSOR, cxDesired, cyDesired, fuLoad);
#else
			m_hCursor = (HCURSOR) ::LoadImage(_Module.GetResourceInstance(), cursor.m_lpstr, IMAGE_CURSOR, cxDesired, cyDesired, fuLoad);
#endif
			return m_hCursor;
		}
		HCURSOR LoadCursorFromFile(LPCTSTR pstrFilename)
		{
			ATLASSERT(m_hCursor==NULL);
			ATLASSERT(!::IsBadStringPtr(pstrFilename,-1));
			m_hCursor = ::LoadCursorFromFile(pstrFilename);
			return m_hCursor;
		}
		HCURSOR CreateCursor(int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID *pvANDPlane, CONST VOID *pvXORPlane)
		{
			ATLASSERT(m_hCursor==NULL);
#if (_ATL_VER >= 0x0700)
			m_hCursor = ::CreateCursor(ATL::_AtlBaseModule.GetResourceInstance(), xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane);
#else
			m_hCursor = ::CreateCursor(_Module.GetResourceInstance(), xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane);
#endif
			return m_hCursor;
		}
		HICON CreateCursorFromResource(PBYTE pBits, DWORD dwResSize, DWORD dwVersion = 0x00030000)
		{
			ATLASSERT(m_hIcon==NULL);
			ATLASSERT(pBits);
			m_hIcon = ::CreateIconFromResource(pBits, dwResSize, FALSE, dwVersion);
			return m_hIcon;
		}
		HICON CreateCursorFromResourceEx(PBYTE pbBits, DWORD cbBits, DWORD dwVersion = 0x00030000, int cxDesired = 0, int cyDesired = 0, UINT uFlags = LR_DEFAULTCOLOR)
		{
			ATLASSERT(m_hIcon==NULL);
			ATLASSERT(pbBits);
			ATLASSERT(cbBits>0);
			m_hIcon = ::CreateIconFromResourceEx(pbBits, cbBits, FALSE, dwVersion, cxDesired,  cyDesired, uFlags);
			return m_hIcon;
		}

		// Operations

		BOOL DestroyCursor()
		{
			ATLASSERT(m_hCursor!=NULL);
			BOOL bRet = ::DestroyCursor(m_hCursor);
			if( bRet ) m_hCursor = NULL;
			return bRet;
		}

		HCURSOR CopyCursor()
		{
			ATLASSERT(m_hCursor!=NULL);
			return (HCURSOR) ::CopyIcon( (HICON) m_hCursor );
		}

#if(WINVER >= 0x0500)
		BOOL GetCursorInfo(LPCURSORINFO pCursorInfo)
		{
			ATLASSERT(m_hCursor!=NULL);
			ATLASSERT(pCursorInfo);
			return ::GetCursorInfo(pCursorInfo);
		}
#endif
	};

	typedef CCursorT<true> CCursor;
	typedef CCursorT<false> CCursorHandle;


	/////////////////////////////////////////////////////////////////////////////
	// CAccelerator

	template< bool t_bManaged >
	class CAcceleratorT
	{
	public:
		HACCEL m_hAccel;

		// Constructor/destructor/operators

		CAcceleratorT(HACCEL hAccel = NULL) : m_hAccel(hAccel)
		{ 
		}

		~CAcceleratorT()
		{
			if( t_bManaged && m_hAccel != NULL ) ::DestroyAcceleratorTable(m_hAccel);
		}

		CAcceleratorT<t_bManaged>& operator=(HACCEL hAccel)
		{
			m_hAccel = hAccel;
			return *this;
		}

		void DestroyObject()
		{
			if( m_hAccel != NULL ) {
				::DestroyAcceleratorTable(m_hAccel);
				m_hAccel = NULL;
			}
		}

		void Attach(HACCEL hAccel)
		{
			if( t_bManaged && m_hAccel != NULL ) ::DestroyAcceleratorTable(m_hAccel);
			m_hAccel = hAccel;
		}  
		HCURSOR Detach()
		{
			HACCEL hAccel = m_hAccel;
			m_hAccel = NULL;
			return hAccel;
		}

		operator HACCEL() const { return m_hAccel; }

		bool IsNull() const { return m_hAccel == NULL; }

		// Create methods

		HACCEL LoadAccelerators(_U_STRINGorID accel)
		{
			ATLASSERT(m_hAccel==NULL);
#if (_ATL_VER >= 0x0700)
			m_hAccel = ::LoadAccelerators(ATL::_AtlBaseModule.GetResourceInstance(), accel.m_lpstr);
#else
			m_hAccel = ::LoadAccelerators(_Module.GetResourceInstance(), accel.m_lpstr);
#endif
			return m_hAccel;
		}
		HACCEL CreateAcceleratorTable(LPACCEL pAccel, int cEntries)
		{
			ATLASSERT(m_hAccel==NULL);
			ATLASSERT(!::IsBadReadPtr(lpAccelDst, sizeof(ACCEL)*cEntries));
			m_hAccel = ::CreateAcceleratorTable(pAccel, cEntries);
			return m_hAccel;
		}

		// Operations

		int CopyAcceleratorTable(LPACCEL lpAccelDst, int cEntries)
		{
			ATLASSERT(m_hAccel!=NULL);
			ATLASSERT(!::IsBadWritePtr(lpAccelDst, sizeof(ACCEL)*cEntries));
			return ::CopyAcceleratorTable(m_hAccel, lpAccelDst, cEntries);
		}

		BOOL TranslateAccelerator(HWND hWnd, LPMSG pMsg)
		{
			ATLASSERT(m_hAccel!=NULL);
			ATLASSERT(::IsWindow(hWnd));
			ATLASSERT(pMsg);
			return ::TranslateAccelerator(hWnd, m_hAccel, pMsg);
		}
	};

	typedef CAcceleratorT<true> CAccelerator;
	typedef CAcceleratorT<false> CAcceleratorHandle;


	/////////////////////////////////////////////////////////////////////////////
	// CLogFont

	class CLogFont : public LOGFONT
	{
	public:
		CLogFont() 
		{ 
			::ZeroMemory( (LOGFONT*) this, sizeof(LOGFONT) );
		}
		CLogFont(const LOGFONT& lf) 
		{ 
			Copy(&lf);
		}
		CLogFont(HFONT hFont)
		{
			ATLASSERT(::GetObjectType(hFont)==OBJ_FONT);
			::GetObject(hFont, sizeof(LOGFONT), (LOGFONT*) this);
		}
		HFONT CreateFontIndirect() 
		{ 
			return ::CreateFontIndirect(this); 
		}
		void SetBold() 
		{ 
			lfWeight = FW_BOLD; 
		}
		BOOL IsBold() const 
		{ 
			return lfWeight >= FW_BOLD; 
		}
		void MakeBolder(int iScale = 1)
		{
			lfWeight += FW_BOLD * iScale;
		}
		void MakeLarger(int iScale)
		{
			if( lfHeight > 0 ) lfHeight += iScale; else lfHeight -= iScale;
		}
		void SetHeight(long PointSize, HDC hDC = NULL) 
		{ 
			// For MM_TEXT mapping mode...
			// NOTE: MulDiv() gives correct rounding.
			lfHeight = -MulDiv(PointSize, ::GetDeviceCaps(hDC, LOGPIXELSY), 72); 
		}
		long GetHeight(HDC hDC = NULL) const
		{
			// For MM_TEXT mapping mode...
			// NOTE: MulDiv() gives correct rounding.
			return MulDiv(-lfHeight, 72, ::GetDeviceCaps(hDC, LOGPIXELSY));
		}
		long GetDeciPointHeight(HDC hDC = NULL)
		{
			POINT ptOrg = { 0, 0 };
			::DPtoLP(hDC, &ptOrg, 1);
			POINT pt = { 0, 0 };
			pt.y = abs(lfHeight) + ptOrg.y;
			::LPtoDP(hDC,&pt,1);
			return MulDiv(pt.y, 720, ::GetDeviceCaps(hDC,LOGPIXELSY)); // 72 points/inch, 10 decipoints/point
		}
		void SetHeightFromDeciPoint(long DeciPtHeight, HDC hDC = NULL)
		{
			POINT pt;
			pt.y = MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), DeciPtHeight, 720); // 72 points/inch, 10 decipoints/point
			::DPtoLP(hDC, &pt, 1);
			POINT ptOrg = { 0, 0 };
			::DPtoLP(hDC, &ptOrg, 1);
			lfHeight = -abs(pt.y - ptOrg.y);
		}
		void SetCaptionFont()
		{
			NONCLIENTMETRICS ncm = { 0 };
			ncm.cbSize = sizeof(ncm);
			::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
			Copy(&ncm.lfCaptionFont);
		}
		void SetMenuFont()
		{
			NONCLIENTMETRICS ncm = { 0 };
			ncm.cbSize = sizeof(ncm);
			::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
			Copy(&ncm.lfMenuFont);
		}
		void SetStatusFont()
		{
			NONCLIENTMETRICS ncm = { 0 };
			ncm.cbSize = sizeof(ncm);
			::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
			Copy(&ncm.lfStatusFont);
		}
		void SetMessageBoxFont()
		{
			NONCLIENTMETRICS ncm = { 0 };
			ncm.cbSize = sizeof(ncm);
			::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
			Copy(&ncm.lfMessageFont);
		}
		void Copy(const LOGFONT* lf)
		{
			ATLASSERT(lf);
			::CopyMemory( (LOGFONT*) this, lf, sizeof(LOGFONT) );
		}
		CLogFont& operator=(const CLogFont& src)
		{
			Copy(&src);
			return *this;
		}
		CLogFont& operator=(const LOGFONT& src)
		{
			Copy(&src);
			return *this;
		}
		CLogFont& operator=(HFONT hFont)
		{
			ATLASSERT(::GetObjectType(hFont)==OBJ_FONT);
			::GetObject(hFont, sizeof(LOGFONT), (LOGFONT*) this);
			return *this;
		}
		bool operator==(const LOGFONT& logfont) const
		{
			return( logfont.lfHeight == lfHeight &&
				logfont.lfWidth == lfWidth &&
				logfont.lfEscapement == lfEscapement &&
				logfont.lfOrientation == lfOrientation &&
				logfont.lfWeight == lfWeight &&
				logfont.lfItalic == lfItalic &&
				logfont.lfUnderline == lfUnderline &&
				logfont.lfStrikeOut == lfStrikeOut &&
				logfont.lfCharSet == lfCharSet &&
				logfont.lfOutPrecision == lfOutPrecision &&
				logfont.lfClipPrecision == lfClipPrecision &&
				logfont.lfQuality == lfQuality &&
				logfont.lfPitchAndFamily == lfPitchAndFamily &&
				::lstrcmp(logfont.lfFaceName, lfFaceName) == 0 );
		}
	};

#endif // _WTL_VER

	/////////////////////////////////////////////////////////////////////////////
	// CMemDC

	/*class CMemDC : public CDC
	{
	public:
		CDCHandle     m_dc;          // Owner DC
		CBitmap       m_bitmap;      // Offscreen bitmap
		CBitmapHandle m_hOldBitmap;  // Originally selected bitmap
		RECT          m_rc;          // Rectangle of drawing area

		CMemDC(HDC hDC, LPRECT pRect = NULL)
		{
			ATLASSERT(hDC!=NULL);
			m_dc = hDC;
			if( pRect != NULL ) m_rc = *pRect; else m_dc.GetClipBox(&m_rc);

			CreateCompatibleDC(m_dc);
			::LPtoDP(m_dc, (LPPOINT) &m_rc, sizeof(RECT) / sizeof(POINT));
			m_bitmap.CreateCompatibleBitmap(m_dc, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top);
			m_hOldBitmap = SelectBitmap(m_bitmap);
			::DPtoLP(m_dc, (LPPOINT) &m_rc, sizeof(RECT) / sizeof(POINT));
			SetWindowOrg(m_rc.left, m_rc.top);
		}
		~CMemDC()
		{
			// Copy the offscreen bitmap onto the screen.
			m_dc.BitBlt(m_rc.left, m_rc.top, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top,
				m_hDC, m_rc.left, m_rc.top, SRCCOPY);
			// Swap back the original bitmap.
			SelectBitmap(m_hOldBitmap);
		}
	};*/

/*class CMemDC : public CDC 
{  
private:         
	CBitmap m_bitmap;			// offscreen bitmap   
	CBitmapHandle m_oldBitmap;	// bitmap originally found in CMemDC   
	CDCHandle m_dc;				// Saves CDC passed in constructor   
	CRect m_rect;				// Rectangle of drawing area.   

public:  
	CMemDC(HDC hdc, LPRECT lpRect) : CDC() 
	{
		ASSERT(hdc != NULL);   

		// Some initialization
		m_dc = hdc;  
		m_oldBitmap = NULL;  

		// Get the rectangle to draw   
		if (lpRect == NULL) {  
			m_dc.GetClipBox(&m_rect);  
		} else {  
			m_rect = *lpRect;  
		}
  
		// Create a Memory DC   
		CreateCompatibleDC(m_dc);  
		m_dc.LPtoDP(&m_rect);  

		m_bitmap.CreateCompatibleBitmap(m_dc, m_rect.Width(), m_rect.Height());
		m_oldBitmap = this->SelectBitmap(m_bitmap);

		SetMapMode(m_dc.GetMapMode());  

		SetWindowExt(m_dc.GetWindowExt());  
		SetViewportExt(m_dc.GetViewportExt());  

		m_dc.DPtoLP(&m_rect);  
		SetWindowOrg(m_rect.left, m_rect.top);  

		// Fill background    
		FillSolidRect(m_rect, m_dc.GetBkColor());
	}  

	~CMemDC()    
	{      
		// Copy the offscreen bitmap onto the screen.   
		m_dc.BitBlt(m_rect.left, m_rect.top,  m_rect.Width(),  m_rect.Height(),  
			*this, m_rect.left, m_rect.top, SRCCOPY);            

		//Swap back the original bitmap.   
		this->SelectBitmap(m_oldBitmap);          
	}  

	// Allow usage as a pointer
	CDC* operator -> ()
	{  
		return this;  
	}         

	// Allow usage as a pointer       
	operator CDC* ()
	{
		return this;  
	}
};*/

template <bool t_bManaged>
class CMemDCT : public WTL::CDCT<t_bManaged>
{
	typedef WTL::CDCT<t_bManaged> Base;
protected:
	WTL::CDCHandle				m_dchandle;
	CRect						m_rect;
	WTL::CBitmapT<t_bManaged>	m_bmp;
	WTL::CBitmapHandle			m_bmphandle;
public:
	CMemDCT(HDC hDC = NULL) : Base(hDC) { }
	CMemDCT(HDC hDC, LPCRECT lpRect)
	{
		CreateCompatibleDC(hDC, lpRect);
	}

	template <bool o_bManaged>
	CMemDCT(CMemDCT<o_bManaged> & o) 
	{
		if(t_bManaged && m_hDC) {
			ATLASSERT(m_hDC != o.m_hDC);
			DeleteDC();
		}
		m_hDC = o.m_hDC;
		m_bmp = o.m_bmp;
		m_dchandle = o.m_dchandle;
		m_bmphandle = o.m_bmphandle;
	}

	/*template <bool o_bManaged>
	CMemDCT<t_bManaged> & operator = (CMemDCT<o_bManaged> & o)
	{
		
	}*/

	virtual ~CMemDCT()
	{
		if (t_bManaged && m_hDC) {
			if (m_dchandle) {
				m_dchandle.BitBlt(m_rect.left, m_rect.top,  m_rect.Width(),  m_rect.Height(),  
					m_hDC, m_rect.left, m_rect.top, SRCCOPY);
			}
			DeleteDC();
		}
	}

	//operator HDC () const { return m_hDC; }
	HDC GetDC()
	{
		return m_hDC;
	}
	BOOL GetRect(LPRECT lpRect)
	{
		ATLASSERT (lpRect);
		if (!IsNull()) {
			memcpy(lpRect, &m_rect, sizeof(RECT));
			return TRUE;
		}
		return FALSE;
	}

public:
	BOOL CreateCompatibleDC(HDC hDC, LPCRECT lpRect)
	{
		m_dchandle = hDC;
		if (lpRect == NULL) {  
			m_dchandle.GetClipBox(&m_rect);  
		} else {  
			m_rect = *lpRect;  
		}

		Base::CreateCompatibleDC(m_dchandle);
		m_dchandle.LPtoDP(&m_rect); 

		m_bmp.CreateCompatibleBitmap(m_dchandle, m_rect.right, m_rect.bottom);
		m_bmphandle = SelectBitmap(m_bmp);

		SetMapMode(m_dchandle.GetMapMode());

		SetBkMode(TRANSPARENT);
		//SetBkColor(m_dchandle.GetBkColor());
		//SetTextColor(m_dchandle.GetTextColor());

		CSize size;
		m_dchandle.GetWindowExt(&size);
		SetWindowExt(size);
		m_dchandle.GetViewportExt(&size);
		SetViewportExt(size);

		m_dchandle.DPtoLP(&m_rect);  
		SetWindowOrg(m_rect.left, m_rect.top);  

		// Fill background    
		//FillSolidRect(m_rect, m_dchandle.GetBkColor());
		//SetBkColor(m_dchandle.GetBkColor());
		//ExtTextOut(0, 0, ETO_OPAQUE, &m_rect, NULL, 0, NULL);

		//Base::BitBlt(0, 0, m_rect.Width(), m_rect.Height(), m_dchandle, m_rect.left, m_rect.top, SRCCOPY);

		return TRUE;
	}

	BOOL CreateCompatibleDC(HDC hDC, int nWidth, int nHeight)
	{
		RECT rc = {0};
		rc.right = nWidth;
		rc.bottom = nHeight;
		return CreateCompatibleDC(hDC, &rc);
	}

	//这里可以把BITMAP从CMEMDC拿出来，不删除
	BOOL DeleteDC(HBITMAP* pBitmap = NULL)
	{
		ASSERT(t_bManaged);
		if (!m_hDC) 
			return FALSE;
		if (m_bmp) {
			SelectBitmap(m_bmphandle);
			if (pBitmap) {
				*pBitmap = m_bmp;
			} else {
				m_bmp.DeleteObject();
			}
		}
		return Base::DeleteDC();
		return TRUE;
	}

	HBITMAP CreateBitmapFromRect(LPCRECT lpRect = NULL)
	{
		CRect rect(lpRect ? *lpRect : m_rect);
		CDC dc;
		dc.CreateCompatibleDC(*this);
		CBitmapHandle bmphandle;
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(*this, rect.Width(), rect.Height());
		bmphandle = dc.SelectBitmap(bmp);
		dc.BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, 
			*this, rect.left, rect.top, SRCCOPY);
		dc.SelectBitmap(bmphandle);
		return bmp.Detach();
	}

	HBRUSH CreateBrushFromRect(LPCRECT lpRect = NULL)
	{
		CBitmap bmp = CreateBitmapFromRect(lpRect);
		CBrush brush;
		brush.CreatePatternBrush(bmp);
		return brush.Detach();
	}
};
typedef CMemDCT<true> CMemDC;
typedef CMemDCT<false> CMemDCHandle;

template<class T>
class CPaintDCT : public WTL::CDC
{
public:
	// Data members
	T* m_pT;
	PAINTSTRUCT m_ps;

	CPaintDCT(T* pT, HDC hDC = NULL)
	{
		m_pT = NULL;
		memset(&m_ps, 0, sizeof(m_ps));
		if (hDC) {
			Attach(hDC);
		} else {
			ATLASSERT(pT->IsWindow());
			m_pT = pT;
			m_hDC = m_pT->BeginPaint(&m_ps);
		}
	}
	
	~CPaintDCT()
	{
		ATLASSERT(m_hDC != NULL);
		if (m_pT) {
			m_pT->EndPaint(&m_ps);
			m_pT = NULL;
		}
		Detach();
	}
};

template<class T>
class CClientDCT : public WTL::CDC
{
public:
	// Data members
	T* m_pT;
	
	// Constructor/destructor
	CClientDCT(T* pT)
	{
		ATLASSERT(pT == NULL || pT->IsWindow());
		m_pT = pT;
		m_hDC = m_pT->GetDC();
	}
	
	~CClientDCT()
	{
		ATLASSERT(m_hDC != NULL);
		m_pT->ReleaseDC(Detach());
	}
};

template<class T>
class CWindowDCT : public WTL::CDC
{
public:
	// Data members
	T* m_pT;
	
	// Constructor/destructor
	CWindowDCT(T* pT)
	{
		ATLASSERT(pT == NULL || pT->IsWindow());
		m_pT = pT;
		m_hDC = m_pT->GetWindowDC();
	}
	
	~CWindowDCT()
	{
		ATLASSERT(m_hDC != NULL);
		m_pT->ReleaseDC(Detach());
	}
};

} // namespace WTL

namespace UIgdi
{
	// Default GUI font helper - "MS Shell Dlg" stock font
	inline HFONT GetDefaultGuiFont()
	{
		return WTL::AtlGetDefaultGuiFont();
	}

	// Control font helper - default font for controls not in a dialog
	// (NOTE: Caller owns the font, and should destroy it when it's no longer needed)
	inline HFONT CreateControlFont()
	{
		return WTL::AtlCreateControlFont();
	}

	// Bold font helper
	// (NOTE: Caller owns the font, and should destroy it when it's no longer needed)
	inline HFONT CreateBoldFont(HFONT hFont = NULL)
	{
		return WTL::AtlCreateBoldFont(hFont);
	}

	inline HICON IconFromResource(HINSTANCE hInstResource, STRINGorID ResOrID, int nWidth = 0, int nHeight = 0)
	{
		if (hInstResource == NULL) {
			hInstResource = UIHelper::GetResourceInstance();
		}
		HICON hIcon = (HICON)::LoadImage(hInstResource, ResOrID, IMAGE_ICON, nWidth, nHeight, LR_DEFAULTCOLOR);
		return hIcon;
	}

	inline HICON IconFromFile(LPCTSTR lpszFilePath, int nWidth = 0, int nHeight = 0)
	{
		HICON hIcon = (HICON)::LoadImage(NULL, lpszFilePath, IMAGE_ICON, nWidth, nHeight, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
		return hIcon;
	}

	inline HICON IconFromDLL(LPCTSTR lpszDLLPath, STRINGorID ResOrID, int nWidth = 0, int nHeight = 0)
	{
		HICON hIcon = NULL;
		HINSTANCE hInstResource = NULL;
		if (NULL == lpszDLLPath) {
			hInstResource = UIHelper::GetResourceInstance();
			hIcon = IconFromResource(hInstResource, ResOrID, nWidth, nHeight);
		} else {
			hInstResource = ::LoadLibraryEx(lpszDLLPath, NULL, 0);
			if (NULL != hInstResource) {
				hIcon = IconFromResource(hInstResource, ResOrID, nWidth, nHeight);
				::FreeLibrary(hInstResource);
			}
		}
		return hIcon;
	}

	inline HBITMAP BitmapFromResource(HINSTANCE hInstResource, STRINGorID ResOrID)
	{
		if (hInstResource == NULL) {
			hInstResource = UIHelper::GetResourceInstance();
		}
		HBITMAP hBitmap = (HBITMAP)::LoadImage(hInstResource, ResOrID, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
		return hBitmap;
	}

	inline HBITMAP BitmapFromFile(LPCTSTR lpszFilePath)
	{
		HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, lpszFilePath, IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
		return hBitmap;
	}

	inline HBITMAP BitmapFromDLL(LPCTSTR lpszDLLPath, STRINGorID ResOrID)
	{
		HBITMAP hBitmap = NULL;
		HINSTANCE hInstResource = NULL;
		if (NULL == lpszDLLPath) {
			hBitmap = BitmapFromResource(NULL, ResOrID);
		} else {
			hInstResource = ::LoadLibraryEx(lpszDLLPath, NULL, 0);
			if (NULL != hInstResource) {
				hBitmap = BitmapFromResource(hInstResource, ResOrID);
				::FreeLibrary(hInstResource);
			}
		}
		return hBitmap;
	}
	// 	static HBITMAP BitmapFromBitmap(HBITMAP hBitmap)
	// 	{
	// 		return CreateBitmapFromBitmap(hBitmap, NULL);
	// 	}
	inline CString StringFromResource(HINSTANCE hInstResource, UINT nID)
	{
		if (hInstResource == NULL) {
			hInstResource = UIHelper::GetResourceInstance();
		}

		CString strString;
#ifdef _UNICODE
		const int CHAR_FUDGE = 1;   // one TCHAR unused is good enough
#else
		const int CHAR_FUDGE = 2;   // two BYTES unused for case of DBC last char
#endif
		int nSize = 256;
		do
		{
			int nLen = ::LoadString(hInstResource, nID, strString.GetBuffer(nSize - 1), nSize);
			if (nSize - nLen > CHAR_FUDGE) {
				break;
			}
			nSize += 256;
		} while (1);
		strString.ReleaseBuffer();
		return strString;
	}

	inline CString StringFromDLL(LPCTSTR lpszDLLPath, UINT nID)
	{
		CString strString;
		HINSTANCE hInstResource = NULL;
		if (NULL == lpszDLLPath) {
			strString = StringFromResource(NULL, nID);
		} else {
			hInstResource = ::LoadLibraryEx(lpszDLLPath, NULL, 0);
			if (NULL != hInstResource) {
				strString = StringFromResource(hInstResource, nID);
				::FreeLibrary(hInstResource);
			}
		}
		return strString;
	}

	///////////////////////////////////////////////////////////
	// Get tooltip string for menu and toolbar items from the 
	// resources of the application.
	// 
	// Parameters:
	//		nID - Resource ID of the string
	//		nNumParam - Which parameter will gets:
	//					 0=long,
	//					 1=short,
	//					 2=disable
	//
	//
	// Format prompt string:  long prompt \n short prompt \n disable prompt
	////////////////////////////////////////////////////////////
	inline CString TooptipStringFromResource(HINSTANCE hInstResource, UINT nID, UINT nNumParam = 0)
	{
		CString strString = StringFromResource(hInstResource, nID);
		if (!strString.IsEmpty()) {
			int nFirst = 0;
			int nLast = nFirst;
			UINT nCount = 0;
			while ((nCount <= nNumParam) && (nFirst < strString.GetLength()))
			{
				nLast = strString.Find(_T('\n'), nFirst);
				if (nLast < 0) {
					if (nCount == nNumParam) {
						strString = strString.Mid(nFirst, strString.GetLength() - nFirst);
					} else {
						strString.Empty();
					}
					break;
				} else {
					if (nCount == nNumParam) {
						strString = strString.Mid(nFirst, nLast - nFirst);
						break;
					} else {
						nFirst = nLast + 1;
					}
				}
				nCount ++;
			}
		}
		return strString;
	}

	inline HBITMAP CreateBitmapFromDC(HDC hdc, LPRECT lpRect)
	{
		ASSERT(hdc);
		ASSERT(lpRect);
		CRect rect(lpRect);
		WTL::CDC dc;
		dc.CreateCompatibleDC(hdc);
		WTL::CBitmapHandle bmphandle;
		WTL::CBitmap bmp;
		bmp.CreateCompatibleBitmap(hdc, rect.Width(), rect.Height());
		bmphandle = dc.SelectBitmap(bmp);
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), hdc, rect.left, rect.top, SRCCOPY);
		dc.SelectBitmap(bmphandle);
		return bmp.Detach();
	}

	inline HBRUSH CreateBrushFromDC(HDC hdc, LPRECT lpRect)
	{
		WTL::CBitmap bmp = CreateBitmapFromDC(hdc, lpRect);
		WTL::CBrush brush;
		brush.CreatePatternBrush(bmp);
		return brush.Detach();
	}

	inline HBITMAP CreateBitmapFromBitmap(HBITMAP hBitmap, LPRECT lpRect = NULL)
	{
		ASSERT(hBitmap);
		RECT rect = {0};
		BITMAP bitmap;
		::GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		if (lpRect == NULL) {
			rect.right = bitmap.bmWidth;
			rect.bottom = bitmap.bmHeight;
			lpRect = &rect;
		}

		HDC hScrDC;
		hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);

		HDC hSrcDC;
		hSrcDC = CreateCompatibleDC(hScrDC);
		HGDIOBJ hPreSrcObj = ::SelectObject(hSrcDC, hBitmap);

		HDC hDstDC = CreateCompatibleDC(hScrDC);
		HBITMAP hDstBmp;
		hDstBmp = CreateCompatibleBitmap(hScrDC, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);
		HGDIOBJ hPreDstObj = ::SelectObject(hDstDC, hDstBmp);
		::BitBlt(hDstDC, 0, 0, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, 
			hSrcDC, lpRect->left, lpRect->top, SRCCOPY);
		::SelectObject(hDstDC, hPreDstObj);

		::SelectObject(hSrcDC, hPreSrcObj);
		::DeleteDC(hDstDC);
		::DeleteDC(hSrcDC);

		::DeleteDC(hScrDC);

		return hDstBmp;
	}

	inline HBRUSH CreateBrushFromBitmap(HBITMAP hBitmap, LPRECT lpRect = NULL)
	{
		HBITMAP hSubBitmap = NULL;
		if ((hSubBitmap = (HBITMAP)CreateBitmapFromBitmap(hBitmap, lpRect)) != NULL) {
			HBRUSH hBrush = CreatePatternBrush(hSubBitmap);
			::DeleteObject((HGDIOBJ)hSubBitmap);
			return hBrush;
		}
		return NULL;
	}

	inline HBITMAP CreateBitmapFromWnd(HWND hwnd, LPRECT lpRect = NULL)
	{
		RECT rtWnd;
		::GetClientRect(hwnd, &rtWnd);
		if (lpRect != NULL) {
			rtWnd = *lpRect;
		}
		HDC hSrcDC = ::GetDC(hwnd);
		HDC hDstDC = CreateCompatibleDC(hSrcDC);
		HBITMAP hDstBmp;
		hDstBmp = CreateCompatibleBitmap(hSrcDC, rtWnd.right - rtWnd.left, rtWnd.bottom - rtWnd.top);
		HGDIOBJ hPreDstObj = ::SelectObject(hDstDC, hDstBmp);
		::BitBlt(hDstDC, 0, 0, rtWnd.right - rtWnd.left, rtWnd.bottom - rtWnd.top, 
			hSrcDC, rtWnd.left, rtWnd.top, SRCCOPY);
		::SelectObject(hDstDC, hPreDstObj);
		::DeleteDC(hDstDC);
		::ReleaseDC(hwnd, hSrcDC);

		return hDstBmp;
	}

	inline HBRUSH CreateBrushFromWnd(HWND hwnd, LPRECT lpRect = NULL)
	{
		HBITMAP hBitmap = NULL;
		if ((hBitmap = (HBITMAP)CreateBitmapFromWnd(hwnd, lpRect)) != NULL) {
			HBRUSH hBrush = CreatePatternBrush(hBitmap);
			::DeleteObject((HGDIOBJ)hBitmap);
			return hBrush;
		}
		return NULL;
	}

	inline HBITMAP CreateBitmapFromChildWnd(HWND hwnd, HWND hChild)
	{
		RECT rcChild;
		::GetWindowRect(hChild, &rcChild);
		::ScreenToClient(hwnd, (LPPOINT)&rcChild);
		::ScreenToClient(hwnd, ((LPPOINT)&rcChild) + 1);
		if ((DWORD)GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_LAYOUTRTL) {
			LONG temp = rcChild.left; 
			rcChild.left = rcChild.right; 
			rcChild.right = temp;
		}
		return CreateBitmapFromWnd(hwnd, &rcChild);
	}

	inline HBRUSH CreateBrushFromChildWnd(HWND hwnd, HWND hChild)
	{
		RECT rcChild;
		::GetWindowRect(hChild, &rcChild);
		::ScreenToClient(hwnd, (LPPOINT)&rcChild);
		::ScreenToClient(hwnd, ((LPPOINT)&rcChild) + 1);
		if ((DWORD)GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_LAYOUTRTL) {
			LONG temp = rcChild.left; 
			rcChild.left = rcChild.right; 
			rcChild.right = temp;
		}
		return CreateBrushFromWnd(hwnd, &rcChild);
	}

	inline COLORREF GrayColor(COLORREF crColor)
	{
		BYTE nGrayColor = (BYTE)((GetRValue(crColor) * 0.299) + (GetGValue(crColor) * 0.587) + (GetBValue(crColor) * 0.114));
		return RGB(nGrayColor, nGrayColor, nGrayColor);
	}
	inline COLORREF GrayMirrorColor(COLORREF crColor)
	{
		BYTE nGrayColor = (BYTE)((GetBValue(crColor) * 0.299) + (GetGValue(crColor) * 0.587) + (GetRValue(crColor) * 0.114));
		return RGB(nGrayColor, nGrayColor, nGrayColor);
	}

	inline COLORREF InvertColor(COLORREF crColor)
	{
		return RGB(255 - GetRValue(crColor), 255 - GetGValue(crColor), 255 - GetBValue(crColor));
	}

	inline COLORREF DarkenColor(COLORREF crColor, double darken)
	{
		if (darken >= 0.0 && darken < 1.0) {
			BYTE color_r, color_g, color_b;
			color_r = (BYTE)(GetRValue(crColor) * darken);
			color_g = (BYTE)(GetGValue(crColor) * darken);
			color_b = (BYTE)(GetBValue(crColor) * darken);
			crColor = RGB(color_r, color_g, color_b);
		}
		return crColor;
	}

	inline COLORREF LightenColor(COLORREF crColor, double lighten)
	{
		if (lighten > 0.0 && lighten <= 1.0) {
			BYTE color_r, color_g, color_b;
			lighten += 1.0;
			color_r = (BYTE)min((DWORD)GetRValue(crColor) * lighten, 255.0);
			color_g = (BYTE)min((DWORD)GetGValue(crColor) * lighten, 255.0);
			color_b = (BYTE)min((DWORD)GetBValue(crColor) * lighten, 255.0);
			crColor = RGB(color_r, color_g, color_b);
		}
		return crColor;
	}

	inline COLORREF AlphaColor(COLORREF crSrc, double src_darken, COLORREF crDest, double dest_darken)
	{
		return RGB (GetRValue (crSrc) * src_darken + GetRValue (crDest) * dest_darken, 
			GetGValue (crSrc) * src_darken + GetGValue (crDest) * dest_darken, 
			GetBValue (crSrc) * src_darken + GetBValue (crDest) * dest_darken);
	}

	// 取得图片平均颜色
	inline COLORREF AverageColorFromDC(HDC hDC)
	{
		COLORREF color = CLR_INVALID;

		WTL::CDCHandle TempDC(hDC);
		WTL::CBitmapHandle Bitmap = TempDC.GetCurrentBitmap();
		if (Bitmap) {
			BITMAP bmp;
			if(Bitmap.GetBitmap(&bmp)) {
				LONG nImageSize = bmp.bmWidth * bmp.bmHeight;
				// 定义位图信息   
				BITMAPINFO bi;  
				bi.bmiHeader.biSize = sizeof(bi.bmiHeader);  
				bi.bmiHeader.biWidth = bmp.bmWidth;  
				bi.bmiHeader.biHeight = bmp.bmHeight;  
				bi.bmiHeader.biPlanes = 1;  
				bi.bmiHeader.biBitCount = 32;   
				bi.bmiHeader.biCompression = BI_RGB;   
				bi.bmiHeader.biSizeImage = nImageSize * 4; // 32 bit
				bi.bmiHeader.biClrUsed = 0;  
				bi.bmiHeader.biClrImportant = 0;  

				// 获取位图数据   
				BYTE* pBits = (BYTE*)new BYTE[bi.bmiHeader.biSizeImage];
				ZeroMemory(pBits, bi.bmiHeader.biSizeImage);  
				int nLine = ::GetDIBits(TempDC, (HBITMAP)Bitmap, 0, bmp.bmHeight, pBits, &bi, DIB_RGB_COLORS);
				if (!nLine) {  
					delete []pBits;
					pBits = NULL;
				} else {
					long r = 0, g = 0, b = 0;
					for (LONG i = 0; i < bmp.bmWidth; i++) 
					{     
						for (LONG j = 0; j < bmp.bmHeight; j++)     
						{     
							b += pBits[(j * bmp.bmWidth + i) * 4];	
							g += pBits[(j * bmp.bmWidth + i) * 4 + 1];
							r += pBits[(j * bmp.bmWidth + i) * 4 + 2];
						}
					}
					delete []pBits;
					pBits = NULL;

					color = RGB(r / nImageSize, g / nImageSize, b / nImageSize);
				}
			}
		}
		return color;
	}

	inline COLORREF AverageColorFromBitmap(HBITMAP hBitmap)
	{
		COLORREF color = CLR_INVALID;

		WTL::CDC TempDC;
		TempDC.CreateCompatibleDC(NULL);
		HBITMAP hOldBitmap = TempDC.SelectBitmap(hBitmap);
		color = AverageColorFromDC(TempDC);
		TempDC.SelectBitmap(hOldBitmap);
		TempDC.DeleteDC();

		return color;
	}

	inline void FillGradient (HDC hDC, LPCRECT lpRect, COLORREF colorStart, COLORREF colorFinish, BOOL bHoriz = TRUE)
	{
		// this will make 2^6 = 64 fountain steps
		int nShift = 6;
		int nSteps = 1 << nShift;

		RECT r2;
		r2.top = lpRect->top;
		r2.left = lpRect->left;
		r2.right = lpRect->right;
		r2.bottom = lpRect->bottom;

		int nHeight = lpRect->bottom - lpRect->top;
		int nWidth = lpRect->right - lpRect->left;

		for (int i = 0; i < nSteps; i++)
		{
			BYTE bR = (BYTE) ((GetRValue(colorStart) * (nSteps - i) +
				GetRValue(colorFinish) * i) >> nShift);
			BYTE bG = (BYTE) ((GetGValue(colorStart) * (nSteps - i) +
				GetGValue(colorFinish) * i) >> nShift);
			BYTE bB = (BYTE) ((GetBValue(colorStart) * (nSteps - i) +
				GetBValue(colorFinish) * i) >> nShift);

			HBRUSH hBrush = ::CreateSolidBrush(RGB(bR, bG, bB));
			// then paint with the resulting color
			if (!bHoriz) {
				r2.top = lpRect->top + ((i * nHeight) >> nShift);
				r2.bottom = lpRect->top + (((i + 1) * nHeight) >> nShift);
				if ((r2.bottom - r2.top) > 0)
					::FillRect(hDC, &r2, hBrush);
			} else {
				r2.left = lpRect->left + ((i * nWidth) >> nShift);
				r2.right = lpRect->left + (((i + 1) * nWidth) >> nShift);
				if ((r2.right - r2.left) > 0)
					::FillRect(hDC, &r2, hBrush);
			}
			::DeleteObject(hBrush);
			hBrush = NULL;
		}
	}

	inline void FillSolidRect(HDC hdc, LPCRECT lprc, COLORREF cr)
	{
		ASSERT(hdc != NULL);
		::SetBkColor(hdc, cr);
		::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, lprc, NULL, 0, NULL);
	}

	inline void DrawRectangle(HDC hdc, int left, int top, int right, int bottom)
	{
		ASSERT(hdc);
		::MoveToEx(hdc, left, top, NULL);
		::LineTo(hdc, right-1, top);
		::LineTo(hdc, right-1, bottom-1);
		::LineTo(hdc, left, bottom-1);
		::LineTo(hdc, left, top);
	}

	inline void DrawRectangle(HDC hdc, LPRECT lprc)
	{
		ASSERT(hdc);
		::MoveToEx(hdc, lprc->left, lprc->top, NULL);
		::LineTo(hdc, lprc->right-1, lprc->top);
		::LineTo(hdc, lprc->right-1, lprc->bottom-1);
		::LineTo(hdc, lprc->left, lprc->bottom-1);
		::LineTo(hdc, lprc->left, lprc->top);
	}

	inline void DrawRectangle(HDC hdc, LPRECT lprc , int PStyle, int nWidth, COLORREF color, int nR2Mode)
	{
		ASSERT(hdc);
		int nOldR2Mode = SetROP2(hdc, nR2Mode);
		HPEN hPen = ::CreatePen(PStyle, nWidth, color);
		HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);
		::MoveToEx(hdc, lprc->left, lprc->top, NULL);
		::LineTo(hdc, lprc->right-1, lprc->top);
		::LineTo(hdc, lprc->right-1, lprc->bottom-1);
		::LineTo(hdc, lprc->left, lprc->bottom-1);
		::LineTo(hdc, lprc->left, lprc->top);
		::SelectObject(hdc, hOldPen);
		::DeleteObject(hPen);
		SetROP2(hdc, nOldR2Mode);
	}

	inline void DrawPolyLine(HDC hdc, LPPOINT lpPoints, int nCount)
	{
		ASSERT(hdc);
		if (nCount >= 2) {
			/*::MoveToEx(hdc, lpPoints[0].x, lpPoints[0].y, NULL);
			for (int i = 1; i < nCount; i++)
			{
				::LineTo(hdc, lpPoints[i].x, lpPoints[i].y);
			}*/
			::Polyline(hdc, lpPoints, nCount);
		}
	}

	inline void DrawPolyLine(HDC hdc, LPPOINT lpPoints, int nCount, int PStyle, int nWidth, COLORREF color, int nR2Mode)
	{
		ASSERT(hdc);
		if (nCount >= 2) {
			int nOldR2Mode = ::SetROP2(hdc, nR2Mode);
			HPEN hPen = ::CreatePen(PStyle, nWidth, color);
			HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);
#if 1
			::MoveToEx(hdc, lpPoints[0].x, lpPoints[0].y, NULL);
			for (int i = 1; i < nCount; i++)
			{
				::LineTo(hdc, lpPoints[i].x, lpPoints[i].y);
			}
#else
			::Polyline(hdc, lpPoints, nCount);
#endif//
			::SelectObject(hdc, hOldPen);
			::DeleteObject(hPen);
			::SetROP2(hdc, nOldR2Mode);
		}
	}

	inline void DrawLine(HDC hdc,int x1, int y1,int x2, int y2)
	{
		ASSERT(hdc);
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
	}

	inline void DrawLine(HDC hdc,int x1, int y1,int x2, int y2, int PStyle, int nWidth, COLORREF color, int nR2Mode)
	{
		ASSERT(hdc);
		int nOldnR2Mode = SetROP2(hdc, nR2Mode);
		HPEN hPen = ::CreatePen(PStyle, nWidth, color);
		HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
		::SelectObject(hdc, hOldPen);
		::DeleteObject(hPen);
		SetROP2(hdc, nOldnR2Mode);
	}

	inline void DrawLine(HDC hdc,const POINT& pt1, const POINT& pt2)
	{
		DrawLine(hdc, pt1.x, pt1.y, pt2.x, pt2.y);
	}

	inline void DrawLine(HDC hdc,const POINT& pt1, const POINT& pt2, int PStyle, int nWidth, COLORREF color, int nR2Mode)
	{
		DrawLine(hdc, pt1.x, pt1.y, pt2.x, pt2.y, PStyle, nWidth, color, nR2Mode);
	}

	//If the function succeeds, the return value is the height of the text in logical units. 
	//If DT_VCENTER or DT_BOTTOM is specified, the return value is the offset from lprc->top to the bottom of the drawn text
	//If the function fails, the return value is zero. 

	inline int DrawTextA(HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format)
	{
		return ::DrawTextA(hdc, lpchText, cchText, lprc, format);
	}

	inline int DrawTextW(HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format)
	{
		ASSERT(hdc);
		return ::DrawTextW(hdc, lpchText, cchText, lprc, format);
	}

	inline int DrawTextA(HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format, COLORREF color, HFONT hFont = NULL, BOOL bVert = FALSE)
	{
		ASSERT(hdc);
		int rlt = 0;
		COLORREF crTextColor = CLR_INVALID;
		if(color!=CLR_INVALID)
			crTextColor = ::SetTextColor(hdc, color);
		HFONT hOldFont = NULL;
		if(hFont)
			hOldFont = (HFONT)::SelectObject(hdc, (HGDIOBJ)hFont);
		if (bVert) {
			int i;
			CHAR ch[2] = {0};
			RECT rc = *lprc;
			UINT cyPadding = bVert;

			TEXTMETRICW tm;
			::GetTextMetricsW(hdc, &tm);

			if ((format&DT_CENTER)) {
				rc.left = lprc->left+((lprc->right-lprc->left)-tm.tmMaxCharWidth)/2;
			} else if ((format&DT_RIGHT)) {
				rc.left = lprc->right-tm.tmMaxCharWidth;
			}
			if ((format&DT_VCENTER)) {
				rc.top = lprc->top+((lprc->bottom-lprc->top)-(tm.tmHeight*cchText+cyPadding*(cchText-1)))/2;
				rlt = (rc.top+(tm.tmHeight*cchText+cyPadding*(cchText-1)))-lprc->top;
			} else if ((format&DT_BOTTOM)) {
				rc.top = lprc->bottom-(tm.tmHeight*cchText+cyPadding*(cchText-1));
				rlt = (rc.top+(tm.tmHeight*cchText+cyPadding*(cchText-1)))-lprc->top;
			}
			rc.right = rc.left + tm.tmMaxCharWidth;
			rc.bottom = rc.top + tm.tmHeight;

			for(i=0; i<cchText; i++)
			{
				ch[0] = lpchText[i];
				::DrawTextA(hdc, ch, 1, &rc, format);
				OffsetRect(&rc, 0, (tm.tmHeight+cyPadding));
			}
		} else {
			rlt = ::DrawTextA(hdc, lpchText, cchText, lprc, format);
		}
		if (hOldFont)
			::SelectObject(hdc, (HGDIOBJ)hOldFont);
		if (color != CLR_INVALID)
			::SetTextColor(hdc, crTextColor);
		return rlt;
	}

	inline int DrawTextW(HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format, COLORREF color, HFONT hFont = NULL, BOOL bVert = FALSE)
	{
		ASSERT(hdc);
		int rlt = 0;
		COLORREF crTextColor = CLR_INVALID;
		if(color!=CLR_INVALID)
			crTextColor = ::SetTextColor(hdc, color);
		HFONT hOldFont = NULL;
		if(hFont)
			hOldFont = (HFONT)::SelectObject(hdc, (HGDIOBJ)hFont);
		if (bVert) {
			int i;
			WCHAR ch[2] = {0};
			RECT rc = *lprc;
			UINT cyPadding = bVert;

			TEXTMETRICW tm;
			::GetTextMetricsW(hdc, &tm);

			if ((format&DT_CENTER)) {
				rc.left = lprc->left+((lprc->right-lprc->left)-tm.tmMaxCharWidth)/2;
			} else if ((format&DT_RIGHT)) {
				rc.left = lprc->right-tm.tmMaxCharWidth;
			}
			if ((format&DT_VCENTER)) {
				rc.top = lprc->top+((lprc->bottom-lprc->top)-(tm.tmHeight*cchText+cyPadding*(cchText-1)))/2;
				rlt = (rc.top+(tm.tmHeight*cchText+cyPadding*(cchText-1)))-lprc->top;
			} else if ((format&DT_BOTTOM)) {
				rc.top = lprc->bottom-(tm.tmHeight*cchText+cyPadding*(cchText-1));
				rlt = (rc.top+(tm.tmHeight*cchText+cyPadding*(cchText-1)))-lprc->top;
			}
			rc.right = rc.left + tm.tmMaxCharWidth;
			rc.bottom = rc.top + tm.tmHeight;

			for(i=0; i<cchText; i++)
			{
				ch[0] = lpchText[i];
				::DrawTextW(hdc, ch, 1, &rc, format);
				OffsetRect(&rc, 0, (tm.tmHeight+cyPadding));
			}
		} else {
			rlt = ::DrawTextW(hdc, lpchText, cchText, lprc, format);
		}
		if (hOldFont)
			::SelectObject(hdc, (HGDIOBJ)hOldFont);
		if (color != CLR_INVALID)
			::SetTextColor(hdc, crTextColor);
		return rlt;
	}
#ifdef UNICODE
#define DrawText	DrawTextW
#else
#define DrawText	DrawTextA
#endif//

	static void DrawBitmap(HDC hdc, int x, int y, int cx, int cy, HBITMAP hbmp, int x1, int y1, BYTE alpha = 255)
	{
		HDC hMemDC = ::CreateCompatibleDC(hdc);
		ASSERT(hMemDC);
		HGDIOBJ hoBmp = ::SelectObject(hMemDC, (HGDIOBJ)hbmp);
		if (alpha >= 255) {
			::BitBlt(hdc, x, y, cx, cy, hMemDC, x1, y1, SRCCOPY);
		} else {
			BLENDFUNCTION bf = {0};
			bf.BlendOp = AC_SRC_OVER;
			bf.SourceConstantAlpha = alpha;
			::AlphaBlend(hMemDC, x, y, cx, cy, hMemDC, x1, y1, cx, cy, bf);
		}
		::SelectObject(hMemDC, (HGDIOBJ)hoBmp);
		::DeleteDC(hMemDC);
	}

	static void StretchBitmap(HDC hdc, int x, int y, int cx, int cy, HBITMAP hbmp, int x1, int y1, int cx1, int cy1, BYTE alpha = 255)
	{
		HDC hMemDC = ::CreateCompatibleDC(hdc);
		ASSERT(hMemDC);
		HGDIOBJ hoBmp = ::SelectObject(hMemDC, (HGDIOBJ)hbmp);
		if (alpha >= 255) {
			::StretchBlt(hdc, x, y, cx, cy, hMemDC, x1, y1, cx1, cy1, SRCCOPY);
		} else {
			BLENDFUNCTION bf = {0};
			bf.BlendOp = AC_SRC_OVER;
			bf.SourceConstantAlpha = alpha;
			::AlphaBlend(hMemDC, x, y, cx, cy, hMemDC, x1, y1, cx1, cy1, bf);
		}
		::SelectObject(hMemDC, (HGDIOBJ)hoBmp);
		::DeleteDC(hMemDC);
	}

	inline void TitleBitBlt(HDC hDestDC, int nDestX, int nDestY, DWORD dwDestWidth, DWORD dwDestHeight, HDC hSrcDC, int nSrcX, int nSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight)
	{
		// Horizontal copying
		int right, bottom;
		int nDestRight = (int)(nDestX + dwDestWidth);
		int nDestBottom = (int)(nDestY + dwDestHeight);
		for (int x = nDestX; x < nDestRight; x+= dwSrcWidth)
		{
			right = min (x + (int)dwSrcWidth, nDestRight);
			// Vertical copying
			for (int y = nDestY; y < nDestBottom; y+= dwSrcHeight)
			{
				bottom = min (y + (int)dwSrcHeight, nDestBottom);
				::BitBlt(hDestDC, x, y, right - x, bottom - y, hSrcDC, nSrcX, nSrcY, SRCCOPY);
			}
		}
	}

	inline void TransBitBlt(HDC hdcDest, int nDestX, int nDestY, int nDestWidth, int nDestHeight,
		HDC hdcSrc, int nSrcX, int nSrcY, int nSrcWidth, int nSrcHeight, COLORREF crColorKey)
	{
		HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nDestWidth, nDestHeight); // 创建兼容位图
		HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nDestWidth, nDestHeight, 1, 1, NULL); // 创建单色掩码位图
		HDC hImageDC = CreateCompatibleDC(hdcDest);
		HDC hMaskDC = CreateCompatibleDC(hdcDest);
		hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
		hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);
		// 将源DC中的位图拷贝到临时DC中
		if (nDestWidth == nSrcWidth && nDestHeight == nSrcHeight) {
			::BitBlt(hImageDC, 0, 0, nDestWidth, nDestHeight, hdcSrc, nSrcX, nSrcY, SRCCOPY);
		} else {
			::StretchBlt(hImageDC, 0, 0, nDestWidth, nDestHeight, hdcSrc, nSrcX, nSrcY, nSrcWidth, nSrcHeight, SRCCOPY);
		}
		// 设置透明色
		SetBkColor(hImageDC, crColorKey);
		// 生成透明区域为白色，其它区域为黑色的掩码位图
		::BitBlt(hMaskDC, 0, 0, nDestWidth, nDestHeight, hImageDC, 0, 0, SRCCOPY);
		// 生成透明区域为黑色，其它区域保持不变的位图
		SetBkColor(hImageDC, RGB(0,0,0));
		SetTextColor(hImageDC, RGB(255,255,255));
		::BitBlt(hImageDC, 0, 0, nDestWidth, nDestHeight, hMaskDC, 0, 0, SRCAND);
		//透明部分保持屏幕不变，其它部分变成黑色
		SetBkColor(hdcDest, RGB(255,255,255));
		SetTextColor(hdcDest, RGB(0,0,0));
		::BitBlt(hdcDest, nDestX, nDestY, nDestWidth, nDestHeight, hMaskDC, 0, 0, SRCAND);
		// "或"运算,生成最终效果
		::BitBlt(hdcDest, nDestX, nDestY, nDestWidth, nDestHeight, hImageDC, 0, 0, SRCPAINT);
		// 清理、恢复 
		SelectObject(hImageDC, hOldImageBMP);
		DeleteDC(hImageDC);
		SelectObject(hMaskDC, hOldMaskBMP);
		DeleteDC(hMaskDC);
		DeleteObject(hImageBMP);
		DeleteObject(hMaskBMP);
	}

	inline void AlphaBitBlt(HDC hDestDC, int nDestX, int nDestY, DWORD dwWidth, DWORD dwHeight, HDC hSrcDC, int nSrcX, int nSrcY, BYTE nAlpha)
	{
		ASSERT ((NULL != hDestDC) || (NULL != hSrcDC));
		if (nAlpha >= 100) {
			::BitBlt(hDestDC, nDestX, nDestY, dwWidth, dwHeight, hSrcDC, nSrcX, nSrcY, SRCCOPY);
		} else {
			HDC hTempDC = ::CreateCompatibleDC(hDestDC);
			if (NULL == hTempDC)
				return;
			LPBITMAPINFO lpbiSrc;
			lpbiSrc = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
			lpbiSrc->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			lpbiSrc->bmiHeader.biWidth = dwWidth;
			lpbiSrc->bmiHeader.biHeight = dwHeight;
			lpbiSrc->bmiHeader.biPlanes = 1;
			lpbiSrc->bmiHeader.biBitCount = 32;
			lpbiSrc->bmiHeader.biCompression = BI_RGB;
			lpbiSrc->bmiHeader.biSizeImage = dwWidth * dwHeight;
			lpbiSrc->bmiHeader.biXPelsPerMeter = 0;
			lpbiSrc->bmiHeader.biYPelsPerMeter = 0;
			lpbiSrc->bmiHeader.biClrUsed = 0;
			lpbiSrc->bmiHeader.biClrImportant = 0;
			COLORREF* pSrcBits = NULL;
			HBITMAP hSrcDib = CreateDIBSection (hSrcDC, lpbiSrc, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, NULL);
			if ((NULL != hSrcDib) && (NULL != pSrcBits)) {
				HBITMAP hOldTempBmp = (HBITMAP)::SelectObject (hTempDC, hSrcDib);
				::BitBlt (hTempDC, 0, 0, dwWidth, dwHeight, hSrcDC, nSrcX, nSrcY, SRCCOPY);
				::SelectObject (hTempDC, hOldTempBmp);

				LPBITMAPINFO lpbiDest;
				lpbiDest = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
				lpbiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				lpbiDest->bmiHeader.biWidth = dwWidth;
				lpbiDest->bmiHeader.biHeight = dwHeight;
				lpbiDest->bmiHeader.biPlanes = 1;
				lpbiDest->bmiHeader.biBitCount = 32;
				lpbiDest->bmiHeader.biCompression = BI_RGB;
				lpbiDest->bmiHeader.biSizeImage = dwWidth * dwHeight;
				lpbiDest->bmiHeader.biXPelsPerMeter = 0;
				lpbiDest->bmiHeader.biYPelsPerMeter = 0;
				lpbiDest->bmiHeader.biClrUsed = 0;
				lpbiDest->bmiHeader.biClrImportant = 0;
				COLORREF* pDestBits = NULL;
				HBITMAP hDestDib = CreateDIBSection (hDestDC, lpbiDest, DIB_RGB_COLORS, (void **)&pDestBits, NULL, NULL);
				if ((NULL != hDestDib) && (NULL != pDestBits)) {
					::SelectObject (hTempDC, hDestDib);
					::BitBlt (hTempDC, 0, 0, dwWidth, dwHeight, hDestDC, nDestX, nDestY, SRCCOPY);
					::SelectObject(hTempDC, hOldTempBmp);

					double src_darken = (double)nAlpha / 100.0;
					double dest_darken = 1.0 - src_darken;
					for (DWORD pixel = 0; pixel < dwWidth * dwHeight; pixel++, pSrcBits++, pDestBits++)
					{
						*pDestBits = AlphaColor(*pSrcBits, src_darken, *pDestBits, dest_darken);
					}

					::SelectObject (hTempDC, hDestDib);
					::BitBlt(hDestDC, nDestX, nDestY, dwWidth, dwHeight, hTempDC, 0, 0, SRCCOPY);
					::SelectObject (hTempDC, hOldTempBmp);

					::DeleteObject(hDestDib);
				}
				delete lpbiDest;
				::DeleteObject(hSrcDib);
			}
			delete lpbiSrc;
			::DeleteDC(hTempDC);
		}
	}

	inline void AlphaBitBlt(HDC hDestDC, int nDestX, int nDestY, DWORD dwWidth, DWORD dwHeight, HDC hSrcDC, int nSrcX, int nSrcY)
	{
		ASSERT ((NULL != hDestDC) || (NULL != hSrcDC));
		HDC hTempDC = ::CreateCompatibleDC(hDestDC);
		if (NULL == hTempDC)
			return;

		LPBITMAPINFO lpbiSrc;
		lpbiSrc = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
		lpbiSrc->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		lpbiSrc->bmiHeader.biWidth = dwWidth;
		lpbiSrc->bmiHeader.biHeight = dwHeight;
		lpbiSrc->bmiHeader.biPlanes = 1;
		lpbiSrc->bmiHeader.biBitCount = 32;
		lpbiSrc->bmiHeader.biCompression = BI_RGB;
		lpbiSrc->bmiHeader.biSizeImage = dwWidth * dwHeight;
		lpbiSrc->bmiHeader.biXPelsPerMeter = 0;
		lpbiSrc->bmiHeader.biYPelsPerMeter = 0;
		lpbiSrc->bmiHeader.biClrUsed = 0;
		lpbiSrc->bmiHeader.biClrImportant = 0;
		COLORREF* pSrcBits = NULL;
		HBITMAP hSrcDib = CreateDIBSection (hSrcDC, lpbiSrc, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, NULL);
		if ((NULL != hSrcDib) && (NULL != pSrcBits)) {
			HBITMAP hOldTempBmp = (HBITMAP)::SelectObject (hTempDC, hSrcDib);
			::BitBlt (hTempDC, 0, 0, dwWidth, dwHeight, hSrcDC, nSrcX, nSrcY, SRCCOPY);
			::SelectObject (hTempDC, hOldTempBmp);

			LPBITMAPINFO lpbiDest;
			lpbiDest = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
			lpbiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			lpbiDest->bmiHeader.biWidth = dwWidth;
			lpbiDest->bmiHeader.biHeight = dwHeight;
			lpbiDest->bmiHeader.biPlanes = 1;
			lpbiDest->bmiHeader.biBitCount = 32;
			lpbiDest->bmiHeader.biCompression = BI_RGB;
			lpbiDest->bmiHeader.biSizeImage = dwWidth * dwHeight;
			lpbiDest->bmiHeader.biXPelsPerMeter = 0;
			lpbiDest->bmiHeader.biYPelsPerMeter = 0;
			lpbiDest->bmiHeader.biClrUsed = 0;
			lpbiDest->bmiHeader.biClrImportant = 0;
			COLORREF* pDestBits = NULL;
			HBITMAP hDestDib = CreateDIBSection (hDestDC, lpbiDest, DIB_RGB_COLORS, (void **)&pDestBits, NULL, NULL);
			if ((NULL != hDestDib) && (NULL != pDestBits)) {
				::SelectObject (hTempDC, hDestDib);
				::BitBlt (hTempDC, 0, 0, dwWidth, dwHeight, hDestDC, nDestX, nDestY, SRCCOPY);
				::SelectObject (hTempDC, hOldTempBmp);

				double src_darken;
				BYTE nAlpha;
				for (DWORD pixel = 0; pixel < dwWidth * dwHeight; pixel++, pSrcBits++, pDestBits++)
				{
					nAlpha = LOBYTE(*pSrcBits >> 24);
					src_darken = (double)nAlpha / 255.0;
					*pDestBits = AlphaColor(*pSrcBits, src_darken, *pDestBits, 1.0 - src_darken);
				}

				::SelectObject (hTempDC, hDestDib);
				::BitBlt (hDestDC, nDestX, nDestY, dwWidth, dwHeight, hTempDC, 0, 0, SRCCOPY);
				::SelectObject (hTempDC, hOldTempBmp);

				::DeleteObject(hDestDib);
			}
			delete lpbiDest;
			::DeleteObject(hSrcDib);
		}
		delete lpbiSrc;
		::DeleteDC(hTempDC);
	}

	// Alpha混合过渡
	inline void AlphaBlendTransition(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, 
		HDC hdcSrc, int nXSrc, int nYSrc, BOOL bHoriz = TRUE, BYTE nAlphaFrom = 0, BYTE nAlphaTo = 100)
	{
		if (nAlphaFrom == nAlphaTo) {
			AlphaBitBlt(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, nAlphaFrom);
		} else {
			BOOL bIsFromToTransition = TRUE;
			if (nAlphaTo < nAlphaFrom) {
				bIsFromToTransition = FALSE;
				BYTE byTemp = nAlphaFrom;
				nAlphaFrom = nAlphaTo;
				nAlphaTo = byTemp;
			}

			int nMinTransition = (int)(255 - 255.0 * nAlphaFrom / 100.0);
			int nMaxTransition = (int)(255.0 * (100 - nAlphaTo) / 100.0);
			double dTransition = (nMinTransition - nMaxTransition) / (double)(bHoriz ? nWidth : nHeight);

			BLENDFUNCTION Blend = {0};
			Blend.BlendOp = AC_SRC_OVER;
			Blend.SourceConstantAlpha = 255;
			for (int i = 0, j = bHoriz ? nWidth : nHeight; i < j; i++)
			{
				Blend.SourceConstantAlpha = (BYTE)(bIsFromToTransition ? nMinTransition - (dTransition * i) : nMaxTransition + (dTransition * i)); 
				if(bHoriz) {
					::AlphaBlend(hdcDest, nXDest + i, nYDest, 1, nHeight, hdcSrc, nXSrc + i, nYSrc, 1, nHeight, Blend);
				} else {
					::AlphaBlend(hdcDest, nXDest, nYDest + i, nWidth , 1, hdcSrc, nXSrc, nYSrc + i, nWidth, 1, Blend);
				}
			}
			//return Blend.SourceConstantAlpha;
		}
	}

	inline Image* ImageFromData(IN LPVOID lpData, IN DWORD dwDataLen)
	{
		return ImageEx::ImageFromData(lpData, dwDataLen);
	}

	inline Image* ImageFromResource(IN HINSTANCE hInstResource, IN LPCTSTR pszResourceName, IN LPCTSTR pszResourceType)
	{
		return ImageEx::ImageFromResource(hInstResource, pszResourceName, pszResourceType);
	}

	/*CLSID encoderClsid
	GetEncoderClsid(L"image/png", &encoderClsid);    //png
	GetEncoderClsid(L"image/bmp", &encoderClsid);
	GetEncoderClsid(L"image/gif", &encoderClsid);
	GetEncoderClsid(L"image/jpeg",&encoderClsid);
	GetEncoderClsid(L"image/tiff",&encoderClsid);*/
	inline int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
	{
		UINT num	= 0;
		UINT size	= 0;
		ImageCodecInfo* pImageCodecInfo = NULL;
		GetImageEncodersSize(&num, &size);
		if(size == 0) {
			return -1;
		}
		pImageCodecInfo= (ImageCodecInfo*)(malloc(size));
		GetImageEncoders(num, size, pImageCodecInfo);
		for(UINT j=0; j< num; ++j) {
			if(wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
				*pClsid= pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
				return j;
			}
		}
		free(pImageCodecInfo);
		return -1;
	}

	inline SIZE & GetIconSize(HICON hIcon, SIZE & Size)
	{
		Size.cx = 0;
		Size.cy = 0;
		if (hIcon != NULL) {
			ICONINFO ii;
			::ZeroMemory(&ii, sizeof(ICONINFO));
			if (::GetIconInfo(hIcon, &ii)) {
				Size.cx = (DWORD)(ii.xHotspot * 2);
				Size.cy = (DWORD)(ii.yHotspot * 2);
				if(ii.hbmMask)
					::DeleteObject(ii.hbmMask);
				if(ii.hbmColor)
					::DeleteObject(ii.hbmColor);
			}
		}
		return Size;
	}

	inline SIZE & GetBitmapSize(HBITMAP hBitmap, SIZE & Size)
	{
		Size.cx = 0;
		Size.cy = 0;
		if (hBitmap != NULL) {
			BITMAP	Bitmap;
			int nRetValue = ::GetObject(hBitmap, sizeof(Bitmap), &Bitmap);
			if (nRetValue) {
				Size.cx = (DWORD)Bitmap.bmWidth;
				Size.cy = (DWORD)Bitmap.bmHeight;
			}
		}
		return Size;
	}
}

template<class T>
class UIBkgnd
{
protected:
	enum 
	{
		UI_BK_STYLE_NONE				= 0,
		UI_BK_STYLE_COLOR,
		UI_BK_STYLE_COLOR2D,
		UI_BK_STYLE_COLOR3D,
		UI_BK_STYLE_STRETCH, 
		UI_BK_STYLE_TITLE, 
		UI_BK_STYLE_CENTER,
		UI_BK_STYLE_PART9,
		UI_BK_STYLE_TYPEMAX				= 16,
		UI_BK_TYPE_MASK					= 0X0000000F,
		UI_BK_EFFECT_ALPHA_HORZ			= 0X00000010,
		UI_BK_EFFECT_ALPHA_VERT			= 0X00000020,
		UI_BK_EFFECT_MASK				= 0X0000FFF0,
		UI_BK_VALUE_MASK				= 0XFFFF0000,
	};
	DWORD		m_bkStyle;
	COLORREF	m_crBkColor;
	union
	{
		COLORREF	m_crBkColor2;
		Image*		m_pBkImage;
	};
public:
	UIBkgnd():m_bkStyle(0),m_crBkColor(CLR_INVALID),m_crBkColor2(CLR_INVALID) { }
	~UIBkgnd() { }

	void SetBkColor(COLORREF color)
	{
		m_crBkColor = color;
		m_bkStyle = UI_BK_STYLE_COLOR;
	}

	void SetBkColor(COLORREF color, COLORREF color2, DWORD dwStyle = UI_BK_STYLE_COLOR2D)
	{
		m_crBkColor = color;
		m_crBkColor2 = color2;
		m_bkStyle = UI_BK_STYLE_COLOR2D;
	}

	void SetBkImage(COLORREF color)
	{
		SetBkColor(color);
	}

	void SetBkImage(Image* pImage, DWORD dwStyle = UI_BK_STYLE_STRETCH)
	{
		m_pBkImage = pImage;
		m_bkStyle = dwStyle;
	}

	DWORD GetBkStyle()
	{
		return m_bkStyle;
	}

	UINT GetBkType()
	{
		return m_bkStyle&UI_BK_TYPE_MASK;
	}

	static BOOL IsBkColor(UINT nBkType)
	{
		return ((nBkType>0)&&(nBkType<UI_BK_STYLE_STRETCH)) ? TRUE : FALSE;
	}

	static BOOL IsBkImage(UINT nBkType)
	{
		if((nBkType>=UI_BK_STYLE_STRETCH)&&(nBkType<UI_BK_STYLE_TYPEMAX)) {
			return TRUE;
		}
		return FALSE;
	}

	BOOL IsBkColor()
	{
		return IsBkColor(GetBkType());
	}

	BOOL IsBkImage()
	{
		return IsBkImage(GetBkType());
	}

	COLORREF GetBkColor()
	{ 
		return m_crBkColor;
	}

	COLORREF GetBkColor2()
	{ 
		ASSERT(IsBkColor());
		return m_crBkColor2;
	}

	Image* GetBkImage() 
	{ 
		ASSERT(IsBkImage());
		return m_pBkImage;
	}

	static void DrawBkColor(HDC hdc, LPCRECT lpRect, COLORREF color)
	{
		UIgdi::FillSolidRect(hdc, lpRect, color);
	}

	static void DrawBkColor(HDC hdc, LPCRECT lpRect, COLORREF color, COLORREF color2, DWORD dwStyle)
	{
		UIgdi::FillGradient(hdc, lpRect, color, color2,dwStyle&UI_BK_EFFECT_ALPHA_HORZ?TRUE:FALSE);
	}

	static void DrawBkColor(HDC hdc, LPCRECT lpRect, COLORREF color, COLORREF color2, COLORREF color3, DWORD dwStyle)
	{
		CRect rc(lpRect);
		if (dwStyle&UI_BK_EFFECT_ALPHA_HORZ) {
			rc.right = rc.left + rc.Width()/2;
			UIgdi::FillGradient(hdc, lpRect, color, color2, TRUE);
			rc.left = rc.right;
			rc.right = lpRect->right;
			UIgdi::FillGradient(hdc, lpRect, color, color2, TRUE);
		} else {
			rc.bottom = rc.top + rc.Height()/2;
			UIgdi::FillGradient(hdc, lpRect, color, color2, FALSE);
			rc.top = rc.bottom;
			rc.bottom = lpRect->bottom;
			UIgdi::FillGradient(hdc, lpRect, color, color2, FALSE);
		}
	}

	static void DrawBkImage(HDC hdc, LPCRECT lpRect, Image* pImage, DWORD dwStyle)
	{
		CRect rc(lpRect);
		WTL::CMemDC MemDC(hdc,&rc);
		Graphics graphics((HDC)MemDC);
		// 反锯齿
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		//
		UINT nBkType = dwStyle & UI_BK_TYPE_MASK;
		DWORD dwBkEffect = dwStyle & UI_BK_EFFECT_MASK;
		switch(nBkType)
		{
		case UI_BK_STYLE_COLOR:
		case UI_BK_STYLE_COLOR2D:
		case UI_BK_STYLE_COLOR3D:
			break;
		case UI_BK_STYLE_STRETCH:
			{
				graphics.DrawImage(pImage, rc.left, rc.top, rc.Width(), rc.Height());
			}
			break;
		case UI_BK_STYLE_CENTER:
			{
				int nWidth = rc.Width(), nHeight = rc.Height();
				int nBgWidth = pImage->GetWidth(), nBgHeight = pImage->GetHeight();
				int x = (nWidth - nBgWidth) / 2, y = (nHeight - nBgHeight) / 2;
				graphics.DrawImage(pImage, x > 0 ? x : 0, y > 0 ? y : 0, x < 0 ? -x : 0, y < 0 ? -y : 0, nBgWidth, nBgHeight, UnitPixel);
			}
			break;
		case UI_BK_STYLE_TITLE:
			{
				int ixOrg = 0, iyOrg = 0;
				UINT nWidth = pImage->GetWidth(), nHeight = pImage->GetHeight();
				for (iyOrg = 0; iyOrg < rc.Height(); iyOrg += nHeight)
				{
					for (ixOrg = 0; ixOrg < rc.Width(); ixOrg += nWidth)
					{
						graphics.DrawImage(pImage, ixOrg, iyOrg, 0, 0, pImage->GetWidth(), pImage->GetHeight(), UnitPixel);
					}
				}
			}
			break;
		default:
			{
				if (nBkType==UI_BK_STYLE_PART9) { 
					//-|-|-
					//-|-|-
					int i,j;
					REAL srcWidth = pImage->GetWidth()/3;
					REAL srcHeight = pImage->GetHeight()/3;
					REAL dstX = 0, dstY = 0, dstWidth = 0, dstHeight = 0;
					for (i=0;i<3;i++)
					{
						REAL srcX = srcWidth*i;
						
						dstWidth = srcWidth;
						if (i=1) {
							dstWidth = rc.Width()-2*srcWidth;
							dstX += dstWidth;
						} else if (i>=2) {
							dstX += srcWidth;
						}
						
						for (j=0;j<3;j++)
						{
							REAL srcY = srcHeight*j;

							dstHeight = srcHeight;
							if (j=1) {
								dstHeight = rc.Height()-2*srcHeight;
								dstY += dstHeight;
							} else if (j>=2) {
								dstY += srcHeight;
							}

							graphics.DrawImage(pImage, dstX, dstY, srcX, srcY, dstWidth, dstHeight, UnitPixel);
						}
					}
				}
			}
			break;
		}
		//
		graphics.ReleaseHDC((HDC)MemDC);

		//特效处理
		if (dwBkEffect & (UI_BK_EFFECT_ALPHA_HORZ|UI_BK_EFFECT_ALPHA_VERT)) {
			UIgdi::FillSolidRect(hdc, &rc, UIgdi::AverageColorFromDC((HDC)MemDC)); 

			UIgdi::AlphaBlendTransition(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top
				, MemDC, rc.left, rc.top, (dwBkEffect&UI_BK_EFFECT_ALPHA_HORZ)?TRUE:FALSE, 0, 100);
		} else {
			::BitBlt(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, MemDC, rc.left, rc.top, SRCCOPY);
		}

		MemDC.DeleteDC();
	}

	BOOL PaintBkgnd(HDC hdc, LPCRECT lpRect)
	{
		if (!hdc || !lpRect) {
			return FALSE;
		}

		// 填充背景颜色
		if (IsBkColor()) {
			UINT nBkType = m_bkStyle&UI_BK_TYPE_MASK;
			switch(nBkType)
			{
			case UI_BK_STYLE_COLOR:
				DrawBkColor(hdc, lpRect, m_crBkColor);
				break;
			case UI_BK_STYLE_COLOR2D:
				DrawBkColor(hdc, lpRect, m_crBkColor, m_crBkColor2, m_bkStyle);
				break;
			case UI_BK_STYLE_COLOR3D:
				DrawBkColor(hdc, lpRect, m_crBkColor, m_crBkColor2, m_crBkColor, m_bkStyle);
				break;
			default:
				break;
			}
			return TRUE;
		}

		// 画背景图片
		if (IsBkImage()) {
			if (m_pBkImage) {
				Image* pImage = m_pBkImage->Clone();
				DrawBkImage(hdc, lpRect, pImage, m_bkStyle);
				delete pImage;
				return TRUE;
			}
		}

		return FALSE;
	}
};

//template<class T>
//class UIFgnd
//{
//protected:
//	enum 
//	{
//		UI_F_STYLE_NONE				= 0,
//		UI_F_STYLE_COLOR,
//		UI_F_STYLE_STRETCH, 
//		UI_F_STYLE_TITLE, 
//		UI_F_STYLE_CENTER,
//		UI_F_STYLE_PART5,
//		UI_F_STYLE_PARTMAX			= 15,
//		UI_F_TYPE_MASK				= 0X0000000F,
//		UI_F_STYLE_HORIZONTAL		= 0X00000010,
//		UI_F_STYLE_VERTICAL			= 0X00000020,
//		UI_F_EFFECT_MASK			= 0X0000FFF0,
//		UI_F_VALUE_MASK				= 0XFFFF0000,
//	};
//	DWORD m_Style;
//	union
//	{
//		COLORREF	m_crColor[4];
//		Image*		m_pImage[4];
//	};
//public:
//	UIBkgnd():m_Style(0) { }
//	~UIBkgnd() { }
//
//	void SetColor(COLORREF color)
//	{
//		m_crColor = color;
//		m_Style = UI_BK_STYLE_COLOR;
//	}
//
//	void SetColor(COLORREF color, COLORREF color2)
//	{
//		m_crColor = color;
//		m_crColor2 = color2;
//		m_Style = UI_BK_STYLE_COLOR;
//	}
//
//	void SetImage(COLORREF color)
//	{
//		SetBkColor(color);
//	}
//
//	void SetImage(Image* pImage, DWORD dwStyle = UI_BK_STYLE_STRETCH)
//	{
//		m_pBkImage = pImage;
//		m_bkStyle = dwStyle;
//	}
//
//	DWORD GetStyle()
//	{
//		return m_Style;
//	}
//
//	UINT GetBkType()
//	{
//		return m_bkStyle&UI_BK_TYPE_MASK;
//	}
//
//	BOOL IsBkColor()
//	{
//		return (m_bkStyle&UI_BK_TYPE_MASK)==UI_BK_STYLE_COLOR?TRUE:FALSE;
//	}
//
//	BOOL IsBkImage()
//	{
//		if((m_bkStyle&UI_BK_TYPE_MASK)>UI_BK_STYLE_COLOR) {
//			return TRUE;
//		}
//		return FALSE;
//	}
//
//	COLORREF GetBkColor()
//	{ 
//		return m_crBkColor;
//	}
//
//	COLORREF GetBkColor2()
//	{ 
//		if((m_bkStyle&UI_BK_TYPE_MASK)==UI_BK_STYLE_COLOR)
//		{
//			return m_crBkColor2;
//		}
//		return CLR_INVALID;
//	}
//
//	Image* GetBkImage() 
//	{ 
//		if((m_bkStyle&UI_BK_TYPE_MASK)>UI_BK_STYLE_COLOR) {
//			return m_pBkImage;
//		}
//		return NULL;
//	}
//
//	void DrawBkColor(HDC hdc, LPCRECT lpRect, COLORREF color)
//	{
//		UIgdi::FillSolidRect(hdc, lpRect, color);
//	}
//
//	void DrawBkColor(HDC hdc, LPCRECT lpRect, COLORREF color, COLORREF color2, DWORD dwStyle)
//	{
//		UIgdi::FillGradient(hdc, lpRect, color, color2,dwStyle&UI_BK_EFFECT_ALPHA_HORZ?TRUE:FALSE);
//	}
//
//	void DrawBkImage(HDC hdc, LPCRECT lpRect, Image* pImage, DWORD dwStyle)
//	{
//		CRect rc(lpRect);
//		WTL::CMemDC MemDC(hdc,&rc);
//		Graphics graphics((HDC)MemDC);
//		// 反锯齿
//		graphics.SetSmoothingMode(SmoothingModeHighQuality);
//		//
//		UINT nBkType = dwStyle & UI_BK_TYPE_MASK;
//		DWORD dwBkEffect = dwStyle & UI_BK_EFFECT_MASK;
//		switch(nBkType)
//		{
//		case UI_BK_STYLE_COLOR:
//			break;
//		case UI_BK_STYLE_STRETCH:
//			{
//				graphics.DrawImage(pImage, rc.left, rc.top, rc.Width(), rc.Height());
//			}
//			break;
//		case UI_BK_STYLE_CENTER:
//			{
//				int nWidth = rc.Width(), nHeight = rc.Height();
//				int nBgWidth = pImage->GetWidth(), nBgHeight = pImage->GetHeight();
//				int x = (nWidth - nBgWidth) / 2, y = (nHeight - nBgHeight) / 2;
//				graphics.DrawImage(pImage, x > 0 ? x : 0, y > 0 ? y : 0, x < 0 ? -x : 0, y < 0 ? -y : 0, nBgWidth, nBgHeight, UnitPixel);
//			}
//			break;
//		case UI_BK_STYLE_TITLE:
//			{
//				int ixOrg = 0, iyOrg = 0;
//				UINT nWidth = pImage->GetWidth(), nHeight = pImage->GetHeight();
//				for (iyOrg = 0; iyOrg < rc.Height(); iyOrg += nHeight)
//				{
//					for (ixOrg = 0; ixOrg < rc.Width(); ixOrg += nWidth)
//					{
//						graphics.DrawImage(pImage, ixOrg, iyOrg, 0, 0, pImage->GetWidth(), pImage->GetHeight(), UnitPixel);
//					}
//				}
//			}
//			break;
//		default:
//			{
//				if (nBkType==9) { 
//					//-|-|-
//					//-|-|-
//					int i,j;
//					REAL srcWidth = pImage->GetWidth()/3;
//					REAL srcHeight = pImage->GetHeight()/3;
//					REAL dstX = 0, dstY = 0, dstWidth = 0, dstHeight = 0;
//					for (i=0;i<3;i++)
//					{
//						REAL srcX = srcWidth*i;
//
//						dstWidth = srcWidth;
//						if (i=1) {
//							dstWidth = rc.Width()-2*srcWidth;
//							dstX += dstWidth;
//						} else if (i>=2) {
//							dstX += srcWidth;
//						}
//
//						for (j=0;j<3;j++)
//						{
//							REAL srcY = srcHeight*j;
//
//							dstHeight = srcHeight;
//							if (j=1) {
//								dstHeight = rc.Height()-2*srcHeight;
//								dstY += dstHeight;
//							} else if (j>=2) {
//								dstY += srcHeight;
//							}
//
//							graphics.DrawImage(pImage, dstX, dstY, srcX, srcY, dstWidth, dstHeight, UnitPixel);
//						}
//					}
//				}
//			}
//			break;
//		}
//		//
//		graphics.ReleaseHDC((HDC)MemDC);
//
//		//特效处理
//		if (dwBkEffect & (UI_BK_EFFECT_ALPHA_HORZ|UI_BK_EFFECT_ALPHA_VERT)) {
//			UIgdi::FillSolidRect(hdc, &rc, UIgdi::AverageColorFromDC((HDC)MemDC)); 
//
//			UIgdi::AlphaBlendTransition(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top
//				, MemDC, rc.left, rc.top, (dwBkEffect&UI_BK_EFFECT_ALPHA_HORZ)?TRUE:FALSE, 0, 100);
//		}
//
//		MemDC.DeleteDC();
//	}
//
//	BOOL PaintBkgnd(HDC hdc, LPCRECT lpRect)
//	{
//		if (!hdc || !lpRect) {
//			return FALSE;
//		}
//
//		// 填充背景颜色
//		if (IsBkColor()) {
//			if(m_crBkColor2 != CLR_INVALID) {
//				DrawBkColor(hdc, lpRect, m_crBkColor, m_crBkColor2, m_bkStyle);
//			} else {
//				DrawBkColor(hdc, lpRect, m_crBkColor);
//			}
//			return TRUE;
//		}
//
//		// 画背景图片
//		if (IsBkImage()) {
//			if (m_pBkImage) {
//				Image* pImage = m_pBkImage->Clone();
//				DrawBkImage(hdc, lpRect, pImage, m_bkStyle);
//				delete pImage;
//				return TRUE;
//			}
//		}
//
//		return FALSE;
//	}
//};

/*
//多页图像是指图像中包含有多个图形页。每页可以看作图像帧。这些图像帧通过连续的显示就形成了一副动画。比如GIF文件。
//GDI+的Image对象提供了直接的对GIF、TIF文件格式的支持。
//调用Image对象的成员函数GetFrameDimensionsCount可以得到Image对象的Dimension数。
//每个Dimension通过一个GUID标示。函数GetFrameDimensionsList可以返回所有Dimension的GUID值。
//第一个GUID值保存在函数参数pDimensionsIDs数组的索引0处。GetFrameCount可以得到每个Dimension里有多少个Frame。
//简单示例代码：
Image* image = new Image(L"Multiframe.gif");
UINT count = 0;
count = image->GetFrameDimensionsCount();
GUID *pDimensionIDs=(GUID*)new GUID[count];
image->GetFrameDimensionsList(pDimensionIDs, count);
WCHAR strGuid[39];
StringFromGUID2(pDimensionIDs[0], strGuid, 39);
UINT frameCount=image->GetFrameCount(&pDimensionIDs[0]);
delete []pDimensionIDs;   
//并不是所有的GIF文件都是含有多帧的，所以我们在显示GIF的时候可以通过上面的代码根据frameCount的值判断这个GIF文件是否有多个帧。
//在确认有多个帧的图像以后，还要得到每帧图像显示的间隔时间。
//GDI+的Image对象提供了GetPropertyItem获取图像的属性。
//GetPropertyItem函数需要用户传递数据返回缓冲区和大小。
//所以在使用前先用GetPropertyItemSize得到需要的缓冲区大小，分配空间后再取得属性数据。  
//PropertyTagFrameDelay是GDI+中预定义的一个GIG属性ID值，表示标签帧数据的延迟时间
int size = GetPropertySize(PropertyTagFrameDelay);
PropertyItem* pItem = NULL;
pItem = (PropertyItem*)malloc(size);
image->GetPropertyItem(PropertyTagFrameDelay,size,pItem);
//这样就把所有和PropertyTagFrameDelay属性相关的数据取到了pItem中。
//然后通过pItem访问结构中的value。每两帧图像之间的间隔时间是不一定相同的，所以还需要得到当前正显示的帧图像的索引值。
//最后调用Image对象的DrawImage函数把每帧图像画出来。简单代码如下：
int     fcount=0;
//Guid的值在显示GIF为FrameDimensionTime，显示TIF时为FrameDimensionPage
GUID    Guid = FrameDimensionTime;
while(true)
{
	Graphics gh(hDC); //hDC是外部传入的画图DC
	gh.DrawImage(image,0,0,image->GetWidth(),image->GetHeight());
	//重新设置当前的活动数据帧
	image->SelectActiveFrame(&Guid,fcount++);
	if(fcount == frameCount) //frameCount是上面GetFrameCount返回值
		fcount= 0;     //如果到了最后一帧数据又重新开始
	//计算此帧要延迟的时间
	long lPause = ((long*)pItem->value)[fcount]*10;
	Sleep(lPause);         //这里简单使用了sleep
} 
*/


//////////////////////////////////////////////////////////////////////////
//DPI
// 96 DPI = 100% scaling
//120 DPI = 125% scaling
//144 DPI = 150% scaling
//168 DPI = 175% scaling
//192 DPI = 200% scaling

#ifndef DPI_ENUMS_DECLARED
#define DPI_ENUMS_DECLARED
enum MONITOR_DPI_TYPE {
	MDT_EFFECTIVE_DPI = 0,
	MDT_ANGULAR_DPI = 1,
	MDT_RAW_DPI = 2,
	MDT_DEFAULT = MDT_EFFECTIVE_DPI
};
#endif//

typedef HRESULT (WINAPI *lpGetDpiForMonitor) (
	_In_  HMONITOR         hmonitor,
	_In_  MONITOR_DPI_TYPE dpiType,
	_Out_ UINT             *dpiX,
	_Out_ UINT             *dpiY
	);

class UIDpi
{
public:
	static void GetDpiFromMonitor(HMONITOR hMonitor, UINT* x, UINT* y)
	{
		*x = 96;
		*y = 96;
		lpGetDpiForMonitor GetDpiForMonitor = NULL;
		HMODULE hModule =::LoadLibrary(_T("Shcore.dll"));
		if(hModule != NULL) {
			lpGetDpiForMonitor GetDpiForMonitor = (lpGetDpiForMonitor)GetProcAddress(hModule, "GetDpiForMonitor");
		}
		HRESULT  hr = S_FALSE;
		if(GetDpiForMonitor) {
			hr = GetDpiForMonitor(hMonitor, MDT_DEFAULT, x, y);
		} 
		if (hr != S_OK) {
			HDC hdc = GetDC(NULL);
			*x = GetDeviceCaps(hdc, LOGPIXELSX);
			*y = GetDeviceCaps(hdc, LOGPIXELSY);
			ReleaseDC(NULL, hdc);
		}
	}

	static void GetDpiFromPoint(POINT pt, UINT* x, UINT* y)
	{
		return GetDpiFromMonitor(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), x, y);
	}

private:
	static UINT s_x, s_y;
public:
	static void SetDpi(int x, int y = 0)
	{
		s_x = MulDiv(x, 100, 96);
		if (s_y==0) {
			s_y = s_x;
		} else {
			s_y = MulDiv(y, 100, 96);
		}
	}

	static int ScaleX(int x)
	{
		return MulDiv(x, s_x, 100);
	}

	static int ScaleY(int y)
	{
		return MulDiv(y, s_y, 100);
	}

	static void Scale(LPPOINT lpPoint)
	{
		if (!lpPoint) {
			return;
		}
		lpPoint->x = ScaleX(lpPoint->x);
		lpPoint->y = ScaleY(lpPoint->y);
	}

	static void Scale(LPSIZE lpSize)
	{
		if (!lpSize) {
			return;
		}
		lpSize->cx = ScaleX(lpSize->cx);
		lpSize->cy = ScaleY(lpSize->cy);
	}

	static void Scale(LPRECT lpRect)
	{
		if (!lpRect) {
			return;
		}
		int sw = ScaleX(lpRect->right-lpRect->left);
		int sh = ScaleY(lpRect->bottom-lpRect->top);
		lpRect->left = ScaleX(lpRect->left);
		lpRect->top = ScaleY(lpRect->top);
		lpRect->right = lpRect->left + sw;
		lpRect->bottom = lpRect->top + sh;
	}
};

__declspec(selectany) UINT UIDpi::s_x = 96;
__declspec(selectany) UINT UIDpi::s_y = 96;

template<class Key, class KeyLess = std::less<Key>>
class UIgdiManagerT
{
public:
	UIgdiManagerT() { }
	~UIgdiManagerT() { Clear(); }
protected:
	typedef std::map<Key,HIMAGELIST,KeyLess>	ID2HIMAGELIST;
	typedef std::map<Key,Image*,KeyLess>		ID2ImagePtr;
	typedef std::map<Key,HBITMAP,KeyLess>		ID2HBITMAP;
	typedef std::map<Key,HBRUSH,KeyLess>		ID2HBRUSH;
	typedef std::map<Key,HFONT,KeyLess>			ID2HFONT;
	typedef std::map<Key,COLORREF,KeyLess>		ID2COLORREF;
	typedef std::map<Key,RECT,KeyLess>			ID2RECT;
	typedef std::map<Key,CString,KeyLess>		ID2String;
	ID2HIMAGELIST	m_ID2HIMAGELIST;
	ID2ImagePtr		m_ID2ImagePtr;
	ID2HBITMAP		m_ID2HBITMAP;
	ID2HBRUSH		m_ID2HBRUSH;
	ID2HFONT		m_ID2HFONT;
	ID2COLORREF		m_ID2COLORREF;
	ID2RECT			m_ID2RECT;
	ID2String		m_ID2String;

public:
	void Clear()
	{
		ID2HIMAGELIST::iterator it_imagelist =	m_ID2HIMAGELIST.begin();
		for (; it_imagelist != m_ID2HIMAGELIST.end(); ++it_imagelist)
		{
			if (it_imagelist->second) {
				ImageList_Destroy(it_imagelist->second);
			}
		}
		m_ID2HIMAGELIST.clear();
		ID2ImagePtr::iterator it_ImagePtr = m_ID2ImagePtr.begin();
		for (; it_ImagePtr != m_ID2ImagePtr.end(); ++it_ImagePtr)
		{
			if (it_ImagePtr->second) {
				delete it_ImagePtr->second;
			}
		}
		m_ID2ImagePtr.clear();
		ID2HBITMAP::iterator it_Bitmap = m_ID2HBITMAP.begin();
		for (; it_Bitmap != m_ID2HBITMAP.end(); ++it_Bitmap)
		{
			if (it_Bitmap->second) {
				::DeleteObject(it_Bitmap->second);
			}
		}
		m_ID2HBITMAP.clear();
		ID2HBRUSH::iterator it_Brush = m_ID2HBRUSH.begin();
		for (; it_Brush != m_ID2HBRUSH.end(); ++it_Brush)
		{
			if (it_Brush->second) {
				::DeleteObject(it_Brush->second);
			}
		}
		m_ID2HBRUSH.clear();
		ID2HFONT::iterator it_Font = m_ID2HFONT.begin();
		for (; it_Font != m_ID2HFONT.end(); ++it_Font)
		{
			if (it_Font->second) {
				::DeleteObject(it_Font->second);
			}
		}
		m_ID2HFONT.clear();
		m_ID2COLORREF.clear();
		m_ID2RECT.clear();
		m_ID2String.clear();
	}

	void SetImageList(const Key &id, HIMAGELIST imagelist) 
	{ 
		HIMAGELIST old = GetImageList(id);
		if (old) {
			ImageList_Destroy(old);
		}
		m_ID2HIMAGELIST[id] = imagelist; 
	}
	void SetImage(const Key &id, Image* image) 
	{ 
		Image* old = GetImage(id);
		if (old) {
			delete old;
		}
		m_ID2ImagePtr[id] = image; 
	}
	void SetHBITMAP(const Key &id, HBITMAP bitmap)
	{ 
		HBITMAP old = GetHBITMAP(id);
		if (old) {
			::DeleteObject(old);
		}
		m_ID2HBITMAP[id] = bitmap; 
	}
	void SetHBRUSH(const Key &id, HBRUSH brush) 
	{ 
		HBRUSH old = GetHBRUSH(id);
		if (old) {
			::DeleteObject(old);
		}
		m_ID2HBRUSH[id] = brush; 
	}
	void SetHFONT(const Key &id, HFONT font) 
	{ 
		HFONT old = GetHFONT(id);
		if (old) {
			::DeleteObject(old);
		}
		m_ID2HFONT[id] = font;
	}
	void SetCOLORREF(const Key &id, COLORREF color) 
	{ 
		m_ID2COLORREF[id] = color;
	}
	void SetRECT(const Key &id, RECT rect) 
	{ 
		m_ID2RECT[id] = rect;
	}
	void SetString(const Key &id, LPCTSTR lpszStr) 
	{ 
		m_ID2String[id] = lpszStr;
	}
	HIMAGELIST GetImageList(const Key &id, HIMAGELIST Default = NULL)
	{ 
		ID2HIMAGELIST::iterator it = m_ID2HIMAGELIST.find(id);
		if (it != m_ID2HIMAGELIST.end()) {
			return it->second;
		}
		return Default; 
	}
	Image* GetImage(const Key &id, Image* Default = 0) 
	{ 
		ID2ImagePtr::iterator it = m_ID2ImagePtr.find(id);
		if (it != m_ID2ImagePtr.end()) {
			return it->second;
		}
		return Default; 
	}
	HBITMAP GetHBITMAP(const Key &id, HBITMAP Default = NULL) 
	{ 
		ID2HBITMAP::iterator it = m_ID2HBITMAP.find(id);
		if (it != m_ID2HBITMAP.end()) {
			return it->second;
		}
		return Default; 
	}
	HBRUSH GetHBRUSH(const Key &id, HBRUSH Default = NULL) 
	{ 
		ID2HBRUSH::iterator it = m_ID2HBRUSH.find(id);
		if (it != m_ID2HBRUSH.end()) {
			return it->second;
		}
		return Default; 
	}
	HFONT GetHFONT(const Key &id, HFONT Default = NULL)
	{ 
		ID2HFONT::iterator it = m_ID2HFONT.find(id);
		if (it != m_ID2HFONT.end()) {
			return it->second;
		}
		return Default; 
	}
	COLORREF GetCOLORREF(const Key &id, COLORREF Default = CLR_INVALID)
	{ 
		ID2COLORREF::iterator it = m_ID2COLORREF.find(id);
		if (it != m_ID2COLORREF.end()) {
			return it->second;
		}
		return Default; 
	}
	BOOL GetRECT(const Key &id, LPRECT pRect)
	{ 
		ID2RECT::iterator it = m_ID2RECT.find(id);
		if (it != m_ID2RECT.end()) {
			*pRect = it->second;
			return TRUE;
		}
		return FALSE; 
	}
	LPCTSTR GetString(const Key &id, LPCTSTR Default = NULL)
	{ 
		ID2String::iterator it = m_ID2String.find(id);
		if (it != m_ID2String.end()) {
			return it->second;
		}
		return Default; 
	}
};

typedef UIgdiManagerT<CString,CStringNoCaseLess> UIStr2GdiManager;
typedef UIgdiManagerT<long> UIID2GdiManager;

#endif//_H_UIGDI_H_