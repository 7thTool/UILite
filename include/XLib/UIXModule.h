#ifndef _H_UIXMLSKINMODULE_H_
#define _H_UIXMLSKINMODULE_H_

#ifndef _AFX
#include "UIXWndModule.h"
#include "UIXSkinModule.h"

class UILITE_API UIXModuleBase
	: public UIXWndModule
	, public UIXSkinModule
{
public:
	long Init();
	void Term();
};
#else
#include "UIXSkinModule.h"

class UILITE_API UIXModuleBase 
	: public UIXSkinModule
{
public:
	long Init();
	void Term();
};
#endif//

template<class T>
class UIXModuleT : public UIXModuleBase
{
	typedef UIXModuleT<T> This;
	typedef UIXModuleBase Base;
public:
};

#endif//_H_UIXMLSKINMODULE_H_