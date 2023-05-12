#include"../head/delete_.h"

delete_* delete_::g_delete_ = nullptr;


LRESULT	CALLBACK delete_::WNDProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result= g_delete_->WNDProc_delete(hwnd, msg, wParam, lParam);
	return	result;
}

LRESULT delete_::WNDProc_delete(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT rt;
	HWND hwnd_desk;

	switch (msg)
	{
	case WM_LBUTTONUP:
	{
		hwnd_desk = GetDesktopWindow();
		GetClientRect(hwnd_desk, &rt);
		rt.left = 25 * rt.right / 100;
		rt.top = 10 * rt.bottom / 100;
		rt.right = 50 * rt.right / 100;
		rt.bottom = 80 * rt.bottom / 100;
		Init_view();
		window_size(g_hwnd, rt);
		//显示道具总条目数  贴图
		auto it = items_prop.begin();
		for (int i = 0; it != items_prop.end(); it++, i++)
		{
			set_prop(*it);
			SendMessage(items.at(i).at(2), WM_APP + 10, 0, 0);
		}
	}
		break;




	default:
		break;
	}


	LRESULT result = CallWindowProc(proc,hwnd,msg,wParam,lParam);
	return result;
}


LRESULT delete_::CLDProc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HMENU menu;

	switch (msg)
	{


	case WM_APP + 10:
		if (hwnd_prop.count(hwnd))
			Draw_Prop_BMP(hwnd, &hwnd_prop.at(hwnd));
		return 1;

	case WM_ERASEBKGND:

		PostMessage(hwnd, WM_APP + 10, 0, 0);

		return 1;

	case WM_COMMAND:
		menu = GetMenu(hwnd);
		delete_prop((int)menu);

		break;


	default:
		break;
	}



	LRESULT result = DefWindowProc(hwnd, msg, wParam, lParam);
	return result;
}
		


void delete_::Init_control()
{
	//GetClientRect(g_hwnd, &g_rt);
	if (!items_prop.empty())
		items_prop.clear();
	if (!items.empty())
		items.clear();
	hwnd_prop.clear();
	if (!index_list.empty())
		index_list.clear();
	
	Read_Prop(items_prop, index_list);
	g_hwnd = Get_g_hwnd(); 
	auto it = index_list.begin();
	
	GetTextMetrics(GetDC(NULL), &textmc);
	for (int i = 0;it != index_list.end();it++,i++ )
	{
			map<int, HWND> id_hwnd_map;
			size_t item_h = textmc.tmHeight * 1.5 + it->second.Illustrate.size() / 10 * textmc.tmHeight * 1.5 + 50;
			size_t item_w = textmc.tmMaxCharWidth * 1.2 * 10 + item_h + textmc.tmMaxCharWidth * 1.2 * 2;

			g_chwnd[0] = CreateWindow(Get_ClassName_CLD(), L"条目窗口", WS_CHILD | WS_VISIBLE,
				0 , i*80, item_w, item_h, Get_g_hwnd(), (HMENU)it->first, hInstance, NULL
			);
			g_chwnd[1] = CreateWindow(STATIC_, it->second.Name._Unchecked_begin(), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY,
				item_h, 0, textmc.tmMaxCharWidth * 1.2 * 10, textmc.tmHeight * 1.5, g_chwnd[0], NULL, hInstance, NULL
			);
			g_chwnd[2] = CreateWindow(Get_ClassName_CLD(), L"图像", WS_CHILD | WS_VISIBLE,
				0, 0, item_h, item_h, g_chwnd[0], NULL, hInstance, NULL
			);
			

			g_chwnd[3] = CreateWindow(STATIC_, it->second.Illustrate._Unchecked_begin(), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY,
				item_h, textmc.tmHeight * 1.5 * 2, textmc.tmMaxCharWidth * 1.2 * 10, (it->second.Illustrate.size() / 10 > 1 ? it->second.Illustrate.size() / 10 * textmc.tmHeight * 1.5 : textmc.tmHeight * 1.5), g_chwnd[0], NULL, hInstance, NULL
			);
			g_chwnd[4] = CreateWindow(BUTTON_,L"删除", WS_CHILD | WS_VISIBLE |BS_PUSHBUTTON,
				item_h + textmc.tmMaxCharWidth * 1.2 * 10, 30, textmc.tmMaxCharWidth * 1.2 * 2, textmc.tmHeight * 1.5, g_chwnd[0], NULL, hInstance, NULL
			);

			id_hwnd_map.insert(make_pair(1, g_chwnd[1]));
			id_hwnd_map.insert(make_pair(2, g_chwnd[2]));
			id_hwnd_map.insert(make_pair(3, g_chwnd[3]));
			id_hwnd_map.insert(make_pair(4, g_chwnd[4]));
			items.push_back(id_hwnd_map);
			hwnd_prop.insert(make_pair(g_chwnd[2], it->second));
	}

	
}

