#pragma once

#ifndef _H_UICOM_H_
#define _H_UICOM_H_

#include "UIWnd.h"

//////////////////////////////////////////////////////////////////////////
//传递给 Create 函数的窗口标题（第三个参数）是一个标识要创建的控件的字符串
//该字符串可以是一个 CLSID（带有大括号）、ProgID、URL 或原始 HTML（以 MSHTML: 为前缀）
//如果提供了 URL 或原始 HTML，则 Web 浏览器将与此信息一起加载
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

inline void UICheckError(SCODE sc)
{
	if (FAILED(sc)) {
		if (sc == E_OUTOFMEMORY)
			ATLTRACE2(atlTraceCOM, 0, "UICheckError Error : OOM\n");
		else
			ATLTRACE2(atlTraceCOM, 0, "UICheckError Error : MISC\n");
	}
}

typedef const SAFEARRAY* LPCSAFEARRAY;
typedef const VARIANT* LPCVARIANT;

inline void UIInitVariantFromItemIDList(CComVariant& v, LPCITEMIDLIST pidl)
{
	if (pidl != NULL)
	{
		// walk through entries in the list and accumulate their size

		UINT cbTotal = 0;
		SAFEARRAY *psa = NULL;
		LPCITEMIDLIST pidlWalker = pidl;

		while (pidlWalker->mkid.cb)
		{
			cbTotal += pidlWalker->mkid.cb;
			pidlWalker = (LPCITEMIDLIST)
				(((LPBYTE)pidlWalker) + pidlWalker->mkid.cb);
		}

		// add the base structure size
		cbTotal += sizeof(ITEMIDLIST);

		// get a safe array for them
		psa = ::SafeArrayCreateVector(VT_UI1, 0, cbTotal);

		// copy it and set members
		if (psa != NULL)
		{
			::memcpy(psa->pvData, (LPBYTE) pidl, cbTotal);
			v.vt = VT_ARRAY | VT_UI1;
			v.parray = psa;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CComSafeArray class
class CComSafeArray : public tagVARIANT
{
public:
	/////////////////////////////////////////////////////////////////////////////
	// Helper for initializing CComSafeArray
	static bool _UICompareSafeArrays(SAFEARRAY* parray1, SAFEARRAY* parray2)
	{
		bool bCompare = false;

		// If one is NULL they must both be NULL to compare
		if (parray1 == NULL || parray2 == NULL)
		{
			return parray1 == parray2;
		}

		// Dimension must match and if 0, then arrays compare
		DWORD dwDim1 = ::SafeArrayGetDim(parray1);
		DWORD dwDim2 = ::SafeArrayGetDim(parray2);
		if (dwDim1 != dwDim2)
			return false;
		else if (dwDim1 == 0)
			return true;

		// Element size must match
		DWORD dwSize1 = ::SafeArrayGetElemsize(parray1);
		DWORD dwSize2 = ::SafeArrayGetElemsize(parray2);
		if (dwSize1 != dwSize2)
			return false;

		long* pLBound1 = NULL;
		long* pLBound2 = NULL;
		long* pUBound1 = NULL;
		long* pUBound2 = NULL;

		void* pData1 = NULL;
		void* pData2 = NULL;

		// Bounds must match
		ATLTRY(pLBound1 = new long[dwDim1]);
		ATLTRY(pLBound2 = new long[dwDim2]);
		ATLTRY(pUBound1 = new long[dwDim1]);
		ATLTRY(pUBound2 = new long[dwDim2]);

		size_t nTotalElements = 1;

		// Get and compare bounds
		for (DWORD dwIndex = 0; dwIndex < dwDim1; dwIndex++)
		{
			UICheckError(::SafeArrayGetLBound(
				parray1, dwIndex+1, &pLBound1[dwIndex]));
			UICheckError(::SafeArrayGetLBound(
				parray2, dwIndex+1, &pLBound2[dwIndex]));
			UICheckError(::SafeArrayGetUBound(
				parray1, dwIndex+1, &pUBound1[dwIndex]));
			UICheckError(::SafeArrayGetUBound(
				parray2, dwIndex+1, &pUBound2[dwIndex]));

			// Check the magnitude of each bound
			if (pUBound1[dwIndex] - pLBound1[dwIndex] !=
				pUBound2[dwIndex] - pLBound2[dwIndex])
			{
				delete[] pLBound1;
				delete[] pLBound2;
				delete[] pUBound1;
				delete[] pUBound2;

				return false;
			}

			// Increment the element count
			nTotalElements *= pUBound1[dwIndex] - pLBound1[dwIndex] + 1;
		}

		// Access the data
		UICheckError(::SafeArrayAccessData(parray1, &pData1));
		UICheckError(::SafeArrayAccessData(parray2, &pData2));

		// Calculate the number of bytes of data and compare
		size_t nSize = nTotalElements * dwSize1;
		int nOffset = memcmp(pData1, pData2, nSize);
		bCompare = (nOffset == 0);

		// Release the array locks
		UICheckError(::SafeArrayUnaccessData(parray1));
		UICheckError(::SafeArrayUnaccessData(parray2));

		// Clean up bounds arrays
		delete[] pLBound1;
		delete[] pLBound2;
		delete[] pUBound1;
		delete[] pUBound2;

		return bCompare;
	}
public:
	// Data members
	// Cache info to make element access (operator []) faster
	DWORD m_dwElementSize;
	DWORD m_dwDims;

	//Constructors
	CComSafeArray()
	{
		_SafeArrayInit(this);
		vt = VT_EMPTY;
	}

	~CComSafeArray()
	{
		Clear();
	}	

	CComSafeArray(const SAFEARRAY& saSrc, VARTYPE vtSrc)
	{
		_SafeArrayInit(this);
		vt = (VARTYPE)(vtSrc | VT_ARRAY);
		UICheckError(::SafeArrayCopy((LPSAFEARRAY)&saSrc, &parray));
		m_dwDims = GetDim();
		m_dwElementSize = GetElemSize();
	}

	CComSafeArray(LPCSAFEARRAY pSrc, VARTYPE vtSrc)
	{
		_SafeArrayInit(this);
		vt = (VARTYPE)(vtSrc | VT_ARRAY);
		UICheckError(::SafeArrayCopy((LPSAFEARRAY)pSrc, &parray));
		m_dwDims = GetDim();
		m_dwElementSize = GetElemSize();
	}

	CComSafeArray(const CComSafeArray& saSrc)
	{
		_SafeArrayInit(this);
		*this = saSrc;
		m_dwDims = GetDim();
		m_dwElementSize = GetElemSize();
	}

	CComSafeArray(const VARIANT& varSrc)
	{
		_SafeArrayInit(this);
		*this = varSrc;
		m_dwDims = GetDim();
		m_dwElementSize = GetElemSize();
	}

	CComSafeArray(LPCVARIANT pSrc)
	{
		_SafeArrayInit(this);
		*this = pSrc;
		m_dwDims = GetDim();
		m_dwElementSize = GetElemSize();
	}

	void _SafeArrayInit(CComSafeArray* psa)
	{
		::memset(psa, 0, sizeof(*psa));
	}

	void Clear()
	{
		VERIFY(::VariantClear(this) == NOERROR);
	}

	operator LPVARIANT()
	{
		return this;
	}

	operator LPCVARIANT() const
	{
		return this;
	}

	DWORD GetDim()
	{
		return ::SafeArrayGetDim(parray);
	}

	DWORD GetElemSize()
	{
		return ::SafeArrayGetElemsize(parray);
	}

	// Operations
	void Attach(VARIANT& varSrc)
	{
		ATLASSERT(varSrc.vt & VT_ARRAY);

		// Free up previous safe array if necessary
		Clear();

		// give control of data to CComSafeArray
		::memcpy(this, &varSrc, sizeof(varSrc));
		varSrc.vt = VT_EMPTY;
	}

	VARIANT Detach()
	{
		VARIANT varResult = *this;
		vt = VT_EMPTY;
		return varResult;
	}

	// Assignment operators
	CComSafeArray& operator=(const CComSafeArray& saSrc)
	{
		ATLASSERT(saSrc.vt & VT_ARRAY);

		UICheckError(::VariantCopy(this, (LPVARIANT)&saSrc));
		return *this;
	}

	CComSafeArray& operator=(const VARIANT& varSrc)
	{
		ATLASSERT(varSrc.vt & VT_ARRAY);

		UICheckError(::VariantCopy(this, (LPVARIANT)&varSrc));
		return *this;
	}

	CComSafeArray& operator=(LPCVARIANT pSrc)
	{
		ATLASSERT(pSrc->vt & VT_ARRAY);

		UICheckError(::VariantCopy(this, (LPVARIANT)pSrc));
		return *this;
	}

	CComSafeArray& operator=(const CComVariant& varSrc)
	{
		ATLASSERT(varSrc.vt & VT_ARRAY);

		UICheckError(::VariantCopy(this, (LPVARIANT)&varSrc));
		return *this;
	}

	// Comparison operators
	bool operator==(const SAFEARRAY& saSrc) const
	{
		return _UICompareSafeArrays(parray, (LPSAFEARRAY)&saSrc);
	}

	bool operator==(LPCSAFEARRAY pSrc) const
	{
		return _UICompareSafeArrays(parray, (LPSAFEARRAY)pSrc);
	}

	bool operator==(const CComSafeArray& saSrc) const
	{
		if (vt != saSrc.vt)
			return false;

		return _UICompareSafeArrays(parray, saSrc.parray);
	}

	bool operator==(const VARIANT& varSrc) const
	{
		if (vt != varSrc.vt)
			return false;

		return _UICompareSafeArrays(parray, varSrc.parray);
	}

	bool operator==(LPCVARIANT pSrc) const
	{
		if (vt != pSrc->vt)
			return false;

		return _UICompareSafeArrays(parray, pSrc->parray);
	}

	bool operator==(const CComVariant& varSrc) const
	{
		if (vt != varSrc.vt)
			return false;

		return _UICompareSafeArrays(parray, varSrc.parray);
	}

	void CreateOneDim(VARTYPE vtSrc, DWORD dwElements,
		const void* pvSrcData = NULL, long nLBound = 0)
	{
		ATLASSERT(dwElements > 0);

		// Setup the bounds and create the array
		SAFEARRAYBOUND rgsabound;
		rgsabound.cElements = dwElements;
		rgsabound.lLbound = nLBound;
		Create(vtSrc, 1, &rgsabound);

		// Copy over the data if neccessary
		if (pvSrcData != NULL)
		{
			void* pvDestData;
			AccessData(&pvDestData);
			memcpy(pvDestData, pvSrcData, GetElemSize() * dwElements);
			UnaccessData();
		}
	}

	DWORD GetOneDimSize()
	{
		ATLASSERT(GetDim() == 1);

		long nUBound, nLBound;

		GetUBound(1, &nUBound);
		GetLBound(1, &nLBound);

		return nUBound + 1 - nLBound;
	}

	void ResizeOneDim(DWORD dwElements)
	{
		ATLASSERT(GetDim() == 1);

		SAFEARRAYBOUND rgsabound;

		rgsabound.cElements = dwElements;
		rgsabound.lLbound = 0;

		Redim(&rgsabound);
	}

	void Create(VARTYPE vtSrc, DWORD dwDims, DWORD* rgElements)
	{
		ATLASSERT(rgElements != NULL);

		// Allocate and fill proxy array of bounds (with lower bound of zero)
		SAFEARRAYBOUND* rgsaBounds = new SAFEARRAYBOUND[dwDims];

		for (DWORD dwIndex = 0; dwIndex < dwDims; dwIndex++)
		{
			// Assume lower bound is 0 and fill in element count
			rgsaBounds[dwIndex].lLbound = 0;
			rgsaBounds[dwIndex].cElements = rgElements[dwIndex];
		}

		Create(vtSrc, dwDims, rgsaBounds);
		delete[] rgsaBounds;
	}

	void Create(VARTYPE vtSrc, DWORD dwDims, SAFEARRAYBOUND* rgsabound)
	{
		ATLASSERT(dwDims > 0);
		ATLASSERT(rgsabound != NULL);

		// Validate the VARTYPE for SafeArrayCreate call
		ATLASSERT(!(vtSrc & VT_ARRAY));
		ATLASSERT(!(vtSrc & VT_BYREF));
		ATLASSERT(!(vtSrc & VT_VECTOR));
		ATLASSERT(vtSrc != VT_EMPTY);
		ATLASSERT(vtSrc != VT_NULL);

		// Free up old safe array if necessary
		Clear();

		ATLTRY(parray = ::SafeArrayCreate(vtSrc, dwDims, rgsabound));
		if (parray == NULL)
		{
			ATLTRACE2(atlTraceDBProvider, 0, "CComSafeArray::Create Error : OOM\n");
			return;
		}

		vt = unsigned short(vtSrc | VT_ARRAY);
		m_dwDims = dwDims;
		m_dwElementSize = GetElemSize();
	}

	void AccessData(void** ppvData)
	{
		UICheckError(::SafeArrayAccessData(parray, ppvData));
	}

	void UnaccessData()
	{
		UICheckError(::SafeArrayUnaccessData(parray));
	}

	void AllocData()
	{
		UICheckError(::SafeArrayAllocData(parray));
	}

	void AllocDescriptor(DWORD dwDims)
	{
		UICheckError(::SafeArrayAllocDescriptor(dwDims, &parray));
	}

	void Copy(LPSAFEARRAY* ppsa)
	{
		UICheckError(::SafeArrayCopy(parray, ppsa));
	}

	void GetLBound(DWORD dwDim, long* pLbound)
	{
		UICheckError(::SafeArrayGetLBound(parray, dwDim, pLbound));
	}

	void GetUBound(DWORD dwDim, long* pUbound)
	{
		UICheckError(::SafeArrayGetUBound(parray, dwDim, pUbound));
	}

	void GetElement(long* rgIndices, void* pvData)
	{
		UICheckError(::SafeArrayGetElement(parray, rgIndices, pvData));
	}

	void PtrOfIndex(long* rgIndices, void** ppvData)
	{
		UICheckError(::SafeArrayPtrOfIndex(parray, rgIndices, ppvData));
	}

	void PutElement(long* rgIndices, void* pvData)
	{
		UICheckError(::SafeArrayPutElement(parray, rgIndices, pvData));
	}

	void Redim(SAFEARRAYBOUND* psaboundNew)
	{
		UICheckError(::SafeArrayRedim(parray, psaboundNew));
	}

	void Lock()
	{
		UICheckError(::SafeArrayLock(parray));
	}

	void Unlock()
	{
		UICheckError(::SafeArrayUnlock(parray));
	}

	void Destroy()
	{
		UICheckError(::SafeArrayDestroy(parray));
	}

	void DestroyData()
	{
		UICheckError(::SafeArrayDestroyData(parray));
	}

	void DestroyDescriptor()
	{
		UICheckError(::SafeArrayDestroyDescriptor(parray));
	}
};

//////////////////////////////////////////////////////////////////////////

class UIAxDispatch : public IDispatch
{
protected:
	ULONG	m_nRef;
public:
	UIAxDispatch():m_nRef(0) {}
	virtual ~UIAxDispatch() 
	{
		ASSERT(m_nRef==0); 
	}

public:
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{
		*ppv = NULL;
		if (IID_IDispatch == riid) {
			*ppv = this;
		} else if (IID_IUnknown==riid) {
			*ppv = this;
		}
		if (NULL != *ppv) {
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

	//IDispatch
	STDMETHODIMP GetTypeInfoCount(UINT* pctinfo)
	{
		return E_NOTIMPL;
	}
	STDMETHODIMP GetTypeInfo(/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ ITypeInfo** ppTInfo)
	{
		return E_NOTIMPL;
	}
	STDMETHODIMP GetIDsOfNames(
		/* [in] */ REFIID riid,
		/* [size_is][in] */ LPOLESTR *rgszNames,
		/* [in] */ UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ DISPID *rgDispId)
	{
		for (UINT i = 0; i < cNames; i++) {
			rgDispId[i] = DISPID_UNKNOWN;
		}
		return ResultFromScode(DISP_E_UNKNOWNNAME);
	}
	STDMETHODIMP Invoke(
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS  *pDispParams,
		/* [out] */ VARIANT  *pVarResult,
		/* [out] */ EXCEPINFO *pExcepInfo,
		/* [out] */ UINT *puArgErr)
	{
		return S_OK;
	}
};

////////////////////////////////////////////////////////////////////////////

class UIAxFrameWindow : public CAxFrameWindow
{
public:
	UIAxFrameWindow():CAxFrameWindow(){}
};

class UIAxUIWindow : public CAxUIWindow
{
public:
	UIAxUIWindow():CAxUIWindow(){}
};

class UIAxHostWindow : public CAxHostWindow
{
public:
	UIAxHostWindow():CAxHostWindow(){}
};

template <class T>
class UIAxHostExternal
{
	typedef UIAxHostExternal<T> This;
protected:
	class UIAxExternal : public IDispatch
	{
	protected:
		ULONG	m_cRef;
		T*		m_pHost;	
	public:
		UIAxExternal(T* pHost = NULL):m_cRef(0),m_pHost(pHost) {}
		~UIAxExternal(){ASSERT(m_cRef==0);}
	public:
		STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
		{
			*ppv = NULL;
			if (IID_IDispatch == riid) {
				*ppv = this;
			}
			if (NULL != *ppv) {
				((LPUNKNOWN)*ppv)->AddRef();
				return NOERROR;
			}
			return E_NOINTERFACE;
		}
		STDMETHODIMP_(ULONG) AddRef(void)
		{
			return ++m_cRef;
		}
		STDMETHODIMP_(ULONG) Release(void)
		{
			return --m_cRef;
		}

		//IDispatch
		STDMETHODIMP GetTypeInfoCount(UINT* pctinfo)
		{
			return E_NOTIMPL;
		}
		STDMETHODIMP GetTypeInfo(/* [in] */ UINT iTInfo,
			/* [in] */ LCID lcid,
			/* [out] */ ITypeInfo** ppTInfo)
		{
			return E_NOTIMPL;
		}
		STDMETHODIMP GetIDsOfNames(
			/* [in] */ REFIID riid,
			/* [size_is][in] */ LPOLESTR *rgszNames,
			/* [in] */ UINT cNames,
			/* [in] */ LCID lcid,
			/* [size_is][out] */ DISPID *rgDispId)
		{
			if (m_pHost) {
				return m_pHost->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgDispId);
			}
			for (UINT i = 0; i < cNames; i++) {
				rgDispId[i] = DISPID_UNKNOWN;
			}
			return ResultFromScode(DISP_E_UNKNOWNNAME);
		}
		STDMETHODIMP Invoke(
			/* [in] */ DISPID dispIdMember,
			/* [in] */ REFIID riid,
			/* [in] */ LCID lcid,
			/* [in] */ WORD wFlags,
			/* [out][in] */ DISPPARAMS  *pDispParams,
			/* [out] */ VARIANT  *pVarResult,
			/* [out] */ EXCEPINFO *pExcepInfo,
			/* [out] */ UINT *puArgErr)
		{
			if (m_pHost) {
				return m_pHost->Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
			}
			return S_OK;
		}
	};
	UIAxExternal m_External;
public:
	UIAxHostExternal():m_External(static_cast<T*>(this)) {}
	~UIAxHostExternal() {}

	IDispatch* operator () () { return static_cast<IDispatch*>(&m_External); }
	IDispatch* GetExternalDispatch() { return static_cast<IDispatch*>(&m_External); }

public:
	HRESULT GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
	{
		for (UINT i = 0; i < cNames; i++) {
			rgDispId[i] = DISPID_UNKNOWN;
		}
		return ResultFromScode(DISP_E_UNKNOWNNAME);
	}

	HRESULT Invoke(DISPID dispIdMember,REFIID riid, LCID lcid,
		WORD wFlags, DISPPARAMS  *pDispParams,VARIANT  *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
	{
		return S_OK;
	}
};

template <class T, class TBase = UIWnd>
class UIAxDialogImpl : public CAxDialogImpl<T, TBase>
{
	typedef UIAxDialogImpl<T, TBase> This;
	typedef CAxDialogImpl<T, TBase> Base;
public:
	UIAxDialogImpl()
	{
	}
	BEGIN_MSG_MAP(This)
	END_MSG_MAP()
};

#endif//_H_UICOM_H_