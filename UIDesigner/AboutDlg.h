// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <XLib/UIXCtrl2.h>
#include <XLib/UXWnd2.h>

class UIMyButton : public UIWnd2Impl<UIMyButton,UIButton2>
{

};

#if _MSC_VER<=1200
template<BOOL bDirectUI = FALSE>
class UIXWnd2TestImpl : public UIXWnd2Impl<UIXWnd2TestImpl>
{
	typedef UIXWnd2TestImpl<bDirectUI> This;
	typedef UIXWnd2Impl<UIXWnd2TestImpl> Base;
#else
template<BOOL bDirectUI = FALSE>
class UIXWnd2TestImpl : public UIXWnd2Impl<UIXWnd2TestImpl<bDirectUI>>
{
	typedef UIXWnd2TestImpl<bDirectUI> This;
	typedef UIXWnd2Impl<UIXWnd2TestImpl<bDirectUI>> Base;
#endif//
public:
	DECLARE_XMLWND_CLASS(_T("UIXWnd2Test"))

	BOOL IsDirectUI() { return bDirectUI; }

	UIXButton m_btnX1;
	UIXButton2 m_btnX2;
	UIButton2 m_btnMy;
	UIMyButton m_btnMy2;
	UIMyButton m_btnRadioBox;
	UIMyButton m_btnCheckBox;

	BEGIN_ATTRIBUTE_MAP(This)
		//
	END_ATTRIBUTE_MAP()
		
	BEGIN_XML_CONTROL_MAP(This)
		XML_NAME_CTRL(_T("btnX1"), m_btnX1)
		XML_NAME_CTRL(_T("btnX2"), m_btnX2)
	END_XML_CONTROL_MAP()

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (!IsDirectUI()) {
			RECT rc = {10, 10, 100, 50};
			m_btnMy.Create(*this, rc, NULL, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON); //不在UIWnd2的窗口管理中,只是一个标准窗口

			RECT rc2 = {10, 50, 100, 100};
			m_btnMy2.Create(*this, rc2);

			RECT rcRadioBox = {10, 100, 100, 150};
			m_btnRadioBox.Create(*this, rcRadioBox, _T("RadioBox"), WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON);

			RECT rcCheckBox = {10, 150, 100, 200};
			m_btnCheckBox.Create(*this, rcCheckBox, _T("CheckBox"), WS_CHILD|WS_VISIBLE|BS_CHECKBOX);
		}
		return bHandled;
	}
};
typedef UIXWnd2TestImpl<FALSE> UIXWndTest;
typedef UIXWnd2TestImpl<TRUE> UIXWndTest2;

