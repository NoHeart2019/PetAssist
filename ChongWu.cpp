/*
	������������д��C32 Control Lib�⡣
	��ǰ��Դ�˵�һ���汾�����ڵİ汾��û����Ҫ��Ҫ��Դ��
	��ʵ���Ƕ�win32�򵥵ķ�װû���κμ���������
	���ǿ��Ը������������Լ�ȥ�ĸġ�
	����ǳ��򵥡�

*/


class C32HoverMsg : public C32Window
{
public:
	C32HoverMsg()
	{

	}	
	~C32HoverMsg()
	{
		ZxDebugEx((__FUNCTION__"():: \n"));

	}
public:
	BOOL Register()
	{
		DWORD Atom = RegisterClassEx32(L"WC_C32HoverMsg");
		ZxDebugEx((__FUNCTION__"():: Atom: 0x%08x \n", Atom));

		return Atom;
	}

	BOOL CreateMsg()
	{
		DWORD ExStyle = WS_EX_TOPMOST;
		DWORD Style = WS_OVERLAPPED |WS_CAPTION | WS_SYSMENU | WS_THICKFRAME     
			;
		HWND Hwnd = Create(ExStyle, L"WC_C32HoverMsg", L"С���˸���Ϣ��",Style, 0, 0, 500, 500, NULL);
		
		return (Hwnd != NULL);
	}

	virtual BOOL CALLBACK OnCreate(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		CString GIFPath = YUAN_SHEN_DIRECTORY;
		// ���ö�ʱ���Ը��¶���
		SetTimer(m_Hwnd, 1, 16, NULL); // Լ 60 FPS
		GIFPath += L"Dance.gif";
		CreateRender(m_Hwnd, 0, 0);
		LoadGIF(GIFPath);
		
		C32SetCenterPosDesktop(m_Hwnd);
		return TRUE;
	}

	virtual BOOL CALLBACK OnPaint(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		RenderGIF();

		 ValidateRect(m_Hwnd, NULL);
		//EndPaint(m_Hwnd, &ps);

		return TRUE;
	}

	virtual BOOL CALLBACK OnTimer(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		ZxDebugEx((" \n"));
		
		RenderGIF();
		

		return Handle;
	}

	// ��ȡ GIF ֡���ӳ�ʱ�䣨��λ�����룩
	HRESULT GetGIFDelayFromFrame(IWICBitmapFrameDecode* pFrame, UINT32& delay) {
		HRESULT hr = S_OK;
		delay = 100; // Ĭ���ӳ� 100ms��GIF89a �Ƽ�ֵ��

		IWICMetadataQueryReader* pMetadataReader = nullptr;
		hr = pFrame->GetMetadataQueryReader(&pMetadataReader);
		if (SUCCEEDED(hr)) {
			PROPVARIANT propVar;
			PropVariantInit(&propVar);

			// ���п��ܵ�Ԫ����·��
			const wchar_t* metadataPaths[] = {
				L"/grct/delay",             // ��׼ GIF ·��
				L"/gdiplus/FrameDelay",     // GDI+ ���ɵ� GIF
				L"/exif/FrameDelay",        // �������������ܵ�·��
				L"/grctlext/Delay"          // �Զ�����չ·��
			};

			for (int i = 0; i < ARRAYSIZE(metadataPaths) ; i++) {
				const wchar_t* path = metadataPaths[i];
				hr = pMetadataReader->GetMetadataByName(path, &propVar);
				if (SUCCEEDED(hr)) {
					if (propVar.vt == VT_UI2) {
						delay = static_cast<UINT32>(propVar.uiVal * 10); // ��λת����1/100 �� -> ����
					} else if (propVar.vt == VT_UI4) {
						delay = propVar.ulVal;
					}
					PropVariantClear(&propVar);
					break; // �ɹ��ҵ�������ѭ��
				}
			}

			PropVariantClear(&propVar);
			pMetadataReader->Release();
		}

		// ȷ���ӳٲ�������Сֵ��10ms��
		delay = max(delay, 10U);

		return hr;
	}
	
	HRESULT CreateRender(HWND Hwnd, int Width, int Height)
	{
		HRESULT Hr ;
		D2D1_RENDER_TARGET_PROPERTIES rtProps = D2D1::RenderTargetProperties();
		D2D1_HWND_RENDER_TARGET_PROPERTIES hwndProps = D2D1::HwndRenderTargetProperties(Hwnd, D2D1::SizeU(Width, Height));
		Hr = m_D2D1Factory->CreateHwndRenderTarget(rtProps, hwndProps, &m_RenderTarget);

		return Hr;
	}

