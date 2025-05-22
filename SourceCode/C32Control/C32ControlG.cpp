#include "stdafx.h"
#include "C32ControlG.h"

CAtlMap<HWND, CJPGViewer*> g_JpgMap;


BOOL SetJPGImagePath(HWND Hwnd, LPCWSTR ImagePath)
{
	POSITION Start = g_JpgMap.GetStartPosition();
	CJPGViewer* JPG = NULL;
	bool Ret =g_JpgMap.Lookup(Hwnd, JPG);
	if (Ret)
	{
		//ASSERT(0);
		g_JpgMap.RemoveKey(Hwnd);
	}

	JPG = new CJPGViewer();
	if (JPG)
	{
		if(JPG->LoadImage(ImagePath))
		{
		   if(g_JpgMap.SetAt(Hwnd, JPG) != NULL)
		   {
				ZxDebugEx((__FUNCTION__"()::  \n"));
				return TRUE;
			}
		}
	}


	return FALSE;
}

LRESULT CALLBACK WndProcJPGViewer(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		{
			g_JpgMap.SetAt(hwnd, NULL);
			break;
		}

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			CJPGViewer* jpgViewer = NULL;
			g_JpgMap.Lookup(hwnd, jpgViewer);
			if (jpgViewer)
			{
				int width, height;
				if (jpgViewer->GetImageSize(width, height))
				{
					jpgViewer->Draw(hdc, 0, 0, width, height);
				}

			}
			// 绘制图片
			EndPaint(hwnd, &ps);
			break;
		}

	case WM_SIZE:
		{
			// 当窗口大小改变时触发重绘
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}

	case WM_DESTROY:
		{
			CJPGViewer* jpgViewer = NULL ;
			g_JpgMap.Lookup(hwnd, jpgViewer);
			g_JpgMap.RemoveKey(hwnd);
			if (jpgViewer)
			{
				delete jpgViewer;
			}
			break;
		}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}


DWORD RegisterJPGViewClass()
{
	// 注册窗口类
	WNDCLASS wc = {0};
	wc.lpfnWndProc = WndProcJPGViewer;
	wc.hInstance = C32Hinstance;
	wc.lpszClassName = _T("JPGViewer");
	
	return RegisterClass(&wc);
}

VOID InitC32ControlGdi()
{
	RegisterJPGViewClass();

}