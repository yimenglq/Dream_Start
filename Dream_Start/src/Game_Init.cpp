#include"../head/Game_Init.h"

 



//������Ϣ������
LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return Init::GetInit()->msg_Proc(hwnd, message, wParam, lParam);
	
 }


LRESULT	Init::msg_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	static HWND hwndBtn;
	static bool v_one = TRUE;
	//static std::vector<std::map<int, HWND> > v;
	static std::map<int, HWND> hwnd_map;

	if (v_one)
	{
		//std::map<int, HWND> hwnd_map;
		hwnd_map.insert(std::pair<int, HWND>(0, hwnd));
		//������򴰿ھ�� ���Ӵ���id
		//v.push_back(hwnd_map);
		v_one = FALSE;
	}
	


	switch (msg)
	{
	case WM_CREATE:
	{
		//DWMNCRENDERINGPOLICY dwmNpy = DWMNCRP_DISABLED;
		//DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &dwmNpy, sizeof(dwmNpy));
	}
		

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_NCHITTEST:
		/*���͵�������ȷ�����ڵ��ĸ����ֶ�Ӧ���ض�����Ļ���ꡣ 
		���磬������ƶ������»��ͷ���갴ť����Ӧ�� WindowFromPoint �Ⱥ����ĵ���ʱ�����ܻᷢ����������� 
		���δ������꣬��Ὣ��Ϣ���͵�����·��Ĵ��ڡ� 
		������Ϣ�����͵��Ѳ������Ĵ��ڡ�*/
		if (hwnd == hwnd_map[0])
			SetFocus(hwnd);
		if (hwnd_map.count(1) != 0)
			if(hwnd_map[1] == hwnd)
				MessageBox(NULL, L"��һ�����ư�ť", L"button", MB_OK);
		return HitTestNCA(hwnd, wParam, lParam);

		break;

	case WM_NCCALCSIZE://�ڱ�����㴰�ڹ������Ĵ�С��λ��ʱ���͡�
		//ͨ���������Ϣ�������ڵĴ�С��λ�÷�������ʱ��Ӧ�ó�����Կ��ƴ��ڹ����������ݡ�
		if (wParam == 1)
			return 0;
		//return 0;
		//return 0;

	case WM_ACTIVATE:
		
	{
		//�������洰�ڹ����� (DWM) ���ڵķǿͻ��˳������Ե�ֵ��
		DWMNCRENDERINGPOLICY dwmNpy = DWMNCRP_DISABLED;//
		//ģ��͸��
		DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &dwmNpy, sizeof(dwmNpy));
		
		MARGINS margins = { 0 };
		margins.cxLeftWidth = LEFTEXTENDWIDTH;     // 15
		margins.cxRightWidth = RIGHTEXTENDWIDTH;    // 8
		margins.cyBottomHeight = BOTTOMEXTENDWIDTH; // 30
		margins.cyTopHeight = TOPEXTENDWIDTH;      // 20
		margins = { -1 };//��������ģ��͸��

		DwmExtendFrameIntoClientArea(hwnd, &margins);

	}
	break;

	case WM_KEYDOWN:
		KeyDown(hwnd,msg,wParam,lParam,hwndBtn,hwnd_map);
		{
			RECT extendedFrameBounds{ 0,0,0,0 };
			HRESULT hr = DwmGetWindowAttribute(hwnd,
				DWMWA_EXTENDED_FRAME_BOUNDS,
				&extendedFrameBounds,
				sizeof(extendedFrameBounds));
			if (hr);
		
		break;
		}


	case WM_CTLCOLORBTN:
		if ((HWND)lParam == hwndBtn)
		{
			HWND hbn = (HWND)lParam;
			HDC hdc = (HDC)wParam;
			RECT rc;
			TCHAR text[64];

			
			//SetTextColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, TRANSPARENT);
			//DrawText(hdc, text, _tcslen(text), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			return (INT_PTR)CreateSolidBrush(RGB(255, 0, 255));
		}


	default:
		break;
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


//�Ӵ�����Ϣ����ȡ  ͨ���������༼����
LRESULT CALLBACK Cid_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{


	return	Init::GetInit()->Cid_Proc_init(hwnd, msg, wParam, lParam);			
}

LRESULT Init::Cid_Proc_init(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_NCHITTEST:
		MessageBox(NULL, L"����", L"d", MB_OK);
		return 0;
		



	default:
		break;
	}



	return CallWindowProc( Proc, hwnd, msg, wParam, lParam);
}



Init* Init::init = nullptr;
WNDPROC Init::Proc = nullptr;

