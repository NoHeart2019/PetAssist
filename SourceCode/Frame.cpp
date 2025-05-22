#include "stdafx.h"
#include "Frame.h"

#pragma comment(lib, "Dwmapi.lib")


CHoverFrame*   g_HoverFrame;



BOOL CreateHoverFrame()
{
	g_HoverFrame = new CHoverFrame();

	g_HoverFrame->SetDelete();

	g_HoverFrame->CreateControl();

	g_HoverFrame->m_iAccelerator = IDC_PETASSIST;

	g_HoverFrame->Loop();
	return TRUE;
}






