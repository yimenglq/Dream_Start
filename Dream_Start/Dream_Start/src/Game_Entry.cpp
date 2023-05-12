#include"../head/Game_Entry.h"

#include<Windows.h>





int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	try
	{
		Game_Enty game_enty(hInstance);
		Game_Enty g(0);
		g = game_enty;


		if (!game_enty.InitMainWindow())
			return 0;
	
		return game_enty.Run();
	}
	catch (MyClaMyExceptionss &e)
	{
		cout<< e.toSing() << endl;
	}
	
}


std::map<int, HWND> Game_Enty::hwnd_map;

BYTE** Game_Enty::g_pBit = nullptr;
BITMAPFILEHEADER** Game_Enty::g_pbitmapadr = nullptr;
BITMAPINFO** Game_Enty::g_pbitmf = nullptr;
BYTE*	Game_Enty::g_pBit_bitmap = nullptr;
Game_Enty* Game_Enty::game_Enty = nullptr;

Game_Enty::Game_Enty(HINSTANCE hInstance) :Init::Init(hInstance) { Game_Enty::game_Enty = this; };


bool Game_Enty::Run()
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


bool Game_Enty::InitMainWindow()
	{

	if (!Init::InitMainWindow())
		return 0;
	return 1;
	}


LRESULT	Game_Enty::msg_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static	WIN_ID win = { 0 };

		static TEXTMETRICW textFont = {0};
		
		static HWND hwndBtn;
		static bool v_one = TRUE;
		static delete_ dele(GethInstance());
		de = &dele;
		//static std::vector<std::map<int, HWND> > v;
		//static std::map<int, HWND> hwnd_map;


		if (v_one)
		{
			//std::map<int, HWND> hwnd_map;
			hwnd_map.insert(std::pair<int, HWND>(0, hwnd));
			//管理程序窗口句柄 与子窗口id
			//v.push_back(hwnd_map);
			v_one = FALSE;
		}



		switch (msg)
		{
		case WM_CREATE://2
		{	
			dele.Set_g_hwnd_part(hwnd);
			dele.CreatrBUTTON();

			hdc = GetDC(hwnd);
			GetTextMetrics(hdc, &textFont);
			hwndBtn = CreateWindow(BUTTON_, L"创建游戏道具", WS_CHILD|WS_VISIBLE | BS_PUSHBUTTON,0,0,textFont.tmAveCharWidth * 14,
				textFont.tmHeight * 1.5,hwnd,(HMENU)(ID_GAME_PROP_ADD), GethInstance(), NULL
				);
			ReleaseDC(hwnd, hdc);
			hwnd_map.insert(std::make_pair(ID_GAME_PROP_ADD, hwndBtn));

			Proc_map.insert(std::make_pair(BUTTON_,(WNDPROC)SetWindowLong(hwndBtn, GWL_WNDPROC, (LONG)GetwndProc_System_Cid())));

			//Proc_map.insert(std::make_pair(BUTTON_, (WNDPROC)SetWindowLong(hwndBtn, GWL_WNDPROC, (LONG)GetwndProc_System_Cid())));
			//DWMNCRENDERINGPOLICY dwmNpy = DWMNCRP_DISABLED;
			//DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &dwmNpy, sizeof(dwmNpy));
		}


		break;

		case WM_CLOSE:
		{
			int i = 0;

			if (i)
			{

			}
		}

		break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:

			break;
		/*case 0x00AE:
		case 0x00AF:
			return 0;*/
			
		case WM_NCPAINT://拦截掉窗口框架则不绘制

			return 0;
			break;
		/*case WM_NCMOUSEMOVE:

			return 0;*/
		case	WM_NCACTIVATE://3

			//if (lParam)
			
				return -1;//返回 -1，不绘制非客户区的东西
			
			//return 0;
			break;


		case WM_NCHITTEST:
			/*发送到窗口以确定窗口的哪个部分对应于特定的屏幕坐标。
			例如，当光标移动、按下或释放鼠标按钮或响应对 WindowFromPoint 等函数的调用时，可能会发生这种情况。
			如果未捕获鼠标，则会将消息发送到光标下方的窗口。
			否则，消息将发送到已捕获鼠标的窗口。*/
			//if (hwnd == hwnd_map[0])
			//	//SetFocus(hwnd);
			//if (hwnd_map.count(1) != 0)
			//	if (hwnd_map[1] == hwnd)
			//		MessageBox(NULL, L"第一个绘制按钮", BUTTON_, MB_OK);
			return HitTestNCA(hwnd, wParam, lParam);

			break;

		case WM_NCCALCSIZE://在必须计算窗口工作区的大小和位置时发送。1
			//通过处理此消息，当窗口的大小或位置发生更改时，应用程序可以控制窗口工作区的内容。
			//if (wParam == 1)
			
		//{MARGINS margins = { 0 };
		//margins.cxLeftWidth = LEFTEXTENDWIDTH;     // 15
		//margins.cxRightWidth = RIGHTEXTENDWIDTH;    // 8
		//margins.cyBottomHeight = BOTTOMEXTENDWIDTH; // 30
		//margins.cyTopHeight = TOPEXTENDWIDTH;      // 20
		////margins = {-1 };//整个窗口模糊透明

		//DwmExtendFrameIntoClientArea(hwnd, &margins);
		//}		//return 0;
			return 0;
			//return 0;
			break;

		case WM_ACTIVATE://4
		{
			//break;
			HRESULT hr;
			hr = S_OK;
			static int i = 1;
			if (i)
			{

				//{
				//	//HRESULT hr = S_OK;

				//	// Create and populate the blur-behind structure.
				//DWM_BLURBEHIND bb = { 0 };

				//	// Specify blur-behind and blur region.
					//bb.dwFlags = DWM_BB_ENABLE;
					//bb.fEnable = true;
					//bb.hRgnBlur = NULL;

				//	// Enable blur-behind.
					//hr = DwmEnableBlurBehindWindow(hwnd, &bb);
				//	if (SUCCEEDED(hr))
				//	{
				//		// ...
				//	}
				//	//return hr;
				//}

				//设置桌面窗口管理器 (DWM) 窗口的非客户端呈现属性的值。
				//DWMNCRENDERINGPOLICY dwmNpy = DWMNCRP_DISABLED;//
				//模糊透明
				//DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &dwmNpy, sizeof(dwmNpy));
				
				MARGINS margins = { 0 };
				margins.cxLeftWidth = LEFTEXTENDWIDTH;     // 15
				margins.cxRightWidth = RIGHTEXTENDWIDTH;    // 8
				margins.cyBottomHeight = BOTTOMEXTENDWIDTH; // 30
				margins.cyTopHeight = TOPEXTENDWIDTH;      // 20
				//margins = {-1 };//整个窗口模糊透明

				hr = DwmExtendFrameIntoClientArea(hwnd, &margins);
				i = 0;
			}
			//PostMessage(hwnd, WM_NCCALCSIZE, (WPARAM)1, 0);
			return hr;
		}
		
		break;


		case WM_COMMAND://子窗口控件
			//break;
			switch (HIWORD(wParam))
			{

			case	BN_CLICKED:
					if (ID_GAME_PROP_ADD == LOWORD(wParam))//LOWORD(wParam)子窗口/菜单id
					{
						win.id = ID_GAME_PROP_ADD_MAIN;
						win.T_window_name = L"\0";
						//SetFocus(hwnd);
						//SendMessage(hwnd_map.at(0), WM_KILLFOCUS, (WPARAM)hwnd, 0);
						LPCREATESTRUCT pcre = (LPCREATESTRUCT)malloc(sizeof(CREATESTRUCT));
						memset(pcre,0, sizeof(CREATESTRUCT));
						
						pcre->hMenu = (HMENU)ID_GAME_PROP_ADD_MAIN;
						GetClientRect(hwnd, &window_Cli);//GetszClassName_Cid()
						hwndBtn = 	CreateWindow(GetszClassName_Cid(),NULL,//L"创建装备/道具",
								WS_OVERLAPPEDWINDOW |WS_VISIBLE,
							//WS_CHILD|WS_VISIBLE|WS_OVERLAPPEDWINDOW ,
							window_Cli.right * 25 / 100, window_Cli.bottom * 5 / 100,
							window_Cli.right * 50 / 100, window_Cli.bottom * 90 / 100, NULL, NULL,//(HMENU)ID_GAME_PROP_ADD_MAIN,
							GethInstance(), (LPVOID)&win);
						free(pcre);
						
						if (hwndBtn)
						{
							if (!hwnd_map.count(ID_GAME_PROP_ADD_MAIN) >= 1)
								hwnd_map.insert(std::make_pair(ID_GAME_PROP_ADD_MAIN, hwndBtn));
							else
							{
								hwnd_map.find(ID_GAME_PROP_ADD_MAIN)->second = hwndBtn;
							}
							SetWindowLong(hwndBtn, GWL_EXSTYLE, WS_EX_ACCEPTFILES | WS_EX_LAYERED);//|WS_EX_LAYERED);//
							
							SetLayeredWindowAttributes(hwndBtn, RGB(255, 0,0), (255 * 85) / 100, LWA_ALPHA | LWA_COLORKEY);
							SetWindowPos(hwndBtn, HWND_TOPMOST, 0, 0, window_Cli.right * 50 / 100, window_Cli.bottom * 90 / 100, SWP_NOMOVE | SWP_NOACTIVATE);
							//SetParent(hwndBtn, hwnd_map.at(0));
							//SetFocus(hwndBtn);
						}
						
					}
					break;

			//case EN_KILLFOCUS:




				default:
					return DefWindowProc(hwnd, msg, wParam, lParam);
			}
			return 0;


		case WM_SETCURSOR:

		{
			static	int i = 1;
			i++;
		}
			break;

		case WM_KEYDOWN:
			KeyDown(hwnd, msg, wParam, lParam, hwndBtn, hwnd_map);
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





		case WM_KILLFOCUS:

		{
			static	int i = 1;
			i++;
		}

		break;

		default:
			break;
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	

}

