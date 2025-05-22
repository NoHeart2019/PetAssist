#pragma once
#include <Windows.h>
//��ȡ����ǰ������ʾ���ķֱ��ʴ�С�����Զ�̬�Ļ�ȡ����������ʾ���ķֱ���
// ���hWnd ΪNULL,��Ϊ����ʾ���Ĵ�С
//
SIZE C32GetDesktopSize(HWND hWnd);

/*
	����(Hwnd)�ڸ������о�����ʾ.
	Parent = NULL �Ǵ��������������ʾ
*/
BOOL C32SetCenterPos(HWND Hwnd, HWND Parent);

BOOL C32SetCenterPosDesktop(HWND Hwnd);

//���Ƶ����а�
BOOL C32SetClipboard(CString& String, HWND Hwnd);

int  C32GetTextLength( HWND Hwnd, LPCWSTR String, HFONT hFont = NULL);

int  C32GetTextLength(HDC Hdc, LPCWSTR String);


/*
	�����滻�Ի���
*/
BOOL C32FindTextDlg(HWND hwndOwner);

BOOL C32ChooseColor(HWND hwndOwner, _Out_ COLORREF* Color);

BOOL C32ChooseFont(HWND hwndOwner, _Inout_ LPLOGFONT LogFont, __out int* FontSize);

/*
	����
*/

HFONT C32GetSysFont();

int C32GetFontHeightInPixels(HDC hdc, int lfHeight);

int C32GetFontSize(HWND hwndOwner, LPLOGFONT LogFont);

int C32GetFontSize(HWND hwndOwner, LPLOGFONT LogFont, int Height);

/*
	�����������ƺ������С���������塣
*/
HFONT C32CreateFont(LPCWSTR FontName, int FontSize);

int C32GetFontSize(HWND hwnd, int Height);


BOOL C32GetFontInfo(HGDIOBJ  hFont);

BOOL C32GetFontInfo(HGDIOBJ  hFont);


BOOL C32FontGetTextExtentPoint32(__in HDC hdc,__in_ecount(c) LPCWSTR lpString,__in int c,__out LPSIZE psizl, LPLOGFONT LogFont);

BOOL C32FontGetTextExtentPoint32(__in HWND hwnd,__in_ecount(c) LPCWSTR lpString,__in int c,__out LPSIZE psizl, LPLOGFONT LogFont);

/*
	ȫ�ֱ�����ȡ
*/
FLOAT C32GetDpiFontSize();

/*
	��ϵͳ���帴��һ�ݣ��ı�������Height�������µ����塣
	Ϊ�˷��㽫�����ŵķ�ʽ*/
HFONT  C32CreateSystemFont(FLOAT Scale);



/*
	�ھ���SrcRect Draw ͼƬ
	���SrcRect�ĸ߶ȺͿ�ȴ���ͼƬ��ͼƬ���¾���
*/
BOOL C32GetDrawIconRect(int IconCx, int IconCy, RECT SrcRect, __out RECT * IconRect);

BOOL C32GetDrawIconRect(SIZE Size, RECT SrcRect, __out RECT * IconRect);

BOOL C32SetSizeInRectCenter(SIZE Size, RECT SrcRect, __out RECT * IconRect);

//�˵�
BOOL C32SetMenuOwnerDraw(__in HMENU hMnu, __in UINT uPosition, __in UINT uFlags,__in UINT_PTR uIDNewItem);


/*
	GDI ����ֱ�ߣ�ƽ��ͼ��
*/
VOID C32DrawLine(HDC hdc,POINT StartPoint, POINT EndPoint, int PenSize, COLORREF PenColor);


/*
	@brief: ϵͳ����
*/
class C32SysFont
{
public:
	C32SysFont()
	{
		m_hSysFont = NULL;
		RtlZeroMemory(&m_SysFont, sizeof(LOGFONT));
	}

	~C32SysFont()
	{
		Unitialize();
	}

	VOID Unitialize()
	{
		if (m_hSysFont)
		{
			DeleteFont(m_hSysFont);
			m_hSysFont = NULL;
		}
	}

	VOID Initialize()
	{
		InitSysFont();
	}

	VOID InitSysFont()
	{
		NONCLIENTMETRICS NcMetrics ={};
		NcMetrics.cbSize = sizeof(NONCLIENTMETRICS);

		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0,
							(PVOID)&NcMetrics, 0);
		
		m_SysFont = NcMetrics.lfCaptionFont;
		m_hSysFont = CreateFontIndirect(&m_SysFont);

		ZxDebugEx((__FUNCTION__"()::FaceName:%ws  \n", NcMetrics.lfCaptionFont.lfFaceName));
	}

	HFONT GetLogicFont()
	{
		return m_hSysFont;
	}

	LPLOGFONT GetLogFont()
	{
		return &m_SysFont;
	}


	HFONT   m_hSysFont;
	LOGFONT m_SysFont;
};

class C32Monitor
{
public:
	C32Monitor()
	{
		m_Cx = m_Cy = 0;
		m_LogPixel = 96;
		m_FontScale = 1.0f;
		m_WindowScale = 1.0f;

		Initialize();
	}

