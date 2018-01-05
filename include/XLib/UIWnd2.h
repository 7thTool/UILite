
#pragma once

#ifndef _H_UIWND2_H_
#define _H_UIWND2_H_

#include <UI/UIWnd.h>
#include "UILite.h"

class UIWnd2;
class UIWnd2Manager;

UILITE_API UIWnd2Manager* getUIWnd2Manager();
#define _pUIWnd2Manager getUIWnd2Manager()
//extern UILITE_API UIWnd2Manager* _pUIWnd2Manager;

/*struct UIWnd2Class : public CWndClassInfo
{
	//WNDPROC lpfnWndProc;
};*/
//使用CWndClassInfo
enum
{
	UIWND2_STATE_NORMAL		= 0x00000000UL,
	UIWND2_STATE_HOVER		= 0x00000001UL,
	UIWND2_STATE_CLICKED	= 0x00000002UL,
	UIWND2_STATE_CHECKED	= 0x00000004UL,
	//UIWND2_STATE_DISABLED	= 0x00000008UL,
};

class HUIWnd2;
typedef HUIWnd2* PHUIWnd2;

class UILITE_API UIWnd2Manager
{
private:
	class HUIWND2ThreadData
	{
	public:
		HWND hWndParent; //用于Create
		struct tagTimerInfo
		{
			HWND hWnd;
			UINT nIDEvent;
		};
		typedef std::map<UINT,tagTimerInfo> TimerID2TimerInfo;
		TimerID2TimerInfo nIDEvent2TimerInfo; //定时器映射
		std::deque<MSG> msgQueue; //用于PostMessage
	};
	typedef std::map<DWORD,HUIWND2ThreadData> ThreadID2HUIWnd2Data;
	ThreadID2HUIWnd2Data m_ThreadWnd2Data;
	typedef std::map<HWND,HUIWnd2*> UIWnd2Pool;
	UIWnd2Pool m_hWnd2Pool;
	PHUIWnd2* m_phUIWnd2Pool;
	HWND m_hMaxWnd2;
	HWND m_hMinWnd2;
	HWND m_hNextWnd2;
	CComAutoCriticalSection m_Wnd2Section;
	typedef CComCritSecLock<CComAutoCriticalSection> CComAutoCritSectionLock;
	
	//HWND m_hWndActive;
	HWND m_hWndHover;
	HWND m_hWndFocus;
	HWND m_hWndTabStop;
	HWND m_hWndCapture;

	// 提示信息
	HWND m_hWndToolTip;
	TOOLINFO m_ToolTip;
public:
	UIWnd2Manager();
	~UIWnd2Manager();

protected:
	HUIWnd2* FindpHUIWnd2(HWND hWnd) const;
	HUIWnd2* FindpHUIWnd2Parent(HWND hWnd) const;
	HWND FindhWnd2Parent(HWND hWnd) const;
	HUIWnd2* FindpHUIWnd2Prev(HWND hWnd) const;
	HWND FindhWnd2Prev(HWND hWnd) const;
	HUIWnd2* FindpHUIWnd2Next(HWND hWnd) const;
	HWND FindhWnd2Next(HWND hWnd) const;
	HUIWnd2* FindpHUIWnd2FirstChild(HWND hWnd) const;
	HWND FindhWnd2FirstChild(HWND hWnd) const;
	HUIWnd2* FindpHUIWnd2CurChild(HWND hWnd) const;
	HWND FindhWnd2CurChild(HWND hWnd) const;
	HUIWnd2* FindpHUIWnd2LastChild(HWND hWnd) const;
	HWND FindhWnd2LastChild(HWND hWnd) const;
	void AddPrevWnd2(HWND hWnd, HWND hPrevWnd, HUIWnd2* phWnd2Prev = NULL);
	void AddNextWnd2(HWND hWnd, HWND hNextWnd, HUIWnd2* phWnd2Next = NULL);
	void AddLastWnd2(HWND hWnd, HWND hLastWnd, HUIWnd2* phWnd2Last = NULL);
	void SetWnd2Pos(HWND hWnd, HWND hWndInsertAfter, UINT nFlags);

public:
	//for create or initdialog
	void SethWndParent(HWND hWndParent, DWORD dwThreadID = GetCurrentThreadId());
	HWND GethWndParent(DWORD dwThreadID = GetCurrentThreadId());
	void PostWnd2Message(MSG & msg);
	BOOL GethWnd2Message(MSG & msg);
	//UIWnd2 Add
	void AddWnd2(HWND hWnd, HUIWnd2* phWnd2 = NULL);
	//标准窗口Add
	void AddWnd2(HWND hWnd, HWND hWndParent);
	//统一移除
	void RemoveWnd2(HWND hWnd, HUIWnd2* phWnd2 = NULL);

protected:
	LRESULT DefWindowProc(
		HWND hWnd, 
		UINT Msg, 
		WPARAM wParam, 
		LPARAM lParam 
		);

public:
	static 
#ifndef _MAC
	LRESULT
	WINAPI
#else
	LRESULT
	CALLBACK
#endif
	DefWindowProc2( 
		HWND hWnd, 
		UINT Msg, 
		WPARAM wParam, 
		LPARAM lParam 
		);
	BOOL IsDirectUI(HWND hWnd) const;
	BOOL IsUIWnd2(HWND hWnd) const;
	HWND Create(HINSTANCE hInstance, HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName,
			DWORD dwStyle, DWORD dwExStyle, UINT nID, ATOM atom, LPVOID lpCreateParam = NULL);
	BOOL DestroyWindow(HWND hWnd);
	BOOL EndDialog(HWND hWnd, int nRetCode);
	BOOL DestroyChildWindow(HWND hWnd);
	BOOL IsAutoDelete(HWND hWnd);
	BOOL SetAutoDelete(HWND hWnd, BOOL bDelete = TRUE);
	DWORD GetStyle(HWND hWnd) const;
	DWORD GetExStyle(HWND hWnd) const;
	DWORD GetClassLongA(HWND hWnd, int nIndex);
	DWORD GetClassLongW(HWND hWnd, int nIndex);
	int GetClassNameA(HWND hWnd, LPTSTR lpClassName, int nMaxCount);
	int GetClassNameW(HWND hWnd, LPTSTR lpClassName, int nMaxCount);
	LONG GetWindowLongA(HWND hWnd, int nIndex) const;
	LONG GetWindowLongW(HWND hWnd, int nIndex) const;
	LONG_PTR GetWindowLongPtrA(HWND hWnd, int nIndex) const;
	LONG_PTR GetWindowLongPtrW(HWND hWnd, int nIndex) const;
	LONG SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong);
	LONG SetWindowLongW(HWND hWnd, int nIndex, LONG dwNewLong);
	LONG_PTR SetWindowLongPtrA(HWND hWnd, int nIndex, LONG_PTR dwNewLong);
	LONG_PTR SetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong);
	WORD GetWindowWord(HWND hWnd, int nIndex) const;
	WORD SetWindowWord(HWND hWnd, int nIndex, WORD wNewWord);
// Message Functions

	LRESULT SendMessage(HWND hWnd, UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
	BOOL PostMessage(HWND hWnd, UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
	BOOL SendNotifyMessage(HWND hWnd, UINT message, WPARAM wParam = 0, LPARAM lParam = 0);

// Window Text Functions

	BOOL SetWindowText(HWND hWnd, LPCTSTR lpszString);
	int GetWindowText(HWND hWnd, LPTSTR lpszStringBuf, int nMaxCount);
	int GetWindowTextLength(HWND hWnd);
// Font Functions

	void SetFont(HWND hWnd, HFONT hFont, BOOL bRedraw = TRUE);
	HFONT GetFont(HWND hWnd) const;
// Menu Functions (non-child windows only)

	HMENU GetMenu(HWND hWnd) const;
	BOOL SetMenu(HWND hWnd, HMENU hMenu);
	BOOL DrawMenuBar(HWND hWnd);
	HMENU GetSystemMenu(HWND hWnd, BOOL bRevert) const;
	BOOL HiliteMenuItem(HWND hWnd, HMENU hMenu, UINT uItemHilite, UINT uHilite);
// Window Size and Position Functions

	BOOL IsIconic(HWND hWnd) const;
	BOOL IsZoomed(HWND hWnd) const;
	BOOL MoveWindow(HWND hWnd, int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE);
	BOOL MoveWindow(HWND hWnd, LPCRECT lpRect, BOOL bRepaint = TRUE);
	BOOL SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);
	BOOL SetWindowPos(HWND hWnd, HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags);
	UINT ArrangeIconicWindows(HWND hWnd);
	BOOL BringWindowToTop(HWND hWnd);
	BOOL GetWindowRect(HWND hWnd, LPRECT lpRect) const;
	BOOL GetClientRect(HWND hWnd, LPRECT lpRect) const;
	BOOL GetWindowPlacement(HWND hWnd, WINDOWPLACEMENT FAR* lpwndpl) const;
	BOOL SetWindowPlacement(HWND hWnd, const WINDOWPLACEMENT FAR* lpwndpl);
// Coordinate Mapping Functions

	BOOL ClientToScreen(HWND hWnd, LPPOINT lpPoint) const;
	BOOL ClientToScreen(HWND hWnd, LPRECT lpRect) const;
	BOOL ScreenToClient(HWND hWnd, LPPOINT lpPoint) const;
	BOOL ScreenToClient(HWND hWnd, LPRECT lpRect) const;
	int MapWindowPoints(HWND hWnd, HWND hWndTo, LPPOINT lpPoint, UINT nCount) const;
	int MapWindowPoints(HWND hWnd, HWND hWndTo, LPRECT lpRect) const;
// Update and Painting Functions

	HDC BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint);
	void EndPaint(HWND hWnd, LPPAINTSTRUCT lpPaint);
	HDC GetDC(HWND hWnd);
	HDC GetWindowDC(HWND hWnd);
	int ReleaseDC(HWND hWnd, HDC hDC);
	void Print(HWND hWnd, HDC hDC, DWORD dwFlags);
	void PrintClient(HWND hWnd, HDC hDC, DWORD dwFlags);
	BOOL UpdateWindow(HWND hWnd);
	void SetRedraw(HWND hWnd, BOOL bRedraw = TRUE);
	BOOL GetUpdateRect(HWND hWnd, LPRECT lpRect, BOOL bErase = FALSE);
	int GetUpdateRgn(HWND hWnd, HRGN hRgn, BOOL bErase = FALSE);
	BOOL Invalidate(HWND hWnd, BOOL bErase = TRUE);
	BOOL InvalidateRect(HWND hWnd, LPCRECT lpRect, BOOL bErase = TRUE);
	BOOL ValidateRect(HWND hWnd, LPCRECT lpRect);
	BOOL InvalidateRgn(HWND hWnd, HRGN hRgn, BOOL bErase = TRUE);
	BOOL ValidateRgn(HWND hWnd, HRGN hRgn);
	BOOL ShowWindow(HWND hWnd, int nCmdShow);
	/*BOOL IsWindowVisible(HWND hWnd) const;*/
	BOOL _ShowWindow(HWND hWnd, int nCmdShow);

	BOOL ShowOwnedPopups(HWND hWnd, BOOL bShow = TRUE);
	HDC GetDCEx(HWND hWnd, HRGN hRgnClip, DWORD flags);
	BOOL LockWindowUpdate(HWND hWnd, BOOL bLock = TRUE);
	BOOL RedrawWindow(HWND hWnd, LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
// Timer Functions

	UINT SetTimer(HWND hWnd, UINT nIDEvent, UINT nElapse);
	UINT FindTimer(HWND hWnd, UINT nIDEvent, BOOL bErase = FALSE);
	BOOL PostTimer(UINT_PTR nIDEvent);
	BOOL KillTimer(HWND hWnd, UINT nIDEvent);

// Window State Functions

	BOOL IsWindowEnabled(HWND hWnd) const;
	BOOL EnableWindow(HWND hWnd, BOOL bEnable = TRUE);
	HWND SetActiveWindow(HWND hWnd);
	HWND SetHover(HWND hWnd, WPARAM wParam = 0, LPARAM lParam = 0L);
	HWND GetHover();
	HWND SetCapture(HWND hWnd);
	HWND GetCapture(void);
	BOOL ReleaseCapture();
	HWND SetFocus(HWND hWnd, BOOL bKillFocus, BOOL bSetFocus);
	HWND SetFocus(HWND hWnd);
	HWND GetFocus();

// Dialog-Box Item Functions

	BOOL CheckDlgButton(HWND hWnd, int nIDButton, UINT nCheck);
	BOOL CheckRadioButton(HWND hWnd, int nIDFirstButton, int nIDLastButton, int nIDCheckButton);
	int DlgDirList(HWND hWnd, LPTSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT nFileType);
	int DlgDirListComboBox(HWND hWnd, LPTSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT nFileType);
	BOOL DlgDirSelect(HWND hWnd, LPTSTR lpString, int nCount, int nIDListBox);
	BOOL DlgDirSelectComboBox(HWND hWnd, LPTSTR lpString, int nCount, int nIDComboBox);
	UINT GetDlgItemInt(HWND hWnd, int nID, BOOL* lpTrans = NULL, BOOL bSigned = TRUE);
	UINT GetDlgItemText(HWND hWnd, int nID, LPTSTR lpStr, int nMaxCount);
	BOOL GetDlgItemText(HWND hWnd, int nID, BSTR& bstrText);
	HWND GetNextDlgGroupItem(HWND hWnd, HWND hWndCtl, BOOL bPrevious = FALSE) const;
	HWND GetNextDlgTabItem(HWND hWnd, HWND hWndCtl, BOOL bPrevious = FALSE) const;
	UINT IsDlgButtonChecked(HWND hWnd, int nIDButton) const;
	LRESULT SendDlgItemMessage(HWND hWnd, int nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
	BOOL SetDlgItemInt(HWND hWnd, int nID, UINT nValue, BOOL bSigned = TRUE);
	BOOL SetDlgItemText(HWND hWnd, int nID, LPCTSTR lpszString);

#ifndef _ATL_NO_HOSTING
	HRESULT GetDlgControl(HWND hWnd, int nID, REFIID iid, void** ppUnk);
#endif //!_ATL_NO_HOSTING

// Scrolling Functions

	int GetScrollPos(HWND hWnd, int nBar) const;
	BOOL GetScrollRange(HWND hWnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos) const;
	BOOL ScrollWindow(HWND hWnd, int xAmount, int yAmount, LPCRECT lpRect = NULL, LPCRECT lpClipRect = NULL);
	int ScrollWindowEx(HWND hWnd, int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate, UINT uFlags);
	int ScrollWindowEx(HWND hWnd, int dx, int dy, UINT uFlags, LPCRECT lpRectScroll = NULL, LPCRECT lpRectClip = NULL, HRGN hRgnUpdate = NULL, LPRECT lpRectUpdate = NULL);
	int SetScrollPos(HWND hWnd, int nBar, int nPos, BOOL bRedraw = TRUE);
	BOOL SetScrollRange(HWND hWnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw = TRUE);
	BOOL ShowScrollBar(HWND hWnd, UINT nBar, BOOL bShow = TRUE);
	BOOL EnableScrollBar(HWND hWnd, UINT uSBFlags, UINT uArrowFlags = ESB_ENABLE_BOTH);

// Window Access Functions

	HWND ChildWindowFromPoint(HWND hWnd, POINT point) const;

#define CWP_SKIPDIRECTUIWND		0X8000
#define CWP_SKIPNODIRECTUIWND	0X4000

	HWND ChildWindowFromPointEx(HWND hWnd, POINT point, UINT uFlags) const;
	HWND GetTopWindow(HWND hWnd) const;
	HWND GetWindow(HWND hWnd, UINT nCmd) const;
	HWND GetLastActivePopup(HWND hWnd) const;
	BOOL IsChild(HWND hWnd, HWND hWndChild) const;
	HWND GetParent(HWND hWnd) const;
	HWND SetParent(HWND hWnd, HWND hWndNewParent);
	HWND GetSafeHwnd(HWND hWnd) const;

// Window Tree Access

	int GetDlgCtrlID(HWND hWnd) const;
	int SetDlgCtrlID(HWND hWnd, int nID);
	HWND GetDlgItem(HWND hWnd, int nID) const;

// Alert Functions

	BOOL FlashWindow(HWND hWnd, BOOL bInvert);
	int MessageBox(HWND hWnd, LPCTSTR lpszText, LPCTSTR lpszCaption = _T(""), UINT nType = MB_OK);

// Clipboard Functions

	BOOL ChangeClipboardChain(HWND hWnd, HWND hWndNewNext);
	HWND SetClipboardViewer(HWND hWnd);
	BOOL OpenClipboard(HWND hWnd);

// Caret Functions

	BOOL CreateCaret(HWND hWnd, HBITMAP hBitmap);
	BOOL CreateSolidCaret(HWND hWnd, int nWidth, int nHeight);
	BOOL CreateGrayCaret(HWND hWnd, int nWidth, int nHeight);
	BOOL HideCaret(HWND hWnd);
	BOOL ShowCaret(HWND hWnd);

#ifdef _INC_SHELLAPI
// Drag-Drop Functions
	void DragAcceptFiles(HWND hWnd, BOOL bAccept = TRUE);
#endif

// Icon Functions

	HICON SetIcon(HWND hWnd, HICON hIcon, BOOL bBigIcon = TRUE);
	HICON GetIcon(HWND hWnd, BOOL bBigIcon = TRUE) const;

// Help Functions

	BOOL WinHelp(HWND hWnd, LPCTSTR lpszHelp, UINT nCmd = HELP_CONTEXT, DWORD dwData = 0);
	BOOL SetWindowContextHelpId(HWND hWnd, DWORD dwContextHelpId);
	DWORD GetWindowContextHelpId(HWND hWnd) const;

// Hot Key Functions

	int SetHotKey(HWND hWnd, WORD wVirtualKeyCode, WORD wModifiers);
	DWORD GetHotKey(HWND hWnd) const;

// Misc. Operations

//N new
	BOOL GetScrollInfo(HWND hWnd, int nBar, LPSCROLLINFO lpScrollInfo);
	BOOL SetScrollInfo(HWND hWnd, int nBar, LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE);
	BOOL GetScrollBarInfo(HWND hWnd, LONG idObject, PSCROLLBARINFO pScrollBarInfo) const;
	BOOL SetScrollBarInfo(HWND hWnd, LONG idObject, PSCROLLBARINFO pScrollBarInfo);
	BOOL IsDialogMessage(HWND hWnd, LPMSG lpMsg);
	void NextDlgCtrl(HWND hWnd) const;
	void PrevDlgCtrl(HWND hWnd) const;
	void GotoDlgCtrl(HWND hWnd, HWND hWndCtrl) const;
	BOOL ResizeClient(HWND hWnd, int nWidth, int nHeight, BOOL bRedraw = TRUE);
	int GetWindowRgn(HWND hWnd, HRGN hRgn);
	int SetWindowRgn(HWND hWnd, HRGN hRgn, BOOL bRedraw = FALSE);
	HDWP DeferWindowPos(HWND hWnd, HDWP hWinPosInfo, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);
	DWORD GetWindowThreadProcessId(HWND hWnd, LPDWORD lpdwProcessId);
	DWORD GetWindowThreadID(HWND hWnd);
	DWORD GetWindowProcessID(HWND hWnd);
	BOOL IsWindow(HWND hWnd);
	BOOL IsWindowUnicode(HWND hWnd);
	BOOL IsParentDialog(HWND hWnd);
	BOOL ShowWindowAsync(HWND hWnd, int nCmdShow);
	HWND GetDescendantWindow(HWND hWnd, int nID) const;
	void SendMessageToDescendants(HWND hWnd, UINT message, WPARAM wParam = 0, LPARAM lParam = 0, BOOL bDeep = TRUE);
	BOOL CenterWindow(HWND hWnd, HWND hWndCenter = NULL);
	BOOL ModifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	BOOL ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	BOOL ModifyState(HWND hWnd, DWORD dwRemove, DWORD dwAdd);
	BOOL SetState(HWND hWnd, DWORD dwState);
	DWORD GetState(HWND hWnd) const;
	BOOL IsWindowVisible(HWND hWnd);
	BOOL IsWindowVisible(HWND hWnd, BOOL bDeep);
	BOOL SetLayeredWindowAttributes(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
	BOOL GetLayeredWindowAttributes(HWND hWnd, COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags);
	void SetAlpha(HWND hWnd, BYTE bAlpha);
	void SetColorKey(HWND hWnd, COLORREF crKey);
	void SetWindowZOrder(HWND hWnd, HWND hWndInsertAfter);
	void GetWindowSize(HWND hWnd, LPSIZE lpSize);
	SIZE GetWindowSize(HWND hWnd);
	void GetClientSize(HWND hWnd, LPSIZE lpSize);
	SIZE GetClientSize(HWND hWnd);
	void SetWindowRect(HWND hWnd, LPCRECT lpRect, BOOL bRedraw = TRUE);
	void SetWindowSize(HWND hWnd, INT cx, INT cy);
	void SetWindowSize(HWND hWnd, SIZE sz);
	void SetClientRect(HWND hWnd, LPCRECT lpRect, BOOL bRedraw = TRUE);
	void SetClientSize(HWND hWnd, SIZE szNew);
	void SetClientSize(HWND hWnd, int cxNew, int cyNew);
	int GetWindowText(HWND hWnd, CString& strText);
	UINT GetDlgItemText(HWND hWnd, int nID, CString& strText);
	LRESULT PostDlgItemMessage(HWND hWnd, int nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0) throw();
	BOOL TrackMouseEvent(HWND hWnd, DWORD dwFalgs = TME_LEAVE);
};

//////////////////////////////////////////////////////////////////////////

class UILITE_API UIWnd2 : public UIWnd
{
public:
	UIWnd2(HWND hWnd = NULL);

	void Attach(HWND hWndNew);
	HWND Detach();

	static UIWnd2* FromHandle(HWND hWnd);

	BOOL DestroyWindow();
	BOOL DestroyChildWindow();
	BOOL IsAutoDelete();
	DWORD GetStyle() const;
	DWORD GetExStyle() const;
	LONG GetWindowLong(int nIndex) const;
	LONG_PTR GetWindowLongPtr(int nIndex) const;
	LONG SetWindowLong(int nIndex, LONG dwNewLong);
	LONG_PTR SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong);
	WORD GetWindowWord(int nIndex) const;
	WORD SetWindowWord(int nIndex, WORD wNewWord);

// Message Functions

	LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) const;
	/*LRESULT SendMessageW(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) const;*/
	BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) const;
	BOOL SendNotifyMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) const;
	// support for C style macros
	static LRESULT SendMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT PostMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Window Text Functions

	BOOL SetWindowText(LPCTSTR lpszString);
	int GetWindowText(LPTSTR lpszStringBuf, int nMaxCount) const;
	int GetWindowTextLength() const;

