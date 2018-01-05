// Platform.h
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <XLib/UIXModule.h>

enum
{
	XML_FLAG_CREATE		= 0,			//Ĭ��CREATE
	XML_FLAG_DOMODAL	= 0X10,			//�Ի���Ļ�����ʹ��DoModal
};

//STR
#define STR_CREATE_XMLA		"CreateXml"	//����Createʹ�õ�����XML�ṹ���ݣ����û�б仯���ͷ���NULL
#define STR_CREATE_XMLW		L"CreateXml"
#define STR_CONFIG_XMLA		"ConfigXml"	//
#define STR_CONFIG_XMLW		L"ConfigXml"
#ifdef UNICODE
#define STR_CREATE_XML		STR_CREATE_XMLA		
#define STR_CONFIG_XML		STR_CONFIG_XMLA	
#else
#define STR_CREATE_XML		STR_CREATE_XMLW		
#define STR_CONFIG_XML		STR_CONFIG_XMLW	
#endif//

//�������

#define WORKDIRA			"WorkDir"		//exe work directory
#define DATADIRA			"DataDir"		//exe data directory
#define USERDIRA			"UserDir"		//user directory

#define WORKDIRW			L"WorkDir"		//exe work directory
#define DATADIRW			L"DataDir"		//exe data directory 
#define USERDIRW			L"UserDir"		//user directory


#ifdef UNICODE
#define WORKDIR				WORKDIRW		
#define DATADIR				DATADIRW	
#define USERDIR				USERDIRW
#else
#define WORKDIR				WORKDIRA		
#define DATADIR				DATADIRA	
#define USERDIR				USERDIRA
#endif//

#define MEMFILEA			"MEM"
#define APPFILEA			"APP"
#define USERFILEA			"USER"
#define THEMEFILEA			"THEME"

#define MEMFILEW			L"MEM"
#define APPFILEW			L"APP"
#define USERFILEW			L"USER"
#define THEMEFILEW			L"THEME"

#ifdef UNICODE
#define MEMFILE				MEMFILEW
#define APPFILE				APPFILEW
#define USERFILE			USERFILEW
#define THEMEFILE			THEMEFILEW
#else
#define MEMFILE				MEMFILEA
#define APPFILE				APPFILEA
#define USERFILE			USERFILEA
#define USERFILE			THEMEFILEA
#endif//

class Platform 
	: public UIXModuleT<Platform>
{
	typedef UIXModuleT<Platform> UXModule;
public:
	Platform();
	~Platform();

	long Init();
	void Term();

protected:
	typedef std::map<std::tstring, Markup*, std::tstringiless> Name2pMarkup;
	Name2pMarkup m_Name2pMarkup;
	Markup* OpenMarkup(LPCTSTR lpszFile);
	void CloseMarkup(LPCTSTR lpszFile);
//public:
	virtual long WriteValue(LPCSTR lpszName, LPCSTR lpszValue, int nValueCount = 0, LPCSTR lpszSpec = NULL, LPCSTR lpszFile = NULL);
	virtual long ReadValue(LPCSTR lpszName, LPSTR lpszValue, int nValueCount, LPCSTR lpszSpec = NULL, LPCSTR lpszFile = NULL);
	virtual long WriteValue(LPCWSTR lpszName, LPCWSTR lpszValue, int nValueCount = 0, LPCWSTR lpszSpec = NULL, LPCWSTR lpszFile = NULL);
	virtual long ReadValue(LPCWSTR lpszName, LPWSTR lpszValue, int nValueCount, LPCWSTR lpszSpec = NULL, LPCWSTR lpszFile = NULL);
};

extern Platform _Platform;