//子窗口
LRESULT Game_Enty::Cid_Proc_init(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static TCHAR clasname[MAX_PATH]; 
	static BYTE* pFILE_buff = nullptr,* pBit = nullptr;
	
	static	BITMAPFILEHEADER * pbitmapadr;
	static	BITMAPINFO* pbitmf;
	static	RECT	c_rect = { 0 };
	
	static	WIN_ID	win;
	HWND chwnd;
	FILE *fs = nullptr;
	PAINTSTRUCT pt;
	HDC	hdc;
	MSG mssg;
	
	g_pbitmapadr = &pbitmapadr;
	g_pbitmf = &pbitmf;
	g_pBit = &pBit;



	switch (msg)
	{


	case WM_NCHITTEST:
	{

		//MessageBox(NULL, L"悬浮", L"d", MB_OK);
		//SetFocus(hwnd);
		////SetCapture(hwnd);
		//SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		//DWORD err = GetLastError();
		//SetLayeredWindowAttributes(hwnd, RGB(255, 0, 0), (255 * 70) / 100, LWA_ALPHA | LWA_COLORKEY);
		break;

	}
	case WM_NCPAINT:


		//return 0;
		break;

	case WM_NCACTIVATE:

		return -1;


	case	WM_NCCALCSIZE:

		//return 0;
		break;
	
	case WM_ACTIVATE:
	{
		//break;
		HRESULT hr;
		hr = S_OK;
		static int i = 1;
		if (i)
		{
			

			//客户区模糊  感觉效果没有 分层窗口有意思
			//{
				//HRESULT hr = S_OK;

			//	// Create and populate the blur-behind structure.
				//DWM_BLURBEHIND bb = { 0 };

				// Specify blur-behind and blur region.
				//bb.dwFlags = DWM_BB_ENABLE;
				//bb.fEnable = true;
				//bb.hRgnBlur = NULL;

			//	// Enable blur-behind.
				//hr = DwmEnableBlurBehindWindow(hwnd, &bb);
			//	if (SUCCEEDED(hr))
			//	{
			//		// ...
			//	}
			//return hr;
			//}



			MARGINS margins = { 0 };
			margins.cxLeftWidth = LEFTEXTENDWIDTH;     // 15
			margins.cxRightWidth = RIGHTEXTENDWIDTH;    // 8
			margins.cyBottomHeight = BOTTOMEXTENDWIDTH; // 30
			margins.cyTopHeight = TOPEXTENDWIDTH;      // 20
			//margins = {-1 };//整个窗口模糊透明

			hr = DwmExtendFrameIntoClientArea(hwnd, &margins);//模糊
			i = 0;
		}
		//PostMessage(hwnd, WM_NCCALCSIZE, (WPARAM)1, 0);
		return hr;
	}
	break;


	case WM_DROPFILES://拖拽文件
		//HDROP
	{
		//int fileName_i = 	DragQueryFile((HDROP)wParam, 0, (LPWSTR)FILE_buff, NULL);
		if (pFILE_buff)
			free(pFILE_buff);


		pFILE_buff = (BYTE*)malloc(MAX_PATH);
		
		DragQueryFile((HDROP)wParam, 0, (LPWSTR)pFILE_buff, MAX_PATH);
		//bitmapadr = * (BITMAPFILEHEADER*)FILE_buff;
		/*CHAR d[MAX_PATH];
		while (*pFILE_buff != '\0')
		{
			static int i = 0,j = 0;
			
			d[j] = *pFILE_buff;
			
			j ++;
			pFILE_buff += 2;
			d[j] = '\0';
		}*/
		
		
		
		openFile_read(fs, &pFILE_buff, L"rb");

		
		
		pBit = pFILE_buff + ((BITMAPFILEHEADER*)pFILE_buff)->bfOffBits;
		pbitmapadr = (BITMAPFILEHEADER*)pFILE_buff;
		pbitmf = (BITMAPINFO *)((BITMAPFILEHEADER*)pFILE_buff + 1);
		
		InvalidateRect(hwnd, NULL, FALSE);
		UpdateWindow(hwnd);
		Button_Enable(hwnd_map.at(ID_SAVE), TRUE);
		//DragQueryFile((HDROP)wParam, 0, (LPWSTR)FILE_buff, ((BITMAPFILEHEADER*)FILE_buff)->bfSize);


		//DragAcceptFiles(hwnd,)
		//SetParent(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_EDIT), hwnd);
		   
	}
		return 0;



	case WM_NCCREATE:

		if(((LPCREATESTRUCT)lParam)->lpszName != NULL)
		if (memcmp(((LPCREATESTRUCT)lParam)->lpszName, L"显示游戏道具", sizeof(L"显示游戏道具")) == 0)
		{

			SetWindowLong(hwnd, GWL_WNDPROC, (LONG)Proc_Text);

			//goto R;
		}

		break;



	case WM_CREATE:
		//break;

		if (	(	(LPWIN_ID)(((LPCREATESTRUCT)lParam)->lpCreateParams)	)->id == ID_GAME_PROP_ADD_MAIN)
		{
			
			//break;
			HWND Foreground	=	GetForegroundWindow();
			 chwnd = CreateWindow(EDIT_, NULL,
				 //WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,
				WS_BORDER|WS_CHILD|WS_VISIBLE|ES_LEFT|ES_MULTILINE| 
				 ES_AUTOVSCROLL,
				
				((LPCREATESTRUCT)lParam)->cx * 25/100, ((LPCREATESTRUCT)lParam)->cy * 50/100,
				((LPCREATESTRUCT)lParam)->cx*50/100, ((LPCREATESTRUCT)lParam)->cy* 20/100,hwnd,
				(HMENU)ID_GAME_PROP_ADD_MAIN_EDIT,GethInstance(), NULL
					
				);
			 if (chwnd)
			 {	
				PostMessage(chwnd, EM_SETLIMITTEXT, 10, 0);
				if(hwnd_map.count(ID_GAME_PROP_ADD_MAIN_EDIT) >= 1)
					if (!(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_EDIT) == chwnd))
					{
						if (Proc_map.count(EDIT_) >= 1)
						{
							Proc_map.find(EDIT_)->second = ((WNDPROC)SetWindowLong(chwnd, GWL_WNDPROC, (LONG)GetwndProc_System_Cid()));
							hwnd_map.find(ID_GAME_PROP_ADD_MAIN_EDIT)->second = chwnd;
						}	
					}
					else 
					{

					}
				else
				{
					Proc_map.insert(std::make_pair(EDIT_, (WNDPROC)SetWindowLong(chwnd, GWL_WNDPROC, (LONG)GetwndProc_System_Cid())));
					hwnd_map.insert(std::make_pair(ID_GAME_PROP_ADD_MAIN_EDIT, chwnd));
				}
			 }
			HDC hdc =	GetDC(NULL);
			SIZE sz = {0};
			GetTextExtentPoint32(hdc,SAVE,2,&sz);

			ReleaseDC(NULL,hdc);
			 chwnd = CreateWindow(BUTTON_,SAVE,
				 //WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,
				 WS_BORDER | WS_CHILD | WS_VISIBLE |  BS_DEFPUSHBUTTON,
				 ((LPCREATESTRUCT)lParam)->cx * 25 / 100 + ((LPCREATESTRUCT)lParam)->cx * 50 / 100,
				 ((LPCREATESTRUCT)lParam)->cy * 50 / 100 + ((LPCREATESTRUCT)lParam)->cy * 20 / 100 + 1,
				 sz.cx*1.5,sz.cy*1 ,
				 hwnd,
				 (HMENU)ID_SAVE, GethInstance(), NULL

			 );
			 if (chwnd)
			 {
				 
				 if (hwnd_map.count(ID_SAVE) >= 1)
					 if (!(hwnd_map.at(ID_SAVE) == chwnd))
					 {
						 
							 hwnd_map.find(ID_SAVE)->second = chwnd;
						
					 }
					 else
					 {

					 }
				 else
				 {
					// Proc_map.insert(std::make_pair(SAVE, (WNDPROC)SetWindowLong(chwnd, GWL_WNDPROC, (LONG)GetwndProc_System_Cid())));
					 hwnd_map.insert(std::make_pair(ID_SAVE, chwnd));
				 }
			 }



				win = { ID_GAME_PROP_ADD_PROP_SHOW,L"显示游戏道具" };
				chwnd = CreateWindow(GetszClassName_Cid(), (TCHAR*)(&(win.T_window_name)) + 2, WS_VISIBLE | WS_POPUPWINDOW&~WS_BORDER, 0, 0, 0,
				 0, NULL, NULL, GethInstance(), (LPVOID)&win
			 );
				if (chwnd)
				{
					if (hwnd_map.count(ID_GAME_PROP_ADD_PROP_SHOW) >= 1)
						if (!(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW) == chwnd))
						{
							
							hwnd_map.find(ID_GAME_PROP_ADD_PROP_SHOW)->second = chwnd;
							
						}
						else
						{

						}
					else
					{
						hwnd_map.insert(std::make_pair(ID_GAME_PROP_ADD_PROP_SHOW, chwnd));
					}
				}
				 

			 SetWindowLong(chwnd, GWL_EXSTYLE, WS_EX_LAYERED);

			 SetLayeredWindowAttributes(chwnd, RGB(255, 0, 255), 255 * 80 / 100, LWA_ALPHA | LWA_COLORKEY);
			 SetWindowPos(chwnd, HWND_TOPMOST, 0, 0, 100, 100, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
			 MoveWindow(chwnd, ((LPCREATESTRUCT)lParam)->cx + ((LPCREATESTRUCT)lParam)->x + 10, ((LPCREATESTRUCT)lParam)->y, 150, 185, TRUE);

		}


		
		break;

	case WM_MOVE:
		if(hwnd_map.count(ID_GAME_PROP_ADD_MAIN) >= 1)
		if (hwnd_map.at(ID_GAME_PROP_ADD_MAIN) == hwnd)
			{
				//int x, y;
				//x = GET_X_LPARAM(lParam);
				//y = GET_Y_LPARAM(lParam);
				RECT rt = { 0 }, rtc = { 0 };
				GetWindowRect(hwnd, &rt);
				GetClientRect(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), &rtc);
				MoveWindow(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), rt.right + 10, rt.top, rtc.right , rtc.bottom, FALSE);

			}

		break;

	case WM_MOUSEMOVE:
		if (hwnd_map.at(ID_GAME_PROP_ADD_MAIN) == hwnd)
			if (MK_LBUTTON == wParam)
			{
				//int x, y;
				//x = GET_X_LPARAM(lParam);
				//y = GET_Y_LPARAM(lParam);
				RECT rt = { 0 }, rtc = { 0 };
				GetWindowRect(hwnd, &rt);
				GetClientRect(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), &rtc);
				MoveWindow(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), rt.right + 10, rt.top, rt.right + 10 + rtc.right, rt.top+ rtc.bottom, FALSE);

			}



		break;


	case WM_NCMOUSEMOVE:
		if(hwnd_map.at(ID_GAME_PROP_ADD_MAIN) == hwnd)
		if (MK_LBUTTON == wParam)
		{
			//int x, y;
			//x = GET_X_LPARAM(lParam);
			//y = GET_Y_LPARAM(lParam);
			RECT rt = { 0 }, rtc = {0};
			GetWindowRect(hwnd, &rt);
			GetClientRect(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), &rtc);
			MoveWindow(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), rt.right + 10, rt.top, rtc.right, rtc.bottom, FALSE);

		}
		
		

		break;

	case WM_SYSCOMMAND:
		if ((wParam & 0xFFF0) == SC_MOVE)
		{
			mssg = {0};
			mssg.message = WM_SYSCOMMAND;
			mssg.hwnd = hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW);
			mssg.wParam = wParam;
			mssg.lParam = lParam;
			_beginthread(Game_Enty::thread, 0, &mssg);//多线程
			//SendMessage(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), WM_SYSCOMMAND, wParam, lParam);

			
		}
			


		break;



	case WM_COMMAND:

		if (ID_GAME_PROP_ADD_MAIN_EDIT == LOWORD(wParam))
		{
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				//SetFocus(hwnd);
				break;

			case EN_KILLFOCUS:
				//SetFocus(hwnd);
				break;

			default:
				break;
			}	
		}
		if (ID_SAVE == LOWORD(wParam))
		{
			switch HIWORD(wParam)
			{
			case BN_CLICKED:
			{
				if (!pbitmf)
					Button_Enable(hwnd_map.at(ID_SAVE),FALSE);//禁用按钮  变灰
				else
				{

					PROP prop;
					prop.sizeImage = pbitmf->bmiHeader.biSizeImage;
					prop.Name = L"撒旦糊";
					prop.Picture = pbitmf;
					prop.pBit = pBit;
					prop.pbitmapadr = pbitmapadr;
					prop.Illustrate.resize((SendMessage(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_), WM_GETTEXTLENGTH, 0, 0)+1) );
					GetWindowText(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_), (LPWSTR)prop.Illustrate._Unchecked_begin(), prop.Illustrate.size());
					
					Backpack::Save_Prop(prop);
					Backpack::Read_Prop(&prop);
					

				return 0;
				}

				
			}

				

				
			}

		}

		break;

		



	case WM_PAINT:
		//break;
		if (hwnd_map.count(ID_GAME_PROP_ADD_MAIN) >= 1 && \
			hwnd_map.at(ID_GAME_PROP_ADD_MAIN) == hwnd)
		{	
			
			
			GetClientRect(hwnd, &c_rect);
			hdc = BeginPaint(hwnd, &pt);
			HPEN pen = 	CreatePen(PS_DASHDOT,10,RGB(255,0,255));
			SelectObject(hdc, pen);
			//HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 0));
			//SelectObject(hdc,	GetStockObject( DC_BRUSH));
			//SetDCBrushColor(pt.hdc, RGB(255, 0, 0));
			//SetBkColor(pt.hdc, RGB(255, 0, 255));
			Rectangle(hdc, c_rect.right * 25 / 100, 0, c_rect.right * 75/100 , c_rect.bottom * 50 / 100);
				//CreateDIBSection()
				if (pbitmf != nullptr)
				{
					
					
					HDC hdc_cm;
					hdc_cm =	CreateCompatibleDC(hdc);
					
					/*SetDIBitsToDevice(hdc_cm, 0, 0,
						(*g_pbitmf)->bmiHeader.biWidth, (*g_pbitmf)->bmiHeader.biHeight,
						0, 0, 0, (*g_pbitmf)->bmiHeader.biHeight, (*g_pBit), (*g_pbitmf), DIB_RGB_COLORS);*/

					SetDIBitsToDevice(hdc_cm, window_Cli.top, window_Cli.left,
						pbitmf->bmiHeader.biWidth, pbitmf->bmiHeader.biHeight,
						0, 0, 0, pbitmf->bmiHeader.biHeight, pBit, pbitmf, DIB_RGB_COLORS);
					SetStretchBltMode(hdc, HALFTONE);

					/*StretchDIBits(pt.hdc, 25, 25, 100, 100,
						0, 0, (*g_pbitmf)->bmiHeader.biWidth, (*g_pbitmf)->bmiHeader.biHeight, *g_pBit, (*g_pbitmf),
						DIB_RGB_COLORS, SRCCOPY
					);*/
					StretchDIBits(hdc, c_rect.right * 25 / 100 , 0, c_rect.right*50/100, c_rect.bottom*50/100,
						0, 0, pbitmf->bmiHeader.biWidth, pbitmf->bmiHeader.biHeight, pBit, pbitmf,
						DIB_RGB_COLORS, SRCCOPY
					);
					
					/*EndPaint(hwnd, &pt);
					return 0;*/
				}
				EndPaint(hwnd, &pt);
				//StretchDIBits(hdc,)

				
		}
		if (hwnd_map.count(ID_GAME_PROP_ADD) >= 1 && \
			hwnd_map.at(ID_GAME_PROP_ADD) == hwnd)
		{
			int i = 0;

		}
		if (hwnd_map.count(ID_GAME_PROP_ADD_PROP_SHOW) >= 1)
		{
			//SendMessage(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), WM_PAINT, 0, 0);
			InvalidateRect(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), NULL, TRUE);
			//UpdateWindow(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW));
		}
			//SendMessage(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), WM_PAINT, 0, 0);
		break;
	case WM_SETCURSOR:
		
		//SetFocus(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_EDIT));
		break;


	case WM_KILLFOCUS:
		
	{

		int i = 0;

	}


		break;

	case WM_CLOSE:
		if(hwnd_map.count(ID_GAME_PROP_ADD_MAIN) >= 1)
			if(hwnd_map.at(ID_GAME_PROP_ADD_MAIN) == hwnd)
		PostMessage(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), WM_CLOSE, 0, 0);
		break;


	default:

		break;
	}


	//GetClassName(hwnd, clasname, MAX_PATH);
	//if (wmemcmp(clasname, GetszClassName_Cid(), 7) == 0)
	//{
