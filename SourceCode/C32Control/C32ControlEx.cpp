#include "stdafx.h"


VOID InitC32ControlEx()
{
	C32RoundProcess::RegisterThisClass();

}

BOOL C32RoundProcessText(HWND Hwnd)
{
	C32RoundProcess::RegisterThisClass();
	C32RoundProcess* Rnd = new C32RoundProcess();
	Rnd->SetDelete();
	DWORD ExStyle = 0;
	DWORD Style = WS_POPUPWINDOW|WS_VISIBLE|WS_SYSMENU|WS_CAPTION;
	Rnd->Create(0, C32_WC_ROUND_PROCESS, L"DDDD", Style,100, 100, 400, 300, Hwnd); 
	Rnd->SetFocus();
	int x = 0;

	return TRUE;
}