	~C32Monitor()
	{


	}
public:
	
	VOID InitLogPixel()
	{
		HDC hdcScreen = GetDC(NULL);
		m_LogPixel = GetDeviceCaps(hdcScreen, LOGPIXELSX);
		DeleteObject(hdcScreen);
	}

	VOID InitScale()
	{
		m_FontScale = ((FLOAT)m_LogPixel/96.0f);
		m_WindowScale = ((FLOAT)m_LogPixel/96.0f*1.5f);
	}

	VOID Initialize()
	{
		InitLogPixel();
		InitScale();

		Debug();
	}

	VOID Debug()
	{
		ZxDebugEx((__FUNCTION__"():: m_Cx = %d, m_Cy = %d, m_LogPixel = %d m_FontScale = %f m_WindowScale = %f \n",
				m_Cx, m_Cy, m_LogPixel, m_FontScale, m_WindowScale));
	}

public:
	int		m_Cx; //
	int		m_Cy;
	int		m_LogPixel;//ÿ���߼�Ӣ������Ļ��ȵ�������

	FLOAT    m_FontScale;
	FLOAT	 m_WindowScale;
};

/*
	@brief: ϵͳ��ɫ
*/
class C32SysColor
{
public:
	C32SysColor()
	{
		m_SysColorWindow = GetSysColor(COLOR_WINDOW);
		m_SysColorWindowText = GetSysColor(COLOR_WINDOWTEXT);
		m_SysColorWindowFrame = GetSysColor(COLOR_WINDOWFRAME);
	}

	~C32SysColor()
	{


	}
public:
	COLORREF  m_SysColorWindow;
	COLORREF  m_SysColorWindowText;
	COLORREF  m_SysColorWindowFrame;

};

/*
	@brief: ϵͳ ��Ļ��ͼ�꣬�������ȵĴ�С��
*/
class C32SystemMetrics : public C32SysColor
{

public:
	C32SystemMetrics()
	{
		Initialize();

	}
	
	~C32SystemMetrics()
	{


	}
	
	VOID Initialize()
	{
		m_CyMenu = GetSystemMetrics(SM_CYMENU);
		m_CyMenuCheck = GetSystemMetrics(SM_CYMENUCHECK);
		m_CyMenuSize = GetSystemMetrics(SM_CYMENUSIZE);
		
		m_SmCxScreen = GetSystemMetrics(SM_CXFULLSCREEN);
		m_SmCyScreen = GetSystemMetrics(SM_CYFULLSCREEN);

		m_SmCxSize = GetSystemMetrics(SM_CXSIZE);
		m_SmCySize = GetSystemMetrics(SM_CYSIZE);


		m_SmCxFrame = GetSystemMetrics(SM_CXFRAME);
		m_SmCyFrame = GetSystemMetrics(SM_CYFRAME);


		m_SmCxSmIcon = GetSystemMetrics(SM_CXSMICON);
		m_SmCySmIcon = GetSystemMetrics(SM_CYSMICON);
		m_SmCxIcon = GetSystemMetrics(SM_CXICON);
		m_SmCyIcon = GetSystemMetrics(SM_CYICON);
		
		//������
		m_SmCxVscroll = GetSystemMetrics(SM_CXVSCROLL);
		m_SmCyVscroll = GetSystemMetrics(SM_CYVSCROLL);

		ZxDebugEx(("SM_CYMENU: %d \n", m_CyMenu));
		ZxDebugEx(("SM_CYMENUCHECK: %d \n", m_CyMenuCheck));
		ZxDebugEx(("SM_CYMENUSIZE: %d \n", m_CyMenuSize));
		ZxDebugEx(("SM_CXSMICON: %d \n", m_SmCxSmIcon));
		ZxDebugEx(("SM_CYSMICON: %d \n", m_SmCySmIcon));
		ZxDebugEx(("SM_CXICON: %d \n", m_SmCxIcon));
		ZxDebugEx(("SM_CXICON: %d \n", m_SmCyIcon));
		ZxDebugEx(("SM_CXVSCROLL: %d \n", m_SmCxVscroll));
		ZxDebugEx(("SM_CYVSCROLL: %d \n", m_SmCyVscroll));
		GetNonClientMetrics();
		InitLanguage();
		
	}

	VOID GetNonClientMetrics()
	{
		m_NonClientMetrics.cbSize = sizeof(NONCLIENTMETRICS);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, (PVOID)&m_NonClientMetrics, 0);
	}

	VOID InitLanguage()
	{
		//Windows Ӧ�ó���Ĺ��ʻ�
		m_LangId = GetSystemDefaultLangID();
		WCHAR Buffer[8]={};
		int Ret = GetSystemDefaultLocaleName(Buffer, 8);
		m_LangString = Buffer;
	}

	VOID GetFontLanguage(LPLOGFONT Font, CString& Lang)
	{
		memcpy(Font, &m_NonClientMetrics.lfCaptionFont, sizeof(LOGFONT));
		
		Lang += m_LangString;
	}

	

	
	VOID GetSmIcon(PSIZE Size)
	{
		Size->cx = m_SmCxIcon;
		Size->cy = m_SmCyIcon;
	}

