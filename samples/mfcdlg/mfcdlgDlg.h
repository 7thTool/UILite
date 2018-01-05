
// mfcdlgDlg.h : header file
//

#pragma once

#include <XLib/UIXPane.h>
#include <XLib/UXWnd.h>


// CmfcdlgDlg dialog
class CmfcdlgDlg 
	: public UXDialogImpl<CmfcdlgDlg>
	, public UIEnableMove<CmfcdlgDlg>
	, public UIRoundRectHelper<CmfcdlgDlg>
{
	typedef CmfcdlgDlg This;
	typedef UXDialogImpl<CmfcdlgDlg> Base;
	DECLARE_XMLWND_CLASS(_T("mfcdlg"))
// Construction
public:
	CmfcdlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCDLG_DIALOG };

	class PaneInfo : public UIBkgnd<PaneInfo>
	{
	public:
		PaneInfo()
		{
			SetBkColor(RGB(rand()%255,rand()%255,rand()%255));
		}
	};
	typedef std::map<Pane*,PaneInfo> PaneInfos;
	PaneInfos m_pPInfos;

	//UIButton m_btnOk;
	//UIProgressBarCtrl m_wndProgressBar;

	std::vector<CString> m_strClassNames;

	void AddClassName(LPCTSTR lpszClassName);

	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(Base)
		CHAIN_XML_CONTROL_AFTER_MAP(This)
	END_XML_CONTROL_MAP()

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	BEGIN_MSG_MAP(CmfcdlgDlg)
		CHAIN_MSG_MAP(UIRoundRectHelper<CmfcdlgDlg>)
		CHAIN_MSG_MAP(UIEnableMove<CmfcdlgDlg>)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	void PaintP(Pane* pP, HDC hdc)
	{
		PaneInfo& PInfo = m_pPInfos[pP];

		WTL::CDCHandle dc(hdc);
		RECT rcP;
		pP->GetRect(&rcP);
		PInfo.PaintBkgnd(hdc,&rcP);

		int nOldBkMode = dc.SetBkMode(TRANSPARENT);
		COLORREF crOldTextColor = dc.SetTextColor(UIgdi::InvertColor(PInfo.GetBkColor()));
		CString strName = pP->GetName();
		dc.DrawText(strName,strName.GetLength(),&rcP,DT_CENTER|DT_VCENTER);
		dc.SetTextColor(crOldTextColor);
		dc.SetBkMode(nOldBkMode);

		for (Pane* pC = pP->FirstChild(); pC; pC = pC->Next())
		{
			PaintP(pC, hdc);
		}
	}

	void Paint(HDC hdc)
	{
		Base::Paint(hdc);
		//if (m_pP) {
		//	PaintP(m_pP,hdc);
		//}
	}

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
