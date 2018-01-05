#include "stdafx.h"
#include "UIXModule.h"

long UIXModuleBase::Init()
{
	//UIXWndModule::Init();
	UIXSkinModule::Init();
	return RLT_OK;
}

void UIXModuleBase::Term()
{
	//UIXWndModule::Term();
	UIXSkinModule::Term();
}