#include "stdafx.h"
#include "UIXWnd.h"
#include <UI/UICtrl.h>

HWND CreateDefaultControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag)
{
	HWND hWndCtrl = NULL;
	BEGIN_XML_MAP(lpszWndClass)
		std::tstring strnull;
		std::tstring strval;

		std::tstring strcalssname;xml->GetName(strcalssname);

		UIWnd myCtrl;
		UINT Id = tcsto<UINT>(xml->GetAttributeString(strnull, std::tstring(_T("id")), strval), 0);
		RECT rcWnd = _RECT(xml->GetAttributeString(strnull, std::tstring(_T("rect")), strval).c_str());
		LPCTSTR lpszTitle = xml->GetAttributeString(strnull, std::tstring(_T("title")), strval).c_str();
		DWORD dwStyle = tcsto<DWORD>(xml->GetAttributeString(strnull, std::tstring(_T("style")), strval), 0);
		DWORD dwExStyle = tcsto<DWORD>(xml->GetAttributeString(strnull, std::tstring(_T("exstyle")), strval), 0);
#ifndef _AFX
		myCtrl.Create(strcalssname.c_str()
			, hWndParent
			, rcWnd
			, lpszTitle
			, dwStyle|WS_CHILD|WS_VISIBLE
			, dwExStyle
			, Id
			, NULL);
		if ((HWND)myCtrl) {
			if (_tcsicmp(strcalssname.c_str(), UIStatic::GetWndClassName()) == 0) {
				//
			} else if (_tcsicmp(strcalssname.c_str(), UIButton::GetWndClassName()) == 0) {
				if (!(myCtrl.GetStyle() & BS_PUSHBUTTON)) {
					UIButton btn((HWND)myCtrl);
					btn.SetCheck(tcsto<DWORD>(xml->GetDataString(strnull, strval), 0));
					btn.Detach();
				}
			} else if (_tcsicmp(strcalssname.c_str(), UIListBox::GetWndClassName()) == 0) {
				UIListBox lstbox((HWND)myCtrl);
				for(long cookie = xml->First(); cookie; cookie = xml->Next(cookie))
				{
					xml->IntoElem();
					lstbox.AddString(xml->GetDataString(strnull,strval).c_str());
					xml->OutofElem();
				}
				lstbox.Detach();
			} else if (_tcsicmp(strcalssname.c_str(), UIComboBox::GetWndClassName()) == 0) {
				UIComboBox cmbbox((HWND)myCtrl);
				for(long cookie = xml->First(); cookie; cookie = xml->Next(cookie))
				{
					xml->IntoElem();
					cmbbox.AddString(xml->GetDataString(strnull,strval).c_str());
					xml->OutofElem();
				}
				cmbbox.Detach();
			} else if (_tcsicmp(strcalssname.c_str(), UIListCtrl::GetWndClassName()) == 0) {
			} else if (_tcsicmp(strcalssname.c_str(), UIProgressBarCtrl::GetWndClassName()) == 0) {
			} else if (_tcsicmp(strcalssname.c_str(), UIScrollBar::GetWndClassName()) == 0) {
			} else if (_tcsicmp(strcalssname.c_str(), UIAnimateCtrl::GetWndClassName()) == 0) {
			} else if (_tcsicmp(strcalssname.c_str(), UITreeCtrl::GetWndClassName()) == 0) {
			} else if (_tcsicmp(strcalssname.c_str(), UIMonthCalendarCtrl::GetWndClassName()) == 0) {
			} else if (_tcsicmp(strcalssname.c_str(), UIDateTimePickerCtrl::GetWndClassName()) == 0) {
			}

			hWndCtrl = myCtrl.Detach();
		}
#else
		myCtrl.CreateEx(dwExStyle
			, strcalssname.c_str()
			, lpszTitle
			, dwStyle|WS_CHILD|WS_VISIBLE
			, rcWnd
			, UIWnd::FromHandle(hWndParent)
			, Id
			, NULL);
		if (myCtrl) {
			if (_tcsicmp(strcalssname.c_str(), _T("STATIC")) == 0) {
				//
			} else if (_tcsicmp(strcalssname.c_str(), _T("BUTTON")) == 0) {
				if (!(myCtrl.GetStyle() & BS_PUSHBUTTON)) {
					UIButton btn;
					btn.Attach((HWND)myCtrl);
					btn.SetCheck(tcsto<DWORD>(xml->GetDataString(strnull, strval), 0));
					btn.Detach();
				}
			} else if (_tcsicmp(strcalssname.c_str(), _T("LISTBOX")) == 0) {
				/*UIListBox lstbox((HWND)myCtrl);
				for(long cookie = xml->First(); cookie; cookie = xml->Next(cookie))
				{
					xml->IntoElem();
					lstbox.AddString(xml->GetDataString(strnull,strval).c_str());
					xml->OutofElem();
				}
				lstbox.Detach();*/
			}

			hWndCtrl = myCtrl.Detach();
		}
#endif//
	END_XML_MAP()
	return hWndCtrl;
}

//////////////////////////////////////////////////////////////////////////

#ifndef _AFX

//

#else

//__declspec(thread) LPVOID lpCreateParams = NULL;

#endif