// Font Functions

	void SetFont(HFONT hFont, BOOL bRedraw = TRUE);
	HFONT GetFont() const;

// Menu Functions (non-child windows only)

	HMENU GetMenu() const;
	BOOL SetMenu(HMENU hMenu);
	BOOL DrawMenuBar();
	HMENU GetSystemMenu(BOOL bRevert) const;
	BOOL HiliteMenuItem(HMENU hMenu, UINT uItemHilite, UINT uHilite);

// Window Size and Position Functions

	BOOL IsIconic() const;
	BOOL IsZoomed() const;
	BOOL MoveWindow(int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE);
	BOOL MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);
	BOOL SetWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);
	BOOL SetWindowPos(HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags);
	UINT ArrangeIconicWindows();
	BOOL BringWindowToTop();
	BOOL GetWindowRect(LPRECT lpRect) const;
	BOOL GetClientRect(LPRECT lpRect) const;
	BOOL GetWindowPlacement(WINDOWPLACEMENT FAR* lpwndpl) const;
	BOOL SetWindowPlacement(const WINDOWPLACEMENT FAR* lpwndpl);

// Coordinate Mapping Functions

	BOOL ClientToScreen(LPPOINT lpPoint) const;
	BOOL ClientToScreen(LPRECT lpRect) const;
	BOOL ScreenToClient(LPPOINT lpPoint) const;
	BOOL ScreenToClient(LPRECT lpRect) const;
	int MapWindowPoints(HWND hWndTo, LPPOINT lpPoint, UINT nCount) const;
	int MapWindowPoints(HWND hWndTo, LPRECT lpRect) const;

// Update and Painting Functions

	HDC BeginPaint(LPPAINTSTRUCT lpPaint);
	void EndPaint(LPPAINTSTRUCT lpPaint);
	HDC GetDC();
	HDC GetWindowDC();
	int ReleaseDC(HDC hDC);
	void Print(HDC hDC, DWORD dwFlags) const;
	void PrintClient(HDC hDC, DWORD dwFlags) const;
	BOOL UpdateWindow();
	void SetRedraw(BOOL bRedraw = TRUE);
	BOOL GetUpdateRect(LPRECT lpRect, BOOL bErase = FALSE);
	int GetUpdateRgn(HRGN hRgn, BOOL bErase = FALSE);
	BOOL Invalidate(BOOL bErase = TRUE);
	BOOL InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	BOOL ValidateRect(LPCRECT lpRect);
	void InvalidateRgn(HRGN hRgn, BOOL bErase = TRUE);
	BOOL ValidateRgn(HRGN hRgn);
	BOOL ShowWindow(int nCmdShow);
	/*BOOL IsWindowVisible() const*/

	BOOL ShowOwnedPopups(BOOL bShow = TRUE);
	HDC GetDCEx(HRGN hRgnClip, DWORD flags);
	BOOL LockWindowUpdate(BOOL bLock = TRUE);
	BOOL RedrawWindow(LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
// Timer Functions

	UINT SetTimer(UINT nIDEvent, UINT nElapse);
	BOOL KillTimer(UINT nIDEvent);
// Window State Functions

	BOOL IsWindowEnabled() const;
	BOOL EnableWindow(BOOL bEnable = TRUE);
	HWND SetActiveWindow();
	HWND GetHover();
	HWND SetCapture();
	HWND GetCapture();
	BOOL ReleaseCapture();
	static HWND SetFocus(HWND hWnd);
	HWND SetFocus();
	/*HWND GetFocus();*/

// Dialog-Box Item Functions

	BOOL CheckDlgButton(int nIDButton, UINT nCheck);
	BOOL CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton);
	int DlgDirList(LPTSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT nFileType);
	int DlgDirListComboBox(LPTSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT nFileType);
	BOOL DlgDirSelect(LPTSTR lpString, int nCount, int nIDListBox);
	BOOL DlgDirSelectComboBox(LPTSTR lpString, int nCount, int nIDComboBox);
	UINT GetDlgItemInt(int nID, BOOL* lpTrans = NULL, BOOL bSigned = TRUE) const;
	UINT GetDlgItemText(int nID, LPTSTR lpStr, int nMaxCount) const;
	BOOL GetDlgItemText(int nID, BSTR& bstrText) const;
	HWND GetNextDlgGroupItem(HWND hWndCtl, BOOL bPrevious = FALSE) const;
	HWND GetNextDlgTabItem(HWND hWndCtl, BOOL bPrevious = FALSE) const;
	UINT IsDlgButtonChecked(int nIDButton) const;
	LRESULT SendDlgItemMessage(int nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
	BOOL SetDlgItemInt(int nID, UINT nValue, BOOL bSigned = TRUE);
	BOOL SetDlgItemText(int nID, LPCTSTR lpszString);
#ifndef _ATL_NO_HOSTING
	HRESULT GetDlgControl(int nID, REFIID iid, void** ppUnk);
#endif //!_ATL_NO_HOSTING

// Scrolling Functions

	int GetScrollPos(int nBar) const;
	BOOL GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const;
	BOOL ScrollWindow(int xAmount, int yAmount, LPCRECT lpRect = NULL, LPCRECT lpClipRect = NULL);
	int ScrollWindowEx(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate, UINT uFlags);
	int ScrollWindowEx(int dx, int dy, UINT uFlags, LPCRECT lpRectScroll = NULL, LPCRECT lpRectClip = NULL, HRGN hRgnUpdate = NULL, LPRECT lpRectUpdate = NULL);
	int SetScrollPos(int nBar, int nPos, BOOL bRedraw = TRUE);
	BOOL SetScrollRange(int nBar, int nMinPos, int nMaxPos, BOOL bRedraw = TRUE);
	BOOL ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	BOOL EnableScrollBar(UINT uSBFlags, UINT uArrowFlags = ESB_ENABLE_BOTH);

// Window Access Functions

	HWND ChildWindowFromPoint(POINT point) const;
	HWND ChildWindowFromPointEx(POINT point, UINT uFlags) const;
	HWND GetTopWindow() const;
	HWND GetTopLevelParent() const;
	HWND GetTopLevelWindow() const;
	HWND GetWindow(UINT nCmd) const;
	HWND GetWindow(HWND hWnd, UINT nCmd) const;
	HWND GetLastActivePopup() const;
	BOOL IsChild(HWND hWnd) const;
	HWND GetParent() const;
	HWND SetParent(HWND hWndNewParent);
	HWND GetSafeHwnd() const;

// Window Tree Access

	int GetDlgCtrlID() const;
	int SetDlgCtrlID(int nID);
	HWND GetDlgItem(int nID) const;

// Alert Functions

	BOOL FlashWindow(BOOL bInvert);
	int MessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption = _T(""), UINT nType = MB_OK);

// Clipboard Functions

	BOOL ChangeClipboardChain(HWND hWndNewNext);
	HWND SetClipboardViewer();
	BOOL OpenClipboard();

// Caret Functions

	BOOL CreateCaret(HBITMAP hBitmap);
	BOOL CreateSolidCaret(int nWidth, int nHeight);
	BOOL CreateGrayCaret(int nWidth, int nHeight);
	BOOL HideCaret();
	BOOL ShowCaret();

#ifdef _INC_SHELLAPI
// Drag-Drop Functions
	void DragAcceptFiles(BOOL bAccept = TRUE);
#endif

// Icon Functions

	HICON SetIcon(HICON hIcon, BOOL bBigIcon = TRUE);
	HICON GetIcon(BOOL bBigIcon = TRUE) const;
// Help Functions

	BOOL WinHelp(LPCTSTR lpszHelp, UINT nCmd = HELP_CONTEXT, DWORD dwData = 0);
	BOOL SetWindowContextHelpId(DWORD dwContextHelpId);
	DWORD GetWindowContextHelpId() const;

