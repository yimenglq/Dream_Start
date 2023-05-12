#include"../head/Game_Backpack.h"

HINSTANCE	Backpack::hInstance = nullptr;
Backpack* Backpack::backpack = nullptr;
RECT Backpack::rect_window_main = {0};
std::map<int, HWND>	Backpack::	hwnd_map_Backpack;
std::map<int, PROP>	Backpack::	hwnd_map_Backpack_prop;




LRESULT CALLBACK wndProc_Backpack(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return	Backpack::GetBackpack()->backpack_Proc(hwnd,message,wParam,lParam);
}

//背包格子
LRESULT CALLBACK	Backpack::Prop_Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return Backpack::GetBackpack()->Prop_Proc_(hwnd, message, wParam, lParam);
}





LRESULT	Backpack::backpack_Proc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	static Preview_Prop pciew_Prop(hInstance);
	preview_prop = &pciew_Prop;
	PAINTSTRUCT ps;
	HDC hdc;



	switch (message)
	{
	case WM_CREATE:
		
	{	
		pciew_Prop.Setg_hwndPar(hwnd);

		//SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 500, 600, SWP_NOACTIVATE | SWP_NOMOVE);//窗口置顶
		SetTimer(hwnd, 1, 10000, NULL);
		this->hwnd = hwnd;

		GetClientRect(hwndParent, &rect_window_main);
		POINT pt = {rect_window_main.left,rect_window_main.top};
		ClientToScreen(hwndParent, &pt);
		rect_window_main.left = pt.x;
		rect_window_main.top = pt.y;
		
		MoveWindow(hwnd, rect_window_main.left+ rect_window_main.right/2 - hwnd_rect.right/2, rect_window_main.top + rect_window_main.bottom / 2 - hwnd_rect.bottom / 2, hwnd_rect.right,
			hwnd_rect.bottom, FALSE);

		//hwnd_map_Backpack.insert(std::make_pair(1,(HWND)0));
		
			Read_Prop(&prop);

		//hwnd_map_Backpack_prop.insert(std::make_pair(0,p));

		Prop_window_init(hwnd_map_Backpack_prop,hwnd_map_Backpack);
		pciew_Prop.Init_view();
	}
		break;

		

	case WM_NCHITTEST:
		//SetFocus(hwnd);
		//SetCapture(hwnd);
		SetWindowLong(hwnd, GWL_EXSTYLE,GetWindowLong(hwnd,GWL_EXSTYLE)|WS_EX_LAYERED);
		//SetLayeredWindowAttributes(hwnd, RGB(255,0,0), (255*70)/100, LWA_ALPHA|LWA_COLORKEY);
		break;

	case WM_NCCALCSIZE:

		/*if (wParam == 1)
			return 0;*/

		break;
	

	case WM_TIMER:

		

		return 0;

	case WM_KEYDOWN:
		
		
		if (wParam == 'W')
		{
			CreateWindow(
				TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE|LBS_STANDARD,
				400, 0, 100, 300, hwnd, (HMENU)1, hInstance, NULL

			);
		}

		


		break;
		
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON)
		{
			static	time_t t{0}, ts{0};
			time(&t);
			if (t - ts >= 1000)
			{
					POINT p;
					p.x	=	GET_X_LPARAM(lParam);
					p.y	=	GET_Y_LPARAM(lParam);
					ClientToScreen(hwnd, &p);
					//movewindow_B(p);
					
			}
			else
			{
				ts = t;
			}
		}

		if (wParam & MK_XBUTTON1)
		{
			BringWindowToTop(hwnd);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, 500, 600, SWP_NOMOVE);
		}

		break;

	//case WM_WINDOWPOSCHANGED:

	//	((WINDOWPOS*)lParam)->hwndInsertAfter = HWND_TOP;
	//	((WINDOWPOS*)lParam)->x = 0;
	//	((WINDOWPOS*)lParam)->y = 0;
	//	//return 0;
	//	break;
	//case WM_WINDOWPOSCHANGING:
	//{

	//	
	//	
	//	((WINDOWPOS*)lParam)->hwndInsertAfter = HWND_TOP;
	//	//((WINDOWPOS*)lParam)->flags = SWP_NOZORDER;
	//}
	//	
	//	
	//	//if ((wp.flags & SWP_NOZORDER) == 0)
	//		//_ = SetTopMostLater(); // 不使用弃元编译器会发出警告
	//
	//	break;


	
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		//SelectObject(hdc, (HGDIOBJ)WHITE_PEN);
		HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hbrush);
		
		//SetDCPenColor(hdc, RGB(0, 0, 255));
		Rectangle(hdc, 0, 0, 100, 300);
		DeleteObject(hbrush);
		SetBkColor(hdc, RGB(255, 255, 0));
		Rectangle(hdc, 300, 0, 100, 300);
		SelectObject(hdc, GetStockObject( DC_BRUSH));
		SetDCBrushColor(hdc, RGB(255, 0, 255));

		Rectangle(hdc, 200, 0, 100, 300);
		EndPaint(hwnd, &ps);

	}
		return 0;

	default:
		break;
	}


	return DefWindowProc(hwnd, message, wParam, lParam);
}


