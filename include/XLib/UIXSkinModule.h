#ifndef _H_UIXSKINMODULE_H_
#define _H_UIXSKINMODULE_H_

#include "UILite.h"
#include "UIXSkin.h"

//////////////////////////////////////////////////////////////////////////

enum
{
	UX_RES_NONE = 0,
	UX_RES_IMAGELIST,
	UX_RES_IMAGE,
	UX_RES_BITMAP,
	UX_RES_BRUSH,
	UX_RES_FONT,
	UX_RES_COLORREF,
	UX_RES_RECT,
	UX_RES_STRING,
};

#define UIX_SKIN_ROOT	_T("root")

class UILITE_API UIXSkinModule : public UISkinManager
{
public:
	UIXSkinModule();
	~UIXSkinModule();

	long Init();
	void Term();
	
public:
	BOOL LoadSkin(LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE, LPCTSTR lpszRoot = UIX_SKIN_ROOT);
	virtual BOOL LoadElement(LPCTSTR lpszElement, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE);
	virtual BOOL LoadAttribute(LPCTSTR lpszElement, LPCTSTR lpszName, LPCTSTR lpszAttr, LPCTSTR lpszValue);

protected:
	BOOL ParseSkinResType(LPCTSTR lpszString, int& nResType);
};

#endif//