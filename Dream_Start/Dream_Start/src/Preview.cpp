#include"../head/Preview.h"




Preview* Preview::lPpreview = nullptr;
HINSTANCE	 Preview::hInstance = NULL;

LRESULT	CALLBACK Preview::WNDProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return	lPpreview->WNDProc_(hwnd, msg, wParam, lParam);
}

LRESULT Preview::CLDProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return	lPpreview->CLDProc_(hwnd, msg, wParam, lParam);
}

bool Preview::Init_view()
{
	Init_WNDClASS();

	g_hwnd =	Cwindow();

	if (!g_hwnd)
		return 0;

	Init_control();
	ShowWindow(g_hwnd, SW_SHOW);

	return 1;
}



TCHAR* Preview::Get_ClassName()
{
	return (TCHAR*)className;
}

TCHAR* Preview::Get_ClassName_CLD()
{
	return (TCHAR*)szclassName_CLD;
}

Preview::Preview(HINSTANCE his)
{
	hInstance = his;
	lPpreview = this;
}

Preview::~Preview()
{
}

LRESULT Preview::WNDProc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{



	default:
		break;
	}

	
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

LRESULT Preview::CLDProc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HMENU menu;

	switch (msg)
	{


	case WM_APP+10:
		if(hwnd_prop.count(hwnd))
		Draw_Prop_BMP(hwnd, &hwnd_prop.at(hwnd));
		return 1;

	case WM_ERASEBKGND:

		PostMessage(hwnd, WM_APP + 10, 0, 0);

		return 1;

	case WM_COMMAND:
		//menu = GetMenu(hwnd);


		break;


	default:
		break;
	}



	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Preview::Init_WNDClASS()
{
	WNDCLASS wcs = {0};

	wcs.lpfnWndProc = WNDProc;
	wcs.style = CS_VREDRAW | CS_HREDRAW;
	wcs.hInstance = hInstance;
	wcs.cbClsExtra = 0;
	wcs.cbWndExtra = 0;
	wcs.hIcon = NULL;
	wcs.hCursor = NULL;
	wcs.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcs.lpszMenuName = NULL;
	wcs.lpszClassName = className;

	if (!RegisterClass(&wcs))
	{
		MessageBox(NULL, L"´íÎó  Preview .cpp 51", L"Àà×¢²á´íÎó", MB_OK);
		return 0;
	}

	wcs.lpfnWndProc = CLDProc;
	
	wcs.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcs.lpszMenuName = NULL;
	wcs.lpszClassName = szclassName_CLD;

	if (!RegisterClass(&wcs))
	{
		MessageBox(NULL, L"´íÎó  Preview .cpp 100", L"Àà×¢²á´íÎó", MB_OK);
		return 0;
	}

	return 1;
}

HWND Preview::Cwindow()
{
	return	CreateWindow(className, L"Ô¤ÀÀ", WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, 0, 0, hInstance, 0);
}

void Preview::Init_control()
{
	g_chwnd[0] = CreateWindow(STATIC_, L"Ãû×Ö", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY,
		60, 0, 50, 20, g_hwnd,NULL , hInstance, NULL
	);
	g_chwnd[1] = CreateWindow(szclassName_CLD, L"Í¼Ïñ", WS_CHILD | WS_VISIBLE,
		0, 0, 50, 50, g_hwnd, NULL, hInstance, NULL
	);
	

	g_chwnd[2] = CreateWindow(STATIC_, L"ÃèÊö", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY,
		60, 30, 100, 30, g_hwnd, NULL, hInstance, NULL
	);

}


bool Preview::Draw_Prop_BMP(HWND hwnd, PROP* lpprop)//½«BMPÍ¼Æ¬»­³ö
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

void Preview::set_prop(PROP& p)
{
	propShow = p;
}

void Preview::show_prop()
{

	SendMessage(g_chwnd[0], WM_SETTEXT, 0, (LPARAM)propShow.Name._Unchecked_begin());
	//InvalidateRect(g_chwnd[1], NULL, TRUE);
	PostMessage(g_chwnd[1], WM_APP + 10, 0, 0);
	PostMessage(g_chwnd[2], WM_SETTEXT, 0, (LPARAM)propShow.Illustrate._Unchecked_begin());

	SetWindowText(g_chwnd[0], propShow.Name._Unchecked_begin());
	SetWindowText(g_chwnd[2], propShow.Illustrate._Unchecked_begin());
	//UpdateWindow(g_chwnd[1]);
	UpdateWindow(g_hwnd);
}

