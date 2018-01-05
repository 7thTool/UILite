// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料

//#define _BIND_TO_CURRENT_CRT_VERSION 1
//#define _BIND_TO_CURRENT_MFC_VERSION 1
//当然，根据需要还可以指定ATL和OPENMP库：
//#define _BIND_TO_CURRENT_ATL_VERSION 1
//#define _BIND_TO_CURRENT_OPENMP_VERSION 1
//或者可以简单地加入
//#define _BIND_TO_CURRENT_VCLIBS_VERSION 1

// TODO: 在此处引用程序需要的其他头文件

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