LRESULT	Backpack::Prop_Proc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static RECT xrect = { 0 };
	PROP *lpprop = nullptr;
	HDC xhdc;
	HPEN hPen,hPen_p;

	switch (msg)
	{
	case WM_CREATE:
		
		lpprop = (PROP*)((LPCREATESTRUCT)lParam)->lpCreateParams;

		SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG)lpprop);


		break;

	case WM_NCHITTEST:
		GetClientRect(hwnd, &xrect);
		SetFocus(hwnd);
		MouseEvents::MouseEvents_Track(hwnd);
		
		hPen = CreatePen(PS_SOLID,1,RGB(0,0,0));
		
		Draw_rectangle(hwnd, xrect, hPen,(HBRUSH)GetStockObject(	NULL_BRUSH));
		
		DeleteObject(hPen);
		
		break;

	case	WM_MOUSELEAVE://离开
		Draw_rectangle(hwnd, xrect, (HPEN)GetStockObject(WHITE_PEN), (HBRUSH)GetStockObject(NULL_BRUSH));
		MouseEvents::Reset(hwnd);
		
		return 0;
	
		

	case	WM_MOUSEHOVER://悬停
		//Draw_rectangle(hwnd, xrect, (HPEN)GetStockObject(NULL_PEN), (HBRUSH)GetStockObject(BLACK_BRUSH));
		//Draw_Prop_BMP(hwnd, &hwnd_map_Backpack_prop.at((int)GetMenu(hwnd)));
		lpprop = (lPPROP)GetWindowLong(hwnd, GWL_USERDATA);
		preview_prop->set_prop(*lpprop);
		preview_prop->Sethwnd_prop(lpprop);
		preview_prop->show_prop();

		return 0;

	case WM_KILLFOCUS:
		//Draw_rectangle(hwnd, xrect, (HPEN)GetStockObject(WHITE_PEN), (HBRUSH)GetStockObject(NULL_BRUSH));
		

		break;
	case	WM_ERASEBKGND:
		//Draw_rectangle(hwnd, xrect, (HPEN)GetStockObject(WHITE_PEN), (HBRUSH)GetStockObject(NULL_BRUSH));


		return 1;	/*(LPRECT)GetStockObject(NULL_BRUSH)*/;

	case WM_PAINT:
		Draw_Prop_BMP(hwnd, &hwnd_map_Backpack_prop.at((int)GetMenu(hwnd)));

		break;

	default:
		break;
	}
	
	return DefWindowProc( hwnd, msg, wParam, lParam);
}




//LRESULT Backpack::Save_Prop_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	return CallWindowProc(Proc_map, hwnd, msg, wParam, lParam);
//}