// Hot Key Functions

	int SetHotKey(WORD wVirtualKeyCode, WORD wModifiers);
	DWORD GetHotKey() const;
// Misc. Operations

//N new
	BOOL GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo);
	BOOL SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE);
	BOOL GetScrollBarInfo(LONG idObject, PSCROLLBARINFO pScrollBarInfo) const;
	BOOL SetScrollBarInfo(LONG idObject, PSCROLLBARINFO pScrollBarInfo);
	BOOL IsDialogMessage(LPMSG lpMsg);
	void NextDlgCtrl() const;
	void PrevDlgCtrl() const;
	void GotoDlgCtrl(HWND hWndCtrl) const;
	BOOL ResizeClient(int nWidth, int nHeight, BOOL bRedraw = TRUE);
	int GetWindowRgn(HRGN hRgn);
	int SetWindowRgn(HRGN hRgn, BOOL bRedraw = FALSE);
	HDWP DeferWindowPos(HDWP hWinPosInfo, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);
	DWORD GetWindowThreadID();
	DWORD GetWindowProcessID();
	BOOL IsDirectUI();
	BOOL IsWindow();
	BOOL IsWindowUnicode();
	BOOL IsParentDialog();
	BOOL ShowWindowAsync(int nCmdShow);
	HWND GetDescendantWindow(int nID) const;
	void SendMessageToDescendants(UINT message, WPARAM wParam = 0, LPARAM lParam = 0, BOOL bDeep = TRUE);
	BOOL CenterWindow(HWND hWndCenter = NULL);
	BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	/*BOOL ModifyState(DWORD dwRemove, DWORD dwAdd);
	BOOL SetState(DWORD dwState);
	DWORD GetState() const;*/

	//////////////////////////////////////////////////////////////////////////

	BOOL IsWindowVisible(BOOL bDeep = FALSE);
	BOOL SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
	BOOL GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags);
	void SetAlpha(BYTE bAlpha);
	void SetColorKey(COLORREF crKey);
	void SetWindowZOrder(HWND hWndInsertAfter);
	void GetWindowSize(LPSIZE lpSize);
	SIZE GetWindowSize();
	void GetClientSize(LPSIZE lpSize);
	SIZE GetClientSize();
	void SetWindowRect(LPCRECT lpRect, BOOL bRedraw = TRUE);
	void SetWindowSize(INT cx, INT cy);
	void SetWindowSize(SIZE sz);
	void SetClientRect(LPCRECT lpRect, BOOL bRedraw = TRUE);
	void SetClientSize(SIZE szNew);
	void SetClientSize(int cxNew, int cyNew);
	int GetWindowText(CString& strText) const;
	UINT GetDlgItemText(int nID, CString& strText) const;
	LRESULT PostDlgItemMessage(int nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0) throw();
	BOOL TrackMouseEvent(DWORD dwFalgs = TME_LEAVE);
};

//////////////////////////////////////////////////////////////////////////

#define DEFINEENUMCHILDPROC(name, code) \
static BOOL CALLBACK name(HWND hwnd, LPARAM lParam) \
{ \
	T* pT = (T*)lParam; \
	ATLASSERT(pT); \
	NMHDR nmh = {0}; \
	nmh.hwndFrom = hwnd; \
	nmh.idFrom = ::GetDlgCtrlID(hwnd); \
	nmh.code = code; \
	pT->SendMessage(WM_NOTIFY, (WPARAM)nmh.code, (LPARAM)&nmh); \
	return TRUE; \
} 

//////////////////////////////////////////////////////////////////////////

// NOTICE: WS_TABSTOP needed for accept focus
//         WS_CLIPSIBLINGS may cause IE Control Redraw Error
typedef CWinTraits<WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_TABSTOP, 0> UICtrl2Traits;

#define DECLARE_WND_SUPERCLASS_EX(WndClassName, OrigWndClassName, style, bkgnd) \
	static ATL::CWndClassInfo& GetWndClassInfo() \
	{ \
		static ATL::CWndClassInfo wc = \
		{ \
			{ sizeof(WNDCLASSEX), style, StartWindowProc, \
				0, 0, NULL, NULL, NULL, (HBRUSH)(bkgnd + 1), NULL, WndClassName, NULL }, \
			OrigWndClassName, NULL, NULL, TRUE, 0, _T("") \
		}; \
		return wc; \
	}

#define DECLARE_WND2_CLASS(style) \
	DECLARE_WND_SUPERCLASS_EX(NULL,GetWndClassName(),style,BLACK_BRUSH)

#define DECLARE_WND2_CLASS_EX(style, bkgnd) \
	DECLARE_WND_SUPERCLASS_EX(NULL,GetWndClassName(),style,bkgnd)

//////////////////////////////////////////////////////////////////////////

//#define BEGIN_BEFORE_MSG_MAP(theClass) \
//public: \
//	BOOL BeforeProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0) \
//	{ \
//		BOOL bHandled = TRUE; \
//		hWnd; \
//		uMsg; \
//		wParam; \
//		lParam; \
//		lResult; \
//		bHandled; \
//		switch(dwMsgMapID) \
//		{ \
//		case 0:
//
//#define CHAIN_BEFORE_MSG_MAP(theChainClass) \
//	{ \
//		if(theChainClass::BeforeProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
//		return TRUE; \
//	}
//
//#define END_BEFORE_MSG_MAP() \
//	END_MSG_MAP()
//
//#define BEGIN_AFTER_MSG_MAP(theClass) \
//public: \
//	BOOL AfterProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0) \
//	{ \
//		BOOL bHandled = TRUE; \
//		hWnd; \
//		uMsg; \
//		wParam; \
//		lParam; \
//		lResult; \
//		bHandled; \
//		switch(dwMsgMapID) \
//		{ \
//		case 0:
//
//#define CHAIN_AFTER_MSG_MAP(theChainClass) \
//	{ \
//		if(theChainClass::AfterProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
//		return TRUE; \
//	}
//
//#define END_AFTER_MSG_MAP() \
//	END_MSG_MAP()

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase = UIWnd2>
class UIWnd2Map
{
	typedef UIWnd2Map<T> This;
	typedef TBase Base;
public:
	UIWnd2Map()
	{
		
	}

	//////////////////////////////////////////////////////////////////////////

	/*LRESULT Notify(HWND hWnd, int code)
	{
		T* pT = static_cast<T*>(this);
		NMHDR nmh = {0};
		nmh.hwndFrom = *pT;
		nmh.idFrom = pT->GetDlgCtrlID();
		nmh.code = code;
		return pT->Notify(hWnd, (LPNMHDR)&nmh);
	}

	LRESULT Notify(HWND hWnd, LPNMHDR lphdr)
	{
		T* pT = static_cast<T*>(this);
		return T::SendMessage(hWnd, WM_NOTIFY, (WPARAM)lphdr->code, (LPARAM)lphdr);
	}
	
	LRESULT NotifyCommand(HWND hWnd, int code)
	{
		T* pT = static_cast<T*>(this);
		return T::SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(code,pT->GetDlgCtrlID()), (LPARAM)(HWND)(*pT));
	}*/

	//////////////////////////////////////////////////////////////////////////

	BEGIN_BEFORE_MSG_MAP(This)
		MESSAGE_HANDLER(WM_DESTROY, OnBeforeDestroy)
		MESSAGE_HANDLER(WM_NCDESTROY, OnBeforeNcDestroy)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGING, OnBeforeWindowPosChanging)
		MESSAGE_HANDLER(WM_PAINT, OnBeforePaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnBeforePaint)
		MESSAGE_HANDLER(WM_PAINTEFFECTMSG, OnBeforePaintEffect)
		MESSAGE_HANDLER(WM_TIMER, OnBeforeTimer)
		MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnBeforeMouse)
		MESSAGE_HANDLER(WM_MOUSEHOVER, OnBeforeMouseHover)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnBeforeMouseLeave)
		MESSAGE_HANDLER(WM_SETFOCUS, OnBeforeSetFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnBeforeKillFocus)
		MESSAGE_HANDLER(WM_SETCURSOR, OnBeforeSetCursor)
		MESSAGE_HANDLER(WM_CONTEXTMENU, OnBeforeContextMenu)
		MESSAGE_RANGE_HANDLER(WM_KEYFIRST, WM_KEYLAST, OnBeforeKey)
		MESSAGE_HANDLER(WM_FORWARDMSG, OnBeforeForwardMsg)
		MESSAGE_HANDLER(WM_POSTDIRECTUIMSG, OnBeforePostMessage)
	END_BEFORE_MSG_MAP()
	
	LRESULT OnBeforeDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if (_pUIWnd2Manager->GetHover() == *pT) {
			_pUIWnd2Manager->SetHover(NULL);
		}
		if (_pUIWnd2Manager->GetFocus() == *pT) {
			_pUIWnd2Manager->SetFocus(NULL, FALSE, FALSE);
		}
		if (_pUIWnd2Manager->GetCapture() == *pT) {
			_pUIWnd2Manager->ReleaseCapture();
		}
		return 0L;
	}

	LRESULT OnBeforeNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0L;
	}

	LRESULT OnBeforeWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		/*WINDOWPOS* pPos = (WINDOWPOS*)lParam;
		if (pPos) {
			if (!(pPos->flags & SWP_NOMOVE)) {
				SIZE szOffset = {0};
				RECT rcWnd = {0};
				pT->GetWindowRect(&rcWnd);
				_pUIWnd2Manager->ScreenToClient(pT->GetParent(), &rcWnd);
				if (pPos->x != rcWnd.left || pPos->y != rcWnd.top) {
					szOffset.cx = pPos->x - rcWnd.left;
					szOffset.cy = pPos->y - rcWnd.top;
					HWND hChild = pT->GetWindow(*pT, GW_CHILD);
					while (hChild)
					{
						RECT rcChild = {0};
						_pUIWnd2Manager->GetWindowRect(hChild, &rcChild);
						_pUIWnd2Manager->ScreenToClient(*pT, &rcChild);
						::OffsetRect(&rcChild, szOffset.cx, szOffset.cy);
						_pUIWnd2Manager->MoveWindow(hChild, &rcChild, FALSE);
						
						hChild = pT->GetWindow(hChild, GW_HWNDNEXT);
					}
				}
			}
		}*/
		return 0L;
	}

	LRESULT OnBeforePaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if(TBase::GetWndClassName() && !pT->IsDirectUI()) {
			bHandled = FALSE;
			return bHandled;
		}

#if 0
		CDCHandle dc((HDC)wParam);
		//AFTERPAINT要ENDPAINT
		if (!dc) {
			PAINTSTRUCT ps;
			dc = pT->BeginPaint(&ps);
			//ATLASSERT(hdc == ps.hdc); 现在使用的是MemDC
		}
		if (pT->IsDirectUI()) {
			/*CRect rcClient;
			pT->GetClientRect(&rcClient);
			if (!dc.RectVisible(&rcClient)) {
				pT->EndPaint(NULL);
				bHandled = TRUE;
			}*/
		}
#else
		//AFTERPAINT要ENDPAINT
		if (!wParam && !pT->IsDirectUI()) {
			PAINTSTRUCT ps;
			HDC hdc = pT->BeginPaint(&ps);
			//ATLASSERT(hdc == ps.hdc); 现在使用的是MemDC
		}
#endif//
		
		return 0L;
	}

	LRESULT OnBeforePaintEffect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		PPAINTEFFECT pPE = (PPAINTEFFECT)lParam;
		if (pPE) {
			HWND hChild = pT->GetWindow(*pT, GW_CHILD);
			while (hChild)
			{
				if (_pUIWnd2Manager->IsDirectUI(hChild) && _pUIWnd2Manager->IsWindowVisible(hChild)) {
					RECT rcChild = {0};
					_pUIWnd2Manager->GetWindowRect(hChild, &rcChild);
					//_pUIWnd2Manager->MapWindowPoints(NULL, *pT, &rcChild);
					_pUIWnd2Manager->ScreenToClient(*pT, &rcChild);
					CDCHandle dc(pPE->hSrcDC);
					dc.OffsetWindowOrg(-rcChild.left, -rcChild.top);
					T::SendMessage(hChild, uMsg, wParam, lParam);
					dc.OffsetWindowOrg(rcChild.left, rcChild.top);
				}
				hChild = pT->GetWindow(hChild, GW_HWNDNEXT);
			}
		}

		return 0L;
	}

	LRESULT OnBeforeTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if(pT->IsDirectUI()) {
			return bHandled;
		}

		if (_pUIWnd2Manager->PostTimer(wParam)) {
			bHandled = TRUE;
		}

		return 0L;
	}

	LRESULT OnBeforeMouse(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);

		POINT pt;
		POINTSTOPOINT(pt, lParam);

		HWND hWndCapture = pT->GetCapture();
		if (hWndCapture) {
			if(hWndCapture == *pT) {
				return bHandled;
			} else {
				bHandled = TRUE;
				_pUIWnd2Manager->MapWindowPoints(*pT, hWndCapture, &pt, 1);
				return T::SendMessage(hWndCapture, uMsg, wParam, POINTTOPOINTS(pt));
			}
		}

		if (!pT->IsDirectUI() && uMsg == WM_MOUSEMOVE) {
			pT->TrackMouseEvent(TME_LEAVE);
		}
		
		HWND hChild = pT->ChildWindowFromPointEx(pt, CWP_SKIPINVISIBLE|CWP_SKIPNODIRECTUIWND);
		if (hChild) {
			if (_pUIWnd2Manager->IsDirectUI(hChild)) {
				bHandled = TRUE;
				_pUIWnd2Manager->MapWindowPoints(*pT, hChild, &pt, 1);
				return T::SendMessage(hChild, uMsg, wParam, POINTTOPOINTS(pt));
			}
		} else {
			switch(uMsg)
			{
			case WM_LBUTTONDOWN:
				{
					_pUIWnd2Manager->SetFocus(*pT);
				}
				break;
			case WM_MOUSEMOVE:
				{
					_pUIWnd2Manager->SetHover(*pT, wParam, lParam);
				}
				break;
			}
		}
		return 0L;
	}

	LRESULT OnBeforeMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if (pT->IsDirectUI()) {
			if(!T::SendMessage(pT->GetParent(), WM_SETCURSOR, (WPARAM)pT->m_hWnd, MAKELPARAM(0,WM_MOUSEHOVER))) {
				pT->SendMessage(WM_SETCURSOR, (WPARAM)pT->m_hWnd, MAKELPARAM(0,WM_MOUSEHOVER));
			}
		}
		return 0L;
	}

	LRESULT OnBeforeMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if (!pT->IsDirectUI()) {
			HWND hWnd = _pUIWnd2Manager->SetHover(NULL, wParam, lParam);
		}
		return 0L;
	}

	LRESULT OnBeforeSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if (!pT->IsDirectUI()) {
			_pUIWnd2Manager->SetFocus(*pT, FALSE, FALSE);
		}
		return 0L;
	}

	LRESULT OnBeforeKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if (!pT->IsDirectUI()) {
			_pUIWnd2Manager->SetFocus(NULL, FALSE, FALSE);
		}
		return 0L;
	}

	LRESULT OnBeforeSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		HWND hWndHover = _pUIWnd2Manager->GetHover();
		if (*pT == (HWND)wParam && hWndHover && hWndHover != *pT) {
			T::SendMessage(hWndHover, uMsg, (WPARAM)hWndHover, lParam);
			bHandled = TRUE;
		}
		return bHandled;
	}

	LRESULT OnBeforeContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);

		HWND hWndFocus = _pUIWnd2Manager->GetFocus();
		if (hWndFocus && hWndFocus != *pT) {
			bHandled = TRUE;
			return T::SendMessage(hWndFocus, uMsg, wParam, lParam);
		}

		return 0L;
	}

	LRESULT OnBeforeKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		
		HWND hWndFocus = _pUIWnd2Manager->GetFocus();
		if (hWndFocus && hWndFocus != *pT) {
			bHandled = TRUE;
			return T::SendMessage(hWndFocus, uMsg, wParam, lParam);
		}
		
		return 0L;
	}

	LRESULT OnBeforeForwardMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if (pT->IsDirectUI()) {
			return bHandled;
		}

		MSG* pMsg = (MSG*)lParam;
		if (_pUIWnd2Manager->IsDirectUI(pMsg->hwnd)) {
			return bHandled;
		}

		if((pMsg->message>=WM_KEYFIRST && pMsg->message<=WM_KEYLAST)) {
			HWND hWndFocus = _pUIWnd2Manager->GetFocus();
			if (hWndFocus && hWndFocus != *pT) {
				if (_pUIWnd2Manager->GetSafeHwnd(hWndFocus) == *pT) {
					MSG msg = *pMsg;
					pMsg = &msg;
					pMsg->hwnd = hWndFocus;
					//模仿MFC的PreTranslateMessage的实现
					for (HWND hWnd = pMsg->hwnd; hWnd != NULL; )
					{
						if (hWnd == *pT) {
							break;
						}
						UIWnd2 wnd2 = hWnd;
						bHandled = wnd2.SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg);
						if(bHandled) {
							break;
						}
						hWnd = wnd2.GetParent();
					}
				}
			}
		}
		return bHandled;
	}

	LRESULT OnBeforePostMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		ASSERT(!pT->IsDirectUI());
		MSG msg = {0};
		if(_pUIWnd2Manager->GethWnd2Message(msg)) {
			MSG* pMsg = &msg;
			//模仿MFC的PreTranslateMessage的实现
			for (HWND hWnd = *pT; hWnd != NULL; )
			{
				UIWnd2 wnd2 = hWnd;
				if(wnd2.SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg)) {
					return TRUE;
				}
				hWnd = wnd2.GetParent();
			}
			return T::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
		return 0L;
	}

	//////////////////////////////////////////////////////////////////////////

	BEGIN_MSG_MAP(This)
