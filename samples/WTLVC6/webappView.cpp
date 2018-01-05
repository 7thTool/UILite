// webappView.cpp : implementation of the CWebappView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "webappView.h"

#include "XLib/XFile.h"
#include "XLib/XUser.h"
#include "XLib/XStr.h"

#include "Public.h"

#include <comutil.h>

#include <oleacc.h>
#pragma comment(lib,"oleacc")

BOOL CALLBACK EnumChildProc(HWND hwnd,LPARAM lParam)
{
	TCHAR szClassName[100];
	::GetClassName(hwnd, szClassName, sizeof(szClassName) );
	if (_tcscmp(szClassName, _T("Internet Explorer_Server")) == 0) {
		*(HWND*)lParam = hwnd;
		return FALSE; // 找到第一个 IE 控件的子窗口就停止
	} else {
		EnumChildWindows(hwnd, EnumChildProc, lParam);
		if(*(HWND*)lParam) {
			return FALSE;
		}
		return TRUE; // 继续枚举子窗口
	}
};

BOOL FindFromHwnd(HWND hWnd) 
{
	HWND hWndChild = NULL;
	::EnumChildWindows( hWnd, EnumChildProc, (LPARAM)&hWndChild);
	if(NULL == hWndChild) {
		return FALSE;
	}

	UINT nMsg = ::RegisterWindowMessage(_T("WM_HTML_GETOBJECT"));
	LRESULT lRes;
	::SendMessageTimeout(hWndChild, nMsg, 0L, 0L, SMTO_ABORTIFHUNG, 1000, (DWORD*)&lRes);

	CComPtr<IHTMLDocument2> spDoc;
	HRESULT hr = ::ObjectFromLresult(lRes, IID_IHTMLDocument2, 0, (LPVOID *)&spDoc);
	if (FAILED(hr)) {
		return FALSE;
	}

	USES_CONVERSION;
	// 程序运行到此，已经找到了 IHTMLDocument2 的接口指针
	//CComPtr<IHTMLElement> spElement;
	//spDoc->get_body(&spElement);
	//if (spElement) {
		//CComBSTR name, innertext, innerhtml, outerhtml;
		//spElement->get_tagName(&name);
		//spElement->get_innerText(&innertext);
		//spElement->get_innerHTML(&innerhtml);
		//spElement->get_outerHTML(&outerhtml);
		//MessageBox(NULL, outerhtml, NULL, MB_OK);
		CComBSTR charset;
		spDoc->get_charset(&charset);
		UINT uCP = _tcs2encode(OLE2T(charset), CP_OEMCP);
		std::string source;
		GetHtmlSourceText(spDoc, source);
		TCHAR szFile[MAX_PATH];
		_stprintf(szFile, _T("%s\\html.txt"), _Module.GetAppData());
		/*{
			std::wstring wsource;
			mb2wc(source, wsource, uCP);
			wofstream fout(szFile, ios::trunc);
			fout << wsource << endl;
		}*/
		File f(szFile, modeWrite|modeCreate);
		f.Write(source.c_str(), source.size());
		f.Close();
		/*CComQIPtr<IPersistFile>	spFile = spDoc;
		if(spFile) {
			spFile->Save(T2OLE(szFile), TRUE);
		}*/
		SHOpen(szFile);
	//}

	return TRUE;
}

