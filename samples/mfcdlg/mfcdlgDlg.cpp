
// mfcdlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfcdlg.h"
#include "mfcdlgDlg.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg //: public CDialog
	: public UIXDialogImpl<CAboutDlg> 
	, public UIEnableMove<CAboutDlg>
	, public UIRoundRectHelper<CAboutDlg>
	, public UIBkgndSkinDrawMap<CAboutDlg>
{
	typedef UIXDialogImpl<CAboutDlg> BaseDlg;
	typedef UIBkgndSkinDrawMap<CAboutDlg> SkinDraw;
	DECLARE_XMLWND_CLASS(_T("AboutDlg"))
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	UIXSysButton m_bnMax;
	UIXSysButton m_bnMin;
	UIXSysButton m_bnClose;
	UIXEdit m_edUsername;
	UIXEdit m_edPassword;
	UIXButton m_bnMultiAccount;
	UIXButton m_bnSetting;
	UIXButton m_bnLogin;
	UIXButton m_bnCheckPassword;
	UIXButton m_bnAutoLogin;

	BEGIN_XML_CONTROL_MAP(This)
		XML_NAME_CTRL(_T("max"), m_bnMax)
		XML_NAME_CTRL(_T("min"), m_bnMin)
		XML_NAME_CTRL(_T("close"), m_bnClose)
		XML_NAME_CTRL(_T("username"), m_edUsername)
		XML_NAME_CTRL(_T("password"), m_edPassword)
		XML_NAME_CTRL(_T("multi_account"), m_bnMultiAccount)
		XML_NAME_CTRL(_T("setting"), m_bnSetting)
		XML_NAME_CTRL(_T("login"), m_bnLogin)
		XML_NAME_CTRL(_T("check_password"), m_bnCheckPassword)
		XML_NAME_CTRL(_T("auto_login"), m_bnAutoLogin)
	END_XML_CONTROL_MAP()

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
public:
	BOOL EraseBkgnd(HDC hdc)
	{
		return SkinDraw::EraseBkgnd(hdc);
	}

	BOOL OnEraseBkgnd(HDC hdc)
	{
		return TRUE;
	}

	void Paint(HDC hdc)
	{
		;
	}

	void OnPaint(HDC hdc)
	{
		SkinDraw::OnPaint(hdc);
	}

	BOOL PaintBkgnd(HDC hdc, LPRECT lpRect)
	{
		ATLTRACE(_T("PaintBkgnd\n"));
		
		int i,j;
		CRect rcClient;
		GetClientRect(&rcClient);

		BOOL bRet = SkinDraw::PaintBkgnd(hdc,&rcClient);

		WTL::CDCHandle dc(hdc);

		//dc.Draw3dRect(&rcClient, RGB(0,0,0), RGB(0,0,0));
		for(i = 1, j = rcClient.Width()-2; i < j; i++)
		{
			dc.SetPixel(i, rcClient.top, UIgdi::AlphaColor(RGB(0,0,0), 0.5, dc.GetPixel(i, rcClient.top), 0.5));
			dc.SetPixel(i, rcClient.bottom-1, UIgdi::AlphaColor(RGB(0,0,0), 0.5, dc.GetPixel(i, rcClient.bottom-1), 0.5));
		}
		for(i = 1, j = rcClient.Height()-2; i < j; i++)
		{
			dc.SetPixel(rcClient.left, i, UIgdi::AlphaColor(RGB(0,0,0), 0.5, dc.GetPixel(rcClient.left,i), 0.5));
			dc.SetPixel(rcClient.right-1, i, UIgdi::AlphaColor(RGB(0,0,0), 0.5, dc.GetPixel(rcClient.right-1, i), 0.5));
		}
		for(i = 2, j = rcClient.Width()-4; i < j; i++)
		{
			dc.SetPixel(i, rcClient.top+1, UIgdi::AlphaColor(RGB(255,255,255), 0.5, dc.GetPixel(i, rcClient.top+1), 0.5));
			dc.SetPixel(i, rcClient.bottom-2, UIgdi::AlphaColor(RGB(255,255,255), 0.5, dc.GetPixel(i, rcClient.bottom-2), 0.5));
		}
		for(i = 2, j = rcClient.Height()-4; i < j; i++)
		{
			dc.SetPixel(rcClient.left+1, i, UIgdi::AlphaColor(RGB(255,255,255), 0.5, dc.GetPixel(rcClient.left+1,i), 0.5));
			dc.SetPixel(rcClient.right-2, i, UIgdi::AlphaColor(RGB(255,255,255), 0.5, dc.GetPixel(rcClient.right-2, i), 0.5));
		}
		for (i = 1; i < 2; i++)
		{
			// 左上
			dc.SetPixel(rcClient.left+i, rcClient.top+i, UIgdi::AlphaColor(RGB(0,0,0), 0.5, dc.GetPixel(rcClient.left+i, rcClient.top+i), 0.5));
			// 右上
			dc.SetPixel(rcClient.right-i-1, rcClient.top+i, UIgdi::AlphaColor(RGB(0,0,0), 0.5, dc.GetPixel(rcClient.right-i-1, rcClient.top+i), 0.5));
			// 左下
			dc.SetPixel(rcClient.left+i, rcClient.bottom-i-1, UIgdi::AlphaColor(RGB(0,0,0), 0.5, dc.GetPixel(rcClient.left+i, rcClient.bottom-i-1), 0.5));
			// 右下
			dc.SetPixel(rcClient.right-i-1, rcClient.bottom-i-1, UIgdi::AlphaColor(RGB(0,0,0), 0.5, dc.GetPixel(rcClient.right-i-1, rcClient.bottom-i-1), 0.5));
		}
		/*CMemDC TempDC(hdc, rcClient);
		TempDC.FillSolidRect(&rcClient, RGB(0, 0, 0));
		rcClient.left++;
		rcClient.top++;
		rcClient.right--;
		rcClient.bottom--;
		TempDC.FillSolidRect(&rcClient, RGB(255, 255, 255));

		//UIgdi::AlphaBitBlt(hdc, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), TempDC, 0, 0);

		BLENDFUNCTION BF={0};
		BF.BlendOp= AC_SRC_OVER;
		BF.SourceConstantAlpha = 128; // 透明度
		
		// 左
		dc.AlphaBlend(0, 0, 2, rcClient.Height(), TempDC, 0, 0, 2, rcClient.Height(), BF);
		// 上中
		dc.AlphaBlend(2, 0, rcClient.Width() - 2, 2, TempDC, 2, 0, rcClient.Width() - 2, 2, BF);
		// 右
		dc.AlphaBlend(rcClient.Width() - 2, 0, 2, rcClient.Height(), TempDC, rcClient.Width() - 2, 0, 2, rcClient.Height(), BF);
		// 下
		dc.AlphaBlend(2, rcClient.Height() - 2, rcClient.Width() - 2, 2, TempDC, 2, rcClient.Height() - 2, rcClient.Width() - 2, 2, BF);

		for (int i = 0; i < 3; i++)
		{
			// 左上
			dc.AlphaBlend(i, 3 - i, 1, 1, TempDC, 0, 0, 1, 1, BF);
			dc.AlphaBlend(i + 1, 3 - i, 1, 1, TempDC, 1, 1, 1, 1, BF);

			// 右上
			dc.AlphaBlend(rcClient.right - 4 + i, i, 1, 1, TempDC, 0, 0, 1, 1, BF);
			dc.AlphaBlend(rcClient.right - 4 + i, i + 1, 1, 1, TempDC, 1, 1, 1, 1, BF);

			// 左下
			dc.AlphaBlend(i, rcClient.bottom - 4 + i, 1, 1, TempDC, 0, 0, 1, 1, BF);
			dc.AlphaBlend(i + 1, rcClient.bottom - 4 + i, 1, 1, TempDC, 1, 1, 1, 1, BF);

			// 右下
			dc.AlphaBlend(rcClient.right - 4 + i, rcClient.bottom - i - 1, 1, 1, TempDC, 0, 0, 1, 1, BF);
			dc.AlphaBlend(rcClient.right - 4 + i, rcClient.bottom - i - 2, 1, 1, TempDC, 1, 1, 1, 1, BF);

		}

		TempDC.DeleteDC();*/
		return bRet;
	}

	BEGIN_MSG_MAP(CAboutDlg)
		CHAIN_MSG_MAP(UIRoundRectHelper<CAboutDlg>)
		CHAIN_MSG_MAP(UIEnableMove<CAboutDlg>)
		CHAIN_MSG_MAP(SkinDraw)
		CHAIN_MSG_MAP(BaseDlg)
	END_MSG_MAP()


	BOOL OnInitDialog()
	{
		BaseDlg::OnInitDialog();

		// TODO: Add extra initialization here

		EnableMove();

		SetBkImage(_pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),_T("background")), NULL,GetWndClassName())
			, UI_BK_STYLE_STRETCH | UI_BK_EFFECT_ALPHA_VERT);

		CenterWindow();

		//m_bnCheckPassword.ModifyStyle(0,BS_OWNERDRAW);

		return TRUE;  // return TRUE  unless you set the focus to a control
	}

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : BaseDlg(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	BaseDlg::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, BaseDlg)
END_MESSAGE_MAP()


