#ifndef _H_WTLVC6SCRIPT_H_
#define _H_WTLVC6SCRIPT_H_

#include <UI/UIScript.h>

/////////////////////////////////////////////////////////////////////////////

class MyWin : public UIAxDispatch
{
public:
	enum {itemCaption,itemColor,itemMoveTo};
	static wchar_t Name[];

	// IDispatch
	STDMETHOD(GetIDsOfNames)(REFIID riid,LPOLESTR *rgszNames,UINT cNames,LCID lcid,DISPID *rgDispId)
	{
		if(lstrcmpW(rgszNames[0],L"Caption") == 0)
		{
			*rgDispId = itemCaption;
		}
		else if(lstrcmpW(rgszNames[0],L"Color") == 0)
		{
			*rgDispId = itemColor;
		}
		else if(lstrcmpW(rgszNames[0],L"MoveTo") == 0)
		{
			*rgDispId = itemMoveTo;
		}
		else
			return E_NOTIMPL;
		return S_OK;
	}

	STDMETHOD(Invoke)(DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,EXCEPINFO *pExcepInfo,UINT *puArgErr)
	{
		switch(dispIdMember)
		{
		case itemCaption:
			{
				if(wFlags==DISPATCH_PROPERTYGET)
				{
					pVarResult->vt = VT_BSTR;
					pVarResult->bstrVal = GetCaption();
				}
				else if(wFlags==DISPATCH_PROPERTYPUT)
				{
					if(pDispParams->cArgs!=1) return DISP_E_BADPARAMCOUNT;
					if(pDispParams->rgvarg[0].vt != VT_BSTR) {
						*puArgErr = 0;
						return DISP_E_TYPEMISMATCH;
					}
					SetCaption(pDispParams->rgvarg[0].bstrVal);
				}
				else
					return DISP_E_MEMBERNOTFOUND;
				break;
			}
		case itemColor:
			{
				if(wFlags==DISPATCH_PROPERTYGET)
				{
					pVarResult->vt = VT_I4;
					pVarResult->intVal = GetColor();
				}
				else if(wFlags==DISPATCH_PROPERTYPUT)
				{
					if(pDispParams->cArgs!=1) return DISP_E_BADPARAMCOUNT;
					if(pDispParams->rgvarg[0].vt != VT_I4) {
						*puArgErr = 0;
						return DISP_E_TYPEMISMATCH;
					}
					SetColor(pDispParams->rgvarg[0].intVal);
				}
				else
					return DISP_E_MEMBERNOTFOUND;
				break;
			}
		case itemMoveTo:
			{
				if(wFlags==DISPATCH_METHOD)
				{
					if(pDispParams->cArgs!=2) return DISP_E_BADPARAMCOUNT;
					if(pDispParams->rgvarg[0].vt != VT_I4) {
						*puArgErr = 0;
						return DISP_E_TYPEMISMATCH;
					}
					else if(pDispParams->rgvarg[1].vt != VT_I4){
						*puArgErr = 1;
						return DISP_E_TYPEMISMATCH;
					}
					MoveTo( pDispParams->rgvarg[1].intVal,
						pDispParams->rgvarg[0].intVal);
				}
				else
					return DISP_E_MEMBERNOTFOUND;
				break;
			}
		default:
			return DISP_E_MEMBERNOTFOUND;
		}
		return S_OK;
	}

	// MyWin
	MyWin(HWND hWnd) : UIAxDispatch(),m_Wnd(hWnd)
	{
	}
	BSTR GetCaption()
	{
		return NULL;
	}
	void SetCaption(BSTR bstrCaption)
	{
		if (m_Wnd)
		{
			::SetWindowText(m_Wnd,bstrCaption);
		}
	}
	int GetColor()
	{
		return 0;
	}
	void SetColor(int iColor)
	{

	}
	void MoveTo(int X,int Y)
	{

	}

private:
	UIWnd m_Wnd;
};

wchar_t MyWin::Name[] = L"MyWin";

class MyGlobalFunc : public UIAxDispatch 
{
public:
	enum {itemScreenWidth,itemScreenHeight,itemSleep};
	static wchar_t Name[];

	STDMETHOD(GetIDsOfNames)(REFIID riid,LPOLESTR *rgszNames,UINT cNames,LCID lcid, DISPID *rgDispId)
	{
		if(lstrcmpW(rgszNames[0],L"ScreenWidth") == 0)
		{
			*rgDispId = itemScreenWidth;
		}
		else if(lstrcmpW(rgszNames[0],L"ScreenHeight") == 0)
		{
			*rgDispId = itemScreenHeight;
		}
		else if(lstrcmpW(rgszNames[0],L"Sleep") == 0)
		{
			*rgDispId = itemSleep;
		}
		else
			return E_NOTIMPL;
		return S_OK;
	}