void delete_::window_size(HWND hwnd,RECT rt)
{
	MoveWindow(hwnd, rt.left, rt.top, rt.right, rt.bottom, TRUE);

}

void delete_::Read_Prop(vector<PROP>& items_prop, map<int, PROP>& index_list)//读取文件中的道具
{
	Preview::Read_Prop(items_prop,index_list);


}

HWND	delete_::CreatrBUTTON()
{
	g_button = CreateWindow(BUTTON_, L"删除道具", WS_CHILD | WS_VISIBLE, 100, 0, 100, 20, g_hwnd_part, NULL, hInstance, NULL);
	proc =(WNDPROC)	SetWindowLongPtr(g_button, GWL_WNDPROC,(LONG)WNDProc);

	return	g_button;
}

void	delete_::Set_g_hwnd_part(HWND part)
{
	g_hwnd_part = part;
}
bool delete_::delete_prop(int list_index)
{
	FILE* flist, *flist_,*f,* fnew,* flistnew;
	BYTE* buff;
	PROP prop, propNew,prop_tp;
	prop_FILE_prop_listadd* buff_list_add;
	prop_FILE_top* buff_list_top;
	_wfopen_s(&flist, SAVE_PROP_FILELIST, L"rb+");
	WORD i = GetLastError();
	if (!flist)
		return 0;
	buff = (BYTE*)malloc(sizeof(prop_FILE_top) +sizeof(prop_FILE_prop_listadd));
	buff_list_top = (prop_FILE_top*)buff;
	buff_list_add = (prop_FILE_prop_listadd*)(buff_list_top + 1);
	fread(buff_list_top, sizeof(prop_FILE_top), 1, flist);
	if ((buff_list_top->porp_num-1) == 0)
	{
		fclose(flist);
		MessageBox(NULL, L"最后一个元素不可删除", L"错误", MB_OK);
		MessageBeep(MB_OK);
		return 0;
	}

	do
	{
		Read_list(buff_list_add, flist);
	} while (buff_list_add->Index != list_index && buff_list_add->Index < list_index);
	
	if (buff_list_add->Index == list_index)
	{
		_wfopen_s(&f, SAVE_PROP_FILENAME, L"rb+");
		_wfopen_s(&fnew, SAVE_PROP_FILENAME_NEW, L"wb+");
		_wfopen_s(&flistnew, SAVE_PROP_FILELIST_NEW, L"wb+");
		_wfopen_s(&flist_, SAVE_PROP_FILELIST_NEW_, L"w+");
		fseek(f, buff_list_add->Offset_Propadd, SEEK_SET);
		Read_prop(&prop, f);
		fseek(f, 0, SEEK_SET);
		size_t i_size = --buff_list_top->porp_num;
		size_t size_prop = 0;
		

		do
		{

			Read_prop(&propNew, f);
			
			if (prop.Index != propNew.Index)
			{
				Write_prop(&propNew, fnew);
				i_size--;
			}
			else
			{
				prop_tp = propNew;
				//list_prop_top->num_porp_sizebyte += sizeof(prop.Index) + sizeof(prop.sizeImage) + sizeof(size_t) + prop.Name.size() * 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + prop.pbitmapadr->bfOffBits + prop.sizeImage + sizeof(size_t) + prop.Illustrate.size() * 2;


				size_prop =	sizeof(prop_tp.Index) + sizeof(prop_tp.sizeImage) + sizeof(size_t) + prop_tp.Name.size() * 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + prop_tp.pbitmapadr->bfOffBits + prop_tp.sizeImage + sizeof(size_t) + prop_tp.Illustrate.size() * 2;
			}
					
		} while (i_size);
		fseek(fnew, 0, SEEK_SET);
		//Read_prop(&propNew, fnew);
		
		fclose(f);
		fclose(fnew);
		//更新向量表
		i_size = buff_list_top->porp_num;
		buff_list_top->num_porp_sizebyte -= size_prop;
		fseek(flistnew, 0, SEEK_SET);
		fwrite(buff_list_top, sizeof(prop_FILE_top), 1, flistnew);
		
		Write_list_SHONW_Top(buff_list_top, flist_);
		fclose(flist_);
		_wfopen_s(&flist_, SAVE_PROP_FILELIST_NEW_, L"a+");

		fseek(flistnew, sizeof(prop_FILE_top), SEEK_SET);
		fseek(flist, sizeof(prop_FILE_top), SEEK_SET);

		do
		{
			Read_list(buff_list_add, flist);
			if (buff_list_add->Index < list_index)
			{
				Write_list_add(buff_list_add, flistnew,flist_);
				i_size--;
			}
			else if (buff_list_add->Index != list_index)
			{
				buff_list_add->Offset_Propadd -= size_prop;
				Write_list_add(buff_list_add, flistnew, flist_);
				i_size--;
			}
			
			
		} while (i_size);
		fclose(flist_);
		fclose(flistnew);
	}
	
	fclose(flist);
	
	int err = _wremove(SAVE_PROP_FILENAME);//删除文件
	err = _wrename(SAVE_PROP_FILENAME_NEW, SAVE_PROP_FILENAME);//修改文件名
	_wremove(SAVE_PROP_FILELIST);
	err = _wrename(SAVE_PROP_FILELIST_NEW, SAVE_PROP_FILELIST);
	err = _wremove(SAVE_PROP_FILELIST_);
	err = _wrename(SAVE_PROP_FILELIST_NEW_, SAVE_PROP_FILELIST_);


	return 1;
}

