// CChildView.cpp : implementation of the CUIDesignerView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ChildView.h"
#include "AboutDlg.h"

//////////////////////////////////////////////////////////////////////////

BOOL EnumUXWndProc(LPCTSTR lpszClassName, LPVOID lParam)
{
	CChildView* pThis = (CChildView*)lParam;	
	pThis->AddClassName(lpszClassName);
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
///CChildView

CChildView::CChildView()
{
	m_bEdit = TRUE;
}

CChildView::~CChildView()
{

}

void CChildView::AddClassName(LPCTSTR lpszClassName)
{
	m_strClassNames.push_back(lpszClassName);
}

void CChildView::SaveLayout()
{
	if(!m_strFile.IsEmpty()) {
		//选择保存文件
		static TCHAR szFilter[] = 
			_T("XML文件(*.xml\0")
			_T("所有文件(*.*)\0*.*\0");
		CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, m_hWnd);
		if(IDOK == dlg.DoModal()) {
			m_strFile = dlg.m_szFileName;
		}
	}
	if (m_strFile.IsEmpty()) {
		return;
	}
	File::RemoveFile(m_strFile);
	Format(m_strFile);
}

BOOL CChildView::GetLayoutRect(LPRECT lpRect)
{
	return ViewSplitter::GetLayoutRect(lpRect);
}

void CChildView::Relayout(LPCRECT lpRect)
{
	return ViewSplitter::Relayout(lpRect);
}

BOOL CChildView::PreTranslateMessage(MSG* pMsg)
{//这里不要调用SendMessage或者PostMessage来转发消息，需要提前处理的消息，明确调用对应的函数，或者明确处理，返回TRUE，否则返回FALSE
	return FALSE;
	BOOL bHandled = FALSE;
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		{
			//OnKeyDown(pMsg->message, pMsg->wParam, pMsg->lParam, bHandled);
		}
		break;
	default:
		break;
	}
	return bHandled;
}

LRESULT CChildView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	DYNCREATE_ENUM(UXWnd,EnumUXWndProc,this);
	return 0;
}

LRESULT CChildView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;

	if (m_bEdit) {
		SaveLayout();
	}

	PaneInfos::iterator it = m_pPInfos.begin();
	for (;it!=m_pPInfos.end();++it)
	{
		if (it->second.IsBkImage())
		{
			Image* pBgImage = it->second.GetBkImage();
			if (pBgImage) {
				delete pBgImage;
			}
		}
	}
	m_pPInfos.clear();

	return bHandled;
}

LRESULT CChildView::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = m_bEdit;
	POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	if (m_bEdit) {
		POINT ptClient = pt;
		ScreenToClient(&ptClient);

		m_pP1 = PaneFromPoint(ptClient);
		if (m_pP1) {
			m_pP2 = m_pP1->Next();
		} else {
			m_pP2 = NULL;
		}

		if (m_pP1) {
			CMenu menu;
			menu.LoadMenu(IDR_MENU_EDIT);
			CMenuHandle subMenu = menu.GetSubMenu(0);
			if (subMenu)
			{
				unsigned long Style = m_pP1->GetStyle();
				subMenu.CheckMenuItem(ID_EDIT_PANE_LR_SCALE, Style&PANEL_STYLE_LR_SCALE?MF_CHECKED:MF_UNCHECKED);
				subMenu.CheckMenuItem(ID_EDIT_PANE_TB_SCALE, Style&PANEL_STYLE_TB_SCALE?MF_CHECKED:MF_UNCHECKED);
				subMenu.CheckMenuItem(ID_EDIT_PANE_L_SIZED, Style&PANEL_STYLE_L_SIZED?MF_CHECKED:MF_UNCHECKED);
				subMenu.CheckMenuItem(ID_EDIT_PANE_R_SIZED, Style&PANEL_STYLE_R_SIZED?MF_CHECKED:MF_UNCHECKED);
				subMenu.CheckMenuItem(ID_EDIT_PANE_T_SIZED, Style&PANEL_STYLE_T_SIZED?MF_CHECKED:MF_UNCHECKED);
				subMenu.CheckMenuItem(ID_EDIT_PANE_B_SIZED, Style&PANEL_STYLE_B_SIZED?MF_CHECKED:MF_UNCHECKED);
				return subMenu.TrackPopupMenu(0, pt.x, pt.y, m_hWnd, NULL);
			}
		}
	} else {
		HWND hChild = ChildWindowFromPointEx(pt, CWP_SKIPINVISIBLE);
	}
	return bHandled;
}