/*#ifdef _DEBUG
		MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouse)
		MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouse)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouse)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
		MESSAGE_HANDLER(WM_PAINTEFFECTMSG, OnPaintEffect)
#endif//*/
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	END_MSG_MAP()

#ifdef _DEBUG //DEBUG//
	/*LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(TBase::GetWndClassName() && !pT->IsDirectUI()) {
			bHandled = FALSE;
			return bHandled;
		}
		if (pT->IsDirectUI()) {
			return TRUE;
		} else {
			bHandled = FALSE;
		}
		return bHandled;
	}

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(TBase::GetWndClassName() && !pT->IsDirectUI()) {
			bHandled = FALSE;
			return bHandled;
		}
		if (wParam) {
			OnPaint((HDC)wParam);
		} else {
			PAINTSTRUCT ps;
			OnPaint(BeginPaint(&ps));
			EndPaint(&ps);
		}
		return bHandled;
	}

	void OnPaint(HDC hdc)
	{
		CDCHandle dc(hdc);
		CString strText;
		GetWindowText(strText);
		RECT rc = {0};
		GetClientRect(&rc);
		
		ATLTRACE("%s RECT={%d,%d,%d,%d}\n", strText, rc.left, rc.top, rc.right, rc.bottom);
		
		dc.SetBkMode(TRANSPARENT);
		
		//dc.FillSolidRect(&rc, RGB(255,255,0));
		dc.FillSolidRect(&rc, RGB(rand()%255,rand()%255,rand()%255));
		dc.TextOut(rc.left, rc.top, strText, strText.GetLength());
	}

	LRESULT OnMouse(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		POINT pt;
		POINTSTOPOINT(pt, lParam);

		CString strText;
		pT->GetWindowText(strText);

		if (uMsg == WM_MOUSEHOVER) {
			ATLTRACE("OnMouseHOVER[%d,%d] %s\n", pt.x, pt.y, strText);
		} else if (uMsg == WM_MOUSELEAVE) {
			ATLTRACE("OnMouseLEAVE[%d,%d] %s\n", pt.x, pt.y, strText);
		} else {
			ATLTRACE("OnMouse[%d,%d] %s\n", pt.x, pt.y, strText);
		}

		if (uMsg == WM_LBUTTONDBLCLK) {
			pT->DestroyWindow();
		}
		return bHandled;
	}

	LRESULT OnPaintEffect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LPPAINTANIMATE pPA = (LPPAINTANIMATE)lParam;
		if (pPA) {
			SIZE szClient;
			GetClientSize(&szClient);
			int nJalousieHeight;  
			nJalousieHeight = szClient.cy / 15; //每个窗子的高度  
			int i, j;  
			for (i = 0; i <= nJalousieHeight; i++ )   
			{  
				for(j = 0; j < 15; j++) //每个窗子  
				{  
					BitBlt(pPA->hDstDC, 0, j * nJalousieHeight, szClient.cx, i, pPA->hSrcDC, 0, j * nJalousieHeight, SRCCOPY);  
				}  
				Sleep(15);  
			}  
		}
		return bHandled;
	}*/
#endif //DEBUG//

	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//ATLTRACE(_T("UIWnd2[%d] SetCursor\n"), wParam);
		T* pT = static_cast<T*>(this);
		HWND hWnd = (HWND)wParam;
		if (*pT == hWnd && (!TBase::GetWndClassName() || _pUIWnd2Manager->IsDirectUI(hWnd))) {
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		} else {
			bHandled = FALSE;
		}
		return bHandled;
	}

	//////////////////////////////////////////////////////////////////////////

	BEGIN_AFTER_MSG_MAP(This)
		MESSAGE_HANDLER(WM_NCCREATE, OnAfterNcCreate)
		MESSAGE_HANDLER(WM_CREATE, OnAfterCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnAfterDestroy)
		MESSAGE_HANDLER(WM_NCDESTROY, OnAfterNcDestroy)
		//MESSAGE_HANDLER(WM_SIZING, OnAfterSizing)
		//MESSAGE_HANDLER(WM_SIZE, OnAfterSize)
		//MESSAGE_HANDLER(WM_MOVING, OnAfterMoving)
		MESSAGE_HANDLER(WM_PAINT, OnAfterPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnAfterPaint)
	END_AFTER_MSG_MAP()

	LRESULT OnAfterNcCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0L;
	}
	
	LRESULT OnAfterCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0L;
	}
	
	LRESULT OnAfterDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		pT->DestroyChildWindow();
		return 0L;
	}

	//WM_NCDESTROY 不会过来，只能使用OnFinalMessage
	LRESULT OnAfterNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		_pUIWnd2Manager->RemoveWnd2(*pT);
		return 0L;
	}

	/*LRESULT OnAfterSizing(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		return OnAfterMoving(uMsg, wParam, lParam, bHandled);
	}

	LRESULT OnAfterSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);

		return 0;
	}

	LRESULT OnAfterMoving(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		LPRECT pRect = (LPRECT)lParam;
		if (pRect) {
			RECT rcWnd = {0};
			pT->GetWindowRect(&rcWnd);
			SIZE szOffset = {pRect->left-rcWnd.left, pRect->top-rcWnd.top};
			HWND hWndChild = _pUIWnd2Manager->GetWindow(*pT, GW_CHILD);
			while (hWndChild) 
			{
				if (_pUIWnd2Manager->IsDirectUI(hWndChild)) {
					RECT rcChild = {0};
					_pUIWnd2Manager->GetWindowRect(hWndChild, &rcChild);
					_pUIWnd2Manager->ScreenToClient(*pT, &rcChild);
					_pUIWnd2Manager->SetWindowPos(hWndChild, NULL, rcChild.left + szOffset.cx, rcChild.top + szOffset.cy, 0, 0, 
						SWP_NOSIZE|SWP_NOREPOSITION|SWP_NOZORDER|SWP_NOSENDCHANGING|SWP_NOACTIVATE);
				}
				hWndChild = _pUIWnd2Manager->GetWindow(hWndChild, GW_HWNDNEXT);
			}
		}
		return 0L;
	}*/

	LRESULT OnAfterPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if(TBase::GetWndClassName() && !pT->IsDirectUI()) {
			return 0L;
		}

#if 0
		CDCHandle dc((HDC)wParam);
		if (dc) {
			HWND hChild = pT->GetWindow(*pT, GW_CHILD);
			while (hChild)
			{
				if (_pUIWnd2Manager->IsDirectUI(hChild) 
					&& _pUIWnd2Manager->IsWindowVisible(hChild)) {
						RECT rcChild = {0};
						_pUIWnd2Manager->GetWindowRect(hChild, &rcChild);
						//_pUIWnd2Manager->MapWindowPoints(NULL, *pT, &rcChild);
						_pUIWnd2Manager->ScreenToClient(*pT, &rcChild);
						if(dc.RectVisible(&rcChild)) {
							dc.OffsetWindowOrg(-rcChild.left, -rcChild.top);
							T::SendMessage(hChild, uMsg, wParam, lParam);
							dc.OffsetWindowOrg(rcChild.left, rcChild.top);
						}
				}
				hChild = pT->GetWindow(hChild, GW_HWNDNEXT);
			}
		} else {
			HWND hChild = pT->GetWindow(*pT, GW_CHILD);
			while (hChild)
			{
				if (_pUIWnd2Manager->IsDirectUI(hChild) 
					&& _pUIWnd2Manager->IsWindowVisible(hChild)) {
					T::SendMessage(hChild, uMsg, wParam, lParam);
				}
				hChild = pT->GetWindow(hChild, GW_HWNDNEXT);
			}
		}

		//和BEFOREPAINT配对
		if (!wParam) {
			pT->EndPaint(NULL);
		}
#else
		CDCHandle dc((HDC)wParam);
		PAINTSTRUCT ps;
		if (!wParam) {
			dc = pT->BeginPaint(&ps);
			pT->EndPaint(&ps);
		}

		if (dc) {
			DWORD dwStyle = pT->GetStyle();
			DWORD dwExStyle =  pT->GetExStyle();
			HWND hChild = pT->GetWindow(*pT, GW_CHILD);
			while (hChild)
			{
				if (_pUIWnd2Manager->IsDirectUI(hChild) 
					&& _pUIWnd2Manager->IsWindowVisible(hChild)) {
					RECT rcChild = {0};
					_pUIWnd2Manager->GetWindowRect(hChild, &rcChild);
					//_pUIWnd2Manager->MapWindowPoints(NULL, *pT, &rcChild);
					_pUIWnd2Manager->ScreenToClient(*pT, &rcChild);
					if(dc.RectVisible(&rcChild)) {
						dc.OffsetWindowOrg(-rcChild.left, -rcChild.top);
						T::SendMessage(hChild, uMsg, (WPARAM)(HDC)dc, lParam);
						dc.OffsetWindowOrg(rcChild.left, rcChild.top);
					}
				}
				hChild = pT->GetWindow(hChild, GW_HWNDNEXT);
			}
		}

		if (pT->IsDirectUI()) {
			pT->ValidateRgn(NULL);
		}
		
		//和BEFOREPAINT配对
		if (!wParam && !pT->IsDirectUI()) {
			pT->EndPaint(&ps);
		}