	STDMETHOD(Invoke)(DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,EXCEPINFO *pExcepInfo,UINT *puArgErr)
	{
		switch(dispIdMember)
		{
		case itemScreenWidth:
			pVarResult->vt=VT_I4;
			pVarResult->intVal = 800;
			break;
		case itemScreenHeight:
			pVarResult->vt=VT_I4;
			pVarResult->intVal = 400;
			break;
		case itemSleep:
			if(pDispParams->cArgs!=1) 
				return DISP_E_BADPARAMCOUNT;
			if(pDispParams->rgvarg[0].vt != VT_I4) {
				*puArgErr = 0;
				return DISP_E_TYPEMISMATCH;
			}
			//Application->ProcessMessages();
			Sleep(pDispParams->rgvarg[0].intVal);
			break;
		default:
			return DISP_E_MEMBERNOTFOUND;
		}
		return S_OK;
	}
};

wchar_t MyGlobalFunc::Name[]=L"MyGlobalFunc";

class MyActiveScriptSiteWindow 
	: public UIWnd
	, public IActiveScriptSiteWindow
{
protected:
	DWORD m_dwRef; // 引用计数
public:
	MyActiveScriptSiteWindow(HWND hWnd = NULL) : UIWnd(hWnd), m_dwRef(0)
	{}
	virtual ~MyActiveScriptSiteWindow() 
	{
		ASSERT(m_dwRef == 0);
	}

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
	{
		*ppv = NULL;
		if(riid == IID_IActiveScriptSiteWindow) {
			*ppv = this;
		} else if (IID_IUnknown==riid) {
			*ppv = this;
		}
		if (*ppv) {
			((LPUNKNOWN)*ppv)->AddRef();
			return S_OK; 
		}
		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG) AddRef(void)
	{
		return ++m_dwRef;
	}

	STDMETHODIMP_(ULONG) Release(void)
	{
		if(--m_dwRef == 0) {
			delete this;
			return 0;
		}
		return m_dwRef;
	}

	STDMETHOD(GetWindow)(HWND *phwnd)
	{
		*phwnd = m_hWnd;
		return S_OK;
	}

	STDMETHOD(EnableModeless)(BOOL fEnable)
	{
		return S_OK;
	}
};

class MyActiveScriptSite : public IActiveScriptSite
{
protected:
	ULONG m_nRef;
	CComQIPtr<IActiveScriptSiteWindow> m_spWindow;
	typedef std::map<CString,CComQIPtr<IDispatch>,CStringNoCaseLess> Name2spIDispatch;
	Name2spIDispatch m_name2spDisp;
public:
	MyActiveScriptSite() : m_nRef(0) { }
	virtual ~MyActiveScriptSite() 
	{ 
		ASSERT(m_nRef==0); 
	}

	// 
	//
	HRESULT SetWindow(HWND hWnd)
	{
		m_spWindow = new MyActiveScriptSiteWindow(hWnd);
		return S_OK;
	}

	HRESULT AddFunc(LPOLESTR lpszName, IDispatch* pDisp)
	{
		m_name2spDisp[lpszName] = pDisp;
		return S_OK;
	}

	HRESULT RemoveFunc(LPOLESTR lpszName, IDispatch** ppDisp)
	{
		Name2spIDispatch::iterator it = m_name2spDisp.find(lpszName);
		if(it != m_name2spDisp.end()) {
			*ppDisp = it->second;
			return S_OK;
		}
		return E_FAIL;
	}

	// IUNKnown
	STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
	{
		*ppv = NULL;
		if(riid == IID_IActiveScriptSite) {
			*ppv=this;
		} else if (riid == IID_IActiveScriptSiteWindow) {
			*ppv = (IActiveScriptSiteWindow*)m_spWindow;
		} else if (riid == IID_IUnknown) {
			*ppv=this;
		} 
		if (*ppv) {
			((LPUNKNOWN)*ppv)->AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}
	STDMETHODIMP_(ULONG) AddRef(void)
	{
		return ++m_nRef;
	}
	STDMETHODIMP_(ULONG) Release(void) 
	{
		if(--m_nRef==0) {
			delete this;
			return 0;
		}
		return m_nRef;
	}

	// IActiveScriptSite
	STDMETHOD(GetLCID)(LCID* /*plcid*/) 
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetItemInfo)(LPCOLESTR pstrName, DWORD dwReturnMask, IUnknown** ppiunkItem, ITypeInfo** ppti) 
	{
		if( (dwReturnMask & SCRIPTINFO_ITYPEINFO)!=0 )
		{
			*ppti = NULL;
			return E_FAIL;
		}
		if( (dwReturnMask & SCRIPTINFO_IUNKNOWN)==0 ) 
			return E_FAIL;
		if( ppiunkItem==NULL ) 
			return E_POINTER;
		*ppiunkItem = NULL;
		Name2spIDispatch::iterator it = m_name2spDisp.find(pstrName);
		if(it != m_name2spDisp.end()) {
			IDispatch* pDisp = it->second;
			pDisp->AddRef();
			*ppiunkItem = it->second;
			return S_OK;
		}
		return E_FAIL;
	}