LRESULT CChildView::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WORD wNotifyCode = HIWORD(wParam); 
	WORD wID = LOWORD(wParam); 
	HWND hwndCtrl = (HWND)lParam;
	/*if (hwndCtrl) {
		switch(wNotifyCode) 
		{
		case EN_UPDATE:
		case STN_DBLCLK:
		default:
			bHandled = FALSE;
			break;
		}
	} else */{
		switch(wID)
		{
		case ID_EDIT_PANE_START_STOP:
			if (m_bEdit) {
				SaveLayout();
			}
			m_bEdit = !m_bEdit;
			break;
		case ID_EDIT_PANE_INSERTLR_2:
			{
				if (!m_pP1) {
					break;
				}
				RemoveChilds(m_pP1);
				m_pP1->SetStyle((m_pP1->GetStyle()&~PANEL_STYLE_TB)|PANEL_STYLE_LR);
				InsertChilds(m_pP1, 2);
			}
			break;
		case ID_EDIT_PANE_INSERTLR_3:
			{
				if (!m_pP1) {
					break;
				}
				RemoveChilds(m_pP1);
				m_pP1->SetStyle((m_pP1->GetStyle()&~PANEL_STYLE_TB)|PANEL_STYLE_LR);
				InsertChilds(m_pP1, 3);
			}
			break;
		case ID_EDIT_PANE_INSERTLR_4:
			{
				if (!m_pP1) {
					break;
				}
			}
			break;
		case ID_EDIT_PANE_INSERTTB_2:
			{
				if (!m_pP1) {
					break;
				}
				RemoveChilds(m_pP1);
				m_pP1->SetStyle((m_pP1->GetStyle()&~PANEL_STYLE_LR)|PANEL_STYLE_TB);
				InsertChilds(m_pP1, 2);
			}
			break;
		case ID_EDIT_PANE_INSERTTB_3:
			{
				if (!m_pP1) {
					break;
				}
				RemoveChilds(m_pP1);
				m_pP1->SetStyle((m_pP1->GetStyle()&~PANEL_STYLE_LR)|PANEL_STYLE_TB);
				InsertChilds(m_pP1, 3);
			}
			break;
		case ID_EDIT_PANE_INSERTTB_4:
			{
				if (!m_pP1) {
					break;
				}

			}
			break;
		case ID_EDIT_PANE_DELETE:
			{
				if (!m_pP1) {
					break;
				}
				if (m_pP1!=m_pP) {
					SendMessage(WM_COMMAND, ID_PANE_CLOSE, (LPARAM)m_pP1);
				}
			}
			break;
		case ID_EDIT_PANE_LR_SCALE:
			{
				if (!m_pP1) {
					break;
				}
				unsigned long Style = m_pP1->GetStyle();
				if (Style & PANEL_STYLE_LR_SCALE) {
					Style &= ~PANEL_STYLE_LR_SCALE;
				} else {
					Style |= PANEL_STYLE_LR_SCALE;
				}
				m_pP1->SetStyle(Style);
			}
			break;
		case ID_EDIT_PANE_TB_SCALE:
			{
				if (!m_pP1) {
					break;
				}
				unsigned long Style = m_pP1->GetStyle();
				if (Style & PANEL_STYLE_TB_SCALE) {
					Style &= ~PANEL_STYLE_TB_SCALE;
				} else {
					Style |= PANEL_STYLE_TB_SCALE;
				}
				m_pP1->SetStyle(Style);
			}
			break;
		case ID_EDIT_PANE_L_SIZED:
			{
				if (!m_pP1) {
					break;
				}
				unsigned long Style = m_pP1->GetStyle();
				if (Style & PANEL_STYLE_L_SIZED) {
					Style &= ~PANEL_STYLE_L_SIZED;
				} else {
					Style |= PANEL_STYLE_L_SIZED;
				}
				m_pP1->SetStyle(Style);
			}
			break;
		case ID_EDIT_PANE_R_SIZED:
			{
				if (!m_pP1) {
					break;
				}
				unsigned long Style = m_pP1->GetStyle();
				if (Style & PANEL_STYLE_R_SIZED) {
					Style &= ~PANEL_STYLE_R_SIZED;
				} else {
					Style |= PANEL_STYLE_R_SIZED;
				}
				m_pP1->SetStyle(Style);
			}
			break;
		case ID_EDIT_PANE_T_SIZED:
			{
				if (!m_pP1) {
					break;
				}
				unsigned long Style = m_pP1->GetStyle();
				if (Style & PANEL_STYLE_T_SIZED) {
					Style &= ~PANEL_STYLE_T_SIZED;
				} else {
					Style |= PANEL_STYLE_T_SIZED;
				}
				m_pP1->SetStyle(Style);
			}
			break;
		case ID_EDIT_PANE_B_SIZED:
			{
				if (!m_pP1) {
					break;
				}
				unsigned long Style = m_pP1->GetStyle();
				if (Style & PANEL_STYLE_B_SIZED) {
					Style &= ~PANEL_STYLE_B_SIZED;
				} else {
					Style |= PANEL_STYLE_B_SIZED;
				}
				m_pP1->SetStyle(Style);
			}
			break;
		case ID_EDIT_BKGND:
			{
				if (!m_pP1) {
					break;
				}
				CString strFile;
				/*CMessageDlg dlg;
				dlg.m_strText = _T("1231231231");
				CString strXmlFile;
				strXmlFile.Format(_T("%s\\MessageBox.xml"), _pUISkinManager->GetSkinPath());
				dlg.DoModal(m_hWnd,strXmlFile);*/
				/*MsgInput(m_hWnd
					, _T("添加效果图"), 380,280
					, 341,0,380,20 
					, 16,139,103,226, _T("请输入背景图片路径：")
					, 112,142,311,170 
					, 156,213,226,240, _T("确认")
					, 236,213,306,240, _T("取消")
					);
				strFile = MsgInputValue();*/
				static TCHAR szFilter[] = 
					_T("图片文件(*.bmp;*.jpg;*.jpeg;*.jpe;*.png;*.gif;*.tif;*.tiff)\0*.bmp;*.jpg;*.jpeg;*.jpe;*.png;*.gif;*.tif;*.tiff\0")
					_T("所有文件(*.*)\0*.*\0");
				CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, m_hWnd);
				if(IDOK == dlg.DoModal()) {
					strFile = dlg.m_szFileName;
				}
				if (!strFile.IsEmpty() && PathFileExists(strFile)) {
					PaneInfo& PInfo = m_pPInfos[m_pP1];
					PInfo.SetBkImage(Image::FromFile((LPCTSTR)strFile));
				}
			}
			break;
		case ID_EDIT_VIEW_DEBUG:
		case ID_EDIT_VIEW_SYSBUTTON:
		case ID_EDIT_VIEW_BUTTON:
		case ID_EDIT_VIEW_CHECKBOX:
		case ID_EDIT_VIEW_RADIOBOX:
		case ID_EDIT_VIEW_STATIC:
		case ID_EDIT_VIEW_EDIT:
		case ID_EDIT_VIEW_IMAGE:
		case ID_EDIT_VIEW_HYPELINK:
		case ID_EDIT_VIEW_LIST:
		case ID_EDIT_VIEW_COMBOBOX:
		case ID_EDIT_VIEW_LISTCTRL:
		case ID_EDIT_VIEW_TREECTRL:
			{
				if (!m_pP1) {
					break;
				}
				//添加并绑定窗口
				CString strClassName;
				CString strText;
				DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
				DWORD dwExStyle = 0;
				if(wID==ID_EDIT_VIEW_STATIC) {
					strClassName = _T("STATIC");
					strText = _T("static");
				} else if(wID==ID_EDIT_VIEW_IMAGE) {
					strClassName = _T("STATIC");
					dwStyle |= SS_BITMAP;
				} else if(wID==ID_EDIT_VIEW_HYPELINK) {
					strClassName = _T("HYPELINK");
					strText = _T("link");
				} else if (wID==ID_EDIT_VIEW_SYSBUTTON) {
					strClassName = _T("SYSBUTTON");
					strText = _T("close");
				} else if(wID==ID_EDIT_VIEW_BUTTON) {
					strClassName = _T("BUTTON");
					strText = _T("button");
				} else if(wID==ID_EDIT_VIEW_CHECKBOX) {
					strClassName = _T("BUTTON");
					strText = _T("checkbox");
					dwStyle |= BS_CHECKBOX;
				} else if(wID==ID_EDIT_VIEW_RADIOBOX) {
					strClassName = _T("BUTTON");
					strText = _T("radiobox");
					dwStyle |= BS_RADIOBUTTON;
				} else if(wID==ID_EDIT_VIEW_EDIT) {
					strClassName = _T("EDIT");
					strText = _T("edit");
				} else if(wID==ID_EDIT_VIEW_RICHEDIT) {
					strClassName = _T("RICHEDIT");
					strText = _T("richedit");
				} else if(wID==ID_EDIT_VIEW_LISTBOX) {
					strClassName = _T("LISTBOX");
					dwStyle |= LBS_COMBOBOX;
				} else if(wID==ID_EDIT_VIEW_COMBOBOX) {
					strClassName = _T("COMBOBOX");
					dwStyle |= CBS_DROPDOWNLIST;
				} else if(wID==ID_EDIT_VIEW_LISTCTRL) {
					strClassName = _T("LISTCTRL");
					dwStyle |= LVS_REPORT;
				} else if(wID==ID_EDIT_VIEW_TREECTRL) {
					strClassName = _T("TREECTRL");
					dwStyle |= TVS_HASLINES|TVS_LINESATROOT;
				} else {
					strClassName = _T("SCROLLBAR");
					//dwStyle |= SBS_VERT;
					/*strText.Format(_T("Unknown:[%d]"), wID);
					MsgAlert(m_hWnd
						, _T("title"), 380,280
						, 341,0,380,20 
						, 16,139,103,226, strText
						, 156,213,226,240, _T("确认"));*/
				}
				if (strClassName.IsEmpty()) {
					break;
				}
				CRect rcP1;
				m_pP1->GetRect(&rcP1);
				CString strNameP1 = m_pP1->GetName();
				CString strXml;
				strXml.Format(_T("<%s name=\"%s\" rect=\"%d,%d,%d,%d\" title=\"%s\", style=\"%d\" exstyle=\"%d\" />")
					, (LPCTSTR)strClassName
					, (LPCTSTR)strNameP1
					, rcP1.left,rcP1.top,rcP1.right,rcP1.bottom
					, (LPCTSTR)strText
					, dwStyle
					, dwExStyle
					);
				HWND hWndCtrl = WndFactory::CreateControl(m_hWnd, strClassName, strNameP1, 0, strXml, XML_FLAG_STREAM);
				if (hWndCtrl) {
					if (wID==ID_EDIT_VIEW_DEBUG) {
						UIScrollBar2 wndScrollBar = hWndCtrl;
						SCROLLINFO ScrollInfo = {0};
						ScrollInfo.cbSize = sizeof(SCROLLINFO);
						ScrollInfo.fMask = SIF_ALL;
						ScrollInfo.nMin = 0;
						ScrollInfo.nMax = 300;
						ScrollInfo.nPage = 100;
						ScrollInfo.nPos = 100;
						ScrollInfo.nTrackPos = 1;
						wndScrollBar.SetScrollInfo(&ScrollInfo);
					} else if(wID==ID_EDIT_VIEW_IMAGE) {
						CString strFile;
						static TCHAR szFilter[] = 
							_T("图片文件(*.bmp;*.jpg;*.jpeg;*.jpe;*.png;*.gif;*.tif;*.tiff)\0*.bmp;*.jpg;*.jpeg;*.jpe;*.png;*.gif;*.tif;*.tiff\0")
							_T("所有文件(*.*)\0*.*\0");
						CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, m_hWnd);
						if(IDOK == dlg.DoModal()) {
							strFile = dlg.m_szFileName;
						}
						if (!strFile.IsEmpty() && PathFileExists(strFile)) {
							UIStatic wndImage = hWndCtrl;
							_pUISkinManager->SetHBITMAP(MAKESKINSTRRESID2(_T("Bitmap"),strNameP1),UIgdi::BitmapFromFile((LPCTSTR)strFile));
							wndImage.SetBitmap(_pUISkinManager->GetHBITMAP(MAKESKINSTRRESID2(_T("Bitmap"),strNameP1)));
						}
					}

					ViewSplitter::OnCreateControl(m_hWnd, hWndCtrl, strClassName, strNameP1, 0);

					//ViewSplitter::Enable(FALSE,m_pP1);
				}
			}
			break;
		case ID_EDIT_VIEW_GROUP:
			{
				if (!m_pP1) {
					break;
				}
			}
			break;
		case ID_EDIT_VIEW_GROUP1:
			{
				if (!m_pP1) {
					break;
				}

			}
			break;
		case ID_EDIT_VIEW_GROUP2:
			{
				if (!m_pP1) {
					break;
				}

			}
			break;
		case ID_EDIT_VIEW_GROUP3:
			{
				if (!m_pP1) {
					break;
				}

			}
			break;
		case ID_EDIT_VIEW_GROUP4:
			{
				if (!m_pP1) {
					break;
				}

			}
			break;
		//////////////////////////////////////////////////////////////////////////
		default:
			bHandled = FALSE;
			break;
		}
		if (bHandled) {
			Invalidate();
		}
	}
	return bHandled;
}

LRESULT CChildView::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch (wParam)
	{
	default:
		bHandled = FALSE;
		break;
	}
	return 0L;
}

//////////////////////////////////////////////////////////////////////////

BOOL CUIDesignerView::PreTranslateMessage(MSG* pMsg)
{
	pMsg;
	return FALSE;
}

LRESULT CUIDesignerView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);

	//TODO: Add your drawing code here

	return 0;
}