void Preview::Read_Prop(vector<PROP> &items_prop,map<int,PROP> &index_list)
{
	PROP* prop,p;
	prop_FILE_prop_listadd* plist_add;
	prop_FILE_top* plist_top;
	FILE* flist,*flist_,*f;
	BYTE* buff,*buff_prop;

	BYTE * pBit;
	BITMAPFILEHEADER* pbitmapadr;
	BITMAPINFO* pbitmf;

	static BYTE** pz = nullptr;
	static	size_t pzSiez = 0;
	if (pz)
	{
		while (pzSiez != 0)
		{
			std::free(pz[(pzSiez - 1) * 3]);
			std::free(pz[(pzSiez - 1) * 3 + 1]);
			std::free(pz[(pzSiez - 1) * 3 + 2]);
			pzSiez--;
		}
		std::free(pz);
		pz = nullptr;
	}

	_wfopen_s(&flist_, SAVE_PROP_FILELIST_, L"rb");
	_wfopen_s(&flist, SAVE_PROP_FILELIST, L"rb");
	_wfopen_s(&f, SAVE_PROP_FILENAME, L"rb");
	if (!(f&&flist&&flist_))
		return;
	buff = (BYTE*)malloc(sizeof(prop_FILE_prop_listadd) + sizeof(prop_FILE_top));
	//prop = (PROP*)malloc(sizeof(PROP)*4 );
	prop = &p;
	if (!buff)
		return;
	plist_top = (prop_FILE_top*)buff;
	plist_add = (prop_FILE_prop_listadd*)(plist_top + 1);
	
	fread(buff, sizeof(prop_FILE_prop_listadd) + sizeof(prop_FILE_top), 1, flist);
	fseek(flist, sizeof(prop_FILE_top), SEEK_SET);
	pz = (BYTE**)malloc(sizeof(BYTE*) * 3 * plist_top->porp_num);//·ÖÅä´æ·ÅÖ¸ÕëµØÖ·µÄ¿Õ¼ä
	pzSiez = plist_top->porp_num;
	for (size_t i = 0; i < plist_top->porp_num ; i++)
	{	
		
		Read_list(plist_add, flist);


		fread(&prop->Index, sizeof(prop->Index), 1, f);
		fread(&prop->sizeImage, sizeof(prop->sizeImage), 1, f);
		size_t size = 0;
		fread(&size, sizeof(size_t), 1, f);
		prop->Name.resize(size);
		fread(prop->Name._Unchecked_begin(), size * 2, 1, f);
		pz[i * 3] = (BYTE*)(pbitmapadr = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER)));
		prop->pbitmapadr = pbitmapadr;
		fread(prop->pbitmapadr, sizeof(BITMAPFILEHEADER), 1, f);
		pz[i * 3 + 1] = (BYTE*)(pbitmf = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + prop->pbitmapadr->bfOffBits));
		prop->Picture = pbitmf;
		fread(prop->Picture, sizeof(BITMAPINFO) + prop->pbitmapadr->bfOffBits, 1, f);
		pz[i * 3 + 2] = (BYTE*)(pBit = (BYTE*)malloc(prop->sizeImage));
		prop->pBit = pBit;
		fread(prop->pBit, prop->sizeImage, 1, f);
		size = 0;
		fread(&size, sizeof(size_t), 1, f);
		prop->Illustrate.resize(size);
		fread(prop->Illustrate._Unchecked_begin(), size * 2, 1, f);

		items_prop.push_back(*prop);
		index_list.insert(make_pair(plist_add->Index, *prop));

	}
	free(buff);
	fclose(flist);
	fclose(f);
	fclose(flist_);


}

HWND	Preview::Get_g_hwnd()
{
	return g_hwnd;

}

void	Preview::Read_list(prop_FILE_prop_listadd *plist_add ,FILE *flist)
{
	/*fread(plist_add, sizeof(prop_FILE_prop_listadd), 1, flist);
	fread(plist_add, sizeof(prop_FILE_prop_listadd), 1, flist);*/
	fread(&(plist_add->Index), sizeof(int), 1, flist);

	fread(&plist_add->Index_Prop, sizeof(plist_add->Index_Prop), 1, flist);

	fread(&plist_add->Offset_Propadd, sizeof(plist_add->Offset_Propadd), 1, flist);

	fread(&plist_add->Netlist, sizeof(plist_add->Netlist), 1, flist);
}

void	Preview::Write_list_add(prop_FILE_prop_listadd* plist_add, FILE* flist,FILE* flist_)
{
	
	

	
	fwrite(&plist_add->Index, sizeof(plist_add->Index), 1, flist);
	
	fwprintf(flist_, L"%d", plist_add->Index);
	fwprintf(flist_, L" ");

	
	fwrite(&plist_add->Index_Prop, sizeof(plist_add->Index_Prop), 1, flist);
	fwprintf(flist_, L"%d", plist_add->Index_Prop);
	fwprintf(flist_, L" ");

	fwrite(&plist_add->Offset_Propadd, sizeof(plist_add->Offset_Propadd), 1, flist);
	fwprintf(flist_, L"%lld", plist_add->Offset_Propadd);
	fwprintf(flist_, L" ");
	fwrite(&plist_add->Netlist, sizeof(plist_add->Netlist), 1, flist);

	fwprintf(flist_, L"%ld", plist_add->Netlist);
	fwprintf(flist_, L"\n");

}

void	Preview::Write_list_SHONW_Top(prop_FILE_top* buff_list_top, FILE* flist_)
{
	fwprintf(flist_, L"%lld", buff_list_top->porp_num);
	fwprintf(flist_, L" ");
	fwprintf(flist_, L"%lld", buff_list_top->num_porp_sizebyte);
	fwprintf(flist_, L"\n");
}

void Preview::Sethwnd_prop(PROP* prop)
{
	hwnd_prop.insert(make_pair(g_chwnd[1], *prop));
}