HWND	Backpack::Gethwnd()
{
	return hwnd;
}


Backpack* Backpack::GetBackpack()
{
	return backpack;
}


TCHAR* Backpack::Get_szClassName() {

	return szClassName;

}
void	Backpack::Sethmenu(HMENU hmenu_)
{
	hmenu = hmenu_;
}
HMENU	Backpack::Gethmenu()
{
	return	hmenu;
}


void	Backpack::SethwndParent(HWND hwndParent)
{
	this->hwndParent = hwndParent;
}

bool Backpack::init(){

	if (hwndParent == nullptr)
		return 0;
	if (!registerClass())
	{
		return 0;
	}
	hwnd = CreateWindow(szClassName, NULL,
		WS_POPUPWINDOW &~WS_BORDER ,
		10, 1, 600, 300, NULL, NULL, hInstance, NULL
	);
 
	if (!hwnd)
		return 0;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	
	return 1;
}


bool	 Backpack::registerClass() 
{
	if (hInstance == nullptr)
		return 0;
	wndclass.lpfnWndProc = wndProc_Backpack;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(PROP);
	wndclass.hInstance = hInstance;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;

	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, L"失败\n位置Backpack.cpp 70 ", L"注册窗口类失败", MB_OK);
		return 0;
	}

	wndclass.lpfnWndProc = Prop_Proc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szClassNaMe_Cid;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, L"失败\n位置Backpack.cpp 198 ", L"注册窗口类失败", MB_OK);
		return 0;
	}

	return 1;
}










bool	Backpack::Prop_window_init(std::map<int,PROP> &map_prop,std::map<int, HWND> &map_Id)
{
	HWND hwnd_c;
	if (!map_prop.empty())
	{
		int i = 0,x = 0,y = 0;
		for (auto pair : map_prop)
		{	
			
			
				hwnd_c = CreateWindow(szClassNaMe_Cid, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, x * 50 + 1 + (hwnd_rect.right * 50 / 100), y * 50 + 1 + hwnd_rect.bottom * 25 / 100,
					50, 50, hwnd, (HMENU)pair.first, hInstance, (LPVOID)&map_prop.at(i));
				DWORD err=	GetLastError();
			
			if (hwnd_c)
			{
				map_Id.insert(std::make_pair(pair.first, hwnd_c));
				
			}
			
			i++;
			x < 2 ? x++ : (x = 0,y++);
		}

	}
	
	return 1;

}



bool Backpack::movewindow_B(POINT &pt)
{


	MoveWindow(hwnd, pt.x, pt.y, 500,600,TRUE);

	return true;
}




void	Backpack::SetHinstance(HINSTANCE hIns)
{
	hInstance = hIns;
}


int Backpack::Set_hwnd_map_Backpack_prop(PROP *p)
{
	PROP pr;
	pr = *p;
	hwnd_map_Backpack_prop.insert(std::make_pair(hwnd_map_Backpack_prop.size(), pr));
	return 1;
}