	STDMETHOD(GetDocVersionString)(BSTR* pbstrVersion) 
	{
		if( pbstrVersion==NULL ) 
			return E_POINTER;
		*pbstrVersion = ::SysAllocString(OLESTR("UI Script 1.0"));
		return S_OK;
	}

	STDMETHOD(OnScriptTerminate)( const VARIANT* /*pvarResult*/, const EXCEPINFO* /*pexcepinfo*/) 
	{
		m_name2spDisp.clear();
		return S_OK;
	}

	STDMETHOD(OnStateChange)(SCRIPTSTATE /*ssScriptState*/) 
	{
		return S_OK;
	}

	STDMETHOD(OnScriptError)(IActiveScriptError* pScriptError) 
	{
		EXCEPINFO e;
		DWORD dwContext;
		ULONG ulLine;
		LONG lPos;
		pScriptError->GetExceptionInfo(&e);
		pScriptError->GetSourcePosition(&dwContext, &ulLine, &lPos);
		TCHAR szFormat[] = _T("An error occured while parsing script: Source: %ws Error: %08X Description: %ws Line: %d");
		TCHAR szMsg[1024];
		::_stprintf(szMsg, szFormat,
			e.bstrSource,
			e.scode,
			e.bstrDescription,
			ulLine+1);
		::MessageBox(::GetActiveWindow(), szMsg, _T("Compile Error"), MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return S_OK;
	}

	STDMETHOD(OnEnterScript)() 
	{
		return S_OK;
	}

	STDMETHOD(OnLeaveScript)() 
	{
		return S_OK;
	}
};

////////////////////////////////////////////////////////////////////////////////////////
//TEST SCRIPT

//class CScriptHost
//	: public UIWnd
//	, public UIAxScriptHostT<CScriptHost>
//{
//public:
//	CScriptHost()
//	{
//		m_spASS = new UIAxInnerScriptSite(this);
//		m_spASSW = new UIAxInnerScriptSiteWindow(this);
//	}
//};

void Test(HWND hWnd)
{
	CComQIPtr<IActiveScript> spAS;
	spAS.CoCreateInstance(L"JScript");
	//spAS.CoCreateInstance(L"VBScript");
	if(!spAS) return;

	CComQIPtr<IActiveScriptParse> spASP(spAS);
	if(!spASP) 
		return;

	spASP->InitNew();

	CComQIPtr<IDispatch> spDispatch_MyWin = new MyWin(hWnd);
	CComQIPtr<IDispatch> spDispatch_MyGlobalFunc = new MyGlobalFunc;
	CComQIPtr<IActiveScriptSite> spActiveScriptSite_My = new MyActiveScriptSite();
	((MyActiveScriptSite*)(IActiveScriptSite*)spActiveScriptSite_My)->SetWindow(hWnd);
	((MyActiveScriptSite*)(IActiveScriptSite*)spActiveScriptSite_My)->AddFunc(MyWin::Name, spDispatch_MyWin);
	((MyActiveScriptSite*)(IActiveScriptSite*)spActiveScriptSite_My)->AddFunc(MyGlobalFunc::Name, spDispatch_MyGlobalFunc);
	
	spAS->SetScriptSite(spActiveScriptSite_My);

	spAS->AddNamedItem(MyWin::Name,SCRIPTITEM_ISVISIBLE);
	spAS->AddNamedItem(MyGlobalFunc::Name,SCRIPTITEM_ISVISIBLE|SCRIPTITEM_GLOBALMEMBERS);

	TCHAR szJScript[] = _T("var bForward = true;\
						   for(var i=0;i<ScreenWidth-200;i+=100) \
						   { \
							   for(var j=0;j<ScreenHeight-200;j+=10) \
							   { \
								   var x = i; \
								   var y = bForward ? j : (ScreenHeight-200-j); \
								   MyWin.MoveTo(x,y); \
								   MyWin.Caption = \"X:\" + x + \" Y:\"+y; \
								   MyWin.Color = (x<<16|y)&0xffffff; \
								   Sleep(10); \
							   } \
							   bForward = !bForward; \
						   }");
	TCHAR szVBScript[] = L"dim strmsg\n \
						  strmsg = \"szVBScript\"\n \
						  msgbox strmsg\n \
						  ";
	spASP->ParseScriptText(
		szJScript,
		//szVBScript,
		NULL,
		NULL,
		NULL,
		0,
		0,
		0,
		NULL,
		NULL);
	spAS->SetScriptState(SCRIPTSTATE_STARTED);

	spAS->Close();

	//CScriptHost ScriptHost;
	//ScriptHost.ExecuteScript(szVBScript, NULL, L"VBScript");
}

#endif//_H_WTLVC6SCRIPT_H_