R:		return DefWindowProc(hwnd, msg, wParam, lParam);
	//}
	

	//return CallWindowProc(Proc, hwnd, msg, wParam, lParam);

}

//窗口控件
LRESULT	Game_Enty::Cid_System_Proc_init(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT pt;
	HDC hdc;
	TCHAR className[30];
	GetClassName(hwnd, className, 30);//获取窗口的注册类名
	_wcslwr_s(className);//宽字符串小写


	if (memcmp(className, EDIT_, sizeof(EDIT_) - 2) == 0)
	{
		switch (msg)
		{


			return Edit_Proc(hwnd, msg, wParam, lParam);


		}
	}

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		if (memcmp(className, EDIT_, sizeof(EDIT_) - 2) == 0)
		{
			HWND Foreground_Whnd = GetForegroundWindow();
			if(	GetForegroundWindow() != hwnd)
				SetFocus(hwnd);

		}

		if (memcmp(className, BUTTON_, sizeof(BUTTON_) - 2) == 0)
		{
			SendMessage(GetParent(hwnd), WM_COMMAND, MAKEWPARAM(ID_GAME_PROP_ADD,BN_CLICKED ), 0);
			return 0;
		}
			
	}
	
		//return 0;
	break;


	/*case WM_PAINT:
		
		break;*/




	default:
		break;
	}


	

	return CallWindowProc(Proc_map.at(className), hwnd, msg, wParam, lParam);//窗口子类回调（子控件原来系统处理的函数）
}