public:
	//LoadIcon ����ֻ�ܼ��ؾ���SM_CXICON��SM_CYICONָ���ߴ��ͼ��
	int m_SmCxIcon;  //ͼ���ϵͳ���ȣ�������Ϊ��λ����
	int m_SmCyIcon;  //ͼ���ϵͳ�߶ȣ�������Ϊ��λ����

	int m_SmCxSmIcon; //ͼ���ϵͳС��ȣ�������Ϊ��λ���� Сͼ��ͨ����ʾ�ڴ��ڱ����Сͼ����ͼ�С�
	int m_SmCySmIcon; //ͼ���ϵͳС�߶ȣ�������Ϊ��λ���� Сͼ��ͨ����ʾ�ڴ��ڱ����Сͼ����ͼ��.
	//����
	int m_SmCxMin; //���ڵ���С��ȣ�������Ϊ��λ����
	int m_SmCyMin; //���ڵ���С�߶ȣ�������Ϊ��λ����

	int m_SmCyMinimized;//��С�����ڵĸ߶ȣ�������Ϊ��λ����
	int m_SmCxMinimized; //��С�����ڵĿ�ȣ�������Ϊ��λ��

	int  m_SmCxFrame;    //�ɵ�����С�Ĵ����ܱߵĴ�С�߿�Ĵ�ϸ��������Ϊ��λ���� SM_CXSIZEFRAME��ˮƽ�߿�Ŀ�ȣ�
	int  m_SmCyFrame;    //SM_CYSIZEFRAME�Ǵ�ֱ�߿�ĸ߶ȡ�
	
	int  m_SmCxSize;	 //�����а�ť�Ŀ���������ֻ��������������Ϊ��λ)
	int  m_SmCySize;     //�����а�ť�ĸ߶��������ֻ��������������Ϊ��λ)

	//����ʾ������
	int m_SmCyMaximized;//����ʾ����������󻯵Ķ������ڵ�Ĭ�ϸ߶ȣ�������Ϊ��λ����
	int m_SmCxMaximized; //����ʾ����������󻯵Ķ������ڵ�Ĭ�Ͽ�ȣ�������Ϊ��λ����

	//��Ļ
	int m_SmCxScreen;   //����ʾ������Ļ��ȣ�������Ϊ��λ���� ����ͨ������ GetDeviceCaps ��ȡ����ֵͬ��
	int m_SmCyScreen;   //����ʾ������Ļ�߶ȣ�������Ϊ��λ���� ����ͨ������ GetDeviceCaps ��ȡ����ֵͬ

	//������
	int m_SmCxHscroll; //ˮƽ�������ϼ�ͷλͼ�Ŀ�ȣ�������Ϊ��λ����
	int m_SmCyHscroll; // ˮƽ�������ĸ߶ȣ�������Ϊ��λ��
		
	int m_SmCxVscroll; //��ֱ�������Ŀ�ȣ�������Ϊ��λ����
	int m_SmCyVscroll; //��ֱ�������ϼ�ͷλͼ�ĸ߶ȣ�������Ϊ��λ����
		
	int m_SmCxHthumb;  //ˮƽ��������Ĵָ��Ŀ�ȣ�������Ϊ��λ����
	int m_SmCyHthumb;  //��ֱ��������Ĵָ��ĸ߶ȣ�������Ϊ��λ����

	//�˵�SM_CYMENU SM_CYMENUSIZE
	
	int m_CyMenu;	    //���в˵����ĸ߶ȣ�������Ϊ��λ��
	int m_CyMenuCheck;  //Ĭ�ϲ˵��ĸ߶ȼ����λͼ��������Ϊ��λ��
	int m_CyMenuSize;   //�˵�����ť�������ڶ���ĵ�������ʹ�õ��Ӵ��ڹرհ�ť���ĸ߶ȣ�������Ϊ��λ��


	LANGID			 m_LangId;
	CString			 m_LangString;
	
	NONCLIENTMETRICS m_NonClientMetrics; //Retrieves the metrics associated with the nonclient area of nonminimized windows

	//DPI ���
	int				 m_LogPixel;
};

/*
	@brief: ϵͳGdi����

*/
class C32SysObject : public C32SysFont
{

public:
	C32SysObject()
	{

	}
	
	~C32SysObject()
	{
	}

	VOID Initialize()
	{	
		C32SysFont::Initialize();
	}

	VOID Destroy()
	{
		
		
	}

	VOID Debug()
	{
	
	}

};

class C32DPI
{
public:
	C32DPI()
	{

	}
	
	~C32DPI()
	{

	}

	VOID Initialize();
	

public:
	LOGFONT m_LogFont;
	CString m_FontString;
	CString m_LocalString;
	FLOAT	m_FontSize;
	FLOAT   m_FontScale;
	FLOAT   m_WindowScale;
};

extern C32SystemMetrics   theSysMetrics;
extern C32SysObject		  theSysObject;
extern C32Monitor		  theMonitor;
extern C32DPI			  theDPI;

VOID InitC32Util();