// CmfcdlgDlg dialog




CmfcdlgDlg::CmfcdlgDlg(CWnd* pParent /*=NULL*/)
	: Base(CmfcdlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcdlgDlg::DoDataExchange(CDataExchange* pDX)
{
	Base::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcdlgDlg, Base)
	ON_WM_SYSCOMMAND()
	//ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CmfcdlgDlg message handlers

BOOL EnumUXWndProc(LPCTSTR lpszClassName, LPVOID lParam)
{
	CmfcdlgDlg* pThis = (CmfcdlgDlg*)lParam;	
	pThis->AddClassName(lpszClassName);
	return FALSE;
}

void CmfcdlgDlg::AddClassName(LPCTSTR lpszClassName)
{
	m_strClassNames.push_back(lpszClassName);
}

BOOL CmfcdlgDlg::OnInitDialog()
{
	Base::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	int i,j;
	/*RECT rect;
	GetLayoutRect(&rect);
	Relayout(&rect);*/

	EnableMove();

	DYNCREATE_ENUM(UXWnd,EnumUXWndProc,this);

	Pane* pP = PaneFromName(_T("main"));
	if(pP) {
		RemoveChilds(pP);
		
		Pane* pP1 = NULL;
		int nCol = (int)sqrt((double)m_strClassNames.size());
		int nRow = nCol+1;
		InsertChilds(pP, nRow);
		for (pP1=pP->FirstChild(); pP1!=NULL; pP1=pP1->Next())
		{
			pP1->SetStyle((pP1->GetStyle()&~PANEL_STYLE_TB)|PANEL_STYLE_LR);
			InsertChilds(pP1, nCol);
		}

		for (i=0,pP1=pP->FirstChild(); pP1!=NULL; i++,pP1=pP1->Next())
		{
			Pane* pC = NULL;
			for(j=0,pC=pP1->FirstChild();pC!=NULL;j++,pC=pC->Next())
			{
				int nClass = i*nCol+j;
				if (nClass>=m_strClassNames.size()) {
					break;
				}

				CString strNameC = pC->GetName();
				CString strClass = m_strClassNames[nClass];
				DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
				DWORD dwExStyle = 0;
				CRect rcC;
				pC->GetRect(&rcC);
				CString strXml;
				strXml.Format(_T("<%s name=\"%s\" rect=\"%d,%d,%d,%d\" title=\"%s\", style=\"%d\" exstyle=\"%d\" />")
					, (LPCTSTR)strClass
					, (LPCTSTR)strNameC
					, rcC.left,rcC.top,rcC.right,rcC.bottom
					, (LPCTSTR)strClass
					, dwStyle
					, dwExStyle
					);
				HWND hWndCtrl = UXWndFactory::CreateControl(m_hWnd, strClass, strNameC, 0, strXml, XML_FLAG_STREAM);
				if (hWndCtrl) {
					OnCreateControl(m_hWnd, hWndCtrl, strClass, strNameC, 0);
				} else {
					ASSERT(0);
				}
			}
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmfcdlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlg;
		CString strXmlFile;
		strXmlFile.Format(_T("%s\\AboutDlg.xml"), _Platform->GetSkinPath());
		dlg.DoModal(strXmlFile);
	}
	else
	{
		Base::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
/*
void CmfcdlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		Base::OnPaint();
	}
}
*/
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmfcdlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

