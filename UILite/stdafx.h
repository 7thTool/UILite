// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����

//#define _BIND_TO_CURRENT_CRT_VERSION 1
//#define _BIND_TO_CURRENT_MFC_VERSION 1
//��Ȼ��������Ҫ������ָ��ATL��OPENMP�⣺
//#define _BIND_TO_CURRENT_ATL_VERSION 1
//#define _BIND_TO_CURRENT_OPENMP_VERSION 1
//���߿��Լ򵥵ؼ���
//#define _BIND_TO_CURRENT_VCLIBS_VERSION 1

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

#include "UILite.h"

#include <ShlObj.h>
#include <Shlwapi.h>
#include <ShellAPI.h>
#include <Psapi.h>
//#pragma comment(lib, "ShlObj.lib")
#pragma comment(lib, "Shlwapi.lib")
//#pragma comment(lib, "ShellAPI.lib")
#pragma comment(lib, "Psapi.lib")

//#define _WTL_NO_AUTOMATIC_NAMESPACE

#include <UI/UIApp.h>
extern UIAppModule _Module;
