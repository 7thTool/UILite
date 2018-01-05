#ifndef _H_PUBLIC_H_
#define _H_PUBLIC_H_

BOOL FindFromHwnd(HWND hWnd);
void EnumIE( void );

HRESULT GetHtmlSourceText(IHTMLDocument2* pHtmlDoc, std::string& strText);

#endif//