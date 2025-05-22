#pragma once
#include <GdiPlus.h>


#define C32_WC_JPG_VIEWER	L"JPGViewer"

// ��װ�� JPG ��ʾ��
class CJPGViewer
{
private:
	Gdiplus::Image* m_Image; // ͼƬ����

public:
	CJPGViewer() : m_Image(nullptr) {}

	~CJPGViewer()
	{
		if (m_Image)
		{
			delete m_Image;
			m_Image = nullptr;
		}
	}

	// ����ͼƬ
	bool LoadImage(const TCHAR* filePath)
	{
		m_Image = new Gdiplus::Image(filePath);
		return (m_Image->GetLastStatus() == Gdiplus::Ok);
	}

	// ����ͼƬ
	void Draw(HDC hdc, int x = 0, int y = 0, int width = -1, int height = -1)
	{
		if (!m_Image) return;

		Gdiplus::Graphics graphics(hdc);
		if (width == -1 || height == -1)
		{
			width = m_Image->GetWidth();
			height = m_Image->GetHeight();
		}
		graphics.DrawImage(m_Image, x, y, width, height);
	}

	// ��ȡͼƬ�ߴ�
	bool GetImageSize(int& width, int& height)
	{
		if (!m_Image) return false;

		width = m_Image->GetWidth();
		height = m_Image->GetHeight();
		return true;
	}
};

BOOL SetJPGImagePath(HWND Hwnd, LPCWSTR ImagePath);

VOID InitC32ControlGdi();