#endif//

		return 0L;
	}
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase = UIWnd2, class TWinTraits = CControlWinTraits>
class UIWnd2Impl 
: public UIWndImpl<T, TBase, TWinTraits>
, public UIWnd2Map<T, TBase>
{
	typedef UIWnd2Impl<T, TBase, TWinTraits> This;
	typedef UIWndImpl<T, TBase, TWinTraits> Base;
	typedef UIWnd2Map<T, TBase> Wnd2Map;
public:
	DECLARE_WND2_CLASS(CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS)

public:
	UIWnd2Impl()
	{
		
	}

	BOOL IsDirectUI()
	{
		return FALSE;
	}

	BOOL SetAutoDelete(BOOL bDelete = TRUE)
	{
		T* pT = static_cast<T*>(this);
		return _pUIWnd2Manager->SetAutoDelete(*pT, bDelete);
	}

	HWND Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0, 
			UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		ATLASSERT(m_hWnd == NULL);
		_pUIWnd2Manager->SethWndParent(hWndParent);
		HWND hWnd = NULL;
		
		T* pT = static_cast<T*>(this);
		if (!pT->IsDirectUI()) {
			//找到真正的父窗口
			HWND hWndRealParent = hWndParent;
			while (hWndRealParent && _pUIWnd2Manager->IsDirectUI(hWndRealParent))
			{
				hWndRealParent = _pUIWnd2Manager->GetParent(hWndRealParent);
			}
			if (hWndRealParent != hWndParent) {
				_pUIWnd2Manager->MapWindowPoints(hWndParent,hWndRealParent,&rcPos);
			}
			hWnd = Base::Create(hWndRealParent, rcPos, szWindowName, dwStyle, dwExStyle, nID, lpCreateParam);
		} else {
			//设置默认WindowProc
			m_pfnSuperWindowProc = UIWnd2Manager::DefWindowProc2;
#if _MSC_VER<=1200
			//注册新的WindowProc
			if (T::GetWndClassInfo().m_lpszOrigName == NULL)
				T::GetWndClassInfo().m_lpszOrigName = GetWndClassName();
			ATOM atom = T::GetWndClassInfo().Register(&m_pfnSuperWindowProc);
			if(atom == 0)
				return NULL;
			
			dwStyle = T::GetWndStyle(dwStyle);
			dwExStyle = T::GetWndExStyle(dwExStyle);

			_Module.AddCreateWndData(&m_thunk.cd, pT);
			
			if(nID == 0 && (dwStyle & WS_CHILD))
				nID = (UINT)pT;
#else
			if (T::GetWndClassInfo().m_lpszOrigName == NULL)
				T::GetWndClassInfo().m_lpszOrigName = GetWndClassName();
			ATOM atom = T::GetWndClassInfo().Register(&m_pfnSuperWindowProc);

			dwStyle = T::GetWndStyle(dwStyle);
			dwExStyle = T::GetWndExStyle(dwExStyle);

			// set caption
			if (szWindowName == NULL)
				szWindowName = T::GetWndCaption();
			
			BOOL result;
			// Allocate the thunk structure here, where we can fail gracefully.
			result = m_thunk.Init(NULL,NULL);
			if (result == FALSE) {
				SetLastError(ERROR_OUTOFMEMORY);
				return NULL;
			}

			if(atom == 0)
				return NULL;

			_AtlWinModule.AddCreateWndData(&m_thunk.cd, pT);

			if(nID == 0 && (dwStyle & WS_CHILD))
				nID = (UINT)pT;
#endif//

			hWnd = _pUIWnd2Manager->Create(_Module.GetModuleInstance(), hWndParent, rcPos, szWindowName, dwStyle, dwExStyle, nID, atom, lpCreateParam);
			ATLASSERT(m_hWnd == hWnd);
		}
		
		return hWnd;
	}

	//Before Handle WM_CREATE function.
	BOOL PreInitWindow(CREATESTRUCT& cs)
	{
		return TRUE;
	}

	virtual WNDPROC GetWindowProc()
	{
		return WindowProc;
	}

	static LRESULT CALLBACK StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (_pUIWnd2Manager->IsDirectUI(hWnd)) {
			This* pThis = (This*)_Module.ExtractCreateWndData();
			ATLASSERT(pThis != NULL);
			//T* pT = static_cast<T*>(pThis);
			//ATLASSERT(pT != NULL);
			pThis->m_hWnd = hWnd;
			pThis->m_thunk.Init(pThis->GetWindowProc(), pThis);
#if _MSC_VER<=1200
			WNDPROC pProc = (WNDPROC)&(pThis->m_thunk.thunk);
#else
			WNDPROC pProc = pThis->m_thunk.GetWNDPROC();
			//WNDPROC pOldProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)pProc);
#endif//
			WNDPROC pOldProc = (WNDPROC)_pUIWnd2Manager->SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
#ifdef _DEBUG
			// check if somebody has subclassed us already since we discard it
			if(pOldProc != StartWindowProc)
				ATLTRACE2(atlTraceWindowing, 0, _T("Subclassing through a hook discarded.\n"));
#else
			pOldProc;	// avoid unused warning
#endif
			return pProc(hWnd, uMsg, wParam, lParam);
		} else {
			return Base::StartWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		This* pThis = (This*)hWnd;
		ATLASSERT(pThis);
		T* pT = static_cast<T*>(pThis);
		ATLASSERT(pT);

		//HWND hWndParent = pThis->m_hWndParent;
		HWND hWndMyself = pT->m_hWnd;

		if (_pUIWnd2Manager->IsDirectUI(hWndMyself)) {
			LRESULT lResBefore = 0, lResAfter = 0;

			if(pT->BeforeProcessWindowMessage(hWndMyself, uMsg, wParam, lParam, lResBefore, 0)) {
				return lResBefore;
			}

#if _MSC_VER<=1200
			// set a ptr to this message and save the old value
			MSG msg = { hWndMyself, uMsg, wParam, lParam, 0, { 0, 0 } };
			const MSG* pOldMsg = pT->m_pCurrentMsg;
			pT->m_pCurrentMsg = &msg;
			// pass to the message map to process
			//LRESULT lRes;
			BOOL bRet = pT->ProcessWindowMessage(hWndMyself, uMsg, wParam, lParam, lRes, 0);
			// restore saved value for the current message
			ATLASSERT(pT->m_pCurrentMsg == &msg);
			pT->m_pCurrentMsg = pOldMsg;
			// do the default processing if message was not handled
			if(!bRet)
			{
				if(uMsg != WM_NCDESTROY)
					lRes = pT->DefWindowProc(uMsg, wParam, lParam);
				else
				{
					// unsubclass, if needed
					LONG pfnWndProc = _pUIWnd2Manager->GetWindowLong(hWndMyself, GWL_WNDPROC);
					lRes = pT->DefWindowProc(uMsg, wParam, lParam);
					if(pT->m_pfnSuperWindowProc != UIWnd2Manager::DefWindowProc2 && _pUIWnd2Manager->GetWindowLong(pT->m_hWnd, GWL_WNDPROC) == pfnWndProc)
						_pUIWnd2Manager->SetWindowLong(pT->m_hWnd, GWL_WNDPROC, (LONG)pT->m_pfnSuperWindowProc);
					// clear out window handle
					HWND hWnd = hWndMyself;
					pT->m_hWnd = NULL;
					// clean up after window is destroyed
					pT->OnFinalMessage(hWnd);
				}
			}
#else
			// set a ptr to this message and save the old value
			_ATL_MSG msg(pThis->m_hWnd, uMsg, wParam, lParam);
			const _ATL_MSG* pOldMsg = pT->m_pCurrentMsg;
			pT->m_pCurrentMsg = &msg;
			// pass to the message map to process
			//LRESULT lRes;
			BOOL bRet = pT->ProcessWindowMessage(hWndMyself, uMsg, wParam, lParam, lRes, 0);
			// restore saved value for the current message
			ATLASSERT(pT->m_pCurrentMsg == &msg);
			pT->m_pCurrentMsg = pOldMsg;
			// do the default processing if message was not handled
			if(!bRet)
			{
				if(uMsg != WM_NCDESTROY)
					lRes = pT->DefWindowProc(uMsg, wParam, lParam);
				else
				{
					// unsubclass, if needed
					LONG pfnWndProc = _pUIWnd2Manager->GetWindowLong(hWndMyself, GWL_WNDPROC);
					lRes = pT->DefWindowProc(uMsg, wParam, lParam);
					if(pT->m_pfnSuperWindowProc != UIWnd2Manager::DefWindowProc2 && _pUIWnd2Manager->GetWindowLong(pT->m_hWnd, GWL_WNDPROC) == pfnWndProc)
						_pUIWnd2Manager->SetWindowLong(pT->m_hWnd, GWL_WNDPROC, (LONG)pT->m_pfnSuperWindowProc);
					// clear out window handle
					HWND hWnd = hWndMyself;
					pT->m_hWnd = NULL;
					// clean up after window is destroyed
					pT->OnFinalMessage(hWnd);
				}
			}
#endif//

			if(uMsg != WM_NCDESTROY) {
				if(pT->AfterProcessWindowMessage(hWndMyself, uMsg, wParam, lParam, lResAfter, 0)) {
					return lResAfter;
				}
			}

		} else {
			lRes = Base::WindowProc(hWnd, uMsg, wParam, lParam);
		}

		return lRes;
	}

	LRESULT ForwardNotifications(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lResult = 0;
		switch(uMsg)
		{
		case WM_COMMAND:
		case WM_NOTIFY:
		case WM_PARENTNOTIFY:
		case WM_DRAWITEM:
		case WM_MEASUREITEM:
		case WM_COMPAREITEM:
		case WM_DELETEITEM:
		case WM_VKEYTOITEM:
		case WM_CHARTOITEM:
		case WM_HSCROLL:
		case WM_VSCROLL:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORDLG:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORMSGBOX:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
			lResult = SendMessage(GetParent(), uMsg, wParam, lParam);
			break;
		default:
			bHandled = FALSE;
			break;
		}
		return lResult;
	}

	LRESULT ReflectNotifications(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HWND hWndChild = NULL;

		switch(uMsg)
		{
		case WM_COMMAND:
			if(lParam != NULL)	// not from a menu
				hWndChild = (HWND)lParam;
			break;
		case WM_NOTIFY:
			hWndChild = ((LPNMHDR)lParam)->hwndFrom;
			break;
		case WM_PARENTNOTIFY:
			switch(LOWORD(wParam))
			{
			case WM_CREATE:
			case WM_DESTROY:
				hWndChild = (HWND)lParam;
				break;
			default:
				hWndChild = GetDlgItem(HIWORD(wParam));
				break;
			}
			break;
		case WM_DRAWITEM:
			if(wParam)	// not from a menu
				hWndChild = ((LPDRAWITEMSTRUCT)lParam)->hwndItem;
			break;
		case WM_MEASUREITEM:
			if(wParam)	// not from a menu
				hWndChild = GetDlgItem(((LPMEASUREITEMSTRUCT)lParam)->CtlID);
			break;
		case WM_COMPAREITEM:
			if(wParam)	// not from a menu
				hWndChild =  ((LPCOMPAREITEMSTRUCT)lParam)->hwndItem;
			break;
		case WM_DELETEITEM:
			if(wParam)	// not from a menu  
				hWndChild =  ((LPDELETEITEMSTRUCT)lParam)->hwndItem;

			break;
		case WM_VKEYTOITEM:
		case WM_CHARTOITEM:
		case WM_HSCROLL:
		case WM_VSCROLL:
			hWndChild = (HWND)lParam;
			break;
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORDLG:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORMSGBOX:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
			hWndChild = (HWND)lParam;
			break;
		default:
			break;
		}

		if(hWndChild == NULL)
		{
			bHandled = FALSE;
			return 1;
		}

		ATLASSERT(_pUIWnd2Manager->IsWindow(hWndChild));
		return SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
	}

	static BOOL DefaultReflectionHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		switch(uMsg)
		{
		case OCM_COMMAND:
		case OCM_NOTIFY:
		case OCM_PARENTNOTIFY:
		case OCM_DRAWITEM:
		case OCM_MEASUREITEM:
		case OCM_COMPAREITEM:
		case OCM_DELETEITEM:
		case OCM_VKEYTOITEM:
		case OCM_CHARTOITEM:
		case OCM_HSCROLL:
		case OCM_VSCROLL:
		case OCM_CTLCOLORBTN:
		case OCM_CTLCOLORDLG:
		case OCM_CTLCOLOREDIT:
		case OCM_CTLCOLORLISTBOX:
		case OCM_CTLCOLORMSGBOX:
		case OCM_CTLCOLORSCROLLBAR:
		case OCM_CTLCOLORSTATIC:
			if (_pUIWnd2Manager->IsDirectUI(hWnd)) {
				lResult = _pUIWnd2Manager->DefWindowProc2(hWnd, uMsg - OCM__BASE, wParam, lParam);
			} else {
				lResult = ::DefWindowProc(hWnd, uMsg - OCM__BASE, wParam, lParam);
			}
			return TRUE;
		default:
			break;
		}
		return FALSE;
	}

	BOOL DestroyWindow()
	{
		T* pT = static_cast<T*>(this);
		return _pUIWnd2Manager->DestroyWindow(*pT);
	}

	BOOL SubclassWindow(HWND hWnd)
	{
		T* pT = static_cast<T*>(this);
		if (_pUIWnd2Manager->IsDirectUI(hWnd)) {
			ATLASSERT(m_hWnd == NULL);
			m_thunk.Init(pT->GetWindowProc(), pT);
			WNDPROC pProc = (WNDPROC)&(m_thunk.thunk);
			WNDPROC pfnWndProc = (WNDPROC)_pUIWnd2Manager->SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
			if(pfnWndProc == NULL)
				return FALSE;
			m_pfnSuperWindowProc = pfnWndProc;
			m_hWnd = hWnd;
			return TRUE;
		} else {
			return Base::SubclassWindow(hWnd);
		}
	}
	
	// Use only if you want to subclass before window is destroyed,
	// WindowProc will automatically subclass when  window goes away
	HWND UnsubclassWindow(BOOL bForce = FALSE)
	{
		T* pT = static_cast<T*>(this);
		if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
			ATLASSERT(m_hWnd != NULL);
			WNDPROC pOurProc = (WNDPROC)&(m_thunk.thunk);
			WNDPROC pActiveProc = (WNDPROC)_pUIWnd2Manager->GetWindowLong(m_hWnd, GWL_WNDPROC);
			
			HWND hWnd = NULL;
			if (bForce || pOurProc == pActiveProc)
			{
				if(!_pUIWnd2Manager->SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_pfnSuperWindowProc))
					return NULL;
				
				m_pfnSuperWindowProc = UIWnd2Manager::DefWindowProc2;
				hWnd = m_hWnd;
				m_hWnd = NULL;
			}
			return hWnd;
		} else {
			return Base::UnsubclassWindow(bForce);
		}
	}

	LRESULT DefWindowProc()
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsDirectUI()) {
#if _MSC_VER<=1200
			const MSG* pMsg = m_pCurrentMsg;
#else
			const _ATL_MSG* pMsg = m_pCurrentMsg;
#endif//
			LRESULT lRes = 0;
			if (pMsg != NULL)
				lRes = DefWindowProc(pMsg->message, pMsg->wParam, pMsg->lParam);
			return lRes;
		} else {
			return Base::DefWindowProc();
		}
	}
	
	LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsDirectUI()) {
			return UIWnd2Manager::DefWindowProc2(m_hWnd, uMsg, wParam, lParam);
		} else {
			return Base::DefWindowProc(uMsg, wParam, lParam);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	BEGIN_BEFORE_MSG_MAP(This)
		MESSAGE_HANDLER(WM_NCCREATE, OnBeforeNcCreate)
		CHAIN_BEFORE_MSG_MAP(Wnd2Map)
		CHAIN_BEFORE_MSG_MAP(Base)
	END_BEFORE_MSG_MAP()
		
	LRESULT OnBeforeNcCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		if (_pUIWnd2Manager->IsDirectUI(*pT)) {
			_pUIWnd2Manager->AddWnd2(*pT);
		} else {
			_pUIWnd2Manager->AddWnd2(*pT, _pUIWnd2Manager->GethWndParent());
		}
		return 0L;
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(Wnd2Map)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	BEGIN_AFTER_MSG_MAP(This)
		CHAIN_AFTER_MSG_MAP(Wnd2Map)
		CHAIN_AFTER_MSG_MAP(Base)
	END_AFTER_MSG_MAP()

	virtual void OnFinalMessage(HWND hWnd)
	{
		T* pT = static_cast<T*>(this);
		//ATLASSERT(m_hWnd == hWnd); 这时候m_hWnd已经为空了
		BOOL bAutoDelete = _pUIWnd2Manager->IsAutoDelete(hWnd);
		_pUIWnd2Manager->RemoveWnd2(hWnd);
		if (bAutoDelete) {
			delete this;
		}
	}
};

//////////////////////////////////////////////////////////////////////////


template<class T>
class UIScrollWnd2Map
{
	typedef UIScrollWnd2Map<T> This;
protected:
	int m_nBarCapture;
public:
	UIScrollWnd2Map():m_nBarCapture(-1)
	{

	}