HRESULT GetHtmlSourceText(IHTMLDocument2* pHtmlDoc, std::string& source)
{ 
	HRESULT hr = S_OK;
	if (pHtmlDoc != NULL) {
		HGLOBAL hMemory = GlobalAlloc(GMEM_MOVEABLE, 0);
		if (hMemory != NULL) {
			CComPtr<IPersistStreamInit> spPersistStream = NULL;
			CComPtr<IStream> spStream = NULL;
			hr = pHtmlDoc->QueryInterface(&spPersistStream);
			if (SUCCEEDED(hr)) {
				hr = CreateStreamOnHGlobal(hMemory, TRUE, &spStream);
				if (SUCCEEDED(hr)) {
					hr = spPersistStream->Save(spStream, FALSE);
					if (SUCCEEDED(hr)) {
						LPVOID pMem = GlobalLock(hMemory);
						if (pMem != NULL) {
							source.assign((char*)pMem, GlobalSize(hMemory));
							GlobalUnlock(hMemory);
						}
					} else {
						ASSERT(FALSE);
						hr = E_POINTER;
					}
				}
			}
			GlobalFree(hMemory);
		} else {
			ASSERT(FALSE);
			hr = E_POINTER;
		}
	} else {
		ASSERT(FALSE);
		hr = E_POINTER;
	}
	return hr;
}

void EnumIE( void )
{
	//cout << _T("开始扫描系统中正在运行的浏览器实例") << endl;
	CComPtr< IShellWindows > spShellWin;
	HRESULT hr = spShellWin.CoCreateInstance( CLSID_ShellWindows );
	if ( FAILED ( hr ) )
	{
		//cout << _T("获取 IShellWindows 接口错误") << endl;
		return;
	}
	long nCount = 0;  // 取得浏览器实例个数(Explorer 和 IExplorer)
	spShellWin->get_Count( &nCount );
	if( 0 == nCount )
	{
		//cout << _T("没有在运行着的浏览器") << endl;
		return;
	}
	for(int i=0; i<nCount; i++)
	{
		CComPtr< IDispatch > spDispIE;
		hr=spShellWin->Item(CComVariant( (long)i ), &spDispIE );
		if ( FAILED ( hr ) ) continue;
		CComQIPtr< IWebBrowser2 > spBrowser = spDispIE;
		if ( !spBrowser )  continue;
		CComPtr < IDispatch > spDispDoc;
		hr = spBrowser->get_Document( &spDispDoc );
		if ( FAILED ( hr ) ) continue;
		CComQIPtr< IHTMLDocument2 > spDocument2 = spDispDoc;
		if ( !spDocument2 )  continue;
		// 程序运行到此，已经找到了 IHTMLDocument2 的接口指针
		// 删除下行语句的注释，把浏览器的背景改变看看
		// spDocument2->put_bgColor( CComVariant( "green" ) );

		//EnumForm( spDocument2 );  //枚举所有的表单
	}
}

//////////////////////////////////////////////////////////////////////////