class UIXPhoto2
	: public UIXStatic2Impl<UIXPhoto2>
	, public UIStatic2Map<UIXPhoto2>
	, public UIXStatic2SkinMap<UIXPhoto2>
{
	typedef UIXPhoto2 This;
	typedef UIXStatic2Impl<UIXPhoto2> Base;
	typedef UIStatic2Map<UIXPhoto2> FuncMap;
	typedef UIXStatic2SkinMap<UIXPhoto2> SkinMap;
protected:
	Image* m_pImage;
	Image* m_pImageEdge;
public:
	UIXPhoto2()
	{
		m_pImage = NULL;
		m_pImageEdge = NULL;
	}
	
	BOOL IsDirectUI() { return TRUE; }

	void SetImage(int nPartID, int nStateID, Image* pImage)
	{
		m_pImage = pImage;
	}
	void SetImageEdge(int nPartID, int nStateID, Image* pImage)
	{
		m_pImageEdge = pImage;
	}
	Image* GetImage(int nPartID, int nStateID)
	{
		return m_pImage;
	}
	Image* GetImageEdge(int nPartID, int nStateID)
	{
		return m_pImageEdge;
	}

	HRESULT DrawThemeBackground(HDC hDC, int nPartID, int nStateID, LPCRECT pRect, LPCRECT pClipRect = NULL)
	{
		Image* pImage = GetImage(nPartID, nStateID);
		if (pImage) {
			Graphics graphics(hDC);
			graphics.DrawImage(pImage, pRect->left+1, pRect->top+1, pRect->right-pRect->left-2, pRect->bottom-pRect->top-2);
			return S_OK;
		}
		return S_FALSE;
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

class CAboutDlg 
	: public UIXDialog2Impl<CAboutDlg> 
	, public UIEnableMove<CAboutDlg>
	, public UIRoundRectHelper<CAboutDlg>
	, public UIBkgndSkinDrawMap<CAboutDlg>
{
	typedef CAboutDlg This;
	typedef UIXDialog2Impl<CAboutDlg> Base;
	typedef UIBkgndSkinDrawMap<CAboutDlg> SkinDraw;
public:
	enum { IDD = IDD_ABOUTBOX };

	DECLARE_XMLWND_CLASS(_T("AboutDlg"))

	CAboutDlg() { }

	/*UIXButton m_btnX1;
	UIXButton2 m_btnX2;
	UIXButton2 m_btnX2_2;
	UIXWndTest m_test1;
	UIXWndTest2 m_test2;*/

	UIXSysButton2 m_bnMax;
	UIXSysButton2 m_bnMin;
	UIXSysButton2 m_bnClose;
	UIXPhoto2 m_Photo;
	UIXEdit2 m_edUsername;
	UIXHypeLink2 m_Register;
	UIXEdit2 m_edPassword;
	UIXButton2 m_bnMultiAccount;
	UIXButton2 m_bnSetting;
	UIXButton2 m_bnLogin;
	UIXButton2 m_bnCheckPassword;
	UIXButton2 m_bnAutoLogin;
	BOOL m_bPaintAnimate; //for paint animate

	BEGIN_ATTRIBUTE_MAP(This)
		//ATTRIBUTE_STRING_HANDLER2(_T("image_background"), SetBgImage, Image::FromFile)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		/*XML_NAME_CTRL(_T("btnX1"), m_btnX1)
		XML_NAME_CTRL(_T("btnX2"), m_btnX2)
		XML_NAME_CTRL(_T("btnX2_2"), m_btnX2_2)
		XML_NAME_CTRL(_T("test1"), m_test1)
		XML_NAME_CTRL(_T("test2"), m_test2)*/
		XML_NAME_CTRL(_T("max"), m_bnMax)
		XML_NAME_CTRL(_T("min"), m_bnMin)
		XML_NAME_CTRL(_T("close"), m_bnClose)
		XML_NAME_CTRL(_T("photo"), m_Photo)
		XML_NAME_CTRL(_T("username"), m_edUsername)
		XML_NAME_CTRL(_T("register"), m_Register)
		XML_NAME_CTRL(_T("password"), m_edPassword)
		XML_NAME_CTRL(_T("multi_account"), m_bnMultiAccount)
		XML_NAME_CTRL(_T("setting"), m_bnSetting)
		XML_NAME_CTRL(_T("login"), m_bnLogin)
		XML_NAME_CTRL(_T("check_password"), m_bnCheckPassword)
		XML_NAME_CTRL(_T("auto_login"), m_bnAutoLogin)
	END_XML_CONTROL_MAP()

	BOOL PaintBkgnd(HDC hdc, LPRECT lpRect)
	{
		ATLTRACE(_T("PaintBkgnd\n"));
		
		int i,j;
		CRect rcClient;
		GetClientRect(&rcClient);

		BOOL bRet = SkinDraw::PaintBkgnd(hdc,&rcClient);

		CDCHandle dc(hdc);

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

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		//MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		MESSAGE_HANDLER(WM_PAINTEFFECTMSG, OnPaintEffect)
		CHAIN_MSG_MAP(UIRoundRectHelper<CAboutDlg>)
		CHAIN_MSG_MAP(UIEnableMove<CAboutDlg>)
		CHAIN_MSG_MAP(SkinDraw)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	//LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		EnableMove();

		SetBkImage(_pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),_T("background")), NULL,GetWndClassName())
			, UI_BK_STYLE_STRETCH | UI_BK_EFFECT_ALPHA_VERT);

		if(m_Photo.IsWindow()) {
			m_Photo.SetImage(0, 0, _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),_T("PHOTO")),0,_T("STATIC")));
			m_Photo.SetImageEdge(0, 0, _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),_T("PHOTOEDGE")),0,_T("STATIC")));
		}

		CenterWindow();
		
		return 0L;
	}

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0L;
	}

	LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bPaintAnimate = wParam;
		return 0;
	}

	LRESULT OnPaintEffect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_bPaintAnimate) {
			m_bPaintAnimate = FALSE;
			PPAINTEFFECT pPE = (PPAINTEFFECT)lParam;
			if (pPE) {
				SIZE szClient;
				GetClientSize(&szClient);
				int nJalousieHeight;  
				nJalousieHeight = szClient.cy / 15; //每个窗子的高度  
				int i, j;  
				for (i = 0; i <= nJalousieHeight; i++ )   
				{  
					for(j = 0; j < 15; j++) //每个窗子  
					{  
						BitBlt(pPE->hDstDC, 0, j * nJalousieHeight, szClient.cx, i, pPE->hSrcDC, 0, j * nJalousieHeight, SRCCOPY);  
					}  
					Sleep(15);  
				}  
			}
		}
		return bHandled;
	}

};