void Game_Enty::KeyDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, HWND& hwndBtn, std::map<int, HWND>& hm)
{
	if (wParam == 'W')
	{

		hwndBtn = CreateWindow(BUTTON_, L"text",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			105 * (hm.size() - 1), -10, 100, 100, hwnd, (HMENU)hm.size(), GethInstance(), NULL
		);
		hm.insert(std::pair<int, HWND>(hm.size(), hwndBtn));
		Proc_map.insert(std::make_pair(BUTTON_,(WNDPROC)SetWindowLong(hwndBtn, GWLP_WNDPROC, (LONG)GetWndProc())));


		//SetWindowLong(,,GWL_)
	}


	if (wParam == 'B')
	{
		Thumbnail(hwnd);
		//EnableBlurBehind(hwnd);
	}


	if (VK_ESCAPE == wParam)
	{
		if (IDYES == MessageBox(hwnd, L"确定退出？", L"提示", MB_YESNO | MB_DEFBUTTON2))
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
	}

	if (VK_TAB == wParam)
	{
		static int i = 0;
		if (!i)
		{
			if (hm.count(1))	
			{
				ShowWindow(hm.at(1), SW_SHOW);
				i = 1;
				return;
			}


			static	Backpack b((wchar_t*)TEXT("backpack"), GethInstance());
			b.SethwndParent(hwnd);
			b.Sethmenu((HMENU)1);

			if (!b.init())
				return;

			/*hwndBtn = CreateWindow(b.Get_szClassName(), NULL,
			*/	//WS_CHILD | WS_VISIBLE, 10, 1, 100, 300, hm.at(0), (HMENU)hm.size(), GethInstance(), NULL);
			if (b.Gethwnd())
			{
				hm.insert(std::make_pair(1, b.Gethwnd()));
				i = 1;
			}
		}
		else
		{
			ShowWindow(hm.at(1),SW_HIDE);
			i = 0;
			return;  
		}

	}
}