BOOL	Backpack::Save_Prop(PROP prop)
{
	FILE* f, * flist, * flist_;
	prop_FILE_prop_listadd* list_prop;
	prop_FILE_top* list_prop_top;
	BYTE* buff;
	BOOL one = 1;
	size_t file_size = 0;

	buff = (BYTE*)malloc(sizeof(prop_FILE_prop_listadd) + sizeof(prop_FILE_top));
	list_prop_top = (prop_FILE_top*)buff;
	list_prop = (prop_FILE_prop_listadd*)(list_prop_top + 1);

	_wfopen_s(&flist_, SAVE_PROP_FILELIST_, L"r+");

	if (!flist_)
	{
		_wfopen_s(&flist_, SAVE_PROP_FILELIST_, L"w");
		fclose(flist_);
		_wfopen_s(&flist_, SAVE_PROP_FILELIST_, L"r+");
	}

	//memccpy(buff,&prop,)SAVE_PROP_FILENAME
	//fread(buff, sizeof(prop_FILE_top), 1, flist_);
	/*if (one)
	{
		list_prop_top->porp_num = 1;
		one = 0;
	}
	else
	{
		list_prop_top->porp_num += 1;
	}*/
	/*fseek(flist_, 0, SEEK_SET);
	fwrite(&list_prop_top->porp_num, sizeof(prop_FILE_top),1, flist_);
	fclose(flist_);
	_wfopen_s(&flist_, SAVE_PROP_FILELIST_, L"ab+");
	fread(buff, sizeof(prop_FILE_top), 1, flist_);
	fseek(flist_, 0, SEEK_SET);
	list_prop_top->porp_num += 1;
	fwrite(&list_prop_top->porp_num, sizeof(prop_FILE_top), 1, flist_);
	fclose(flist_);
	_wfopen_s(&flist_, SAVE_PROP_FILELIST_, L"ab+");
	fread(buff, sizeof(prop_FILE_top), 1, flist_);*/



	_wfopen_s(&flist, SAVE_PROP_FILELIST, L"rb+");//先找向量表里是否有文件list
	WORD i = GetLastError();
	if (!flist)
	{
		_wfopen_s(&flist, SAVE_PROP_FILELIST, L"wb+");

		fclose(flist);
		//return 0;
		_wfopen_s(&flist, SAVE_PROP_FILELIST, L"rb+");
		if (!flist)
			return 0;
	}

	fread(buff, sizeof(prop_FILE_top) + sizeof(prop_FILE_prop_listadd), 1, flist);
	fseek(flist, 0, SEEK_SET);
	fseek(flist, 0, SEEK_END);
	file_size = _ftelli64(flist);
	_wfopen_s(&f, SAVE_PROP_FILENAME, L"ab+");
	if (!f)
		return 0;
	list_prop->Netlist = sizeof(LONG);
	//_wfopen_s(&flist_, SAVE_PROP_FILELIST_, L"wb+");
	if (((prop_FILE_top*)buff)->porp_num < 1 || ((prop_FILE_top*)buff)->porp_num == NULL)
	{
		((prop_FILE_top*)buff)->porp_num = 0;
		list_prop_top->num_porp_sizebyte = 0;
		list_prop->Offset_Propadd = list_prop_top->num_porp_sizebyte;
		prop.Index = 0;

		fwrite(&prop.Index, sizeof(prop.Index), 1, f);
		fwrite(&prop.sizeImage, sizeof(prop.sizeImage), 1, f);
		size_t size = prop.Name.size();
		fwrite(&size, sizeof(size_t), 1, f);
		fwrite(prop.Name._Unchecked_begin(), prop.Name.size() * 2, 1, f);

		fwrite(prop.pbitmapadr, sizeof(BITMAPFILEHEADER), 1, f);
		fwrite(prop.Picture, sizeof(BITMAPINFO) + prop.pbitmapadr->bfOffBits, 1, f);
		fwrite(prop.pBit, prop.sizeImage, 1, f);

		size = prop.Illustrate.size();
		fwrite(&size, sizeof(size_t), 1, f);
		fwrite(prop.Illustrate._Unchecked_begin(), prop.Illustrate.size() * 2, 1, f);

		//写入向量表

		fseek(flist, 0, SEEK_SET);
		((prop_FILE_top*)buff)->porp_num++;
		fwrite(&(((prop_FILE_top*)buff)->porp_num), sizeof(((prop_FILE_top*)buff)->porp_num), 1, flist);
		fwprintf(flist_, L"%d", list_prop_top->porp_num);
		fwprintf(flist_, L" ");

		//计算下一个偏移量
		list_prop_top->num_porp_sizebyte += sizeof(prop.Index) + sizeof(prop.sizeImage) + sizeof(size_t) + prop.Name.size() * 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + prop.pbitmapadr->bfOffBits + prop.sizeImage + sizeof(size_t) + prop.Illustrate.size() * 2;
		
		
		fwrite(&list_prop_top->num_porp_sizebyte, sizeof(list_prop_top->num_porp_sizebyte), 1, flist);
		fwprintf(flist_, L"%lld", list_prop_top->num_porp_sizebyte);
		fwprintf(flist_, L"\n");

		list_prop->Index = 1;
		fwrite(&(((prop_FILE_prop_listadd*)(((prop_FILE_top*)buff) + 1))->Index), sizeof((((prop_FILE_prop_listadd*)(((prop_FILE_top*)buff) + 1))->Index)), 1, flist);
		fwprintf(flist_, L"%d", ((prop_FILE_prop_listadd*)(((prop_FILE_top*)buff) + 1))->Index);
		fwprintf(flist_, L" ");

		list_prop->Index_Prop = prop.Index;
		fwrite(&list_prop->Index_Prop, sizeof(list_prop->Index_Prop), 1, flist);
		fwprintf(flist_, L"%d", list_prop->Index_Prop);
		fwprintf(flist_, L" ");

		fwrite(&list_prop->Offset_Propadd, sizeof(list_prop->Offset_Propadd), 1, flist);
		fwprintf(flist_, L"%lld", list_prop->Offset_Propadd);
		fwprintf(flist_, L" ");
		fwrite(&list_prop->Netlist, sizeof(list_prop->Netlist), 1, flist);

		fwprintf(flist_, L"%ld", list_prop->Netlist);
		fwprintf(flist_, L"\n");

	}
	else
	{
		LONGLONG Offset_Propadd = list_prop_top->num_porp_sizebyte;//从文件开头到达当前道具的偏移量
		LONGLONG porp_num =	((prop_FILE_top*)buff)->porp_num + 1;//计数当前总道具数
		//计算下一个偏移量
		list_prop_top->num_porp_sizebyte += sizeof(prop.Index) + sizeof(prop.sizeImage) + sizeof(size_t) + prop.Name.size() * 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + prop.pbitmapadr->bfOffBits + prop.sizeImage + sizeof(size_t) + prop.Illustrate.size() * 2;
		
		LONGLONG num_porp_sizebyte = list_prop_top->num_porp_sizebyte;
		//fseek(flist, 0, SEEK_SET);

		int res =	fseek(flist, (sizeof(struct prop_FILE_top) + ((sizeof(struct prop_FILE_prop_listadd)-4) * (list_prop_top->porp_num - 1))), SEEK_SET);
		int i = ftell(flist);
		fread(list_prop, sizeof(struct prop_FILE_prop_listadd), 1, flist);



		prop.Index = list_prop->Index_Prop + 1;// ((prop_FILE_prop_listadd*)buff)->Index_Prop + 1;//写入文件引索

		//写入道具文件
		fwrite(&prop.Index, sizeof(prop.Index), 1, f);
		fwrite(&prop.sizeImage, sizeof(prop.sizeImage), 1, f);

		size_t size = prop.Name.size();
		fwrite(&size, sizeof(size_t), 1, f);
		fwrite(prop.Name._Unchecked_begin(), size * 2, 1, f);

		fwrite(prop.pbitmapadr, sizeof(BITMAPFILEHEADER), 1, f);
		fwrite(prop.Picture, sizeof(BITMAPINFO) + prop.pbitmapadr->bfOffBits, 1, f);
		fwrite(prop.pBit, prop.sizeImage, 1, f);

		size = prop.Illustrate.size();
		fwrite(&size, sizeof(size_t), 1, f);
		fwrite(prop.Illustrate._Unchecked_begin(), size * 2, 1, f);//prop.Illustrate._Unchecked_begin()  因为考虑读写时 Resize() wstring 会重新开辟一个内存空间 存放字符串的位置在这个空间里  所以用这个方法可以直接拿出这个空间的地址

		//写入向量表


		fseek(flist, 0, SEEK_SET);
		//fread(buff, sizeof(prop_FILE_top) + sizeof(prop_FILE_prop_listadd), 1, flist);
		//((prop_FILE_top*)buff)->porp_num++;
		fwrite(&porp_num, sizeof(((prop_FILE_top*)buff)->porp_num), 1, flist);
		fwprintf(flist_, L"%d", porp_num);
		fwprintf(flist_, L" ");

		//计算下一个偏移量
		//list_prop_top->num_porp_sizebyte += sizeof(prop.Index) + sizeof(prop.sizeImage) + sizeof(size_t) + prop.Name.size() * 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + prop.pbitmapadr->bfOffBits + prop.sizeImage + sizeof(size_t) + prop.Illustrate.size() * 2;
		//上面这个很关键
		fwrite(&num_porp_sizebyte, sizeof(list_prop_top->num_porp_sizebyte), 1, flist);

		fwprintf(flist_, L"%lld", num_porp_sizebyte);
		fwprintf(flist_, L"\n");

		fclose(flist_);
		_wfopen_s(&flist_, SAVE_PROP_FILELIST_, L"a");
		//写当前道具的向量引索条目
		//fseek(flist, 0, SEEK_END);
		fseek(flist, 0, SEEK_SET);
		fseek(flist, file_size, SEEK_SET);

		list_prop->Index++;
		fwrite(&(list_prop->Index), sizeof(int), 1, flist);
		fwprintf(flist_, L"%d", list_prop->Index);
		fwprintf(flist_, L" ");
		list_prop->Index_Prop = prop.Index;
		fwrite(&list_prop->Index_Prop, sizeof(list_prop->Index_Prop), 1, flist);
		fwprintf(flist_, L"%d", list_prop->Index_Prop);
		fwprintf(flist_, L" ");
		fwrite(&Offset_Propadd, sizeof(list_prop->Offset_Propadd), 1, flist);
		fwprintf(flist_, L"%lld", Offset_Propadd);
		fwprintf(flist_, L" ");
		fwrite(&list_prop->Netlist, sizeof(list_prop->Netlist), 1, flist);
		fwprintf(flist_, L"%ld", list_prop->Netlist);
		fwprintf(flist_, L"\n");

	}
	free(buff);
	fclose(flist_);
	fclose(flist);
	fclose(f);

	return 1;
}