WNDCLASS Init::Init_wndclass()//LRESULT ( Init::*w_PROC)(HWND, UINT, WPARAM, LPARAM))
{
	WNDCLASS wndclass;
	wndclass.lpfnWndProc = wndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hIcon = LoadIcon(NULL, IDI_INFORMATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH +1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;

	return wndclass;
}

//
bool	Init::InitMainWindow()
{


	WNDCLASS wndclass;
	wndclass.lpfnWndProc = wndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hIcon = LoadIcon(NULL, IDI_INFORMATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, L"ע�ᴰ��ʧ����\nλ���� Init::InitMainWindow 55", TEXT("ʧ��"), MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	RECT R = { 0, 0, 900, 700 };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	HWND Main_Hwnd = CreateWindow(
					szClassName,NULL,
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,CW_USEDEFAULT,R.right,R.bottom,
					NULL,NULL,hInstance,NULL
	);
	if (!Main_Hwnd)
	{
		MessageBox(NULL, L"ʧ��\nλ�� Init::InitMainWindow 68", L"ʧ��", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	ShowWindow(Main_Hwnd,SW_SHOW);
	UpdateWindow(Main_Hwnd);

	//Init_wndclass();
	return 1;
}

//��Ϣѭ��
bool	Init::Run()
{
	MSG msg = {0};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);//  ��������Կ��Ϣת��Ϊ�ַ���Ϣ�� ������Ϣ
			DispatchMessage(&msg);//����Ϣ���ȵ����ڹ���(  �ַ���Ϣ )
		}
		else
		{

		}
	}

	return (int)msg.wParam;
}


Init* Init::GetInit()
{
	return init;
}




// Hit test the frame for resizing and moving.
LRESULT Init::HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// Get the point coordinates for the hit test.
	POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

	// Get the window rectangle.
	RECT rcWindow;
	GetWindowRect(hWnd, &rcWindow);

	// Get the frame rectangle, adjusted for the style without a caption.
	RECT rcFrame = { 0 };
	AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

	// Determine if the hit test is for resizing. Default middle (1,1).
	USHORT uRow = 1;
	USHORT uCol = 1;
	bool fOnResizeBorder = false;

	// Determine if the point is at the top or bottom of the window.
	if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + TOPEXTENDWIDTH)
	{
		fOnResizeBorder = (ptMouse.y < (rcWindow.top - rcFrame.top));
		uRow = 0;
	}
	else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - BOTTOMEXTENDWIDTH)
	{
		uRow = 2;
	}

	// Determine if the point is at the left or right of the window.
	if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + LEFTEXTENDWIDTH)
	{
		uCol = 0; // left side
	}
	else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - RIGHTEXTENDWIDTH)
	{
		uCol = 2; // right side
	}

	// Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
	LRESULT hitTests[3][3] =
	{
		{ HTTOPLEFT,    fOnResizeBorder ? HTTOP : HTCAPTION,    HTTOPRIGHT },
		{ HTLEFT,       HTNOWHERE,     HTRIGHT },
		{ HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
	};

	return hitTests[uRow][uCol];
}


void Init::KeyDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam,HWND &hwndBtn,std::map<int,HWND> &hm)
{
	if (wParam == 'W')
	{
		
		hwndBtn = CreateWindow(L"button", L"text",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			105*(hm.size()-1), -10, 100, 100, hwnd, (HMENU)hm.size(), hInstance, NULL
			);
		hm.insert(std::pair<int, HWND>(hm.size(), hwndBtn));
		Proc  =	(WNDPROC)SetWindowLong(hwndBtn, GWLP_WNDPROC, (LONG)Cid_Proc);

		
		//SetWindowLong(,,GWL_)
	}

	if (wParam == 'B')
	{
		Thumbnail(hwnd);
		//EnableBlurBehind(hwnd);
	}

}
void Init::KeyDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

}


HRESULT Init::EnableBlurBehind(HWND	hwnd)
{
	HRESULT hr = S_OK;

	DWM_BLURBEHIND dwmBd = {0};//ָ�����洰�ڹ����� (DWM) ģ���������ԡ�
	dwmBd.dwFlags = DWM_BB_ENABLE;
	dwmBd.fEnable = TRUE;
	dwmBd.hRgnBlur = NULL;//��Ӧ��ģ�����صĹ������е����� NULL ֵ������������������Ӧ��ģ����
		
	hr = DwmEnableBlurBehindWindow(hwnd, &dwmBd);

	return hr;
}
HRESULT Init::Thumbnail(HWND hwnd)
{
	HRESULT hr = S_OK;
	HTHUMBNAIL thumbnail = NULL;

	// Register the thumbnail
	hr = DwmRegisterThumbnail(hwnd, FindWindow(TEXT("Progman"), NULL), &thumbnail);//TEXT("Progman")
	if (SUCCEEDED(hr))
	{
		// Specify the destination rectangle size
		RECT dest = { 0,50,1000,800 };

		// Set the thumbnail properties for use
		DWM_THUMBNAIL_PROPERTIES dskThumbProps;
		dskThumbProps.dwFlags = DWM_TNP_SOURCECLIENTAREAONLY | DWM_TNP_VISIBLE | DWM_TNP_OPACITY | DWM_TNP_RECTDESTINATION| DWM_TNP_RECTSOURCE;
		dskThumbProps.fSourceClientAreaOnly = FALSE;
		dskThumbProps.fVisible = TRUE;
		dskThumbProps.opacity = 100;//(255 * 70) / 100;
		dskThumbProps.rcDestination = dest;
		dskThumbProps.rcSource = {0,0,300,100};

		// Display the thumbnail
		hr = DwmUpdateThumbnailProperties(thumbnail, &dskThumbProps);
		if (SUCCEEDED(hr))
		{
			// ...
		}
	}
	return hr;

}

