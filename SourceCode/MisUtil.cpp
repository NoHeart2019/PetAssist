#include "stdafx.h"
#include "MisUtil.h"

#define PNG_DIRECTORY L"XueXiZhuShou\\PNG\\"

BOOL CreateDonationWindow(HWND Hwnd, LPCWSTR Title)
{
	C32Window Donation ;
	DWORD Style = WS_POPUPWINDOW | WS_CAPTION  |WS_VISIBLE;
	C32ResorceFile File;
	CString DiskPath = PNG_DIRECTORY;
	DiskPath += L"Donation.jpg";
	File.FreeResourceDisk(IDB_PNG_DONATION, L"JPG", DiskPath);
	Donation.Create(0,C32_WC_JPG_VIEWER, Title, Style, 0 ,0, 632, 900, Hwnd);
	SetJPGImagePath(Donation.m_Hwnd,DiskPath);
	DeleteFile(DiskPath);
	Donation.SetCenterPos();
	return TRUE;
}