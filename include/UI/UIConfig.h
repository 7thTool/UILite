
#pragma once

#ifndef _H_UICONFIG_H_
#define _H_UICONFIG_H_ 

#define BEGIN_ATTRIBUTE_MAP(theClass) \
    LRESULT SetAttributeString(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0) \
    { \
		LRESULT lRes = 0; 

#define CHAIN_ATTRIBUTE_OBJECT(obj) \
		if ((lRes = obj.SetAttributeString(lpszAttr, lpszValue, uFlags))) { \
			return lRes; \
		} else 

#define CHAIN_ATTRIBUTE_OBJECTPTR(objptr) \
		if ((lRes = objptr->SetAttributeString(lpszAttr, lpszValue, uFlags))) { \
			return lRes; \
		} else 

#define CHAIN_ATTRIBUTE_HANDLER(func) \
		if ((lRes = func(lpszAttr, lpszValue, uFlags))) { \
			return lRes; \
		} else 

#define CHAIN_ATTRIBUTE_MAP(classname) \
		if ((lRes = classname::SetAttributeString(lpszAttr, lpszValue, uFlags))) { \
			return lRes; \
		} else

// LRESULT OnAttribute(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
#define ATTRIBUTE_HANDLER(name, func) \
		if (_tcsicmp(name, lpszAttr)==0) { \
			lRes = func(lpszAttr, lpszValue, uFlags); \
		} else 

// str = str
#define ATTRIBUTE_STRING(name, str) \
		if (_tcsicmp(name, lpszAttr)==0) { \
			str = lpszValue; \
			lRes = TRUE; \
		} else 

// val = val
#define ATTRIBUTE_VALUE(name, type, val) \
		if (_tcsicmp(name, lpszAttr)==0) { \
			val = data_cast<type>(std::tstring(lpszValue)); \
			lRes = TRUE; \
		} else 

#define ATTRIBUTE_VALUE_HANDLER(name, type, func) \
		if (_tcsicmp(name, lpszAttr)==0) { \
			func(data_cast<type>(std::tstring(lpszValue))); \
			lRes = TRUE; \
		} else 

#define ATTRIBUTE_VALUE_POINTER(name, type, ptr) \
		if (_tcsicmp(name, lpszAttr)==0) { \
			ptr = (type*)data_cast<long>(std::tstring(lpszValue)); \
			lRes = TRUE; \
		} else 

// COLORREF = "r,g,b"
#define ATTRIBUTE_COLORREF(name, val) \
		if (_tcsicmp(name, lpszAttr)==0) { \
			val = _COLORREF(lpszValue); \
			lRes = TRUE; \
		} else 

// RECT = "l,t,r,b"
#define ATTRIBUTE_RECT(name, val) \
		if (_tcsicmp(name, lpszAttr)==0) { \
			val = _RECT(lpszValue); \
			lRes = TRUE; \
		} else 

#define END_ATTRIBUTE_MAP() \
		return 0L; \
		return lRes; \
    } 

//////////////////////////////////////////////////////////////////////////
/*
class UIConfig
{
public:
	LRESULT SetAttributeString(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0);
	LRESULT GetAttributeString(LPCTSTR lpszAttr, LPCTSTR lpszValue, int nValueLen, UINT uFlags = 0);
};*/

#endif//_H_UICONFIG_H_