bool	Game_Enty
::	openFile_read(FILE* fe,OUT BYTE** pbuff	/* 文件名字与存储的位置  */, const wchar_t* mode)
{
	_wfopen_s(&fe, (wchar_t*)*pbuff, mode);//读

	_fseeki64(fe, 0, SEEK_END);

	int ifs = _ftelli64(fe);
	try
	{
		free(*pbuff);
	}
	catch (const std::exception&)
	{
		goto A;
	}
	A:	*pbuff = (BYTE*)malloc(ifs);
		_fseeki64(fe, 0, SEEK_SET);

		fread(*pbuff, ifs, 1, fe);
		fclose(fe);
	return 1;

	/*pBit = pFILE_buff + ((BITMAPFILEHEADER*)pFILE_buff)->bfOffBits;
	pbitmapadr = (BITMAPFILEHEADER*)pFILE_buff;
	pbitmf = (BITMAPINFO*)((BITMAPFILEHEADER*)pFILE_buff + 1);*/
}



//ID_GAME_PROP_ADD_PROP_SHOW
LRESULT CALLBACK	Game_Enty::Proc_Text(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	return Game_Enty::game_Enty->Proc_Text_ADD_SHOW(hwnd, msg, wParam, lParam);
}

LRESULT Game_Enty::Proc_Text_ADD_SHOW(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool z = 1;


	PAINTSTRUCT pt;
	HBRUSH hBrush;
	HBITMAP hbmap;
	BITMAP bitmap;
	HDC hdc;
	HGDIOBJ gdiobj;
	HWND chwnd;
	RECT rt;

	switch (msg)
	{

	case WM_CREATE:

		chwnd = CreateWindow(STATIC_, L"请输入描述",  WS_CHILD |   SS_LEFT|SS_NOTIFY,
			20, 130, 128, 48, hwnd, (HMENU)ID_GAME_PROP_ADD_MAIN_STATIC_, GethInstance(), NULL
		);
		
		if (chwnd)
		{
			if (hwnd_map.count(ID_GAME_PROP_ADD_MAIN_STATIC_) >= 1)
				if (hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_) != chwnd)
				{

					hwnd_map.find(ID_GAME_PROP_ADD_MAIN_STATIC_)->second = chwnd;
					Proc_map.find(STATIC_)->second = (WNDPROC)SetWindowLong(chwnd, GWL_WNDPROC, (LONG)Game_Enty::Proc_Text_ADD_SHOW_STATIC);

				}
				else;
			else
			{
				hwnd_map.insert(std::make_pair(ID_GAME_PROP_ADD_MAIN_STATIC_, chwnd));
				Proc_map.insert(std::make_pair(STATIC_, (WNDPROC)SetWindowLong(chwnd, GWL_WNDPROC, (LONG)Game_Enty::Proc_Text_ADD_SHOW_STATIC)));
				HDC hdc =	GetDC(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_));
				
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 0, 0));
				//SetBkColor(hdc, RGB(255 * 50 / 100, 255 * 50 / 100, 255 * 50 / 100));
				ReleaseDC(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_), hdc);
				LOGFONT font;
				font.lfHeight = 16*80/100;
				font.lfWidth = 0;
				font.lfEscapement = 0;
				font.lfOrientation = 0;
				font.lfWeight = FW_BOLD;
				font.lfItalic = false;
				font.lfUnderline = false;
				font.lfStrikeOut = false;
				font.lfEscapement = 0;
				font.lfOrientation = 0;
				font.lfOutPrecision = OUT_DEFAULT_PRECIS;
				font.lfClipPrecision = CLIP_STROKE_PRECIS | CLIP_MASK | CLIP_TT_ALWAYS | CLIP_LH_ANGLES;
				font.lfQuality = ANTIALIASED_QUALITY;
				font.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;

				HFONT hFont = ::CreateFontIndirect(&font);
				SendMessage(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_), WM_SETFONT, (WPARAM)hFont, TRUE);
				SetWindowText(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_), L"请输入描述");
				
				
			}
		}



		return 0;



	case WM_PAINT:
		//break;
		rt = {50,25,90,100};
		ValidateRect(hwnd, &rt);
 		hdc = BeginPaint(hwnd, &pt);

		hBrush = CreateSolidBrush(RGB(255 * 50 / 100, 255 * 50 / 100, 255 * 50 / 100));

		gdiobj = SelectObject(pt.hdc, hBrush);

		RoundRect(pt.hdc, 20, 130, 180, 200, 10, 10);

		SelectObject(pt.hdc, gdiobj);
		DeleteObject(hBrush);

		if (*g_pbitmapadr)
		{
			
			/*DWORD c;
			SetLastError(0);
			c = GetLastError();*/
			//g_pBit_bitmap = g_pBit;
			//g_pBit_bitmap = (BYTE*)malloc((*g_pbitmf)->bmiHeader.biSizeImage);
			/*hbmap = CreateDIBSection(NULL, *g_pbitmf, 1, (void**)&g_pBit_bitmap, NULL, NULL);
			c = GetLastError();
			memcpy((BYTE*)g_pBit_bitmap, *g_pBit, (*g_pbitmf)->bmiHeader.biSizeImage);
			SetLastError(0);*/
			HDC c_hdc = CreateCompatibleDC(pt.hdc);
			/*HDC c_hdc_1 = CreateCompatibleDC(pt.hdc);*/
			//c = GetLastError();
			//gdiobj = SelectObject(c_hdc, hbmap);
			// c =	GetLastError();
			// SetLastError(0);
			//GetObject(hbmap, sizeof(BITMAP), &bitmap);
			//SetStretchBltMode(pt.hdc, HALFTONE);
			//StretchBlt(pt.hdc, 25, 25, 100, 100, c_hdc, 0, 0, (*g_pbitmf)->bmiHeader.biWidth, (*g_pbitmf)->bmiHeader.biHeight, SRCCOPY);
			//c = GetLastError();
			//SetLastError(0);
			////BitBlt(pt.hdc, 0, 0, 1000, 1100, c_hdc, 0, 0, SRCCOPY);
			//c = GetLastError();
			SetDIBitsToDevice(c_hdc, 0, 0,
				(*g_pbitmf)->bmiHeader.biWidth, (*g_pbitmf)->bmiHeader.biHeight,
				0, 0, 0, (*g_pbitmf)->bmiHeader.biHeight, (*g_pBit), (*g_pbitmf), DIB_RGB_COLORS);

			SetStretchBltMode(pt.hdc, HALFTONE);

			/*StretchDIBits(c_hdc_1, 25, 25, 100, 100,
				0, 0, (*g_pbitmf)->bmiHeader.biWidth, (*g_pbitmf)->bmiHeader.biHeight, *g_pBit, (*g_pbitmf),
				DIB_RGB_COLORS, SRCCOPY
			);*/
			StretchDIBits(pt.hdc, 25, 25, 100, 100,
				0, 0, (*g_pbitmf)->bmiHeader.biWidth, (*g_pbitmf)->bmiHeader.biHeight, *g_pBit, (*g_pbitmf),
				DIB_RGB_COLORS, SRCCOPY
			);
			/*	SelectObject(c_hdc, gdiobj);
				DeleteObject(hbmap);
				*/
			DeleteDC(c_hdc);
			/*DeleteDC(c_hdc_1);*/

			if (z)
			{
				
				if (hwnd_map.count(ID_GAME_PROP_ADD_MAIN_STATIC_) >= 1)
				{
					ShowWindow(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_), SW_SHOW);
					SetTimer(Game_Enty::hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_), 1, 5000, NULL);

					z = 0;
				}
					


			}
		}

		else
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 0));

			gdiobj = SelectObject(pt.hdc, hBrush);
			RoundRect(pt.hdc, 25, 25, 100, 100, 10, 10);
			SelectObject(pt.hdc, gdiobj);
			DeleteObject(hBrush);
		}




		
		//pt.rcPaint = { 0,0,0,0 };