	// �� WIC λͼת��Ϊ Direct2D λͼ
	HRESULT ConvertWicBitmapToD2DBitmap(IWICImagingFactory* pWICFactory, IWICBitmapSource* wicBitmap, ID2D1Bitmap** d2dBitmap) {
		IWICFormatConverter* formatConverter = nullptr;
		HRESULT hr = pWICFactory->CreateFormatConverter(&formatConverter);

		if (SUCCEEDED(hr)) {
			// ת��Ϊ 32bppPBGRA ��ʽ��Direct2D ֧�ֵĸ�ʽ��
			hr = formatConverter->Initialize(
				wicBitmap,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.0f,
				WICBitmapPaletteTypeMedianCut
				);

			if (SUCCEEDED(hr)) {
				// ���� Direct2D λͼ
				hr = m_RenderTarget->CreateBitmapFromWicBitmap(
					formatConverter,
					NULL,
					d2dBitmap
					);
			}

			formatConverter->Release();
		}

		return hr;
	}

	HRESULT LoadGIF(LPCWSTR FilePath) {
		CoInitialize(nullptr);
		IWICImagingFactory* pWICFactory = nullptr;
		HRESULT hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pWICFactory)
			);

		if (SUCCEEDED(hr)) {
			IWICBitmapDecoder* pDecoder = nullptr;
			hr = pWICFactory->CreateDecoderFromFilename(FilePath, nullptr, GENERIC_READ,WICDecodeMetadataCacheOnLoad, &pDecoder);
			if (SUCCEEDED(hr)) {
				UINT frameCount = 0;
				hr = pDecoder->GetFrameCount(&frameCount);
				if (SUCCEEDED(hr)) {
					for (UINT i = 0; i < frameCount; ++i) {
						IWICBitmapFrameDecode* pFrame = nullptr;
						hr = pDecoder->GetFrame(i, &pFrame);
						
						if (SUCCEEDED(hr)) {
							UINT Width = 0, Height = 0;
							pFrame->GetSize(&Width, &Height);
							// ��ȡ֡�ӳ�ʱ�䣨GIF ���ӳ�ʱ�䵥λ�� 1/100 �룩
							UINT delay = 0;
							hr = GetGIFDelayFromFrame(pFrame, delay);
							if (SUCCEEDED(hr)) {
								m_FrameDelays.Add(delay); // ʹ�� CAtlArray ��� std::vector
							}else
							{
							m_FrameDelays.Add(100);
							}
							
							// �� WIC ֡ת��Ϊ Direct2D λͼ
							ID2D1Bitmap* pBitmap = nullptr;
							hr = ConvertWicBitmapToD2DBitmap(pWICFactory,pFrame, &pBitmap);
							if (SUCCEEDED(hr)) {
								m_FrameBitmaps.Add(pBitmap);
							}

							pFrame->Release();
						}
					}
				}
				pDecoder->Release();
			}
			pWICFactory->Release();
		}
		CoUninitialize();
		return hr;
	}

	// ��Ⱦ GIF ֡
	void RenderGIF() {
		HRESULT hr;
		if (!m_FrameBitmaps.IsEmpty()) {
			static int currentFrame = 0;
			
			
			ID2D1Bitmap* Bitmap = m_FrameBitmaps[currentFrame];
			D2D1_SIZE_U SizeU = Bitmap->GetPixelSize();
			D2D1_SIZE_F SizeF = Bitmap->GetSize();


			ResizeDpi(&SizeU);
			hr = m_RenderTarget->Resize(SizeU);
			m_RenderTarget->BeginDraw();
			ZxDebugEx((__FUNCTION__"():: Render Size: {%d, %d} \n", SizeU.width, SizeU.height));
			
			//m_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
			// ��ȡ��ȾĿ���С
			D2D1_SIZE_F renderTargetSize = m_RenderTarget->GetSize();
			
			m_RenderTarget->DrawBitmap(Bitmap, D2D1::RectF(0, 0, SizeF.width, SizeF.height));
			m_RenderTarget->EndDraw();

			// ����֡����
			currentFrame = (currentFrame + 1) % m_FrameBitmaps.GetCount();
			Sleep(m_FrameDelays[currentFrame]); // ����֡���
		}
	}

	VOID ResizeDpi(D2D1_SIZE_F* Size)
	{
		float DpiX, DpiY;
		m_RenderTarget->GetDpi(&DpiX, &DpiY);

		Size->width *= DpiX/96.0f;
		Size->height *= DpiY/96.f;
	}

	VOID ResizeDpi(D2D1_SIZE_U* Size)
	{
		float DpiX, DpiY;
		m_RenderTarget->GetDpi(&DpiX, &DpiY);

		Size->width *= (UINT32)DpiX/96;
		Size->height *= (UINT32)DpiY/96;
	}