class CMessageDlg
	: public UXDialog2Impl<CMessageDlg> 
	, public UIEnableMove<CMessageDlg>
	, public UIRoundRectHelper<CMessageDlg>
	, public UIBkgndSkinDrawMap<CMessageDlg>
{
	typedef CMessageDlg This;
	typedef UXDialog2Impl<CMessageDlg> Base;
	typedef UIBkgndSkinDrawMap<CMessageDlg> SkinDraw;
public:
	enum { IDD = IDD_ABOUTBOX };

	DECLARE_XMLWND_CLASS(_T("MessageBox"))

	CMessageDlg() { }

	UIXSysButton2 m_bnMax;
	UIXSysButton2 m_bnMin;
	UIXSysButton2 m_bnClose;
	UIXStatic2 m_stcText;
	UIXEdit2 m_edtInput;
	UIXButton2 m_bnOk;
	UIXButton2 m_bnCancel;
	UIXButton2 m_bnCheck;

	INT_PTR m_nResult;
	CString m_strInput;

	BEGIN_ATTRIBUTE_MAP(This)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		XML_NAME_CTRL(_T("max"), m_bnMax)
		XML_NAME_CTRL(_T("min"), m_bnMin)
		XML_NAME_CTRL(_T("close"), m_bnClose)
		XML_NAME_CTRL(_T("text"), m_stcText)
		//XML_NAME_CTRL(_T("input"), m_edtInput)
		XML_NAME_CTRL(_T("ok"), m_bnOk)
		XML_NAME_CTRL(_T("cancel"), m_bnCancel)
		XML_NAME_CTRL(_T("check"), m_bnCheck)
		CHAIN_XML_CONTROL_MAP(Base)
		CHAIN_XML_CONTROL_AFTER_MAP(This)
	END_XML_CONTROL_MAP()

	void OnCreateControl(HWND hWndParent, HWND hWndCtrl, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID)
	{
		;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		//MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		CHAIN_MSG_MAP(UIRoundRectHelper<CMessageDlg>)
		CHAIN_MSG_MAP(UIEnableMove<CMessageDlg>)
		CHAIN_MSG_MAP(SkinDraw)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	//LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		if((HWND)m_stcText && m_stcText.IsWindowVisible()) {
			if(m_stcText.GetWindowTextLength()<=0) {
				m_stcText.ShowWindow(SW_HIDE);
			}
		}
		if((HWND)m_bnCheck && m_bnCheck.IsWindowVisible()) {
			if(m_bnCheck.GetWindowTextLength()<=0) {
				m_bnCheck.ShowWindow(SW_HIDE);
			}
		}
		
		EnableMove();

		SetBkImage(_pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),_T("background")), NULL,GetWndClassName())
			, UI_BK_STYLE_STRETCH | UI_BK_EFFECT_ALPHA_VERT);

		CenterWindow();
		
		return 0L;
	}

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0L;
	}

	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		WORD wNotifyCode = HIWORD(wParam); 
		WORD wID = LOWORD(wParam); 
		HWND hwndCtrl = (HWND)lParam;
		if (hwndCtrl) {
			if (hwndCtrl==m_bnOk) {
				if (wNotifyCode==BN_CLICKED) {
					m_nResult = IDOK;
					if ((HWND)m_edtInput) {
						m_edtInput.GetWindowText(m_strInput);
					}
					OnOK();
				}
			} else if (hwndCtrl==m_bnCancel) {
				if (wNotifyCode==BN_CLICKED) {
					m_nResult = IDCANCEL;
					//m_edtInput
					OnCancel();
				}
			} else {
				bHandled = FALSE;
			}
		} else {
			bHandled = FALSE;
		}
		return bHandled;
	}
};

