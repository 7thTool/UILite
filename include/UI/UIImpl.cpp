
#if (_ATL_VER < 0x0700)
#include <atlimpl.cpp>
#endif //(_ATL_VER < 0x0700)

#include "UIBase.h"

UINT WM_MSG_TASKBARCREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));
