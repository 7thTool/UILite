// WTLVC6View.h : interface of the CWTLVC6View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WTLVC6VIEW_H__E8EC6096_84ED_43B5_9A54_D51BF1EABEB7__INCLUDED_)
#define AFX_WTLVC6VIEW_H__E8EC6096_84ED_43B5_9A54_D51BF1EABEB7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWTLVC6View : public CWindowImpl<CWTLVC6View, CAxWindow>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, CAxWindow::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CWTLVC6View)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WTLVC6VIEW_H__E8EC6096_84ED_43B5_9A54_D51BF1EABEB7__INCLUDED_)