//读取单个道具
bool delete_::Read_prop(prop* prop, FILE* f)
{
	static	BYTE* pBit;
	static BITMAPFILEHEADER* pbitmapadr;
	static BITMAPINFO* pbitmf;

	if (pBit)
		free(pBit);
	if (pbitmapadr)
		free(pbitmapadr);
	if (pbitmf)
		free(pbitmf);

	fread(&prop->Index, sizeof(prop->Index), 1, f);
	fread(&prop->sizeImage, sizeof(prop->sizeImage), 1, f);
	size_t size = 0;
	fread(&size, sizeof(size_t), 1, f);
	prop->Name.resize(size);
	fread(prop->Name._Unchecked_begin(), size * 2, 1, f);
	pbitmapadr = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
	prop->pbitmapadr = pbitmapadr;
	fread(prop->pbitmapadr, sizeof(BITMAPFILEHEADER), 1, f);
	pbitmf = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + prop->pbitmapadr->bfOffBits);
	prop->Picture = pbitmf;
	fread(prop->Picture, sizeof(BITMAPINFO) + prop->pbitmapadr->bfOffBits, 1, f);
	pBit = (BYTE*)malloc(prop->sizeImage);
	prop->pBit = pBit;
	fread(prop->pBit, prop->sizeImage, 1, f);
	size = 0;
	fread(&size, sizeof(size_t), 1, f);
	prop->Illustrate.resize(size);
	fread(prop->Illustrate._Unchecked_begin(), size * 2, 1, f);


	return 1;
}
bool delete_::Write_prop(prop* prop, FILE* f)
{
	fwrite(&prop->Index, sizeof(prop->Index), 1, f);
	fwrite(&prop->sizeImage, sizeof(prop->sizeImage), 1, f);
	size_t size = prop->Name.size();
	fwrite(&size, sizeof(size_t), 1, f);
	fwrite(prop->Name._Unchecked_begin(), prop->Name.size() * 2, 1, f);

	fwrite(prop->pbitmapadr, sizeof(BITMAPFILEHEADER), 1, f);
	fwrite(prop->Picture, sizeof(BITMAPINFO) + prop->pbitmapadr->bfOffBits, 1, f);
	fwrite(prop->pBit, prop->sizeImage, 1, f);

	size = prop->Illustrate.size();
	fwrite(&size, sizeof(size_t), 1, f);
	fwrite(prop->Illustrate._Unchecked_begin(), prop->Illustrate.size() * 2, 1, f);

	return 1;
}