#define MsgAlert_Format \
	_T("<MessageBox title=\"%s\" rect=\"0,0,%d,%d\"> \
<SYSBUTTON name=\"close\" rect=\"%d,%d,%d,%d\" title=\"close\" style=\"0x56000000\" ></SYSBUTTON> \
<STATIC name=\"text\" rect=\"%d,%d,%d,%d\" title=\"%s\" style=\"0x56000000\" ></STATIC> \
<BUTTON name=\"ok\" rect=\"%d,%d,%d,%d\" title=\"%s\" style=\"0x56000001\" ></BUTTON> \
</MessageBox>")

#define MsgConfirm_Format \
	_T("<MessageBox title=\"%s\" rect=\"0,0,%d,%d\"> \
<SYSBUTTON name=\"close\" rect=\"%d,%d,%d,%d\" title=\"close\" style=\"0x56000000\" ></SYSBUTTON> \
<STATIC name=\"text\" rect=\"%d,%d,%d,%d\" title=\"%s\" style=\"0x56000000\" ></STATIC> \
<BUTTON name=\"ok\" rect=\"%d,%d,%d,%d\" title=\"%s\" style=\"0x56000001\" ></BUTTON> \
<BUTTON name=\"cancel\" rect=\"%d,%d,%d,%d\" title=\"%s\" style=\"0x56000000\" ></BUTTON> \
</MessageBox>")

#define MsgInput_Format \
	_T("<MessageBox title=\"%s\" rect=\"0,0,%d,%d\"> \
<SYSBUTTON name=\"close\" rect=\"%d,%d,%d,%d\" title=\"close\" style=\"0x56000000\" ></SYSBUTTON> \
<STATIC name=\"text\" rect=\"%d,%d,%d,%d\" title=\"%s\" style=\"0x56000000\" ></STATIC> \
<EDIT name=\"input\" rect=\"%d,%d,%d,%d\" style=\"0x56090000\" ></EDIT> \
<BUTTON name=\"ok\" rect=\"%d,%d,%d,%d\" title=\"%s\" style=\"0x56000001\" ></BUTTON> \
<BUTTON name=\"cancel\" rect=\"%d,%d,%d,%d\" title=\"%s\" style=\"0x56000000\" ></BUTTON> \
</MessageBox>")

#define MsgAlert(hWnd,...) \
	CMessageDlg MsgDlg; \
	CString strMsgXml; strMsgXml.Format(MsgAlert_Format, ##__VA_ARGS__); \
	int nMsgRet = MsgDlg.DoModal(hWnd,strMsgXml,XML_FLAG_STREAM); 

#define MsgConfirm(hWnd,...) \
	CMessageDlg MsgDlg; \
	CString strMsgXml; strMsgXml.Format(MsgConfirm_Format, ##__VA_ARGS__); \
	int nMsgRet = MsgDlg.DoModal(hWnd,strMsgXml,XML_FLAG_STREAM); 

#define MsgInput(hWnd,...) \
	CMessageDlg MsgDlg; \
	CString strMsgXml; strMsgXml.Format(MsgInput_Format, ##__VA_ARGS__); \
	int nMsgRet = MsgDlg.DoModal(hWnd,strMsgXml,XML_FLAG_STREAM); 

#define MsgBox(hWnd,format,...) \
	CMessageDlg MsgDlg; \
	CString strMsgXml; strMsgXml.Format(format, ##__VA_ARGS__); \
	int nMsgRet = MsgDlg.DoModal(hWnd,strMsgXml,XML_FLAG_STREAM); 

#define MsgResult() \
	MsgDlg.m_nResult

#define MsgInputValue() \
	MsgDlg.m_strInput

