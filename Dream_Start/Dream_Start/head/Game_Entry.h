#pragma once

#include"Game_Init.h"
#include"erro.h"
#include"Game_Backpack.h"
#include"Struct_Game.h"
#include"delete_.h"

class Game_Enty:public Init
{
private:
	RECT window_Cli;
	delete_* de;
	
	static BYTE** g_pBit,* g_pBit_bitmap;
	static	BITMAPFILEHEADER** g_pbitmapadr;
	static	BITMAPINFO** g_pbitmf;
	static Game_Enty* game_Enty;


protected:
	
	static std::map<int, HWND> hwnd_map;



public:
	Game_Enty(HINSTANCE hInstance);
	
	~Game_Enty() {};
	virtual bool InitMainWindow()override;
	virtual LRESULT msg_Proc(HWND, UINT, WPARAM, LPARAM) override;
	virtual LRESULT Cid_Proc_init(HWND, UINT, WPARAM, LPARAM) override;
	virtual	void KeyDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, HWND& hwndBtn, std::map<int, HWND>& hm) override;
	virtual	LRESULT	Cid_System_Proc_init(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
	bool	openFile_read(FILE* fe, BYTE** pbuff,const wchar_t * mode);


	static	LRESULT CALLBACK Proc_Text(HWND, UINT, WPARAM, LPARAM);
	static	LRESULT CALLBACK Proc_Text_ADD_SHOW_STATIC(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Save_Prop_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


	static	VOID	thread(PVOID p);

	 bool Run()override;


	LRESULT Edit_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT Proc_Text_ADD_SHOW(HWND, UINT, WPARAM, LPARAM);

	LRESULT  Proc_Text_ADD_SHOW_STATIC_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void delete_prop();


	//BOOL Save_Prop(PROP prop);
	//BOOL	Read_Prop(OUT	PROP* prop);
};
