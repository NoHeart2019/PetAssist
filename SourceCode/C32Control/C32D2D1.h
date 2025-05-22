#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

BOOL InitC32D2D1();

VOID UnInitC32D2D1();

#define Rect2RectF(Rt)\
		 D2D1::RectF((FLOAT)Rt.left, (FLOAT)Rt.top, (FLOAT)Rt.right, (FLOAT)Rt.bottom)

#define C32D2D1GetRectFWidth(RectF1)(RectF1.right - RectF1.left)

#define C32D2D1GetRectFHeight(RectF1)(RectF1.bottom - RectF1.top)

#define C32D2RGB(r, g, b) RGB(b, g, r)

#define C32Color2ColorF(Color1) \
	D2D1::ColorF((FLOAT)GetBValue(Color1),(FLOAT)GetGValue(Color1),(FLOAT)GetRValue(Color1), 1.0f)

#define C32_CIRCLE_PI 3.14159265358979323846f


extern ID2D1Factory* m_D2D1Factory;
extern IDWriteFactory* m_D2D1WriteFactory;
extern IDWriteTextFormat* m_D2D1WriteTextFormat;
extern IWICImagingFactory* m_D2D1WICFactory;

/*
	@brief: ����ϵͳĬ�����������Ŵ�������
*/
HRESULT C32D2D1CreateTextFormatSystem(FLOAT FontSize, IDWriteTextFormat** WirteTextFormat);


HRESULT C32D2D1GetTextSize(const WCHAR* text, IDWriteTextFormat* pTextFormat, D2D1_SIZE_F& size);



/*
	����WriteTextFormat �;���RECT���������ھ��ξ�����ʾʱ��D2D1_RECT_F��
	Original :Ҫ�ڴ˾����ھ�����ʾ���֡�
	Center   :���־��о������ꡣ


*/
HRESULT C32D2D1GetTextCenter(CString& Stirng, IDWriteTextFormat* pTextFormat, D2D1_RECT_F& Rect,__inout D2D1_RECT_F& Center);

class C32D2D1TextFormat
{

public:
	C32D2D1TextFormat()
	{

	}

	~C32D2D1TextFormat()
	{


	}
	
	VOID Initialize()
	{
		m_IsSystemFont = TRUE;
		m_IsColor = FALSE;
		m_IsFontBkGndColor = FALSE;
		m_IsFontColor	  = FALSE;
	}

	HRESULT CreateD2Font(LPCWSTR Local,LPCWSTR Family, FLOAT FontSize)
	{
		HRESULT Hr;
		m_IsSystemFont = FALSE;
		m_D2TextFormat.Release();
		Hr= m_D2D1WriteFactory->CreateTextFormat(
			Family,
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			FontSize,
			Local,
			&m_D2TextFormat
			);

		m_D2FontLocalName = Local;
		m_D2FontFamilyName = Family;
		m_D2FontSize = FontSize;
		
		return Hr;
	}
	
	BOOL SetFontBkGndColor(D2D1_COLOR_F Color)
	{
		m_IsColor = TRUE;		
		m_IsFontBkGndColor = TRUE;
		m_D2ColorFontBkGnd = Color;
	}

	BOOL SetFontColor(D2D1_COLOR_F Color)
	{
		m_IsColor = TRUE;
		m_IsFontColor = TRUE;
		m_D2ColorFontBkGnd = Color;
	}

public:
	BOOL		  m_IsSystemFont;		 //�Ƿ���ϵͳ����
	BOOL		  m_IsColor;			 //�Ƿ�ʹ����ɫ
	BOOL		  m_IsFontBkGndColor;   //�Ƿ����屳��ɫ
	BOOL		  m_IsFontColor;		//�Ƿ�������ɫ
			
	D2D1_COLOR_F  m_D2ColorFontBkGnd;//���屳��ɫ
	D2D1_COLOR_F  m_D2ColorFont;     //������ɫ;

	FLOAT		  m_D2FontSize;      //�����С
	CString		  m_D2FontFamilyName; //��������
	CString		  m_D2FontLocalName;  //��������
	
	CComPtr<IDWriteTextFormat> m_D2TextFormat;

};



