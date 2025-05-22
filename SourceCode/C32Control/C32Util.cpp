#include "stdafx.h"
#include "C32Util.h"

 
C32SystemMetrics   theSysMetrics;
C32SysObject       theSysObject;
C32Monitor		   theMonitor;
C32DPI			   theDPI;

//��ȡ����ǰ������ʾ���ķֱ��ʴ�С�����Զ�̬�Ļ�ȡ����������ʾ���ķֱ���
SIZE C32GetDesktopSize(HWND hWnd) {
	SIZE size = {};
	
	//MONITOR_DEFAULTTONEAREST ����ֵ����ӽ��õ����Ļ���
	//MONITOR_DEFAULTTOPRIMARY ����ֵ������Ļ�ľ��
	//�������һ����Ļ�����õ㣬�򷵻�ֵ�Ǹ���Ļ��HMONITOR��������û��һ����Ļ�����õ㣬�򷵻�ֵȡ����dwFlags��ֵ
	DWORD dwFlag = (hWnd ?MONITOR_DEFAULTTONEAREST : MONITOR_DEFAULTTOPRIMARY);
	HMONITOR hMonitor = MonitorFromWindow(hWnd, dwFlag);
	MONITORINFOEX miex;
	miex.cbSize = sizeof(miex);
	if (!GetMonitorInfo(hMonitor, &miex))
		return size;

	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;

	//ENUM_CURRENT_SETTINGS ������ʾ�豸�ĵ�ǰ����
	//ENUM_REGISTRY_SETTINGS ������ǰ�洢��ע����е���ʾ�豸������
	if (!EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm))
		return size;

	size.cx = dm.dmPelsWidth;
	size.cy = dm.dmPelsHeight;
	return size;
}

BOOL C32SetCenterPos(HWND Hwnd, HWND Parent)
{
	RECT Rect1 = {}, Rect = {};
	GetWindowRect(Hwnd, &Rect1);
	
	if (Parent == NULL) //�������
	{
		SIZE Size = C32GetDesktopSize(NULL);
		Rect.left = Rect.top = 0;
		Rect.right = Size.cx;
		Rect.bottom = Size.cy;

						
	}else
	{
		GetWindowRect(Parent, &Rect);
		
	}
	
	int X = (Rect.left + Rect.right)/2 - C32GetRectWidth(Rect1)/2;
	int Y = (Rect.top + Rect.bottom)/2 - C32GetRectHeight(Rect1)/2;

	return ::SetWindowPos(Hwnd, NULL, X, Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

}

BOOL C32SetCenterPosDesktop(HWND Hwnd)
{
	return C32SetCenterPos(Hwnd, NULL);
}

BOOL C32SetClipboard(CString& String, HWND Hwnd)
{
	CStringA Str = C32W2A(String);
	int ByteSize = Str.GetLength() + 1;
	if ( !OpenClipboard(Hwnd))
	{
		return FALSE;
	}
	// Remove the current Clipboard contents
	if( !EmptyClipboard())
	{
		return FALSE;
	}
	// Get the currently selected data
	HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, ByteSize);
	if (hGlob == NULL)
	{
		CloseClipboard();
		return FALSE;
	}
	GlobalLock(hGlob);
	strcpy_s((char*)hGlob, ByteSize, Str.GetString());
	GlobalUnlock(hGlob);
	// For the appropriate data formats...
	if ( ::SetClipboardData( CF_TEXT, hGlob ) == NULL )
	{
		CloseClipboard();
		GlobalFree(hGlob);
		return FALSE;
	}
	CloseClipboard();

	return TRUE;
}

int  C32GetTextLength(HWND Hwnd, LPCWSTR String, HFONT hFont)
{
	SIZE Size = {};
	HDC  Hdc = NULL;
    TEXTMETRIC Tm={};
	if (String == NULL || Hwnd == NULL)
		return 0;
	
	Hdc = GetDC(Hwnd);

	WCHAR FontName[256]={};
	int FontNameLength =  GetTextFace(Hdc, 256, FontName);
	BOOL Ret = GetTextMetrics(Hdc,&Tm);
	if (Hdc)
	{
		HFONT hFont0 = SelectFont(Hdc, hFont);
		GetTextExtentPoint32(Hdc, String, (int)wcslen(String), &Size);	
		SelectFont(Hdc, hFont0);
	}
	ReleaseDC(Hwnd, Hdc);
	ZxDebugEx((__FUNCTION__"Font Name : %ws Width: %d \n", FontName, Size.cx));

	return Size.cx;
}

int  C32GetTextLength(HDC Hdc, LPCWSTR String)
{
	SIZE Size = {};
	TEXTMETRIC Tm={};
	if (String == NULL || Hdc == NULL)
		return 0;
	WCHAR FontName[256]={};
	int FontNameLength =  GetTextFace(Hdc, 256, FontName);
	BOOL Ret = GetTextMetrics(Hdc,&Tm);
	if (Hdc)
	{

		GetTextExtentPoint32(Hdc, String, (int)wcslen(String), &Size);	
	}
	ZxDebugEx((__FUNCTION__"Font Name : %ws Width: %d \n", FontName, Size.cx));
	return Size.cx;
}