BOOL	Backpack::Read_Prop(PROP* prop)
{



	FILE* f, * flist, * flist_;
	prop_FILE_prop_listadd* list_prop;
	prop_FILE_top* list_prop_top;
	BYTE* buff,*pBit;
	BITMAPFILEHEADER* pbitmapadr;
	BITMAPINFO* pbitmf;
	
	static BYTE** pz = nullptr;
	static	size_t pzSiez = 0;
	if (pz)
	{
		while (pzSiez != 0)
			{
			std::free(pz[(pzSiez - 1)*3]);
			std::free(pz[(pzSiez - 1)*3 + 1]);
			std::free(pz[(pzSiez - 1) * 3 + 2]);
			pzSiez--;
			}
		std::free(pz);
		pz = nullptr;
	}
	

	buff = (BYTE*)malloc(sizeof(prop_FILE_prop_listadd) + sizeof(prop_FILE_top));
	list_prop_top = (prop_FILE_top*)buff;
	list_prop = (prop_FILE_prop_listadd*)(list_prop_top + 1);

	_wfopen_s(&f, SAVE_PROP_FILENAME, L"rb");
	if (!f)
		return 0;

	_wfopen_s(&flist, SAVE_PROP_FILELIST, L"rb");//先找向量表里是否有文件list
	if (!flist)
		return 0;
	fread(buff, sizeof(prop_FILE_top), 1, flist);
	fseek(flist, 0, SEEK_SET);
	//fread(&(((prop_FILE_top*)buff)->porp_num), sizeof(((prop_FILE_top*)buff)->porp_num), 1, flist);
	//fread(&list_prop_top->num_porp_sizebyte, sizeof(list_prop_top->num_porp_sizebyte), 1, flist);
	pz = (BYTE**)malloc(sizeof(BYTE*)*3 * list_prop_top->porp_num);//分配存放指针地址的空间
	pzSiez = list_prop_top->porp_num;

	for (size_t i = 0; i < list_prop_top->porp_num; i++)
	{



		//fread(&(((prop_FILE_prop_listadd*)(((prop_FILE_top*)buff) + 1))->Index), sizeof(((prop_FILE_top*)buff)->porp_num), 1, flist);

		//fread(&list_prop->Index_Prop, sizeof(list_prop->Index_Prop), 1, flist);
		//fread(&list_prop->Offset_Propadd, sizeof(list_prop->Offset_Propadd), 1, flist);

		//fread(&list_prop->Netlist, sizeof(list_prop->Netlist), 1, flist);



		fread(&prop->Index, sizeof(prop->Index), 1, f);
		fread(&prop->sizeImage, sizeof(prop->sizeImage), 1, f);
		size_t size = 0;
		fread(&size, sizeof(size_t), 1, f);
		prop->Name.resize(size);
		fread(prop->Name._Unchecked_begin(), size * 2, 1, f);
		pz[i*3] = (BYTE*)(pbitmapadr = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER)));
		prop->pbitmapadr = pbitmapadr;
		fread(prop->pbitmapadr, sizeof(BITMAPFILEHEADER), 1, f);
		pz[i*3+1] = (BYTE*)(pbitmf = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + prop->pbitmapadr->bfOffBits));
		prop->Picture = pbitmf;
		fread(prop->Picture, sizeof(BITMAPINFO) + prop->pbitmapadr->bfOffBits, 1, f);
		pz[i*3 + 2] = (BYTE*)(pBit = (BYTE*)malloc(prop->sizeImage));
		prop->pBit = pBit;
		fread(prop->pBit, prop->sizeImage, 1, f);
		size = 0;
		fread(&size, sizeof(size_t), 1, f);
		prop->Illustrate.resize(size);
		fread(prop->Illustrate._Unchecked_begin(), size * 2, 1, f);

		Backpack::Set_hwnd_map_Backpack_prop(prop);

	}















	free(buff);
	fclose(flist);
	fclose(f);

	return 1;
}

