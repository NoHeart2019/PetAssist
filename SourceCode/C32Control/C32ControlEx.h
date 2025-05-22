#include "C32D2D1.h"

/*
	用Direct2D 实现得控件库
*/
#define C32_WC_ROUND_PROCESS L"C32RoundProcess"


class C32RoundProcess : public C32Window
{
public:
	static DWORD RegisterThisClass()
	{
		DWORD Atom;
		Atom = RegisterClassEx32(C32_WC_ROUND_PROCESS);
		ZxDebugEx((__FUNCTION__"():: Atom: %d \n", Atom));
		return Atom;
	}

public:
	C32RoundProcess()
	{
		m_D2Factory = m_D2D1Factory;
		m_D2WriteFactory = m_D2D1WriteFactory;
		Initialize();
	}

	~C32RoundProcess()
	{


	}

	virtual BOOL CALLBACK OnPaint(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_Hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.
		D2D1_RENDER_TARGET_PROPERTIES Prop =  D2D1::RenderTargetProperties();
		Prop.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_IGNORE);
		CComPtr<ID2D1DCRenderTarget> Target;
		CComPtr<ID2D1SolidColorBrush> OutBrush;
		CComPtr<ID2D1SolidColorBrush> InBrush;
		CComPtr<ID2D1SolidColorBrush> CenterBrush;
		CComPtr<ID2D1SolidColorBrush> TitleBrush;
		CComPtr<IDWriteTextFormat> m_CenterTextFormat;

		m_D2Factory->CreateDCRenderTarget(&Prop, &Target);
		Target->BindDC(hdc, &m_ClientRect);
		CreateBrush(Target, &OutBrush, &InBrush, &CenterBrush, &TitleBrush);
		D2D1_RECT_F FontRect;
		D2D1_RECT_F SquareRect;
		D2D1_ELLIPSE Ellipse = GetOutEllipse(FontRect, SquareRect);

		FLOAT NumberFontHeight = Ellipse.radiusX;
		//画内圆
		CComPtr<ID2D1PathGeometry> PathGeometry;
		CComPtr<ID2D1GeometrySink> GeometrySink;
		CreatePathGeometryArc(Ellipse, &PathGeometry, &GeometrySink, m_CurrentAngle);

		C32D2D1CreateTextFormatSystem(NumberFontHeight, &m_CenterTextFormat);

		CString CenterString = L"88";

		Target->BeginDraw();
		//设置窗口背景色。
		Target->Clear(m_D2ColorBkGnd);

		if (m_OutStrokeWidth == 0.0F)
		{
			m_OutStrokeWidth = Ellipse.radiusX/5;
			m_InStrokeWidth = m_OutStrokeWidth-4;
		}
		//画外圆
		Target->DrawEllipse(Ellipse,OutBrush, m_OutStrokeWidth);

		Target->DrawGeometry(PathGeometry, InBrush, m_InStrokeWidth);

		if (m_IsText)
		{
			m_D2D1WriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			m_D2D1WriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			Target->DrawText(m_AssText.GetString(),m_AssText.GetLength(), m_D2D1WriteTextFormat, FontRect, TitleBrush);
		}
		m_CenterTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_CenterTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		Target->DrawText(CenterString,CenterString.GetLength(), m_CenterTextFormat, SquareRect, CenterBrush);

		Target->DrawRectangle(SquareRect, InBrush, 2.0f);
		Target->EndDraw();
		EndPaint(m_Hwnd, &ps);