BOOL C32ChooseColor(HWND hwndOwner, _Out_ COLORREF* Color)
{
	CHOOSECOLOR cc;                 // common dialog box structure 
	COLORREF acrCustClr[16] = {}; // array of custom colors 
	DWORD rgbCurrent = 0;        // initial color selection

	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwndOwner;
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc)==TRUE) 
	{
		*Color = cc.rgbResult;
		return TRUE;
	}

	return FALSE;
}

BOOL C32ChooseFont(HWND hwndOwner, _Inout_ LPLOGFONT LogFont, __out int* FontSize)
{
	CHOOSEFONT cf;            // common dialog box structure
	static LOGFONT lf;        // logical font structure
	static DWORD rgbCurrent;  // current text color
	// Initialize CHOOSEFONT
	ZeroMemory(&cf, sizeof(cf));
	cf.lStructSize = sizeof (cf);
	cf.hwndOwner = hwndOwner;
	cf.lpLogFont = LogFont;
	cf.rgbColors = rgbCurrent;
	cf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;

	if (ChooseFont(&cf)==TRUE)
	{
		if (FontSize)
			*FontSize =cf.iPointSize/10;
		return TRUE;
	}

	return FALSE;
}
//https://zhuanlan.zhihu.com/p/528345722
//Windows��ȡ��Ļ���ű���(�Ŵ��ʣ�DPI �ֱ��ʵȵ����Դ����С������ЧOffice

int C32GetFontHeightInPixels(HDC hdc, int lfHeight)  
{  
	// ��ȡ�豸��DPIֵ��ÿӢ����������Y�ᣩ  
	int dpiY = GetDeviceCaps(hdc, LOGPIXELSY);  
	dpiY = dpiY/ (dpiY/USER_DEFAULT_SCREEN_DPI);
	 
	// ע�⣺lfHeight�Ǹ���ʱ����ʾ�ַ��߶�  
	// ������Ҫ����ת��Ϊ�������м��㣬��ΪMulDiv������������  
	// Ȼ������ʹ��MulDiv�����о�ȷ���������������⸡��������  
	// MulDiv(a, b, c) �൱�� (a * b) / c�����������ȷ  
	return MulDiv(-lfHeight, dpiY, 72);  
} 

HFONT C32GetSysFont()
{
	return theSysObject.GetLogicFont();
}


int C32GetFontSize(HWND hwndOwner, LPLOGFONT LogFont)
{
	int FontSize = 0;
	HDC Hdc = GetDC(hwndOwner);
	if (Hdc == NULL)
		return 0;

	HFONT hFont = CreateFontIndirect(LogFont);
	if (hFont)
	{
		//C32SelectObject Sel(Hdc, hFont);
		HFONT hGdiObj1 = SelectFont(Hdc, hFont);
		//FontSize =-LogFont->lfHeight*GetDeviceCaps(Hdc, LOGPIXELSY)/72.0 + 0.5;

		FontSize = C32GetFontHeightInPixels(Hdc, LogFont->lfHeight);

		SelectFont(Hdc, hGdiObj1);
		DeleteFont(hFont);
	}
	ReleaseDC(hwndOwner, Hdc);
	return FontSize;
}

int C32GetFontSize(HWND hwndOwner, LPLOGFONT LogFont, int Height)
{
	int FontSize = 0;
	HDC Hdc = GetDC(hwndOwner);
	if (Hdc == NULL)
		return 0;
	LogFont->lfHeight = Height;
	HFONT hFont = CreateFontIndirect(LogFont);
	if (hFont)
	{
		HFONT hGdiObj1 = SelectFont(Hdc, hFont);
		TEXTMETRIC Tm={};
		GetTextMetrics(Hdc, &Tm);
		FontSize = Height - Tm.tmDescent;
		SelectFont(Hdc, hGdiObj1);
		DeleteFont(hFont);
	}
	ReleaseDC(hwndOwner, Hdc);
	return FontSize;
}

HFONT C32CreateFont(LPCWSTR FontName, int FontSize)
{
	C32Dc  dc(NULL); 
	int nPointSize = 14; // �û�ָ���ֺ�
	int nHeight = -MulDiv(nPointSize, GetDeviceCaps(dc, LOGPIXELSY), 72);

	LOGFONT lf = {0};
	lf.lfHeight = nHeight;
	lf.lfWidth = 0;               // �����ϵͳ�Զ�����
	lf.lfEscapement = 0;          // �ı���ת�Ƕȣ�0 ��ʾ������
	lf.lfOrientation = 0;
	lf.lfWeight = FW_NORMAL;      // �����ϸ�����棩
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut = FALSE;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(lf.lfFaceName, FontName); // �����Ӣ������
	HFONT hFont = CreateFontIndirect(&lf);

	return hFont;
}

