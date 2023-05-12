#pragma once
#include"Import.h"
#include"Preview.h"
class delete_:	public	 Preview
{

private:
	RECT g_rt;
	HWND g_hwnd, g_hwnd_part, g_button, g_chwnd[10];
	
	static	LRESULT CALLBACK WNDProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	static	delete_* g_delete_;
	vector<PROP> items_prop;
	vector<map<int, HWND>> items;
	map<int, PROP> index_list;
	WNDPROC proc;

public:
	delete_(HINSTANCE hin) :Preview(hin) { g_delete_ = this; };

	
	void	Init_control()override;

	void window_size(HWND hwnd, RECT rt);
	
	void Read_Prop(vector<PROP>& items_prop, map<int, PROP>& index_list);//读取文件中的道具

	HWND	CreatrBUTTON();
	void	Set_g_hwnd_part(HWND part);

	 LRESULT WNDProc_delete(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	 LRESULT CLDProc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
	 
	 virtual bool delete_prop(int list_index);
	 bool Read_prop(prop * prop,FILE *f);
	 bool Write_prop(prop* prop, FILE* f);


};