BOOL IsLinkElement(IHTMLElement* pElement)
{
	if(pElement) {
		CComQIPtr<IHTMLLinkElement> spLink = pElement;
		if (spLink) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL IsEditElement(IHTMLElement* pElement)
{
	BOOL bEdit = FALSE;
	if(pElement) {
		VARIANT_BOOL bTextEdit = FALSE;
		pElement->get_isTextEdit(&bTextEdit);
		bEdit = bTextEdit;
		if(!bEdit) {
			CComQIPtr<IHTMLElement3> spElement3 = pElement;
			if(spElement3) {
				VARIANT_BOOL bEditable = FALSE;
				spElement3->get_isContentEditable(&bEditable);
				bEdit = bEditable;
			}
		}
		/*CComQIPtr<IHTMLElementDefaults> spElementDefaults = pElement;
		if(spElementDefaults) {
			BSTR p = NULL;
			spElementDefaults->get_contentEditable(&p);
			CString strEditable = p;
		}*/
		if(!bEdit) {
// 			CComBSTR bstrTagName;
// 			pElement->get_tagName(&bstrTagName);
// 			if (lstrcmpiW(L"TEXTAREA", bstrTagName) == 0) {
// 				bEdit = TRUE;
// 			}
			//else if (lstrcmpiW(L"DIV", bstrTagName) == 0)
			//{
			//}
			//else if (lstrcmpiW(L"IFRAME", bstrTagName) == 0 || lstrcmpiW(L"FRAME", bstrTagName) == 0)
			//{
			//	
			//}
		}
	}
	return bEdit;
}

BOOL IsEditElementEditable(IHTMLElement* pElement)
{
	ATLASSERT(IsEditElement(pElement));
	BOOL bEditable = FALSE;
	if(pElement) {
		/*BSTR p = NULL;
		spDocument->get_designMode(&p);
		CString strDesignMode = p;
		if(strDesignMode.CompareNoCase(_T("On")) == 0)
		{
			bEditMode = TRUE;
		}*/
		/*CComQIPtr<IDisplayServices> spDisplayServices = spDocument;
		if(spDisplayServices)
		{
			CComPtr<IHTMLCaret> spCaret;
			spDisplayServices->GetCaret(&spCaret);
			if(spCaret)
			{
				BOOL bCaretVisible = FALSE;
				spCaret->IsVisible(&bCaretVisible);
				bEditMode = bCaretVisible;
			}
		}*/
		if(!bEditable) {
			CComQIPtr<IHTMLElement3> spElement3 = pElement;
			if(spElement3) {
				VARIANT_BOOL bEditable = FALSE;
				spElement3->get_isContentEditable(&bEditable);
				bEditable = bEditable;
			}
		}
	}
	return bEditable;
}

BOOL IsDocumentEditable(IHTMLDocument2* pDocument)
{
	BOOL bEditable = FALSE;
	if(pDocument) {
		USES_CONVERSION;

		BSTR p = NULL;
		pDocument->get_designMode(&p);
		CString strDesignMode = OLE2T(p);
		if(strDesignMode.CompareNoCase(_T("On")) == 0)
		{
			bEditable = TRUE;
		}
	}
	return bEditable;
}

HRESULT InsertTextToCaret(IHTMLDocument2* pDocument, LPCTSTR lpszText)
{
	HRESULT hr = -1L;
	CComQIPtr<IDisplayServices> spDisplayServices = pDocument;
	if(spDisplayServices) {
		CComPtr<IHTMLCaret> spCaret;
		spDisplayServices->GetCaret(&spCaret);
		if(spCaret) {
			BOOL bCaretVisible = FALSE;
			spCaret->IsVisible(&bCaretVisible);
			if (bCaretVisible) {
				CComBSTR text(lpszText);
				hr = spCaret->InsertText(text,text.Length()); 
			}
		}
	}
	return hr;
}

HRESULT EnumForm(IHTMLFormElement* pFromElement, void* pParam)
{
	HRESULT hr = S_FALSE;
	long i = 0, j = 0;
	//表单域的总数目
	hr = pFromElement->get_length(&j);
	for(i = 0; i < j; i++)
	{
		CComDispatchDriver spInputElement; // IDispatch 的智能指针
		pFromElement->item(CComVariant(i), CComVariant(), &spInputElement);

		CComVariant vName,vVal,vType; // 域名称，域值，域类型
		spInputElement.GetPropertyByName(L"name", &vName);
		spInputElement.GetPropertyByName(L"value",&vVal);
		spInputElement.GetPropertyByName(L"type", &vType);
		// 使用 IDispatch 的智能指针的好处就是：象上面这样读取、设置属性很简单
		// 另外调用 Invoke 函数也异常方便，Invoke0(),Invoke1(),Invoke2()...
	}

	//想提交这个表单吗？删除下面语句的注释吧
	//pForm->submit();

	return hr;
}

HRESULT EnumForms(IHTMLElementCollection* pElementCollection, void* pParam)
{
	HRESULT hr = -1L;
	long i = 0, j = 0;   
	//取得表单数目
	hr = pElementCollection->get_length(&j);
	for(i = 0; i < j; i++)
	{
		CComPtr<IDispatch> spDisp = NULL; //取得第 i 项表单
		hr = pElementCollection->item(CComVariant(i), CComVariant(), &spDisp);
		if (spDisp) {
			CComQIPtr<IHTMLFormElement> spFormElement = spDisp;
			//hr = EnumForm(spFormElement, pParam);
			hr = ((CWebappView*)pParam)->OnForm(spFormElement);
		}
	}
	return hr;
}

HRESULT EnumElement(IHTMLDocument2* pDocument, void* pParam)
{
	HRESULT hr = -1L;
	long i = 0, j = 0;
	CComPtr<IHTMLElementCollection> spElementCollection;  
	pDocument->get_all(&spElementCollection);
	if(spElementCollection) {
		spElementCollection->get_length(&j);
		for(i = 0; i < j; i++)
		{
			VARIANT id, index;
			V_VT(&id) = VT_I4;
			V_I4(&id) = i;
			V_VT(&index) = VT_I4;
			V_I4(&index) = 0;
			CComPtr<IDispatch> spDispatch;
			spElementCollection->item(id, index, &spDispatch);
			if(spDispatch) {
				// 假设 spDisp 是由IHTMLElementCollection::item() 得到的 IDispatch 指针
				/*CComQIPtr<IHTMLInputTextElement> spInputText(spDispatch);
				CComQIPtr<IHTMLInputButtonElement> spInputButton(spDispatch);
				CComQIPtr<IHTMLInputHiddenElement> spInputHidden(spDispatch);
				CComQIPtr<IHTMLLinkElement> spLink(spDispatch);
				CComQIPtr<IHTMLAnchorElement> spAnchor(spDispatch); */
	
				/*if (spInputText) {
					//如果是文本输入表单域
				} else if (spInputButton) {
					//如果是按纽输入表单域
				} else if (spInputHidden) {
					//如果是隐藏输入表单域
				} else if(spLink) {
					CComBSTR href;
					spLink->get_href(&href);
					MessageBox(NULL, href, NULL, MB_OK);
				} else if(spAnchor) {
					CComBSTR name, href;
					spAnchor->get_name(&name);
					spAnchor->get_href(&href);
					MessageBox(NULL, href, name, MB_OK);
				} else */{
					CComQIPtr<IHTMLElement> spElement(spDispatch);
					if (spElement)
					{
						hr = ((CWebappView*)pParam)->OnElement(spElement);
						if (SUCCEEDED(hr)) {
							break;
						}
						/*CComBSTR name, innertext, innerhtml, outerhtml;
						spElement->get_tagName(&name);
						spElement->get_innerText(&innertext);
						spElement->get_innerHTML(&innerhtml);
						spElement->get_outerHTML(&outerhtml);
						//这里就是百度主页中 贴吧的标签。
						if(name==CComBSTR("A") && innertext==CComBSTR("贴吧")
							//&& innerhtml==CComBSTR("贴&nbsp;吧")
							)
						{
							spElement->click() ;  //找到了，点击它
						}*/
					}
					/*if(IsEditElement(spElement)) {
#ifdef _DEBUG
						CComBSTR bstrTagName;
						spElement->get_tagName(&bstrTagName);
						if (IsEditElementEditable(spElement)) {
							MessageBox(NULL, bstrTagName, NULL, MB_OK);
						}
#endif//
					}*/
				}
			}
		}
	}
	return hr;
}

HRESULT EnumDocument(IHTMLDocument2* pDocument, void* pParam)
{
	HRESULT hr = -1L;
	long i = 0, j = 0;
	CComQIPtr<IOleContainer> spContainer(pDocument); 
	if(spContainer) {
		CComPtr<IEnumUnknown> spEnumerator;
		if(SUCCEEDED(spContainer->EnumObjects(OLECONTF_EMBEDDINGS, &spEnumerator))) {
			ULONG uFetched = 0;
			CComPtr<IUnknown> spUnk;
			while (spEnumerator->Next(1, &spUnk, &uFetched) == S_OK) 
			{
				CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> spWB(spUnk); 
				if(spWB) {
					CComPtr<IDispatch> spDisp;
					spWB->get_Document(&spDisp);                                        
					CComPtr<IHTMLDocument2> spDocument2; 
					spDisp->QueryInterface(IID_IHTMLDocument2, (void**) &spDocument2);
					//EnumElement(spDocument2, pParam);
					hr = ((CWebappView*)pParam)->OnDocument(spDocument2);
					if (SUCCEEDED(hr)) {
						break;
					}
				}
				spUnk.Release();
			}
		}
	}
	return hr;
}

//////////////////////////////////////////////////////////////////////////

void CWebappView::SetAutoClickKeyValue(LPCTSTR lpszSite, LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	m_bAutoClickKey = FALSE;
	m_bAutoClickValue = FALSE;
	m_strAutoClickKey = lpszKey;
	m_strAutoClickValue = lpszValue;
	Navigate2(lpszSite);
}

HRESULT CWebappView::OnDocument(IHTMLDocument2* pDocument)
{
	HRESULT hr = -1L;
	if (pDocument) {
		if (m_strAutoClickKey.IsEmpty()) {
			m_bAutoClickKey = TRUE;
		} else {
			if (!m_bAutoClickKey) {
				hr = InsertTextToCaret(pDocument, m_strAutoClickKey);
				if (SUCCEEDED(hr)) {
					m_bAutoClickKey = TRUE;
					//模拟搜索
					//PostMessage(WM_KEYUP, VK_RETURN, 0L);
					//PostMessage(WM_KEYDOWN, VK_RETURN, 0L);
					CComPtr<IHTMLElementCollection> spFormCollection;
					pDocument->get_forms(&spFormCollection);
					if (spFormCollection) {
						EnumForms(spFormCollection, this);
					}
					return hr;
				}
			}
		}

		if(m_bAutoClickKey && !m_bAutoClickValue) {
			hr = EnumElement(pDocument, this);
		}
		
		hr = EnumDocument(pDocument, this);
	}
	return hr;
}

HRESULT CWebappView::OnElement(IHTMLElement* pElement)
{
	HRESULT hr = -1L;
	if (pElement) {
		if (!m_bAutoClickValue) {
			CComQIPtr<IHTMLAnchorElement> spAnchor(pElement);
			if (spAnchor) {
				CComBSTR name, innertext, innerhtml, outerhtml, href;
				//pElement->get_tagName(&name);
				pElement->get_innerText(&innertext);
				//pElement->get_innerHTML(&innerhtml);
				//pElement->get_outerHTML(&outerhtml);
				//这里就是百度主页中 贴吧的标签。
				if(1
					//&& name==CComBSTR("A") 
					&& innertext == CComBSTR(m_strAutoClickValue)
					//&& innerhtml==CComBSTR("贴&nbsp;吧")
					)
				{
					hr = S_OK;
					m_bAutoClickValue = TRUE;

					spAnchor->get_href(&href);
					Navigate2(CString(href));

					//hr = pElement->click() ;  //找到了，点击它,有可能在新窗口弹出
				}
			}
		}
	}
	return hr;
}

HRESULT CWebappView::OnForm(IHTMLFormElement* pFromElement)
{
	HRESULT hr = S_FALSE;
	/*long i = 0, j = 0;
	//表单域的总数目
	hr = pFromElement->get_length(&j);
	for(i = 0; i < j; i++)
	{
		CComDispatchDriver spInputElement; // IDispatch 的智能指针
		pFromElement->item(CComVariant(i), CComVariant(), &spInputElement);

		CComVariant vName,vVal,vType; // 域名称，域值，域类型
		spInputElement.GetPropertyByName(L"name", &vName);
		spInputElement.GetPropertyByName(L"value",&vVal);
		spInputElement.GetPropertyByName(L"type", &vType);
		// 使用 IDispatch 的智能指针的好处就是：象上面这样读取、设置属性很简单
		// 另外调用 Invoke 函数也异常方便，Invoke0(),Invoke1(),Invoke2()...
		//spInputElement.PutPropertyByName();
		MessageBox(vVal.bstrVal ? COLE2CT( vVal.bstrVal ) : _T("NULL"),
			vName.bstrVal ? COLE2CT( vName.bstrVal ) : _T("NULL"));
	}*/

	//想提交这个表单吗？删除下面语句的注释吧
	hr = pFromElement->submit();

	return hr;
}

BOOL CWebappView::PreTranslateMessage(MSG* pMsg)
{
	if((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
	   (pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
		return FALSE;

	// give HTML page a chance to translate this message
	return (BOOL)SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg);
}

LRESULT CWebappView::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	KillTimer(100);

	CComQIPtr<IHTMLDocument2> spDocument = GetDocument();
	OnDocument(spDocument);

	return bHandled;
}

//////////////////////////////////////////////////////////////////////////

void CWebappView::OnStatusTextChange(const CString& strText) { }
void CWebappView::OnProgressChange(long progress, long progressMax) { }
void CWebappView::OnCommandStateChange(long Command, BOOL bEnable) { }
void CWebappView::OnDownloadBegin() { }
void CWebappView::OnDownloadComplete() { }
void CWebappView::OnTitleChange(const CString& strTitle) 
{
	::SetWindowText(GetParent(), strTitle);
}

void CWebappView::OnNavigateComplete2(IDispatch* pDisp, const CString& strURL) 
{
	/*VARIANT var;
	execScript(L"window.alert=null", &var, L"javascript");
	execScript(L"window.confirm=null", &var, L"javascript");
	execScript(L"window.open=null", &var, L"javascript");
	execScript(L"window.showModalDialog=null", &var, L"javascript");
	execScript(L"window.close=null", &var, L"javascript");*/
}
void CWebappView::OnBeforeNavigate2(IDispatch* pDisp, const CString& strURL, DWORD nFlags,
					   const CString& strTargetFrameName, CArray<BYTE>& baPostedData, const CString& strHeaders, BOOL& bCancel) 
{
	m_strUrl = strURL;
}
void CWebappView::OnPropertyChange(const CString& strProperty) { }
void CWebappView::OnNewWindow2(IDispatch** ppDisp, BOOL& bCancel) 
{
	/*CComQIPtr<IHTMLDocument2> spDocument = GetDocument();

	CComPtr<IHTMLElement> spElement;
	spDocument->get_activeElement(&spElement);
	if (spElement) {
		//variant_t url;
		CComVariant url;
		if (SUCCEEDED(spElement->getAttribute(CComBSTR(_T("href")), 0, &url))) {
			//Navigate2(url, NULL, NULL, NULL, NULL);
			//BSTR bstrval;
			//url.CopyTo(&bstrval);
			//Navigate2(bstrval, NULL, NULL, NULL, NULL);
			if(SUCCEEDED(m_spBrowser->Navigate2(&url, NULL, NULL, NULL, NULL))) {
				bCancel=TRUE;
			}
			url.Clear();
		}
	} */
	if (!bCancel) {
		//Navigate2(m_strUrl, NULL, NULL, NULL, NULL);
		bCancel=TRUE;
	}
}

void CWebappView::OnDocumentComplete(IDispatch* pDisp, const CString& strURL) 
{
	//MessageBox(strURL);

	SetTimer(100, 1000);
}
void CWebappView::OnQuit() { }
void CWebappView::OnVisible(BOOL bVisible) { }
void CWebappView::OnToolBar(BOOL bToolBar) { }
void CWebappView::OnMenuBar(BOOL bMenuBar) { }
void CWebappView::OnStatusBar(BOOL bStatusBar) { }
void CWebappView::OnFullScreen(BOOL bFullScreen) { }
void CWebappView::OnTheaterMode(BOOL bTheaterMode) { }

void CWebappView::OnStateConnecting() { }
void CWebappView::OnStateDownloading() { }
void CWebappView::OnStateCompleted() { }