public:
	CAtlArray<ID2D1Bitmap*> m_FrameBitmaps;
	CAtlArray<UINT32> m_FrameDelays;
	ID2D1HwndRenderTarget* m_RenderTarget;
};

class CHoverFrame : public C32Window
{
public:
	CHoverFrame()
	{
		SetDelete();
		m_MouseStatus = E32MouseEventUnCapture;
	}
	
	~CHoverFrame()
	{
		//PostQuitMessage(0); 		
	}

	DWORD Register()
	{
		DWORD Atom = RegisterClassEx32(WC32_HOVER_FRAME, NULL,  NULL, IDC_TOOLBOX, IDI_TOOLBOX, IDI_TOOLBOX, NULL);

		ZxDebugEx((__FUNCTION__"():: Atom : 0x%08x \n", Atom));

		return Atom;
	}

public:
	BOOL CreateControl(HWND Parent = NULL)
	{
		if(Register())
		{
			DWORD dwExStyle = WS_EX_TOPMOST |WS_EX_TOOLWINDOW;
			DWORD dwStyle =  WS_POPUP | WS_VISIBLE;
			
			HWND Hwnd = Create(dwExStyle, WC32_HOVER_FRAME, LANG_MAIN_TITLE, dwStyle,  CW_USEDEFAULT, CW_USEDEFAULT,  CW_USEDEFAULT,  CW_USEDEFAULT, Parent);
			if (Hwnd)
			{
				C32SetCenterPosDesktop(Hwnd);
				m_ToolTip.Create(TTS_BALLOON| TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT , CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_Hwnd);
				RECT TipRect = {0, 0, 80, 80};
				m_ToolTip.AddTool(Hwnd, L"С����", &TipRect, (ULONG_PTR)0, TTF_SUBCLASS);
				RECT TipRect1 = {80, 80, 200, 200};
				m_ToolTip.AddTool(Hwnd, L"��û�", &TipRect1, (ULONG_PTR)1, TTF_SUBCLASS);

				Show(SW_SHOW);
				return TRUE;
			}

		}

		return FALSE;
	}

public:
	
	// ���·ֲ㴰��
	HBITMAP LoadPng(LPCWSTR filePath, int& width, int& height) {
		Gdiplus::Image image(filePath);
		if (image.GetLastStatus() != Gdiplus::Ok) return NULL;

		width = image.GetWidth();
		height = image.GetHeight();

		// ���� 32 λ ARGB λͼ��֧�� Alpha ͨ����
		Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
		Gdiplus::Graphics g(bmp);
		g.DrawImage(&image, 0, 0, width, height);

		// ת��Ϊ HBITMAP
		HBITMAP hBitmap = NULL;
		bmp->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitmap);
		delete bmp;
		return hBitmap;
	}

	// 4. �ڴ��ڹ����л��ƣ�ʹ�� UpdateLayeredWindow��
	// ʹ�� Alpha ͨ�����´���
	void UpdateWindowWithAlpha(HWND hwnd, HBITMAP hBitmap, int width, int height) {
		if (!hwnd || !hBitmap || width <= 0 || height <= 0) return;

		HDC hdcScreen = GetDC(NULL);
		HDC hdcMem = CreateCompatibleDC(hdcScreen);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

		// ���û�Ϻ�����ʹ�� Alpha ͨ����
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

		// ���·ֲ㴰��
		POINT ptDst = { 0, 0 };
		POINT ptSrc = { 0, 0 };
		SIZE size = { width, height };
		UpdateLayeredWindow(hwnd, hdcScreen, &ptDst, &size, 
			hdcMem, &ptSrc, 0, &blend, ULW_ALPHA);

		// ������Դ
		SelectObject(hdcMem, hOldBitmap);
		DeleteDC(hdcMem);
		ReleaseDC(NULL, hdcScreen);
	}

	//�����¼�
public:
	virtual BOOL CALLBACK OnCreate(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		// ���÷ֲ�����  
		SetWindowLong(m_Hwnd, GWL_EXSTYLE, GetWindowLong(m_Hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		//// ����͸��ɫ   
		//COLORREF clTransparent = RGB(255, 255, 255);
		//SetLayeredWindowAttributes(m_Hwnd, clTransparent, 0, LWA_COLORKEY);
		
		
		DWORD Style = GetStyle();
		Style &= ~WS_CAPTION;
		SetStyle(Style);


		// ���� PNG ͼƬ
		int width;
		int height;
		CString PngPath = YUAN_SHEN_DIRECTORY;
		PngPath += L"YuanShen.PNG";
		HBITMAP hBitmap = LoadPng(PngPath, width, height);
		// ���´���
		UpdateWindowWithAlpha(m_Hwnd, hBitmap, width, height);

		SetTimer(m_Hwnd, 1, 1000*60*60, NULL);
		CreateTray();

		return TRUE;
	}

	virtual BOOL CALLBACK OnEraseBkgnd(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		return FALSE;
	}

	virtual BOOL CALLBACK OnPaint(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_Hwnd, &ps);
		GetPos();

		Gdiplus::Bitmap Image(L"XueXiZhuShou\\YuanShen.PNG"); // �滻Ϊ���͸��ͼƬ·��
		Gdiplus::Graphics Graphics(hdc);
		
		Graphics.DrawImage(&Image, 0, 0, Image.GetWidth(), Image.GetHeight());
		
		EndPaint(m_Hwnd, &ps);

		int  Width = 0;
		int  Height = 0;
		Width = Image.GetWidth();
		Height = Image.GetHeight();
		SetPos(0, 0, Width, Height,SWP_NOMOVE | SWP_NOZORDER);
		return TRUE;
	}

	BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		C32MenuEx Menu;

		Menu.CreatePopup();
		Menu.AppendItemString(IDM_HIDE_WINDOW, L"����");
		Menu.Display(m_Hwnd);

		return Handle;
	}

	BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;

		if (C32CommandIsMenu(wParam, lParam))
		{
			Handle = TRUE;

			if(C32CommandMenuId(wParam) == IDM_HIDE_WINDOW)
			{
				Show(SW_HIDE);
			}else if(C32CommandMenuId(wParam) == IDM_SHOW_WINDOW)
			{
				Show(SW_SHOW);
			}else if(C32CommandMenuId(wParam) == IDM_EXIT)
			{
				DeleteTray();
				PostQuitMessage(0);
			}else if(C32CommandMenuId(wParam) == IDM_TEST_1)
			{
				C32HoverMsg* Msg = new C32HoverMsg();
				Msg->SetDelete();
				Msg->Register();
				Msg->CreateMsg();
				Msg->Show(SW_SHOW);
			}else if(C32CommandMenuId(wParam) == IDM_FREE_SOFTWARE)
			{
				CreateDonationWindow(m_Hwnd, L"��л�����Ͽɣ��һ����Ŭ��");
			}
				
		}

		return Handle;
	}

	BOOL CALLBACK OnLButtonDown(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		ZxDebugEx((__FUNCTION__"():: \n"));
		SetCapture(NULL);
		PostMessage(m_Hwnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
		//SetCapture(m_Hwnd);

		//Handle = TRUE;

		return Handle;
	}

	BOOL CALLBACK OnTimer(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;

		Handle = TRUE;

		PostMessage(m_Hwnd, WM_COMMAND, IDM_TEST_1, 0);

		return Handle;
	}

	//BOOL CALLBACK OnMouseHover(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	//{
	//	BOOL Handle = FALSE;
	//	ZxDebugEx((__FUNCTION__"():: \n"));
	//	//PostMessage(m_Hwnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	//	if (m_MouseStatus == E32MouseEventEnter)
	//	{
	//		m_MouseStatus = E32MouseEventHover;
	//		
	//		Handle = TRUE;
	//	}
	//	
	//	//SetCapture(m_Hwnd);
	//	return Handle;
	//}

	//BOOL CALLBACK OnMouseMove(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	//{
	//	ZxDebugEx((__FUNCTION__"():: \n"));
	//	
	//	BOOL Handle = TRUE;
	//	//return FALSE;
	//	TRACKMOUSEEVENT Event = {};
	//	Event.cbSize = sizeof(TRACKMOUSEEVENT);
	//	Event.dwFlags = TME_HOVER|TME_LEAVE;
	//	Event.dwHoverTime = HOVER_DEFAULT;
	//	Event.hwndTrack = m_Hwnd;
	//	if (GetCapture() != m_Hwnd)
	//	{
	//		
	//		Handle = _TrackMouseEvent(&Event);
	//		if (Handle)
	//		{
	//			ZxDebugEx((__FUNCTION__"():: m_MouseStatus : %d \n", m_MouseStatus));
	//			if (C32MouseEventIsTrack(m_MouseStatus) == FALSE)
	//				m_MouseStatus = E32MouseEventEnter;
	//		}
	//	}
	//	
	//	return Handle;
	//}

	//BOOL CALLBACK OnMouseLeave(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	//{
	//	BOOL Handle = FALSE;
	//	ZxDebugEx((__FUNCTION__"():: \n"));
	//	
	//	ZxDebugEx((__FUNCTION__"():: Relase\n"));
	//	Handle = ReleaseCapture();
	//	m_MouseStatus = E32MouseEventLeave;
	//	

	//	return Handle;
	//}

	BOOL OnTray( WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;

		DWORD Msg = LOWORD(lParam);
		CHAR* String = C32DbgGetTrayNotifyString(Msg);
		ZxDebug((__FUNCTION__"():: C32WM_TRAY :wParam:%p  %s (0x%04x)\n", wParam, String,Msg));
		switch(Msg)
		{
		case WM_RBUTTONDOWN:
			{
				// ��ʾ�Ҽ��˵�
				SetForegroundWindow(m_Hwnd);
				m_TrayMenu.Display(m_Hwnd);
				Handle = TRUE;
			}
			break;
		case WM_LBUTTONDBLCLK:
			{
				Show(SW_SHOW);
				Handle = TRUE;
			}
			break;
		}

		return Handle;
	}

	virtual BOOL CALLBACK OnDefault(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		switch(uMsg)
		{
		case C32WM_TRAY:
			Handle = OnTray(wParam, lParam, lResult);
			break;

		default:
			Handle = FALSE;
		}
		return Handle;
	}

	VOID CreateTray()
	{
		m_TrayMenu.CreatePopup();
		m_TrayMenu.AppendItemString( IDM_FREE_SOFTWARE, L"����");
		m_TrayMenu.AppendItemString( IDM_SHOW_WINDOW, L"��ʾ����");
		m_TrayMenu.AppendItemString( IDM_TEST_1, L"����");
		m_TrayMenu.AppendItemString( IDM_EXIT, L"�˳�");

		AddTray(IDI_TOOLBOX, L"��������");
	}

	BOOL AddTray(int iIcon, LPCWSTR Tip, UINT uId = 1)
	{
		// ����ϵͳ����ͼ��
		NOTIFYICONDATA nid = { sizeof(nid) };
		nid.hWnd = m_Hwnd;
		nid.uID = uId;
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = C32WM_TRAY;
		nid.hIcon = LoadIcon(C32Hinstance, MAKEINTRESOURCE(iIcon));
		nid.uVersion = 0;
		wcscpy_s(nid.szTip, Tip);
		return Shell_NotifyIcon(NIM_ADD, &nid);
	}

	BOOL DeleteTray()
	{
		NOTIFYICONDATA nid = { sizeof(nid) };
		nid.hWnd = m_Hwnd;
		nid.uID = 1;
		return Shell_NotifyIcon(NIM_DELETE, &nid);
	}

public:
	/*BOOL CreateTip()
	{
		C32MessageBoxTip(L"DDD");
		return TRUE;
		DWORD ExStyle = 0;
		DWORD Style = WS_OVERLAPPEDWINDOW;
		 Create(ExStyle, WC32_TOOL_BOX, L"С��������?", Style, 300, 300, 100, 100, NULL);
		C32Window* Tip = new C32Window();
		Tip->SetDelete();
		Tip->Loop();
		return TRUE;
	}*/

	C32ToolTip		m_ToolTip;
	C32MenuEx       m_TrayMenu;
	E32MouseEvent  m_MouseStatus; //���״̬��
};


BOOL CreateHoverFrame()
{
	g_HoverFrame = new CHoverFrame();

	g_HoverFrame->CreateControl();

	g_HoverFrame->m_iAccelerator = IDC_TOOLBOX;

	g_HoverFrame->Loop();
	return TRUE;
}