	BOOL CalcScrollBar(int nBar, LPSCROLLINFO lpScrollInfo, PSCROLLBARINFO pScrollBarInfo)
	{
		T* pT = static_cast<T*>(this);
		if(!lpScrollInfo || !pScrollBarInfo) {
			return FALSE;
		}

		SCROLLINFO& SInfo = *lpScrollInfo;
		SCROLLBARINFO& SBInfo = *pScrollBarInfo;

		CRect rcScrollBar;
		pT->GetClientRect(&rcScrollBar);
		SBInfo.rcScrollBar = rcScrollBar;

		HDC hdc = pT->GetDC();
		if(nBar==SB_VERT) {
			SBInfo.dxyLineButton = rcScrollBar.Width();
			pT->GetThemeMetric(hdc,SBP_ARROWBTN,ABS_UPNORMAL,TMT_HEIGHT,&SBInfo.dxyLineButton);
			int xyLineButton2 = rcScrollBar.Width();
			pT->GetThemeMetric(hdc,SBP_ARROWBTN,ABS_UPNORMAL,TMT_WIDTH,&xyLineButton2);
			SBInfo.rcScrollBar.left = SBInfo.rcScrollBar.right-xyLineButton2;
			rcScrollBar = SBInfo.rcScrollBar;
		} else {
			SBInfo.dxyLineButton = rcScrollBar.Height();
			pT->GetThemeMetric(hdc,SBP_ARROWBTN,ABS_LEFTNORMAL,TMT_WIDTH,&SBInfo.dxyLineButton);
			int xyLineButton2 = rcScrollBar.Height();
			pT->GetThemeMetric(hdc,SBP_ARROWBTN,ABS_LEFTNORMAL,TMT_HEIGHT,&xyLineButton2);
			SBInfo.rcScrollBar.top = SBInfo.rcScrollBar.bottom-xyLineButton2;
			rcScrollBar = SBInfo.rcScrollBar;
		}
		pT->ReleaseDC(hdc);
		
		int nMaxRange = SInfo.nMax-SInfo.nMin; //最大逻辑范围
		int nPos = SInfo.nPos-SInfo.nMin; //当前逻辑位置
		int nPage = SInfo.nPage; //一页逻辑范围
		
		int dxyTrackBar = (nBar==SB_VERT?rcScrollBar.Height():rcScrollBar.Width())-SBInfo.dxyLineButton-SBInfo.dxyLineButton;

		if (nMaxRange<=0 || nPage<=0 || dxyTrackBar<=0) {
			SBInfo.xyThumbTop = 0;
			SBInfo.xyThumbBottom = 0;
		} else {
			//校验数据
			if (nMaxRange%nPage) {
				SInfo.nMax = SInfo.nMin+(nMaxRange+nPage-1)/nPage*nPage;
				nMaxRange = SInfo.nMax-SInfo.nMin;
			}
			if(nPos>(SInfo.nMax-SInfo.nPage)) {
				SInfo.nPos = (SInfo.nMax-SInfo.nPage);
				nPos = SInfo.nPos;
			}
			//ASSERT(nMaxRange%nPage!=0);
			ASSERT(nPos<=(SInfo.nMax-SInfo.nPage));
			int nPageNum = nMaxRange/nPage; //一共多少页
			double dxyThumbButton = dxyTrackBar/nPageNum*1.;
			if (SInfo.nPos>=(SInfo.nMax-SInfo.nPage)) {
				SBInfo.xyThumbTop = SBInfo.dxyLineButton+dxyTrackBar-(int)dxyThumbButton;
				SBInfo.xyThumbBottom = SBInfo.xyThumbTop+(int)dxyThumbButton;
			} else {
				//拖动范围只有dxyTrackBar-dxyThumbButton，逻辑范围也是nMaxRange-nPage
				double dRangePerPixel = (nMaxRange-nPage)/(dxyTrackBar-dxyThumbButton)*1.;
				SBInfo.xyThumbTop = SBInfo.dxyLineButton+(int)(nPos/dRangePerPixel);
				SBInfo.xyThumbBottom = SBInfo.xyThumbTop+(int)dxyThumbButton;
			}
		}
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;

		LPCREATESTRUCT lpCreateStruct = (LPCREATESTRUCT)lParam;

		DWORD dwStyle = pT->GetStyle();
		if(dwStyle&WS_HSCROLL) {
			SCROLLINFO SInfo = {0};
			SCROLLBARINFO SBInfo = {0};
			if(pT->GetScrollInfo(SB_HORZ,&SInfo) && pT->GetScrollBarInfo(SB_HORZ,&SBInfo)) {
				pT->CalcScrollBar(SB_HORZ,&SInfo,&SBInfo);
				pT->SetScrollInfo(SB_HORZ,&SInfo);
				pT->SetScrollBarInfo(SB_HORZ,&SBInfo);
			}
		}
		if(dwStyle&WS_VSCROLL) {
			SCROLLINFO SInfo = {0};
			SCROLLBARINFO SBInfo = {0};
			if(pT->GetScrollInfo(SB_VERT,&SInfo) && pT->GetScrollBarInfo(SB_VERT,&SBInfo)) {
				pT->CalcScrollBar(SB_VERT,&SInfo,&SBInfo);
				pT->SetScrollInfo(SB_VERT,&SInfo);
				pT->SetScrollBarInfo(SB_VERT,&SBInfo);
			}
		}

		return bHandled;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		if (wParam != SIZE_MINIMIZED && lParam != 0) {
			DWORD dwStyle = pT->GetStyle();
			if(dwStyle&WS_HSCROLL) {
				SCROLLINFO SInfo = {0};
				SCROLLBARINFO SBInfo = {0};
				if(pT->GetScrollInfo(SB_HORZ,&SInfo) && pT->GetScrollBarInfo(SB_HORZ,&SBInfo)) {
					pT->CalcScrollBar(SB_HORZ,&SInfo,&SBInfo);
					pT->SetScrollInfo(SB_HORZ,&SInfo);
					pT->SetScrollBarInfo(SB_HORZ,&SBInfo);
				}
			}
			if(dwStyle&WS_VSCROLL) {
				SCROLLINFO SInfo = {0};
				SCROLLBARINFO SBInfo = {0};
				if(pT->GetScrollInfo(SB_VERT,&SInfo) && pT->GetScrollBarInfo(SB_VERT,&SBInfo)) {
					pT->CalcScrollBar(SB_VERT,&SInfo,&SBInfo);
					pT->SetScrollInfo(SB_VERT,&SInfo);
					pT->SetScrollBarInfo(SB_VERT,&SBInfo);
				}
			}
		}
		return bHandled;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);

		bHandled = FALSE;

		POINT pt;
		POINTSTOPOINT(pt, lParam); 

		int nBar = -1;
		SCROLLINFO SInfo = {0};
		SCROLLBARINFO SBInfo = {0};
		DWORD dwStyle = pT->GetStyle();
		if(dwStyle&WS_HSCROLL) {
			if(pT->GetScrollInfo(SB_HORZ,&SInfo) && pT->GetScrollBarInfo(SB_HORZ,&SBInfo)) {
				if (PtInRect(&SBInfo.rcScrollBar,pt)) {
					nBar = SB_HORZ;
				}
			}
		}
		if(dwStyle&WS_VSCROLL) {
			SCROLLINFO SInfo = {0};
			SCROLLBARINFO SBInfo = {0};
			if(pT->GetScrollInfo(SB_VERT,&SInfo) && pT->GetScrollBarInfo(SB_VERT,&SBInfo)) {
				if (PtInRect(&SBInfo.rcScrollBar,pt)) {
					nBar = SB_VERT;
				}
			}
		}

		if(nBar==-1) {
			return bHandled;
		}

		if (SInfo.nMin>=SInfo.nMax || SInfo.nPage<=0) {
			return bHandled;
		}
		if (SBInfo.xyThumbTop>=SBInfo.xyThumbBottom || SBInfo.dxyLineButton<=0) {
			return bHandled;
		}

		bHandled = TRUE;

		CRect rcScrollBar = SBInfo.rcScrollBar;

		int nSBCode = 0;
		int nPos = 0;
		if (nBar==SB_VERT) {
			if(pt.y<(rcScrollBar.top+SBInfo.dxyLineButton)) {
				nSBCode = SB_LINEUP;
				nPos = SInfo.nPos-1;
			} else if (pt.y>=(rcScrollBar.bottom-SBInfo.dxyLineButton)) {
				nSBCode = SB_LINEDOWN;
				nPos = SInfo.nPos+1;
			} else {
				RECT rcThumb = rcScrollBar;
				rcThumb.top = rcScrollBar.top+SBInfo.xyThumbTop;
				rcThumb.bottom = rcScrollBar.top+SBInfo.xyThumbBottom;
				if(pt.y<rcThumb.top) {
					nSBCode = SB_PAGEUP;
					nPos = SInfo.nPos-SInfo.nPage;
				} else if(pt.y>=rcThumb.bottom) {
					nSBCode = SB_PAGEDOWN;
					nPos = SInfo.nPos+SInfo.nPage;
				} else {
					nSBCode = SB_THUMBTRACK;
					nPos = SInfo.nPos;
					SInfo.nTrackPos =(pt.y-SBInfo.dxyLineButton)*(SInfo.nMax-SInfo.nMin)/(rcScrollBar.Height()-SBInfo.dxyLineButton-SBInfo.dxyLineButton);
					pT->SetCapture();
					m_nBarCapture = nBar;
				}
			}
			if (nPos<SInfo.nMin) {
				nPos = SInfo.nMin;
			} else if (nPos>(SInfo.nMax-SInfo.nPage)) {
				nPos = (SInfo.nMax-SInfo.nPage);
			}
			if (SInfo.nPos!=nPos) {
				SInfo.nPos = nPos;
				pT->SendMessage(WM_VSCROLL, (WPARAM)(MAKELONG(nSBCode,(WORD)nPos)),(LPARAM)(HWND)(*pT));
				pT->CalcScrollBar(nBar,&SInfo,&SBInfo);
				pT->SetScrollInfo(nBar,&SInfo);
				pT->SetScrollBarInfo(nBar,&SBInfo);
				pT->InvalidateRect(&rcScrollBar);
			}
		} else {
			if(pt.x<(rcScrollBar.left+SBInfo.dxyLineButton)) {
				nSBCode = SB_LINELEFT;
				nPos = SInfo.nPos-1;
			} else if (pt.x>=(rcScrollBar.right-SBInfo.dxyLineButton)) {
				nSBCode = SB_LINERIGHT;
				nPos = SInfo.nPos+1;
			} else {
				RECT rcThumb = rcScrollBar;
				rcThumb.left = rcScrollBar.left+SBInfo.xyThumbTop;
				rcThumb.right = rcScrollBar.left+SBInfo.xyThumbBottom;
				if(pt.x<rcThumb.left) {
					nSBCode = SB_PAGELEFT;
					nPos = SInfo.nPos-SInfo.nPage;
				} else if(pt.x>=rcThumb.right) {
					nSBCode = SB_PAGERIGHT;
					nPos = SInfo.nPos+SInfo.nPage;
				} else {
					nSBCode = SB_THUMBTRACK;
					nPos = SInfo.nPos;
					SInfo.nTrackPos = (pt.x-SBInfo.dxyLineButton)*(SInfo.nMax-SInfo.nMin)/(rcScrollBar.Width()-SBInfo.dxyLineButton-SBInfo.dxyLineButton);
					pT->SetCapture();
					m_nBarCapture = nBar;
				}
			}
			if (nPos<SInfo.nMin) {
				nPos = SInfo.nMin;
			} else if (nPos>(SInfo.nMax-SInfo.nPage)) {
				nPos = (SInfo.nMax-SInfo.nPage);
			}
			if (SInfo.nPos!=nPos) {
				SInfo.nPos = nPos;
				pT->SendMessage(WM_HSCROLL, (WPARAM)(MAKELONG(nSBCode,(WORD)nPos)),(LPARAM)(HWND)(*pT));
				pT->CalcScrollBar(nBar,&SInfo,&SBInfo);
				pT->SetScrollInfo(nBar,&SInfo);
				pT->SetScrollBarInfo(nBar,&SBInfo);
				pT->InvalidateRect(&rcScrollBar);
			}
		}
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(pT->GetCapture() == *pT && m_nBarCapture!=-1) {
			m_nBarCapture = -1;
			pT->ReleaseCapture();
		}
		return bHandled;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(pT->GetCapture() == *pT && m_nBarCapture!=-1) {
			POINT pt;
			POINTSTOPOINT(pt, lParam);

			int nBar = m_nBarCapture;
			SCROLLINFO SInfo = {0};
			SCROLLBARINFO SBInfo = {0};
			if(!pT->GetScrollInfo(nBar,&SInfo) || pT->GetScrollBarInfo(nBar,&SBInfo)) {
				return bHandled;
			}
			
			/*if (SInfo.nMin>=SInfo.nMax || SInfo.nPage<=0) {
				return bHandled;
			}
			if (SBInfo.xyThumbTop>=SBInfo.xyThumbBottom || SBInfo.dxyLineButton<=0) {
				return bHandled;
			}*/

			CRect rcScrollBar = SBInfo.rcScrollBar;

			int nSBCode = 0;
			int nPos = 0;
			int nPosOff = 0;
			if (nBar==SB_VERT) {	
				nSBCode = SB_THUMBTRACK;
				nPos = (pt.y-SBInfo.dxyLineButton)*(SInfo.nMax-SInfo.nMin)/(rcScrollBar.Height()-SBInfo.dxyLineButton-SBInfo.dxyLineButton);
				nPosOff = nPos-SInfo.nTrackPos;
				SInfo.nTrackPos = nPos;
				nPos = SInfo.nPos+nPosOff;

				if (nPos<SInfo.nMin) {
					nPos = SInfo.nMin;
				} else if (nPos>(SInfo.nMax-SInfo.nPage)) {
					nPos = (SInfo.nMax-SInfo.nPage);
				}
				if (SInfo.nPos!=nPos) {
					SInfo.nPos = nPos;
					pT->SendMessage(WM_VSCROLL, (WPARAM)(MAKELONG(nSBCode,(WORD)nPos)),(LPARAM)(HWND)(*pT));
					pT->CalcScrollBar(nBar,&SInfo,&SBInfo);
					pT->SetScrollInfo(nBar,&SInfo);
					pT->SetScrollBarInfo(nBar,&SBInfo);
					pT->InvalidateRect(&rcScrollBar);
				}
			} else {
				nSBCode = SB_THUMBTRACK;
				nPos = (pt.x-SBInfo.dxyLineButton)*(SInfo.nMax-SInfo.nMin)/(rcScrollBar.Width()-SBInfo.dxyLineButton-SBInfo.dxyLineButton);
				nPosOff = nPos-SInfo.nTrackPos;
				SInfo.nTrackPos = nPos;
				nPos = SInfo.nPos+nPosOff;

				if (nPos<SInfo.nMin) {
					nPos = SInfo.nMin;
				} else if (nPos>(SInfo.nMax-SInfo.nPage)) {
					nPos = (SInfo.nMax-SInfo.nPage);
				}
				if (SInfo.nPos!=nPos) {
					SInfo.nPos = nPos;
					pT->SendMessage(WM_HSCROLL, (WPARAM)(MAKELONG(nSBCode,(WORD)nPos)),(LPARAM)(HWND)(*pT));
					pT->CalcScrollBar(nBar,&SInfo,&SBInfo);
					pT->SetScrollInfo(nBar,&SInfo);
					pT->SetScrollBarInfo(nBar,&SBInfo);
					pT->InvalidateRect(&rcScrollBar);
				}
			}
		} else {
			bHandled = FALSE;
		}
		return bHandled;
	}

	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);

		bHandled = FALSE;

		return bHandled;
	}

	LRESULT OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);

		bHandled = FALSE;

		POINT pt;
		POINTSTOPOINT(pt, lParam); 

		int nBar = -1;
		SCROLLINFO SInfo = {0};
		SCROLLBARINFO SBInfo = {0};
		DWORD dwStyle = pT->GetStyle();
		if(dwStyle&WS_HSCROLL) {
			if(pT->GetScrollInfo(SB_HORZ,&SInfo) && pT->GetScrollBarInfo(SB_HORZ,&SBInfo)) {
				if (PtInRect(&SBInfo.rcScrollBar,pt)) {
					nBar = SB_HORZ;
				}
			}
		}
		if(dwStyle&WS_VSCROLL) {
			SCROLLINFO SInfo = {0};
			SCROLLBARINFO SBInfo = {0};
			if(pT->GetScrollInfo(SB_VERT,&SInfo) && pT->GetScrollBarInfo(SB_VERT,&SBInfo)) {
				if (PtInRect(&SBInfo.rcScrollBar,pt)) {
					nBar = SB_VERT;
				}
			}
		}

		if(nBar==-1) {
			return bHandled;
		}

		pT->InvalidateRect(&SBInfo.rcScrollBar);

		return bHandled;
	}

	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);

		bHandled = FALSE;

		POINT pt;
		POINTSTOPOINT(pt, lParam); 

		int nBar = -1;
		SCROLLINFO SInfo = {0};
		SCROLLBARINFO SBInfo = {0};
		DWORD dwStyle = pT->GetStyle();
		if(dwStyle&WS_HSCROLL) {
			if(pT->GetScrollInfo(SB_HORZ,&SInfo) && pT->GetScrollBarInfo(SB_HORZ,&SBInfo)) {
				pT->InvalidateRect(&SBInfo.rcScrollBar);
			}
		}
		if(dwStyle&WS_VSCROLL) {
			SCROLLINFO SInfo = {0};
			SCROLLBARINFO SBInfo = {0};
			if(pT->GetScrollInfo(SB_VERT,&SInfo) && pT->GetScrollBarInfo(SB_VERT,&SBInfo)) {
				pT->InvalidateRect(&SBInfo.rcScrollBar);
			}
		}

		if(nBar==-1) {
			return bHandled;
		}

		bHandled = TRUE;

		return bHandled;
	}
};