BOOL Backpack::Draw_rectangle(HWND hwnd, RECT& xrect,HPEN hPen,HBRUSH hBrush)
{
	HDC xhdc;
	HPEN	hPen_tp;
	HBRUSH hBrush_tp;

	xhdc = GetDC(hwnd);
	
	hPen_tp = (HPEN)SelectObject(xhdc, hPen);
	//DrawRectangle()

	hBrush_tp =(HBRUSH)SelectObject(xhdc, hBrush);
	Rectangle(xhdc, xrect.left, xrect.top, xrect.right, xrect.bottom);
	SelectObject(xhdc, hPen_tp);
	SelectObject(xhdc, hBrush_tp);
	ReleaseDC(hwnd,xhdc);

	return 1;
}

BOOL Backpack::Draw_Prop_BMP(HWND hwnd, PROP* lpprop)//将BMP图片画出
{
	HDC hdc_tp;
	RECT rt;

	hdc_tp = GetDC(hwnd);

	GetClientRect(hwnd, &rt);
	SetStretchBltMode(hdc_tp, HALFTONE);
	/*SetDIBitsToDevice(hdc_tp, 0, 0, 50, 50, 0, 0, 0, lpprop->Picture->bmiHeader.biHeight, lpprop->pBit,
		lpprop->Picture, DIB_RGB_COLORS);*/
	StretchDIBits(hdc_tp, 0, 0, rt.right, rt.bottom, 0, 0,
		lpprop->Picture->bmiHeader.biWidth, lpprop->Picture->bmiHeader.biHeight,
		lpprop->pBit, lpprop->Picture, DIB_RGB_COLORS, SRCCOPY);


	ReleaseDC(hwnd, hdc_tp);


	return 1;
}
