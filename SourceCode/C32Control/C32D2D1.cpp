#include "stdafx.h"
#include "C32D2D1.h"


ID2D1Factory* m_D2D1Factory;
IDWriteFactory* m_D2D1WriteFactory;
IDWriteTextFormat* m_D2D1WriteTextFormat;
IWICImagingFactory* m_D2D1WICFactory;

BOOL InitC32D2D1()
{
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&m_D2D1Factory
		);
	if (SUCCEEDED(hr))
	{
		hr= DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_D2D1WriteFactory)
			);
		m_D2D1WriteFactory->CreateTextFormat(
			theDPI.m_FontString.GetString(),
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			theDPI.m_FontSize,
			theDPI.m_LocalString.GetString(),
			&m_D2D1WriteTextFormat
			);


	}

	 CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_D2D1WICFactory)
		);;


	return FALSE;
}

VOID UnInitC32D2D1()
{
	if (m_D2D1Factory)
		m_D2D1Factory->Release();

	if (m_D2D1WriteFactory)
	{
		m_D2D1WriteFactory->Release();
	}

	if (m_D2D1WICFactory)
	{
		m_D2D1WICFactory->Release();
	}

}


HRESULT C32D2D1CreateTextFormatSystem(FLOAT FontSize, IDWriteTextFormat** WirteTextFormat)
{
	HRESULT Hr;
	Hr = m_D2D1WriteFactory->CreateTextFormat(
		theDPI.m_FontString.GetString(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		FontSize,
		theDPI.m_LocalString.GetString(),
		WirteTextFormat);

	return Hr;
}

HRESULT C32D2D1GetTextSize(const WCHAR* text, IDWriteTextFormat* pTextFormat, D2D1_SIZE_F& size)
{ 
	HRESULT hr = S_OK; 
	CComPtr<IDWriteTextLayout> pTextLayout = NULL;   
	// �����ı����� 
	hr = m_D2D1WriteFactory->CreateTextLayout(text, (UINT)wcslen(text), pTextFormat, 0.0f, 0.0f, &pTextLayout);   
	if (SUCCEEDED(hr)) 
	{     
		// ��ȡ�ı��ߴ�  
		DWRITE_TEXT_METRICS textMetrics;  
		hr = pTextLayout->GetMetrics(&textMetrics);  
		size = D2D1::SizeF(ceil(textMetrics.widthIncludingTrailingWhitespace), ceil(textMetrics.height));
	} 
	
	return hr;
}

HRESULT C32D2D1GetTextCenter(CString& Stirng, IDWriteTextFormat* pTextFormat, D2D1_RECT_F& Rect,__inout D2D1_RECT_F& Center)
{
	HRESULT hr;
	// �����ı����뷽ʽ
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	//���ö�������ڲ��ֿ���ϱ�Ե���±�Ե�Ķ���ѡ��
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	// �����ı�����

	IDWriteTextLayout* pTextLayout = nullptr;
	hr = m_D2D1WriteFactory->CreateTextLayout(
		Stirng.GetString(),                    // �ı�����
		Stirng.GetLength(),            // �ı�����
		pTextFormat,             // �ı���ʽ
		Rect.right-Rect.left,                  // ����ȣ��ɸ�����Ҫ������
		Rect.bottom-Rect.top,                  // ���߶ȣ��ɸ�����Ҫ������
		&pTextLayout
		);
	if (SUCCEEDED(hr))
	{
		// ��ȡ�ı����ֵĳߴ�
		DWRITE_TEXT_METRICS textMetrics;
		hr = pTextLayout->GetMetrics(&textMetrics);
		if (SUCCEEDED(hr))
		{
			// ������ʼ����λ�ã����ж��룩
			float x = Rect.left + (Rect.right - Rect.left - textMetrics.width) / 2;
			float y = Rect.top + (Rect.bottom - Rect.top - textMetrics.height) / 2;
			Center = D2D1::RectF(x, y, x+textMetrics.width, y+textMetrics.height);
		}
	}

	
	return hr;
}