template <class T>
class UIScroll2Impl : public CScrollImpl<T>
{
	typedef UIScroll2Impl<T> This;
	typedef CScrollImpl<T> Base;
public:
	// Constructor
	UIScroll2Impl():Base()
	{
		
	}

	// offset operations
	void SetScrollOffset(int x, int y, BOOL bRedraw = TRUE)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());

		pT->AdjustScrollOffset(x, y);

		int dx = m_ptOffset.x - x;
		int dy = m_ptOffset.y - y;
		m_ptOffset.x = x;
		m_ptOffset.y = y;

		// block: set horizontal scroll bar
		{
			SCROLLINFO si = { sizeof(SCROLLINFO) };
			si.fMask = SIF_POS;
			if((m_dwExtendedStyle & SCRL_DISABLENOSCROLLH) != 0)
				si.fMask |= SIF_DISABLENOSCROLL;
			si.nPos = m_ptOffset.x;
			pT->SetScrollInfo(SB_HORZ, &si, bRedraw);
		}

		// block: set vertical scroll bar
		{
			SCROLLINFO si = { sizeof(SCROLLINFO) };
			si.fMask = SIF_POS;
			if((m_dwExtendedStyle & SCRL_DISABLENOSCROLLV) != 0)
				si.fMask |= SIF_DISABLENOSCROLL;
			si.nPos = m_ptOffset.y;
			pT->SetScrollInfo(SB_VERT, &si, bRedraw);
		}

		// Move all children if needed
		if(IsScrollingChildren() && (dx != 0 || dy != 0))
		{
			for(HWND hWndChild = pT->GetWindow(pT->m_hWnd, GW_CHILD); hWndChild != NULL; hWndChild = pT->GetWindow(hWndChild, GW_HWNDNEXT))
			{
				RECT rect = { 0 };
				_pUIWnd2Manager->GetWindowRect(hWndChild, &rect);
				_pUIWnd2Manager->MapWindowPoints(NULL, pT->m_hWnd, (LPPOINT)&rect, 1);
				_pUIWnd2Manager->SetWindowPos(hWndChild, NULL, rect.left + dx, rect.top + dy, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
			}
		}

		if(bRedraw)
			pT->Invalidate();
	}

	// size operations
	void SetScrollSize(int cx, int cy, BOOL bRedraw = TRUE, bool bResetOffset = true)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());

		m_sizeAll.cx = cx;
		m_sizeAll.cy = cy;

		int x = 0;
		int y = 0;
		if(!bResetOffset)
		{
			x = m_ptOffset.x;
			y = m_ptOffset.y;
			pT->AdjustScrollOffset(x, y);
		}

		int dx = m_ptOffset.x - x;
		int dy = m_ptOffset.y - y;
		m_ptOffset.x = x;
		m_ptOffset.y = y;

		// block: set horizontal scroll bar
		{
			SCROLLINFO si = { sizeof(SCROLLINFO) };
			si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
			if((m_dwExtendedStyle & SCRL_DISABLENOSCROLLH) != 0)
				si.fMask |= SIF_DISABLENOSCROLL;
			si.nMin = 0;
			si.nMax = m_sizeAll.cx - 1;
			si.nPage = m_sizeClient.cx;
			si.nPos = m_ptOffset.x;
			pT->SetScrollInfo(SB_HORZ, &si, bRedraw);
		}

		// block: set vertical scroll bar
		{
			SCROLLINFO si = { sizeof(SCROLLINFO) };
			si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
			if((m_dwExtendedStyle & SCRL_DISABLENOSCROLLV) != 0)
				si.fMask |= SIF_DISABLENOSCROLL;
			si.nMin = 0;
			si.nMax = m_sizeAll.cy - 1;
			si.nPage = m_sizeClient.cy;
			si.nPos = m_ptOffset.y;
			pT->SetScrollInfo(SB_VERT, &si, bRedraw);
		}

		// Move all children if needed
		if(IsScrollingChildren() && (dx != 0 || dy != 0))
		{
			for(HWND hWndChild = pT->GetWindow(pT->m_hWnd, GW_CHILD); hWndChild != NULL; hWndChild = pT->GetWindow(hWndChild, GW_HWNDNEXT))
			{
				RECT rect = { 0 };
				_pUIWnd2Manager->GetWindowRect(hWndChild, &rect);
				_pUIWnd2Manager->MapWindowPoints(hWndChild, pT->m_hWnd, (LPPOINT)&rect, 1);
				_pUIWnd2Manager->SetWindowPos(hWndChild, NULL, rect.left + dx, rect.top + dy, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
			}
		}

		SetScrollLine(0, 0);
		SetScrollPage(0, 0);

		if(bRedraw)
			pT->Invalidate();
	}

	// commands
	void ScrollLineDown()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_VERT, SB_LINEDOWN, (int&)m_ptOffset.y, m_sizeAll.cy, m_sizePage.cy, m_sizeLine.cy);
	}

	void ScrollLineUp()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_VERT, SB_LINEUP, (int&)m_ptOffset.y, m_sizeAll.cy, m_sizePage.cy, m_sizeLine.cy);
	}

	void ScrollPageDown()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_VERT, SB_PAGEDOWN, (int&)m_ptOffset.y, m_sizeAll.cy, m_sizePage.cy, m_sizeLine.cy);
	}

	void ScrollPageUp()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_VERT, SB_PAGEUP, (int&)m_ptOffset.y, m_sizeAll.cy, m_sizePage.cy, m_sizeLine.cy);
	}

	void ScrollTop()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_VERT, SB_TOP, (int&)m_ptOffset.y, m_sizeAll.cy, m_sizePage.cy, m_sizeLine.cy);
	}

	void ScrollBottom()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_VERT, SB_BOTTOM, (int&)m_ptOffset.y, m_sizeAll.cy, m_sizePage.cy, m_sizeLine.cy);
	}

	void ScrollLineRight()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_HORZ, SB_LINEDOWN, (int&)m_ptOffset.x, m_sizeAll.cx, m_sizePage.cx, m_sizeLine.cx);
	}

	void ScrollLineLeft()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_HORZ, SB_LINEUP, (int&)m_ptOffset.x, m_sizeAll.cx, m_sizePage.cx, m_sizeLine.cx);
	}

	void ScrollPageRight()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_HORZ, SB_PAGEDOWN, (int&)m_ptOffset.x, m_sizeAll.cx, m_sizePage.cx, m_sizeLine.cx);
	}

	void ScrollPageLeft()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_HORZ, SB_PAGEUP, (int&)m_ptOffset.x, m_sizeAll.cx, m_sizePage.cx, m_sizeLine.cx);
	}

	void ScrollAllLeft()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_HORZ, SB_TOP, (int&)m_ptOffset.x, m_sizeAll.cx, m_sizePage.cx, m_sizeLine.cx);
	}

	void ScrollAllRight()
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_HORZ, SB_BOTTOM, (int&)m_ptOffset.x, m_sizeAll.cx, m_sizePage.cx, m_sizeLine.cx);
	}

	// scroll to make point/view/window visible
	void ScrollToView(POINT pt)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		RECT rect = { pt.x, pt.y, pt.x, pt.y };
		pT->ScrollToView(rect);
	}

	void ScrollToView(RECT& rect)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());

		RECT rcClient = { 0 };
		pT->GetClientRect(&rcClient);

		int x = m_ptOffset.x;
		if(rect.left < m_ptOffset.x)
			x = rect.left;
		else if(rect.right > (m_ptOffset.x + rcClient.right))
			x = rect.right - rcClient.right;

		int y = m_ptOffset.y;
		if(rect.top < m_ptOffset.y)
			y = rect.top;
		else if(rect.bottom > (m_ptOffset.y + rcClient.bottom))
			y = rect.bottom - rcClient.bottom;

		SetScrollOffset(x, y);
	}

	void ScrollToView(HWND hWnd)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());

		RECT rect = { 0 };
		_pUIWnd2Manager->GetWindowRect(hWnd, &rect);
		_pUIWnd2Manager->MapWindowPoints(NULL, pT->m_hWnd, (LPPOINT)&rect, 2);
		ScrollToView(rect);
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
		MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
#if !((_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)) && !defined(_WIN32_WCE)
		MESSAGE_HANDLER(m_uMsgMouseWheel, OnMouseWheel)
#endif // !((_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)) && !defined(_WIN32_WCE)
		MESSAGE_HANDLER(WM_MOUSEHWHEEL, OnMouseHWheel)
		MESSAGE_HANDLER(WM_SETTINGCHANGE, OnSettingChange)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
#endif // !_WIN32_WCE
		// standard scroll commands
		ALT_MSG_MAP(1)
		COMMAND_ID_HANDLER(ID_SCROLL_UP, OnScrollUp)
		COMMAND_ID_HANDLER(ID_SCROLL_DOWN, OnScrollDown)
		COMMAND_ID_HANDLER(ID_SCROLL_PAGE_UP, OnScrollPageUp)
		COMMAND_ID_HANDLER(ID_SCROLL_PAGE_DOWN, OnScrollPageDown)
		COMMAND_ID_HANDLER(ID_SCROLL_TOP, OnScrollTop)
		COMMAND_ID_HANDLER(ID_SCROLL_BOTTOM, OnScrollBottom)
		COMMAND_ID_HANDLER(ID_SCROLL_LEFT, OnScrollLeft)
		COMMAND_ID_HANDLER(ID_SCROLL_RIGHT, OnScrollRight)
		COMMAND_ID_HANDLER(ID_SCROLL_PAGE_LEFT, OnScrollPageLeft)
		COMMAND_ID_HANDLER(ID_SCROLL_PAGE_RIGHT, OnScrollPageRight)
		COMMAND_ID_HANDLER(ID_SCROLL_ALL_LEFT, OnScrollAllLeft)
		COMMAND_ID_HANDLER(ID_SCROLL_ALL_RIGHT, OnScrollAllRight)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		GetSystemSettings();
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnVScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_VERT, (int)(short)LOWORD(wParam), (int&)m_ptOffset.y, m_sizeAll.cy, m_sizePage.cy, m_sizeLine.cy);
		return 0;
	}

	LRESULT OnHScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		pT->DoScroll(SB_HORZ, (int)(short)LOWORD(wParam), (int&)m_ptOffset.x, m_sizeAll.cx, m_sizePage.cx, m_sizeLine.cx);
		return 0;
	}

	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());

#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400) || defined(_WIN32_WCE)
		uMsg;
		int zDelta = (int)GET_WHEEL_DELTA_WPARAM(wParam);
#else
		int zDelta = (uMsg == WM_MOUSEWHEEL) ? (int)GET_WHEEL_DELTA_WPARAM(wParam) : (int)wParam;
