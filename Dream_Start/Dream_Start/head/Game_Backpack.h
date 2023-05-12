#pragma once
#include"Import.h"
#include"Mouse_Events.h"
#include"Preview_Prop.h"





class Backpack
{
private:
		
		
		
		TCHAR	*	szClassName = (TCHAR*)TEXT("Backpack");
		TCHAR* szClassNaMe_Cid = (TCHAR*)L"CID";
		HWND hwnd,hwndParent;
		WNDCLASS wndclass;
		HMENU hmenu;
		RECT hwnd_rect = { 0,0,300,200 };
		PROP prop;

		static RECT rect_window_main;
		static	Backpack * backpack;

		static	HINSTANCE hInstance;

		static std::map<int, HWND> hwnd_map_Backpack;//背包格子ID与句柄
		static std::map<int, PROP> hwnd_map_Backpack_prop;//游戏存有的游戏道具
		//static std::map<int, WNDPROC> hwnd_map_Backpack_prop;


		bool registerClass();
		bool Prop_window_init(std::map<int, PROP>& map_prop, std::map<int, HWND>& map_Id);

	static	LRESULT CALLBACK Prop_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
	
		

		

protected:
	Preview_Prop* preview_prop;

	virtual	bool	movewindow_B(POINT &pt);


public:
	Backpack() {
	
		if (backpack == nullptr)
			backpack = this;
		

	};
	Backpack(wchar_t str[],HINSTANCE hIns):szClassName(str){
	
		if (backpack == nullptr)
			backpack = this;
		if(hInstance == nullptr)
			hInstance = hIns;

	};
	~Backpack() {};
			
	
	bool init();
	TCHAR*	Get_szClassName();
	HWND Gethwnd();


	void SetHinstance( HINSTANCE hIns);


	
	virtual	LRESULT backpack_Proc(HWND, UINT, WPARAM, LPARAM);//游戏背包的窗口消息过程
	//virtual	LRESULT backpack_Proc_(HWND, UINT, WPARAM, LPARAM);
	
	virtual	LRESULT Prop_Proc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//virtual	void KeyDown(HWND,WPARAM,LPARAM);
	
	//virtual	LPVOID open_prop_file(FILE* f, PROP * prop);//
	//virtual	LRESULT Save_Prop_Proc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	

	void Sethmenu(HMENU hmenu_);
	HMENU Gethmenu();
	void	SethwndParent(HWND hwnd);
	static Backpack* GetBackpack();

	
	static int Set_hwnd_map_Backpack_prop(PROP	*p);

	static BOOL	Read_Prop(OUT	PROP* prop);
	static BOOL Save_Prop(PROP prop);

	BOOL	Draw_rectangle(HWND hwnd, RECT& rect, HPEN hPen, HBRUSH hBrush);

	BOOL Draw_Prop_BMP(HWND hwnd, PROP* lpprop);
};


