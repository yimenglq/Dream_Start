#include"../head/Game_Init.h"

 



//窗口消息处理函数
LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return Init::GetInit()->msg_Proc(hwnd, message, wParam, lParam);
	
 }





//子窗口消息（截取  通过窗口子类技术）
LRESULT CALLBACK CID_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return Init::GetInit()->Cid_Proc_init(hwnd, message, wParam, lParam);

}

LRESULT CALLBACK CID_System_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return Init::GetInit()->Cid_System_Proc_init(hwnd, message, wParam, lParam);

}



//消息循环
bool	Init::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);//  将虚拟密钥消息转换为字符消息。 翻译消息
			DispatchMessage(&msg);//将消息调度到窗口过程(  分发消息 )
		}
		else
		{

		}
	}

	return (int)msg.wParam;
}



Init* Init::init = nullptr;
std::map<std::wstring, WNDPROC>	Init::Proc_map;

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
	wndclass.lpfnWndProc =	wndProc;
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
		MessageBox(NULL, L"注册窗口失败了\n位置在 Init::InitMainWindow 55", TEXT("失败"), MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}


	RECT R = { 0, 0, 900, 700 };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	

	wndclass.lpfnWndProc = CID_proc;
	wndclass.cbWndExtra = 256;
	wndclass.hbrBackground = CreateSolidBrush(RGB(255, 0, 255));	 //(HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszClassName = szClassName_Cid;

if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, L"注册窗口失败了\n位置在 Init::InitMainWindow 112", TEXT("失败"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	HWND Main_Hwnd = CreateWindow(
	szClassName, NULL,
	WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT, CW_USEDEFAULT, R.right, R.bottom,
	NULL, NULL, hInstance, NULL
	);
	if (!Main_Hwnd)
	{
		MessageBox(NULL, L"失败\n位置 Init::InitMainWindow 133", L"失败", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	
	/*HWND Main = CreateWindow(
		szClassName_Cid, NULL,
		WS_OVERLAPPEDWINDOW,
		0, 0, R.right, R.bottom,
		NULL, NULL, hInstance, NULL
	);*/
	DWORD h = 	GetLastError();


	ShowWindow(Main_Hwnd,SW_SHOW);
	UpdateWindow(Main_Hwnd);

	//Init_wndclass();
	return 1;
}




HINSTANCE Init::GethInstance()
{
	return hInstance;
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
		if (ptMouse.x >= rcWindow.right - RIGHTEXTENDWIDTH && ptMouse.x <= rcWindow.right)
		{
			uCol = 3;
		}

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
	else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - 1)
	{
		uCol = 2; // right side
	}

	// Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
	LRESULT hitTests[3][4] =
	{
		{ HTTOPLEFT,    fOnResizeBorder ? HTTOP : HTCAPTION,    HTTOPRIGHT,	HTCLOSE },
		{ HTLEFT,       HTNOWHERE,     HTRIGHT ,},
		{ HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT ,},
	};

	return hitTests[uRow][uCol];
}


void Init::KeyDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam,HWND &hwndBtn,std::map<int,HWND> &hm)
{
	if (wParam == 'W')
	{
		
		hwndBtn = CreateWindow(BUTTON_, L"text",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			105*(hm.size()-1), -10, 100, 100, hwnd, (HMENU)hm.size(), hInstance, NULL
			);
		hm.insert(std::pair<int, HWND>(hm.size(), hwndBtn));
		Proc_map.insert(std::make_pair(BUTTON_,(WNDPROC)SetWindowLong(hwndBtn, GWLP_WNDPROC, (LONG)CID_proc)));

		
		//SetWindowLong(,,GWL_)
	}
	

	if (wParam == 'B')
	{
		Thumbnail(hwnd);
		//EnableBlurBehind(hwnd);
	}


	if (VK_ESCAPE == wParam)
	{
		if (IDYES == MessageBox(hwnd, L"确定退出？", L"提示", MB_YESNO|MB_DEFBUTTON2))
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
	}

	if (VK_TAB == wParam)
	{

		hwndBtn =  CreateWindow(NULL, NULL,
			WS_CHILD|WS_VISIBLE,  10, 1, 100, 300, hm.at(0), (HMENU)hm.size(), hInstance, NULL);
		if (hwndBtn)
		{
			hm.insert(std::make_pair(hm.size(), hwndBtn));
		}
			
	}

}
void Init::KeyDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

}


HRESULT Init::EnableBlurBehind(HWND	hwnd)
{
	HRESULT hr = S_OK;

	DWM_BLURBEHIND dwmBd = {0};//指定桌面窗口管理器 (DWM) 模糊隐藏属性。
	dwmBd.dwFlags = DWM_BB_ENABLE;
	dwmBd.fEnable = TRUE;
	dwmBd.hRgnBlur = NULL;//将应用模糊隐藏的工作区中的区域。 NULL 值将在整个工作区后面应用模糊。
		
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

WNDPROC	Init::GetWndProc() {

	return CID_proc;

}

TCHAR* Init::GetszClassName_Cid()
{
	return szClassName_Cid;
}

WNDPROC	Init::GetwndProc_System_Cid()
{
	return CID_System_proc;
}