#endif // !((_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400) || defined(_WIN32_WCE))
		int nScrollCode = (m_nWheelLines == WHEEL_PAGESCROLL) ? ((zDelta > 0) ? SB_PAGEUP : SB_PAGEDOWN) : ((zDelta > 0) ? SB_LINEUP : SB_LINEDOWN);
		m_zDelta += zDelta;   // cumulative
		int zTotal = (m_nWheelLines == WHEEL_PAGESCROLL) ? abs(m_zDelta) : abs(m_zDelta) * m_nWheelLines;
		if(m_sizeAll.cy > m_sizeClient.cy)
		{
			for(int i = 0; i < zTotal; i += WHEEL_DELTA)
			{
				pT->DoScroll(SB_VERT, nScrollCode, (int&)m_ptOffset.y, m_sizeAll.cy, m_sizePage.cy, m_sizeLine.cy);
				pT->UpdateWindow();
			}
		}
		else		// can't scroll vertically, scroll horizontally
		{
			for(int i = 0; i < zTotal; i += WHEEL_DELTA)
			{
				pT->DoScroll(SB_HORZ, nScrollCode, (int&)m_ptOffset.x, m_sizeAll.cx, m_sizePage.cx, m_sizeLine.cx);
				pT->UpdateWindow();
			}
		}
		m_zDelta %= WHEEL_DELTA;

		return 0;
	}

	LRESULT OnMouseHWheel(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());

		int zDelta = (int)GET_WHEEL_DELTA_WPARAM(wParam);
		int nScrollCode = (m_nHWheelChars == WHEEL_PAGESCROLL) ? ((zDelta > 0) ? SB_PAGERIGHT : SB_PAGELEFT) : ((zDelta > 0) ? SB_LINERIGHT : SB_LINELEFT);
		m_zHDelta += zDelta;   // cumulative
		int zTotal = (m_nHWheelChars == WHEEL_PAGESCROLL) ? abs(m_zHDelta) : abs(m_zHDelta) * m_nHWheelChars;
		if(m_sizeAll.cx > m_sizeClient.cx)
		{
			for(int i = 0; i < zTotal; i += WHEEL_DELTA)
			{
				pT->DoScroll(SB_HORZ, nScrollCode, (int&)m_ptOffset.x, m_sizeAll.cx, m_sizePage.cx, m_sizeLine.cx);
				pT->UpdateWindow();
			}
		}
		m_zHDelta %= WHEEL_DELTA;

		return 0;
	}

	LRESULT OnSettingChange(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		GetSystemSettings();
		return 0;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());

		m_sizeClient.cx = GET_X_LPARAM(lParam);
		m_sizeClient.cy = GET_Y_LPARAM(lParam);

		// block: set horizontal scroll bar
		{
			SCROLLINFO si = { sizeof(SCROLLINFO) };
			si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
			si.nMin = 0;
			si.nMax = m_sizeAll.cx - 1;
			if((m_dwExtendedStyle & SCRL_DISABLENOSCROLLH) != 0)
				si.fMask |= SIF_DISABLENOSCROLL;
			si.nPage = m_sizeClient.cx;
			si.nPos = m_ptOffset.x;
			pT->SetScrollInfo(SB_HORZ, &si, TRUE);
		}

		// block: set vertical scroll bar
		{
			SCROLLINFO si = { sizeof(SCROLLINFO) };
			si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
			si.nMin = 0;
			si.nMax = m_sizeAll.cy - 1;
			if((m_dwExtendedStyle & SCRL_DISABLENOSCROLLV) != 0)
				si.fMask |= SIF_DISABLENOSCROLL;
			si.nPage = m_sizeClient.cy;
			si.nPos = m_ptOffset.y;
			pT->SetScrollInfo(SB_VERT, &si, TRUE);
		}

		int x = m_ptOffset.x;
		int y = m_ptOffset.y;
		if(pT->AdjustScrollOffset(x, y))
		{
			// Children will be moved in SetScrollOffset, if needed
			pT->ScrollWindowEx(m_ptOffset.x - x, m_ptOffset.y - y, (m_uScrollFlags & ~SCRL_SCROLLCHILDREN));
			SetScrollOffset(x, y, FALSE);
		}

		bHandled = FALSE;
		return 1;
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(pT->IsWindow());
		if(wParam != NULL)
		{
			CDCHandle dc = (HDC)wParam;
			POINT ptViewportOrg = { 0, 0 };
			dc.SetViewportOrg(-m_ptOffset.x, -m_ptOffset.y, &ptViewportOrg);
			pT->DoPaint(dc);
			dc.SetViewportOrg(ptViewportOrg);
		}
		else
		{
			CPaintDC dc(pT->m_hWnd);
			dc.SetViewportOrg(-m_ptOffset.x, -m_ptOffset.y);
			pT->DoPaint(dc.m_hDC);
		}
		return 0;
	}

	// scrolling handlers
	LRESULT OnScrollUp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollLineUp();
		return 0;
	}

	LRESULT OnScrollDown(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollLineDown();
		return 0;
	}

	LRESULT OnScrollPageUp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollPageUp();
		return 0;
	}

	LRESULT OnScrollPageDown(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollPageDown();
		return 0;
	}

	LRESULT OnScrollTop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollTop();
		return 0;
	}

	LRESULT OnScrollBottom(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollBottom();
		return 0;
	}

	LRESULT OnScrollLeft(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollLineLeft();
		return 0;
	}

	LRESULT OnScrollRight(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollLineRight();
		return 0;
	}

	LRESULT OnScrollPageLeft(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollPageLeft();
		return 0;
	}

	LRESULT OnScrollPageRight(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollPageRight();
		return 0;
	}

	LRESULT OnScrollAllLeft(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollAllLeft();
		return 0;
	}

	LRESULT OnScrollAllRight(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ScrollAllRight();
		return 0;
	}

	// Overrideables
	void DoPaint(CDCHandle /*dc*/)
	{
		// must be implemented in a derived class
		ATLASSERT(FALSE);
	}

	// Implementation
	void DoScroll(int nType, int nScrollCode, int& cxyOffset, int cxySizeAll, int cxySizePage, int cxySizeLine)
	{
		T* pT = static_cast<T*>(this);
		RECT rect = { 0 };
		pT->GetClientRect(&rect);
		int cxyClient = (nType == SB_VERT) ? rect.bottom : rect.right;
		int cxyMax = cxySizeAll - cxyClient;

		if(cxyMax < 0)   // can't scroll, client area is bigger
			return;

		bool bUpdate = true;
		int cxyScroll = 0;

		switch(nScrollCode)
		{
		case SB_TOP:		// top or all left
			cxyScroll = cxyOffset;
			cxyOffset = 0;
			break;
		case SB_BOTTOM:		// bottom or all right
			cxyScroll = cxyOffset - cxyMax;
			cxyOffset = cxyMax;
			break;
		case SB_LINEUP:		// line up or line left
			if(cxyOffset >= cxySizeLine)
			{
				cxyScroll = cxySizeLine;
				cxyOffset -= cxySizeLine;
			}
			else
			{
				cxyScroll = cxyOffset;
				cxyOffset = 0;
			}
			break;
		case SB_LINEDOWN:	// line down or line right
			if(cxyOffset < cxyMax - cxySizeLine)
			{
				cxyScroll = -cxySizeLine;
				cxyOffset += cxySizeLine;
			}
			else
			{
				cxyScroll = cxyOffset - cxyMax;
				cxyOffset = cxyMax;
			}
			break;
		case SB_PAGEUP:		// page up or page left
			if(cxyOffset >= cxySizePage)
			{
				cxyScroll = cxySizePage;
				cxyOffset -= cxySizePage;
			}
			else
			{
				cxyScroll = cxyOffset;
				cxyOffset = 0;
			}
			break;
		case SB_PAGEDOWN:	// page down or page right
			if(cxyOffset < cxyMax - cxySizePage)
			{
				cxyScroll = -cxySizePage;
				cxyOffset += cxySizePage;
			}
			else
			{
				cxyScroll = cxyOffset - cxyMax;
				cxyOffset = cxyMax;
			}
			break;
		case SB_THUMBTRACK:
			if(IsNoThumbTracking())
				break;
			// else fall through
		case SB_THUMBPOSITION:
			{
				SCROLLINFO si = { sizeof(SCROLLINFO), SIF_TRACKPOS };
				if(pT->GetScrollInfo(nType, &si))
				{
					cxyScroll = cxyOffset - si.nTrackPos;
					cxyOffset = si.nTrackPos;
				}
			}
			break;
		case SB_ENDSCROLL:
		default:
			bUpdate = false;
			break;
		}

		if(bUpdate && cxyScroll != 0)
		{
			pT->SetScrollPos(nType, cxyOffset, TRUE);
			if(nType == SB_VERT)
				pT->ScrollWindowEx(0, cxyScroll, m_uScrollFlags);
			else
				pT->ScrollWindowEx(cxyScroll, 0, m_uScrollFlags);
		}
	}

	void GetSystemSettings()
	{
		T* pT = static_cast<T*>(this);
#ifndef _WIN32_WCE
#ifndef SPI_GETWHEELSCROLLLINES
		const UINT SPI_GETWHEELSCROLLLINES = 104;
#endif // !SPI_GETWHEELSCROLLLINES
		::SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &m_nWheelLines, 0);

#ifndef SPI_GETWHEELSCROLLCHARS
		const UINT SPI_GETWHEELSCROLLCHARS = 0x006C;
#endif // !SPI_GETWHEELSCROLLCHARS
		::SystemParametersInfo(SPI_GETWHEELSCROLLCHARS, 0, &m_nHWheelChars, 0);

#if !((_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400))
		if(m_uMsgMouseWheel != 0)
			m_uMsgMouseWheel = ::RegisterWindowMessage(MSH_MOUSEWHEEL);

		HWND hWndWheel = FindWindow(MSH_WHEELMODULE_CLASS, MSH_WHEELMODULE_TITLE);
		if(pT->IsWindow(hWndWheel))
		{
			UINT uMsgScrollLines = ::RegisterWindowMessage(MSH_SCROLL_LINES);
			if(uMsgScrollLines != 0)
				m_nWheelLines = (int)::SendMessage(hWndWheel, uMsgScrollLines, 0, 0L);
		}
#endif // !((_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400))
#endif // !_WIN32_WCE
	}
};


template <class T, class TBase = UIWnd2>
class UIScrollWnd2Impl 
	: public UIWnd2Impl<T,TBase>
	, public UIScroll2Impl<T>
{
	typedef UIScrollWnd2Impl<T,TBase> This;
	typedef UIWnd2Impl<T,TBase> Base;
	typedef UIScroll2Impl<T> ScrollMap;
public:
	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_VSCROLL, UIScroll2Impl< T >::OnVScroll)
		MESSAGE_HANDLER(WM_HSCROLL, UIScroll2Impl< T >::OnHScroll)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, UIScroll2Impl< T >::OnMouseWheel)
#if !((_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)) && !defined(_WIN32_WCE)
		MESSAGE_HANDLER(m_uMsgMouseWheel, UIScroll2Impl< T >::OnMouseWheel)
#endif // !((_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)) && !defined(_WIN32_WCE)
		MESSAGE_HANDLER(WM_MOUSEHWHEEL, UIScroll2Impl< T >::OnMouseHWheel)
		MESSAGE_HANDLER(WM_SETTINGCHANGE, UIScroll2Impl< T >::OnSettingChange)
		MESSAGE_HANDLER(WM_SIZE, UIScroll2Impl< T >::OnSize)
		MESSAGE_HANDLER(WM_PAINT, UIScroll2Impl< T >::OnPaint)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(WM_PRINTCLIENT, UIScroll2Impl< T >::OnPaint)
#endif // !_WIN32_WCE
		CHAIN_MSG_MAP(Base)
	ALT_MSG_MAP(1)
		COMMAND_ID_HANDLER(ID_SCROLL_UP, UIScroll2Impl< T >::OnScrollUp)
		COMMAND_ID_HANDLER(ID_SCROLL_DOWN, UIScroll2Impl< T >::OnScrollDown)
		COMMAND_ID_HANDLER(ID_SCROLL_PAGE_UP, UIScroll2Impl< T >::OnScrollPageUp)
		COMMAND_ID_HANDLER(ID_SCROLL_PAGE_DOWN, UIScroll2Impl< T >::OnScrollPageDown)
		COMMAND_ID_HANDLER(ID_SCROLL_TOP, UIScroll2Impl< T >::OnScrollTop)
		COMMAND_ID_HANDLER(ID_SCROLL_BOTTOM, UIScroll2Impl< T >::OnScrollBottom)
		COMMAND_ID_HANDLER(ID_SCROLL_LEFT, UIScroll2Impl< T >::OnScrollLeft)
		COMMAND_ID_HANDLER(ID_SCROLL_RIGHT, UIScroll2Impl< T >::OnScrollRight)
		COMMAND_ID_HANDLER(ID_SCROLL_PAGE_LEFT, UIScroll2Impl< T >::OnScrollPageLeft)
		COMMAND_ID_HANDLER(ID_SCROLL_PAGE_RIGHT, UIScroll2Impl< T >::OnScrollPageRight)
		COMMAND_ID_HANDLER(ID_SCROLL_ALL_LEFT, UIScroll2Impl< T >::OnScrollAllLeft)
		COMMAND_ID_HANDLER(ID_SCROLL_ALL_RIGHT, UIScroll2Impl< T >::OnScrollAllRight)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

template <class T, class TBase = UIWnd2>
class UIDialog2Impl 
: public UIDialogImpl<T, TBase>
, public UIWnd2Map<T, TBase>
{
	typedef UIDialog2Impl<T, TBase> This;
	typedef UIDialogImpl<T, TBase> Base;
	typedef UIWnd2Map<T, TBase> FuncMap;
public:
	//UIDialog2Impl()

	BOOL SetAutoDelete(BOOL bDelete = TRUE)
	{
		T* pT = static_cast<T*>(this);
		return _pUIWnd2Manager->SetAutoDelete(*pT, bDelete);
	}

	// modal dialogs
	INT_PTR DoModal(HWND hWndParent = ::GetActiveWindow(), LPARAM dwInitParam = NULL)
	{
		ATLASSERT(m_hWnd == NULL);
		_pUIWnd2Manager->SethWndParent(hWndParent);
		return Base::DoModal(_pUIWnd2Manager->GetSafeHwnd(hWndParent), dwInitParam);
	}
	// modeless dialogs
	HWND Create(HWND hWndParent, LPARAM dwInitParam = NULL)
	{
		ATLASSERT(m_hWnd == NULL);
		_pUIWnd2Manager->SethWndParent(hWndParent);
		return Base::Create(_pUIWnd2Manager->GetSafeHwnd(hWndParent), dwInitParam);
	}
	// for CComControl
	HWND Create(HWND hWndParent, RECT&, LPARAM dwInitParam = NULL)
	{
		return Create(hWndParent, dwInitParam);
	}

	BOOL EndDialog(int nRetCode)
	{
		T* pT = static_cast<T*>(this);
		return _pUIWnd2Manager->EndDialog(*pT, nRetCode);
	}

	BOOL DestroyWindow()
	{
		T* pT = static_cast<T*>(this);
		return _pUIWnd2Manager->DestroyWindow(*pT);
	}

	//Before Handle WM_INITDIALOG function.
	BOOL PreInitDialog(LPARAM lParam)
	{
		return TRUE;
	}

#if _MSC_VER<=1200
	WNDPROC GetDialogProc()
#else
	DLGPROC GetDialogProc()
#endif//
	{
		return DialogProc;
	}

#if _MSC_VER<=1200
	static LRESULT CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
#else
	static INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
#endif//
	{
		LRESULT lResBefore = 0, lRes = 0, lResAfter = 0;
		This* pThis = (This*)hWnd;
		ATLASSERT(pThis);
		T* pT = static_cast<T*>(pThis);
		ATLASSERT(pT);
		
		//HWND hWndParent = pThis->m_hWndParent;
		HWND hWndMyself = pT->m_hWnd;
		
		if(pT->BeforeProcessWindowMessage(hWndMyself, uMsg, wParam, lParam, lResBefore, 0)) {
			return lResBefore;
		}

		lRes = Base::DialogProc(hWnd, uMsg, wParam, lParam);

		if(uMsg != WM_NCDESTROY) {
			if(pT->AfterProcessWindowMessage(hWndMyself, uMsg, wParam, lParam, lResAfter, 0)) {
				return lResAfter;
			}
		}

		return lRes;
	}

	BEGIN_BEFORE_MSG_MAP(This)
		MESSAGE_HANDLER(WM_INITDIALOG, OnBeforeInitDialog)
		CHAIN_BEFORE_MSG_MAP(FuncMap)
	END_BEFORE_MSG_MAP()

	LRESULT OnBeforeInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (_pUIWnd2Manager->IsDirectUI(*pT)) {
			ATLASSERT(0);
			_pUIWnd2Manager->AddWnd2(*pT);
		} else {
			_pUIWnd2Manager->AddWnd2(*pT, _pUIWnd2Manager->GethWndParent());
		}
		pT->SetWindowLongPtr(GWLP_USERDATA, reinterpret_cast<LONG>(pT));
		if(!pT->PreInitDialog(lParam)) {
			pT->DefWindowProc();
			pT->OnCancel();
			return FALSE;
		}
		/*SIZE sz;
		pT->GetClientSize(&sz);
		pT->PostMessage(WM_SIZE, SIZE_RESTORED, MAKELPARAM(sz.cx,sz.cy));*/
		bHandled = FALSE;
		return 0L;
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
		
	virtual void OnFinalMessage(HWND hWnd)
	{
		T* pT = static_cast<T*>(this);
		//ATLASSERT(m_hWnd == hWnd); 这时候m_hWnd已经为空了
		BOOL bAutoDelete = _pUIWnd2Manager->IsAutoDelete(hWnd);
		_pUIWnd2Manager->RemoveWnd2(hWnd);
		if (bAutoDelete) {
			delete this;
		}
	}
};

/*
template<class T>
class UIPreTranslateMessage2Map : public UIPreTranslateMessageMap
{
	typedef UIPreTranslateMessage2Map<T> This;
	typedef UIPreTranslateMessageMap<T> Base;
public:
	UIPreTranslateMessage2Map()
	{
	}

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}
};*/
/*
template<class T>
class UIPaint2 : public UIPaint<T>
{
	typedef UIPaint2<T> This;
	typedef UIPaint<T> Base;
public:
	BOOL OnEraseBkgnd(HDC hdc)
	{
		return TRUE;
	}

	void Paint(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		pT->DefWindowProc(pT->GetCurrentMessage()->message, (WPARAM)hdc, (LPARAM)0L);
	}

	void OnPaint(HDC hdc)
	{
		Base::OnPaint(hdc);
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
		//CHAIN_MSG_MAP(Base) //这里不要调用基类处理
	END_MSG_MAP()

	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = pT->OnEraseBkgnd((HDC)wParam);
		return TRUE;
	}

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		HDC hdc = (HDC)wParam;
		if (hdc) {
			pT->OnPaint(hdc);
		} else {
			PAINTSTRUCT PaintS = {0};
			hdc = pT->BeginPaint(&PaintS);
			pT->OnPaint(hdc);
			pT->EndPaint(&PaintS);
		}
		return bHandled;
	}
};*/

#endif//_H_UIWND2_H_