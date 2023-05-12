#include"../head/Preview_Prop.h"

void Preview_Prop::Setg_hwndPar(HWND hwndP)
{
	g_hwndPar = hwndP;

}

HWND Preview_Prop::Cwindow()
{
	return	CreateWindow(Get_ClassName(), NULL,WS_CHILD	|WS_BORDER, 0, 0, 100, 500,
		g_hwndPar,(HMENU) ID_SHOW_PROP, hInstance, (LPVOID)L"Èö´ó´ó"
	);
}

LRESULT Preview_Prop::WNDProc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{



	default:
		break;
	}

	LRESULT result = DefWindowProc(hwnd,msg,wParam,lParam);
	return result;
}

bool Preview_Prop::Init_view()
{
	

	return Preview::Init_view();
}

void Preview_Prop::show_prop()
{
	Preview::show_prop();
}

void Preview_Prop::set_prop(PROP& p)
{
	Preview::set_prop(p);
}
void Preview_Prop::Sethwnd_prop( PROP* prop)
{
	Preview::Sethwnd_prop( prop);
}