BOOL C32GetFontInfo(HGDIOBJ  hFont)
{
	LOGFONT LogFont = {};
	int Size;
	int SizeOfLogFont = sizeof(LOGFONT);

	Size = GetObject(hFont, SizeOfLogFont, (PVOID)&LogFont);
	if (Size)
	{
		return TRUE;
	}

	return FALSE;
}

HFONT  C32CreateSystemFont(FLOAT Scale)
{
	LOGFONT Font = {};
	HFONT   hFont = NULL;
	memcpy(&Font,&theSysMetrics.m_NonClientMetrics.lfCaptionFont, sizeof(LOGFONT));
	Font.lfHeight = (LONG)(Scale* Font.lfHeight);
	
	return CreateFontIndirect(&Font);
}



/*
	�ھ���SrcRect Draw ͼƬ
	���SrcRect�ĸ߶ȺͿ�ȴ���ͼƬ��ͼƬ���¾���
*/
BOOL C32GetDrawIconRect(int IconCx, int IconCy, RECT SrcRect, __out RECT * IconRect)
{
	int SrcCx = C32GetRectWidth(SrcRect);
	int SrcCy = C32GetRectHeight(SrcRect);
	
	int Cx = (IconCx > SrcCx ? SrcCx : IconCx);
	int Cy = (IconCy > SrcCy ? SrcCy : IconCy);
	
	int yPos = SrcRect.top + (SrcCy - Cy)/2;
	int yPos1 = yPos + Cy;

	int xPos = SrcRect.left + (SrcCx - Cx)/2;
	int xPos1 = xPos + Cx; 

	IconRect->left = xPos;
	IconRect->top = yPos;
	IconRect->right = xPos1;
	IconRect->bottom = yPos1;

	return TRUE;
}

BOOL C32GetDrawIconRect(SIZE Size, RECT SrcRect, __out RECT * IconRect)
{
	return C32GetDrawIconRect(Size.cx, Size.cy, SrcRect, IconRect);

}

BOOL C32SetSizeInRectCenter(SIZE Size, RECT SrcRect, __out RECT * IconRect)
{
	return C32GetDrawIconRect(Size, SrcRect, IconRect);

}

BOOL C32SetMenuOwnerDraw(__in HMENU hMnu, __in UINT uPosition, __in UINT uFlags,__in UINT_PTR uIDNewItem)
{
	UINT State = GetMenuState(hMnu, uPosition, uFlags);
	State |= MF_OWNERDRAW;

	return ModifyMenu(hMnu, uPosition, State|uFlags,uIDNewItem, NULL);
}


BOOL C32FontGetTextExtentPoint32(__in HDC hdc,__in_ecount(c) LPCWSTR lpString,__in int c,__out LPSIZE psizl, LPLOGFONT LogFont)
{
	BOOL Ret = FALSE;
	HFONT hFont = CreateFontIndirect(LogFont);
	HFONT hFont0 =SelectFont(hdc, hFont);

	Ret = GetTextExtentPoint32(hdc, lpString, c, psizl);

	SelectFont(hdc, hFont0);
	DeleteFont(hFont);

	return Ret;
}

BOOL C32FontGetTextExtentPoint32(__in HWND hwnd,__in_ecount(c) LPCWSTR lpString,__in int c,__out LPSIZE psizl, LPLOGFONT LogFont)
{
	BOOL Ret = FALSE;
	C32Dc   Dc(hwnd);
	C32Font Font;
	Font.CreateFontIndirect(LogFont);
	C32SelectObject So(Dc, Font);
	Ret = C32FontGetTextExtentPoint32(Dc, lpString, c, psizl, LogFont);


	return Ret;
}

FLOAT C32GetDpiFontSize()
{
	return theDPI.m_FontSize;
}

VOID C32DrawLine(HDC hdc,POINT StartPoint, POINT EndPoint, int PenSize, COLORREF PenColor)
{

	// ����һ�����ʣ�������ɫ�Ϳ�ȡ������Ժ�ɫΪ�������Ϊ2��
	HPEN hPen = CreatePen(PS_SOLID, PenSize, PenColor);
	// ��ȡ��ǰ�����Ա�֮��ָ�
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	// �����Ҫ�������������ƶ�����ʼλ��
	MoveToEx(hdc, StartPoint.x, StartPoint.y, NULL);

	// ʹ�� LineTo ����ֱ��
	LineTo(hdc, EndPoint.x, EndPoint.y);

	// �ָ�֮ǰ�Ļ���
	SelectObject(hdc, hOldPen);
	// ɾ���´����Ļ��ʣ������ڴ�й©
	DeleteObject(hPen);

}


VOID C32DPI::Initialize()
{
	theSysMetrics.GetFontLanguage(&m_LogFont, m_LocalString);
	m_FontString = m_LogFont.lfFaceName;
	m_FontScale = theMonitor.m_FontScale;
	m_WindowScale = theMonitor.m_WindowScale;
	m_FontSize =  24;//MulDiv(-m_LogFont.lfHeight, theMonitor.m_LogPixel, 96);
}

VOID InitC32Util()
{
	theSysObject.Initialize();
	theDPI.Initialize();
}