-		EndPaint(hwnd, &pt);


		return 0;


	case WM_CTLCOLORSTATIC://拦截WM_CTLCOLORSTATIC消息 //控制静态文本框的文字颜色与背景颜色
	{
		if ((HWND)lParam == GetDlgItem(hwnd, ID_GAME_PROP_ADD_MAIN_STATIC_))//获得指定标签句柄用来对比
		{
			SetTextColor((HDC)wParam, RGB(255, 0, 0));//设置文本颜色
			SetBkMode((HDC)wParam, TRANSPARENT);//设置背景透明
			//SetBkColor((HDC)wParam, RGB(255, 0, 0));
		}

		return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
	}





	case WM_STATIC_HIDE:

		z = wParam;

		return wParam;




	default:
		break;
	}







	return DefWindowProc(hwnd, msg, wParam, lParam);

}

//预览界面的文字描述
LRESULT Game_Enty::Proc_Text_ADD_SHOW_STATIC_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	static	ULONG textlength = 0;
	static	LPTCH text = nullptr;
	static	RECT rt = {0};

	static int i = 1;

	switch (msg)
	{
	case WM_CREATE:

		//SetTimer(Game_Enty::hwnd_map.at(ID_GAME_PROP_ADD_MAIN_STATIC_), 1, 100,NULL );

		break;

	case WM_ERASEBKGND:
		/*SetTextColor((HDC)wParam, RGB(50 * 255 / 100, 0,0));
		SetBkMode((HDC)wParam, TRANSPARENT);
		SetBkColor((HDC)wParam, RGB(50 * 255 / 100, 0 * 255 / 100,0 * 255 / 100));
		SetWindowText(hwnd, L"sdhauhud1");*/
		break;
		return 0;

	case WM_TIMECHANGE:

		break;

	case WM_TIMER:
		if (i)
		{
			GetWindowRect(hwnd, &rt);
			POINT t;
			t.x = rt.left;
			t.y = rt.top;


			ScreenToClient(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), &t);
			rt.left = t.x;
			rt.top = t.y;
			i = 0;
		}

		textlength = SendMessage(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_EDIT), WM_GETTEXTLENGTH, 0, 0) * 2 + 2;
		if (!textlength)
			return 0;
		free(text);
		InvalidateRect(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), &rt, FALSE);
		UpdateWindow(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW));
		text = (LPTCH)malloc(textlength);
		if (text)
			SendMessage(hwnd_map.at(ID_GAME_PROP_ADD_MAIN_EDIT), WM_GETTEXT, textlength, (LPARAM)text);
		//SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)text);
		//		SetWindowText(hwnd, text);
		Static_SetText(hwnd, text);

		return 0;


	case WM_DESTROY:

		KillTimer(hwnd, 1);
		SendMessage(hwnd_map.at(ID_GAME_PROP_ADD_PROP_SHOW), WM_STATIC_HIDE, 1, 0);

		break;


	default:
		break;
	}





	return CallWindowProc(Proc_map.at(STATIC_), hwnd, msg, wParam, lParam);
}




LRESULT		Game_Enty::Edit_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_NCCREATE:
		


		break;

	case WM_CREATE:
		
		break;

	default:
		break;
	}



	
	return CallWindowProc(Proc_map.at(EDIT_), hwnd, msg, wParam, lParam);

}


LRESULT CALLBACK	Game_Enty::Proc_Text_ADD_SHOW_STATIC(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	return Game_Enty::game_Enty->Proc_Text_ADD_SHOW_STATIC_(hwnd, msg, wParam, lParam);
}



//LRESULT Game_Enty::Save_Prop_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	return CallWindowProc(Proc_map.at(SAVE), hwnd, msg, wParam, lParam);
//}

//#include"../prop/"






VOID	Game_Enty::thread(PVOID p)
{
	MSG msg = *(LPMSG)p;

	SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
}


void Game_Enty::delete_prop()
{
	de->Init_view();

}