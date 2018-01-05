#ifndef _H_UIXPANE2_H_
#define _H_UIXPANE2_H_

#include "UIXPane.h"
#include "UIXWnd2.h"

class UIXPane2 : public UIXPaneT<UIXPane2,UIWnd2>
{
	typedef UIXPane2 This;
	typedef UIXPaneT<UIXPane2,UIWnd2> Base;
	typedef UIXPane2 Pane;
protected:

public:
	UIXPane2(HWND hWnd = NULL) : Base(hWnd)
	{

	}

	// 	~UIXPane2()
	// 	{
	// 		
	// 	}
};

#endif//_H_UIXPANE2_H_