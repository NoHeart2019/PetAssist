// PetAssist.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PetAssist.h"
#include "Frame.h"
#include "MisUtil.h"
#include "Procduct.h"
#include "Util.h"
#define MAX_LOADSTRING 100
#define  EVENT_NAME_RUN_ONLY L"PetAssistOnlyRunEvent"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//_CrtDumpMemoryLeaks();
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	InitC32(hInstance);
	
#ifndef _DEBUG
	if(IsAppAlreadyRunning(EVENT_NAME_RUN_ONLY))
	{
		C32MessageBoxTip(L"只允许运行一个程序，请在右下角托盘中打开主界面");
		return 0;
	}
	theApp.CreateAutoRunLink();	
	theLog.SetLogLevel(LogLevelError);	
#else
	theLog.SetLoggingEnabled(true);
	theLog.SetLogLevel(LogLevelInfo);	
#endif

	CreateHoverFrame();

	return (int) 0;
}

