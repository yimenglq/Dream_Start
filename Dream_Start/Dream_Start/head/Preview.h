#pragma once
#include"Import.h"


//预览类
class Preview
{

private:
	constexpr static	TCHAR className[] = L"Preview";
	constexpr static	TCHAR szclassName_CLD[] = L"BMP";
	
	PROP propShow;
	static	Preview* lPpreview;

	HWND g_hwnd,g_chwnd[3];

	static	LRESULT CALLBACK WNDProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	static	LRESULT CALLBACK CLDProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	




protected:
	TEXTMETRIC textmc;
	static	HINSTANCE	hInstance;
	map<HWND, PROP> hwnd_prop;
	HWND	Get_g_hwnd();
	TCHAR* Get_ClassName();
	TCHAR* Get_ClassName_CLD();

public:


	Preview(HINSTANCE);
	~Preview();
	
	bool Init_view();
	virtual LRESULT WNDProc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual	LRESULT CLDProc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


	virtual	bool	Init_WNDClASS();

	virtual	HWND Cwindow();
	virtual void Init_control();

	virtual	bool Draw_Prop_BMP(HWND hwnd, PROP* lpprop);//贴图


	void	set_prop(PROP &p);
	virtual	void	show_prop();

	virtual void Read_Prop(vector<PROP> &items_prop, map<int, PROP>& index_list);//读取文件中的道具
	void	Read_list(prop_FILE_prop_listadd* plist_add, FILE* flist);
	void	Write_list_add(prop_FILE_prop_listadd* plist_add, FILE* flist, FILE* flist_);
	void	Write_list_SHONW_Top(prop_FILE_top* buff_list_top, FILE* flist_);//字符串显示的向量表
	void Sethwnd_prop(PROP * prop);

};