		return TRUE;
	}

	//计算外圆，显示标题，环中文字的坐标
	D2D1_ELLIPSE GetOutEllipse(D2D1_RECT_F& FontRect, D2D1_RECT_F& Square)
	{		
		FLOAT Radix;
		FLOAT xPos, yPos;

		FLOAT Cx = (FLOAT)m_ClientCx;
		FLOAT Cy = (FLOAT)m_ClientCy;

		FLOAT FontHeight = GetFontHeight();
		FLOAT FontCy = FontHeight*1.1F;

		//圆环所在的矩形
		//Padding 默认或者是字体双倍
		m_MarginPadding =(m_IsText ? FontCy : m_MarginPadding);
		Cy -= (m_IsText ? FontCy : 0);

		//获取长和宽中的最小值
		FLOAT Diameter = (FLOAT)C32Min(Cx, Cy);
		Radix = (Diameter/2 - m_MarginPadding);

		xPos = Cx/2;
		yPos = Cy/2 + ((m_IsText== FALSE || m_IsTopText == FALSE) ? 0 : FontCy);

		//字体所在的矩形
		FLOAT yPosFont = m_IsTopText ? 0 : m_ClientCy-FontCy;
		FLOAT xPosFont = 0.0f;
		FontRect.left = xPosFont;
		FontRect.top = yPosFont;
		FontRect.right = Cx;
		FontRect.bottom = yPosFont + FontCy;


		FLOAT  SquareSide=  sqrt(2.0F)*Radix;
		SquareSide /= 2.0F;
		Square.left = xPos - SquareSide;
		Square.top = yPos -SquareSide;
		Square.right = xPos + SquareSide;
		Square.bottom = yPos + SquareSide;

		return D2D1::Ellipse(D2D1::Point2F(xPos, yPos), Radix, Radix);
	}

	BOOL   CreatePathGeometryArc(D2D1_ELLIPSE& Ellipse, ID2D1PathGeometry** OutPathGeometry, ID2D1GeometrySink** OutGeometrySink, FLOAT Angle)
	{
		HRESULT Hr;
		ID2D1PathGeometry* PathGeometry;
		ID2D1GeometrySink* GeometrySink;
		Hr = m_D2Factory->CreatePathGeometry(&PathGeometry);
		if (SUCCEEDED(Hr))
		{
			Hr= PathGeometry->Open(&GeometrySink);
			if (SUCCEEDED(Hr))
			{
				//设置起始点以X轴右侧点为起始点。方便计算
				D2D1_POINT_2F EllipseWestCenter = D2D1::Point2F(Ellipse.point.x + Ellipse.radiusX, Ellipse.point.y );
				GeometrySink->BeginFigure(EllipseWestCenter,
					D2D1_FIGURE_BEGIN_FILLED);

				D2D1_POINT_2F EndPoint;
				EndPoint.x = Ellipse.point.x +  Ellipse.radiusX*cos(Angle*C32_CIRCLE_PI/180.0F);
				EndPoint.y = Ellipse.point.y + Ellipse.radiusX*sin(Angle*C32_CIRCLE_PI/180.0F);

				D2D1_ARC_SEGMENT Arc = D2D1::ArcSegment(
					EndPoint, 
					D2D1::SizeF(Ellipse.radiusX, Ellipse.radiusY),
					Angle, D2D1_SWEEP_DIRECTION_CLOCKWISE, 
					(Angle >= 180?D2D1_ARC_SIZE_LARGE:D2D1_ARC_SIZE_SMALL));

				GeometrySink->AddArc(Arc);
				GeometrySink->EndFigure(D2D1_FIGURE_END_OPEN);
				GeometrySink->Close();

				*OutPathGeometry = PathGeometry;
				*OutGeometrySink = GeometrySink;
			}
		}

		return SUCCEEDED(Hr);
	}

	BOOL   CreateBrush(ID2D1DCRenderTarget* Target, ID2D1SolidColorBrush** OutBrush, ID2D1SolidColorBrush** InBrush, ID2D1SolidColorBrush** CenterBrush, ID2D1SolidColorBrush** TitleBrush)
	{

		Target->CreateSolidColorBrush(m_D2ColorOutCircle, OutBrush);
		Target->CreateSolidColorBrush(m_D2ColorInCircle, InBrush);	
		Target->CreateSolidColorBrush(m_D2ColorFontCenter, CenterBrush);	
		Target->CreateSolidColorBrush(m_D2ColorFontTitle, TitleBrush);

		return TRUE;

	}

	FLOAT GetFontHeight()
	{
		return m_D2D1WriteTextFormat->GetFontSize();
	}

	VOID Initialize()
	{

		m_D2ColorBkGnd =  D2D1::ColorF(D2D1::ColorF::White);
		m_D2ColorFontCenter = D2D1::ColorF(D2D1::ColorF::Black);
		m_D2ColorFontTitle = D2D1::ColorF(D2D1::ColorF::Black);
		m_D2ColorOutCircle = D2D1::ColorF(D2D1::ColorF::WhiteSmoke);
		m_D2ColorInCircle = D2D1::ColorF(C32D2RGB(38, 160, 218));

		m_MarginPadding = 10.0F;
		m_OutStrokeWidth = m_InStrokeWidth = 0.0F;

		m_CurrentAngle = 90;
		m_IsTopText = FALSE;
		m_IsText = TRUE;
		m_AssText = L"环形展示";
	}

	VOID SetTitle(CString& Title)
	{
		m_AssText = Title;
	}

	VOID SetAngle(FLOAT Angle)
	{
		m_CurrentAngle = Angle;
	}

public:
	FLOAT m_StartAngle;//起始角度
	FLOAT m_CurrentAngle;//当前的角度
	FLOAT m_MarginPadding; //距离上下左右的边距
	BOOL m_Clockwise; //顺时针

	BOOL m_IsText;		//输出文字
	BOOL m_IsTopText;  //文字在上方还是在下方

	D2D1_COLOR_F m_D2ColorBkGnd; //窗口背景颜色
	D2D1_COLOR_F m_D2ColorFontCenter; //环形中显示文字颜色
	D2D1_COLOR_F m_D2ColorFontTitle;  //环形标题字体颜色

	BOOL		m_IsOutCircle; //外圆
	D2D1_COLOR_F m_D2ColorOutCircle; //外圆轮廓颜色
	FLOAT		m_OutStrokeWidth;	//轮廓宽度

	BOOL		 m_IsInCircle;		//弧线圆
	D2D1_COLOR_F m_D2ColorInCircle; //弧线圆轮廓颜色
	FLOAT		 m_InStrokeWidth;   //轮廓宽度

	CString m_AssText;


	ID2D1Factory*  m_D2Factory;
	IDWriteFactory* m_D2WriteFactory;
};


BOOL C32RoundProcessText(HWND Hwnd);


VOID InitC32ControlEx();