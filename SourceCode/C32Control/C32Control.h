#pragma once

#include "C32DebugMsg.h"
#include "C32Helper.h"
#include "C32Class.h"
#include "C32Util.h"
#include <atlcoll.h>
#include <algorithm>
#include <atlstr.h>
#include <atlconv.h>
#include <assert.h>
#include <Richedit.h>
#include <RichOle.h>
#include "C32GdiObject.h"
#include "C32DebugMsg.h"





/*
	Windows �ؼ� https://learn.microsoft.com/zh-cn/windows/win32/controls/window-controls

	ʹ��C32Lib�������Ҫ�����¼���ֻ��Ҫ��עC32ControlEventCallback
*/
#ifndef ASSERT
#define ASSERT assert
#endif

#define C32GetRectWidth(rc) (rc.right -rc.left) 
#define C32GetRectHeight(rc) (rc.bottom -rc.top) 


#define RtlZeroStringW(Ptr, Count) RtlZeroMemory(Ptr, Count*2)

#define C32_WC_EXPLORER L"C32Explorer"
#define C32_WC_CONTAINTER L"C32Container"

#define C32MessageBox(Title, Caption) MessageBox(NULL,Caption, Title, MB_OK)

#define C32MessageBoxTipYes(Caption) MessageBox(NULL,Caption, L"��ʾ", MB_YESNO)

#define C32MessageBoxTip(Caption) MessageBox(NULL,Caption, L"��ʾ", MB_OK)

#define C32MessageBoxSuccess(x) x ? MessageBox(NULL,  L"�����ɹ�", L"��ʾ", MB_OK) : MessageBox(NULL,  L"����ʧ��", L"��ʾ", MB_OK)

#define C32MessageBoxUser(Caption) MessageBox(NULL,Caption, L"��ʾ", MB_YESNO)

#define C32MessageBoxTipReturn(Caption, Bool){\
			MessageBox(NULL,Caption, L"��ʾ", MB_OK);\
			return Bool;\
			}
#define C32MessageBoxUserEx(Hwnd,Caption) MessageBox(Hwnd,Caption, L"��ʾ", MB_YESNO)
#define C32MessageBoxTipEx(Hwnd,Caption) MessageBox(Hwnd,Caption, L"��ʾ", MB_OK)
#define C32MessageBoxEx(Hwnd,Title, Caption) MessageBox(Hwnd, Caption, Title, MB_OK)
#define C32MessageBoxSuccessEx(Hwnd,x) x ? MessageBox(Hwnd, L"�����ɹ�", L"��ʾ", MB_OK) : MessageBox(NULL,  L"����ʧ��", L"��ʾ", MB_OK)

#define C32MessageBoxTipReturnEx(Hwnd,Caption, Bool){\
	MessageBox(Hwnd,Caption, L"��ʾ", MB_OK);\
	return Bool;\
			}



#define C32GetLastError() m_Error = GetLastError()
#define C32GetUserData(hwnd)  (LONG_PTR)GetWindowLongPtr(hwnd, GWLP_USERDATA)
#define C32SetUserData(hwnd, UserData)  (LONG_PTR)SetWindowLongPtr(hwnd, GWLP_USERDATA, UserData)

#define C32GetUserClass(hwnd)  (C32Window*)C32GetUserData(hwnd)

#define C32BoolToString(x) (x  ? "Yes" : "No")
#if _WIN64
	#define C32DWL_MSGRESULT  DWLP_MSGRESULT
#else
	#define C32DWL_MSGRESULT  DWL_MSGRESULT
#endif


							
#define C32EVENT_UNREFERENCED_PARAMETER()\
							{			\
								UNREFERENCED_PARAMETER(wParam);	\
								UNREFERENCED_PARAMETER(lParam);	\
								UNREFERENCED_PARAMETER(lResult);	\
							}
#define C32WM_TRAY   WM_USER + 0x100
#define C32DBG_MESSAGE_BOX() MessageBox(NULL, NULL, NULL, MB_OK)


#define C32SetHandleLReslut(IsHandle, lResultValue) Handle = IsHandle, lResult = lResultValue

#define C32CommandIsMenu(wParam, lParam) (HIWORD(wParam) == 0 && lParam == 0)
#define C32CommandIsAccelerator(wParam, lParam) (HIWORD(wParam) == 1 && lParam == 0)
#define C32CommandIsCtrl(wParam) (HIWORD(wParam) > 1)

#define C32CommandMenuId(wParam) LOWORD(wParam)
#define C32CommandCtrlNotifiyCode(wParam) HIWORD(wParam)
#define C32CommandCtrlId(wParam) LOWORD(wParam)

#define C32IsNull(x) (x == NULL) 
#define C32IsNonNull(x) (x != NULL) 		
#define C32NonZero    (LPARAM)1

#define C32CtrlDebug(x) ZxDebug(x)


			
#define C32SelectFontDefault(hdc) SelectFont(hdc,GetStockObject(DEFAULT_GUI_FONT));
#define C32LvIsSelected(lpnmlv) ((lpnmlv->uNewState& LVIS_SELECTED))

#define C32LvGetStateCheckState(x) ((x & LVIS_STATEIMAGEMASK) >>12)
//��ɫ
#define C32ColorWhite				0x00FFFFFF
#define C32ColorBlack				0x00000000

//������ ΢�� Edge ��ɫ����
#define C32ColorDarkBlack1			0x00333333
#define C32ColorDarkBlack2			0x003B3B3B
#define C32ColorDarkBlack3			0x00454545

#define C32ColorListViewSelAlways 0x00F0F0F0 //Ĭ��ʧȥ����ѡ�е���ɫ: �Ұ�ɫ
#define C32ColorListViewSel       0x00FF8000 //Ĭ��ѡ����ɫ�� ��ɫ

//
//����
//
#define C32GetSystemFont() C32GetSysFont()
#define C32IsValidHwnd(Hwnd) (Hwnd != NULL && Hwnd != INVALID_HANDLE_VALUE)


#define C32Min(x, y) (x >= y ? y : x)
#define C32Max(x, y) (x >= y ? x : y)

//WM_USER
#define  C32_WM_CREATE  WM_USER + 0x0010


class C32Static;
class C32SysLink;
class C32Window;
class C32ListView;
class C32TreeView;
class C32StatusBar;
class C32Button;
class C32GroupBox;
class C32ComboBox;
class C32Dialog;
class C32DialogSearch;
class C32Header;
class C32TabCtrl;
class C32TabList;
class C32ToolTip;
class C32Container;
class C32DialogSyn;
class C32DateTimeCtrl;
class C32Edit;
class C32RichEditCtrl;

typedef Gdiplus::Status  C32GdiStatus;
typedef Gdiplus::Pen  C32GdiPen;
typedef Gdiplus::Brush  C32GdiBrush;
typedef Gdiplus::Graphics  C32Graphics;

typedef Gdiplus::ImageAttributes C32ImageAttributes;
typedef Gdiplus::Matrix          C32Matrix;         
typedef Gdiplus::Brush           C32GdiBrush;          
typedef Gdiplus::Pen             C32Pen;            
typedef Gdiplus::StringFormat    C32StringFormat;   
typedef Gdiplus::PathData        C32PathData;           
typedef Gdiplus::Graphics        C32Graphics;       
typedef Gdiplus::Metafile        C32Metafile;       
typedef Gdiplus::CachedBitmap    C32CachedBitmap;   
typedef Gdiplus::Region          C32Region;         
typedef Gdiplus::FontCollection  C32FontCollection; 
typedef Gdiplus::FontFamily      C32FontFamily;     
typedef Gdiplus::Font            C32GdiFont;           
typedef Gdiplus::Bitmap          C32Bitmap; 
       

extern HINSTANCE C32Hinstance;


typedef BOOL (WINAPI* C32_ON_EVENT_CALLBACK)(WPARAM wParam, LPARAM lParam, LRESULT& lResult);
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK)(WPARAM wParam, LPARAM lParam, LRESULT& lResult, C32Window* This);
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_CREATE)(LRESULT& lResult, C32Window* This);
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_DESTROY)(LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_COMMADN)(DWORD CtrlId, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_CONTEXTMENU)(HWND hwndClicked, int xPos, int yPos, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_COMMAND_MENU)(DWORD CtrlId, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_ONSIZE)(DWORD ResizeType, int Cx, int Cy, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_DRAW_ITEM)(LPDRAWITEMSTRUCT lpdis, LRESULT& lResult,C32Window* This);

typedef BOOL (WINAPI* C32_EVENT_IS_DIALOG_MESSAGE)(LPMSG lpMsg, C32Window* ThisWnd);

//Static Event
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_STATIC_CLICK)(DWORD CtrlId, C32Window* This);
typedef C32_EVENT_CALLBACK_STATIC_CLICK C32_EVENT_CALLBACK_STATIC_DCLICK;
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_STATIC_DRAW_ITEM)(LPDRAWITEMSTRUCT lpdis, LRESULT& lResult,C32Static* ThisStatic);


//SysLink Event
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_SYSLINK_CLICK)(PLITEM Item, LRESULT& lResult,C32SysLink* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_BUTTON_CLICK)(DWORD CtrlId, C32Button* ThisButton);


// Button Event
typedef C32_EVENT_CALLBACK_BUTTON_CLICK C32_EVENT_CALLBACK_BUTTON_DCLICK;


//Header
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_HEADER)(WPARAM wParam, LPARAM lParam, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_HEADER_NOTIFY)(LPNMHEADER lpnmhdr, LRESULT& lResult, C32Header* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_DIALOG_INIT)(C32Dialog* This);


//Tab Control
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE)(int iSelectItem, LRESULT& lResult, C32TabCtrl* This);

//ToolTip Control
typedef BOOL (WINAPI*C32_EVENT_CALLBACK_TOOLTIP_CTRL_NOTIFY_GETDISPINFO)(ULONG_PTR idFrom, BOOL IsHwnd, __inout LPWSTR* lpszText, __out BOOL* isRetain,LRESULT& lResult, C32ToolTip* This);

//DateTime Control
typedef BOOL (WINAPI*C32_EVENT_CALLBACK_DATETIME_CTRL_NOTIFY_CHANGE)(LPNMDATETIMECHANGE lpdtc,LRESULT& lResult, C32DateTimeCtrl* ThisDataTimeCtrl);


//typedef C32_EVENT_CALLBACK_EX  C32_EVENT_CALLBACK_HEADER;


#define C32OnXyz(OnXyz)\
	virtual BOOL CALLBACK OnXyz(WPARAM wParam, LPARAM lParam, LRESULT& lResult)\
	{\
		C32EVENT_UNREFERENCED_PARAMETER();\
		return FALSE;\
	}

#define C32OnXyzM(OnXyz)\
	virtual BOOL CALLBACK OnXyz(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)\
{\
	C32EVENT_UNREFERENCED_PARAMETER();\
	return FALSE;\
}



#define C32_CALL_EVENT_CALLBACK(CallBackFunction)(CallBackFunction(wParam, lParam, lResult, this))

typedef struct _C32TCreateStruct
{
	ULONG   ResorceId;
	HWND    m_LogicHwnd;
	LPARAM  m_LogiclParam;
}C32TCreateStruct, *PC32TCreateStruct; 

extern HINSTANCE C32Hinstance;
extern HWND      C32Hwnd;
extern C32Container* C32MainFrame;
extern UINT C32FindReplaceMsg;
extern LONG_PTR C32ControlId; 


/*
	�ͷ� CAtlArray<C32Window*> m_List
	DeletePtr:TRUE ���� delete m_List[i]
*/
VOID  C32FreeWindowList(CAtlArray<C32Window*>& List, BOOL DeletePtr = FALSE);
 
/*
	����Ĭ�ϵĿؼ�
	Windows Explorer Tree
	Windows Explorer List
*/
VOID C32CreateTree(C32TreeView& Tree, HWND hwndParent, int xPos = 0, int yPos = 0, int Cx = 0, int Cy = 0);

VOID C32CreateList(C32ListView& List, HWND hwndParent, int xPos = 0, int yPos = 0, int Cx = 0, int Cy = 0);

VOID C32CreateStatus(C32StatusBar& Status, HWND hwndParent);



class C32DrawText
{
public:
	C32DrawText()
	{

	}

	~C32DrawText()
	{

	}

	/*
		���¾���дд����
	*/
	BOOL TextOutExt(__in HDC hdc,  __in UINT Options, RECT * Rect,  LPCWSTR String, int Count)
	{
		BOOL bRet = FALSE;
		TEXTMETRIC tm = {};
		int xPos; 
		int yPos;
		GetTextMetrics(hdc, &tm);
		xPos = Rect->left;
		yPos = (Rect->top + Rect->bottom - tm.tmHeight)/2;

		bRet = ExtTextOut(hdc, xPos, yPos, Options, Rect, String, Count, NULL);

		return !!bRet;
	}

};

/*
	����ϵͳ��񻭿ؼ�
	��ֱ�ӵ���DrawFrameControl
	�ĵ���Visual Styles -> Parts and States

*/
class C32DrawControl
{
public:
	C32DrawControl()
	{
		Init();
	}
	~C32DrawControl()
	{
		Destroy();

	}

	BOOL Open(LPCWSTR ControlName, HWND Controlhwnd = NULL)
	{
		Close();
		m_Theme = OpenThemeData(Controlhwnd, ControlName);

		return (m_Theme != NULL);
	}

	VOID Close()
	{
		if (m_Theme)
		{
			CloseThemeData(m_Theme);
			m_Theme = NULL;
		}
	}

	BOOL DrawControl(HDC hdc, int iCtrlPartId, int iCtrlStateId, RECT* Rect)
	{
		HRESULT hrst;
		
		
		hrst = DrawThemeBackground(m_Theme, hdc, iCtrlPartId, iCtrlStateId, Rect, NULL);
		if (S_OK != hrst)
		{
			ZxDebug((__FUNCTION__"():: Fail : iPartId : %d iStateId: %d\n", iCtrlPartId, iCtrlStateId));
		}
		return (S_OK == hrst);
	}

	BOOL DrawControlSystemStyle(HDC hdc, int iCtrlPartId, int iCtrlStateId, RECT* Rect)
	{
		SIZE Size = {26,26};
		if (!GetPartSize(hdc, iCtrlPartId, iCtrlStateId, Size))
			return FALSE;

		RECT rcSysTyle = *Rect;
		rcSysTyle.left = Rect->left;
		rcSysTyle.right = rcSysTyle.left + Size.cx;
		rcSysTyle.top = (Rect->bottom + Rect->top - Size.cy)/2;
		rcSysTyle.bottom = rcSysTyle.top+Size.cy;
		
		if(DrawControl(hdc, iCtrlPartId, iCtrlStateId, &rcSysTyle) == FALSE)
			return FALSE;
		*Rect = rcSysTyle;
		return TRUE;
	}

	BOOL DrawCheckBoxImage(HDC hdc, int iStateId, RECT Rect)
	{
		HRESULT hrst;
		SIZE Size = {};

		hrst = GetThemePartSize(m_Theme, hdc, BP_CHECKBOX, iStateId, NULL,TS_DRAW, &Size);

		Rect.top += (C32GetRectHeight(Rect)/2 - Size.cy/2);
		Rect.right = Rect.left + Size.cx;
		Rect.bottom = Rect.top + Size.cy;

		return DrawControl(hdc, BP_CHECKBOX, iStateId, &Rect);
	}

	BOOL GetPartSize(HDC hdc, int iPartId, int iStateId, SIZE& Size)
	{
		Size.cx = Size.cy = 0;
		HRESULT hrst;
		hrst = GetThemePartSize(m_Theme, hdc, iPartId, iStateId, NULL,TS_TRUE, &Size);
		if (hrst == S_OK )
			return TRUE;

		return FALSE;
	}

	COLORREF GetThemeSysColor(__in int iColorID)
	{
		return ::GetThemeSysColor(m_Theme, iColorID);
	}

	BOOL DrawCheckBox(HDC hdc, int iStateId, RECT Rect,LPCWSTR String)
	{
		BOOL  bRet = FALSE;

		SIZE Size = {26,26};
		if (!GetPartSize(hdc, BP_CHECKBOX, iStateId, Size))
			return FALSE;
	
		// ��д�����ڻ�ͼƬ why?
		if (String)
		{
			Rect.left += Size.cx + 5;
			C32DrawText Text;
			bRet = Text.TextOutExt(hdc, ETO_OPAQUE, &Rect, String, (int)wcslen(String));
			Rect.left -= (Size.cx + 5);
		}

		Rect.top += (C32GetRectHeight(Rect)/2 - Size.cy/2);
		Rect.right = Rect.left + Size.cx;
		Rect.bottom = Rect.top + Size.cy;
		if(DrawControl(hdc, BP_CHECKBOX, iStateId, &Rect) == FALSE)
			return FALSE;

		return bRet;
	}

#if 0
	BOOL DrawCheckBoxEx(HDC hDc, int iStateId, RECT Rect)
	{
		BOOL bDraw = FALSE;
		if(Open(WC_BUTTON))
		{
			bDraw= DrawCheckBox(hDc, iStateId, Rect);
			Close();
		}

		return bDraw;
	}

#endif
	
	BOOL DrawThemeText(HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int cchText, DWORD dwTextFlags, DWORD dwTextFlags2, LPCRECT pRect)
	{
		HRESULT hrst;
		hrst = ::DrawThemeText(m_Theme, hdc, iPartId, iStateId, pszText, cchText,dwTextFlags, dwTextFlags2, pRect);

		return (hrst == S_OK);
	}

	VOID Init()
	{
		m_Theme = NULL;
	}

	VOID Destroy()
	{
		Close();
	}


public:
	HTHEME m_Theme;
};

class C32SysGdiObject
{
public:
	static HFONT  m_SysGuiFont; //DEFAULT_GUI_FONT 
	static HFONT  m_SysFont;    //SYSTEM_FONT

public:
	static VOID Initialize()
	{
		m_SysGuiFont = GetStockFont(DEFAULT_GUI_FONT);
		m_SysFont = GetStockFont(SYSTEM_FONT);
	}

	VOID Uninitialize()
	{
		if (m_SysGuiFont)
		{
			DeleteObject(m_SysGuiFont);
			m_SysGuiFont = NULL;
		}

		if (m_SysFont)
		{
			DeleteObject(m_SysFont);
			m_SysFont = NULL;
		}
	}


public:
	C32SysGdiObject()
	{

	}

	~C32SysGdiObject()
	{

	}

	
};

/*
	��װ hdc .
*/
class C32DeviceContext
{
	
public:
	C32DeviceContext()
	{
		Init();
	}

	~C32DeviceContext()
	{
		if (m_Font)
		{
			SelectFont(m_Hdc, m_Font);
			m_Font = NULL;
		}

		if (m_OriginPen)
		{
			SelectPen(m_Hdc, m_OriginPen);
			m_OriginPen = NULL;
		}

		if (m_Brush)
		{
			SelectBrush(m_Hdc, m_Brush);
			m_Brush = NULL;
		}

		

	}

	C32DeviceContext(HDC hdc)
	{
		Init();
		m_Hdc = hdc;
	}

public:
	VOID SetHdc(HDC hdc)
	{
		m_Hdc = hdc;
	}

	// ѡ��Font Ĭ���� : DEFAULT_GUI_FONT
	VOID SelectFont32(HFONT hFont = NULL)
	{
		if (hFont == NULL)
		{
			m_Font = GetStockFont(DEFAULT_GUI_FONT);
			m_OriginFont = SelectFont(m_Hdc, m_Font);
		}else
		{
			m_OriginFont = SelectFont(m_Hdc, hFont);
		}
	}

	// ѡ��Font Ĭ���� : DEFAULT_GUI_FONT
	VOID SelectBrush32(HBRUSH hBrush)
	{
		m_OriginBrush = SelectBrush(m_Hdc, hBrush);	
	}



	VOID Init()
	{
		m_Pen	= NULL;
		m_Font	= NULL;
		m_Brush	= NULL;
		m_Pen	= NULL;
		m_Rng	= NULL; 
		m_Hdc   = NULL;
		m_OriginPen	= NULL;
		m_OriginFont= NULL;
		m_OriginBrush= NULL;
		m_OriginPen= NULL;
		m_OriginRng= NULL; 

	}

public:
	 operator HDC() const
	 {
		return m_Hdc;
	 }
public:
	HPEN	m_Pen;
	HFONT	m_Font;
	HBRUSH	m_Brush;
	HRGN	m_Rng; 
	HDC     m_Hdc;


	HPEN	m_OriginPen;
	HFONT	m_OriginFont;
	HBRUSH	m_OriginBrush;
	HRGN	m_OriginRng; 

};

/*
	��GDI+ �������м򵥵ķ�װ.
*/


class C32GdiPlus 
{
public:
	static ULONG_PTR m_GdiToken;
	static Gdiplus::GdiplusStartupInput m_GdiInput;
	static Gdiplus::GdiplusStartupOutput m_GdiOutput;
	
public:
	static BOOL Initialize()
	{
		
		C32GdiStatus Status = Gdiplus::GdiplusStartup(&C32GdiPlus::m_GdiToken, &C32GdiPlus::m_GdiInput, &C32GdiPlus::m_GdiOutput);
		(Status);
		return (Status == Gdiplus::Ok);

	}
	            
	static VOID Uninitialize()
	{
		Gdiplus::GdiplusShutdown(m_GdiToken);
	}





};

/*
	�����������ã�Ŀǰֻ֧��Dark ����
*/
class C32ThemeStyle
{
public:
	enum E32ThemeStyle
	{
		E32ThemeStyleNormal = 0,
		E32ThemeStyleDark = 1,
	};

	static VOID SetThemeStyle(E32ThemeStyle Style, COLORREF ColorBk, COLORREF FontBk, COLORREF Font)
	{
		m_ThemeStyle = Style;
		m_ColorBk = ColorBk;
		m_ColorFontBk = FontBk;
		m_ColorFont = Font;
		m_HbrBkGnd = CreateSolidBrush(m_ColorBk);

	}

	static VOID SetThemeStyleDark()
	{
		SetThemeStyle(E32ThemeStyleDark, C32ColorDarkBlack1, C32ColorDarkBlack3, C32ColorWhite);
	}


	static BOOL  IsThemeStyleDark()
	{
		return (m_ThemeStyle == E32ThemeStyleDark);
	}

public:
	static E32ThemeStyle m_ThemeStyle;

	static DWORD    m_ColorMode;
	static COLORREF m_ColorBk;
	static COLORREF m_ColorFontBk; 
	static COLORREF m_ColorFont;
	static  COLORREF m_ColorSplit;
	static HBRUSH	m_HbrBkGnd;
	static HFONT    m_FontCustom;


};

class C32ThemeStyleList
{
public:
	C32ThemeStyleList()
	{
		
	}

	~C32ThemeStyleList()
	{


	}
	
	VOID SetThemeStyleNormal();

	VOID SetThemeStyleDark();


	VOID  AddButton(C32Button* Button)
	{
		m_BtnArray.Add(Button);
	}

	VOID AddListView(C32ListView* ListView)
	{
		m_ListViewArray.Add(ListView);
	}

	VOID AddDataTime(C32DateTimeCtrl* DataTime)
	{
		m_DataTimeArray.Add(DataTime);
	}

	VOID AddStatusBar(C32StatusBar* StatusBar)
	{
		m_StatusBarArray.Add(StatusBar);
	}

	VOID AddRichEdit(C32RichEditCtrl* RichEdit)
	{
		m_RichEditArray.Add(RichEdit);
	}

	VOID AddEdit(C32Edit* Edit)
	{
		m_EditArray.Add(Edit);
	}

	VOID AddGroupBox(C32GroupBox* Box)
	{
		m_BoxArray.Add(Box);
	}


public:
	CAtlArray<C32Button*>   m_BtnArray;
	CAtlArray<C32ListView*> m_ListViewArray;
	CAtlArray<C32DateTimeCtrl*> m_DataTimeArray;
	CAtlArray<C32StatusBar*> m_StatusBarArray;
	CAtlArray<C32RichEditCtrl*> m_RichEditArray;
	CAtlArray<C32Edit*>			m_EditArray;
	CAtlArray<C32GroupBox*>		m_BoxArray;



};

/*
	@brief: ������ɫ���á�
	����ɫ�����屳��ɫ��������ɫ
*/

#define C32UICOLOR_BKGND  0x0001
#define C32UICOLOR_BKGND_FONT  0x0002
#define C32UICOLOR_FONT  0x0004
#define C32UICOLOR_ALL (C32UICOLOR_BKGND|C32UICOLOR_BKGND_FONT|C32UICOLOR_FONT)

class C32CColor
{
public:
	C32CColor()
	{
		m_ColorMode = TRANSPARENT;
		m_ColorMask = 0;
		m_HbrBkGnd = NULL;
		m_ColorBk = 0;
		m_ColorSelect = 0;
		m_ColorFontBk = 0;
		m_ColorFont = 0;

		/*if (C32ThemeStyle::IsThemeStyleDark())
		{
			m_ColorBk = C32ThemeStyle::m_ColorBk;
			m_ColorFontBk = C32ThemeStyle::m_ColorFontBk;
			m_ColorFont = C32ThemeStyle::m_ColorFont;
			m_HbrBkGnd = CreateSolidBrush(m_ColorBk);
			m_ColorMask = C32UICOLOR_ALL;
		}*/

	}
	
	~C32CColor()
	{
		if(m_HbrBkGnd)
		{
			DeleteObject(m_HbrBkGnd);
			m_HbrBkGnd = NULL;
		}
	}
	/*
	** ����ɫ�����屳��ɫ��������ɫ��
	*/
	VOID SetUIColor(ULONG ColorMask, COLORREF BkGndColor = 0, COLORREF FontBkGndColor = 0,COLORREF FontColor = 0)
	{
		m_ColorMask = ColorMask;

		m_ColorBk = BkGndColor;
		m_ColorFontBk = FontBkGndColor;
		m_ColorFont = FontColor;
		m_HbrBkGnd = CreateSolidBrush(m_ColorBk);
	}

	BOOL  IsUseBkGnd()
	{
		return (m_ColorMask & C32UICOLOR_BKGND);
	}
	
	BOOL  IsUseFontBkGnd()
	{
		return (m_ColorMask & C32UICOLOR_BKGND_FONT);
	}
	
	BOOL  IsUseFont()
	{
		return (m_ColorMask & C32UICOLOR_FONT);
	}

	BOOL  IsUseColor()
	{
		return(m_ColorMask & (C32UICOLOR_BKGND| C32UICOLOR_BKGND_FONT |C32UICOLOR_FONT));
	}

public:
	ULONG	   m_ColorMode;
	
	ULONG	   m_ColorMask;
	COLORREF   m_ColorBk;
	
	COLORREF   m_ColorFontBk;
	COLORREF   m_ColorFont;

	COLORREF   m_ColorSelect;
	COLORREF   m_ColorSelFont;

	HBRUSH	   m_HbrBkGnd; 


};

class C32RegisterClass
{



};



class C32MouseEvent
{
public:
	C32MouseEvent()
	{

	}

	~C32MouseEvent()
	{


	}

public: //windows message handle

	C32OnXyz(OnNcLButtonUP)

	C32OnXyz(OnNcLButtonDown)

	C32OnXyz(OnMouseMove)

	C32OnXyz(OnMouseHover)

	C32OnXyz(OnMouseLeave)

};

/*
	�¼�(Msg)������
	�¼��ʹ������Ķ�Ӧ��ϵ
	WM_XYZ : OnXyz
	�¼������������ʽ��
	BOOL  OnXyz(WPARAM wParam, LPARAM lParam, LRESULT& lResult);
		���⣺ WM_CREATE, WM_INITDIALOG
	
*/
class C32Event : public C32MouseEvent
{

public:
	C32Event()
	{
		
	}

	virtual ~C32Event()
	{
		
	}

public:
	//ͨ���궨���¼�����

	C32OnXyz(OnCreate)
	
	C32OnXyz(OnClose)

	C32OnXyz(OnSize)

	C32OnXyz(OnCommand)
	
	C32OnXyz(OnNotify)

	C32OnXyz(OnDrawItem)

	C32OnXyz(OnPaint)

	C32OnXyz(OnNcDestroy)

	C32OnXyz(OnContextMenu)
	
	C32OnXyz(OnDestroy)

	C32OnXyz(OnLButtonDown)

	C32OnXyz(OnNcLButtonDown)

	C32OnXyz(OnLButtonUp)
	
	C32OnXyz(OnGetMinMaxInfo)

	C32OnXyz(OnMeasureItem)

	C32OnXyz(OnDefalutHandle)

	//�˵�����

	C32OnXyz(OnInitMenu)

	C32OnXyz(OnInitMenuPopup)

	C32OnXyz(OnUnInitMenuPopup)

	//��ɫ
	C32OnXyz(OnEraseBkgnd)

	//WM_CTLCOLORSTATIC
	C32OnXyz(OnCtlColorStatic)

	//WM_CTLCOLOR
	C32OnXyz(OnCtlColor)

	//WM_CTLCOLORBTN
	C32OnXyz(OnCtlColorBtn)

	//WM_CTLCOLORLISTBOX
	C32OnXyz(OnCtlColorListBox)

	//WM_CTLCOLOREDIT
	C32OnXyz(OnCtlColorEdit)

	C32OnXyz(OnNcPaint)


	//��������Ϣ
	C32OnXyz(OnKeyUp)

	C32OnXyz(OnKeyDown)

	/*
		�û������Window Message
	*/
	C32OnXyz(OnC32Create)

	C32OnXyzM(OnDefault)

	/*
		��ʱ��
	*/
	C32OnXyz(OnTimer);
	

};

class C32EventCallback
{
public:
	C32EventCallback()
	{
		Init();
	}

	~C32EventCallback()
	{

	}

	VOID Init()
	{
		m_OnCreate = NULL;
		m_OnDestroy = NULL;
		m_OnCommand = NULL;
		m_OnSize = NULL;
		m_OnContextMenu = NULL;
		m_OnCommandMenu = NULL;
		m_OnDrawItem = NULL;
	}

public:
	

	VOID SetEventCreate(C32_EVENT_CALLBACK_CREATE Callback)
	{
		m_OnCreate = Callback;
	}

	VOID SetEventDestroy(C32_EVENT_CALLBACK_DESTROY Callback)
	{
		m_OnDestroy = Callback;
	}


	VOID SetEventCommand(C32_EVENT_CALLBACK Callback)
	{
		m_OnCommand = Callback;
	}

	VOID SetEventSize(C32_EVENT_CALLBACK_ONSIZE Callback)
	{
		m_OnSize = Callback;
	}

	VOID SetEventContextMenu(C32_EVENT_CALLBACK_CONTEXTMENU Callback)
	{
		m_OnContextMenu = Callback;
	}

	VOID SetEventCommandMenu(C32_EVENT_CALLBACK_COMMAND_MENU Callback)
	{
		m_OnCommandMenu = Callback;
	}

	VOID SetEventDrawItem(C32_EVENT_CALLBACK_DRAW_ITEM Callback)
	{
		m_OnDrawItem = Callback;
	}


public: //Window Message
	C32_EVENT_CALLBACK_CREATE m_OnCreate;
	C32_EVENT_CALLBACK_DESTROY m_OnDestroy;

	C32_EVENT_CALLBACK m_OnCommand;
	C32_EVENT_CALLBACK_ONSIZE m_OnSize;
	C32_EVENT_CALLBACK_CONTEXTMENU m_OnContextMenu;
	C32_EVENT_CALLBACK_COMMAND_MENU  m_OnCommandMenu;

	////Draw Item
	C32_EVENT_CALLBACK_DRAW_ITEM   m_OnDrawItem;
};


class C32StaticEventCallback
{
	
public:
	C32StaticEventCallback()
	{
		Init();
	}

	~C32StaticEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnClick = NULL;
		m_OnDClick = NULL;
	}

	VOID SetEventClick(C32_EVENT_CALLBACK_STATIC_CLICK Callback)
	{
		m_OnClick = Callback;
	}

	VOID SetEventDClick(C32_EVENT_CALLBACK_STATIC_CLICK Callback)
	{
		m_OnDClick = Callback;
	}


	//Static Control Event
	C32_EVENT_CALLBACK_STATIC_CLICK m_OnClick; //���
	C32_EVENT_CALLBACK_STATIC_DCLICK m_OnDClick;//˫��
	
};

class C32SysLinkEventCallback
{

public:
	C32SysLinkEventCallback()
	{
		Init();
	}
	~C32SysLinkEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnClick = NULL;
	}

	VOID SetEventClick(C32_EVENT_CALLBACK_SYSLINK_CLICK Callback)
	{
		m_OnClick = Callback;
	}


	//SysLink Control Event
	C32_EVENT_CALLBACK_SYSLINK_CLICK m_OnClick; //���
};

class C32ButtonEventCallback
{

public:
	C32ButtonEventCallback()
	{
		Init();
	}
	~C32ButtonEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnClick = NULL;
		m_OnDClick = NULL;
	}

	VOID SetEventClick(C32_EVENT_CALLBACK_BUTTON_CLICK Callback)
	{
		m_OnClick = Callback;
	}

	VOID SetEventDClick(C32_EVENT_CALLBACK_BUTTON_DCLICK Callback)
	{
		m_OnDClick = Callback;
	}

	//Button Control Event
	C32_EVENT_CALLBACK_BUTTON_CLICK m_OnClick; //���
	C32_EVENT_CALLBACK_BUTTON_DCLICK m_OnDClick;//˫��
};

class C32DialogEventCallback
{

public:
	C32DialogEventCallback()
	{
		Init();
	}
	~C32DialogEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnInitDialog = NULL;
	}
	
	VOID SetEventDialogInit(C32_EVENT_CALLBACK_DIALOG_INIT Callback)
	{
		m_OnInitDialog = Callback;
	}
	//Dialog Event Callback
	C32_EVENT_CALLBACK_DIALOG_INIT  m_OnInitDialog; //WM_INIT_DIALOG
	
};


class C32Icon
{
public:
	static HINSTANCE hInstance;
public:
	C32Icon()
	{
		Init();
	}
	~C32Icon()
	{
		Destroy();
	}
public:
	operator HICON()
	{
		return m_Icon;
	}

public:
	VOID Init()
	{
		m_Icon = NULL;
	}
	VOID Destroy()
	{
		if (m_Icon)
		{
			DestroyIcon(m_Icon);
			m_Icon = NULL;
		}
	}

	BOOL Load(int ResourceId)
	{
		Destroy();

		m_Icon = LoadIcon(hInstance, MAKEINTRESOURCE(ResourceId));

		return (m_Icon != NULL);
	}


	HICON m_Icon;
};

/*
	@breif: ���ڷŴ���Сʱ���ؼ��ı��С��λ�á�
	��ס�� ����Ϊλ�úʹ�Сͬʱ�仯ʱ��̫�����ˣ�������
	m_SwpFlag : ��¼�仯����
	m_SwpPos;  //λ�ò���ʱ����Ե��������
	m_SwpSize; //��С����ʱ����Ե��������
	m_Margin;  //��¼�ؼ��ڴ������Ե���ϱ�Ե���ұ�Ե�±�Ե�����ʼֵ���Դ����ο�.

	˳�� �Դ��ϵ��£�������Ϊ�Ⱥ�˳����
	��С����Ŀؼ�һ��Ϊ
		Button ComboBox
			���ϱ߾಻�䣺֮ǰû�пɱ��С�Ŀؼ�
			���±߾಻�䣺֮ǰ�пɱ��С�Ŀؼ�
	λ�ò���Ŀؼ�һ��Ϊ
		ListView TreeView Edit ...
			���ϱ߾಻�䣺 ��Ϊλ���Ѿ����䡣���ϱ߾��Ѿ�ʧȥ������
			���±߾಻�䣺

*/
class C32PosSize
{
public:
	C32PosSize()
	{
		Init();
	}

	~C32PosSize()
	{

	}

public:
	VOID Init()
	{
		SetRectEmpty(&m_SwpPos);
		SetRectEmpty(&m_SwpSize);
		SetRectEmpty(&m_Margin);
		SetRectEmpty(&m_Content);
		RtlZeroMemory(&m_SizeWindow,sizeof(SIZE));
		RtlZeroMemory(&m_SwpSizeFlag,sizeof(SIZE));
		
		m_SwpFlag = 0;  

		m_PosVisible = TRUE;
	}

	VOID CalPosSize(POINT& Pt, SIZE& Size)
	{
			if (m_SwpFlag& SWP_NOSIZE) //��С���䣬λ�ñ�
			{
				if (m_SwpSize.left)  //��߾಻��
				{
					Pt.x = m_Margin.left;
				}
				if (m_SwpSize.top) //�ϱ߾಻��
				{
					Pt.y = m_Margin.top;
				}
				if (m_SwpSize.right) //�ұ߾಻��
				{
					Pt.x = m_SizeWindow.cx - m_Margin.right -C32GetRectWidth(m_Content);
				} 
				if (m_SwpSize.bottom) //�±߾಻��
				{
					Pt.y = m_SizeWindow.cy -m_Margin.bottom - C32GetRectHeight(m_Content);
				}
			}

			if (m_SwpFlag& SWP_NOMOVE)
			{
				//λ�ò��䣬��С��
				
				if (m_SwpSizeFlag.cx == 1) //���Ȳ���
				{
					Size.cx = C32GetRectWidth(m_Content);
				}else                   //���ȱ�
				{
					if (m_SwpPos.right)
					{
						Size.cx = m_SizeWindow.cx - m_Margin.right - m_Content.left;
					}
				}
				if (m_SwpSizeFlag.cy == 1) //�߶Ȳ���
				{
					Size.cy = C32GetRectHeight(m_Content);
				}else
				{
					if (m_SwpPos.bottom)
					{
						Size.cy = m_SizeWindow.cy - m_Margin.bottom - m_Content.top;
					}
				}
				
			}
		
	}

	/*
		��С����ʱ,��Ե��������
	*/
	VOID SetNoSizeLeftTop()
	{
		m_SwpFlag |= SWP_NOSIZE;		
		m_SwpSize.left = 1;
		m_SwpSize.top  = 1;

		m_SwpSize.right = 0;
		m_SwpSize.bottom = 0;
	}

	VOID SetNoSizeLeftBottom()
	{
		m_SwpFlag |= SWP_NOSIZE;		
		m_SwpSize.left = 1;
		m_SwpSize.top  = 0;

		m_SwpSize.right = 0;
		m_SwpSize.bottom = 1;
	}

	VOID SetNoSizeRightBotton()
	{
		m_SwpFlag |= SWP_NOSIZE;		
		m_SwpSize.left = 0;
		m_SwpSize.top  = 0;

		m_SwpSize.right = 1;
		m_SwpSize.bottom = 1;
	}

	VOID SetNoSizeRightTop()
	{
		m_SwpFlag |= SWP_NOSIZE;
		
		m_SwpSize.left = 0;
		m_SwpSize.top  = 1;

		m_SwpSize.right = 1;
		m_SwpSize.bottom = 0;
	}

	VOID SetNoMoveHeigthRight()
	{
		m_SwpSizeFlag.cy = 1;
		m_SwpFlag |= SWP_NOMOVE;

		m_SwpPos.right = 1;
		m_SwpPos.bottom = 0;
	}

	VOID SetNoWidthBottom()
	{
		m_SwpSizeFlag.cx = 1;
		m_SwpFlag |= SWP_NOMOVE;

		m_SwpPos.right = 0;
		m_SwpPos.bottom = 1;
	}

	VOID SetNoMoveRightTop()
	{
		m_SwpFlag |= SWP_NOMOVE;

		m_SwpPos.right = 1;
		m_SwpPos.top = 1;
	}

	VOID SetNoMoveLeftTop()
	{
		m_SwpFlag |= SWP_NOMOVE;

		m_SwpPos.left = 1;
		m_SwpPos.top = 1;
	}

	VOID SetNoMoveRightBottom()
	{
		m_SwpFlag |= SWP_NOMOVE;

		m_SwpPos.right = 1;
		m_SwpPos.bottom = 1;
	}

	VOID SetNoMoveLeftBottom()
	{
		m_SwpFlag |= SWP_NOMOVE;
		m_SwpSize.right = 1;
		m_SwpSize.top  = 0;
		m_SwpPos.left = 0;
		m_SwpPos.bottom = 1;
	}


public:
	RECT  m_SwpPos;  //λ�ò���ʱ����Ե��������
	RECT  m_SwpSize; //��С����ʱ����Ե��������
	SIZE m_SwpSizeFlag; // ���Ƹ߶ȺͿ���Ƿ�仯
	DWORD m_SwpFlag;
	RECT  m_Margin;  //��¼�ؼ��ڴ������Ե���ϱ�Ե���ұ�Ե�±�Ե����
	RECT  m_Content; //�ؼ��ڴ���Client���е�λ��
	SIZE  m_SizeWindow; //����Client���С

public:
	BOOL  m_PosVisible;

};

class C32ImageList
{
public:
#define IMAGE_LIST_INITIAL_COUNT 32
#define IMAGE_LIST_GROUW_COUNT  10
	static HINSTANCE hInstance;
public:
	C32ImageList():m_List(NULL),m_bDestroy(FALSE)
	{

	}

	C32ImageList(HIMAGELIST hImageList)
	{
		m_List = hImageList;
		m_bDestroy = FALSE;
	}

	~C32ImageList()
	{
		Destroy();
	}

	operator HIMAGELIST() const
	{
		return m_List;
	}

	HIMAGELIST Create(int Cx, int Cy, UINT Flags, int Initial = IMAGE_LIST_INITIAL_COUNT, int Grow = IMAGE_LIST_GROUW_COUNT)
	{
		m_CxIcon = Cx;
		m_CyIcon = Cy;
		m_List = ImageList_Create(Cx, Cy, Flags, Initial, Grow);
		m_bDestroy = TRUE;
		return m_List; 
	}

	HIMAGELIST CreateMetrics(int MetricsIndexX, int MetricsIndexY)
	{
		DWORD Cx = GetSystemMetrics(MetricsIndexX);
		DWORD Cy = GetSystemMetrics(MetricsIndexY);
		return Create(Cx, Cy, ILC_COLOR32);
	}

	
	HIMAGELIST CreateSmall()
	{
		return CreateMetrics(SM_CXSMICON, SM_CYSMICON);
	}

	HIMAGELIST CreateNormal()
	{
		return CreateMetrics(SM_CXICON, SM_CYICON);
	}

	VOID LoadSmallIcons(int IconArrayCount, int* IconArray)
	{
		CreateSmall();

		for(int i = 0; i < IconArrayCount; i++)
		{
			AddIcon(IconArray[i]);
		}
	}

	VOID LoadNormalIcons(int IconArrayCount, int* IconArray)
	{
		CreateNormal();

		for(int i = 0; i < IconArrayCount; i++)
		{
			AddIcon(IconArray[i]);
		}
	}


	VOID Destroy()
	{
		if (m_List&& m_bDestroy == TRUE)
		{
			ImageList_Destroy(m_List);
		}
		m_List = NULL;
		m_bDestroy = TRUE;
	}

	int  AddIcon(HICON hIcon)
	{
		int Index = -1;
	
		if (m_List)
			Index = ImageList_AddIcon(m_List, hIcon);
	
		return Index;
	}

	/*
		Resource �ļ����ICON id
	*/
	int AddIcon(INT ResourceId)
	{
		int Index = -1;
		LPWSTR Id = MAKEINTRESOURCE(ResourceId);
		HICON hIcon = LoadIcon(C32ImageList::hInstance, Id);

		if (hIcon)
		{
			Index = AddIcon(hIcon);
		}
		DestroyIcon(hIcon);

		return Index;
	}

	BOOL Remove(int Index)
	{
		return ImageList_Remove(m_List, Index);
	}

	COLORREF SetBkColor(__in COLORREF color)
	{
		return ImageList_SetBkColor(m_List, color);
	}

	VOID SetImageList(HIMAGELIST hImageList)
	{
		m_List = hImageList;
	}

	BOOL GetIconSize(PSIZE lpSize)
	{
		BOOL Ret;
		SIZE Size = {};
		Ret = ImageList_GetIconSize(m_List, (int*)&Size.cx, (int*)&Size.cy);
		if (Ret)
		{
			*lpSize = Size;
		}
		return Ret;
	}
	
	VOID Attach(HIMAGELIST hImageList)
	{
		m_List = hImageList;
		m_bDestroy = FALSE;
	}

	VOID Detach()
	{
		m_List = NULL;
	}

	BOOL Draw(HDC Hdc, int iIndex, int xPos, int yPos,INT fStyle)
	{
		return ImageList_Draw(m_List, iIndex, Hdc, xPos, yPos, fStyle);
	}
	
	BOOL DrawEx(HDC hdcDst, int iIndex, int x,int y,int dx,int dy,COLORREF rgbBk,COLORREF rgbFg,UINT fStyle)
	{
		return ImageList_DrawEx(m_List,iIndex,hdcDst, x, y, dx, dy, rgbBk, rgbFg, fStyle);

	}



	HIMAGELIST GetList()
	{
		return m_List;
	}

	VOID Init()
	{
		m_List = NULL;
		m_bDestroy = TRUE;
	}

	

public:
	HIMAGELIST m_List;
	int        m_CxIcon;
	int        m_CyIcon;
	BOOL      m_bDestroy;

};
 /*
	C32Windows �����͡�
	�� Win32 Control �ṩ�Ļ����ؼ�һһ��Ӧ��
	���������������ȡ�Ǻ��ֿؼ�

 */
enum C32CtrlType
{
	C32CtrlTypeUnknown,
	C32CtrlTypeStatic ,
	C32CtrlTypeBox,
	C32CtrlTypeButton,
	C32CtrlTypeEdit,
	C32CtrlTypeCommbox,
	C32CtrlTypeHeader,
	C32CtrlTypeListView,
	C32CtrlTypeTreeView,
	C32CtrlTypeStatusBar,
	C32CtrlTypeStatusBarToolBar,
	C32CtrlTypeDialog,
	C32CtrlTypeContainer
};



class C32Window : public C32Event, public C32EventCallback,
				 public C32PosSize, public C32CColor
{
public:  
	static BOOL     m_MainIsExit; 
	static LRESULT CALLBACK C32WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		BOOL    Handle = FALSE;
		LRESULT lResult = 0;
		 LPCWSTR Title;
		C32Window* This;
		This =  (C32Window*)C32GetUserData(hwnd);
		
		char* sMsg = C32DbgGetWindowMsgString(uMsg);
		Title = (This ? This->m_StringText.GetString(): L"NULL");
		if (sMsg != NULL)
			ZxDebug((__FUNCTION__"():: Title %ws sMsg: %s :hwnd: %p :C32Window: %p wParam:%p lParam: %p \n",Title, sMsg, hwnd, This, wParam, lParam));
		    
		switch(uMsg)
		{ 
			case WM_CREATE:
				 {
					LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
					This = (C32Window*)lpcs->lpCreateParams;
					This->Attach(hwnd) ;
					Handle = This->OnCreate(wParam, lParam, lResult);
					This->SetUserData();
				 }
				 break; 
			
			case WM_SIZE:
				Handle = This->OnSize(wParam, lParam, lResult);
				break;
			case WM_PAINT:
				Handle = This->OnPaint(wParam, lParam, lResult);
				break;
			case WM_NCPAINT:
				Handle = This->OnNcPaint(wParam, lParam, lResult);
				break;
			case WM_NOTIFY:
				Handle = This->OnNotify(wParam, lParam, lResult);
				break;
			case WM_DRAWITEM:
				Handle = This->OnDrawItem(wParam, lParam, lResult);
				break;
			case WM_COMMAND:
				Handle = This->OnCommand(wParam, lParam, lResult);
				break;
			
			case WM_CONTEXTMENU:
				Handle = This->OnContextMenu(wParam, lParam, lResult);
				break; 
			case WM_LBUTTONDOWN: 
				Handle = This->OnLButtonDown(wParam, lParam, lResult);
				break;
			case WM_NCLBUTTONDOWN:
				Handle = This->OnNcLButtonDown(wParam, lParam, lResult);
				break;
			case WM_LBUTTONUP:
				Handle = This->OnLButtonUp(wParam, lParam, lResult);
				break;
			case WM_MOUSEMOVE:
				Handle = This->OnMouseMove(wParam, lParam, lResult);
				break;
			case WM_MOUSEHOVER:
				Handle = This->OnMouseHover(wParam, lParam, lResult);
				break;
			case WM_MOUSELEAVE:
				Handle = This->OnMouseLeave(wParam, lParam, lResult);
				break;



			case WM_MEASUREITEM:
				Handle = This->OnMeasureItem(wParam, lParam, lResult);
				break;

			case WM_ERASEBKGND:
				Handle = This->OnEraseBkgnd(wParam, lParam, lResult);
				break;

			//�ؼ�����ɫ����
			case WM_CTLCOLORSTATIC:
				Handle = This->OnCtlColorStatic(wParam, lParam, lResult);
				break;
			case WM_CTLCOLOR:
				Handle = This->OnCtlColor(wParam, lParam, lResult);
				break;
			//�˵�����
			case WM_INITMENU:
				Handle = This->OnInitMenu(wParam, lParam, lResult);
				break;
			case WM_INITMENUPOPUP:
				Handle = This->OnInitMenuPopup(wParam, lParam, lResult);
				break;
			case WM_UNINITMENUPOPUP:
				Handle = This->OnUnInitMenuPopup(wParam, lParam, lResult);
				break;

			case WM_KEYUP:
				Handle = This->OnKeyUp(wParam, lParam, lResult);
				break;
			case WM_KEYDOWN:
				Handle = This->OnKeyDown(wParam, lParam, lResult);
				break;
			case WM_CLOSE:
				Handle = This->OnClose(wParam, lParam, lResult);
				break;
			case C32_WM_CREATE: 
				Handle = This->OnC32Create(wParam, lParam, lResult);
				break;
			case WM_DESTROY:
				Handle = This->OnDestroy(wParam, lParam, lResult);
				if(This->IsDelete())
					delete This;
				break;
			case WM_NCDESTROY:
				Handle = This->OnNcDestroy(wParam, lParam, lResult);
				break;
			case WM_TIMER:
				Handle = This->OnTimer(wParam, lParam, lResult);
				break;
			default:
				if (This)
					Handle = This->OnDefault(uMsg, wParam, lParam, lResult);
				break;
		}

		if (Handle == FALSE)
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		return lResult;

	}

public:
	C32Window()
	{
		Init();
	}

	C32Window(HWND Hwnd)
	{
		Init();
		m_Hwnd = Hwnd;
		GetClientRect(m_Hwnd, &m_ClientRect);
		GetWindowRect(m_Hwnd, &m_Rect);
	}

	virtual ~C32Window()
	{
		if (m_Hwnd && !m_Attach)
		{
			C32SetUserData(m_Hwnd, NULL);			
			m_Hwnd = NULL;
		}
		DeleteFont32();

		if (m_SubWndProc)
		{
		}

		if (m_hbrBackground)
		{
			DeleteObject(m_hbrBackground);
			m_hbrBackground = NULL;
		}

	}

	int GetClassName(__out LPWSTR ClassName,   int nMaxCount)
	{
		 return ::GetClassName(m_Hwnd, ClassName, nMaxCount);
	}

	static DWORD RegisterClassEx32(LPCWSTR lpszClassName, 
							WNDPROC lpfnWndProc = NULL, 
							HCURSOR hCursor = NULL,
							HBRUSH hBackGround = NULL, 
							int MenuResorseId = 0,
							int IconId = NULL,
							int IconSmId = NULL)
	{
		WNDCLASSEX wcex = {};

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= lpfnWndProc ? lpfnWndProc : C32Window::C32WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= C32Hinstance;
		wcex.hIcon			= (IconId?LoadIcon(C32Hinstance, MAKEINTRESOURCE(IconId)):NULL);
		wcex.hbrBackground	= hBackGround ? hBackGround :(HBRUSH)(COLOR_WINDOW + 1);
		wcex.hCursor		= hCursor ? hCursor : LoadCursor(NULL, IDC_ARROW);
		wcex.lpszMenuName	= MenuResorseId == 0 ? NULL : MAKEINTRESOURCE(MenuResorseId);
		wcex.lpszClassName	= lpszClassName;
		wcex.hIconSm		= (IconSmId?LoadIcon(C32Hinstance, MAKEINTRESOURCE(IconSmId)):NULL);

		ATOM Atom = RegisterClassEx(&wcex);
		ZxDebugEx((__FUNCTION__"():: ClassName: %ws Atom: %d Error: %d\n", lpszClassName,Atom, GetLastError()));
		return Atom;
	}

	static DWORD RegisterClassEx32(LPCWSTR lpszClassName,  
		LPCWSTR iCursor ,
		LONG_PTR hBackGround , 
		int MenuResorseId ,
		int IconId ,
		int IconSmId,
		WNDPROC lpfnWndProc)
	{
		WNDCLASSEX wcex = {};

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= lpfnWndProc ? lpfnWndProc : C32Window::C32WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= C32Hinstance;
		wcex.hIcon			= (IconId?LoadIcon(C32Hinstance, MAKEINTRESOURCE(IconId)):NULL);
		wcex.hbrBackground	= hBackGround ? (HBRUSH)hBackGround :(HBRUSH)(COLOR_WINDOW+1);
		wcex.hCursor		= iCursor ? LoadCursor(NULL, iCursor)  : LoadCursor(NULL, IDC_ARROW);
		wcex.lpszMenuName	= MenuResorseId == 0 ? NULL : MAKEINTRESOURCE(MenuResorseId);
		wcex.lpszClassName	= lpszClassName;
		wcex.hIconSm		= (IconSmId?LoadIcon(C32Hinstance, MAKEINTRESOURCE(IconSmId)):NULL);

		ATOM Atom = RegisterClassEx(&wcex);

		ZxDebugEx((__FUNCTION__"():: ClassName: %ws Atom: %d Error: %d\n", lpszClassName,Atom, GetLastError()));

		return Atom;
	}

	/*
		������ģʽ�Ի�����ֵ�ʱ������ʵ��
	*/
	BOOL IsDialogMessageC32(LPMSG lpMsg)
	{

		return FALSE;
	}
	
	int Loop()
	{
		MSG msg;
		BOOL bRet;
		HACCEL hAccelTable;
		if(m_iAccelerator)
		hAccelTable = LoadAccelerators(C32Hinstance, MAKEINTRESOURCE(m_iAccelerator));

		// Main message loop:
		while ((bRet =GetMessage(&msg, NULL, 0, 0)) != 0)
		{
			if (bRet == -1)
			{
				// handle the error and possibly exit
				assert(0);
			}

			if (msg.message == WM_QUIT)
				break;
			//��ģʽ�Ի���
			if(IsDialogMessageC32(&msg) == TRUE)
				continue;
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			/*if (msg.message == WM_KEYUP)
			{
				OnKeyUp(msg.hwnd, msg.wParam, msg.wParam, msg.lParam);
			}else if(msg.message == WM_KEYDOWN)
			{
				OnKeyDown(msg.hwnd, msg.wParam, msg.wParam, msg.lParam);
			}*/


		}
		if( msg.message == WM_QUIT )
		{
			::PostQuitMessage((int)msg.wParam);
		}
		return (int) msg.wParam;
	}

	DWORD RegisterClassNew(LPCWSTR lpwszClassName)
	{
		DWORD Atom = RegisterClassEx32(lpwszClassName, m_iCursor, m_iBackground, m_iMenu, m_iIcon,m_iIconSmall, m_WndProc);
		return Atom;
	}
	
	virtual HWND Create(DWORD ExStyle, LPCWSTR lpwszClassName,LPCWSTR lpwszWindowName,DWORD Style, int xPos, int yPos, int Cx, int Cy, HWND hwnd)
	{
		m_Hwnd = CreateWindowEx(ExStyle,lpwszClassName, lpwszWindowName, Style, xPos,yPos, Cx, Cy, hwnd, NULL, C32Hinstance,this);
		if (m_Hwnd)
		{
			Attach(m_Hwnd);
		}
		ZxDebugEx((__FUNCTION__"()::%ws::%ws m_Hwnd : %p This : %p Parent:%p Code: %d\n", lpwszClassName,lpwszWindowName,m_Hwnd, this, hwnd, GetLastError()));
		return m_Hwnd;
	}

	BOOL Show(int nCmdShow)
	{
		BOOL Ret = FALSE;
		if (m_Hwnd)
		{
			Ret = ShowWindow(m_Hwnd, nCmdShow);
			Ret = UpdateWindow(m_Hwnd);
		}
		return Ret;
	}

	BOOL Hide()
	{
		BOOL Ret = FALSE;
		if (m_Hwnd)
		{
			Ret = ShowWindow(m_Hwnd, SW_HIDE);
		}
		return Ret;
	}

	VOID SetRegister(LPCWSTR ClassName, int iIcon = 0, int iIconSmall = 0, int iMenu = 0,LPCWSTR iCursor = IDC_ARROW, int iBackGround = COLOR_WINDOWFRAME, WNDPROC lpfnWndProc = NULL)
	{
		m_iIcon = 0;
		m_iIconSmall = iIconSmall;
		m_iCursor = iCursor;
		m_iBackground = iBackGround;
		m_iMenu = iMenu;
		if (ClassName)
			wcscpy_s(m_ClassName, 127, ClassName);
		m_WndProc = lpfnWndProc;

	}
	
	VOID InitPosSize()
	{
		m_Cx = 0;
		m_Cy = 0;
		RtlZeroMemory(&m_Rect, sizeof(RECT));
		m_ClientCx = 0;
		m_ClientCy = 0;

		m_MinCx = 0;
		m_MinCy = 0;

		RtlZeroMemory(&m_ClientRect, sizeof(RECT));

	}

	operator HWND () const
	{
		return m_Hwnd;
	}
	
	C32Window& operator =(HWND Hwnd)
	{
		SetHwnd(Hwnd);
		return *this;
	}
	
	VOID Attach(HWND Hwnd)
	{
		m_Hwnd = Hwnd;
		m_Attach = TRUE;
		SetUserData(); 
		GetPos();
		SetMargin();
		GetWindowText32();
	}

	VOID Detach()
	{
		m_Hwnd = NULL;
	}

public:// visual style 
	BOOL SetVisualStyle(LPCWSTR Theme)
	{
		BOOL Ret = FALSE;
		if (m_Hwnd)
		{
			Ret = ::SetWindowTheme(m_Hwnd, Theme, NULL);
			Ret = (Ret == S_OK ? TRUE : FALSE);
		}
		return Ret;
	}

	BOOL SetExplorerTheme()
	{
		return SetVisualStyle(L"Explorer");
	}

	VOID GetPos()
	{
		GetClientRect(m_Hwnd, &m_ClientRect);
		GetWindowRect(m_Hwnd, &m_Rect);

		m_ClientCx = C32GetRectWidth(m_ClientRect);
		m_ClientCy = C32GetRectHeight(m_ClientRect);

		m_Cx =  C32GetRectWidth(m_Rect);
		m_Cy = C32GetRectHeight(m_Rect);
	}

	BOOL GetCursorPos32(POINT& Pt)
	{
		BOOL bRet = FALSE;
		RtlZeroMemory(&Pt, sizeof(POINT));
	
		if (GetCursorPos(&Pt))
		{
			if (ScreenToClient(m_Hwnd, &Pt))
				bRet = TRUE;
		}

		ZxDebug((__FUNCTION__"():: {%d, %d} \n", Pt.x, Pt.y));
		return bRet;
	}

	VOID SetMargin()
	{
		GetContentRect();

		m_Margin.left = m_Content.left;
		m_Margin.top = m_Content.top;
		RECT rc = GetParentClient();
		m_Margin.right = C32GetRectWidth(rc) - m_Content.right;
		m_Margin.bottom = C32GetRectHeight(rc)  - m_Content.bottom;
	
	}

	RECT GetParentClient()
	{
		RECT rc = {};
		m_Parent = m_Parent? m_Parent : GetParent(m_Hwnd);

		if (m_Parent)
		{
			GetClientRect(m_Parent, &rc);
		}

		return rc;
	}

	//����Ļ�������Σ�ת���ɸô�������ڸ�����Client��Ϊ����ľ���
	RECT GetContentRect()
	{
		BOOL bConvert = FALSE;
		RECT  rcRet = {};
		GetPos();
		POINT Pt={m_Rect.left, m_Rect.top};
		if (m_Hwnd)
		{
			HWND Parent = m_Parent ? m_Parent :GetParent(m_Hwnd);	
			if (ScreenToClient(Parent, &Pt))
			{
				rcRet.left = Pt.x;
				rcRet.top = Pt.y;
				rcRet.right = Pt.x + C32GetRectWidth(m_Rect);
				rcRet.bottom = Pt.y + C32GetRectHeight(m_Rect);
			}
			m_Parent = Parent;
		}
		m_Content = rcRet;
		
		return rcRet;

	}

	BOOL ScreenToClient32(PPOINT Point)
	{
		BOOL bRet = ScreenToClient(m_Hwnd, Point);

		return (bRet ? TRUE : FALSE);
	}

	BOOL ScreenToClient32(int xPos, int yPos, PPOINT Point)
	{
		Point->x = xPos;
		Point->y = yPos;
		BOOL bRet = ScreenToClient(m_Hwnd, Point);
		
		return (bRet ? TRUE : FALSE);
	}

	BOOL SetPos(int X, int Y, int Cx, int Cy,  UINT Flag = SWP_NOZORDER,HWND hWndInsertAfter = NULL)
	{
		if (m_Hwnd == NULL)
			return FALSE; 
		
		BOOL bRet = SetWindowPos(m_Hwnd, hWndInsertAfter, X, Y, Cx, Cy, Flag);
		//BOOL bRet = MoveWindow(m_Hwnd,  X, Y, Cx, Cy, TRUE);
		if (bRet == FALSE)
		{
			int i = 0;
		}
		GetPos();
		return bRet;
	}
	
	BOOL SetCenterPos(HWND Parent = NULL)
	{ 
		HWND Target = (Parent ? Parent : GetParent(m_Hwnd));
		if (Target == NULL)
			return FALSE;
		RECT Rect = {};
		GetPos();
		GetWindowRect(Target, &Rect);
		int X = (Rect.left + Rect.right)/2 - C32GetRectWidth(m_Rect)/2;
		int Y = (Rect.top + Rect.bottom)/2 - C32GetRectHeight(m_Rect)/2;
		return SetPos(X, Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	BOOL GetCenterPos(LPPOINT Point)
	{
		GetPos();
		RECT Rect = m_ClientRect;
		int X = (Rect.left + Rect.right)/2 ;
		int Y = (Rect.top + Rect.bottom)/2;
		Point->x = X;
		Point->y = Y;
		return (X !=0 && Y != 0);
	}

	VOID SetMinCxy(int Cx = -1, int Cy = -1)
	{
		if (Cx == -1 || Cy == -1)
		{
			SIZE Size = GetWindowSize();
			Cx = Size.cx;
			Cy = Size.cy;
		}
		m_MinCx = Cx;
		m_MinCy = Cy;
	}
	//Style

	DWORD GetStyle()
	{
		DWORD Style = (DWORD)GetWindowLongPtr(m_Hwnd, GWL_STYLE);
		return Style;
	}

	DWORD SetStyle(DWORD Style)
	{
		return (DWORD)SetWindowLongPtr(m_Hwnd, GWL_STYLE, (LONG_PTR)Style);
	}
	/*
		����Style
	*/
	BOOL AddStyle(DWORD Style)
	{
		DWORD Style0 = 0;
		DWORD dwStyle = GetStyle();
		dwStyle |= Style;

		SetStyle(dwStyle);
		Style0 = GetStyle();

		if (Style0&Style)
			return TRUE;
		else
			return FALSE;
	}

	BOOL ClearStyle(DWORD Style)
	{
		DWORD Style0 = 0;
		DWORD dwStyle = GetStyle();
		dwStyle &= ~Style;

		SetStyle(dwStyle);
		Style0 = GetStyle();

		if (Style0&Style)
			return FALSE;
		else
			return TRUE;
	}

	 BOOL  ModifyStyle(HWND hWnd, int nStyleOffset,
		DWORD dwRemove, DWORD dwAdd, UINT nFlags)
	{
		ASSERT(hWnd != NULL);
		DWORD dwStyle = (DWORD)::GetWindowLongPtr(hWnd, nStyleOffset);
		DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
		if (dwStyle == dwNewStyle)
			return FALSE;

		::SetWindowLong(hWnd, nStyleOffset, dwNewStyle);
		if (nFlags != 0)
		{
			::SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
				SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
		}
		return TRUE;
	}

	 BOOL ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
	 {
		 return ModifyStyle(hWnd, GWL_EXSTYLE, dwRemove, dwAdd, nFlags);
	 }

	VOID ReflushWindow()
	{
		SetWindowPos(m_Hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER  );
	}

	VOID RedrawWindow32()
	{
		//InvalidateRect(m_Hwnd, NULL, TRUE);
		RedrawWindow(m_Hwnd, NULL, NULL, RDW_INVALIDATE|RDW_ERASE);
		UpdateWindow(m_Hwnd);
	}

	VOID DragFullWindows()
	{
		BOOL m_bDragFullWindow = NULL;
		// 1����ѯ��ǰϵͳ���϶���ʾ�������ݡ�����
		SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, (PVOID)&m_bDragFullWindow, NULL);

		// 2�������Ҫ�޸����ã�����ÿ�ν���CDialog::OnNcLButtonDownĬ�ϴ���֮ǰ�޸�
		if(m_bDragFullWindow)
			SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, NULL);

		// 3��Ĭ�ϴ���ϵͳ���Զ��������

		// 4��Ĭ�ϴ�����Ϻ󣬻�ԭϵͳ����
		if(m_bDragFullWindow)
			SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, NULL);

	}

	VOID SetDragFullWindows(BOOL bDragFullWindows = TRUE)
	{
		m_DrawFullWindowsFlag = bDragFullWindows;
	}

public:
	VOID SetText(LPCWSTR Text)
	{
		SetWindowText(m_Hwnd, Text);
	}

	LPCWSTR GetText()
	{
		GetWindowText32();
		return m_StringText.GetString();
	}

public:
	BOOL Enable()
	{
		return EnableWindow(m_Hwnd, TRUE);
	}

	BOOL Disable()
	{
		return EnableWindow(m_Hwnd, FALSE);
	}

	BOOL IsEnable()
	{
		return IsWindowEnabled(m_Hwnd);
	}

	VOID SetVisibleM(BOOL Visible = TRUE)
	{
		m_bVisible = Visible;
	}

	BOOL IsVisibleM()
	{
		return (m_bVisible == TRUE);
	}

	virtual VOID SetVisible(BOOL bVisible = TRUE)
	{
		DWORD Style = GetStyle();
		if (bVisible)
			Style |= WS_VISIBLE;
		else
			Style &= ~WS_VISIBLE;

		SetStyle(Style);
	}

	BOOL IsStyleVisible()
	{
		DWORD Style = GetStyle();
		BOOL  Is = ((Style& WS_VISIBLE) == WS_VISIBLE);
		ZxDebugEx((__FUNCTION__"()::%s \n", (Is ? "Visible" :"InVisible")));
		return Is;
	}

	HWND SetFocus()
	{
		return ::SetFocus(m_Hwnd);
	}

	// С�Ĵ���
	VOID SetUserData(LPVOID UserData = NULL)
	{ 
		if (GetUserData())
			return;
		UserData = UserData ? UserData : this;
		SetWindowLongPtr(m_Hwnd, GWLP_USERDATA, (LONG_PTR)UserData);
	}

	LPVOID GetUserData()
	{
		return (LPVOID)C32GetUserData(m_Hwnd);
	}

	C32Window* GetParentC32Class()
	{
		C32Window* Class = NULL;
		if (m_Parent == NULL)
			m_Parent = ::GetParent(m_Hwnd);
		

		if (m_Parent)
			Class = (C32Window*)C32GetUserData(m_Parent);

		return Class;
	}
	
public:
	VOID GetClientLength(__inout int & Width, __inout int& Height)
	{
		Width = C32GetRectWidth(m_ClientRect);
		Height = C32GetRectHeight(m_ClientRect);
	}

	int GetWidth()
	{
		return C32GetRectWidth(m_ClientRect);
	}

	int GetHeight()
	{
		return C32GetRectHeight(m_ClientRect);
	}

	VOID GetLength(int & Width, int& Height)
	{
		Width = C32GetRectWidth(m_Rect);
		Height = C32GetRectHeight(m_Rect);
	}

	VOID SetPtr(HWND Hwnd = NULL)
	{
		m_Hwnd = Hwnd;
	}

	HWND GetPtr()
	{
		return m_Hwnd;
	}

	LONG_PTR GetControlId()
	{
		return GetWindowLongPtr(m_Hwnd, GWL_ID);
	}

	VOID SetParentPtr(HWND hwnd)
	{
		m_Parent = hwnd;
	}

	HWND SetParentPtr()
	{
		return m_Parent;
	}
	
	HWND GetParentHwnd()
	{
		return ::GetParent(m_Hwnd);
	}


	VOID SetLogicalPtr(HWND hwnd)
	{
		m_HwndLogic = hwnd;
	}

	/*
		��ȡ�˿ؼ����ڵĶ��㴰�ڵ�C32Class,
		Ϊ�˸����㴦��ͬһ�������ڶ���ؼ�ͨ��
		һ�㲻ʹ�á�
	*/

	C32Window* GetLogicalClass()
	{
		C32Window* Class = NULL;
		
		if (m_HwndLogic)
			Class = (C32Window*)C32GetUserData(m_HwndLogic);

		return Class;
	}

	HWND GetWindow()
	{
		return m_Hwnd;
	}

	VOID SetHwnd(HWND hwnd)
	{
		SetPtr(hwnd);
		GetPos();
	}

	HWND GetHwnd()
	{
		return m_Hwnd;
	}


	int GetWindowText32()
	{
		m_StringText.AssignStringW(256);
		m_StringText.m_Count = GetWindowText(m_Hwnd, m_StringText, 256);

		return m_StringText.m_Count;
	}
	
	SIZE GetClientSize()
	{
		SIZE Size={0, 0};		
		RECT Rect = {};
		if(GetClientRect(m_Hwnd, &Rect))
		{
			m_ClientCx = C32GetRectWidth(Rect);
			m_ClientCy = C32GetRectHeight(Rect);
			Size.cx = m_ClientCx;
			Size.cy = m_ClientCy;
		}
		

		return Size;
	}

	SIZE GetWindowSize()
	{
		SIZE Size={m_Cx, m_Cy};

		return Size;
	}

	BOOL DeleteFont32()
	{
		BOOL Delete = FALSE;
		if (m_hFont)
		{
			Delete = DeleteFont(m_hFont);
			m_hFont = NULL;
		}

		return Delete;
	}

	VOID SetFont(HFONT hFont)
	{
		DeleteFont32();

		HFONT hFont0 = GetFont();

		SetWindowFont(m_Hwnd, hFont, TRUE);

		m_hFont = hFont;

		HFONT hFont1 = GetFont();
		if (hFont )
		{
			assert(hFont1 == NULL || hFont == hFont1);
		}
	}

	HFONT GetFont()
	{
		return GetWindowFont(m_Hwnd);
	}

	VOID SetDelete( BOOL IsDelete = TRUE)
	{
		m_IsDelete = IsDelete;
	}
	
	/*
		���ٶԻ������Delete��new ������Ҫɾ��
	*/
	BOOL IsDelete()
	{
		return m_IsDelete;
	}

	/*
		�ı�Ի����С��ʱ��Push Button ��ť�����²���ͼ��
	*/
	BOOL  IsButton()
	{
		DWORD Style = GetStyle();
		return (Style& BS_PUSHBUTTON );
	}

	BOOL  IsContainer()
	{
		return m_IsContainer;
	}


public:
	LRESULT SendMessageParent(UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		if (m_Parent == NULL)
			m_Parent = GetParent(m_Hwnd);
		return ::SendMessage(m_Parent, Msg, wParam, lParam);
	}

	LRESULT SendMessageEx(UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		return ::SendMessage(m_Hwnd, Msg, wParam, lParam);
	}

	LRESULT PostMessageEx(UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		return ::PostMessage(m_Hwnd, Msg, wParam, lParam);
	}

public:
	VOID Init()
	{
		InitPosSize();
		m_Error = 0;
		m_Style = 0;
		m_ExStyle = 0;

		m_Hwnd = NULL;
		m_WindowId = 0; 
		m_Parent = NULL;
		m_HwndLogic = NULL;
		m_IsContainer = FALSE;
		m_CtrlType = C32CtrlTypeUnknown;
		m_Attach = FALSE;
		//Register Class
		m_iIconSmall = 0;
		m_IconSmall = NULL;
		m_iIcon = 0;
		m_Icon = NULL;
		
		m_iCursor = IDC_ARROW;
		m_iMenu = COLOR_WINDOW+1;
		m_WndProc = NULL;

		m_SubWndProc = NULL;
		m_SubWndProcOrignal = NULL;

		RtlZeroMemory(m_ClassName, 256);

		m_hbrBackground = NULL; //������ˢ.

		m_StringText.AssignStringW(256);
		m_IsClose = TRUE;
		m_IsDelete = FALSE;
		m_hFont = NULL;
		m_bVisible = TRUE;
		m_DrawFullWindowsFlag = FALSE;
		
		m_LogicParam = (LPARAM)0;
	}

public:
	VOID DebugRect()
	{
		ZxDebugEx((__FUNCTION__"():: Window: {%d, %d, %d, %d} \n", m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom));		
		ZxDebugEx((__FUNCTION__"():: Client: {%d, %d, %d, %d} \n", m_ClientRect.left, m_ClientRect.top, m_ClientRect.right, m_ClientRect.bottom));
	}

public:
	int	 m_Cy;
	int  m_Cx;

	RECT m_Rect;
	int  m_ClientCx;
	int  m_ClientCy;
	RECT m_ClientRect;

	int     m_MinCx;
	int     m_MinCy;

	HWND	 m_Hwnd;
	LONG_PTR     m_WindowId; //hMenu specifies the child-window identifier, an integer value used by a dialog box control to notify its parent about events
	HWND    m_Parent;
	HWND    m_HwndLogic;
	LPARAM  m_LogicParam;
	BOOL    m_IsContainer; //����Ͽؼ���һ����

	DWORD   m_Error;
	C32CtrlType  m_CtrlType;
	DWORD	m_Style;
	DWORD   m_ExStyle;
	BOOL    m_Attach;

	//new �����Ĳ���Ҫ��C32Window\C32Container��ɾ��
	BOOL    m_IsDelete;
	//����رհ�ťʱ���Ƿ�رմ���
	BOOL    m_IsClose;
	C32String m_StringTitle;
	C32String m_StringText;
public:
	//Register Class
	int     m_iIconSmall;
	HICON   m_IconSmall;
	int     m_iIcon;
	HICON   m_Icon;
	LPCWSTR     m_iCursor;
	int		m_iMenu;
	int     m_iBackground;
	
	WCHAR   m_ClassName[128];
	WNDPROC m_WndProc;

	WNDPROC m_SubWndProc;
	WNDPROC m_SubWndProcOrignal;

	HBRUSH  m_hbrBackground; // ��̬�ı䱳��ɫ��

public:
	HFONT   m_hFont;
public:                      //����?
	BOOL    m_bVisible;      //�ؼ��Ƿ�ɼ�����ʼ��ʱ�õ����ֶΡ�Ĭ�Ͽɼ�
	BOOL	m_DrawFullWindowsFlag;

	int		m_iAccelerator;
};

class C32Menu : public C32Window
{
public:
	static HINSTANCE hInstance;
	C32Menu()
	{
		Init();
	}

	virtual ~C32Menu()
	{
		DestroyMenu32();
	}


public:
	HMENU LoadMenu32(int ResourceId, int nPos)
	{
		m_hMenu = LoadMenu(C32Menu::hInstance, MAKEINTRESOURCE(ResourceId));
		m_Sub = GetSubMenu(m_hMenu, nPos);
		m_SubList.Add(m_Sub);
		return m_hMenu;
	}

	VOID  DestroyMenu32()
	{
		if (m_hMenu)
		{
			DestroyMenu(m_hMenu);
			m_hMenu = NULL;
		}
		if (m_Sub)
		{
			m_Sub = NULL;
		}
		for(size_t i = 0; i < m_SubList.GetCount(); i++)
		{
			DestroyMenu(m_SubList[i]);
		}

		m_SubList.RemoveAll();

	}

	BOOL Display(int ResorceId, int nPos, int xPos, int yPos, HWND Parent)
	{
	   if (m_Sub == NULL || m_hMenu == NULL)
	   {
		 assert(0);
		 return FALSE;
	   }
		
	  return TrackPopupMenuEx(m_Sub,  TPM_LEFTALIGN, xPos, yPos, Parent, NULL);
	}
	
	BOOL Display(int xPos, int yPos)
	{
		if(m_ResourceId)
			return Display(m_ResourceId, m_SubPos, xPos, yPos, m_Parent);
		else
			return Display(xPos, yPos, m_Parent);
			
	}

	BOOL Display(int xPos, int yPos, HWND Parent)
	{
		 return TrackPopupMenuEx(m_Sub,  TPM_LEFTALIGN, xPos, yPos, Parent, NULL);
	}

	int GetSubItemCount()
	{
		return GetMenuItemCount(m_Sub);
	}

	LPCWSTR GetSubItemString(int CommandId)
	{
		if(GetMenuString(m_Sub, CommandId, m_StringText, 255, MF_BYCOMMAND))
			return m_StringText;
		else
			return NULL;
	}

	LPCWSTR GetSubItemStringPos(int Pos)
	{
		if(GetMenuString(m_Sub, Pos, m_StringText, 255, MF_BYPOSITION))
			return m_StringText;
		else
			return NULL;
	}


	// ��
	BOOL SetSelectSubItem(int CommandId, BOOL bCheck = TRUE)
	{
		DWORD Status;

		Status = CheckMenuItem(m_hMenu, CommandId, bCheck?MF_CHECKED:MF_UNCHECKED);
		return (Status == MF_UNCHECKED ? TRUE : FALSE);
	}

	BOOL SelectSubItem(int CommandId)
	{
		return SetSelectSubItem(CommandId,TRUE);
	}

	BOOL ClearSubItem(int CommandId)
	{
		return SetSelectSubItem(CommandId,FALSE);
	}

	VOID SelectSubMenuItem(int CommandId)
	{
		int Count = GetSubItemCount();
		for(int i = 0; i < Count; i++)
		{
			UINT Id = GetMenuItemID(m_Sub, i);
			if (Id == CommandId)
			{
				SelectSubItem(Id);
			}else
			{
				ClearSubItem(Id);
			}

		}

		C32CtrlDebug((__FUNCTION__"():: Click %ws: \n", GetSubItemString(CommandId)));
	}

	VOID SelectSubItemPos(int nPos)
	{
		CheckMenuItem(m_Sub, nPos, MF_BYPOSITION|MF_CHECKED);
	}

	BOOL IsSubItem(int CommandId)
	{
		BOOL Is = FALSE;
		int Count = GetSubItemCount();
		for(int i = 0; i < Count; i++)
		{
			UINT Id = GetMenuItemID(m_Sub, i);
			if (Id == CommandId)
			{	
				Is = TRUE;
				break;
			}
		}
		return Is;
	}

	HMENU CreateMenu32()
	{
		HMENU  hMenu = CreateMenu();
		m_hMenu = hMenu;

		return m_hMenu;
	}

	HMENU CreatePopupMenu32()
	{
		HMENU  hPopMenu = CreatePopupMenu();
		m_Sub = hPopMenu;
		m_SubList.Add(hPopMenu);
		return m_Sub;
	}

	BOOL AppendMenu32(__in HMENU hMenu,__in UINT uFlags,__in UINT_PTR uIDNewItem, __in_opt LPCWSTR lpNewItem)
	{
		return AppendMenu(hMenu, uFlags, uIDNewItem, lpNewItem);
	}
	
	BOOL CreatePopup()
	{
		CreateMenu32();
		CreatePopupMenu32();
		
		return AppendMenu(m_hMenu, MF_STRING | MF_POPUP, (ULONG_PTR)m_hMenu,L"");
	}


public:
	VOID SetParent(HWND Parent)
	{
		m_Parent = Parent;
	}
	
	VOID SetResourceId(int MakeIntId)
	{
		m_ResourceId = MakeIntId;
	}

	int GetResourceId()
	{
		return m_ResourceId;
	}


	VOID Set(HWND Parent, int ResorceId, int SubPos = 0)
	{
		m_Parent = Parent;
		m_ResourceId = ResorceId;
		m_SubPos = SubPos;
	}
	
	VOID Init()
	{
		m_hMenu = NULL;
		m_Sub = NULL;
		m_Parent = NULL;
		m_ResourceId = 0;
		m_SubPos = 0;

		m_SubList.RemoveAll();
	}

public:
	HMENU m_hMenu;
	HMENU m_Sub;
	CAtlArray<HMENU> m_SubList;
	HWND  m_Parent;
	int   m_ResourceId;
	int   m_SubPos;
};

class C32MenuEx : public C32Window
{
public:

	C32MenuEx()
	{
		Init();
	}

	virtual ~C32MenuEx()
	{
		DestroyMenu32();
	}


public:

	VOID  DestroyMenu32()
	{
		if (m_Menu)
		{
			DestroyMenu(m_Menu);
			m_Menu = NULL;
		}
		
		for(size_t i = 0; i < m_SubList.GetCount(); i++)
		{
			DestroyMenu(m_SubList[i]);
		}

		m_SubList.RemoveAll();

	}

	BOOL Display(int xPos, int yPos, HWND Parent)
	{
		return TrackPopupMenuEx(m_Menu,  TPM_LEFTALIGN, xPos, yPos, Parent, NULL);
	}

	BOOL Display( HWND Parent, UINT Flag = TPM_LEFTALIGN)
	{
		POINT pt;
		GetCursorPos(&pt);
		int xPos = pt.x, yPos = pt.y;
		return TrackPopupMenuEx(m_Menu,  Flag, xPos, yPos, Parent, NULL);
	}
	
	int GetItemCount()
	{
		return GetMenuItemCount(m_Menu);
	}

	CString GetItemString(int CommandId)
	{
		WCHAR String[256]={};
		GetMenuString(m_Menu, CommandId, String, 255, MF_BYCOMMAND);
		return String;
	}

	LPCWSTR GetSubItemStringPos(int Pos)
	{
		if(GetMenuString(m_Menu, Pos, m_StringText, 255, MF_BYPOSITION))
			return m_StringText;
		else
			return NULL;
	}


	// ��
	BOOL SetSelectItem(int CommandId, BOOL bCheck = TRUE)
	{
		DWORD Status;

		Status = CheckMenuItem(m_Menu, CommandId, bCheck?MF_CHECKED:MF_UNCHECKED);
		return (Status == MF_UNCHECKED ? TRUE : FALSE);
	}

	VOID SelectMenuItem(int CommandId)
	{
		int Count = GetItemCount();
		for(int i = 0; i < Count; i++)
		{
			UINT Id = GetMenuItemID(m_Menu, i);
			if (Id == CommandId)
			{
				SetSelectItem(Id, TRUE);
			}else
			{
				SetSelectItem(Id, FALSE);
			}

		}

		C32CtrlDebug((__FUNCTION__"():: Click %ws: \n", GetItemString(CommandId)));
	}

	VOID SelectItemPos(int nPos)
	{
		CheckMenuItem(m_Menu, nPos, MF_BYPOSITION|MF_CHECKED);
	}

	BOOL IsSubItem(int CommandId)
	{
		BOOL Is = FALSE;
		int Count = GetItemCount();
		for(int i = 0; i < Count; i++)
		{
			UINT Id = GetMenuItemID(m_Menu, i);
			if (Id == CommandId)
			{	
				Is = TRUE;
				break;
			}
		}
		return Is;
	}

	HMENU CreatePopup()
	{
		m_Menu = CreatePopupMenu();

		return m_Menu;
	}

	BOOL AppendMenu32(__in UINT uFlags,__in UINT_PTR uIDNewItem, __in_opt LPCWSTR lpNewItem)
	{
		return AppendMenu(m_Menu, uFlags, uIDNewItem, lpNewItem);
	}

	BOOL AppendItemString(__in UINT_PTR uIDNewItem, __in_opt LPCWSTR lpNewItem)
	{
		return AppendMenu(m_Menu, MF_STRING, uIDNewItem, lpNewItem);
	}

public:
	VOID SetParent(HWND Parent)
	{
		m_Parent = Parent;
	}

	VOID Init()
	{
		m_Menu = NULL;
		m_SubList.RemoveAll();
	}

public:
	HMENU m_Menu;
	CAtlArray<HMENU> m_SubList;
};

class C32ToolBar : public C32Window
{
public:
	C32ToolBar()
	{
		Init();

	}
	
	~C32ToolBar()
	{

	}
public:
	virtual HWND Create(DWORD ExStyle,DWORD Style, int xPos, int yPos, int Cx, int Cy, HWND hwnd)
	{
		m_WindowId = ++C32ControlId;
		m_Hwnd = CreateWindowEx(ExStyle,TOOLBARCLASSNAME, L"C32ToolBar", Style, xPos,yPos, Cx, Cy, hwnd, (HMENU)m_WindowId, C32Hinstance,this);
		Attach(m_Hwnd);
		ZxDebugEx((__FUNCTION__"()::m_Hwnd : %p Id:%d This : %p Parent:%p Code: %d\n",m_Hwnd, m_WindowId,this, hwnd, GetLastError()));
		return m_Hwnd;
	}

public:
 BOOL EnableButton(int nID, BOOL bEnable)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_ENABLEBUTTON, nID, MAKELPARAM(bEnable, 0)); 
  }
 BOOL CheckButton(int nID, BOOL bCheck)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_CHECKBUTTON, nID, MAKELPARAM(bCheck, 0)); 
  }
 BOOL PressButton(int nID, BOOL bPress)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_PRESSBUTTON, nID, MAKELPARAM(bPress, 0)); 
  }
 BOOL HideButton(int nID, BOOL bHide)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_HIDEBUTTON, nID, MAKELPARAM(bHide, 0)); 
  }
 BOOL Indeterminate(int nID, BOOL bIndeterminate)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_INDETERMINATE, nID, MAKELPARAM(bIndeterminate, 0)); 
  }
 BOOL IsButtonEnabled(int nID) const
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_ISBUTTONENABLED, nID, 0); 
  }
 BOOL IsButtonChecked(int nID) const
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_ISBUTTONCHECKED, nID, 0); 
  }
 BOOL IsButtonPressed(int nID) const
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_ISBUTTONPRESSED, nID, 0); 
  }
 BOOL IsButtonHidden(int nID) const
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_ISBUTTONHIDDEN, nID, 0); 
  }
 BOOL IsButtonIndeterminate(int nID) const
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_ISBUTTONINDETERMINATE, nID, 0); 
  }
 BOOL SetState(int nID, UINT nState)
 
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_SETSTATE, nID, MAKELPARAM(nState, 0)); 
  }
 int GetState(int nID) const
	{
   return (int) ::SendMessage(m_Hwnd, TB_GETSTATE, nID, 0L); 
  }
 BOOL AddButtons(int nNumButtons, LPTBBUTTON lpButtons)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_ADDBUTTONS, nNumButtons, (LPARAM)lpButtons); 
  }
 BOOL InsertButton(int nIndex, LPTBBUTTON lpButton)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_INSERTBUTTON, nIndex, (LPARAM)lpButton); 
  }
 BOOL DeleteButton(int nIndex)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_DELETEBUTTON, nIndex, 0); 
  }
 BOOL GetButton(int nIndex, LPTBBUTTON lpButton) const
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_GETBUTTON, nIndex, (LPARAM)lpButton); 
  }
 int GetButtonCount() const
	{
   return (int) ::SendMessage(m_Hwnd, TB_BUTTONCOUNT, 0, 0L); 
  }
 UINT CommandToIndex(UINT nID) const
	{
   return (UINT) ::SendMessage(m_Hwnd, TB_COMMANDTOINDEX, nID, 0L); 
  }
 void Customize()
	{
   ::SendMessage(m_Hwnd, TB_CUSTOMIZE, 0, 0L); 
  }
// lpszStrings are separated by zeroes, last one is marked by two zeroes
 int AddStrings(LPCTSTR lpszStrings)
	{
   return (int) ::SendMessage(m_Hwnd, TB_ADDSTRING, 0, (LPARAM)lpszStrings); 
  }
 BOOL GetItemRect(int nIndex, LPRECT lpRect) const
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_GETITEMRECT, nIndex, (LPARAM)lpRect); 
  }
 void SetButtonStructSize(int nSize)
	{
   ::SendMessage(m_Hwnd, TB_BUTTONSTRUCTSIZE, nSize, 0L); 
  }
 BOOL SetButtonSize(SIZE size)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_SETBUTTONSIZE, 0, MAKELPARAM(size.cx, size.cy)); 
  }
 BOOL SetBitmapSize(SIZE size)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_SETBITMAPSIZE, 0, MAKELPARAM(size.cx, size.cy)); 
  }
 void AutoSize()
	{
   ::SendMessage(m_Hwnd, TB_AUTOSIZE, 0, 0L); 
  }
 HWND GetToolTips() const
	{
   return (HWND) ::SendMessage(m_Hwnd, TB_GETTOOLTIPS, 0, 0L); 
  }
 void SetToolTips(HWND pTip)
	{
   ::SendMessage(m_Hwnd, TB_SETTOOLTIPS, (WPARAM)pTip, 0L); 
  }
 void SetOwner(HWND pWnd)
	{
   ::SendMessage(m_Hwnd, TB_SETPARENT, (WPARAM)pWnd, 0L); 
  }
 void SetRows(int nRows, BOOL bLarger, LPRECT lpRect)
	{
   ::SendMessage(m_Hwnd, TB_SETROWS, MAKEWPARAM(nRows, bLarger), (LPARAM)lpRect); 
  }
 int GetRows() const
	{
   return (int) ::SendMessage(m_Hwnd, TB_GETROWS, 0, 0L); 
  }
 BOOL SetCmdID(int nIndex, UINT nID)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_SETCMDID, nIndex, nID); 
  }
 UINT GetBitmapFlags() const
	{
   return (UINT) ::SendMessage(m_Hwnd, TB_GETBITMAPFLAGS, 0, 0L); 
  }
 int GetBitmap(int nID) const
	{
   return (int) ::SendMessage(m_Hwnd, TB_GETBITMAP, nID, 0L); 
  }
 BOOL ReplaceBitmap(_In_ LPTBREPLACEBITMAP pReplaceBitmap)
	{
   return (int) ::SendMessage(m_Hwnd, TB_REPLACEBITMAP, 0, (LPARAM)pReplaceBitmap); 
  }
 BOOL ChangeBitmap(int idButton, int iBitmap)
	{
   return (BOOL) ::SendMessage(m_Hwnd, TB_CHANGEBITMAP, idButton, (LPARAM)MAKELPARAM(iBitmap, 0)); 
  }
 int HitTest(LPPOINT ppt) const
	{
   return (int) ::SendMessage(m_Hwnd, TB_HITTEST, 0, (LPARAM)ppt); 
  }
 DWORD GetExtendedStyle() const
	{
   return (DWORD) ::SendMessage(m_Hwnd, TB_GETEXTENDEDSTYLE, 0, 0L); 
  }
 DWORD SetExtendedStyle(DWORD dwExStyle)
	{
   return (DWORD) ::SendMessage(m_Hwnd, TB_SETEXTENDEDSTYLE, 0, dwExStyle); 
  }
 void GetPadding(int& nHorzPadding, int& nVertPadding) const
	{
   DWORD dwPadding = (DWORD)::SendMessage(m_Hwnd, TB_GETPADDING, 0, 0L); nHorzPadding = (int)LOWORD(dwPadding); nVertPadding = (int)HIWORD(dwPadding); 
  }
 DWORD SetPadding(int nHorzPadding, int nVertPadding)
	{
   return (DWORD) ::SendMessage(m_Hwnd, TB_SETPADDING, 0, (LPARAM)MAKELPARAM(nHorzPadding, nVertPadding)); 
  }
 COLORREF GetInsertMarkColor() const
	{
   return (COLORREF) ::SendMessage(m_Hwnd, TB_GETINSERTMARKCOLOR, 0, 0); 
  }
 COLORREF SetInsertMarkColor(COLORREF clrNew)
	{
   return (COLORREF) ::SendMessage(m_Hwnd, TB_SETINSERTMARKCOLOR, 0, (LPARAM) clrNew); 
  }
 BOOL GetColorScheme(COLORSCHEME* lpcs) const
	{
   lpcs->dwSize = ULONG(sizeof(COLORSCHEME)); return (BOOL)(::SendMessage(m_Hwnd, TB_GETCOLORSCHEME, 0, (LPARAM)lpcs) != 0); 
  }
 void SetColorScheme(const COLORSCHEME* lpcs)
	{
   ((COLORSCHEME*)lpcs)->dwSize = sizeof(COLORSCHEME); ::SendMessage(m_Hwnd, TB_SETCOLORSCHEME, 0, (LPARAM)lpcs); 
  }


 DWORD GetButtonSize() const
 { return (DWORD) ::SendMessage(m_Hwnd, TB_GETBUTTONSIZE, 0, 0L); }
 HIMAGELIST GetDisabledImageList() const
 { return (HIMAGELIST) ::SendMessage(m_Hwnd, TB_GETDISABLEDIMAGELIST, 0, 0); }
 HIMAGELIST GetHotImageList() const
 { return (HIMAGELIST) ::SendMessage(m_Hwnd, TB_GETHOTIMAGELIST, 0, 0); }
 HIMAGELIST GetImageList() const
 { return (HIMAGELIST) ::SendMessage(m_Hwnd, TB_GETIMAGELIST, 0, 0); }
 DWORD GetStyle() const
 { return (DWORD) ::SendMessage(m_Hwnd, TB_GETSTYLE, 0, 0L); }
 INT GetMaxTextRows() const
 { return (INT) ::SendMessage(m_Hwnd, TB_GETTEXTROWS, 0, 0L); }
 BOOL GetRect(int nID, LPRECT lpRect) const
 { return (BOOL) ::SendMessage(m_Hwnd, TB_GETRECT, nID, (LPARAM)lpRect); }
 BOOL IsButtonHighlighted(int nID) const
 { return (BOOL) ::SendMessage(m_Hwnd, TB_ISBUTTONHIGHLIGHTED, nID, 0); }
 void LoadImages(int iBitmapID, HINSTANCE hinst)
 { ::SendMessage(m_Hwnd, TB_LOADIMAGES, iBitmapID, (LPARAM)hinst); }
 BOOL SetButtonWidth(int cxMin, int cxMax)
 { return (BOOL) ::SendMessage(m_Hwnd, TB_SETBUTTONWIDTH, 0, MAKELPARAM(cxMin, cxMax)); }
 HIMAGELIST SetDisabledImageList(HIMAGELIST pImageList)
 { return (HIMAGELIST) ::SendMessage(m_Hwnd, TB_SETDISABLEDIMAGELIST, 0, (LPARAM)pImageList); }
 HIMAGELIST SetHotImageList(HIMAGELIST pImageList)
 { return (HIMAGELIST) ::SendMessage(m_Hwnd, TB_SETHOTIMAGELIST, 0, (LPARAM)pImageList); }
 HIMAGELIST SetImageList(HIMAGELIST pImageList)
 { return (HIMAGELIST) ::SendMessage(m_Hwnd, TB_SETIMAGELIST, 0, (LPARAM)pImageList); }
 BOOL SetIndent(int iIndent)
 { return (BOOL) ::SendMessage(m_Hwnd, TB_SETINDENT, iIndent, 0L); }
 BOOL SetMaxTextRows(int iMaxRows)
 { return (BOOL) ::SendMessage(m_Hwnd, TB_SETMAXTEXTROWS, iMaxRows, 0L); }
 void SetStyle(DWORD dwStyle)
 { ::SendMessage(m_Hwnd, TB_SETSTYLE, 0, dwStyle); }
 int GetButtonInfo(int nID, TBBUTTONINFO* ptbbi) const
 { return (int) ::SendMessage(m_Hwnd, TB_GETBUTTONINFO, nID, (LPARAM)ptbbi); }
 BOOL SetButtonInfo(int nID, TBBUTTONINFO* ptbbi)
 { return (BOOL) ::SendMessage(m_Hwnd, TB_SETBUTTONINFO, nID, (LPARAM)ptbbi); }
 DWORD SetDrawTextFlags(DWORD dwMask, DWORD dwDTFlags)
 { return (DWORD) ::SendMessage(m_Hwnd, TB_SETDRAWTEXTFLAGS, dwMask, dwDTFlags); }
 BOOL GetAnchorHighlight() const
 { return (BOOL) ::SendMessage(m_Hwnd, TB_GETANCHORHIGHLIGHT, 0, 0); }
 BOOL SetAnchorHighlight(BOOL fAnchor)
 { return (BOOL) ::SendMessage(m_Hwnd, TB_SETANCHORHIGHLIGHT, fAnchor, 0); }
 int GetHotItem() const
 { return (int) ::SendMessage(m_Hwnd, TB_GETHOTITEM, 0, 0); }
 int SetHotItem(int nHot)
 { return (int) ::SendMessage(m_Hwnd, TB_SETHOTITEM, nHot, 0); }
 void GetInsertMark(TBINSERTMARK* ptbim) const
 { ::SendMessage(m_Hwnd, TB_GETINSERTMARK, 0, (LPARAM)ptbim); }
 void SetInsertMark(TBINSERTMARK* ptbim)
 { ::SendMessage(m_Hwnd, TB_SETINSERTMARK, 0, (LPARAM)ptbim); }
 BOOL GetMaxSize(LPSIZE pSize) const
 { return (BOOL) ::SendMessage(m_Hwnd, TB_GETMAXSIZE, 0, (LPARAM)pSize); }
 BOOL InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim) const
 { return (BOOL) ::SendMessage(m_Hwnd, TB_INSERTMARKHITTEST, (WPARAM)ppt, (LPARAM)ptbim); }
 BOOL MapAccelerator(TCHAR chAccel, UINT* pIDBtn)
 { return (BOOL) ::SendMessage(m_Hwnd, TB_MAPACCELERATOR, (WPARAM)chAccel, (LPARAM)pIDBtn); }
 BOOL MarkButton(int nID, BOOL bHighlight)
 { return (BOOL) ::SendMessage(m_Hwnd, TB_MARKBUTTON, nID, MAKELPARAM(bHighlight, 0)); }
 BOOL MoveButton(UINT nOldPos, UINT nNewPos)
 { return (BOOL) ::SendMessage(m_Hwnd, TB_MOVEBUTTON, nOldPos, nNewPos); }

#if _WIN32_IE >= 0x0500
 int GetString(_In_ int nString, _Out_z_cap_post_count_(cchMaxLen, return + 1) LPTSTR lpstrString, _In_ size_t cchMaxLen) const
 { return (int) ::SendMessage(m_Hwnd, TB_GETSTRING, MAKEWPARAM(cchMaxLen, nString), (LPARAM)lpstrString); lpstrString[cchMaxLen]=_T('\0'); }
#endif


 VOID Init()
 {
	 m_iImageID = 0;
 }

public:
	int           m_iImageID;		  
	C32ImageList  m_ImageList;
};


class C32Button : public C32Window, public C32ButtonEventCallback
{

public:
	static LRESULT C32SubClassProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam,
						UINT_PTR uIdSubclass,DWORD_PTR dwRefData);
	

public:
	C32Button()
	{
		Init();
	};

	C32Button(HWND Hwnd)
	{
		Init();
		Attach(Hwnd);
	};

	~C32Button(){
		
		
	};

	HWND Create(DWORD Style, int xPos, int yPos, int Cx, int Cy, HWND hwnd)
	{
		m_Hwnd = CreateWindow(WC_BUTTON, L"C32Button", Style, xPos, yPos, Cx, Cy, hwnd, NULL, C32Hinstance, (LPVOID)this);
		if (m_Hwnd)
			Attach(m_Hwnd);

		ZxDebugEx((__FUNCTION__"():: m_Hwnd: %p This: %p \n", m_Hwnd, this));
		
		return m_Hwnd;
	}
	  
public:
	int SetText(LPCWSTR Text)
	{
		return (int)Button_SetText(m_Hwnd, Text);
	}

	LPWSTR GetText()
	{
		m_StringText.AssignStringW(256);

		m_StringText.m_Count = Button_GetText(m_Hwnd, m_StringText, 256);
		return m_StringText;
	}

	HICON SetIcon(HICON hIcon)
	{
		return (HICON)SendMessage(m_Hwnd, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);
	}

	HICON GetIcon()
	{
		return (HICON)SendMessage(m_Hwnd, BM_GETIMAGE, (WPARAM)IMAGE_ICON,(LPARAM)0);
	}
	
	HICON SetIcon(int RresourceId)
	{
		HICON hIcon = NULL;

		if(m_Icon.Load(RresourceId) == TRUE)
			hIcon = SetIcon(RresourceId);
		
		return hIcon;
	}
	
	DWORD GetCheck()
	{
		BOOL State = Button_GetCheck(m_Hwnd);

		return State;
	}

	BOOL IsCheck()
	{
		DWORD State = GetCheck();

		return (State & BST_CHECKED);
	}

	VOID SetCheck(BOOL bCheck = TRUE)
	{
		int State = (bCheck ? BST_CHECKED : BST_UNCHECKED);
		Button_SetCheck(m_Hwnd, State);
	}

public:
	VOID Disable()
	{
		Button_Enable(m_Hwnd, FALSE);
	}

	VOID Enable()
	{
		Button_Enable(m_Hwnd, TRUE);
	}

	virtual BOOL SetSubClass(DWORD_PTR dwRefData = 0)
	{
		BOOL Ret;
		Ret = SetWindowSubclass(m_Hwnd, C32Button::C32SubClassProc, (ULONG_PTR)this, dwRefData);
		ASSERT(Ret == TRUE);

		return Ret;
	}

	virtual BOOL RemoveSubClass()
	{
		BOOL Ret;

		Ret = RemoveWindowSubclass(m_Hwnd, C32Button::C32SubClassProc, (ULONG_PTR)this);

		return Ret;
	}

public: // Event
	
	//If an application processes this message, it should return zero.
	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		BOOL Handle = FALSE;
		C32SetHandleLReslut(FALSE, 0);
		DWORD NotifyCode;
		NotifyCode = HIWORD(wParam);
		ZxDebugEx((__FUNCTION__"():: Text: %ws \n", this->GetText()));
		switch(NotifyCode)
		{
			case BN_CLICKED:
				Handle  = OnCommandClick(wParam, lParam);
				break;
			case BN_DOUBLECLICKED:
				Handle  = OnCommandDClick(wParam, lParam);
				break;
			case BN_SETFOCUS:
				break;

		}

		if (Handle == TRUE)
			lResult = 0;

		return Handle;
	}

	virtual BOOL OnCommandClick(WPARAM wParam, LPARAM lParam)
	{
		BOOL Handle = FALSE;
		if (m_OnClick)
			Handle = m_OnClick(C32CommandCtrlId(wParam), this);
		
				
		return Handle;
	}

	virtual BOOL OnCommandDClick(WPARAM wParam, LPARAM lParam)
	{
		BOOL Handle = FALSE;
		if (m_OnDClick)
			Handle = m_OnDClick(C32CommandCtrlId(wParam), this);	
		return Handle;
	}
	
	virtual BOOL CALLBACK OnCtlColorBtn(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HDC  Hdc = (HDC)wParam;
		HWND Hwnd = (HWND)lParam;
		lResult = 0;
		ZxDebug((__FUNCTION__"():: %ws \n", GetText()));
		m_ColorMask = C32UICOLOR_ALL;
		if (C32ThemeStyle::IsThemeStyleDark())
		{
			Handle = TRUE;
			//�������ֱ���ɫ,�����ÿؼ�����ɫ����Ч
			if(IsUseFontBkGnd())
				SetBkColor(Hdc, C32ThemeStyle::m_ColorFontBk);

			//����������ɫ
			if (IsUseFont())
				SetTextColor(Hdc, C32ThemeStyle::m_ColorFont);

			SetBkMode(Hdc, OPAQUE);
			//���û��ƾ�̬�ؼ������Ļ��ʵľ������Ϊ OPAQUE :���������ֱ���ɫ������Ϊ��ɫ.
			if (IsUseBkGnd())
				lResult = (LRESULT)C32ThemeStyle::m_HbrBkGnd;
		}


		return Handle;
	}

	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		
		lResult = 0;
		LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lParam;
		ZxDebugEx((__FUNCTION__"():: %ws itemState:0x%08x\n", GetText(), pdis->itemState));
		if (C32ThemeStyle::IsThemeStyleDark())
		{
			ASSERT(pdis->CtlType == ODT_BUTTON);
			HBRUSH  Brush = CreateSolidBrush(C32ThemeStyle::m_ColorFontBk);
			if (pdis->CtlType == ODT_BUTTON)
			{
					HDC hdc = pdis->hDC; 
					RECT rect = pdis->rcItem;
					
					// ���ݰ�ť״̬���Ʊ���
					if (pdis->itemState & ODS_FOCUS)
					{
						FillRect(hdc, &rect, Brush);
					}
					else
					{
						// ��ť����״̬
						FillRect(hdc, &rect,Brush);
					}

					// ���ư�ť�ı�
					CString text = GetText();
					SetTextColor(hdc, C32ThemeStyle::m_ColorFont); // ��ɫ����
					SetBkMode(hdc, OPAQUE);          // ���ֱ���͸��
					DrawText(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				DeleteObject(Brush);
		}
		
		return Handle;
	}

public:
	VOID Init()
	{
		m_CtrlType = C32CtrlTypeButton;
		
	}

	C32Icon  m_Icon;
};

class C32Radio : public C32Button
{
public:
	C32Radio()
	{

	}
	virtual ~C32Radio()
	{


	}

};

class C32CheckBox : public C32Button
{
public:
	C32CheckBox()
	{

	}
	~C32CheckBox()
	{

	}

public:
	



};


class C32Edit : public C32Window
{
public:
	C32Edit()
	{
		Init();
	}
	~C32Edit()
	{

	}

	VOID Init()
	{
		m_CtrlType = C32CtrlTypeEdit;
		
		m_Length = 0;
	}
	//��ǰ״̬ 0:Disable !0 : Enable
	BOOL Enable()
	{
		return Edit_Enable(m_Hwnd, TRUE);
	}
	
	BOOL Disable()
	{
		return Edit_Enable(m_Hwnd, FALSE);
	}

	VOID SetRect(LPRECT Rect)
	{
		Edit_SetRect(m_Hwnd, Rect);
	}

	VOID SetRect(int X, int Y, int Cx, int Cy)
	{
		RECT Rect = {};
		Rect.left = X;
		Rect.top = Y;
		Rect.right = X + Cx;
		Rect.bottom = Y + Cy;
		Edit_SetRect(m_Hwnd, &Rect);
	}

	LPWSTR GetText()
	{
		m_String.FreeBuffer();
		LPWSTR Text = NULL;
		m_Length = Edit_GetTextLength(m_Hwnd);
		if (m_Length > 0)
		{
			m_String.Assign(m_Length*2);
			if (m_String.GetBuffer())
			{
				int  iCount = Edit_GetText(m_Hwnd, (LPWSTR)m_String, m_String.GetLength());
				if (iCount == 0)
				{
					m_String.FreeBuffer();
				}
			}
		}
		return m_String;
	}

	BOOL  SetText(LPCWSTR Text)
	{
		 return Edit_SetText(m_Hwnd, Text);
	}

	VOID  ResetText()
	{
		SetText(L"");
	}

	BOOL SetCueBanner(_In_z_ LPCWSTR lpszText, _In_ BOOL fDrawWhenFocused = FALSE)
	{
		return Edit_SetCueBannerTextFocused(m_Hwnd, lpszText, fDrawWhenFocused); // EM_SETCUEBANNER
	}

	BOOL CanUndo() const
	{ 
		return (BOOL)::SendMessage(m_Hwnd, EM_CANUNDO, 0, 0); 
	}
	
	int GetLineCount() const
	{  
		return (int)::SendMessage(m_Hwnd, EM_GETLINECOUNT, 0, 0);
	}

	BOOL GetModify() const
	{  
		return (BOOL)::SendMessage(m_Hwnd, EM_GETMODIFY, 0, 0); 
	}
	
	void SetModify(BOOL bModified)
	{  
		::SendMessage(m_Hwnd, EM_SETMODIFY, bModified, 0); 
	}
	
	void GetRect(LPRECT lpRect) const
	{  
		::SendMessage(m_Hwnd, EM_GETRECT, 0, (LPARAM)lpRect); 
	}
	
	void GetSel(int& nStartChar, int& nEndChar) const
	{  
		::SendMessage(m_Hwnd, EM_GETSEL, (WPARAM)&nStartChar,(LPARAM)&nEndChar);
	}
	
	DWORD GetSel() const
	{  
		return DWORD(::SendMessage(m_Hwnd, EM_GETSEL, 0, 0)); 
	}

	HLOCAL GetHandle() const
	{  
		return (HLOCAL)::SendMessage(m_Hwnd, EM_GETHANDLE, 0, 0); 
	}

	void SetHandle(HLOCAL hBuffer)
	{  
		::SendMessage(m_Hwnd, EM_SETHANDLE, (WPARAM)hBuffer, 0); 
	}
	
	int GetLine(_In_ int nIndex, _Out_ LPTSTR lpszBuffer) const
	{ 
		return (int)::SendMessage(m_Hwnd, EM_GETLINE, nIndex, (LPARAM)lpszBuffer); 
	}

	int GetLine(_In_ int nIndex, _Out_cap_post_count_(nMaxLength, return) LPTSTR lpszBuffer, _In_ int nMaxLength) const
	{

		*(LPWORD)lpszBuffer = (WORD)nMaxLength;
		return (int)::SendMessage(m_Hwnd, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}
	
	void EmptyUndoBuffer()
	{  
		::SendMessage(m_Hwnd, EM_EMPTYUNDOBUFFER, 0, 0); 
	}
	
	BOOL FmtLines(BOOL bAddEOL)
	{  
		return (BOOL)::SendMessage(m_Hwnd, EM_FMTLINES, bAddEOL, 0); 
	}
	
	void LimitText(int nChars)
	{  
		::SendMessage(m_Hwnd, EM_LIMITTEXT, nChars, 0); 
	}
	
	int LineFromChar(int nIndex) const
	{  
		return (int)::SendMessage(m_Hwnd, EM_LINEFROMCHAR, nIndex, 0); 
	}
	
	int LineIndex(int nLine) const
	{  
		return (int)::SendMessage(m_Hwnd, EM_LINEINDEX, nLine, 0); 
	}
	
	int LineLength(int nLine) const
	{  
		return (int)::SendMessage(m_Hwnd, EM_LINELENGTH, nLine, 0); 
	}
	
	void LineScroll(int nLines, int nChars)
	{  
		::SendMessage(m_Hwnd, EM_LINESCROLL, nChars, nLines); 
	}
	
	void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo)
	{  
		::SendMessage(m_Hwnd, EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)lpszNewText); 
	}
	
	void SetPasswordChar(TCHAR ch)
	{  
		::SendMessage(m_Hwnd, EM_SETPASSWORDCHAR, ch, 0); 
	}

	void SetRect(LPCRECT lpRect)
	{  
		::SendMessage(m_Hwnd, EM_SETRECT, 0, (LPARAM)lpRect); 
	}

	void SetRectNP(LPCRECT lpRect)
	{  
		::SendMessage(m_Hwnd, EM_SETRECTNP, 0, (LPARAM)lpRect); 
	}
	
	void SetSel(DWORD dwSelection, BOOL bNoScroll)
	{  
		::SendMessage(m_Hwnd, EM_SETSEL, LOWORD(dwSelection), HIWORD(dwSelection));
		if (!bNoScroll)
			::SendMessage(m_Hwnd, EM_SCROLLCARET, 0, 0); 
	}
	
	void SetSel(int nStartChar, int nEndChar, BOOL bNoScroll)
	{  
		::SendMessage(m_Hwnd, EM_SETSEL, nStartChar, nEndChar);
		if (!bNoScroll)
			::SendMessage(m_Hwnd, EM_SCROLLCARET, 0, 0); 
	}

	BOOL SetTabStops(int nTabStops, LPINT rgTabStops)
	{  
		return (BOOL)::SendMessage(m_Hwnd, EM_SETTABSTOPS, nTabStops,(LPARAM)rgTabStops); 
	}
	
	void SetTabStops()
	{  
		::SendMessage(m_Hwnd, EM_SETTABSTOPS, 0, 0); 
	}
	
	BOOL SetTabStops(const int& cxEachStop)
	{  
		return (BOOL)::SendMessage(m_Hwnd, EM_SETTABSTOPS,1, (LPARAM)(LPINT)&cxEachStop); 
	}
	
	BOOL Undo()
	{  
		return (BOOL)::SendMessage(m_Hwnd, EM_UNDO, 0, 0); 
	}
	
	void Clear()
	{  
		::SendMessage(m_Hwnd, WM_CLEAR, 0, 0); 
	}
	
	void Copy()
	{  
		::SendMessage(m_Hwnd, WM_COPY, 0, 0); 
	}
	void Cut()
	{  
		::SendMessage(m_Hwnd, WM_CUT, 0, 0); 
	}
	void Paste()
	{  
		::SendMessage(m_Hwnd, WM_PASTE, 0, 0); 
	}

	BOOL SetReadOnly(BOOL bReadOnly )
	{  
		return (BOOL)::SendMessage(m_Hwnd, EM_SETREADONLY, bReadOnly, 0L);
	 }

	int GetFirstVisibleLine() const
	{  
		return (int)::SendMessage(m_Hwnd, EM_GETFIRSTVISIBLELINE, 0, 0L); 
	}
	
	WCHAR GetPasswordChar() const
	{  
		return (WCHAR)::SendMessage(m_Hwnd, EM_GETPASSWORDCHAR, 0, 0L); 
	}
	void SetMargins(UINT nLeft, UINT nRight)
	{  
		::SendMessage(m_Hwnd, EM_SETMARGINS, EC_LEFTMARGIN|EC_RIGHTMARGIN, MAKELONG(nLeft, nRight)); 
	}
	
	DWORD GetMargins() const
	{  
		return (DWORD)::SendMessage(m_Hwnd, EM_GETMARGINS, 0, 0); 
	}
	void SetLimitText(UINT nMax)
	{  
		::SendMessage(m_Hwnd, EM_SETLIMITTEXT, nMax, 0); 
	}
	UINT GetLimitText() const
	{  
		return (UINT)::SendMessage(m_Hwnd, EM_GETLIMITTEXT, 0, 0); 
	}
	
	DWORD PosFromChar(UINT nChar) const
	{  
		return  (DWORD)::SendMessage(m_Hwnd, EM_POSFROMCHAR, nChar, 0); 
	}
	int CharFromPos (int xPos, int yPos) const
	{  
		return (int)::SendMessage(m_Hwnd, EM_CHARFROMPOS, 0, MAKELPARAM(xPos, yPos)); 
	}


public:
	virtual BOOL CALLBACK OnCtlColorEdit(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HDC  Hdc = (HDC)wParam;
		HWND Hwnd = (HWND)lParam;
		lResult = 0;
	
		ZxDebug((__FUNCTION__"():: %ws \n", GetText()));

		if (C32ThemeStyle::IsThemeStyleDark() /*&& IsUseColor()*/)
		{
			m_ColorMask = C32UICOLOR_ALL;
			Handle = TRUE;
			//�������ֱ���ɫ,�����ÿؼ�����ɫ����Ч
			if(IsUseFontBkGnd())
				SetBkColor(Hdc, C32ThemeStyle::m_ColorFontBk);

			//����������ɫ
			if (IsUseFont())
				SetTextColor(Hdc, C32ThemeStyle::m_ColorFont);

			SetBkMode(Hdc, m_ColorMode);
			//���û��ƾ�̬�ؼ������Ļ��ʵľ������Ϊ OPAQUE :���������ֱ���ɫ������Ϊ��ɫ.
			if (IsUseBkGnd())
				lResult = (LRESULT)C32ThemeStyle::m_HbrBkGnd;
		}


		return Handle;
	}

public:
	int  m_Length;
	C32String  m_String;
};

class C32Static: public C32Window , public C32StaticEventCallback
{
public:
	C32Static()
	{

	}
	
	~C32Static()
	{


	}

public:
	
	BOOL LoadIcon(int ResourceId)
	{
		m_hIcon.Load(ResourceId);
		SetIcon(m_hIcon);
	}

	BOOL SetIcon(HICON hIcon)
	{
		HICON hIco;
		hIco = Static_SetIcon(m_Hwnd, hIcon);

		return C32IsNonNull(hIco);
	}

	HICON GetIcon()
	{
		return Static_GetIcon(m_Hwnd, 0);
	}

	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_UNREFERENCED_PARAMETER();
		BOOL Handle = FALSE;
		 
		switch(C32CommandCtrlNotifiyCode(wParam))
		{
			case STN_CLICKED:
				Handle = OnClick(wParam, lParam, lResult);
				break;
			case STN_DBLCLK:
				Handle = OnDClick(wParam, lParam, lResult);
				break;

		}
		if (Handle == TRUE)
			lResult = 0;

		return Handle;
	}

	virtual BOOL OnClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_UNREFERENCED_PARAMETER();		
		BOOL Handle = FALSE;
		if (m_OnClick)
			Handle = m_OnClick(C32CommandCtrlId(wParam), this);	
		return Handle;
	}

	virtual BOOL OnDClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_UNREFERENCED_PARAMETER();

		BOOL Handle = FALSE;
		if (m_OnDClick)
			Handle = m_OnDClick(C32CommandCtrlId(wParam), this);	
		return Handle;
	}

	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		if (m_OnDrawItem)
		{
			Handle = m_OnDrawItem(lpdis, lResult, (C32Window*)this);
		}
		if (Handle == TRUE)
			lResult = 0;

		return Handle;
	}

	virtual BOOL CALLBACK OnCtlColorStatic(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HDC  Hdc = (HDC)wParam;
		HWND Hwnd = (HWND)lParam;
		lResult = 0;
		DWORD Style = GetStyle();
		ZxDebug((__FUNCTION__"():: %ws Style: 0x%08x\n", GetText(), Style));
		
		if (C32ThemeStyle::IsThemeStyleDark() /*&& IsUseColor()*/)
		{
			m_ColorMask = C32UICOLOR_ALL;
			Handle = TRUE;
			//�������ֱ���ɫ,�����ÿؼ�����ɫ����Ч
			if(IsUseFontBkGnd())
				SetBkColor(Hdc, C32ThemeStyle::m_ColorFontBk);
			
			//����������ɫ
			if (IsUseFont())
				SetTextColor(Hdc, C32ThemeStyle::m_ColorFont);

			SetBkMode(Hdc, m_ColorMode);
			//���û��ƾ�̬�ؼ������Ļ��ʵľ������Ϊ OPAQUE :���������ֱ���ɫ������Ϊ��ɫ.
			if (IsUseBkGnd())
				lResult = (LRESULT)C32ThemeStyle::m_HbrBkGnd;
		}


		return Handle;
	}
	
	VOID Init()
	{
		m_CtrlType = C32CtrlTypeStatic;
	}

public:
	C32Icon m_hIcon;
};


class C32GroupBox : public C32Static
{
public:
	static LRESULT C32SubClassProcBox(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam,
		UINT_PTR uIdSubclass,DWORD_PTR dwRefData);

public:
	C32GroupBox()
	{
		m_CtrlType = C32CtrlTypeBox;
		
	}
	
	virtual ~C32GroupBox()
	{

	}

public:
	BOOL SetSubClass(DWORD_PTR dwRefData = 0)
	{
		BOOL Ret;
		Ret = SetWindowSubclass(m_Hwnd, C32GroupBox::C32SubClassProcBox, (ULONG_PTR)this, dwRefData);
		//ASSERT(Ret == TRUE);
		return Ret;
	}

	BOOL RemoveSubClass()
	{
		BOOL Ret;
		Ret = RemoveWindowSubclass(m_Hwnd, C32GroupBox::C32SubClassProcBox, (ULONG_PTR)this);
		return Ret;
	}


	virtual BOOL CALLBACK OnCtlColorStatic(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HDC  Hdc = (HDC)wParam;
		HWND Hwnd = (HWND)lParam;
		lResult = 0;
		ZxDebug((__FUNCTION__"():: %ws \n", GetText()));
		m_ColorMask = C32UICOLOR_ALL;
		if (C32ThemeStyle::IsThemeStyleDark())
		{
			Handle = TRUE;
			//�������ֱ���ɫ,�����ÿؼ�����ɫ����Ч
			if(IsUseFontBkGnd())
				SetBkColor(Hdc, C32ThemeStyle::m_ColorFontBk);

			//����������ɫ
			if (IsUseFont())
				SetTextColor(Hdc, C32ThemeStyle::m_ColorFont);

			SetBkMode(Hdc, OPAQUE);
			//���û��ƾ�̬�ؼ������Ļ��ʵľ������Ϊ OPAQUE :���������ֱ���ɫ������Ϊ��ɫ.
			if (IsUseBkGnd())
				lResult = (LRESULT)C32ThemeStyle::m_HbrBkGnd;
		}


		return Handle;
	}


};


class C32SysLink : public C32Window , public C32SysLinkEventCallback
{
public:
	C32SysLink()
	{

	}

	~C32SysLink()
	{


	}

public:
	BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{ 
		BOOL Handle = FALSE;
		PNMLINK Link = (PNMLINK)lParam;
		PLITEM  Item = &Link->item;
		CHAR* NotifyStr = GetGenericNotifyString(Link->hdr.code);
		ZxDebugEx((__FUNCTION__"():: Hwnd %p %s : 0x%08x \n", Link->hdr.hwndFrom, NotifyStr,Link->hdr.code ));
		switch(Link->hdr.code)
		{
			case NM_CLICK:
				if (m_OnClick)
				{
					ZxDebugEx((__FUNCTION__"():: Mask: 0x%08x iLink: %d, state: 0x%08x stateMask: 0x%08x szID: %ws szUrl: %ws\n",
						Item->mask,Item->iLink, Item->state, Item->stateMask, Item->szID, Item->szUrl));

					Handle = m_OnClick(Item, lResult,this);
				}
				break;
		}
		
		return Handle;
	}

};


typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_SELCHANGE)(C32ComboBox* This);

class C32ComboBoxEventCallback
{

public:
	C32ComboBoxEventCallback()
	{
		Init();
	}
	~C32ComboBoxEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnSelChange = NULL;
	}

	VOID SetEventSelChange(C32_EVENT_CALLBACK_SELCHANGE Callback)
	{
		m_OnSelChange = Callback;
	}

	//Button Control Event
	C32_EVENT_CALLBACK_SELCHANGE m_OnSelChange; //���
	
};

class C32ComboBox : public C32Window, public C32ComboBoxEventCallback
{

public:
	C32ComboBox()
	{
		m_CtrlType = C32CtrlTypeCommbox;
		m_ListBox = NULL;

		RtlZeroMemory(&m_BoxInfo, sizeof(COMBOBOXINFO));
		
	}

	~C32ComboBox()
	{

	}

public:
	HWND Create(DWORD dwStyle, 
				int X, int Y, int Cx, int Cy,
				HWND Parent)
	{
		m_Hwnd = CreateWindowEx(0, WC_COMBOBOX, L"C32ComboBox",dwStyle,
								X, Y, Cx, Cy,
								Parent, (HMENU)NULL,  C32Hinstance, (LPVOID)this);
		return m_Hwnd;
	}
	
	BOOL GetComboBoxInfo(PCOMBOBOXINFO pcbi)
	{
		return ::GetComboBoxInfo(m_Hwnd, pcbi);
	}

	HWND GetListBoxHwnd()
	{
		HWND ListBox = NULL;

		COMBOBOXINFO pcbi = {};
		pcbi.cbSize = sizeof(COMBOBOXINFO);
		if(GetComboBoxInfo(&pcbi))
		{
			ListBox = pcbi.hwndList;
		}

		return ListBox;
	}

	VOID GetBoxInfo()
	{
		m_BoxInfo.cbSize = sizeof(COMBOBOXINFO);

		GetComboBoxInfo(&m_BoxInfo);
	}

	VOID Attach(HWND Hwnd)
	{
		C32Window::Attach(Hwnd);

		GetBoxInfo();

		m_ListBox = GetListBoxHwnd();

	}

	BOOL SetEditText(LPCWSTR EditText)
	{
		return ComboBox_SetCueBannerText(m_Hwnd, EditText);
	}

	// �������
	int  Add(LPCWSTR String)
	{
		return ComboBox_AddString(m_Hwnd, String);
	}

	int  AddString(LPCWSTR String)
	{
		return Add(String);
	}

	int AddStringList(CAtlArray<CString>& Array)
	{
		int Count = 0;
		for (int i = 0; i < Array.GetCount(); i++)
		{
			  if(AddString(Array[i]) != CB_ERR)
				Count++;
		}

		return Count;
	}

	//����List�ĸ���
	int Delete(int Index)
	{
		return ComboBox_DeleteString(m_Hwnd, Index);
	}

	// �������
	int Insert(int Index, LPCWSTR String)
	{
		return ComboBox_InsertString(m_Hwnd, Index, String);
	}

	int Reset()
	{
		return ComboBox_ResetContent(m_Hwnd);
	}

	int SelectItemString(LPCWSTR String)
	{
		return ComboBox_SelectString(m_Hwnd, -1, String);
	}

	int SelectItem(int Index)
	{
		return ComboBox_SetCurSel(m_Hwnd, Index);
	}
	
	int GetItemHeight()
	{
		return ComboBox_GetItemHeight(m_Hwnd);
	}

	int SetItemHeight(int iHeight)
	{
		return ComboBox_SetItemHeight(m_Hwnd,0, iHeight);
	}

	int SetSelectItemHeight(int iHeight)
	{
		return ComboBox_SetItemHeight(m_Hwnd,-1, iHeight);
	}

	/*

	*/
	DWORD SetStyleSort(BOOL IsSort = TRUE)
	{
		DWORD Style = GetStyle();
		if (IsSort == FALSE)
		{
			Style &= ~CBS_SORT;
		}else
		{
			Style |= CBS_SORT;
		}

		return SetStyle(Style);
	}

	BOOL ShowList()
	{
		return ComboBox_ShowDropdown(m_Hwnd, TRUE);
	}

	BOOL HideList()
	{
		return ComboBox_ShowDropdown(m_Hwnd, FALSE);

	}

	BOOL Enable()
	{
		return ComboBox_Enable(m_Hwnd, TRUE);
	}

	BOOL Disable()
	{
		return ComboBox_Enable(m_Hwnd, FALSE);
	}

	int GetCurrentSelect()
	{
		return (int)ComboBox_GetCurSel(m_Hwnd);
	}
	
	int GetString(int Index, CString& String)
	{
		int Length = (int)ComboBox_GetLBTextLen(m_Hwnd, Index);
		if (Length <= 0)
			return LB_ERR;

		C32String TmpString;
		TmpString.AssignStringW(Length++);

		Length = (int)ComboBox_GetLBText(m_Hwnd, Index, (LPWSTR)TmpString.GetString());
		TmpString.m_Length = Length;
		String.Append(TmpString.GetString(), TmpString.m_Length);

		return  TmpString.GetStringLength();
	}

	CString GetCurrentSelectString()
	{
		CString String;
		int iIndex = GetCurrentSelect();
		if(GetString(iIndex, String))
		{
			return String;
		}

		return String;
	}

	BOOL GetCueBannerText(CString& Text)
	{
	
		C32String Buffer;
		Buffer.AssignStringW(4096);
		
		if (Buffer.GetString())
		{
			BOOL Ret = ComboBox_GetCueBannerText(m_Hwnd, Buffer.GetString(), 4096);
			if (Ret == TRUE)
			{
				Text.Append(Buffer, Buffer.GetStringLengthW());

				return TRUE;
			}
		}

		return FALSE;
	}

	BOOL GetComboBoxText(CString& Text)
	{
		C32String Buffer;
		Buffer.AssignStringW(4096);

		if (Buffer.GetString())
		{
			BOOL Ret = ComboBox_GetText(m_Hwnd, Buffer.GetString(), 4096);
			if (Ret)
			{
				Text.Append(Buffer, Buffer.GetStringLengthW());

				return TRUE;
			}
		}

		return FALSE;
	}
	
	BOOL SetText(LPCWSTR Text)
	{
	
		BOOL Ret = ComboBox_SetText(m_Hwnd, Text);
		
		return Ret;
	}

public:
	//virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	//{
	//	BOOL Handle = FALSE;

	//	lResult = 0;
	//	LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lParam;
	//	setlocale(LC_ALL, "Chinese");
	//	CString Text;
	//	GetCueBannerText(Text);
	//	ZxDebugEx((__FUNCTION__"():: %ws itemState:0x%08x\n", Text.GetString(), pdis->itemState));
	//	ASSERT(pdis->CtlType == ODT_COMBOBOX);
	//	if (C32ThemeStyle::IsThemeStyleDark())
	//	{
	//		Handle = TRUE;
	//		if (pdis->CtlType == ODT_COMBOBOX)
	//		{
	//			HDC hdc = pdis->hDC; 
	//			RECT rect = pdis->rcItem;
	//			HBRUSH  Brush = CreateSolidBrush(0x0);

	//			// ���ݰ�ť״̬���Ʊ���
	//			if (pdis->itemState & ODS_SELECTED)
	//			{
	//				// ��ť����״̬
	//				FillRect(hdc, &rect, Brush);
	//			}
	//			else
	//			{
	//				// ��ť����״̬
	//				FillRect(hdc, &rect, Brush);
	//			}

	//			// ���ư�ť�ı�
	//			wchar_t text[256] = L"ABC";
	//			

	//			DrawText(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//		}
	//	}

	//	return Handle;
	//}


	//Event
public:
	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		BOOL Handle = FALSE;
		C32SetHandleLReslut(FALSE, 0);
		DWORD NotifyCode;
		NotifyCode = HIWORD(wParam);
		ZxDebugEx((__FUNCTION__"():: Text: %ws \n", this->GetText()));
		switch(NotifyCode)
		{
		case CBN_SELCHANGE:
			Handle  = (m_OnSelChange ? m_OnSelChange(this) : FALSE);
			break;
		}

		if (Handle == TRUE)
			lResult = 0;

		return Handle;
	}

	virtual BOOL CALLBACK OnCtlColorListBox(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HDC  Hdc = (HDC)wParam;
		HWND Hwnd = (HWND)lParam;
		lResult = 0;
		ZxDebug((__FUNCTION__"():: %ws \n", GetText()));

		if (C32ThemeStyle::IsThemeStyleDark() /*&& IsUseColor()*/ )
		{
			Handle = TRUE;
			m_ColorMask = C32UICOLOR_ALL;
			//�������ֱ���ɫ,�����ÿؼ�����ɫ����Ч
			if(IsUseFontBkGnd())
				SetBkColor(Hdc, C32ThemeStyle::m_ColorFontBk);

			//����������ɫ
			if (IsUseFont())
				SetTextColor(Hdc, C32ThemeStyle::m_ColorFont);

			SetBkMode(Hdc, m_ColorMode);
			//���û��ƾ�̬�ؼ������Ļ��ʵľ������Ϊ OPAQUE :���������ֱ���ɫ������Ϊ��ɫ.
			if (IsUseBkGnd())
				lResult = (LRESULT)C32ThemeStyle::m_HbrBkGnd;
		}


		return Handle;
	}

	virtual BOOL CALLBACK OnCtlColorEdit(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HDC  Hdc = (HDC)wParam;
		HWND Hwnd = (HWND)lParam;
		lResult = 0;
		ZxDebugEx((__FUNCTION__"():: %ws \n", GetText()));

		if (C32ThemeStyle::IsThemeStyleDark() /*&& IsUseColor() */)
		{
			m_ColorMask = C32UICOLOR_ALL;
			Handle = TRUE;
			//�������ֱ���ɫ,�����ÿؼ�����ɫ����Ч
			if(IsUseFontBkGnd())
				SetBkColor(Hdc, C32ThemeStyle::m_ColorFontBk);

			//����������ɫ
			if (IsUseFont())
				SetTextColor(Hdc, C32ThemeStyle::m_ColorFont);

			SetBkMode(Hdc, OPAQUE);
			//���û��ƾ�̬�ؼ������Ļ��ʵľ������Ϊ OPAQUE :���������ֱ���ɫ������Ϊ��ɫ.
			if (IsUseBkGnd())
				lResult = (LRESULT)C32ThemeStyle::m_HbrBkGnd;
		}


		return Handle;
	}

	HWND   m_ListBox;

	COMBOBOXINFO m_BoxInfo;
	
};

class C32ListBox : public C32Window
{

public:
	static HINSTANCE hInstance;
	
	static VOID Initialize()
	{
		
	}

public:
	C32ListBox()
	{
		Init();
	}
	virtual ~C32ListBox()
	{

	}

	HWND  Create(DWORD dwStyle, 
		int X, int Y, int Cx, int Cy,
		HWND Parent)
	{
		
		m_Hwnd = CreateWindow( L"listbox", NULL, dwStyle, 
								X, Y, Cx, Cy,
								Parent, (HMENU)NULL, hInstance, this);
		C32GetLastError();
		
		m_Parent = Parent;

		return m_Hwnd;
	}
	//index
	int AddString(LPCWSTR String)
	{
		return (int)SendMessageW(m_Hwnd, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)String);		
	}
	//Count
	int DeleteString(int Index)
	{
		return (int)SendMessage(m_Hwnd, LB_DELETESTRING, (WPARAM)Index, (LPARAM)NULL);		

	}

	int InsertString(int Index, LPCWSTR String)
	{
		return (int)SendMessage(m_Hwnd, LB_INSERTSTRING, (WPARAM)Index, (LPARAM)String);		
	}

	void Reset()
	{
		SendMessage(m_Hwnd, LB_RESETCONTENT, (WPARAM)NULL, (LPARAM)NULL);		
	}

	int GetCount()
	{
		 int Count = (int)SendMessage(m_Hwnd,  LB_GETCOUNT, (WPARAM)NULL, (LPARAM)NULL);
		 if (Count == LB_ERR)
			Count = 0;

		return Count;
	}
	
	int GetString(int Index, C32String& String)
	{
		int Length = (int)SendMessageW(m_Hwnd, LB_GETTEXTLEN, (WPARAM)Index, (LPARAM)0);
		if (Length <= 0)
			return LB_ERR;
		
		String.AssignStringW(Length++);
		
		Length = (int)ListBox_GetText(m_Hwnd, Index, (LPWSTR)String.GetBuffer());
		String.m_Length = Length;
		return  String.GetStringLength();
	}

	LPWSTR GetString(int Index)
	{
		GetString(Index,m_StringText);

		return (LPWSTR)m_StringText;
	}

	int SelectString(LPCWSTR String, int Index = -1)
	{
		return (int)SendMessage(m_Hwnd, LB_SELECTSTRING, (WPARAM)Index, (LPARAM)String);		
	}

	// single-selection list box
	// Current Select Item
	int SetCurrentSelect(int Index)
	{
		return (int)SendMessage(m_Hwnd, LB_SETCURSEL, (WPARAM)Index, (LPARAM)NULL);
	}
	
	int ClearCurrentSelect()
	{
		return SetCurrentSelect(-1);
	}

	int GetSelectCount()
	{
		int Count = ListBox_GetSelCount(m_Hwnd);
		if (Count == LB_ERR)
			return 0;

		return Count;
	}

	PINT GetCurentSelectMul(PINT ArraySize)
	{
		int Count = GetSelectCount();
		if (Count == 0)
			return NULL;

		PINT Array = new INT[Count];
		if (Array == NULL)
			return NULL;

		if (Array)
			RtlZeroMemory(Array, sizeof(INT)*4);
		int Sel = ListBox_GetSelItems((HWND)m_Hwnd, Count, Array);
		if (Sel < 0)
		{
			delete Array;
			Array = NULL;
			Count = 0;
		}
		*ArraySize = Count;
		return Array;

	}

	int GetCurrentSelect()
	{
		return (int)SendMessage(m_Hwnd, LB_GETCURSEL, (WPARAM)NULL, (LPARAM)NULL);
	}
	
	LPCWSTR GetCurrentSelectString()
	{
		int iIndex = GetCurrentSelect();
		if(GetString(iIndex, m_StringText))
		{
			return m_StringText.GetString();
		}

		return NULL;
	}

	//multiple-selection list box.
	// Select Item
	BOOL SetSelect(int Index)
	{
		//LPARAM lParam = MAKELPARAM(Index, Index);
		int Ret = (int)SendMessage(m_Hwnd, LB_SETSEL, (WPARAM)TRUE, (LPARAM)Index);
		return (Ret == LB_ERR);
	}

	BOOL ClearSelect(int Index)
	{
		int Ret = (int)SendMessage(m_Hwnd, LB_SETSEL, (WPARAM)FALSE, (LPARAM)Index);
		return (Ret == LB_ERR);
	}

	BOOL SetSelectAll()
	{
		return SetSelect(-1);
	}

	BOOL ClearSelectAll()
	{
		return ClearSelect(-1);
	}

	BOOL SelectItemRange(DWORD iStart, DWORD iEnd)
	{
		LRESULT Ret = SendMessage(m_Hwnd, LB_SELITEMRANGE, (WPARAM)TRUE, (LPARAM)MAKELPARAM(iStart, iEnd));		

		return (Ret == LB_ERR);
	}

	BOOL ClearItemRance(DWORD iStart, DWORD iEnd)
	{
		LRESULT Ret = SendMessage(m_Hwnd, LB_SELITEMRANGE, (WPARAM)FALSE, (LPARAM)MAKELPARAM(iStart, iEnd));		

		return (Ret == LB_ERR);
	}

public:
	BOOL SetItemHeight(int Height, int Index = 0)
	{
	  LRESULT Ret = SendMessage(m_Hwnd, LB_SETITEMHEIGHT, (WPARAM)Index, (LPARAM)Height);		
	  return (Ret == LB_ERR);
	}
	//multiple-column list box
	VOID SetColumnWidth(int Width)
	{
		ListBox_SetColumnWidth(m_Hwnd, Width);	
	}
public:
	//������
	
	int  GetHorizontalExtent()
	{
		return ListBox_GetHorizontalExtent(m_Hwnd);
	}

	VOID  SetHorizontalExtent(int Width)
	{
		return ListBox_SetHorizontalExtent(m_Hwnd, Width);
	}

	BOOL IsHorizontalScroll()
	{
		DWORD Style = GetStyle();
		return (Style & WS_HSCROLL);
	}


public:
	 //WM_MEASUREITEM: 
	virtual BOOL OnMeasureItem(LPMEASUREITEMSTRUCT lpmis, LRESULT& lResult)
	{
		lpmis->itemHeight = m_ItemCy;
		lResult = (LRESULT)TRUE;

		return TRUE;
	}

	//WM_DRAWITEM
	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		TEXTMETRIC tm = {}; 
		C32String String;
		RECT  Rect = lpdis->rcItem;
		if (IsOwnerDraw() == FALSE)
			return FALSE;

		lResult = (LRESULT)TRUE;
		// If there are no list box items, skip this message. 
		if (lpdis->itemID == -1)
		{
			return TRUE;
		}
		
		C32DrawControl Draw;
		C32DeviceContext Cdc;
		Draw.Open(WC_BUTTON, this->GetWindow());
		
		switch(lpdis->itemAction)
		{
			case ODA_SELECT: 
			case ODA_DRAWENTIRE: 
				  if(GetString(lpdis->itemID, String) ==LB_ERR)
					break;
				 
				Cdc.SetHdc(lpdis->hDC);
				Cdc.SelectFont32();
				  // Is the item selected? 
				if (lpdis->itemState & ODS_SELECTED) 
				{ 		
					Draw.DrawCheckBox(lpdis->hDC, CBS_CHECKEDNORMAL, lpdis->rcItem, String);
				}else
				{
					Draw.DrawCheckBox(lpdis->hDC, CBS_UNCHECKEDNORMAL, lpdis->rcItem, String);
				} 
				break;
			/*case ODA_FOCUS: 
				Draw.DrawCheckBox(lpdis->hDC, CBS_CHECKEDHOT, lpdis->rcItem, String);
				break;*/
		}

		return TRUE;

	}

	virtual BOOL CALLBACK OnCtlColorListBox(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HDC  Hdc = (HDC)wParam;
		HWND Hwnd = (HWND)lParam;
		lResult = 0;

		if (IsUseColor())
		{
			Handle = TRUE;
			//�������ֱ���ɫ,�����ÿؼ�����ɫ����Ч
			if(IsUseFontBkGnd())
				SetBkColor(Hdc, m_ColorFontBk);

			//����������ɫ
			if (IsUseFont())
				SetTextColor(Hdc, m_ColorFont);

			SetBkMode(Hdc, m_ColorMode);
			//���û��ƾ�̬�ؼ������Ļ��ʵľ������Ϊ OPAQUE :���������ֱ���ɫ������Ϊ��ɫ.
			if (IsUseBkGnd())
				lResult = (LRESULT)m_HbrBkGnd;
		}


		return Handle;
	}


public:
	VOID SetItemCy(int Height)
	{
		m_ItemCy = Height;
	}

public:
	BOOL IsOwnerDraw()
	{
		DWORD Style = GetWindowStyle(m_Hwnd);

		if (Style&(LBS_OWNERDRAWFIXED|LBS_OWNERDRAWVARIABLE))
			return TRUE;
		else
			return FALSE;
	}

public:
	VOID Init()
	{
		m_ItemCy = 40;
	}
public:
	int  m_ItemCy;	

public:  // �Ի���Ҫ��ͼ��
	C32Icon   m_IconCheck;
	C32Icon   m_IconUnCheck;

};

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_SEL_CHANGE)(C32String& NewText, LPARAM lParam, LPNMTREEVIEW lpnmtv,  LRESULT& lResult, C32TreeView* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_ITEM_CHANGE)(C32String& ItemText, NMTVITEMCHANGE* lpnmic,  LRESULT& lResult, C32TreeView* This);


class C32TreeViewEventCallback
{

public:
	C32TreeViewEventCallback()
	{
		Init();
	}
	~C32TreeViewEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnNotifySelChanged = NULL;
		m_OnNotifyItemChanged = NULL;
	}

	
	VOID SetEventNotifySelChange(C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_SEL_CHANGE Callback)
	{
		m_OnNotifySelChanged = Callback;
	}

	VOID SetEventNotifyItemChanged(C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_ITEM_CHANGE Callback)
	{
		m_OnNotifyItemChanged = Callback;
	}

public:
	
	/*
		The return value is ignored.
	*/
	C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_SEL_CHANGE m_OnNotifySelChanged;
	/*
		TVN_ITEMCHANGED Returns FALSE to accept the change, or TRUE to prevent the change.
	*/
	C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_ITEM_CHANGE m_OnNotifyItemChanged;
};

class C32TreeView : public C32Window, public C32TreeViewEventCallback
{
#define TV_MASK_NO_BIT -1
#define C32TV_CHECK_STATE 0x2000
#define C32TV_UNCHECK_STATE 0x1000
#define C32TvGetCheckState(x) (x &LVIS_STATEIMAGEMASK)
#define C32TvIsCheckState(x) (C32TvGetCheckState(x) == C32TV_CHECK_STATE)
public:

	static HINSTANCE  hInstance; //
	static  LRESULT  CALLBACK TreeSubclassProc (HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

public:
	C32TreeView(){};
	~C32TreeView(){};

	HWND Create(DWORD  dwExStyle, DWORD dwStyle,int X, int Y, int Width, int Height, HWND Parent);

	VOID DestroyView();

	// �ؼ���ʽ
	VOID SetExplorerTheme(){if(m_Hwnd)SetWindowTheme(m_Hwnd, L"Explorer", NULL);};

	VOID SetExtendedStyles(DWORD dwExStyle);

	VOID AddExtendedStyles(DWORD dwExStyle);

	DWORD GetExtendedStyles();

	BOOL  IsCheckBoxStyle()
	{
		DWORD Style = GetStyle();
		if (Style& TVS_CHECKBOXES)
			return TRUE;
		else
			return FALSE;
	}

	BOOL SetSubclass();

	BOOL RemovSubClass()
	{
		RemoveWindowSubclass(m_Hwnd, C32TreeView::TreeSubclassProc, (ULONG_PTR)this);
	}
public: //��Ա��������
	//����.rc���Ҽ���ʾ�˵�����ԴID
	VOID SetMenuId(int ResourceId)
	{
		m_Menu.m_ResourceId = ResourceId;
	}

	VOID SetImageList(BOOL bNormal = TRUE, BOOL bState = TRUE)
	{
		//Sets the normal image list, which contains the selected and nonselected images for the tree view item
		if (bNormal)
			TreeView_SetImageList(m_Hwnd, m_ImageListNormal, TVSIL_NORMAL);

		if (bState)
			TreeView_SetImageList(m_Hwnd, m_ImageListState, TVSIL_STATE);
	}

	VOID AddSilNormalIcon(int ResourceId)
	{
		m_ImageListNormal.AddIcon(ResourceId);
	}

	VOID AddSilStateIcon(int ResourceId)
	{
		m_ImageListState.AddIcon(ResourceId);
	}

	// ����ڵ�
	HTREEITEM InsertItem(HTREEITEM Parent, HTREEITEM InsertAfter, LPWSTR Text, int iImage, int iSelectedImage, int cChildren, LPARAM lParam);

	HTREEITEM InsertItem(HTREEITEM Parent, HTREEITEM InsertAfter, LPWSTR Text, int cChildren = 1, int iImage = TV_MASK_NO_BIT,  LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItem(Parent, InsertAfter, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);

		return hItem;
	}

	HTREEITEM InsertItemFirst(HTREEITEM Parent, LPWSTR Text, int cChildren = 1, int iImage = TV_MASK_NO_BIT,  LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItem(Parent, (HTREEITEM)TV_FIRST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);

		return hItem;
	}

	HTREEITEM InsertItemLast(HTREEITEM Parent, LPWSTR Text, int cChildren = 1, int iImage = TV_MASK_NO_BIT,  LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItem(Parent, (HTREEITEM)TVI_LAST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);

		return hItem;
	}

	HTREEITEM InsertItemSort(HTREEITEM Parent, LPWSTR Text, int cChildren = 1, int iImage = TV_MASK_NO_BIT,  LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItem(Parent, (HTREEITEM)TVI_SORT, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);

		return hItem;
	}

	HTREEITEM InsertItemRoot(HTREEITEM InsertAfter, LPWSTR Text, int iImage, int iSelectedImage , int cChildren , LPARAM lParam);

	HTREEITEM InsertItemRootText(HTREEITEM InsertAfter, LPWSTR Text, int cChildren ,LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot(InsertAfter, Text, TV_MASK_NO_BIT, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}

	HTREEITEM InsertItemRoot(LPWSTR Text, int cChildren = 1, int iImage =TV_MASK_NO_BIT, LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot(TVI_LAST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}

	HTREEITEM InsertItemRootSort(LPWSTR Text, int cChildren = 1, int iImage =TV_MASK_NO_BIT, LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot((HTREEITEM)TVI_SORT, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}

	HTREEITEM InsertItemRootFirst(LPWSTR Text, int cChildren = 1, int iImage =TV_MASK_NO_BIT, LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot((HTREEITEM)TVI_FIRST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}
	
	HTREEITEM InsertItemRootLast(LPWSTR Text, int cChildren = 1, int iImage =TV_MASK_NO_BIT, LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot((HTREEITEM)TVI_LAST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}


	HTREEITEM InsertItemAsyn(HTREEITEM Parent, HTREEITEM InsertAfter, LPWSTR Text, int iImage, int iSelectedImage, int cChildren, LPARAM lParam);
	
public:
	BOOL   DeleteAllItem()
	{
		return TreeView_DeleteAllItems(m_Hwnd);
	}

	BOOL   GetItem(HTREEITEM hItem,TVITEM &tvi, C32String& Text)
	{
		Text.AssignStringW(260);
		
		//RtlZeroMemory(&tvi, sizeof(tvi));
		tvi.mask = TVIF_TEXT | TVIF_IMAGE| TVIF_PARAM|TVIF_STATE|TVIF_HANDLE|TVIF_CHILDREN;
		tvi.hItem = hItem;
		
		tvi.stateMask = TVIS_SELECTED|TVIS_CUT|TVIS_EXPANDED|TVIS_EXPANDEDONCE|TVIS_EXPANDPARTIAL|TVIS_EX_DISABLED;
		tvi.pszText = Text.GetString();
		tvi.cchTextMax = Text.GetTotalCount();
		
		Text.SetCount();

		return TreeView_GetItem(m_Hwnd, &tvi);
	}
	
	C32String   GetItemText(HTREEITEM hItem)
	{
		C32String Text;
		Text.AssignStringW(260);

		TVITEM tvi = {};
		tvi.mask = TVIF_TEXT ;
		tvi.hItem = hItem;

		tvi.pszText = Text.GetString();
		tvi.cchTextMax = Text.GetTotalCount();

		BOOL bGet = TreeView_GetItem(m_Hwnd, &tvi);
		if (bGet == FALSE)
		{
			return C32String();
		}
		Text.SetCount();
		return Text;
	}

	LPARAM   GetItemUserData(HTREEITEM hItem)
	{
		TVITEM tvi = {};
		tvi.mask = TVIF_PARAM ;
		tvi.hItem = hItem;
		BOOL bGet = TreeView_GetItem(m_Hwnd, &tvi);
		if (bGet == FALSE)
			return NULL;
		
		return tvi.lParam;
	}


	BOOL GetItem(HTREEITEM hItem, C32String& Text, LPARAM& lParam)
	{
		TVITEM tvi = {};
		if(GetItem(hItem, tvi, Text) == TRUE)
		{
			lParam = tvi.lParam;
		}else
			return FALSE;

		return TRUE;
	}

	BOOL GetItemlParam(HTREEITEM hItem, LPARAM& lParam)
	{
		TVITEM tvi = {};
		C32String Text;
		if(GetItem(hItem, tvi,Text) == TRUE)
		{
			lParam = tvi.lParam;
			return TRUE;
		}

		return TRUE;
	} 

	BOOL GetSelectItem(C32String& Text, LPARAM& lParam)
	{ 
		TVITEM tvi = {};
		HTREEITEM hti = TreeView_GetSelection(m_Hwnd);
		if (hti)
		{
			if(GetItem(hti, tvi,Text))
			{
				lParam = tvi.lParam;
				return TRUE;
			}
		}

		return FALSE;
	}

	HTREEITEM GetRootItem()
	{
		return TreeView_GetRoot(m_Hwnd);
	}

	/*
		������Child
	*/
	VOID GetChild(HTREEITEM hItem, CAtlArray<HTREEITEM>& hChildList)
	{
		HTREEITEM hChild = TreeView_GetChild(m_Hwnd, hItem);
		HTREEITEM hSibling = hChild;
		if (hChild)
		{
			do 
			{
				hChildList.Add(hSibling);
				GetChild(hSibling, hChildList);
			} while ((hSibling = TreeView_GetNextSibling(m_Hwnd, hSibling)) != NULL);
		}
		
	}

	LPARAM GetSelectItemlParam(LPARAM& lParam)
	{
		C32String Text;
		GetSelectItem(Text, lParam);

		return lParam;
	}
	
	UINT GetCount()
	{
		 return TreeView_GetCount(m_Hwnd);
	}

	VOID GetItemLevel(HTREEITEM hItem, int& Level)
	{
		if (hItem == NULL)
			return ;

		HTREEITEM hParent = TreeView_GetParent(m_Hwnd, hItem);
		if (hParent)
		{
			++Level;
			return  GetItemLevel(hParent, Level);
		}
			

	}
	
	UINT GetCheckState(HTREEITEM hItem)
	{
		UINT Check = TreeView_GetCheckState(m_Hwnd, hItem);
		return Check;
	}

	UINT IsCheckState(HTREEITEM hItem)
	{
		if (GetCheckState(hItem) == 1)
			return TRUE;

		return FALSE;
	}

	VOID SetCheckState(HTREEITEM hItem, BOOL bCheckState = TRUE)
	{
		TreeView_SetCheckState(m_Hwnd, hItem, bCheckState)
	}

	VOID SetChildCheckState(HTREEITEM hItem, BOOL bCheckState = TRUE)
	{
		HTREEITEM hChild = TreeView_GetChild(m_Hwnd, hItem);
		HTREEITEM hSibling = hChild;
		if (hChild)
		{
			do 
			{
				SetChildCheckState(hSibling, bCheckState);
			} while ((hSibling = TreeView_GetNextSibling(m_Hwnd, hSibling)) != NULL);
		}
		SetCheckState(hItem, bCheckState);

	}

	VOID GetCheckStateItems(HTREEITEM hItem, CAtlArray<HTREEITEM>& List)
	{
		HTREEITEM hChild = TreeView_GetChild(m_Hwnd, hItem);
		HTREEITEM hSibling = hChild;
		if (hChild)
		{
			do 
			{
				GetCheckStateItems(hSibling, List);
			} while ((hSibling = TreeView_GetNextSibling(m_Hwnd, hSibling)) != NULL);
		}
		
		if(IsCheckState(hItem))
		{
			List.Add(hItem);
		}


	}

	VOID GetCheckStateItems(CAtlArray<HTREEITEM>& List)
	{
		HTREEITEM hRootItem;
		hRootItem = TreeView_GetRoot(m_Hwnd);

		GetCheckStateItems(hRootItem, List);
	}


public:	
	
	//WM_CONTEXMENU
	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		int xCursor, yCursor;

		xCursor = GET_X_LPARAM(lParam);
		yCursor = GET_Y_LPARAM(lParam);
		if (m_Menu.m_ResourceId == 0)
			return FALSE;
		
		m_Menu.Display(m_Menu.m_ResourceId, 1,xCursor, yCursor, m_Hwnd);

		return TRUE;

	}

	virtual BOOL CALLBACK OnContextMenu(HWND hwnd, int xCursor, int yCursor)
	{
		m_Menu.Display(m_Menu.m_ResourceId, 1,xCursor, yCursor, m_Hwnd);
		return TRUE;
	}

	// WM_COMMAND
	//virtual BOOL CALLBACK OnCommand()
	BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND HwndCtrl;
		DWORD MenuId;
		HwndCtrl= (HWND)lParam;
		MenuId = LOWORD(wParam);
		
		m_Menu.SelectSubMenuItem(MenuId);

		ZxDebugEx((__FUNCTION__"():: %ws \n", m_Menu.GetSubItemString(C32CommandMenuId(wParam))));

		if (m_OnCommandMenu)
			Handle = m_OnCommandMenu(C32CommandMenuId(wParam), lResult, this);

		
		return TRUE;	
	}
	// WM_NOTIFY
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	 
	//Return nonzero to prevent the default processing, or zero to allow the default processing.
	virtual BOOL CALLBACK OnNotifyNmClick(LPNMHDR lpnmhdr, LRESULT& lResult)
	{
		lResult = FALSE ;
		return TRUE;
	}

	//Return zero to enable the control to set the cursor or nonzero to prevent the control from setting the cursor.

	virtual BOOL CALLBACK OnNotifyNmSetCursor(LPNMMOUSE lpnmm, LRESULT& lResult)
	{
		lResult = 1;
		return TRUE;
	}


	//Returns FALSE to accept the change, or TRUE to prevent the change
	virtual BOOL CALLBACK OnNotifySelChanged(LPNMTREEVIEW NMTreeView)
	{
		(NMTreeView);
		m_Result = FALSE ;
		return FALSE;
	}
	//Returns TRUE to prevent the selection from changing.
	virtual BOOL CALLBACK OnNotifySelChanging(LPNMTREEVIEW NMTreeView)
	{
		(NMTreeView);
		m_Result = FALSE ;		
		return TRUE;
	}

	//Returns FALSE to accept the change, or TRUE to prevent the change.
	virtual BOOL CALLBACK OnNotifyItemChanging(NMTVITEMCHANGE*   NMItemChange)
	{
		(NMItemChange);
		m_Result = FALSE ;
		return TRUE;
	}

	virtual BOOL CALLBACK OnNotifyItemChanged(NMTVITEMCHANGE*  lpnmtvi, LRESULT& lResult)
	{
		ZxDebugEx(("uChanged: 0x%08x uStateNew : 0x%08x uStateOld : 0x%08x lParam:%p \n",
				  lpnmtvi->uChanged, lpnmtvi->uStateNew, lpnmtvi->uStateOld, lpnmtvi->lParam));
		(lpnmtvi);
		BOOL Handle = FALSE;
		lResult = FALSE ;

		int Level = 0;  
		GetItemLevel(lpnmtvi->hItem, Level);
		if (IsCheckBoxStyle())
		{
			if (C32TvGetCheckState(lpnmtvi->uStateOld) != C32TvGetCheckState(lpnmtvi->uStateNew))
			{
				if (C32TvIsCheckState(lpnmtvi->uStateNew))
				{
					SetChildCheckState(lpnmtvi->hItem);
				}else
				{
					SetChildCheckState(lpnmtvi->hItem, FALSE);
				}
			} 
		}

		if (m_OnNotifyItemChanged)
		{
			C32String ItemText = GetItemText(lpnmtvi->hItem);
			ZxDebug((__FUNCTION__"()::Item Text: %ws \n", ItemText.GetString()));
			Handle = m_OnNotifyItemChanged(ItemText, lpnmtvi, lResult, this); 

		}
		
		return Handle;
	}
	//The return value is ignored.
	virtual BOOL CALLBACK OnNotifySelChanged(LPNMTREEVIEW lptv, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = FALSE ;
		if (m_OnNotifySelChanged)
		{
			C32String Text;
			LPARAM    lParam;
			if(GetItem(lptv->itemNew.hItem, Text, lParam) == TRUE)
				Handle = m_OnNotifySelChanged(Text, lParam, lptv, lResult, this);
		}
		
		return Handle;
	}
	//Returns TRUE to prevent the selection from changing.
	virtual BOOL CALLBACK OnNotifySelChanging(LPNMTREEVIEW lptv, LRESULT& lResult)
	{
		lResult = FALSE ;
		return TRUE;
	}

	virtual BOOL CALLBACK OnNotifyCustomDraw(LPNMTVCUSTOMDRAW  lplvcd, LRESULT& lResult)
	{ 
		return FALSE;
	}

	virtual BOOL CALLBACK OnNotifyGetDispInfo(LPNMTVDISPINFO NMTvDispInfo);


	virtual LPWSTR CALLBACK AsynGetText(TVITEM& Tvi)
	{
		return L"AsynGetText";
	}

	virtual int    CALLBACK AsynGetSelectedImage(TVITEM& Tvi)
	{
		return 0;
	}

	virtual int    CALLBACK AsynGetImage(TVITEM& Tvi)
	{
		return 0;
	}

	virtual int    CALLBACK AsynGetChildren(TVITEM& Tvi)
	{
		return 0;
	}

public:
	VOID Init()
	{

		m_Cx = 0;
		m_Cy = 0;
	}
public:


public:
	LRESULT		 m_Result;
	C32ImageList m_ImageListNormal;
	C32ImageList m_ImageListState;
	C32Menu		 m_Menu;



};

class C32HeaderEventCallback
{

public:
	C32HeaderEventCallback()
	{
		Init();
	}
	
	~C32HeaderEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnNotifyItemStateIconClick = NULL;
		m_OnNotifyBeginTrack = NULL;
		m_OnNotifyEndTrack = NULL;

	}

	VOID SetEventItemStateIconClick(C32_EVENT_CALLBACK_HEADER_NOTIFY Callback)
	{
		m_OnNotifyItemStateIconClick = Callback;
	}

	VOID SetEventBeginTrack(C32_EVENT_CALLBACK_HEADER_NOTIFY Callback)
	{
		m_OnNotifyBeginTrack = Callback;
	}

	VOID SetEventEndTrack(C32_EVENT_CALLBACK_HEADER_NOTIFY Callback)
	{
		m_OnNotifyEndTrack = Callback;
	}


	//��� CheckBox
	C32_EVENT_CALLBACK_HEADER_NOTIFY m_OnNotifyItemStateIconClick;
	C32_EVENT_CALLBACK_HEADER_NOTIFY m_OnNotifyBeginTrack;
	C32_EVENT_CALLBACK_HEADER_NOTIFY m_OnNotifyEndTrack;


};



class C32Header : public C32Window, public C32HeaderEventCallback
{
#define HEADER_COUNT_MAX  20

public:
	C32Header()
	{
		Init();
	};
	~C32Header(){};

public:
	static LRESULT C32SubClassProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam,
		UINT_PTR uIdSubclass,DWORD_PTR dwRefData);

public:

	BOOL SetSubClass(DWORD_PTR dwRefData = 0)
	{
		BOOL Ret;
		Ret = SetWindowSubclass(m_Hwnd, C32Header::C32SubClassProc, (ULONG_PTR)this, dwRefData);
		ASSERT(Ret == TRUE);

		return Ret;
	}

	BOOL RemoveSubClass()
	{
		BOOL Ret;

		Ret = RemoveWindowSubclass(m_Hwnd, C32Header::C32SubClassProc, (ULONG_PTR)this);

		return Ret;
	}

	VOID SetHeader(HWND Header, C32ListView* List = NULL)
	{
		  m_List = List;
		  Attach(Header);
	}
	
	CString GetItemString(int iItem)
	{
		CString String;
		BOOL Ret;
		
		HDITEM Hdi;
		Hdi.mask = HDI_TEXT;
		Hdi.pszText = String.GetBufferSetLength(256);;
		Hdi.cchTextMax = 256;
		Ret = GetItem(iItem, Hdi);
		if (Ret ==  FALSE)
			return L"";

		String.ReleaseBuffer();
		return String;
	}

	BOOL GetItem(int iItem, HDITEM& hdi)
	{
		return Header_GetItem((HWND)m_Hwnd, iItem, &hdi);
	}

	BOOL GetItemRect(int nIndex, LPRECT lpRect) const
	{ 
		return (BOOL)::SendMessage(m_Hwnd, HDM_GETITEMRECT, nIndex, (LPARAM)lpRect); 
	}
	
	int GetWidth(int iItem = 0)
	{
		HDITEM hdi = {};
		hdi.mask = HDI_WIDTH;

		if(GetItem(iItem, hdi) == FALSE)
			return 0;

		return hdi.cxy;
	}

	int GetItemWidth(int iItem = 0)
	{
		HDITEM hdi = {};
		hdi.mask = HDI_WIDTH;

		if(GetItem(iItem, hdi) == FALSE)
			return 0;

		return hdi.cxy;
	}
	
	BOOL SetItem(int iItem, HDITEM& hdi)
	{
		return Header_SetItem((HWND)m_Hwnd, iItem, &hdi);
	}

	BOOL DeleteItem(int iItem)
	{
		return Header_DeleteItem(m_Hwnd, iItem);
	}

	int GetFormat(int iItem)
	{
		HDITEM hdi = {};
		hdi.mask = HDI_FORMAT;
		GetItem(iItem, hdi);

		return hdi.fmt;
	}

	int GetSort(int iItem)
	{
		int fmt = GetFormat(iItem);
		
		fmt &= HDF_SORTUP|HDF_SORTDOWN;

		return(fmt);
	}

	void SetFormat(int iItem, int Format)
	{
		HDITEM hdi = {};
		hdi.mask = HDI_FORMAT;
		hdi.fmt =Format;
		SetItem(iItem, hdi);
	}

	void AddFormat(int iItem, int Format)
	{
		int fmt = 0;
		fmt = GetFormat(iItem);

		if ((fmt& Format) == Format)
			return;

		fmt|= Format;
		SetFormat(iItem, fmt);
	}

	VOID ResetSort(int iItem)
	{
		HDITEM  hi = {};
		hi.mask = HDI_FORMAT;
		if(GetItem(iItem, hi))
		{
			int sfmt = (HDF_SORTDOWN | HDF_SORTUP);
			if (hi.fmt & sfmt)
			{
				hi.fmt &=(~sfmt);
				SetItem(iItem, hi);
			}
			
		}
	}

	VOID SetSort(int iItem, BOOL bDown = TRUE)
	{
		int fmt;
		fmt = GetFormat(iItem);
		
		int sfmt = (HDF_SORTDOWN | HDF_SORTUP);
		fmt &=(~sfmt);
		fmt |= (bDown ? HDF_SORTDOWN : HDF_SORTUP);
				
		SetFormat(iItem, fmt);
	}

	/*
		ֻ��һ����ʾ����ͼ��
	*/
	VOID SetHeaderSort(int iItem, BOOL bDown = TRUE)
	{
		int Count = GetCount();
		for(int i = 0; i < Count; i++)
		{
			if (iItem != i)
				ResetSort(i);
			else
				SetSort(i, bDown);
		}
	}

	VOID SetHeaderSortUp(int iItem)
	{
		SetHeaderSort(iItem, FALSE);
	}

	VOID SetHeaderSortDown(int iItem)
	{
		SetHeaderSort(iItem, TRUE);
	}

	int  GetCount()
	{
		if (m_Hwnd)
			m_Count = Header_GetItemCount((HWND)m_Hwnd);
		return m_Count;
	}

	int  Reset()
	{
		int Count = GetCount();

		for(int i = Count-1; i >= 0; i--)
		{
			DeleteItem(i);
		}

		return Count;
	}

	//Check Box
	VOID SetCheckboxStyle(int iItem = 0)
	{
		AddStyle(HDS_CHECKBOXES);

		int fmt = GetFormat(iItem);
		fmt |= HDF_CHECKBOX;
		SetFormat(iItem, fmt);
	}

	BOOL IsCheckState(int iItem)
	{
		int Fmt = GetFormat(iItem);

		return !!(Fmt&HDF_CHECKED);
	}

	void SetOwnerDraw(BOOL Set = TRUE)
	{
		int Count = GetCount();
		for (int i = 0; i < Count; i++)
		{
			int Fmt = GetFormat(i);
			if(Set == TRUE)
				Fmt |= HDF_OWNERDRAW;
			else
				Fmt &= ~HDF_OWNERDRAW;

			SetFormat(i, Fmt);

			int Fmt1 = GetFormat(i);
			ASSERT(Fmt == Fmt1);
		}

	}

	void ResetOwnerDraw()
	{
		SetOwnerDraw(FALSE);

	}

public:
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMHDR lphdr = (LPNMHDR)lParam;
		LPNMHEADER lpnmhdr = (LPNMHEADER)lParam;
		PCHAR Str = C32DbgGetHeaderNotifyString(lphdr->code);
		//C32DbgOutHeaderNotify(lphdr->code);
		ZxDebug((__FUNCTION__"():: %s (%d)\n",Str, lphdr->code));
		switch(lphdr->code)
		{
			case HDN_ITEMSTATEICONCLICK:
				Handle= OnNotifyItemStateIconClick(wParam, lParam, lResult);
				break;
			case HDN_BEGINTRACK:
				Handle= OnNotifyBeginTrack(lpnmhdr, lResult);
				break;
			case HDN_ENDTRACK:
				Handle= OnNotifyEndTrack(lpnmhdr, lResult);
				break;
		}

		return Handle;
	}

	virtual BOOL OnNotifyItemStateIconClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult);

	//Returns FALSE to allow tracking of the divider, or TRUE to prevent tracking
	virtual BOOL OnNotifyBeginTrack(LPNMHEADER lpnmhdr, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = FALSE;
		if (m_OnNotifyBeginTrack)
		{
			Handle = m_OnNotifyBeginTrack(lpnmhdr, lResult, this);
		}
			
		return Handle;

	}
	
	//Returns FALSE to allow tracking of the divider, or TRUE to prevent tracking
	virtual BOOL OnNotifyEndTrack(LPNMHEADER lpnmhdr, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = FALSE;
		if (m_OnNotifyEndTrack)
		{
			Handle = m_OnNotifyEndTrack(lpnmhdr, lResult, this);
		}

		return Handle;

	}

	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = TRUE;
		int xCursor = GET_X_LPARAM(lParam);
		int yCursor = GET_Y_LPARAM(lParam);
		m_Menu.Display(m_Menu.m_ResourceId, 0, xCursor, yCursor, m_Menu.m_Parent);
		return Handle;
	}

	BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;

		lResult = 0;
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;

		
		return Handle;
	}

	BOOL IsHaveMenu()
	{
		return (m_Menu.m_hMenu != NULL && m_Menu.m_Sub != NULL);
	}


public:
	VOID Init()
	{
		m_List = NULL;
		m_Count = 0;
	}
public:
	int m_Count; //Item ����
public:
	C32ImageList m_ImageList;
	C32ListView* m_List; //Header ������List
	C32Menu  m_Menu;
};

typedef BOOL  (CALLBACK* C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_DBCLICK)(int iItem, int iSubItem, LPNMITEMACTIVATE  lpnmlv,LRESULT& lResult, C32ListView* This);
typedef BOOL  (CALLBACK* C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_CHANGED)(int iItem, int iSubItem, LPNMLISTVIEW lpnmlv,LRESULT& lResult, C32ListView* This);
typedef BOOL  (CALLBACK* C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_GET_DISP_INFO)(int iItem, int iSubItem, NMLVDISPINFO* lpnmdi,LRESULT& lResult, C32ListView* This);
typedef BOOL  (CALLBACK* C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_NM_CUSTOMDRAW)(LPNMLVCUSTOMDRAW lpnmcd,LRESULT& lResult, C32ListView* This);
typedef BOOL  (CALLBACK* C32_EVENT_CALLBACK_LIST_VIEW_GET_INFO_TIP)(LPNMLVGETINFOTIP lpdis,LRESULT& lResult, C32ListView* This);


class C32ListViewEventCallback
{

public:
	C32ListViewEventCallback()
	{
		Init();
	}
	~C32ListViewEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnNotifyDBClick = NULL;
		m_OnNotifyItemChanging = NULL;
		m_OnNotifyItemChanged = NULL;
		m_OnNotifyGetDispInfo = NULL;
		m_OnNotifyCustomDraw = NULL;
		m_OnContextMenuHeader = NULL;
		m_OnGetInfoTip = NULL;
	}

	VOID SetEventItemChanged(C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_CHANGED Callback)
	{
		m_OnNotifyItemChanged = Callback;
	}

	VOID SetEventItemChanging(C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_CHANGED Callback)
	{
		m_OnNotifyItemChanging = Callback;
	}
	
	VOID SetEventGetDispInfo(C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_GET_DISP_INFO Callback)
	{
		m_OnNotifyGetDispInfo = Callback;
	}
	
	VOID SetEventCustomDraw(C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_NM_CUSTOMDRAW Callback)
	{
		m_OnNotifyCustomDraw = Callback;
	}

	VOID SetEventContextMenuHeader(C32_EVENT_CALLBACK_CONTEXTMENU Callback)
	{
		m_OnContextMenuHeader = Callback;
	}

	VOID SetEventDBClick(C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_DBCLICK Callback)
	{
		m_OnNotifyDBClick = Callback;
	}

	VOID SetEventGetInfoTip(C32_EVENT_CALLBACK_LIST_VIEW_GET_INFO_TIP Callback)
	{
		m_OnGetInfoTip = Callback;
	}

	//List View Event Callback
	C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_DBCLICK m_OnNotifyDBClick;
	C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_CHANGED m_OnNotifyItemChanged;
	C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_CHANGED m_OnNotifyItemChanging;

	C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_GET_DISP_INFO m_OnNotifyGetDispInfo; //ListView_InsertItem Callback
	C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_NM_CUSTOMDRAW m_OnNotifyCustomDraw;

	C32_EVENT_CALLBACK_CONTEXTMENU					  m_OnContextMenuHeader;

	C32_EVENT_CALLBACK_LIST_VIEW_GET_INFO_TIP		  m_OnGetInfoTip;

};
//https://www.codeproject.com/articles/2890/using-listview-control-under-win32-api
//https://www.codeproject.com/articles/28787/clistctrl-which-can-show-and-hide-columns
class C32ListView : public C32Window, public C32ListViewEventCallback
{
public:
#define LV_MASK_NO_BIT -1
	static HINSTANCE  hInstance;
	static LRESULT CALLBACK ListSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		LRESULT lResult = 0;
		C32ListView* This = (C32ListView*)dwRefData;
		char* sMsg = C32DbgGetWindowMsgString(uMsg);
		ZxDebugEx((__FUNCTION__"()::sMsg: %s :hwnd: %p :C32: %p\n", sMsg, hWnd, This));

		switch(uMsg)
		{
			case WM_COMMAND:
				This->OnCommand(wParam, lParam, lResult);
				break;
				
		}
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

public:
	C32ListView(){
		m_Header.m_PosVisible = FALSE;
		m_CyItem = 0;
		m_VkDown = 0;
		m_iLastSel = -1;
	}
	~C32ListView(){}	
	
public:
	HWND Create( DWORD dwExStyle, DWORD dwStyle, 
		int X, int Y, int Width, int Height,HWND Parent, LPCWSTR Title = NULL)
	{
		
		//m_Rect.left = X, m_Rect.top = Y, m_Rect.right = X + Width, m_Rect.bottom = Y + Height;
		m_Parent = Parent;
		Title = Title ? Title :  L"C32ListView";
		HWND  List = CreateWindowEx(dwExStyle, WC_LISTVIEW, Title,dwStyle,
			X, Y, Width, Height, Parent,(HMENU)++C32ControlId, C32ListView::hInstance, (LPVOID)this);
		
		ZxDebugEx((__FUNCTION__"()::ListView:  %p Parent: %p Title: %ws {%d, %d, %d, %d} ErrorCode : %d\n",
			 List, Parent,Title, X, Y, (X + Width), (Y + Height),GetLastError()));
		m_Hwnd = List;
		Attach(List);
		return m_Hwnd;
	}
	  
public:
	operator HWND ()
	{
		return m_Hwnd;
	}
	
	VOID Attach(HWND Hwnd)
	{
		C32Window::Attach(Hwnd);
		SetListHeader();
	}

	HWND GetWindow()
	{
		return m_Hwnd;
	}

	BOOL SetExtendedStyle(DWORD dwExStyle)
	{
		DWORD ExStyle1 = GetExtendedStyle();
		DWORD ExStyle = ListView_SetExtendedListViewStyle(m_Hwnd, dwExStyle);
		DWORD ExStyle2 = GetExtendedStyle();

		if ((ExStyle2& dwExStyle) == dwExStyle)
		{
			return TRUE;
		}
		
		return FALSE;
	}

	VOID AddExtendedStyle(DWORD dwExStyle)
	{
		DWORD Ex = ListView_GetExtendedListViewStyle(m_Hwnd);
		Ex |= dwExStyle;
		ListView_SetExtendedListViewStyle(m_Hwnd, Ex);
	}

	DWORD GetExtendedStyle()
	{
		DWORD dwExStyle = ListView_GetExtendedListViewStyle(m_Hwnd);
		return dwExStyle;
	}

	VOID SetCheckBoxStyle()
	{
		AddExtendedStyle(LVS_EX_CHECKBOXES);
	}
	/*
		�˺���Ҫ�� �в������֮�����
	*/
	VOID SetHeaderCheckBox()
	{
		m_Header.SetCheckboxStyle(0);
	}

	VOID SetExplorerTheme()
	{
		SetWindowTheme(m_Hwnd, L"Explorer", NULL);
	}

	VOID SetSubclass()
	{
		SetWindowSubclass(m_Hwnd, C32ListView::ListSubclassProc, (UINT_PTR)this, (DWORD_PTR)this);
	}

	BOOL RemovSubClass()
	{
		RemoveWindowSubclass(m_Hwnd, C32ListView::ListSubclassProc, (ULONG_PTR)this);
	}

	HWND SetListHeader()
	{
		HWND Header = ListView_GetHeader(m_Hwnd);

		m_Header.SetHeader(Header, this);

		return Header;
	}

	VOID SetMenuId(int ResourceId)
	{
		m_Menu.SetResourceId(ResourceId);
	}

	VOID SetImageList()
	{
		ListView_SetImageList(m_Hwnd, m_ImageListNormal, LVSIL_NORMAL);
		ListView_SetImageList(m_Hwnd, m_ImageListSmall, LVSIL_SMALL);
		ListView_SetImageList(m_Hwnd, m_ImageListStatus, LVSIL_STATE);
		
		ListView_SetGroupHeaderImageList(m_Hwnd, m_ImageListGroup);
	}

	HIMAGELIST GetImageList(int iImageList)
	{
		return ListView_GetImageList(m_Hwnd, iImageList);
	}

	VOID SetImageListNormal()
	{
		ListView_SetImageList(m_Hwnd, m_ImageListNormal, LVSIL_NORMAL);
	}

	VOID SetImageListSmall()
	{
		ListView_SetImageList(m_Hwnd, m_ImageListSmall, LVSIL_SMALL);
	}
	
	VOID SetImageListState()
	{
		ListView_SetImageList(m_Hwnd, m_ImageListStatus, LVSIL_STATE);
	}

	BOOL SetBkColor(COLORREF clrBk = CLR_DEFAULT)
	{
		return (BOOL)ListView_SetBkColor(m_Hwnd, clrBk);
	}

	BOOL SetTextBkColor(COLORREF clrBk = CLR_DEFAULT)
	{
		return (BOOL)ListView_SetTextBkColor(m_Hwnd, clrBk);
	}

	BOOL SetTextColor(COLORREF clrBk = CLR_DEFAULT)
	{
		return (BOOL)ListView_SetTextColor(m_Hwnd, clrBk);
	}

	int InsertColumn(int iCol, int iSubItem, LPWSTR Text,int Format, int Cx, int iImage = -1, int CxMin = 0);

	int InsertColumnCenter(int iCol, int iSubItem, LPWSTR Text, int Cx)
	{
		return InsertColumn(iCol, iSubItem, Text, LVCFMT_CENTER, Cx, -1, Cx);
	}

	int InsertColumn(int iCol, int iSubItem, LPCWSTR Text, int Cx)
	{
		return InsertColumn(iCol, iSubItem, (LPWSTR)Text, LVCFMT_LEFT, Cx, -1, Cx);
	}

	BOOL GetColumnWidth(int iCol)
	{
		return ListView_GetColumnWidth(m_Hwnd,iCol);
	}

	int  GetColumnCount()
	{
		return m_Header.GetCount();
	}

	int  GetSelectedColumn()
	{
		return ListView_GetSelectedColumn(m_Hwnd);
	}

	int  GetStringWidth(LPCWSTR String)
	{
		return ListView_GetStringWidth(m_Hwnd, String);
	}

	BOOL  SetColumnWidth(int iCol, int Width)
	{
		return ListView_SetColumnWidth(m_Hwnd, iCol, Width);
	}
	
	C32String GetColumnText(int iCol)
	{
		C32String String;
		BOOL Ret;
		String.AssignStringW(260);
		LVCOLUMN Lv = {};
		Lv.mask = LVCF_TEXT;
		Lv.pszText = (LPWSTR)String;
		Lv.cchTextMax = 260;
		
		Ret = ListView_GetColumn(m_Hwnd, iCol, &Lv);
		if (Ret == FALSE)
		{
			String.FreeBuffer();
		}
		String.SetCount();
		return String;
	}

	BOOL  GetColumnOrderArray(int * iArray)
	{
		BOOL Ret = FALSE;
		int Count = GetColumnCount();
		Ret = ListView_GetColumnOrderArray(m_Hwnd, Count, iArray);
		
		return Ret;
	}

	BOOL  GetColumnOrderWidthArray(int * iOrderArray, int iOrderArrayCount, int* iOrderWidthArray, int iOrderWidthCount)
	{
		BOOL Ret = FALSE;
		int Count = GetColumnCount();
		if (Count > iOrderArrayCount || Count > iOrderWidthCount)
			return FALSE;
		Ret = ListView_GetColumnOrderArray(m_Hwnd, Count, iOrderArray);
		if (Ret == FALSE)
			return FALSE;
		for (int i = 0; i < Count; i++)
		{
			iOrderWidthArray[i] = GetColumnWidth(iOrderArray[i]);
		}

		return Ret;
	}

	BOOL  SetColumnOrderArray(int * iArray)
	{
		BOOL Ret = FALSE;
		int Count = GetColumnCount();
		Ret = ListView_SetColumnOrderArray(m_Hwnd, Count, iArray);

		return Ret;
	}

	BOOL DeleteColumn(int iCol)
	{
		return ListView_DeleteColumn(m_Hwnd, iCol);
	}

	VOID DeleteAllColumn()
	{
		DWORD Count = GetColumnCount();
		for(int i = Count; i >= 0; i--)
		{
			DeleteColumn(i);
		}
	}

	/*
		����
			���� LVS_OWNERDATA style���ĸ�����
			�����ô˺���������List View ��������Ͳ���ÿ�������һ��Insert������ģ�
		ʹ�ó�����
			��������̫���ʱ��ÿһ�����һ��InsertЧ��̫�ͣ�ֱ�����ø����Ϳ����ˡ�
	*/
	VOID SetItemCountEx(int Count, DWORD dwFlags = LVSICF_NOINVALIDATEALL)
	{
		ListView_SetItemCountEx(m_Hwnd, Count, dwFlags);
	}

	VOID SetItemCount(int Count)
	{
		ListView_SetItemCount(m_Hwnd, Count);
	}
	 
	int InsertItem(int iItem, LPCWSTR Text,  int iImage, int iGroupId, LPARAM lParam);

	int InsertItem(int iItem, LPCWSTR Text, int iImage,  LPARAM lParam = 0);

	int InsertItem(int iItem, LPCWSTR Text, LPARAM lParam = 0);

	int InsertItemCheckBox(int iItem, LPWSTR Text, BOOL bCheck = TRUE, int iImage = -1,  LPARAM lParam = 0)
	{
		int Index;

		Index  = InsertItem(iItem, Text, iImage,lParam);
		if (Index != -1)
		{
			if (bCheck == TRUE)
				SetItemCheckState(Index);
		}

		return Index;
	}

	BOOL InsertSubItem(int iItem, int iSubItem, LPWSTR Text, int Image = -1);

	BOOL InsertSubItem(int iItem, int iSubItem, LPCWSTR Text, int Image = -1);

	int InsertItemAsyn(int iItem, LPCWSTR Text, int iImage, LPARAM lParam);
	
	int InsertSubItemAsyn(int iItem, int iSubItem, LPWSTR Text, int Image = -1, LPARAM lParam = NULL);

	int InsertSubItemAsyn(int iItem, int iSubItem, LPWSTR Text, LPARAM lParam)
	{
		return InsertSubItemAsyn(iItem, iSubItem,(LPWSTR)Text, -1, lParam);
	}

	int GetItemCount()
	{
		return ListView_GetItemCount(m_Hwnd);
	}

	C32String GetItemText(int iIndex, int iSubItem)
	{
		C32String Text;
		Text.AssignStringW(260);
		/*LVITEM lvi = {};
		lvi.mask = LVIF_TEXT;
		lvi.pszText = Text;
		lvi.cchTextMax = Text.GetTotalCount();*/

		ListView_GetItemText(m_Hwnd, iIndex,iSubItem,Text, Text.GetTotalCount());
		Text.SetCount();

		return Text;
	}

	/*
	����
		��StyleΪ LVS_OWNERDATA���˺�����Ч 
	*/
	BOOL  GetItemLParam(int iIndex, int iSubItem, LPARAM* lParam)
	{
		LVITEM Lv= {};
		Lv.mask = LVIF_PARAM;
		Lv.iItem = iIndex;
	
		if( ListView_GetItem(m_Hwnd, &Lv) == FALSE)
			return FALSE;
		*lParam = Lv.lParam;
		return TRUE;
	}

	BOOL GetItemRect(int iIndex, DWORD Portion, RECT* Rect)
	{
		return ListView_GetItemRect(m_Hwnd, iIndex, Rect, Portion);
	}

	BOOL GetItemIndexRect(int iIndex, int iSubItem, int Portion,RECT* Rect)
	{
		LVITEMINDEX lve = {};
		lve.iItem = iIndex;
		lve.iGroup = 0;
		return ListView_GetItemIndexRect(m_Hwnd, &lve, iSubItem, Portion, Rect);
	}
	
	BOOL GetItemPosition(int iIdenx, PPOINT Point)
	{
		return ListView_GetItemPosition(m_Hwnd, iIdenx, Point);
	}

	VOID SetItemPosition32(int iIndex, int x0, int y0)
	{
		 ListView_SetItemPosition32(m_Hwnd, iIndex, x0, y0);
	}

	BOOL GetItemCheckBoxSize(PSIZE lpSize)
	{
		SIZE Size ={};
		HIMAGELIST hImageList = GetImageList(LVSIL_STATE);
		if (hImageList)
		{
			C32ImageList IL(hImageList);
			if (IL.GetIconSize(&Size))
			{
				*lpSize = Size;
				return TRUE;
			}
		}
		
		return FALSE;
	}

	VOID SetItemState(int iIndex, UINT State, UINT Mask)
	{
		ListView_SetItemState(m_Hwnd, iIndex, State, Mask);
	}

	VOID SelectItem(int iIndex, BOOL Select = TRUE)
	{
		UINT Mask = LVIS_SELECTED;
		UINT State = LVIS_SELECTED;
		if (Select == FALSE)
		{
			State = 0;
		}
		
		SetItemState(iIndex, State, Mask);

	}

	UINT GetSelectedCount()
	{
		return ListView_GetSelectedCount(m_Hwnd);
	}

	int GetCountPerPage()
	{
		return ListView_GetCountPerPage(m_Hwnd);
	}

	int GetTopIndex()
	{
		return ListView_GetTopIndex(m_Hwnd);
	}
	
	BOOL EnableVisible(int iIndex, BOOL PartialOK)
	{
		return ListView_EnsureVisible(m_Hwnd, iIndex, PartialOK);
	}
	
	BOOL SearchString(LPCWSTR String)
	{
		return ListView_GetISearchString(m_Hwnd, String);
	}

	int FindString(int iStart, LPCWSTR String)
	{
		int iFind = 0;
		LVFINDINFO Lvi = {};
		Lvi.flags = LVFI_PARTIAL|LVFI_WRAP;
		Lvi.psz = String;
		iFind = ListView_FindItem(m_Hwnd, iStart, &Lvi);
		return iFind;
	}

	BOOL RedrawItems(int iFirst, int iLast)
	{
	   BOOL bRedraw;
	   bRedraw = ListView_RedrawItems(m_Hwnd, iFirst, iLast);
	   assert(bRedraw == TRUE);
	   UpdateWindow(m_Hwnd);

	   return bRedraw;
	}
	
	BOOL RedrawVisibleItems()
	{
		int iFirst = GetTopIndex();
		int Page = GetCountPerPage();

		return RedrawItems(iFirst, iFirst+Page);
	}

	int  HitTest(POINT Point, UINT Flags)
	{
		int iIndex = 0;
		LVHITTESTINFO lhti={};
		lhti.pt = Point;
		lhti.flags = Flags;
		lhti.iItem = 1;
		lhti.iSubItem = 0;
		iIndex = ListView_HitTest(m_Hwnd, &lhti);
		return iIndex; 
	}

	int  SubItemHitTest(POINT Point, UINT Flags, __inout int* piSubItem = NULL)
	{
		int iIndex = 0;
		LVHITTESTINFO lhti={};
		lhti.pt = Point;
		lhti.flags = Flags;
		iIndex = ListView_SubItemHitTest(m_Hwnd, &lhti);
		if (iIndex != -1)
		{
			if (piSubItem)
				*piSubItem = lhti.iSubItem;
		}
		return iIndex; 
	}

	// ֧������ק������Ż�ı�
	int  GetSubItemOrderIndex(int iSubItem)
	{

		return -1;
	}


public:
	//LVS_ICON style
	VOID SetIconSpacing(int Cx, int Cy)
	{
		ListView_SetIconSpacing(m_Hwnd, Cx, Cy);
	}

	HWND GetToolTips()
	{
		HWND ToolTip;

		ToolTip = ListView_GetToolTips(m_Hwnd);
		ZxDebugEx((__FUNCTION__"():: ToolTip: %p \n", ToolTip));

		return ToolTip;
	}

	HWND SetToolTips(HWND ToolTip)
	{
		HWND LastTip;

		LastTip = ListView_SetToolTips(m_Hwnd, ToolTip);
		ZxDebugEx((__FUNCTION__"():: LastTipHwnd: %p \n", LastTip));

		return LastTip;
	}
	//��
	VOID EnableGroupView(BOOL Enable = TRUE)
	{
		ListView_EnableGroupView(m_Hwnd, Enable);
	}

	VOID InsertGroup(int Index, LPCWSTR Header, int iTitleImage, BOOL IsCollapsed = FALSE)
	{
		LVGROUP lvg = {};
		lvg.cbSize = sizeof(LVGROUP);
		lvg.mask =  LVGF_HEADER | LVGF_GROUPID  | LVGF_TITLEIMAGE| LVGF_STATE | LVGF_ALIGN;
		lvg.pszHeader = (LPWSTR)Header;
		lvg.cchHeader = (int)wcslen(Header)+1;
		lvg.iExtendedImage = 0;
		lvg.iTitleImage = iTitleImage;
		lvg.iGroupId = Index;
		lvg.state = LVGS_COLLAPSIBLE | (IsCollapsed ? LVGS_COLLAPSED : 0);
		lvg.uAlign = LVGA_FOOTER_LEFT;

		ListView_InsertGroup(m_Hwnd, -1, &lvg);
	}
	
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		C32ListView* List = (C32ListView*)lParamSort;
		ZxDebug(("iItem1 : %d iItem2: %d  %x\n", lParam1, lParam2,(LOWORD(List->m_Parameter)& HDF_SORTDOWN)));
		WCHAR T1[260]={}, T2[260]={};
		ListView_GetItemText(List->m_Hwnd,  lParam1, HIWORD(List->m_Parameter), T1, 260);
		ListView_GetItemText(List->m_Hwnd,  lParam2, HIWORD(List->m_Parameter), T2, 260);

		if (LOWORD(List->m_Parameter)&HDF_SORTDOWN)
		{
			return wcscmp(T1, T2);
		}else
		{
			return wcscmp(T2, T1);			
		}
	}

	virtual LPWSTR GetDispInfoText(int iItem, int iSubItem)
	{
		return L"C32ListView";
	}

	virtual int GetDispInfoImage(int iItem, int iSubItem)
	{
		return 0;
	}

	BOOL OnNotifyGetDispInfo(NMLVDISPINFO* Disp)
	{
		BOOL Handle = FALSE;
		LRESULT lResult = 0;
		if (m_OnNotifyGetDispInfo)
		{
			Handle = m_OnNotifyGetDispInfo(Disp->item.iItem, Disp->item.iSubItem, Disp, lResult, this);
		}else
		{
			LVITEM& lvi = Disp->item;
			if (lvi.mask & LVIF_TEXT)
			{
				lvi.pszText = GetDispInfoText(lvi.iItem, lvi.iSubItem);
			}
			if (lvi.mask & LVIF_IMAGE)
			{
				lvi.iImage = GetDispInfoImage(lvi.iItem, lvi.iSubItem);
			}

		}

		

		return TRUE;
	} 


public:
/*
	ֻ��ʾһ���Ҽ��͵������Ҫʵ��m_OnContextMenu���д���
*/
	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		int xCursor = GET_X_LPARAM(lParam);
		int yCursor = GET_Y_LPARAM(lParam);
		POINT Point = {};
		ScreenToClient32(xCursor, yCursor, &Point);
		
		if (m_Header.IsHaveMenu())
		{
			int ColmunHeight;
			POINT Pt = {};
			
			SIZE Size = m_Header.GetClientSize();
			ColmunHeight = Size.cy;
			if (ColmunHeight)
			{
				if (0 <= Point.y && Point.y <= ColmunHeight)
				{
					if (m_OnContextMenuHeader)
						Handle = m_OnContextMenuHeader(*this, xCursor, yCursor, lResult,this);

					if(Handle == FALSE)
						m_Header.m_Menu.Display(xCursor, yCursor);
					return TRUE;
				}
			}
		}
		if (m_OnContextMenu)
			Handle = m_OnContextMenu(*this, xCursor, yCursor, lResult,this);
		if (Handle == FALSE)
			m_Menu.Display(xCursor, yCursor, m_Hwnd);
		
		return TRUE;
	}

	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND HwndCtrl;
		DWORD MenuId;
		HwndCtrl= (HWND)lParam;
		MenuId = LOWORD(wParam);
		C32String String ;
		if (m_Header.IsHaveMenu() && m_Header.m_Menu.IsSubItem(MenuId))
		{
			String = m_Header.m_Menu.GetSubItemString(MenuId);
			m_Header.m_Menu.SelectSubMenuItem(MenuId);
		}else
		{
			m_Menu.SelectSubMenuItem(MenuId);			
			String = this->m_Menu.GetSubItemString(MenuId);
		}

		ZxDebugEx((__FUNCTION__"():: Click: %ws Hwnd: %p %d(0x%04x) \n", (LPWSTR)String, HwndCtrl, MenuId, MenuId));
		if (m_OnCommandMenu)
			Handle = m_OnCommandMenu(C32CommandMenuId(wParam), lResult, this);

		return Handle;	
	}

	virtual BOOL CALLBACK OnMeasureItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		if (m_CyItem == 0)
			return FALSE;
		ZxDebugEx((__FUNCTION__"():: \n"));
		LPMEASUREITEMSTRUCT  lpmis = (LPMEASUREITEMSTRUCT)lParam;
		lpmis->itemHeight = m_CyItem;
		Handle = TRUE;
		lResult = TRUE;
		return Handle;
	}

	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		assert(lpdis->CtlType == ODT_LISTVIEW);

		ZxDebug((__FUNCTION__"()::111itemId %d hwndItem: %p , itemAction:%x, itemState:%d {%d, %d, %d, %d}\n", lpdis->itemID, lpdis->hwndItem,lpdis->itemAction,lpdis->itemState,lpdis->rcItem.left, lpdis->rcItem.top, lpdis->rcItem.right, lpdis->rcItem.bottom));
		if (m_OnDrawItem)
		{
			Handle = m_OnDrawItem(lpdis, lResult, this);
		}
		
		return Handle;
	}

	virtual BOOL CALLBACK OnNotifyDBClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) lParam;
		
		if(m_OnNotifyDBClick)
		{
			ZxDebugEx((__FUNCTION__"():: iItem : %d iSubItem: %d uNewState : 0x%08x uOldState: 0x%08x uChanged: 0x%08x ptAction:{%d, %d} lParam : %p uKeyFlags: 0x%08x \n",
				lpnmitem->iItem, lpnmitem->iSubItem, lpnmitem->uNewState, lpnmitem->uOldState, lpnmitem->uChanged, lpnmitem->ptAction.x, lpnmitem->ptAction.y, lpnmitem->lParam, lpnmitem->uKeyFlags));

			Handle = m_OnNotifyDBClick(lpnmitem->iItem, lpnmitem->iSubItem, lpnmitem, lResult, this);
		}
		return Handle;	
	}
	
	virtual BOOL CALLBACK OnNotifyClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) lParam;

		ZxDebugEx((__FUNCTION__"():: iItem : %d iSubItem: %d uNewState : 0x%08x uOldState: 0x%08x uChanged: 0x%08x ptAction:{%d, %d} lParam : %p uKeyFlags: 0x%08x \n",
				lpnmitem->iItem, lpnmitem->iSubItem, lpnmitem->uNewState, lpnmitem->uOldState, lpnmitem->uChanged, lpnmitem->ptAction.x, lpnmitem->ptAction.y, lpnmitem->lParam, lpnmitem->uKeyFlags));

		
		return Handle;	
	}


	//To accept the notification message, return zero. To quit the bounding box selection, return nonzero
	virtual BOOL CALLBACK OnNotifyMarqueenBegin(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 0;
		
		LPNMLISTVIEW  pnmv = (LPNMLISTVIEW) lParam;
		
		ZxDebugEx((__FUNCTION__"():: iItem : %d iSubItem: %d uNewState : 0x%08x uOldState: 0x%08x uChanged: 0x%08x ptAction:{%d, %d} \n",
				   pnmv->iItem, pnmv->iSubItem, pnmv->uNewState, pnmv->uOldState, pnmv->uChanged, pnmv->ptAction.x, pnmv->ptAction.y));
		
		return Handle;	
	}
	
	virtual BOOL CALLBACK OnNotifyGetInfoTip(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMLVGETINFOTIP lpit = (LPNMLVGETINFOTIP) lParam;

		if(m_OnGetInfoTip)
		{
			ZxDebugEx((__FUNCTION__"():: iItem : %d iSubItem: %d lParam : %p  \n",
				lpit->iItem, lpit->iSubItem, lpit->lParam));

			Handle = m_OnGetInfoTip(lpit, lResult, this);
		}
		return Handle;	
	}

	virtual BOOL CALLBACK OnNotifyColumnClick(LPNMLISTVIEW NMLv)
	{
		int iSubItem = NMLv->iSubItem;

		int fmt = m_Header.GetSort(iSubItem);
		/*
		if (fmt& HDF_SORTDOWN)
		{
			
		}else if(fmt& HDF_SORTUP)
		{

		}else
		{

		}*/
		ZxDebugEx((__FUNCTION__"():: Click : %d  %s\n", iSubItem, (fmt == HDF_SORTDOWN ? "down-arrow" :"up-arrow")));
		
		m_Parameter = MAKELONG(fmt, iSubItem);
		ListView_SortItemsEx(m_Hwnd, CompareFunc, this);

		m_Header.SetHeaderSort(NMLv->iSubItem, (fmt == HDF_SORTDOWN ? FALSE :TRUE));

		return TRUE;
	}

	virtual BOOL CALLBACK OnNotifyCustomDraw(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMLVCUSTOMDRAW lpnmcd = (LPNMLVCUSTOMDRAW)lParam;

		if (m_OnNotifyCustomDraw)
		{
			Handle = m_OnNotifyCustomDraw(lpnmcd, lResult, this);
		}

		return Handle;
	}

	virtual BOOL  CALLBACK OnNotifyItemChanged(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMLISTVIEW lplv = (LPNMLISTVIEW)lParam;
		int iSubItem = lplv->iSubItem;



#if 0
		if (IsCheckBoxStyle())
		{
			if (!(lplv->uOldState&LVIS_SELECTED) && lplv->uNewState&LVIS_SELECTED)
			{
				SetItemCheckState(lplv->iItem);
			}
			if ((lplv->uOldState&LVIS_SELECTED) && !(lplv->uNewState&LVIS_SELECTED))
			{
				ResetItemCheckState(lplv->iItem);
			}

		}

#endif
		C32DbgOutNmListView(lplv);
		ZxDebugEx((__FUNCTION__"():: iItem : %d iSubItem: %d uNewState : 0x%08x uOldState: 0x%08x uChanged: 0x%08x ptAction:{%d, %d} \n",
			lplv->iItem, lplv->iSubItem, lplv->uNewState, lplv->uOldState, lplv->uChanged, lplv->ptAction.x, lplv->ptAction.y));

		//ά������ѡ��
		if (IsMultiSelect())
		{
			HandleSelectItemList(lplv);
		}

		if (m_OnNotifyItemChanged)
		{
			
			Handle = m_OnNotifyItemChanged(lplv->iItem, lplv->iSubItem, lplv, lResult, this);
		}
		
		if (!IsMultiSelect() && C32LvIsSelected(lplv))
		{
			m_iLastSel = lplv->iItem;
		}


		
		return Handle;
	}
				  
	virtual BOOL  CALLBACK OnNotifyItemChanging(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = FALSE;
		LPNMLISTVIEW lplv = (LPNMLISTVIEW)lParam;
		int iSubItem = lplv->iSubItem;
		ZxDebugEx((__FUNCTION__"():: \n"));
		/*lplv->uNewState &= ~LVIS_FOCUSED;
		lplv->uOldState &= ~LVIS_FOCUSED;*/
		//C32DbgOutNmListView(lplv);

		return Handle;
	}
				  
	virtual BOOL  CALLBACK OnNotifyKeyDown(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = FALSE;
		LPNMLVKEYDOWN lpvk = (LPNMLVKEYDOWN)lParam;
		ZxDebug((__FUNCTION__"():: %s(0x%x)\n", GetVirtualKeyString(lpvk->wVKey), lpvk->wVKey));

		m_VkDown = lpvk->wVKey;
		
		return TRUE;
	}
	
	// WM_NOTIFY
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 0;
		LPNMHDR lphdr = (LPNMHDR)lParam;

		int NotifyCode = 0;
		NotifyCode = lphdr->code;
		if (m_Header.GetHwnd() == lphdr->hwndFrom)
		{
			int i = 0;
		}
		LPCSTR Str = C32GetListViewNotifyString(lphdr->code);
		C32String Title = this->GetText();
		//ZxDebugEx((__FUNCTION__"()::%ws Str:%s \n", Title.GetString(), Str));
		switch(NotifyCode)
		{
		case LVN_COLUMNCLICK:
			OnNotifyColumnClick((LPNMLISTVIEW)lphdr);
			break;
		case LVN_GETDISPINFO:
			OnNotifyGetDispInfo((NMLVDISPINFO*)lphdr);
			break;
		case LVN_ITEMCHANGING:
			Handle = OnNotifyItemChanging(wParam, lParam, lResult);
			break;
		case LVN_ITEMCHANGED:
			Handle =OnNotifyItemChanged(wParam, lParam,lResult);
			break;
		case NM_CUSTOMDRAW:
			Handle = OnNotifyCustomDraw(wParam, lParam, lResult);
			break;
		case NM_CLICK:
			Handle = OnNotifyClick(wParam, lParam, lResult);
			break;
		case NM_DBLCLK:
			Handle = OnNotifyDBClick(wParam, lParam, lResult);
		case LVN_MARQUEEBEGIN:
			Handle = OnNotifyMarqueenBegin(wParam, lParam, lResult);
			break;
		case LVN_KEYDOWN:
			Handle = OnNotifyKeyDown(wParam, lParam, lResult);
			break;
		case LVN_GETINFOTIP:
			Handle = OnNotifyGetInfoTip(wParam, lParam, lResult);
			break;

		}
		return Handle;
	};


	BOOL DeleteItem(int iItem)
	{
		return ListView_DeleteItem(m_Hwnd, iItem);
	}

	BOOL DeleteAllItem()
	{
		return ListView_DeleteAllItems(m_Hwnd);
	}

	VOID ResetItem()
	{
		DeleteAllItem();
	}

	VOID Reset()
	{
		DeleteAllItem();
		DeleteAllColumn();
		
	}

	//LVS_EX_CHECKBOXES
	VOID SetItemCheckState(int iItem)
	{
		ListView_SetCheckState((HWND)m_Hwnd, iItem, TRUE);
	}

	VOID ResetItemCheckState(int iItem)
	{
		ListView_SetCheckState((HWND)m_Hwnd, iItem, FALSE);
	}

	BOOL GetItemCheckState(int iItem)
	{
		return ListView_GetCheckState((HWND)m_Hwnd, iItem);
	}

	/*
		��������Item��CheckBox״̬Ϊѡ��

	*/
	VOID SetListCheckState()
	{
		int Count = GetItemCount();

		for(int i = 0; i < Count; i++)
		{
			SetItemCheckState(i);
		}
	}

	VOID ResetListCheckState()
	{
		int Count = GetItemCount();

		for(int i = 0; i < Count; i++)
		{
			ResetItemCheckState(i);
		}
	}

	BOOL  IsCheckBoxStyle()
	{
		DWORD ExStyle = GetExtendedStyle();

		return (ExStyle & LVS_EX_CHECKBOXES ? TRUE :FALSE);
	}
	
	//List View ��CheckBox Ϊѡ��״̬���б�
	int GetListCheckState(CAtlArray<BOOL>& StateList)
	{
		int Count = GetItemCount();
		if (Count == 0)
			return 0;

		for(int i = 0; i < Count; i++)
		{
			BOOL Check = GetItemCheckState(i);
			StateList.Add(Check);
		}

		return Count;
	}

	/*
		five different views
	*/
	BOOL SetView(DWORD iView)
	{
		DWORD iSet = ListView_SetView(m_Hwnd, iView);

		return (iSet == 1 ? TRUE : FALSE);
	}

	DWORD GetView()
	{
		DWORD View = ListView_GetView(m_Hwnd);
		
		return View;
	}

	BOOL IsViewDetail()
	{
		DWORD View = GetView();
		
		return (View == LV_VIEW_DETAILS); 
	}

	//ά������ѡ����
public:
	BOOL IsMultiSelect()
	{
		DWORD Style = GetStyle();
		
		return (BOOL)!(Style & LVS_SINGLESEL);
	}

	BOOL IsSingleSelect()
	{
		DWORD Style = GetStyle();

		return (BOOL)(Style & LVS_SINGLESEL);
	}

	//����ѡ��ά��ѡ�е�Item

	VOID AddFirstItem(int iSelect)
	{
		m_SelList.InsertAt(0, iSelect);
	}

	VOID AddSelectItem(int iSelect)
	{
		
		m_SelList.Add(iSelect);
	}

	int RemoveSelectItem(int iSelect, int iCount = -1)
	{
		int iFind = -1;
		size_t Count = m_SelList.GetCount();
		
		for(size_t i = 0; i < Count; i++)
		{
			if (m_SelList[i] == iSelect)
			{
				iFind = (int)i;
				break;
			}
		}

		if(iFind != -1)
		{
			if(iCount == -1)
				iCount = (int)Count - iFind;
			m_SelList.RemoveAt(iFind, iCount);

		}else
		{
			iCount = -1;
		}
			
		ZxDebug((__FUNCTION__"()::TotalCount : %d iSelect: %d Index : %d  iCount: %d \n", Count, iSelect,iFind, iCount));

		return iFind -1;
	}

	int RemoveSelectAllItem()
	{
		int Count = (int)m_SelList.GetCount();
		m_SelList.RemoveAll();
		ZxDebugEx((__FUNCTION__"()::Count : %d \n",Count));
		return Count;
	}

	//����סShitf����ѡ�ж��������£��ٴε����
	BOOL IsInSelectItem(int iSelect)
	{
		BOOL Is = FALSE;
		size_t Count = m_SelList.GetCount();

		for(size_t i = 0; i < Count; i++)
		{
			if (m_SelList[i] == iSelect)
			{
				Is = TRUE;
				break;
			}
		}
		return Is;
	}

	BOOL IsEndSelectItem(int iSelect)
	{
		BOOL Is = FALSE;
		size_t Count = m_SelList.GetCount();

		for(size_t i = 0; i < Count; i++)
		{
			if (m_SelList[i] == iSelect)
			{
				if (i == Count -1)
					Is = TRUE;

				break;
			}
		}
		return Is;
	}

	BOOL HandleSelectItemList(LPNMLISTVIEW lplv)
	{
		ZxDebug((__FUNCTION__"()::iItem : %d  uNewState : %08x uOldState:%08x  m_VkDown : %s,  m_iLastSel:%d\n", 
							lplv->iItem, lplv->uNewState, lplv->uOldState, GetVirtualKeyString(m_VkDown),  m_iLastSel));

		if(lplv->uChanged == LVIF_STATE 
			&& C32AndValue(lplv->uOldState, LVIS_SELECTED) != C32AndValue(lplv->uNewState, LVIS_SELECTED) 
			)
		{
			if (C32AndValue(lplv->uNewState, LVIS_SELECTED))
			{
				//������һ��ѡ�е���
				//����סshiftʱ��Ҫ�õ�.
				m_iLastSel = lplv->iItem;

				AddFirstItem(lplv->iItem);
			}
			else
			{
				if (m_VkDown == VK_SHIFT)
				{
					int PtItem;
					POINT Pt={};
					GetCursorPos(&Pt);
					ScreenToClient(m_Hwnd, &Pt);
					PtItem = HitTest(Pt, LVHT_ONITEM);
					ZxDebug((__FUNCTION__"():: PtItem: %d \n", PtItem));
					//�˴�������Ż�����Ŀǰ���Ż����߼����е��Ρ�
					if (IsInSelectItem(PtItem))
					{
						//��סShift��iItem��ѡ�е��б���
						//�����ѡ�е����һ�����ᷢ�� �Ϻ���״̬��ѡ�б�����Ϊѡ�е���Ϣ��������
						//	 (lplv->uOldState&LVIS_SELECTED && lplv->uOldState&LVIS_SELECTED == lplv->uNewState&LVIS_SELECTED) 
						if (IsEndSelectItem(PtItem) == TRUE)
						{
						}else
						{
							RemoveSelectItem(m_iLastSel, -1);
						}

					}else
					{
						//��סShift��iItem����ѡ�е��б���
						//�Ƴ���ѡ�к�ʣ���Ԫ��
						//���뱣֤��ѡ�е�ʱ��һ������
						ZxDebugEx((__FUNCTION__"():: ����ѡ��������\n"));
						RemoveSelectItem(m_iLastSel, -1);

					}
				}else if (lplv->iItem == -1)
				{
					RemoveSelectAllItem();
				}else
				{
					
					int Pre = RemoveSelectItem(lplv->iItem, 1);
					if (m_VkDown == VK_CONTROL)
						m_iLastSel = lplv->iItem;
				}

			}
		}else if ( C32AndValue(lplv->uOldState, LVIS_SELECTED)
			&&C32AndValue(lplv->uOldState, LVIS_SELECTED) == C32AndValue(lplv->uNewState, LVIS_SELECTED))
		{
			assert(lplv->iItem != -1);
			if(m_VkDown == VK_SHIFT || m_VkDown == VK_CONTROL)
			{
				int iStart = min(m_iLastSel, lplv->iItem);
				int iLast = max(m_iLastSel, lplv->iItem);
				ZxDebugEx((__FUNCTION__"():: Shift ���� (%d - %d )\n", iStart, iLast));
				//��ֻ��һ����ѡ�е���ʱ���Ѿ���ǰ�洦��
				//��ѡ�е����ǵ�һ������
				if (iStart != iLast)
				{
					RemoveSelectAllItem();
					AddFirstItem(m_iLastSel);
					for (int i = iStart; i <= iLast; i++)
					{
						if(m_iLastSel != i)
							AddSelectItem(i);
					}
				}


			}
		}

		return TRUE;

	}

	int  GetSelect()
	{
		return m_iLastSel;
	}

	BOOL IsSelected()
	{
		return (m_iLastSel != -1);
	}

public:
	VOID SetItemHeight(int ItemHeight)
	{
		m_CyItem = ItemHeight;
	}

	int GetItemHeight()
	{
		return m_CyItem;
	}

public:
	VOID DebugListView()
	{
		int CountPerPage =GetCountPerPage();
		int ItemHeight = GetItemHeight();
		RECT ItemRect = {};
		BOOL bItemRect = GetItemRect(0, LVIR_BOUNDS, &ItemRect);
		ZxDebugEx((__FUNCTION__"():: CountPerPage: %d ItemHeight:%d \n", CountPerPage, ItemHeight));

	}

public:
	

	DWORD m_ExStyle;
	DWORD m_Style;

public:
	C32ImageList m_ImageListStatus;
	C32ImageList m_ImageListNormal;
	C32ImageList m_ImageListSmall;
	C32ImageList m_ImageListGroup;


public:
	C32Header m_Header;
	C32Menu       m_Menu;
	
	//ά��ѡ���б�
	DWORD		  m_VkDown;
	int			  m_iLastSel;

	HWND		  m_Parent;
	int            m_CyItem;
	CAtlArray<int> m_SelList;
public:
	
	LPARAM m_Parameter;

public:
};


class C32StatusBar : public C32Window
{
#define STATUS_PART_MAX_COUNT 20

//public:
//	static LRESULT C32SubClassProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam,
//		UINT_PTR uIdSubclass,DWORD_PTR dwRefData);
//
//public:
//	BOOL SetSubClass(DWORD_PTR dwRefData = 0)
//	{
//		BOOL Ret;
//		Ret = SetWindowSubclass(m_Hwnd, C32StatusBar::C32SubClassProc, (ULONG_PTR)this, dwRefData);
//		ASSERT(Ret == TRUE);
//
//		return Ret;
//	}
//
//	BOOL RemoveSubClass()
//	{
//		BOOL Ret;
//
//		Ret = RemoveWindowSubclass(m_Hwnd, C32StatusBar::C32SubClassProc, (ULONG_PTR)this);
//
//		return Ret;
//	}

public:
	HWND CreateStatus(DWORD ExStyle, DWORD Style, HWND Parent)
	{
		HWND hwnd = CreateWindowEx(ExStyle, STATUSCLASSNAME, L"C32StatusBar", Style,
								   0, 0, 0, 0, Parent, (HMENU)this, C32Hinstance, (LPVOID)this);
		if (hwnd)
			Attach(hwnd);
		ZxDebugEx((__FUNCTION__"():: m_Hwnd: %p ErrorCode: %d \n", m_Hwnd, GetLastError()));
		return hwnd;
	}

	VOID DestroyStatus()
	{
		
		DestroyWindow(m_Hwnd);
			
	}

	BOOL SetParts(int nParts, int* pWidths)
	{ 
		return (BOOL) ::SendMessage(m_Hwnd, SB_SETPARTS, nParts, (LPARAM)pWidths);
	}
	
	int GetParts(int nParts, int* pParts) const
	{ 
		return (int) ::SendMessage(m_Hwnd, SB_GETPARTS, nParts, (LPARAM)pParts);
	}
	
	BOOL GetBorders(int* pBorders) const
	{ 
		return (BOOL) ::SendMessage(m_Hwnd, SB_GETBORDERS, 0, (LPARAM)pBorders);
	}
	
	void SetMinHeight(int nMin)
	{ 
		::SendMessage(m_Hwnd, SB_SETMINHEIGHT, nMin, 0L);
	}

	BOOL SetSimple(BOOL bSimple)
	{ 
		return (BOOL) ::SendMessage(m_Hwnd, SB_SIMPLE, bSimple, 0L);
	}
	
	BOOL GetRect(int nPane, LPRECT lpRect) const
	{ 
		return (BOOL) ::SendMessage(m_Hwnd, SB_GETRECT, nPane, (LPARAM)lpRect);
	}

	BOOL SetText(LPCTSTR lpszText, int nPane, int nType = 0)
	{ 
		ASSERT(nPane < 256); 
		BOOL Ret = (BOOL) ::SendMessage(m_Hwnd, SB_SETTEXT, (nPane|nType), (LPARAM)lpszText); 
		if (Ret == TRUE)
		{
			m_ODText[nPane] = lpszText;
		}

		return Ret;
	}

	BOOL SetTextOD(LPCTSTR lpszText, int nPane)
	{ 
		ASSERT(nPane < 256); 
		return SetText(lpszText, nPane, SBT_OWNERDRAW);
	}
	
	int GetText(LPTSTR lpszText, int nPane, int* pType) const
	{
		ASSERT(nPane < 256);
		LRESULT dw = ::SendMessage(m_Hwnd, SB_GETTEXT, (WPARAM)nPane,
			(LPARAM)lpszText);
		if (pType != NULL)
			*pType = HIWORD(dw);
		return LOWORD(dw);
	}

	CString GetText(int nPane, int* pType) const
	{
		ASSERT(nPane < 256);
		LRESULT lLength = ::SendMessage(m_Hwnd, SB_GETTEXTLENGTH,
			(WPARAM)nPane, 0L);
		int nLength = LOWORD(lLength);
		CString str;
		LRESULT dw = ::SendMessage(m_Hwnd, SB_GETTEXT, (WPARAM)nPane,
			(LPARAM)str.GetBufferSetLength(nLength+1));
		str.ReleaseBuffer();
		if (pType != NULL)
			*pType = HIWORD(dw);
		return str;
	}

	int GetTextLength(int nPane, int* pType) const
	{
		ASSERT(nPane < 256);
		LRESULT dw = ::SendMessage(m_Hwnd, SB_GETTEXTLENGTH, (WPARAM)nPane, 0L);
		if (pType != NULL)
			*pType = HIWORD(dw);
		return LOWORD(dw);
	}

	CString GetTextOD(int nPane)
	{
		return m_ODText[nPane];
	}

	CString GetTipText(int nPane) const
	{

		ASSERT(nPane < 256);
		TCHAR buf[256];
		::SendMessage(m_Hwnd, SB_GETTIPTEXT, MAKEWPARAM(nPane, 256), (LPARAM)buf);
		return CString(buf);
	}

	BOOL SetIcon(int iPart, HICON hIcon)
	{
		return (BOOL)SendMessage(m_Hwnd, SB_SETICON, (WPARAM)iPart, (LPARAM)hIcon);
	}

	COLORREF SetBkColor(COLORREF clrBk = CLR_DEFAULT)
	{
		return (COLORREF)SendMessage(m_Hwnd, SB_SETBKCOLOR, 0, (LPARAM)(COLORREF) clrBk);
	}

	BOOL GetBorders(int& nHorz, int& nVert, int& nSpacing) const
	{
		int borders[3];
		BOOL bResult = (BOOL)::SendMessage(m_Hwnd, SB_GETBORDERS, 0, (LPARAM)borders);
		if (bResult)
		{
			nHorz = borders[0];
			nVert = borders[1];
			nSpacing = borders[2];
		}
		return bResult;
	}

	/*
		����OwnerDraw
	*/
	VOID SetOwnerDraw()
	{
		int Part= 20;	
		
		for(int i = 0; i < 20; i++)
		{
			int Index = i;
			CString String = m_ODText[Index];
			SetTextOD(String, Index);
		}
	}

	VOID ResetOwnerDraw()
	{
		int Part= 20;	

		for(int i = 0; i < 20; i++)
		{
			int Index = i;
			CString String = m_ODText[Index];
			SetText(String, Index);
		}
	}


public:
	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	

public:
	int  m_Count; //�ָ�����
	int  m_Part[STATUS_PART_MAX_COUNT];

	CString  m_ODText[STATUS_PART_MAX_COUNT];
};

typedef BOOL  (CALLBACK* C32_EVENT_CALLBACK_TAB_LIST_NOTIFY_SELECTED)(int iItem, LPNMLISTVIEW lpnmlv,LRESULT& lResult, C32TabList* This);


class C32TabListEventCallback
{

public:
	C32TabListEventCallback()
	{
		Init();
	}
	
	~C32TabListEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnSelected = NULL;
	}

	VOID SetEventItemSelected(C32_EVENT_CALLBACK_TAB_LIST_NOTIFY_SELECTED Callback)
	{
		m_OnSelected = Callback;
	}

	C32_EVENT_CALLBACK_TAB_LIST_NOTIFY_SELECTED					  m_OnSelected;

};

/*
	������
	���һ�����ڰ�������ؼ����Խ��ô�����Ϊ����������ؼ�.
*/
#define C32ContainerCallOnXyz(hwndCtl, OnXyz)\
		for(size_t i = 0; i < m_List.GetCount(); i++)\
		{										\
			if (m_List[i]->GetPtr() == hwndCtl)\
			{\
				Handle = m_List[i]->OnXyz(wParam, lParam, lResult);\
				break;\
			}\
		}
#define C32ContainerCallOnXyzCtlId(CtlId, OnXyz)\
	for(size_t i = 0; i < m_List.GetCount(); i++)\
{										\
	if (m_List[i]->GetControlId() == CtlId)\
{\
	Handle = m_List[i]->OnXyz(wParam, lParam, lResult);\
	break;\
}\
}
//SendMessage(*m_List[i], WM_SIZE, wParam, lParam);\

#define C32ContainerCallOnSize()\
		for(size_t i = 0; i < m_List.GetCount(); i++)\
		{										\
			m_List[i]->OnSize(wParam, lParam, lResult);\
		}

class C32Container : public C32Window/*, public C32MouseEvent*/
{

public:
	C32Container()
	{
		Init();
	}

	virtual ~C32Container()
	{
		ZxDebugEx((__FUNCTION__"():: m_Hwnd: %p This: %p  %ws\n", m_Hwnd,this, this->GetText()));
		Destroy();
	}

	static DWORD RegisterClass()
	{
		DWORD Atom = RegisterClassEx32(C32_WC_CONTAINTER);

		return Atom;
	}

	static VOID Initialize()
	{
		//ע��C32Container��
		RegisterClass();

	}
public:
	
	VOID AddC32Window(C32Window* Window)
	{
		m_List.Add(Window);
	}
	
	VOID AddC32Child(C32Window* Window)
	{
		m_List.Add(Window);
	}

	virtual VOID SetVisible(BOOL bVisible = TRUE)
	{
		int Count = (int)m_List.GetCount();
		for(int i = 0; i < Count; i++)
		{
			m_List[i]->SetVisible(bVisible);
		}
		C32Window::SetVisible(bVisible);
	}

	int GetC32WindowCount()
	{
		return (int)m_List.GetCount();
	}

	virtual BOOL OnDestroy()
	{
		return TRUE;
	}

	BOOL CreateContainer(LPCWSTR WindowName,int X, int Y, int Cx, int Cy, HWND Hwnd)
	{
		DWORD ExStyle = 0;
		DWORD Style = WS_VISIBLE | WS_CHILDWINDOW ;

		HWND  hwndContainter = Create(ExStyle, C32_WC_CONTAINTER, WindowName, Style, X, Y, Cx, Cy, Hwnd);

		return C32IsValidHwnd(hwndContainter);
	}

public:
	virtual BOOL CALLBACK OnDestroy(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		Handle = OnDestroy();
		return Handle;
	}

	virtual BOOL CALLBACK OnMeasureItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		
		BOOL Handle = FALSE;
		LPMEASUREITEMSTRUCT  lpmis = (LPMEASUREITEMSTRUCT)lParam;
		ZxDebugEx((__FUNCTION__"()::Type:%s \n", C32GetOwnerDrawCtrlType(lpmis->CtlType)));
		C32ContainerCallOnXyzCtlId(lpmis->CtlID,  OnMeasureItem);

		return Handle;
	}

	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		C32String Buffer;
		Buffer.AssignStringW(256);
		GetWindowText(lpdis->hwndItem, Buffer, 256);
		ZxDebugEx((__FUNCTION__"()::Type:%s Control Text: %ws \n",C32GetOwnerDrawCtrlType(lpdis->CtlType), Buffer.GetString()));
		ZxDebugEx((__FUNCTION__"():: CtlType:%d CtlID:%d itemID:%d itemAction:0x%08x itemState:0x%08x hwndItem:%p hDC:%p{%d, %d, %d, %d}\n", 
					lpdis->CtlType, lpdis->CtlID,lpdis->itemID, lpdis->itemAction, lpdis->itemState,lpdis->hwndItem,lpdis->hDC,
					lpdis->rcItem.left,lpdis->rcItem.top, lpdis->rcItem.right, lpdis->rcItem.bottom));
		if (lpdis->CtlType == ODT_MENU)
		{
			if (m_OnDrawItem)
			{
				Handle = m_OnDrawItem(lpdis, lResult, this);
			}
		}else
		{
			C32ContainerCallOnXyz(lpdis->hwndItem, OnDrawItem);
		}
		

		return Handle;
	}

	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		//C32ContainerCallOnSize();
		BOOL Handle = FALSE;
		int Cx = GET_X_LPARAM(lParam);
		int Cy = GET_Y_LPARAM(lParam);
		ZxDebug((__FUNCTION__"():: %ws: {%d , %d } \n", GetText(),Cx, Cy));
		CString Text = GetText();
		if (Text.Compare(L"CClockTask") == 0)
		{
			INT XXXXXXXXXX=0;
		}
		
		for(size_t i = 0; i < m_List.GetCount(); i++)
		{
			Text= m_List[i]->GetText();
			ZxDebug((__FUNCTION__"():: %ws Flag: 0x%08x\n", m_List[i]->GetText(), m_List[i]->m_SwpFlag));
			if (Text.Compare(L"CClockTask") == 0)
			{ 
				INT XXXXXXXXXX=0;
			}
			if (m_List[i]->m_PosVisible == FALSE)
				continue;
			m_List[i]->GetPos();
			m_List[i]->m_SizeWindow.cx = Cx;
			m_List[i]->m_SizeWindow.cy = Cy;
			POINT Pt = {};
			SIZE  Size={};
			LPCWSTR xx = m_List[i]->GetText();
			m_List[i]->CalPosSize(Pt, Size);
			ZxDebug((__FUNCTION__"():: %ws : {%d, %d, %d, %d }\n",m_List[i]->GetText(), Pt.x, Pt.y, Size.cx, Size.cy));
			DWORD Flag = SWP_NOZORDER | m_List[i]->m_SwpFlag;
			
			m_List[i]->SetPos(Pt.x, Pt.y, Size.cx, Size.cy, Flag);
			/*if (!IsContainer())
			{
				m_List[i]->OnSize(wParam, (LPARAM)MAKELONG(Size.cx, Size.cy), lResult);
			}*/
			int xxxxxxxxxxxx=0;
		}
		return FALSE;
	}

	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		int xPos, yPos;

		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);

		if (m_OnContextMenu)
			Handle = m_OnContextMenu((HWND)wParam, xPos, yPos, lResult, this);
		
		if (Handle == FALSE)
			Handle = m_Menu.Display(xPos, yPos);

		if (Handle == FALSE)
			C32ContainerCallOnXyz((HWND)wParam, OnContextMenu);

		return Handle;
	}
	
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMHDR lphdr = (LPNMHDR)lParam;
		ZxDebug((__FUNCTION__"():: hwndFrom: %p Code: %d\n", lphdr->hwndFrom, lphdr->code));
		C32ContainerCallOnXyz(lphdr->hwndFrom, OnNotify);
		return Handle;
	}

	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		if (m_OnCommand)
			Handle = m_OnCommand(wParam, lParam, lResult, this);
		
		if (Handle == FALSE)
		{
			if (C32CommandIsCtrl(wParam) || (PVOID)lParam != NULL)
			{
				C32ContainerCallOnXyz((HWND)lParam, OnCommand);
			}
		}
			
		return Handle;
	}

	virtual BOOL CALLBACK OnCtlColorStatic(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND hwnd = (HWND)lParam;
		ZxDebug((__FUNCTION__"():: hwndFrom: %p \n", hwnd));
		
		C32ContainerCallOnXyz(hwnd, OnCtlColorStatic);
		return Handle;
	}

	virtual BOOL CALLBACK OnCtlColorBtn(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND hwnd = (HWND)lParam;
		
		C32ContainerCallOnXyz(hwnd, OnCtlColorBtn);
		return Handle;
	}

	virtual BOOL CALLBACK OnCtlColorListBox(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND hwnd = (HWND)lParam;
		
		
		
		ZxDebug((__FUNCTION__"():: hwndFrom: %p \n", hwnd));
		//C32ContainerCallOnXyz(hwnd, OnCtlColorListBox);
		for(size_t i = 0; i < m_List.GetCount(); i++)
		{
			HWND ListBox = m_List[i]->GetPtr();
			WCHAR ClassName[64]={};
			 m_List[i]->GetClassName(ClassName, 64);
			if(wcscmp(ClassName, WC_COMBOBOX) == 0)
			{
				C32ComboBox* Cb = (C32ComboBox*)m_List[i];
				ListBox = Cb->GetListBoxHwnd();
			}
			if (ListBox == hwnd)
			{
				Handle = m_List[i]->OnCtlColorListBox(wParam, lParam, lResult);
				break;
			}
		}
		return Handle;
	}

	virtual BOOL CALLBACK OnCtlColorEdit(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND hwnd = (HWND)lParam;
		ZxDebug((__FUNCTION__"():: hwndFrom: %p \n", hwnd));

		C32ContainerCallOnXyz(hwnd, OnCtlColorEdit);
		return Handle;
	}


	
public:
	BOOL IsChildStyle()
	{
		DWORD_PTR dwStyle = GetWindowLongPtr(m_Hwnd, GWL_STYLE);

		if (dwStyle & WS_CHILD) {
			// ����һ���Ӵ���
			return TRUE;
		} else {
			// �ⲻ��һ���Ӵ���
			return FALSE;
		}
	}
public:	
	VOID Init()
	{
		m_CtrlType = C32CtrlTypeContainer;
				
		m_bDeleteList = FALSE;
		m_IsContainer = TRUE;
	}

	VOID SetFreeList(BOOL bFree = TRUE)
	{
		m_bDeleteList = TRUE;
	}

	VOID Destroy()
	{
		//C32FreeWindowList(m_List, m_bDeleteList);
	}

public:
	CAtlArray<C32Window*> m_List;
	C32Menu            m_Menu;
	BOOL					m_bDeleteList;

public:
	const C32Container(const C32Container& Other)
	{
		*this = Other;
		

	}

	const C32Container& operator=(const C32Container& Other)
	{
		m_Hwnd = Other.m_Hwnd;
		Attach(Other.m_Hwnd);
	
		for(size_t i = 0; i < Other.m_List.GetCount(); i++)
		{
			m_List.Add(Other.m_List[i]);
		}
		return *this;
	}

};

/*
	Ϊ��ʵ�ֽ���λ�úʹ�С�ĸı�.
	̫���ӣ��벻�����������ʱ��ǳ��
*/
class C32Layout
{
public:
	C32Layout()
	{
		Init();
	}

	~C32Layout()
	{
		Destroy();
	}

public:
	VOID SetPosSize(int X, int Y, int Cx, int Cy)
	{
		m_Rect.left = X;
		m_Rect.top = Y;
		m_Rect.right = X + Cx;
		m_Rect.bottom = Y + Cy;
	}

public:
	VOID Init()
	{
		SetRectEmpty(&m_Rect);
	}
	
	VOID Destroy()
	{
		//m_LayList.clear();
		//m_LayList.resize(0);
	
	}
public:
	enum Type
	{
		horizontal,
		vertical,
	};

	VOID SetHorizontalLayout()
	{
		m_Type = horizontal;
	}

	VOID SetVerticalLayout()
	{
		m_Type = vertical;
	}

	int GetWidth()
	{
		return C32GetRectWidth(m_Rect);
	}

	int GetHeight()
	{
		return C32GetRectHeight(m_Rect);
	}

	VOID AddLayout(C32Layout& Layout)
	{
		m_LayList.Add(Layout);
	}

	
	VOID DebugRect()
	{
		C32DbgOutRectPosSize(m_Rect, __FUNCTION__);
	}

	VOID Debug(int K = 0)
	{
		C32String String;

		String += L"";
		for(int i = 0; i < K; i++)
		{
			String += L"    ";
		}

		ZxDebug((__FUNCTION__"()::	%ws {%d, %d, %d,%d} \n", String.GetString(),m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom));
		

		for(size_t i = 0; i < m_LayList.GetCount(); i++)
		{
			m_LayList[i].Debug(K+1);
		}
	}



public:
	Type  m_Type;
	RECT  m_Rect;
	C32Container m_List; //Layout �еĿؼ�
	CAtlArray<C32Layout> m_LayList;
public:
	C32Layout(__in const C32Layout& Other)
	{
		operator=(Other);
	}
	C32Layout& operator=(__in const C32Layout& Other)
	{
		m_Type = Other.m_Type;
		m_Rect = Other.m_Rect;
		m_List = Other.m_List;
		m_LayList.Copy(Other.m_LayList);

		return *this;
	}
};

class C32HLayout : public C32Layout
{
public:
	C32HLayout()
	{
		SetHorizontalLayout();
	}

	~C32HLayout()
	{

	}


};

static VOID C32LayoutTest()
{
	C32Layout hLay;
	hLay.SetPosSize(0,0, 200, 200);
	{
		C32Layout hLayTop;
		C32Layout hLayTop1;
		C32Layout hLayTop2;
		hLayTop.SetPosSize(0,0, 200, 50);
		hLayTop1.SetPosSize(0,0, 50, 50);
		hLayTop2.SetPosSize(50,0, 150, 50);
		hLayTop.AddLayout(hLayTop1);
		hLayTop.AddLayout(hLayTop2);



		C32Layout hLayCenter;
		hLayCenter.SetPosSize(0,50, 200, 50);

		C32Layout hLayBottom;
		hLayBottom.SetPosSize(0,100, 200, 100);

		hLay.AddLayout(hLayTop);
		hLay.AddLayout(hLayCenter);
		hLay.AddLayout(hLayBottom);

	}
	
	hLay.Debug();
	


}

class C32TabCtrlEventCallback
{

public:
	C32TabCtrlEventCallback()
	{
		Init();
	}
	
	~C32TabCtrlEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnNotifySelChange = NULL;
		m_OnNotifySelChanging = NULL;
	}

	VOID SetEventSelectChange(C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE Callback)
	{
		m_OnNotifySelChange = Callback;
	}

	VOID SetEventSelectChanging(C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE Callback)
	{
		m_OnNotifySelChanging = Callback;
	}

	//Button Control Event
	C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE m_OnNotifySelChange; //�Ѿ��ı�
	C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE m_OnNotifySelChanging;//��Ҫ�ı�
};

#define TTCtrl_Active(hwnd, bActivate)\
		SendMessage(hwnd, TTM_ACTIVATE, (WPARAM)bActivate, (LPARAM)0L)
	
#define TTCtrl_SetToolInfo(hwnd, lpti)\
			SendMessage(hwnd, TTM_SETTOOLINFO, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_AddTool(hwnd, lpti)\
			  (BOOL)SendMessage(hwnd, TTM_ADDTOOL, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)
#define TTCtrl_DelTool(hwnd, lpti)\
				SendMessage(hwnd, TTM_DELTOOL, (WPARAM)0L, (LPARAM)(LPTOOLINFO) lpti)
#define TTCtrl_EnumTool(hwnd, iTool,lpti)\
			 (BOOL)SendMessage(hwnd, TTM_ENUMTOOLS, (WPARAM)(UINT) iTool, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_GetBubbleSize(hwnd, lpti)\
			  (DWORD)SendMessage(hwnd, TTM_GETBUBBLESIZE, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_GetCurTool(hwnd, lpti)\
     (int)SendMessage(hwnd, TTM_GETCURRENTTOOL, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_GetDelayTime(hwnd, duration)\
     (int)SendMessage(hwnd, TTM_GETDELAYTIME, (WPARAM)(DWORD)duration, (LPARAM)0L)

#define TTCtrl_SetDelayTime(hwnd, duration, time)\
     (int)SendMessage(hwnd, TTM_SETDELAYTIME, (WPARAM)(DWORD)duration, (LPARAM)(DWORD)time)

#define TTCtrl_GetMargin(hwnd, lprc)\
     SendMessage(hwnd, TTM_GETMARGIN, (WPARAM)0L, (LPARAM)(LPRECT) lprc)

#define TTCtrl_SetMargin(hwnd, lprc) \
    SendMessage(hwnd, TTM_SETMARGIN, (WPARAM)0L, (LPARAM)(LPRECT) lprc)

#define TTCtrl_GetMaxTipWidth(hwnd) \
    (int)SendMessage(hwnd, TTM_GETMAXTIPWIDTH, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_SetMaxTipWidth(hwnd, width) \
    (int)SendMessage(hwnd, TTM_SETMAXTIPWIDTH, (WPARAM)0L, (LPARAM)(int)width)

#define TTCtrl_GetText(hwnd, iChar, lpti)  \
	SendMessage(hwnd, TTM_GETTEXT, (WPARAM)(DWORD)iChar, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_GetTipBkColor(hwnd)\
     (COLORREF)SendMessage(hwnd, TTM_GETTIPBKCOLOR, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_SetTipBkColor(hwnd, clr)\
     (COLORREF)SendMessage(hwnd, TTM_SETTIPBKCOLOR, (WPARAM)(COLORREF) clr, (LPARAM) 0L)

#define TTCtrl_GetTipTextColor(hwnd)\
     (COLORREF)SendMessage(hwnd, TTM_GETTIPTEXTCOLOR, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_SetTipTextColor(hwnd, clr)\
     (COLORREF)SendMessage(hwnd, TTM_SETTIPTEXTCOLOR, (WPARAM)(COLORREF) clr, (LPARAM)0L);

#define TTCtrl_GetTitle(hwnd, lpttgt)\
     SendMessage(hwnd, TTM_GETTITLE, (WPARAM)0L, (LPARAM)(PTTGETTITLE)lpttgt)

#define TTCtrl_SetTitle(hwnd, icon, title)\
     (BOOL)SendMessage(hwnd, TTM_SETTITLE, (WPARAM)(int) icon, (LPARAM)(LPCWSTR) title)

#define TTCtrl_GetToolCount(hwnd)\
     (int)SendMessage(hwnd, TTM_GETTOOLCOUNT, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_GetToolInfo(hwnd, lpti)\
		  (BOOL)SendMessage(hwnd, TTM_GETTOOLINFO, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_SetToolInfo(hwnd, lpti)\
		  SendMessage(hwnd, TTM_SETTOOLINFO, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_SetWindowTheme(hwnd, theme)\
     (BOOL)SendMessage(hwnd, TTM_SETWINDOWTHEME , (WPARAM)0L, (LPARAM))(LPCWSTR) theme)

#define TTCtrl_TrackActive(hwnd, bActivate, lpti)\
		SendMessage(hwnd, TTM_TRACKACTIVATE, (WPARAM) bActivate, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_TrackPosition(hwnd, x, y)\
		SendMessage(hwnd, TTM_TRACKPOSITION, (WPARAM) 0, (LPARAM) MAKELONG(x, y))

#define TTCtrl_HitTest(hwnd, lphti)	\
	  (BOOL)SendMessage(hwnd, TTM_HITTEST, (WPARAM)0L, (LPARAM)(LPHITTESTINFO)lphti)

#define TTCtrl_NewToolRect(hwnd, lpti)\
		  SendMessage(hwnd, TTM_NEWTOOLRECT, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_Pop(hwnd)\
				SendMessage(hwnd, TTM_POP, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_PopUP(hwnd)\
				SendMessage(hwnd, TTM_POPUP, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_RelayEvent(hwnd, lpmsg)\
				SendMessage(hwnd, TTM_RELAYEVENT, (WPARAM)0L, LPARAM)(LPMSG) lpmsg)

#define TTCtrl_Update(hwnd)\
				SendMessage(hwnd, TTM_UPDATE , (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_UpdateTipText(hwnd, lpti)\
		  SendMessage(hwnd, TTM_UPDATETIPTEXT, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_WindowFromPoint(hwnd, lppt)\
		  SendMessage(hwnd, TTM_WINDOWFROMPOINT, (WPARAM)0L, (LPARAM)(LPPOINT)lppt)

 
class C32ToolTipEventCallback
{

public:
	C32ToolTipEventCallback()
	{
		Init();
	}

	~C32ToolTipEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnNotifyGetDispInfo = NULL;
	}

	
	VOID SetEventGetDispInfo(C32_EVENT_CALLBACK_TOOLTIP_CTRL_NOTIFY_GETDISPINFO Callback)
	{
		m_OnNotifyGetDispInfo = Callback;
	}

	//ȡ��Tip��ʾ���ı�
	C32_EVENT_CALLBACK_TOOLTIP_CTRL_NOTIFY_GETDISPINFO m_OnNotifyGetDispInfo;
	
};


class C32ToolTip : public C32Window,  C32ToolTipEventCallback
{
#define C32ToolTipMaxChar 4096
#define C32ToolTipIdIsHwnd(Flag)((Flag & TTF_IDISHWND) == TTF_IDISHWND)
public:
	C32ToolTip()
	{

	}
	
	~C32ToolTip()
	{


	}

	HWND Create(DWORD Style, int xPos, int yPos, int Cx, int Cy, HWND hwnd)
	{
		m_Hwnd = CreateWindow(TOOLTIPS_CLASS, L"C32ToolTip", Style, xPos, yPos,Cx,Cy, hwnd, NULL, C32Hinstance, (LPVOID)this);
		if (m_Hwnd)
			Attach(m_Hwnd);
		ZxDebugEx((__FUNCTION__"():: m_Hwnd: %p This: %p \n", m_Hwnd, this));
		return m_Hwnd;
	}

	/*
		
		hwndCtrlParent �� Handle to the window that contains the tool
		CtrlId ��Application-defined identifier of the tool. If uFlags includes the TTF_IDISHWND flag, uId must specify the window handle to the tool
	*/
	BOOL AddTool(HWND Hwnd, LPCWSTR lpszText, LPCRECT lpRectTool, UINT_PTR nIDTool, DWORD Flags = TTF_IDISHWND|TTF_SUBCLASS, LPARAM lParam = 0){
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.uFlags = Flags;
		ti.hwnd = Hwnd;
		ti.hinst = C32Hinstance;
		ti.lParam = lParam;
		ti.lpszText = (LPWSTR)lpszText;
		ti.uId = (ULONG_PTR)nIDTool;
		ti.rect = *lpRectTool;

		BOOL Ret = TTCtrl_AddTool(m_Hwnd, &ti);

		ZxDebugEx((__FUNCTION__"()::Owner : %p Id : %p %d \n", Hwnd,reinterpret_cast<PVOID>(nIDTool) ,Ret));

		return Ret;

	}


	VOID DeleteTip(HWND Hwnd, UINT_PTR nIDTool)
	{
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.uFlags = TTF_IDISHWND;
		ti.hwnd = Hwnd;
		ti.uId = (UINT_PTR)nIDTool;

		TTCtrl_DelTool(m_Hwnd, &ti);
	}

	VOID DeleteTip(HWND Hwnd)
	{
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.hwnd = Hwnd;
		TTCtrl_DelTool(m_Hwnd, &ti);

	}

	
	VOID DeleteAllTip()
	{
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.uFlags = TTF_IDISHWND;
		
	}
	
	BOOL EnumTip(int iTip)
	{
		C32String Text;
		Text.AssignStringW(256);

		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.lpszText = (LPWSTR)Text;
		return TTCtrl_EnumTool(m_Hwnd, iTip, &ti);
	}

	void FillInToolInfo(TOOLINFO& ti, HWND hwnd, UINT_PTR nIDTool) const
	{
		memset(&ti, 0, sizeof(TOOLINFO));
		
		if (nIDTool == 0)
		{
			ti.hwnd = ::GetParent(hwnd);
			ti.uFlags = TTF_IDISHWND;
			ti.uId = (UINT_PTR)hwnd;
		}
		else
		{
			ti.hwnd = hwnd;
			ti.uFlags = 0;
			ti.uId = nIDTool;
		}
	}


	SIZE GetBubbleSize(LPTOOLINFO lpti)
	{
		SIZE Size = {};
		DWORD dwSize = TTCtrl_GetBubbleSize(m_Hwnd, lpti);
		Size.cx = LOWORD(dwSize);
		Size.cy = HIWORD(dwSize);

		return Size;
	}

	int GetDelayTime(DWORD dwDuration = TTDT_AUTOPOP)
	{
		return TTCtrl_GetDelayTime(m_Hwnd, dwDuration);
	}

	VOID SetDelayTime(DWORD dwDuration, int iTimeMs)
	{
		TTCtrl_SetDelayTime(m_Hwnd, dwDuration, iTimeMs);
	}

	VOID GetMargin(LPRECT Rect)
	{
		TTCtrl_GetMargin(m_Hwnd, &Rect);
	}

	VOID SetMargin(LPRECT Rect)
	{
		TTCtrl_SetMargin(m_Hwnd, &Rect);
	}
	
	int GetMaxTipWidth()
	{
		return TTCtrl_GetMaxTipWidth(m_Hwnd);
	}

	int SetMaxTipWidth(int Width)
	{
		return TTCtrl_SetMaxTipWidth(m_Hwnd, Width);
	}

	VOID GetText(HWND hwndOwer, HWND hwnd, C32String& Text)
	{
		Text.AssignStringW(C32ToolTipMaxChar);
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.hwnd = hwndOwer;
		ti.uId = (ULONG_PTR)hwnd;
		ti.lpszText = Text;

		TTCtrl_GetText(m_Hwnd, 256, &ti);
	}

	VOID GetTitle(PTTGETTITLE Title, C32String& pszTitle)
	{
		RtlZeroMemory(Title, sizeof(TTGETTITLE));
		pszTitle.AssignStringW(C32ToolTipMaxChar);
		Title->cch = C32ToolTipMaxChar;
		Title->pszTitle = pszTitle;
		TTCtrl_GetTitle(m_Hwnd, &Title);
	}

	BOOL SetTitle(int iIcon, LPCWSTR Title)
	{
		return TTCtrl_SetTitle(m_Hwnd, iIcon,Title);
	}

	COLORREF GetTipBkColor()
	{
		return TTCtrl_GetTipBkColor(m_Hwnd);
	}

	COLORREF SetTipBkColor(COLORREF clr)
	{
		return TTCtrl_SetTipBkColor(m_Hwnd, clr);
	}

	COLORREF GetTipTextColor()
	{
		return TTCtrl_GetTipTextColor(m_Hwnd);
	}

	COLORREF SetTipTextColor(COLORREF clr)
	{
		return TTCtrl_SetTipTextColor(m_Hwnd, clr);
	}

	int GetTipCount()
	{
		int Count = TTCtrl_GetToolCount(m_Hwnd);

		return Count;
	}

	BOOL GetTipInfo(LPTOOLINFO lpti)
	{
		return TTCtrl_GetToolInfo(m_Hwnd, lpti);
	}

	VOID SetTipInfo(LPTOOLINFO lpti)
	{
		TTCtrl_SetToolInfo(m_Hwnd, lpti);
	}

	VOID SetTipRect(LPTOOLINFO lpti)
	{
		TTCtrl_NewToolRect(m_Hwnd, lpti);
	}

public:
	void Activate(_In_ BOOL bActivate = TRUE)
	{
		TTCtrl_Active(m_Hwnd, bActivate);
	}

	VOID Hidden()
	{
		TTCtrl_Pop(m_Hwnd);
	}

	VOID Popup()
	{
		TTCtrl_PopUP(m_Hwnd);
	}
	
	VOID TrackActive(BOOL bActive, HWND hwndOwner, ULONG_PTR hwndId)
	{
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.hwnd = hwndOwner;
		ti.uId = hwndId;

		TTCtrl_TrackActive(m_Hwnd, bActive, &ti);
	}

	VOID TrackActive(int xPos, int yPos)
	{
		TTCtrl_TrackPosition(m_Hwnd, xPos, yPos);
	}

	BOOL    OnNotifyShow(WPARAM idTT, LPNMHDR lpnmhdr,LRESULT& lResult)
	{
		ZxDebugEx((__FUNCTION__"():: idTT : %p hwnd: %p \n", (PVOID)idTT, lpnmhdr->hwndFrom));
		return FALSE;
	}

	BOOL    OnNotifyGetDispInfo(LPNMTTDISPINFO lpnmttd,LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		ZxDebugEx((__FUNCTION__"():: Hwnd: %p idFrom: %p lpszText : %p hinst: %p uFlags: 0x%08X lParam : %p \n",
		lpnmttd->hdr.hwndFrom, (PVOID)lpnmttd->hdr.idFrom,lpnmttd->lpszText, lpnmttd->hinst, lpnmttd->uFlags, (PVOID)lpnmttd->lParam));
		lpnmttd->lpszText = L"0123456789\n0123456789\n0123456789\n01234567890123456789012345678901234567890123456789012345678901234567890\n";
		SetMaxTipWidth(150);
		if (m_OnNotifyGetDispInfo)
		{
			BOOL IsRetain = FALSE;
			Handle = m_OnNotifyGetDispInfo(lpnmttd->hdr.idFrom, C32ToolTipIdIsHwnd(lpnmttd->uFlags), &lpnmttd->lpszText, &IsRetain, lResult, this);
			if (IsRetain)
			{
				lpnmttd->uFlags |= TTF_DI_SETITEM;
			}
		}
		
		return Handle;
	}


	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;

		LPNMHDR lpnm = (LPNMHDR)lParam;

		CHAR* Str = C32DbgGetToolTipCtrlNotifyString(lpnm->code);
		ZxDebugEx((__FUNCTION__"():: %s \n", Str));
		
		switch(lpnm->code)
		{
			case TTN_SHOW:
				Handle = OnNotifyShow(wParam, lpnm, lResult);
				break;
			case  TTN_GETDISPINFO:
				Handle = OnNotifyGetDispInfo((LPNMTTDISPINFO)lParam,lResult);
				break;
			default:
				break;
		}

		return TRUE;
	}
	

	
public:
	operator HWND() const
	{
		return m_Hwnd;
	}

};

class C32TabCtrl : public C32Container , public C32TabCtrlEventCallback
{
public:
	C32TabCtrl()
	{
		m_iCurSel = 0;
		m_ToolTip = NULL;
	}
	
	virtual ~C32TabCtrl()
	{

	}

	HWND Create(DWORD Style, int xPos, int yPos, int Cx, int Cy, HWND hwnd)
	{
		m_Hwnd = CreateWindow(WC_TABCONTROL, L"C32TabCtrl",Style, xPos, yPos, Cx, Cy, hwnd, NULL, C32Hinstance, NULL);
		ZxDebugEx((__FUNCTION__"():: m_Hwnd : %p This: %p\n", m_Hwnd, this));
		if (m_Hwnd)
			Attach(m_Hwnd);

		return m_Hwnd;
	}

	int InsertItem(int iIndex, LPCWSTR Text, int iImage = -1, LPARAM lParam = NULL)
	{
		TCITEM tci = {};
		tci.mask = TCIF_TEXT | TCIF_IMAGE | TCIF_PARAM;
		tci.pszText = (LPWSTR)Text;
		tci.cchTextMax = (int)wcslen(Text);
		tci.iImage = iImage;
		tci.lParam = lParam;

		int Index = TabCtrl_InsertItem(m_Hwnd, iIndex, &tci);
		ZxDebugEx((__FUNCTION__"():: iIndex :%d %ws Index : %d \n",iIndex, Text,Index));
		if (iIndex != -1)
			CreateTabPage();
		return Index;
	} 

	BOOL DeleteItem(int iIndex)
	{
		return TabCtrl_DeleteItem(m_Hwnd, iIndex);
	}
	
	BOOL DeleteAllItems()
	{
		return TabCtrl_DeleteAllItems(m_Hwnd);
	}

	VOID Reset()
	{
		DeleteAllItems();
	}

	int GetCount()
	{
		return TabCtrl_GetItemCount(m_Hwnd);
	}

	//Only tab controls that have the TCS_MULTILINE style can have multiple rows of tabs
	int GetLineCount()
	{
		return TabCtrl_GetRowCount(m_Hwnd);
	}

	int GetCurrentSelect()
	{
		return TabCtrl_GetCurSel(m_Hwnd);
	}

	int SetCurrentSelect(int iIndex)
	{
		if (iIndex < 0 || iIndex >= GetCount())
			return m_iCurSel;
		
		int iSel = TabCtrl_SetCurSel(m_Hwnd, iIndex);
		if (iSel != -1)
		{
			m_iCurSel = iIndex;
		}
		return iSel;
	}

	DWORD SetItemSize(int Cx, int Cy)
	{
		return TabCtrl_SetItemSize(m_Hwnd, Cx, Cy);
	}

	BOOL GetItemRect(int iIndex, LPRECT Rect)
	{
		return TabCtrl_GetItemRect(m_Hwnd, iIndex, Rect);
	}

	int SetMinWidth(int Cx)
	{
		int Cx0 = 0;
		
		Cx0 = TabCtrl_SetMinTabWidth(m_Hwnd, Cx);
		ZxDebugEx((__FUNCTION__"():: MinTabWidth : %d \n", Cx0));

		return Cx0;
	}

	BOOL GetItem(int iIndex, LPTCITEM lptci)
	{
		m_ItemText.AssignStringW(256);
		lptci->mask = TCIF_TEXT | TCIF_IMAGE | TCIF_RTLREADING | TCIF_PARAM | TCIF_STATE;
		lptci->pszText = (LPWSTR)m_ItemText.GetBuffer();
		lptci->cchTextMax = 256;
		return TabCtrl_GetItem(m_Hwnd, iIndex, lptci);
	}

	DWORD SetExtendedStyle(DWORD ExSyle)
	{
		return TabCtrl_SetExtendedStyle(m_Hwnd, ExSyle);
	}

	DWORD GetExtendedStyle()
	{
		return TabCtrl_GetExtendedStyle(m_Hwnd);
	}
	
	VOID SetPadding(int Cx, int Cy)
	{
		return TabCtrl_SetPadding(m_Hwnd, Cx, Cy);
	}
	 
	VOID SetToolTips(HWND hwndTT)
	{
		TabCtrl_SetToolTips(m_Hwnd, hwndTT);
	}

	HWND GetToolTips()
	{
		return TabCtrl_GetToolTips(m_Hwnd);
	}

	HIMAGELIST SetImageList()
	{
		return TabCtrl_SetImageList(m_Hwnd, m_ImageList);
	}

	HIMAGELIST GetImageList()
	{
		return TabCtrl_GetImageList(m_Hwnd);
	}

	VOID AdjustRect(BOOL fLarger, LPRECT Rect)
	{
		TabCtrl_AdjustRect(m_Hwnd, fLarger, Rect);
		
	}

// ��Ϣ����
public:
	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		DWORD Type = (DWORD)wParam;
		int Cx = GET_X_LPARAM(lParam);
		int Cy = GET_Y_LPARAM(lParam);
		RECT rc = {};
		SetRect(&rc, 0, 0, 
			GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); 
		SetPos(0, 0, Cx, Cy, SWP_NOMOVE|SWP_NOZORDER);
		OnSizeTabPage();
		//AdjustRect(FALSE, rc);
		if (m_OnSize)
		{
			Handle = m_OnSize(Type, Cx, Cy, lResult, this);
		}

		return Handle;
	}

	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMHDR lpnmhdr = (LPNMHDR)lParam;
		int iSelItem = GetCurrentSelect();
		ZxDebugEx((__FUNCTION__"():: iSelItem: %d %s \n", iSelItem,C32DbgGetTabCtrlNotifyString(lpnmhdr->code)));
		switch(lpnmhdr->code)
		{
			case TCN_SELCHANGE:
				SetChildVisible(m_iCurSel, FALSE);
				m_iCurSel = iSelItem;
				SetChildVisible(m_iCurSel);
				InvalidateRect(m_Hwnd, NULL, TRUE);
				if (m_OnNotifySelChange)
				{
					Handle = m_OnNotifySelChange(iSelItem, lResult, this);
				}
			break;
			case TCN_SELCHANGING:
				if (m_OnNotifySelChanging)
				{
					Handle = m_OnNotifySelChanging(iSelItem, lResult, this);
				}
				
			break;


		}
		return Handle;
	}

public:
	virtual VOID AddChild(int iIndex, C32Window* Child)
	{
		if ((int)m_ListTab.GetCount() <= iIndex)
			return;
		::SetParent(Child->GetHwnd(), m_ListTab[iIndex]->GetHwnd());
		m_ListTab[iIndex]->AddC32Window(Child);
	}
	
	virtual VOID SetChildVisible(int iIndex, BOOL bVisible = TRUE)
	{
		if ((int)m_ListTab.GetCount() <= iIndex)
			return;
		m_ListTab[iIndex]->SetVisible(bVisible);
		//UpdateWindow(m_List[iIndex]->GetHwnd());
		//m_List[iIndex]->ReflushWindow();
	}

	int GetTabHeigth()
	{
		int Count;
		int RowCount;
		Count = GetCount();
		RowCount = GetLineCount();

		RECT Rect = m_ClientRect;
		AdjustRect(FALSE, &Rect);
		

		return Rect.top;
	}

	RECT GetDisplayRect()
	{
		RECT Rect = m_ClientRect;
		AdjustRect(FALSE, &Rect);

		return Rect;
	}

private:
	RECT GetTabPageRect()
	{
		RECT TabRect = GetDisplayRect();
		
		return TabRect;
	}
	
	VOID CreateTabPage()
	{
		DWORD Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
		
		RECT Rect = GetTabPageRect();
		C32Container* TabPage  = new C32Container();
		TabPage->Create(0, C32_WC_CONTAINTER, L"TabPage", Style, Rect.left, Rect.top, C32GetRectWidth(Rect), C32GetRectHeight(Rect), m_Hwnd);
		m_ListTab.Add(TabPage);

	}	

	VOID OnSizeTabPage()
	{
		GetPos();
		RECT Rect = GetTabPageRect();
		for(int i = 0; i < (int)m_ListTab.GetCount(); i++)
		{
			m_ListTab[i]->SetPos(Rect.left, Rect.top, C32GetRectWidth(Rect), C32GetRectHeight(Rect), SWP_NOMOVE|SWP_NOZORDER);
		}
	}

public:
	operator HWND() const
	{
	  return m_Hwnd;
	}

	operator const HWND() const
	{
		return m_Hwnd;
	}

public:
	C32String m_ItemText;
	CAtlArray<C32Container*> m_ListTab; //ÿ��Tab���е�����Ӧ�Ŀؼ�
	CAtlArray<C32Menu*> m_ListTabMenu; //ÿ��Tab���е�����Ӧ�Ŀؼ�

	int       m_iCurSel;
public:
	C32ImageList m_ImageList;
	C32ToolTip* m_ToolTip;
};

class C32TabList : public C32ListView, public C32TabListEventCallback
{

public:
	C32TabList()
	{
		m_ColorSel = C32ColorListViewSel;
		m_CustomDrawSel = -1;
	}

public:
	BOOL CreateTabList(int xPos, int yPos, int Cx, int Cy, HWND Hwnd)
	{
		DWORD ExStyle = 0;
		DWORD Style  =   WS_CHILD | WS_VISIBLE  |LVS_ICON | LVS_AUTOARRANGE;
		HWND HwndTab = Create(ExStyle, Style, xPos, yPos, Cx, Cy, Hwnd);
		if(!C32IsValidHwnd(HwndTab))
			return FALSE;
	
		//����ͼ��
		m_ImageListNormal.CreateNormal();
		SetImageList();

		return TRUE;
	}

	virtual BOOL  CALLBACK OnNotifyItemChanged(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMLISTVIEW lplv = (LPNMLISTVIEW)lParam;
		int iSubItem = lplv->iSubItem;

		if(C32LvIsSelected(lplv) && m_OnSelected)
		{
			ZxDebugEx((__FUNCTION__"():: iItem : %d iSubItem: %d uNewState : 0x%08x uOldState: 0x%08x uChanged: 0x%08x ptAction:{%d, %d} \n",
				lplv->iItem, lplv->iSubItem, lplv->uNewState, lplv->uOldState, lplv->uChanged, lplv->ptAction.x, lplv->ptAction.y));

			Handle = m_OnSelected(lplv->iItem, lplv, lResult, this);
		} 
		if(C32LvIsSelected(lplv))
		{
			m_iLastSel = lplv->iItem;			
			ZxDebugEx((__FUNCTION__"():: %d \n", m_iLastSel));
			ReflushWindow();
		}
		return Handle;
	}

public:
	COLORREF  m_ColorSel;
	int		  m_CustomDrawSel;
};

/*
	ʱ��ѡȡ�ؼ��ص�����
*/
class C32DateTimeCtrlEventCallback
{

public:
	C32DateTimeCtrlEventCallback()
	{
		Init();
	}

	~C32DateTimeCtrlEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnNotifyChange = NULL;
	}

	VOID SetEventNotifyChange(C32_EVENT_CALLBACK_DATETIME_CTRL_NOTIFY_CHANGE Callback)
	{
		m_OnNotifyChange = Callback;
	}

	//ȡ��Tip��ʾ���ı�
	C32_EVENT_CALLBACK_DATETIME_CTRL_NOTIFY_CHANGE m_OnNotifyChange;

};

// C32DateTimeCtrl
class C32DateTimeCtrl : public C32Window, public C32DateTimeCtrlEventCallback
{
public:
	// Constructors
	C32DateTimeCtrl()
	{
	
	}

	virtual ~C32DateTimeCtrl()
	{

	}
	// Retrieves the color for the specified portion of the calendar within the datetime picker control.
	COLORREF GetMonthCalColor(_In_ int iColor) const
	{
		return (COLORREF)DateTime_GetMonthCalColor(m_Hwnd, iColor);
	}

	// Sets the color for the specified portion of the calendar within the datetime picker control.
	COLORREF SetMonthCalColor(_In_ int iColor, _In_ COLORREF ref)
	{
		return (COLORREF)DateTime_SetMonthCalColor(m_Hwnd, iColor, ref);
	}

	// Sets the display of the datetime picker control based on the specified format string.
	BOOL SetFormat(_In_z_ LPCTSTR pstrFormat)
	{  
		return (BOOL) DateTime_SetFormat(m_Hwnd,(LPARAM) pstrFormat); 
	}
	
	// Sets the font of the datetime picker control's child calendar control.
	void SetMonthCalFont(_In_ HFONT hFont, _In_ BOOL bRedraw = TRUE)
	{
		DateTime_SetMonthCalFont(m_Hwnd, hFont, bRedraw);
	}

	// Sets the minimum and maximum allowable times for the datetime picker control.
	BOOL SetRange(_In_ const DWORD pMinRange, _In_ const LPSYSTEMTIME pMaxRange)
	{
		return DateTime_SetRange(m_Hwnd, pMaxRange, pMaxRange);
	}

	// Retrieves the current minimum and maximum allowable times for the datetime picker control.
	DWORD GetRange(_Inout_ LPSYSTEMTIME SysTime) const
	{
		return DateTime_GetRange(m_Hwnd, SysTime);

	}
	

	// REVIEW: Sets the style of the datetime picker control's child calendar control.
	DWORD SetMonthCalStyle(_In_ DWORD dwStyle)
	{
		return (DWORD)DateTime_SetMonthCalStyle(m_Hwnd, dwStyle);
	}

	// REVIEW: Retrieves the style of the datetime picker control's child calendar control.
	DWORD GetMonthCalStyle() const
	{
		return (DWORD)DateTime_GetMonthCalStyle(m_Hwnd);
	}

	// Retrieves information from the datetime picker control.
	BOOL GetDateTimePickerInfo(_Out_ LPDATETIMEPICKERINFO pDateTimePickerInfo) const
	{
		return (BOOL)DateTime_GetDateTimePickerInfo(m_Hwnd, &pDateTimePickerInfo);
	}

	// Retrieves the ideal size for the control (so that all the text fits).
	BOOL GetIdealSize(_Out_ LPSIZE pSize) const
	{
		return DateTime_GetIdealSize(m_Hwnd, pSize);
	}

	DWORD GetSystemtime(LPSYSTEMTIME pst)
	{
		return DateTime_GetSystemtime(m_Hwnd, pst);
		
	}

	// Operations
	// Sets the time in the datetime picker control.
	BOOL SetSystemtime(LPSYSTEMTIME pst, DWORD  gd =GDT_VALID)
	{
		return DateTime_SetSystemtime(m_Hwnd, gd, pst);
	}

	// REVIEW: Closes the datetime picker control.
	void CloseMonthCal()
	{
		DateTime_CloseMonthCal(m_Hwnd);
	}


public:
public:
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		BOOL Handle = FALSE;
		LPNMDATETIMECHANGE lpdtc = (LPNMDATETIMECHANGE)lParam;

		ZxDebugEx((__FUNCTION__"():: Text: %ws \n", this->GetText()));
		switch(lpdtc->nmhdr.code)
		{
		case DTN_DATETIMECHANGE	:
			Handle  = (m_OnNotifyChange ? m_OnNotifyChange(lpdtc, lResult, this) : FALSE);
			break;
		}

		if (Handle == TRUE)
			lResult = 0;

		return Handle;
	}

};



class C32RichEditCtrl : public C32Window
{
public:
	// ���캯����ʼ�����ھ��ΪNULL
	C32RichEditCtrl()  
	{


	}

	// ����Ƿ���Գ�������
	BOOL CanUndo() const {
		return (BOOL)::SendMessage(m_Hwnd, EM_CANUNDO, 0, 0);
	}

	// ����Ƿ������������
	BOOL CanRedo() const {
		return (BOOL)::SendMessage(m_Hwnd, EM_CANREDO, 0, 0);
	}

	// ��ȡ���һ�γ�������������
	UNDONAMEID GetUndoName() const {
		return (UNDONAMEID)::SendMessage(m_Hwnd, EM_GETUNDONAME, 0, 0);
	}

	// ��ȡ���һ����������������
	UNDONAMEID GetRedoName() const {
		return (UNDONAMEID)::SendMessage(m_Hwnd, EM_GETREDONAME, 0, 0);
	}

	// ��ȡ����
	int GetLineCount() const {
		return (int)::SendMessage(m_Hwnd, EM_GETLINECOUNT, 0, 0);
	}

	// ��ȡ�޸�״̬
	BOOL GetModify() const {
		return (BOOL)::SendMessage(m_Hwnd, EM_GETMODIFY, 0, 0);
	}

	// �����޸�״̬
	void SetModify(BOOL bModified = TRUE) {
		::SendMessage(m_Hwnd, EM_SETMODIFY, bModified, 0);
	}

	// �����ı�ģʽ
	BOOL SetTextMode(UINT fMode) {
		return (BOOL)::SendMessage(m_Hwnd, EM_SETTEXTMODE, (WPARAM)fMode, 0);
	}

	// ��ȡ�ı�ģʽ
	UINT GetTextMode() const {
		return (UINT)::SendMessage(m_Hwnd, EM_GETTEXTMODE, 0, 0);
	}

	// ��ȡ��������
	void GetRect(LPRECT lpRect) const {
		::SendMessage(m_Hwnd, EM_GETRECT, 0, (LPARAM)lpRect);
	}

	// �����ַ�λ�û�ȡ������
	VOID GetCharPos(long lChar, LPPOINT Point ) const {
		::SendMessage(m_Hwnd, EM_POSFROMCHAR, (WPARAM)Point, (LPARAM)lChar);
	}

	// ��ȡѡ��
	UINT GetOptions() const {
		return (UINT)::SendMessage(m_Hwnd, EM_GETOPTIONS, 0, 0);
	}

	// ����ѡ��
	void SetOptions(WORD wOp, DWORD dwFlags) {
		::SendMessage(m_Hwnd, EM_SETOPTIONS, (WPARAM)wOp, (LPARAM)dwFlags);
	}

	// �����Զ�URL���
	BOOL SetAutoURLDetect(BOOL bEnable = TRUE) {
		return (BOOL)::SendMessage(m_Hwnd, EM_AUTOURLDETECT, (WPARAM)bEnable, 0);
	}

	// ��ճ���������
	void EmptyUndoBuffer() {
		::SendMessage(m_Hwnd, EM_EMPTYUNDOBUFFER, 0, 0);
	}

	// ���ó�������
	UINT SetUndoLimit(UINT nLimit) {
		return (UINT)::SendMessage(m_Hwnd, EM_SETUNDOLIMIT, (WPARAM)nLimit, 0);
	}

	// �滻ѡ�е��ı�
	void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo) {
		::SendMessage(m_Hwnd, EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpszNewText);
	}

	// ���þ�������
	void SetRect(LPCRECT lpRect) {
		::SendMessage(m_Hwnd, EM_SETRECT, 0, (LPARAM)lpRect);
	}

	// ֹͣ������
	void StopGroupTyping() {
		::SendMessage(m_Hwnd, EM_STOPGROUPTYPING, 0, 0);
	}

	// ��������
	BOOL Redo() {
		return (BOOL)::SendMessage(m_Hwnd, EM_REDO, 0, 0);
	}

	// ��������
	BOOL Undo() {
		return (BOOL)::SendMessage(m_Hwnd, EM_UNDO, 0, 0);
	}

	// �������
	void Clear() {
		::SendMessage(m_Hwnd, WM_CLEAR, 0, 0);
	}

	// ��������
	void Copy() {
		::SendMessage(m_Hwnd, WM_COPY, 0, 0);
	}

	// ��������
	void Cut() {
		::SendMessage(m_Hwnd, WM_CUT, 0, 0);
	}

	// ճ������
	void Paste() {
		::SendMessage(m_Hwnd, WM_PASTE, 0, 0);
	}

	// ����ֻ��״̬
	BOOL SetReadOnly(BOOL bReadOnly = TRUE) {
		return (BOOL)::SendMessage(m_Hwnd, EM_SETREADONLY, bReadOnly, 0L);
	}

	// ��ȡ��һ���ɼ��к�
	int GetFirstVisibleLine() const {
		return (int)::SendMessage(m_Hwnd, EM_GETFIRSTVISIBLELINE, 0, 0L);
	}

	// ��ʾ����
	BOOL DisplayBand(LPRECT pDisplayRect) {
		return (BOOL)::SendMessage(m_Hwnd, EM_DISPLAYBAND, 0, (LPARAM)pDisplayRect);
	}

	// ��ȡѡ��Χ
	void GetSel(CHARRANGE &cr) const {
		::SendMessage(m_Hwnd, EM_EXGETSEL, 0, (LPARAM)&cr);
	}

	// ��ȡ����������
	BOOL GetPunctuation(UINT fType, PUNCTUATION* lpPunc) const {
		return (BOOL)::SendMessage(m_Hwnd, EM_GETPUNCTUATION, (WPARAM)fType, (LPARAM)lpPunc);
	}

	// ���ñ�����
	BOOL SetPunctuation(UINT fType, PUNCTUATION* lpPunc) {
		return (BOOL)::SendMessage(m_Hwnd, EM_SETPUNCTUATION, (WPARAM)fType, (LPARAM)lpPunc);
	}

	// �����ı�����
	void LimitText(long nChars) {
		::SendMessage(m_Hwnd, EM_EXLIMITTEXT, 0, nChars);
	}

	// �����ַ�������ȡ�к�
	long LineFromChar(long nIndex) const {
		return (long)::SendMessage(m_Hwnd, EM_EXLINEFROMCHAR, 0, nIndex);
	}

	// �����ַ�������ȡλ��
	VOID PosFromChar(UINT nChar, LPPOINT Point) const {
		
		::SendMessage(m_Hwnd, EM_POSFROMCHAR, (WPARAM)Point, nChar);
		
	}

	// ����λ�û�ȡ�ַ�����
	int CharFromPos(POINT pt) const {
		POINTL ptl = {pt.x, pt.y};
		return (int)::SendMessage(m_Hwnd, EM_CHARFROMPOS, 0, (LPARAM)&ptl);
	}

	// ����ѡ��Χ
	void SetSel(CHARRANGE &cr) {
		::SendMessage(m_Hwnd, EM_EXSETSEL, 0, (LPARAM)&cr);
	}

	// ���ҵ��ʱ߽�
	DWORD FindWordBreak(UINT nCode, DWORD nStart) const {
		return (DWORD)::SendMessage(m_Hwnd, EM_FINDWORDBREAK, (WPARAM)nCode, (LPARAM)nStart);
	}

	// �����ı�
	long FindText(DWORD dwFlags, FINDTEXTEX* pFindText) const {
		return (long)::SendMessage(m_Hwnd, EM_FINDTEXTEX, dwFlags, (LPARAM)pFindText);
	}

	// ��ʽ����Χ
	long FormatRange(FORMATRANGE* pfr, BOOL bDisplay) {
		return (long)::SendMessage(m_Hwnd, EM_FORMATRANGE, (WPARAM)bDisplay, (LPARAM)pfr);
	}

	// ��ȡ�¼�����
	long GetEventMask() const {
		return (long)::SendMessage(m_Hwnd, EM_GETEVENTMASK, 0, 0L);
	}

	// ��ȡ�ı����Ƴ���
	long GetLimitText() const {
		return (long)::SendMessage(m_Hwnd, EM_GETLIMITTEXT, 0, 0L);
	}

	// ��ȡѡ���ı�
	long GetSelText(_Pre_notnull_ _Post_z_ LPSTR lpBuf) const {
		return (long)::SendMessage(m_Hwnd, EM_GETSELTEXT, 0, (LPARAM)lpBuf);
	}

	// ���ػ���ʾѡ�в���
	void HideSelection(BOOL bHide, BOOL bPerm) {
		::SendMessage(m_Hwnd, EM_HIDESELECTION, bHide, bPerm);
	}

	// ���������С
	void RequestResize() {
		::SendMessage(m_Hwnd, EM_REQUESTRESIZE, 0, 0L);
	}

	// ��ȡѡ������
	WORD GetSelectionType() const {
		return (WORD)::SendMessage(m_Hwnd, EM_SELECTIONTYPE, 0, 0L);
	}

	// ��ȡ���ʻ���ģʽ
	UINT GetWordWrapMode() const {
		return (UINT)::SendMessage(m_Hwnd, EM_GETWORDWRAPMODE, 0, 0);
	}

	// ���õ��ʻ���ģʽ
	UINT SetWordWrapMode(UINT uFlags) const {
		return (UINT)::SendMessage(m_Hwnd, EM_SETWORDWRAPMODE, (WPARAM)uFlags, 0);
	}
	
	// ���ñ�����ɫ
	COLORREF SetBackgroundColor(BOOL bSysColor, COLORREF cr) {
		return (COLORREF)::SendMessage(m_Hwnd, EM_SETBKGNDCOLOR, bSysColor, cr);
	}

	// ���ø��ı��ؼ���������ɫ
	VOID SetTextColor(COLORREF color)
	{
		CHARFORMAT cf = {0};
		cf.cbSize = sizeof(CHARFORMAT);
		cf.dwMask = CFM_COLOR;              // ������ɫ����
		cf.crTextColor = color;             // ����������ɫ
		cf.dwEffects = 0;                   // �������Ч��

		SendMessage(m_Hwnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	}

	// �����¼�����
	DWORD SetEventMask(DWORD dwEventMask) {
		return (DWORD)::SendMessage(m_Hwnd, EM_SETEVENTMASK, 0, dwEventMask);
	}

	// ����OLE�ص�
	BOOL SetOLECallback(IRichEditOleCallback* pCallback) {
		return (BOOL)::SendMessage(m_Hwnd, EM_SETOLECALLBACK, 0, (LPARAM)pCallback);
	}

	
	// ����Ŀ���豸��ͨ��CDC��
	BOOL SetTargetDevice(HDC dc, long lLineWidth) {
		return (BOOL)::SendMessage(m_Hwnd, EM_SETTARGETDEVICE, (WPARAM)dc, lLineWidth);
	}

	// ��������
	long StreamIn(int nFormat, EDITSTREAM &es) {
		return (long)::SendMessage(m_Hwnd, EM_STREAMIN, nFormat, (LPARAM)&es);
	}

	// ��������
	long StreamOut(int nFormat, EDITSTREAM &es) {
		return (long)::SendMessage(m_Hwnd, EM_STREAMOUT, nFormat, (LPARAM)&es);
	}

	// ��ȡ�ı�����
	long GetTextLength() const {
		return (long)::SendMessage(m_Hwnd, WM_GETTEXTLENGTH, NULL, NULL);
	}

	BOOL GetText(CString& String)
	{
		BOOL Ret = FALSE;
		long nChar = GetTextLength();
		if (nChar)
		{
			nChar += 2;
			LPWSTR Buffer = new WCHAR[nChar];
			if (Buffer)
			{
				RtlZeroMemory(Buffer, nChar*2);
				int rChar =GetWindowText(m_Hwnd, Buffer, nChar+1);
				if (rChar > 0)
				{
					String = Buffer;
					Ret = TRUE;
				}
			}
			delete Buffer;
		}
		
		return Ret;
	}
};

class C32RichEditCtrlEx : public C32RichEditCtrl
{
	static LRESULT CALLBACK LinkHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		ENLINK* pEnLink = (ENLINK*)lParam;
		if (message == WM_NOTIFY && pEnLink->msg == EN_LINK && pEnLink->msg == ENM_LINK) {
			SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
			sei.fMask = SEE_MASK_NOCLOSEPROCESS;
			sei.lpVerb = L"open";
			sei.lpFile = (LPCTSTR)pEnLink->lParam;
			ShellExecuteEx(&sei);
		}
		return 0;
	}

public:
	void AddTextColorLink(const wchar_t* text, BOOL bold, COLORREF color, BOOL isLink = FALSE, const wchar_t* linkUrl = NULL) {
		HWND hRichEdit = m_Hwnd;
		CHARFORMAT2 cf;
		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_LINK;
		SendMessage(m_Hwnd, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

		if (bold) {
			cf.dwEffects |= CFE_BOLD;
		} else {
			cf.dwEffects &= ~CFE_BOLD;
		}
		cf.crTextColor = color;

		if (isLink) {
			cf.dwEffects |= CFE_LINK;
			cf.dwMask |= CFM_LINK;
		} else {
			cf.dwEffects &= ~CFE_LINK;
		}

		SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

		int length = GetWindowTextLength(hRichEdit);
		SendMessage(hRichEdit, EM_SETSEL, length, length);
		SendMessage(hRichEdit, EM_REPLACESEL, FALSE, (LPARAM)text);

		if (isLink && linkUrl != NULL) {
			ENLINK enLink = { 0 };
			enLink.msg = EN_LINK;
			enLink.wParam = TRUE; // LBN_CLICK
			enLink.lParam = (LPARAM)linkUrl;
			SendMessage(hRichEdit, EM_SETEVENTMASK, 0, ENM_LINK);
			SendMessage(hRichEdit, EM_SETTEXTEX, (WPARAM)&cf, (LPARAM)linkUrl); // ��������URL
		}
	}

	void AddTextBlod( const wchar_t* text, BOOL bold) {
		HWND hRichEdit = m_Hwnd;
		CHARFORMAT cf = { 0 };
		cf.cbSize = sizeof(cf);
		cf.dwMask = CFM_BOLD;
		SendMessage(hRichEdit, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

		if (bold) {
			cf.dwEffects |= CFE_BOLD;
		} else {
			cf.dwEffects &= ~CFE_BOLD;
		}
		SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

		int length = GetWindowTextLength(hRichEdit);
		SendMessage(hRichEdit, EM_SETSEL, length, length);
		SendMessage(hRichEdit, EM_REPLACESEL, FALSE, (LPARAM)text);
	}

};



class C32Dialog : public C32Container, public C32DialogEventCallback
{

public:

	static INT_PTR CALLBACK C32DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//C32DbgOutWinowsMsgFilter(uMsg, wParam, lParam, __FUNCTION__);
		C32Dialog * This = (uMsg == WM_INITDIALOG ? (C32Dialog*)lParam : (C32Dialog*)GetWindowLongPtr(hwndDlg, GWLP_USERDATA));
		LPCWSTR Title = (This? This->m_StringText.GetString() : L"NULL");
		ZxDebug((__FUNCTION__"()::Title:%ws uMsg:%s  (%d) wParam: %08x lParam: %08x(%d:%d)\n", \
			Title, C32DbgGetWindowMsgString(uMsg),								\
			 uMsg, wParam,lParam,LOWORD(lParam), HIWORD(lParam)));

		BOOL Handle = FALSE;
		LRESULT lResult = FALSE;
		if (This == NULL)
			return Handle;
		switch(uMsg)
		{
			case C32_WM_CREATE: 
				Handle = This->OnC32Create(wParam, lParam, lResult);
				break;
			case WM_INITDIALOG:
				Handle = This->OnInitDialog(hwndDlg, uMsg, wParam, lParam,lResult);
				break;
			case WM_COMMAND:
				Handle = This->OnCommand(wParam, lParam, lResult);
				break;
			case WM_NOTIFY:
				if (This)
					Handle = This->OnNotify(wParam, lParam, lResult);
				break;
			case WM_NCDESTROY: //��ΪDialog ������WM_NCDESTROY �����ڴ˺����ͷ��ڴ�.
				This->Destroy();
				break;
			/*case WM_NCCALCSIZE:
				Handle = This->OnNcCalcSize(wParam, lParam, lResult);
				return Handle;
			
			case WM_WINDOWPOSCHANGED:
				Handle = This->OnWindowPosChanged(wParam, lParam, lResult);
				break;
			case WM_MOVE:
				Handle = This->OnMove(wParam, lParam, lResult);
				break;*/
			case WM_SIZE:
				Handle = This->OnSize(wParam, lParam, lResult);
				break;	
			case WM_DRAWITEM:
				Handle = This->OnDrawItem(wParam, lParam, lResult);
				break;
			case WM_PAINT:
				Handle = This->OnPaint(wParam, lParam, lResult);
				break;
			case WM_CONTEXTMENU:
				Handle = This->OnContextMenu(wParam, lParam, lResult);
				break;
			case WM_GETMINMAXINFO:
				Handle = This->OnGetMinMaxInfo(wParam, lParam, lResult);
				break;
			case WM_NCLBUTTONDOWN:
				Handle = This->OnNcLButtonDown(wParam, lParam, lResult);
				break;
		
			//�ؼ�����ɫ����
			case WM_CTLCOLORSTATIC:
				Handle = This->OnCtlColorStatic(wParam, lParam, lResult);
				if (Handle == TRUE)
					return (INT_PTR)lResult;
				break;
			case WM_CTLCOLORBTN:
				Handle = This->OnCtlColorBtn(wParam, lParam, lResult);
				if (Handle == TRUE)
					return (INT_PTR)lResult;
				break; 
			case WM_CTLCOLORLISTBOX:
				Handle = This->OnCtlColorListBox(wParam, lParam, lResult);
				if (Handle == TRUE)
					return (INT_PTR)lResult;
				break;
			case WM_CTLCOLOREDIT:
				Handle = This->OnCtlColorEdit(wParam, lParam, lResult);
				if (Handle == TRUE)
					return (INT_PTR)lResult;
				break;
			case WM_CTLCOLORDLG:
				Handle = This->OnCtlColorDlg(wParam, lParam, lResult);
				if (Handle == TRUE)
					return (INT_PTR)lResult;
				break;
			
				
		}
		//�����ڶԻ�������д������Ϣ�ķ���ֵ��
		if (Handle)
		{
			SetWindowLongPtr(This->m_Hwnd, C32DWL_MSGRESULT, lResult);
		}
		return (INT_PTR)Handle;
	}
	static HINSTANCE hInstance;

public:
	
public:

	C32Dialog()
	{
		m_CtrlType = C32CtrlTypeDialog;
		InitDialog();
	}

	virtual ~C32Dialog()
	{
		ZxDebugEx((__FUNCTION__"():: m_Hwnd: %p Title: %ws \n", m_Hwnd, m_StringText.GetString()));
		C32SetUserData(*this, NULL);
	}

public:
	VOID CloseDialog()
	{
		if (m_bModelLess == TRUE)
			DestroyWindow(m_Hwnd);
		else
			EndDialog(m_Hwnd, 0);
	}

public:
	HWND Create(int ResourceId, HWND hwndParent, BOOL bModeless = FALSE)
	{
		INT_PTR Ret = 0;
		m_bModelLess =bModeless;
		if (bModeless == TRUE)
		{
			CreateDialogParam(C32Dialog::hInstance,
				MAKEINTRESOURCE(ResourceId), 
				hwndParent, C32Dialog::C32DialogProc, (LPARAM)this);
			if (m_Hwnd)
			{
				ShowWindow(m_Hwnd, SW_SHOW);
			}

		}else
		{
			Ret = DialogBoxParam(C32Dialog::hInstance,
				MAKEINTRESOURCE(ResourceId), 
				hwndParent, C32Dialog::C32DialogProc, (LPARAM)this);
		}
		
		ZxDebugEx((__FUNCTION__"():: m_Hwnd : %p Error %d Title: %ws\n", m_Hwnd, GetLastError(), this->GetText()));
		return m_Hwnd;
	}

	BOOL WaitCreate()
	{
		ZxDebugEx((__FUNCTION__"():: \n"));
		do 
		{
			if (GetHwnd())
				break;
			Sleep(50);
		} while (TRUE);

		return TRUE;
	}

public:
	VOID SetReturnValue(LRESULT lResult)
	{
		 SetWindowLongPtr(m_Hwnd, DWLP_MSGRESULT, lResult);
	}

	VOID Close()
	{
		CloseDialog();
	}

	virtual VOID Destroy()
	{
		LRESULT lResult = 0;
		ZxDebugEx((__FUNCTION__"():: \n"));
		if (m_OnDestroy)
			m_OnDestroy(lResult, this);
		if (m_bModelLess && m_IsDelete == TRUE)
		{
			delete this;
		}
	}

	DWORD GetSystemFontCxy()
	{
		return GetDialogBaseUnits();
	}
	
	static BOOL EnumChildProcSetFont(_In_ HWND   hwnd, _In_ LPARAM lParam)
	{
		SetWindowFont(hwnd, (HFONT)lParam, TRUE);
		return TRUE;
	}
	

	BOOL SetChildWindowsFont(HFONT hFont)
	{
		return EnumChildWindows(m_Hwnd, EnumChildProcSetFont, (LPARAM)hFont);
	}
public: // Windows Message
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		(hwndDlg),(uMsg),(DefautFocusHwnd),(InitParam);
		lResult = TRUE;
		this->SetUserData();
		Attach(hwndDlg);
		Handle = this->OnInitDialog();
		if (m_OnCreate)
			m_OnCreate(lResult, this);
		if(this->IsCenter())
			this->SetCenterPos(this->m_Parent);
		return Handle;
	}

	virtual BOOL CALLBACK OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 1;
		ZxDebug((__FUNCTION__"()::WM_COMMAND: wParam: 0x%08x lParam: %p\n", wParam,lParam));
		if (this->m_MinCx !=0 && this->m_MinCy != 0)
		{
			LPMINMAXINFO lpmmi = (LPMINMAXINFO)lParam;
			lpmmi->ptMinTrackSize.x = this->m_MinCx;
			lpmmi->ptMinTrackSize.y = this->m_MinCy;
			lResult = 0;
		}
		
		return Handle;
	}
	
	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		ZxDebug((__FUNCTION__"()::WM_COMMAND: wParam: %p lParam: %p\n", wParam,lParam));

		if (HIWORD(wParam) == 0ULL && lParam == 0ULL )
		{
			Handle = OnCommandMenu(wParam, lParam, lResult);
		}else if (HIWORD(wParam) == 1ULL && lParam == 0ULL)
		{
			Handle = OnCommandAccelerator(wParam, lParam, lResult);
		}else //Control Command
		{
			HWND HwndControl = (HWND)lParam;
			C32ContainerCallOnXyz(HwndControl, OnCommand);
		}
		return Handle;
	}
	
	virtual BOOL OnCommandMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		BOOL Handle = FALSE;
		if (m_OnCommandMenu)
			Handle = m_OnCommandMenu(C32CommandMenuId(wParam), lResult, this);
		else
		{
			if (C32CommandMenuId(wParam) == IDCANCEL)
			{
				Close();
				Handle = TRUE;
			}

		}
		return Handle;
	}

	virtual BOOL OnCommandAccelerator(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		return FALSE;
	}

	virtual BOOL OnCommandControl(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		return FALSE;
	}

	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		int Cx = GET_X_LPARAM(lParam);
		int Cy = GET_Y_LPARAM(lParam);
		HDWP hdwp = BeginDeferWindowPos((int)m_List.GetCount());
		assert(hdwp);
		
		for(size_t i = 0; i < m_List.GetCount(); i++)
		{
			if (m_List[i]->m_PosVisible == FALSE)
				continue;

			m_List[i]->GetPos();
			m_List[i]->m_SizeWindow.cx = Cx;
			m_List[i]->m_SizeWindow.cy = Cy;
			POINT Pt = {};
			SIZE  Size={};
			C32String xx = m_List[i]->GetText();
			m_List[i]->CalPosSize(Pt, Size);
			C32DbgOutRect(m_List[i]->m_Rect,"m_Rect");
			C32DbgOutRect(m_List[i]->m_ClientRect,"m_ClientRect");
			
			C32DbgOutRect(m_List[i]->m_Content,"m_Content");
			C32DbgOutRect(m_List[i]->m_Margin, "m_Margin");

			DWORD Flag = SWP_NOZORDER | m_List[i]->m_SwpFlag;
			hdwp = DeferWindowPos(hdwp, *m_List[i], 0,  Pt.x, Pt.y, Size.cx, Size.cy, Flag);
			assert(hdwp);
	
			m_List[i]->OnSize(wParam, (LPARAM)MAKELONG(Size.cx, Size.cy), lResult);
			if(m_List[i]->IsButton())
			{
				m_List[i]->RedrawWindow32();
			}
		}
		EndDeferWindowPos(hdwp); 
		return FALSE;
	}

	virtual BOOL CALLBACK OnMouseMove(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
	
		int xPos = GET_X_LPARAM(lParam); 
		int yPos = GET_Y_LPARAM(lParam);
		POINT Point = {xPos, yPos};
		ZxDebug((__FUNCTION__"():: {%d, %d} \n", xPos, yPos));
		for (int i = 0; i < (int)m_List.GetCount(); i++)
		{
			if (m_List[i]->m_CtrlType == C32CtrlTypeButton)
			{
				CString CtrlText = m_List[i]->GetText();
				RECT Rect = m_List[i]->GetContentRect();

				//Ҫ������߿�Ŀ�� 1PX
				InflateRect(&Rect, 1, 1);
				if(PtInRect(&Rect, Point))
				{
					Handle = TRUE;
					lResult = 0;
					HCURSOR hCursor  = LoadCursor(NULL, IDC_HAND); 
					SetCursor(hCursor);
										
					ZxDebugEx((__FUNCTION__"():: %ws {%d, %d, %d, %d}\n", CtrlText.GetString(),Rect.left , Rect.top, Rect.right, Rect.bottom));
					break;
				}
			}
		}

		return Handle;
	}

	virtual BOOL CALLBACK OnWindowPosChanged(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 1;
		SetReturnValue(0);
		LPWINDOWPOS lpwpos = (LPWINDOWPOS)lParam;
		ZxDebug((__FUNCTION__"():: LPWINDOWPOS {%d %d %d %d} 0x%08x (hwnd:%p : after:%p)\n", lpwpos->x, lpwpos->y, lpwpos->cx, lpwpos->cy, lpwpos->flags, lpwpos->hwnd, lpwpos->hwndInsertAfter));
		
		return FALSE;
	}

	virtual BOOL CALLBACK OnNcCalcSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		LPNCCALCSIZE_PARAMS lpncp = NULL;
		BOOL Handle = FALSE;
		lResult = 1;
		
		if (wParam == TRUE)
		{
			
			lpncp = (LPNCCALCSIZE_PARAMS)lParam;
		}


		return Handle;
	}
	
	virtual BOOL CALLBACK OnNcPaint(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 1;
		SetReturnValue(0);
		
		return FALSE;
	}

	virtual BOOL CALLBACK OnPaint(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 1;
		SetReturnValue(0);

		return FALSE;
	}
	
	virtual BOOL CALLBACK OnCtlColorDlg(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HDC  Hdc = (HDC)wParam;
		HWND Hwnd = (HWND)lParam;
		lResult = 0;
		if (C32ThemeStyle::IsThemeStyleDark() /*&& IsUseColor()*/)
		{
			Handle = TRUE;
			m_ColorMask = C32UICOLOR_ALL;
			//�������ֱ���ɫ,�����ÿؼ�����ɫ����Ч
			if(IsUseFontBkGnd())
				SetBkColor(Hdc, C32ThemeStyle::m_ColorFontBk);

			//����������ɫ
			if (IsUseFont())
				SetTextColor(Hdc, C32ThemeStyle::m_ColorFont);

			SetBkMode(Hdc, m_ColorMode);
			//���û��ƾ�̬�ؼ������Ļ��ʵľ������Ϊ OPAQUE :���������ֱ���ɫ������Ϊ��ɫ.
			if (IsUseBkGnd())
				lResult = (LRESULT)C32ThemeStyle::m_HbrBkGnd;
		}


		return Handle;
	}

	virtual BOOL CALLBACK OnNcLButtonDown(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		if (m_DrawFullWindowsFlag)
		{
			DragFullWindows();
			lResult = 0;
		}

		return FALSE;
	}

public:
	operator HWND() const
	{
		return m_Hwnd;
	}

public:
	virtual BOOL  OnInitDialog()
	 {
		return TRUE;
	 }
	
	VOID InitDialog()
	{
		m_bModelLess = FALSE;
		m_IsCenter = TRUE;
	}

	VOID SetModalType(BOOL ModelLess = FALSE)
	{
		m_bModelLess = ModelLess;
	}

	VOID SetCenter(BOOL IsCenter = TRUE)
	{
		m_IsCenter = IsCenter;
	}
	BOOL IsCenter()
	{
		return m_IsCenter;
	}


public:
	BOOL   m_bModelLess;
	BOOL   m_IsCenter;
};

class C32Explorer : public C32Container
{
public:

	static HINSTANCE hInstance;

	static DWORD RegisterClass()
	{
		HCURSOR hCursor	= (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZEWE), IMAGE_CURSOR, 0 , 0, LR_SHARED);
		DWORD Atom = RegisterClassEx32(C32_WC_EXPLORER, NULL, hCursor);

		return Atom;
	}

	static VOID Initialize()
	{
		//ע��C32Explore��
		RegisterClass();

	}

public:
	C32Explorer(){}
	~C32Explorer(){};


public:

	BOOL CALLBACK OnCreate(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = TRUE;
		C32SetHandleLReslut(TRUE, 0);

		LPCREATESTRUCT Cs = (LPCREATESTRUCT)lParam;

		C32Explorer* This = (C32Explorer*)Cs->lpCreateParams;
		Handle = This->OnCreate(Cs);

		return Handle;
	}

	virtual BOOL CreateExplorer(RECT& TreeRt, RECT& ListRt)
	{

		CreateTreeCtl(TreeRt);
		CreateListCtl(ListRt);
		CreateStatusCtl();
		return NULL;
	}

	virtual BOOL CreateTreeCtl(RECT& TreeRt)
	{
		DWORD Style = WS_CHILD | WS_VISIBLE;
		Style |= TVS_LINESATROOT  | TVS_HASBUTTONS | TVS_FULLROWSELECT|TVS_DISABLEDRAGDROP;
		Style |= TVS_TRACKSELECT ;
		m_Tree.Create(0, Style,
			TreeRt.left, TreeRt.top, C32GetRectWidth(TreeRt), C32GetRectHeight(TreeRt), 
			(HWND)m_Hwnd);

		m_Tree.SetSubclass();
		m_Tree.SetExplorerTheme();
		m_Tree.m_ImageListNormal.CreateNormal();
		m_Tree.m_ImageListState.CreateNormal();

		return TRUE;
	}

	virtual BOOL CreateListCtl(RECT& Rt)
	{
		DWORD Style = WS_CHILD | WS_VISIBLE;
		Style |=   LVS_REPORT ;
		m_List.Create(0, Style,
			Rt.left, Rt.top, C32GetRectWidth(Rt), C32GetRectHeight(Rt), 
			(HWND)m_Hwnd);
		m_List.SetSubclass();
		m_List.SetExplorerTheme();

		//m_Tree.SetExtendedStyles();
		return TRUE;
	}

	virtual BOOL CreateStatusCtl()
	{
		DWORD Style3 = WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP | SBARS_TOOLTIPS ;
		m_Status.CreateStatus(0, Style3, (HWND)m_Hwnd);
		m_Status.GetPos();
		return TRUE;
	}

	virtual HWND CreateExplorer(HWND Parent, int X, int Y, int Cx, int Cy)
	{
		m_Parent = Parent;

		DWORD ExStyle = 0;
		DWORD Style =  WS_CHILD | WS_VISIBLE;
		HWND hwnd = CreateWindowEx(ExStyle, C32_WC_EXPLORER, L"C32Explorer", Style,
			X, Y, Cx, Cy,
			Parent, (HMENU)NULL, hInstance, (LPVOID)this);

		DWORD Error = GetLastError();
		m_Hwnd = hwnd;
		SetWindowLongPtr(m_Hwnd, GWLP_USERDATA, (LONG_PTR)this);
		return hwnd;
	}

public:
	virtual BOOL OnCreate(LPCREATESTRUCT Cs)
	{
		RECT RcTree = {0, 0, m_Tree.m_Cx, Cs->cy};
		RECT RcList = {m_Tree.m_Cx, 0, Cs->cx - m_Tree.m_Cx, Cs->cy};
		
		CreateTreeCtl(RcTree);
		CreateListCtl(RcList);
		CreateStatusCtl();

		
		AddC32Window(&m_Tree);
		AddC32Window(&m_List.m_Header);
		AddC32Window(&m_List);
		AddC32Window(&m_Status);

		return TRUE;

	}

	virtual BOOL OnDestroy()
	{
		return TRUE;
	}


	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle;
		C32SetHandleLReslut(TRUE, 0);

		if(IsIconic(m_Hwnd)) // ��С��
			return Handle;

		DWORD Type = (DWORD)wParam;
		int Cx = GET_X_LPARAM(lParam);
		int Cy = GET_Y_LPARAM(lParam);
		// m_Hwnd.SetPos(0, 0, Cx, Cy);
		//// �����б�ָ���10
		// m_Tree.m_Hwnd.SetPos(0,0,m_Tree.m_Hwnd.m_Cx, Cy - m_Status.m_Hwnd.m_Cy);
		// m_Tree.m_Hwnd.GetPos();

		// m_List.m_Hwnd.SetPos(m_Tree.m_Hwnd.m_Cx+10,0,Cx - m_Tree.m_Hwnd.m_Cx-10, Cy - m_Status.m_Hwnd.m_Cy);
		// m_List.m_Hwnd.GetPos();
		// 
		// m_Status.m_Hwnd.SetPos(0,m_Tree.m_Hwnd.m_Cy, Cx, m_Status.m_Hwnd.m_Cy);
		// m_Status.m_Hwnd.GetPos();

		//InvalidateRect(m_Hwnd,NULL, TRUE);
		//RedrawWindow(m_Hwnd, )
		HDWP hdwp = BeginDeferWindowPos(3);
		SetPos(0, 0, Cx, Cy);

		DeferWindowPos(hdwp, m_Tree, NULL,0,0,m_Tree.m_Cx, Cy - m_Status.m_Cy, SWP_NOZORDER);
		DeferWindowPos(hdwp, m_List, NULL,m_Tree.m_Cx+10,0,Cx - m_Tree.m_Cx-10, Cy - m_Status.m_Cy, SWP_NOZORDER);
		DeferWindowPos(hdwp, m_Status, NULL,0,Cy-m_Status.m_Cy, Cx, m_Status.m_Cy, SWP_NOZORDER);
		EndDeferWindowPos(hdwp);
		m_List.GetPos();
		m_Status.GetPos();

		GetPos();
		m_Tree.GetPos();

		return Handle;
	}

	virtual BOOL CALLBACK OnLButtonUp(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = TRUE;
		C32SetHandleLReslut(TRUE, 0);

		lResult = 0;
		DWORD Type = (DWORD)wParam;
		int xCursor = GET_X_LPARAM(lParam);
		int yCursor = GET_Y_LPARAM(lParam);
		m_Tree.m_Cx = xCursor;

		SendMessage((HWND)m_Hwnd, WM_SIZE, (WPARAM)-1, (LPARAM)MAKELPARAM(m_ClientCx, m_ClientCy));
		ReleaseCapture();

		return Handle;
	}
	
	//If an application processes this message, it should return zero
	virtual BOOL CALLBACK OnLButtonDown(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 0;

		SetCapture(m_Hwnd);
		
		return Handle;
	}


public:
	int m_CxMin; 

public:
	C32TreeView m_Tree;
	C32ListView m_List;
	C32StatusBar m_Status;
};

class C32Progress : public C32Window
{
static HINSTANCE hInstance;
public:
	C32Progress()
	{
		m_Range.iLow = 0;
		m_Range.iHigh = 100;
		m_Step = 1;
	}
	HWND Create(HWND Parent, 
				int X, int Y, int Cx, int Cy,
				DWORD dwStyle = PBS_MARQUEE)
	{
		dwStyle |= WS_CHILDWINDOW | WS_VISIBLE;

		HWND Hwnd = CreateWindowEx(0, PROGRESS_CLASS, L"C32ProgressBar", dwStyle, 
						X, Y, Cx, Cy,
						Parent,
						(HMENU)NULL,
						hInstance, this);
		m_Hwnd = Hwnd;
		C32GetLastError();
		return Hwnd;
	}


	

	int SetStatus(int iStatus)
	{
		return (int)SendMessage(m_Hwnd,PBM_SETSTATE,(WPARAM)iStatus,0);
	}

	int SetRange(int iLow, int iHigh)
	{
		m_Range.iLow = iLow;
		m_Range.iHigh = iHigh;

		return (int)SendMessage(m_Hwnd, PBM_SETRANGE, 0, MAKELPARAM(iLow, iHigh));
	}

	int SetPos(int iPos)
	{
		if (iPos < m_Range.iLow)
			iPos = m_Range.iHigh;
		else if(iPos > m_Range.iHigh)
			iPos = m_Range.iHigh;

		m_Pos = iPos;

	 return (int)SendMessage(m_Hwnd, PBM_SETPOS, (WPARAM)iPos, NULL);
	}

	int SetStep(int iStep)
	{
		m_Step = iStep;
		
		return (int)SendMessage(m_Hwnd, PBM_SETSTEP, (WPARAM)iStep, 0);
	}

	int NextStep()
	{
		return (int)SendMessage(m_Hwnd, PBM_STEPIT, 0, 0);
	}
	
	DWORD SetStyle(DWORD Style = PBS_SMOOTH)
	{
		//Style = ;
		return (DWORD)SetWindowLong(m_Hwnd, GWL_STYLE, Style);
	}

	VOID SetMarqueem()
	{
		SendMessage(m_Hwnd, PBM_SETMARQUEE, TRUE, 30);
	}

public:
	int      m_Pos;
	int	     m_Step;
	PBRANGE  m_Range;
	

	
};

class C32DialogProgress : public C32Window
{
public:
	static HINSTANCE hInstance;
	static INT_PTR WINAPI C32DialogProgressProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		INT_PTR Ret = 0;
		C32DialogProgress* This = (C32DialogProgress*)GetWindowLongPtr(hDialog, GWLP_USERDATA);
		if (This == NULL)
			This = (C32DialogProgress*)lParam;
		switch(uMsg)
		{
		case WM_INITDIALOG:
			This->Init(hDialog);
			break;
		case WM_COMMAND:
			 switch(LOWORD(wParam))
			 {
				case IDOK:
					This->OnClickOk();
					break;
				case IDCANCEL:
					This->OnClickCancel();
					EndDialog(hDialog, 0);
					break;
			 }
			 break;

		}

		return Ret;
	}

	virtual BOOL OnDestroy()
	{
		return TRUE;
	}

	C32DialogProgress()
	{
		InitText();
	}

	C32DialogProgress(DWORD dwProgressStyle)
	{
		//SetCtrlText();
		InitText();
	}

	C32DialogProgress(LPCWSTR DialogText, 
						LPCWSTR OKText = L"��ͣ", 
						LPCWSTR CancelText = L"ֹͣ")
	{
		InitText();
		SetCtrlText(DialogText, OKText, CancelText);
	}

	~C32DialogProgress()
	{

	}
public:
	
	VOID Create(HWND Parent)
	{
		m_Parent = Parent;
		DialogBoxParam(hInstance, 
			MAKEINTRESOURCE(IDD_DIALOG_C32CLASS_PROGRESS), 
			Parent,
			C32DialogProgress::C32DialogProgressProc, 
			(LPARAM)this);
	}

	virtual VOID Init(HWND hDialog)
	{
		Attach(hDialog);
		SetUserData();
		HWND Ok = GetDlgItem(hDialog, IDOK);
		HWND Cancel = GetDlgItem(hDialog, IDCANCEL);
		HWND Progress = GetDlgItem(hDialog, IDC_PROGRESS);

		m_ProBar.Attach(Progress);
		m_ProBar.SetStyle(PBS_MARQUEE| WS_CHILD|WS_VISIBLE);
		m_ProBar.SetMarqueem();
		m_Ok.Attach(Ok);
		m_Cancel.Attach(Cancel);
		if (m_OkText)
			m_Ok.SetText(m_OkText);
		if (m_CancelText)
			m_Cancel.SetText(m_CancelText);

		SetCenterPos(this->m_Parent);
	}
	
	VOID SetCtrlText(LPCWSTR DialogText = L"����չʾ", 
		LPCWSTR OKText = L"��ͣ", 
		LPCWSTR CancelText = L"ֹͣ")
	{
		m_Title = DialogText;
		m_OkText = OKText;
		m_CancelText = CancelText;

	}

	VOID InitText()
	{
		m_OkText = NULL;
		m_CancelText = NULL;
		m_Title = NULL;
	}

public:
	virtual BOOL OnClickOk()
	{
		ZxDebug((__FUNCTION__"():: \n"));
		return TRUE;
	}

	virtual BOOL OnClickCancel()
	{
		return TRUE;
	}

	C32Progress m_ProBar;
	C32Button m_Ok;
	C32Button m_Cancel;

	LPCWSTR   m_OkText;
	LPCWSTR   m_CancelText;

	LPCWSTR   m_Title;
};

/*
	@brief: 
	�Ի����������button��һ����������
	�ṩ��ͣ�������Ȳ�����
*/
class C32DialogSyn : public C32Dialog
{
public:
	 enum ETaskState
	{
		ETaskStateStart,
		ETaskStateRunning,
		ETaskStatePause,
		ETaskStateClose,
	};
	/*C32DialogSyn()
	{

	}	
	*/
	C32DialogSyn(LPCWSTR Title = L"���������ʾ", 
				LPCWSTR OkText = L"��ͣ", 
				LPCWSTR CancelText = L"ȡ��",
				C32_EVENT_CALLBACK_BUTTON_CLICK BtnEventClickOk = NULL,
				C32_EVENT_CALLBACK_BUTTON_CLICK BtnEventClickCancel = NULL,
				C32_EVENT_CALLBACK_BUTTON_CLICK BtnEventClickClose = NULL,
				PVOID Context = NULL)
	{
		m_TitelText = Title;
		m_BtnOkText = OkText;
		m_BtnCancelText = CancelText;
		m_BtnOk.SetEventClick(BtnEventClickOk);
		m_BtnCancel.SetEventClick(BtnEventClickCancel);
		m_BtnClose.SetEventClick(BtnEventClickClose);
		m_TaskState = ETaskStateStart;
		m_Context = Context;
	}


	virtual ~C32DialogSyn()
	{

	}

	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		C32Dialog::OnInitDialog(hwndDlg, uMsg, DefautFocusHwnd, InitParam, lResult);

		//��ʼ���ؼ�
		InitC32Ctrl(hwndDlg);

		if (!m_BtnOk.IsVisibleM())
			m_BtnOk.SetVisible(FALSE);

		SetCenterPos(m_Parent);

		m_Event.Set();

		return TRUE;
	}

	VOID InitC32Ctrl(HWND hwndDlg)
	{
		HWND Ok = GetDlgItem(hwndDlg, IDD_DIALOG_C32_CLASS_PROGRESS_OK);
		HWND Cancel = GetDlgItem(hwndDlg, IDD_DIALOG_C32_CLASS_PROGRESS_CANCEL);
		HWND Close = GetDlgItem(hwndDlg, IDCANCEL);
		HWND Progress = GetDlgItem(hwndDlg, IDC_PROGRESS);

		m_Progress.Attach(Progress);
		m_Progress.SetStyle(PBS_MARQUEE| WS_CHILD|WS_VISIBLE);
		m_Progress.SetMarqueem();

		m_BtnOk.Attach(Ok);
		m_BtnCancel.Attach(Cancel);

		m_BtnOk.SetText(m_BtnOkText);
		m_BtnCancel.SetText(m_BtnCancelText);
		SetText(m_TitelText);

		m_BtnClose.Attach(Close);
		AddC32Window(&m_BtnClose);
		AddC32Window(&m_Progress);
		AddC32Window(&m_BtnOk);
		AddC32Window(&m_BtnCancel);
		AddC32Window(&m_BtnClose);
		
		

	}

	static DWORD WINAPI ThreadCreateDialog(LPVOID Parameter)
	{
		
		C32DialogSyn* This = (C32DialogSyn*)Parameter;
		BOOL Ret = IsGUIThread(TRUE);
		ZxDebugEx((__FUNCTION__"():: IsGuiThread: %d\n", Ret));
		This->Create(IDD_DIALOG_C32CLASS_PROGRESS, This->m_Parent);
		return 0;
	}

	BOOL CreateThreadDialog(HWND hwndOwner)
	{
		m_Parent = hwndOwner;
		m_Event.Create(FALSE);
		m_ThreadGui.Create(C32DialogSyn::ThreadCreateDialog, this);
		SetTaskStateRunning();

		//m_Thread.Wait();
		ZxDebugEx((__FUNCTION__"():: \n"));
		return TRUE;
	}

	VOID SetTaskState(ETaskState State)
	{
		m_TaskState = State;
	}

	VOID SetTaskStateRunning()
	{
		m_TaskState = ETaskStateRunning;
	}

	VOID SetTaskStateClose()
	{
		m_TaskState = ETaskStateClose;
	}

	BOOL IsTaskStateClose()
	{
		return (m_TaskState == ETaskStateClose);
	}

public:
	C32Button  m_BtnOk;
	C32Button  m_BtnCancel;
	C32Button  m_BtnClose;

	C32Progress  m_Progress;
	C32String    m_BtnOkText;   
	C32String    m_BtnCancelText;
	C32String    m_TitelText;

	C32SynEvent m_Event;       //�¼�ͬ�����ݶ������˳�...
	C32SynThread m_Thread;     //�����̡߳�
	C32SynThread m_ThreadGui; //�ڴ��߳��д���Dialog
	ETaskState   m_TaskState;

	PVOID   m_Context; //ͬ��Dialog������Ϣ��
};

class C32DialogSynCancel : public C32DialogSyn
{
public:
	C32DialogSynCancel(LPCWSTR Title = L"���������ʾ", 
		C32_EVENT_CALLBACK_BUTTON_CLICK BtnEventClickCancel = NULL,
		C32_EVENT_CALLBACK_BUTTON_CLICK BtnEventClickClose = NULL)
	{
		m_BtnOk.SetVisibleM(FALSE);
		m_BtnCancelText = L"ȡ��";
		m_BtnCancel.SetEventClick(BtnEventClickCancel);
		m_BtnClose.SetEventClick(BtnEventClickClose);
	}
	
	~C32DialogSynCancel()
	{


	}




};


/*
	@brief: ����ʾһ���ȴ������Ի��򣬸öԻ����ɴ���Create������EndDialog�����ṩ�κε��������
	����:ִ��ĳЩ����������Ҫһ��ʱ�䣬Ϊ��ȷ���ò������֮���û����ܽ�����һ�β����������ṩ���ࡣ
	ʹ�÷�����
		����Ҫ��ʱ�������ɵĺ�����ֱ�ӵ��� C32DialogSynSimple xx;����
	
	
*/
class C32DialogSynSimple : public C32DialogSyn
{
public:
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		C32DialogSyn::OnInitDialog(hwndDlg, uMsg, DefautFocusHwnd, InitParam, lResult);
		SetText(L"�����ĵȴ�...");
		m_BtnOk.SetVisible(FALSE);
		m_BtnCancel.SetVisible(FALSE);
		Disable();
		m_Event.Set();
		return TRUE;
	}

	C32DialogSynSimple()
	{
		CreateThreadDialog(C32Hwnd);
	}

	~C32DialogSynSimple()
	{
		m_Event.WaitFor();
		CloseDialog();
	}


};

class C32DialogSearch : public C32Dialog
{

public:
	C32DialogSearch()
	{
		m_DbgOnSizeCount = 0;
	}
	~C32DialogSearch()
	{

	}

public:
	
	 virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  FocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		
		BOOL Handle = FALSE;
		HWND hwndCombo = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_COMBO);
		HWND hwndEdit = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_EDIT);
		HWND hwndButton = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_BUTTON);
		HWND hwndGroup = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_GROUP);
		HWND hwndList = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_LIST);

		C32Dialog::OnInitDialog(hwndDlg, uMsg, FocusHwnd,InitParam, lResult);
		m_ComboBox.Attach(hwndCombo);
		m_Edit.Attach(hwndEdit);
		m_Button.Attach(hwndButton);
		m_Group.Attach(hwndGroup);
		m_LV.Attach(hwndList);


		m_ComboBox.SetItemHeight(38);
		//m_Button.SetEventClick(OnSearchClick);
		
		m_List.Add(&m_ComboBox);
		m_List.Add(&m_Edit);
		m_List.Add(&m_Button);
		m_List.Add(&m_LV);
		
		SetText(L"C32���ҶԻ���");
		GetPos();
		SetMinCxy(m_ClientCx, m_ClientCy);
		
		SetCenterPos(GetParent(m_Hwnd));
		if (m_OnInitDialog)
			Handle = m_OnInitDialog(this);

		return Handle;
	}
	 
	

public: // WindowsMessage

	
	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
	
		int Cx = GET_X_LPARAM(lParam);
		int Cy = GET_Y_LPARAM(lParam);
		if (Cx <= m_MinCx && Cy <= m_MinCy)
			return FALSE;
		
		GetPos();
		
		RECT GroupRc = m_Group.GetContentRect();
		m_Group.SetPos(0, 0, Cx - GroupRc.left*2 , m_Group.m_Cy, SWP_NOZORDER | SWP_NOMOVE);
		 GroupRc = m_Group.GetContentRect();
		// combo box ����
		m_ComboBox.SetPos(0, 0, 0,0, SWP_NOZORDER | SWP_NOMOVE| SWP_NOSIZE);
		RECT CommboRc = m_ComboBox.GetContentRect();

		RECT ButtonRc = m_Button.GetContentRect();
		
		int BtnX = m_ClientRect.right - C32GetRectWidth(ButtonRc) -  GroupRc.left - 10;
		m_Button.GetContentRect();
		m_Button.SetPos(BtnX, ButtonRc.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		ButtonRc = m_Button.GetContentRect();

		RECT EditRc = m_Edit.GetContentRect();
		int EditCx = BtnX - EditRc.left -20 ;
		m_Edit.SetPos(0, 0,  EditCx, m_Edit.m_Cy, SWP_NOZORDER | SWP_NOMOVE);

		RECT LvRc = m_LV.GetContentRect();
		
		m_LV.SetPos(0, 0,  m_Group.m_Cx, Cy - LvRc.top-80, SWP_NOZORDER | SWP_NOMOVE);


		return TRUE;
	}

	virtual BOOL CALLBACK OnMove(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		/*if (Cx <= m_MinCx && Cy <= m_MinCy)
			return TRUE;*/
		m_ComboBox.GetPos();
		

		return TRUE;
	}

	virtual BOOL CALLBACK OnNcCalcSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		LPNCCALCSIZE_PARAMS lpncp = NULL;
		BOOL Handle = FALSE;
		lResult = 1;
		SetReturnValue(0);
		if (wParam == TRUE)
		{
			lpncp = (LPNCCALCSIZE_PARAMS)lParam;
			SetReturnValue(WVR_VALIDRECTS);
			
		}
		
		
		return FALSE;
	}

	
public:
	C32ComboBox m_ComboBox;
	C32Edit		m_Edit;
	C32Button   m_Button;
	C32ListView m_LV;
	C32GroupBox    m_Group;

	int         m_DbgOnSizeCount;

};


/*
	���ļ��������ļ��Ի���
*/

class C32DialogFile
{
public:
	enum eFileDialogType
	{
		FILE_DIALOG_OPEN,
		FILE_DIALOG_SAVE,
	};

public:
	C32DialogFile():m_Type(FILE_DIALOG_OPEN)
	{
		Init();
	}

	C32DialogFile(eFileDialogType Type):
	m_Type(Type)
	{
		Init();
	}

	virtual ~C32DialogFile()
	{

	}

	// OK button, the return value is nonzero
	// cancels or closes the Open dialog box or an error occurs
	//TRUE : Ok
	//FALSE: Cancel or close
	virtual BOOL Show()
	{
		int ret;
		if (m_Type == FILE_DIALOG_OPEN)
		{
			ret = GetOpenFileName(&m_File);
		}else
		{
			ret = GetSaveFileName(&m_File);
		}
		ZxDebug(("m_Path: %ws \n", m_String.GetString()));
		return !!(ret);
	}

	virtual BOOL Show(LPCWSTR Title, LPCWSTR Filter = NULL, LPCWSTR Directory = NULL)
	{
		m_File.lpstrTitle = (LPWSTR)Title;
		m_File.lpstrInitialDir = Directory;
		m_File.lpstrFilter = (LPWSTR)Filter;
		m_File.nFilterIndex = 1;

		return Show();
	}

	virtual BOOL Open(LPCWSTR Title, LPCWSTR Filter = NULL, LPCWSTR Directory = NULL)
	{
		m_Type = FILE_DIALOG_OPEN;
		return Show(Title, Filter, Directory);
	}

	virtual BOOL Save(LPCWSTR Title, LPCWSTR Filter = NULL, LPCWSTR Directory = NULL)
	{
		m_Type = FILE_DIALOG_SAVE;
		return Show(Title, Filter, Directory);
	}

	VOID Init()
	{
		m_Filter = NULL;
		RtlZeroMemory(&m_File, sizeof(OPENFILENAME));
		m_String.AssignStringW(8192);

		m_File.lStructSize = sizeof(OPENFILENAMEW);
		m_File.hwndOwner = NULL;
		m_File.nMaxFile = 8192;//����������ã������õĻ�������ִ��ļ��Ի���  
		m_File.lpstrFilter = m_Filter;
		m_File.lpstrFile = (LPWSTR)m_String;
		m_File.nFilterIndex = 1;
		m_File.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_NOCHANGEDIR;


	}

public:
	eFileDialogType m_Type;
	OPENFILENAME m_File;
	LPCWSTR  m_Filter;
	C32String m_String;
};

class C32DialogFindReplace
{

public:
	C32DialogFindReplace()
	{
		Init();
	}

	virtual ~C32DialogFindReplace()
	{
		Destroy();
	}
public:

	VOID Init()
	{
		m_bFind = TRUE;
		m_String = new WCHAR[4096];
		RtlZeroMemory(m_String, 4096*2);
		
		m_Parameter = NULL;
		m_FindHwnd = NULL;
		RtlZeroMemory(&m_FindReplace, sizeof(FINDREPLACE));
	}

	VOID Destroy()
	{
		if (m_String)
		{
			delete m_String;
			m_String = NULL;
		}
		m_Parameter = NULL;
	}

	LPWSTR GetFindString()
	{
		return m_String;
	}

	VOID SetFindReplace(HWND hwndOwner, DWORD Flags)
	{
		m_FindReplace.lStructSize = sizeof(FINDREPLACE);
		m_FindReplace.hwndOwner = hwndOwner;
		m_FindReplace.lpstrFindWhat =m_String;
		m_FindReplace.wFindWhatLen = 4096;
		m_FindReplace.Flags = Flags;
	}

	BOOL CreateFind(HWND hwndOwner, DWORD Flags = FR_DOWN|FR_FINDNEXT)
	{
		if (m_String == NULL)
			return FALSE;
		SetFindReplace(hwndOwner, Flags);
		m_FindHwnd = FindText(&m_FindReplace);
		
		return (m_FindHwnd != NULL);
	}
	
	// �ǲ��ҶԻ������滻�Ի���
	VOID SetDialogType(BOOL bFind)
	{
		m_bFind = bFind;
	}

public:
	FINDREPLACE  m_FindReplace; //// must be first data member
	HWND		m_FindHwnd;
	LPWSTR		m_String;
	BOOL		m_bFind;
	PVOID		m_Parameter;
	
};

#define C32GetDialogFindReplace(x) (C32DialogFindReplace*)((PUCHAR)x - sizeof(PVOID));

class C32DialogFindReplaceLv : public C32DialogFindReplace
{
public:
	C32DialogFindReplaceLv()
	{
		m_iFindIndex = -1;
	}

	virtual ~C32DialogFindReplaceLv()
	{


	}

public:
	ULONG_PTR   m_iFindIndex;
	ULONG_PTR   m_iFindSubItem;
	ULONG_PTR   m_iFindSubItemOffset;
};



#define C32DeletePtrInVector(List) \
				{\
					for(size_t i = 0; i < List.GetCount(); i++)\
					{\
						delete List[i];\
						List[i] = NULL;\
					}\
				}

class C32TLvItem
{
public:
	C32TLvItem()
	{
		m_iIcon = 0;
	}
public:
	int m_iIcon;
	CString m_Text;
};

class C32LvItem
{
public:
	C32LvItem()
	{

	}
	~C32LvItem()
	{


	}
public:
	
	VOID DebugThis()
	{
		CString Str;
		for (int i = 0; i < (int)m_List.GetCount(); i++)
		{
			Str += m_List[i].m_Text + L"##";
		}

		ZxDebug((__FUNCTION__"():: %ws \n", (LPCWSTR)Str));

	}

	CString DebugGetLvItemString()
	{
		CString Str;
		for (int i = 0; i < (int)m_List.GetCount(); i++)
		{
			Str += m_List[i].m_Text + L" ";
		}

		return Str;
	}

public:
	CAtlArray<C32TLvItem> m_List; //����������Ϣ��
	int iIndent;
	LPARAM lParam; //Ҫ���������ֵ��

public:
	C32LvItem(__in const C32LvItem& Other)
	{
		operator=(Other);
	}

	C32LvItem& operator=(__in const C32LvItem& Other)
	{
		m_List.Copy(Other.m_List);
		return *this;
	}


};

class C32LvList
{
public:
	C32LvList()
	{

	}
	virtual ~C32LvList()
	{


	}

public:

	int InsertLvItem(int iIndex, C32LvItem& Item)
	{
		if (iIndex > (int)m_List.GetCount())
			return -1;

		m_List.InsertAt(iIndex, Item);

		ZxDebug((__FUNCTION__"():: iIndex = %d \n", iIndex));
		return iIndex;

	}

	int  GetLvItem(LPARAM lParam)
	{
		int iIndex = -1;
		for(int i = 0; i < (int)m_List.GetCount(); i++)
		{
			if (m_List[i].lParam == lParam)
			{
				iIndex = i;
				break;
			}
		}
		return iIndex;
	}

	int  RemoveLvItem(LPARAM lParam)
	{
		int iIndex = -1;
		for(int i = 0; i < (int)m_List.GetCount(); i++)
		{
			if (m_List[i].lParam == lParam)
			{
				iIndex = i;
				break;
			}
		}
		CString lvItemString;
		if (iIndex != -1)
		{
			lvItemString = m_List[iIndex].DebugGetLvItemString();
			m_List.RemoveAt(0 + iIndex);
		}
		ZxDebug((__FUNCTION__"():: iIndex = %d %ws Size: %d\n", iIndex, lvItemString, (int)m_List.GetCount()));

		return iIndex;

	}

	VOID DebugThis()
	{
		for (int i = 0; i < (int)m_List.GetCount(); i++)
		{
			ZxDebug((__FUNCTION__"():: iIndex : %d iIndent : %d  lParam:%p", i, m_List[i].iIndent, m_List[i].lParam));
			m_List[i].DebugThis();

		}
	}


public:
	CAtlArray<C32LvItem> m_List;

public:
	C32LvList(__in const C32LvList& Other)
	{
		operator=(Other);
	}
	C32LvList& operator=(__in const C32LvList& Other)
	{
		m_List.Copy(Other.m_List);

		return *this;

	}
};

class C32TreeNode
{
	#define C32TV_EXPANDED   0x00000001
	#define C32TV_COLLAPSE   0x00000000

public:
	C32TreeNode()
	{
		m_Expanded = C32TV_EXPANDED;
		m_Indent = 0;
		m_lParam = (LPARAM)0;
		m_LvLog = NULL;
		m_ListView = NULL;
	}

	~C32TreeNode()
	{
		C32DeletePtrInVector(m_Child);
		//DeleteNode();
	}

public:
	C32TreeNode(CAtlArray<CString>& StringList, C32LvList* List, C32ListView* ListView,LPARAM lParam = NULL)
	{
		m_Indent = 0;
		m_ItemString.Append(StringList) ;
		m_lParam = lParam;
		m_Indent = 32;
		m_LvLog = List;
		m_ListView = ListView;
		m_Expanded = C32TV_EXPANDED;
	}

public:

	VOID Insert(CAtlArray<CString>& StringList, LPARAM lParam = NULL)
	{
		//���ṹ��ӽڵ�
		C32TreeNode* Node = new C32TreeNode(StringList,m_LvLog, m_ListView, lParam);
		Node->m_Indent = m_Indent + 20;

		//������List ����ڵ�.
		C32LvItem lvItem;
		lvItem.m_List.SetCount(StringList.GetCount());
		for(int i = 0; i < (int)StringList.GetCount(); i++)
		{
			lvItem.m_List[i].m_Text = StringList[i];
		}
		lvItem.lParam = (LPARAM)Node->GetThis();
		lvItem.iIndent = Node->m_Indent;

		int iIndex = m_LvLog->GetLvItem((LPARAM)GetThis());
		if (iIndex == -1)
		{
			iIndex = (int)m_LvLog->m_List.GetCount();
		}else
		{
			iIndex += (int)m_Child.GetCount();
			iIndex++;

		}


		//iIndex++;
		m_LvLog->InsertLvItem(iIndex, lvItem);
		m_Child.Add(Node);

		if (m_ListView)
		{
			m_ListView->InsertItemAsyn(iIndex, lvItem.m_List[0].m_Text, -1, -1);
			for(int i = 0; i < (int)lvItem.m_List.GetCount(); i++)
			{
				
			}
		}

		
	}

	C32TreeNode* GetThis()
	{
		return this;
	}

	CAtlArray<CString>& GetItemString()
	{
		return m_ItemString;
	}

	LPARAM GetlParam()
	{
		return m_lParam;
	}

	CAtlArray<C32TreeNode*>& GetChild()
	{
		return m_Child;
	}


	int InsertLvList(C32TreeNode* ChildNode, int NodeIndex = -1)
	{
		
		C32LvItem lvItem;
		lvItem.m_List.SetCount(ChildNode->m_ItemString.GetCount());
		for(int i = 0; i < (int)ChildNode->m_ItemString.GetCount(); i++)
		{
			lvItem.m_List[i].m_Text = ChildNode->m_ItemString[i];
		}

		lvItem.lParam = (LPARAM)ChildNode;
		lvItem.iIndent = ChildNode->m_Indent;

		int iIndex = m_LvLog->GetLvItem((LPARAM)GetThis());
		if (iIndex == -1)
		{
			iIndex = (int)m_LvLog->m_List.GetCount();
		}else
		{
			iIndex += NodeIndex;
			iIndex++;
		}

		m_LvLog->InsertLvItem(iIndex, lvItem);

		ZxDebug((__FUNCTION__"():: iIndex : %d %ws \n", iIndex,lvItem.DebugGetLvItemString()));

		return iIndex;
	}


	int CollapseChild()
	{
		int Count = 0;
		CollapseChild(Count);

		/*int LvCount = m_ListView->GetItemCount();
		m_ListView->SetItemCountEx( LvCount - Count, LVSICF_NOSCROLL);*/
		return Count;
	}

	VOID CollapseChild(int& Count)
	{
		SetCollapse();
		for (int i = 0; i < (int)m_Child.GetCount(); i++)
		{
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->CollapseChild(Count);
			}
			m_Child[i]->SetCollapse();
			{
				C32TreeNode* Node = m_Child[i];
				
				int iIndex = m_LvLog->RemoveLvItem((LPARAM)Node);
				m_ListView->DeleteItem(iIndex);
				ZxDebug((__FUNCTION__"():: %ws \n",(LPCWSTR)Node->DebugGetItemString()));
				Count++;
				
			}
		}
		

	}
	
	int ExpanedChild()
	{
		int Count = 0;
		int LvCount111 = m_ListView->GetItemCount();
		ExpanedChild(Count);

		//int LvCount = m_ListView->GetItemCount();
		//m_ListView->SetItemCountEx(Count + LvCount, LVSICF_NOSCROLL);

		return Count;

	}
	
	//��������ڵ�
	VOID GetChildCount(int& Count)
	{
		for(int i = 0; i < (int)m_Child.GetCount(); i++)
		{
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->GetChildCount(Count);
			}
			Count++;
		}
	}

	int GetChildPartCount(int iIndex1, int iIndex2)
	{
		int Count = 0;
		for(int i = 0; i < (int)m_Child.GetCount(); i++)
		{
			if (iIndex1 <= i && i <= iIndex2)
			{
				m_Child[i]->GetChildCount(Count);
				Count++;
			}

		}

		return Count;

	}
	

	VOID ExpanedChild(int& Count)
	{
		SetExpanded();
		
		for (int i = 0; i < (int)m_Child.GetCount(); i++)
		{
			ZxDebug((__FUNCTION__"():: %ws \n", m_Child[i]->DebugGetItemString()));	
			int iChildIndex = 0;
			if (i != 0)
			{
				iChildIndex = GetChildPartCount(0, i-1);
			}
				
			int iIndex = InsertLvList(m_Child[i], iChildIndex);
			
			m_ListView->InsertItemAsyn(iIndex,m_ItemString[0], -1, (LPARAM)m_Child[i]);
			m_Child[i]->SetExpanded();
			Count++;
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->ExpanedChild(Count);

			}
		}

	}

	int DeleteChild()
	{
		int Count = 0;

		DeleteChild(Count);
		
		return Count;
		
	}

	VOID DeleteChild(int& Count)
	{

		for (int i = 0; i < (int)m_Child.GetCount(); i++)
		{
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->DeleteChild();

			}else
			{
				C32TreeNode* Node = m_Child[i];
				m_Child.RemoveAt(i);
				m_LvLog->RemoveLvItem((LPARAM)Node);
				ZxDebug((__FUNCTION__"():: %ws \n",(LPCWSTR)Node->DebugGetItemString()));
				Count++;
				delete Node;
				Node = NULL;
			}
		}

	}

	BOOL IsHasChild()
	{
		return !m_Child.IsEmpty();
	}

	BOOL IsExpanded()
	{
		return (m_Expanded&C32TV_EXPANDED);
	}

	VOID SetCollapse()
	{
		m_Expanded = C32TV_COLLAPSE;
	}

	VOID SetExpanded()
	{
		m_Expanded = C32TV_EXPANDED;
	}

	VOID DeleteNode()
	{
		for(int i = 0; i < (int)m_Child.GetCount(); i++)
		{
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->DeleteNode();
			}
			ZxDebug((__FUNCTION__"():: %ws \n", m_Child[i]->DebugGetItemString()));
			delete m_Child[i];
			m_Child[i]=NULL;

		}
		m_Child.RemoveAll();
	}

public:
	int m_Indent;		//������������������Ϊ��λ��
	LPARAM m_lParam;	//Ҫ���������ֵ

	CAtlArray<C32TreeNode*> m_Child;  //�ӽڵ�
	CAtlArray<CString>   m_ItemString; //�����ı�
	DWORD m_Expanded;
	C32LvList*   m_LvLog;
	C32ListView*  m_ListView;
	CString DebugGetItemString()
	{
		CString String;
		for(int i =0; i < (int)m_ItemString.GetCount(); i++)
		{
			String += m_ItemString[i] + L" \t";;
		}

		return String;
	}

	VOID DebugThis()
	{
		ZxDebug((__FUNCTION__"():: %*s iIndent :%8d %ws\n", m_Indent/2," ",m_Indent, DebugGetItemString()));

		if (!m_Child.IsEmpty())
		{
			for(int i = 0 ; i < (int)m_Child.GetCount(); i++)
			{
				//ZxDebug((__FUNCTION__"():: %.*s iIndent :%8d %ws\n", m_Child[i]->m_Indent/5, "\t",m_Child[i]->m_Indent, m_Child[i]->DebugGetItemString()));
				m_Child[i]->DebugThis();
			}
		}
	}

	C32TreeNode(const C32TreeNode& Other)
	{
		m_ItemString.Append(Other.m_ItemString);
		m_Child.Copy(Other.m_Child);
		m_Indent = Other.m_Indent;
	}

};

class C32TreeTable : public C32Container
{
public:
	 static BOOL  CALLBACK OnEventItemChange(int iItem, int iSubItem, LPNMLISTVIEW lpnmlv,LRESULT& lResult, C32ListView* This)
	 {
		if (iItem == -1)
			return TRUE;
		C32TreeTable* Table = (C32TreeTable*)This->GetParentC32Class(); 
		C32TreeNode* Node = (C32TreeNode*)Table->m_List.m_List[iItem].lParam;
		POINT Pt = {};
		if (!(lpnmlv->uNewState& LVIS_SELECTED))
			return TRUE;
		if(Table->m_ListView.GetCursorPos32(Pt))
		{
			RECT rcClose={};
			rcClose.left = Node->m_Indent;
			rcClose.right = rcClose.left + 32;
			if (rcClose.left < Pt.x && Pt.x < rcClose.right)
			{
				ZxDebug((__FUNCTION__"():: չ����ť : %ws : %d\n", Node->DebugGetItemString(), iItem));

				if (Node->IsExpanded())
				{
					int DelCount = Node->CollapseChild();
					Node->SetCollapse();
				}else
				{
					int DelCount = Node->ExpanedChild();
					Node->SetExpanded();
				}
				

			}

		}

		return TRUE;
	 }
	 
	 static BOOL  CALLBACK OnEventGetDispInfo(int iItem, int iSubItem, NMLVDISPINFO* lpnmdi,LRESULT& lResult, C32ListView* This)
	 {
		 C32ListView* ListView = (C32ListView*)This;
		 C32TreeTable* Table = (C32TreeTable*)This->GetParentC32Class(); 
		
		ZxDebug((__FUNCTION__"():: %d %d \n",iItem, iSubItem));
		if (iItem > (int)Table->m_List.m_List.GetCount() -1)
		{
			ZxDebug((__FUNCTION__"()::Error iItem \n"));
			return FALSE;
		}
		lpnmdi->item.mask = lpnmdi->item.mask|LVIF_DI_SETITEM ;
		if (lpnmdi->item.mask & LVIF_TEXT)
		{
			
			lpnmdi->item.pszText = (LPWSTR)(LPCWSTR)Table->m_List.m_List[iItem].m_List[iSubItem].m_Text;
			lpnmdi->item.cchTextMax = 256;
		}else if (lpnmdi->item.mask & LVIF_IMAGE)
		{
			
		}
		return TRUE;
	 }

	 static BOOL CALLBACK OnEventCustomDraw(LPNMLVCUSTOMDRAW lplvcd, LRESULT& lResult, C32ListView* This)
	 {
		return FALSE;
		/* ZxDebug((__FUNCTION__"():: dwItemSpec: %p dwDrawStage: 0x%08x iSubItem: %d dwItemType:0x%08x\n",
						(PVOID)lplvcd->nmcd.dwItemSpec,lplvcd->nmcd.dwDrawStage, lplvcd->iSubItem, lplvcd->dwItemType));
		 */ switch(lplvcd->nmcd.dwDrawStage) {
  
		  case CDDS_PREPAINT:
			  lResult = CDRF_NOTIFYITEMDRAW;
			  break;
		  case CDDS_ITEMPREPAINT:
			  lResult = CDRF_NEWFONT;
			  break;
		  case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
			  lResult = CDRF_NEWFONT; 
			  break;
			     
		  }


		return FALSE;
	 }
	 //
	 static BOOL CALLBACK OnEventDrawItem(LPDRAWITEMSTRUCT lpdis, LRESULT& lResult, C32Window* ThisWindow)
	 {
		C32ListView* This = (C32ListView*)ThisWindow;
		C32TreeTable* Table = (C32TreeTable*)This->GetParentC32Class(); 
		C32TreeNode* Node = (C32TreeNode*)Table->m_List.m_List[lpdis->itemID].lParam;
		C32String DbgText = This->GetItemText(lpdis->itemID, 0);
		//ZxDebug(("iItem: %d Text: %ws Indent : %d \n", lpdis->itemID, (LPWSTR)DbgText, Node->m_Indent));
		ZxDebug(("%ws  %ws itemState: 0x%08x itemAction: 0x%08x\n", 
					DbgText.GetString(),
					C32DbgGetStringRect(lpdis->rcItem).GetString(),
					lpdis->itemState, lpdis->itemAction));
		DWORD iState = Node->IsExpanded()?GLPS_OPENED:GLPS_CLOSED;
		int ColumnCount = This->m_Header.GetCount();
		int ColumnWidth = 0;
		RECT rcText = lpdis->rcItem;
		int ArrayClomunWidth = 0;
		
		C32DeviceContext Dc32;

		COLORREF Clr;
		if (ODS_SELECTED & lpdis->itemState)
			Clr = RGB(91, 173, 255);
		else
			Clr = RGB(255, 255, 255);

		HBRUSH hBrush = CreateSolidBrush(Clr);
		Dc32.SetHdc(lpdis->hDC);
		Dc32.SelectBrush32(hBrush);

		FillRect(lpdis->hDC, &lpdis->rcItem, hBrush);
		
		for(int i = 0; i < ColumnCount; i++)
		{
			ColumnWidth = This->GetColumnWidth(i);
			
			RECT rcClose ={};
			if (i == 0)
			{
				C32DrawControl DrawCtrl;
				DrawCtrl.Open(VSCLASS_TREEVIEW);
				SIZE Size={};
				DrawCtrl.GetPartSize(lpdis->hDC, TVP_GLYPH, GLPS_CLOSED, Size);
				SetRect(&rcClose, Node->m_Indent, lpdis->rcItem.top, Node->m_Indent+Size.cx, lpdis->rcItem.bottom);
				if (Node->IsHasChild())
				{
					rcClose.right = rcClose.left + ColumnWidth;
					DrawCtrl.DrawControlSystemStyle(lpdis->hDC, TVP_GLYPH, iState, &rcClose);
				}

				rcText.left += rcClose.right +10;
			}else
			{
				rcText.left = ArrayClomunWidth;
			}
			rcText.right = ArrayClomunWidth + ColumnWidth;
			
			C32String sTextRect = C32DbgGetStringRect(rcText);
			
			CString Text = Table->m_List.m_List[lpdis->itemID].m_List[i].m_Text;
			
			DrawText(lpdis->hDC, Text, Text.GetLength(),&rcText, DT_END_ELLIPSIS);
			ArrayClomunWidth += ColumnWidth;

		}
		DeleteObject((HGDIOBJ)hBrush);
		
		 return FALSE;
	 }

public:
	
	 
	C32TreeTable()
	{

	}

	~C32TreeTable()
	{
		m_RootNode.DeleteNode();
	}

	 BOOL CALLBACK  OnCreate(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	 {
		lResult = 0;
		BOOL Handle = TRUE;
		
		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;

		DWORD ExStyle = LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP;
		DWORD Style = WS_CHILD | WS_VISIBLE |LVS_REPORT|LVS_OWNERDRAWFIXED|LVS_OWNERDATA;

		C32Window* Pos = C32GetUserClass(lpcs->hwndParent);
		assert(Pos!= NULL);

		HWND hwnd = m_ListView.Create(0, Style, 0, 0, Pos->m_ClientCx, Pos->m_ClientCy, m_Hwnd);
		ZxDebug((__FUNCTION__"()::m_ListView:  %p \n", hwnd));
		if (hwnd == NULL)
		{
			lResult = -1;
			return Handle;
		}

		m_ListView.SetExtendedStyle(ExStyle);
		m_ListView.SetSubclass();
		m_ListView.SetEventItemChanged(OnEventItemChange);
		m_ListView.SetEventGetDispInfo(OnEventGetDispInfo);
		m_ListView.SetEventCustomDraw(OnEventCustomDraw);
		m_ListView.SetEventDrawItem(OnEventDrawItem);

		m_RootNode.m_ListView = &m_ListView;
		m_RootNode.m_LvLog = &m_List;

		AddC32Window(&m_ListView);

		InsertColumn();
		
		return TRUE;
	 }
	 

public:
	VOID InsertRoot(CAtlArray<CString>& StringList,LPARAM lParam)
	{
		m_RootNode.m_ItemString.Copy(StringList);
		m_RootNode.m_Indent = 0;
	}

public:
	VOID InsertColumn()
	{
		m_ListView.InsertColumn(0, 0, L"C32TreeTableColumn0", 100);
		m_ListView.InsertColumn(1, 1, L"C32TreeTableColumn1", 100);
		m_ListView.InsertColumn(2, 2, L"C32TreeTableColumn2", 100);

	
	}

public:
	C32TreeNode m_RootNode;
	C32ListView m_ListView;
	C32LvList m_List;

};

extern C32ThemeStyleList  theTmeStyleList;

#define C32ThemeStyleAddGroupBox(Box) \
	theTmeStyleList.AddGroupBox(Box)


#define C32ThemeStyleAddButton(Button) \
	theTmeStyleList.AddButton(Button)

#define C32ThemeStyleAddLv(ListView) \
	theTmeStyleList.AddListView(ListView)

#define C32ThemeStyleAddDataTime(DataTime) \
	theTmeStyleList.AddDataTime(DataTime)

#define C32ThemeStyleAddStatusBar(StatusBar) \
	theTmeStyleList.AddStatusBar(StatusBar)

#define C32ThemeStyleAddRichEdit(RichEdit) \
	theTmeStyleList.AddRichEdit(RichEdit)

#define C32ThemeStyleAddEdit(Edit) \
	theTmeStyleList.AddEdit(Edit)



#define C32ThemeStyleToDark()\
		theTmeStyleList.SetThemeStyleDark();


VOID C32TreeTableTest(HWND Parent);

VOID C32DialogFileTest();

VOID C32DrawControlTest(HDC hDc);

VOID C32VisualStyleTest(LPCWSTR Class, HDC Hdc);

VOID C32ListBoxTest(HWND Parent);

C32Button* C32ButtonTest();

C32ToolTip* C32ToolTipTest();

VOID C32DialogSearchTest();

C32Explorer* C32ExplorerTest(HWND hWnd);

VOID C32DialogProgressTest(HWND hWnd);

VOID C32StatusBarTest();

VOID InitC32Control(HINSTANCE hInstance);

VOID UnInitC32Control();



