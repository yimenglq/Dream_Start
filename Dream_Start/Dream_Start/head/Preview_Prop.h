#pragma once
#include"Preview.h"

class Preview_Prop : protected Preview 
{
private:
	HWND g_hwndPar;

protected:


public:
	Preview_Prop(HINSTANCE hin) :Preview(hin) {};
	~Preview_Prop() {};
	void	Setg_hwndPar(HWND hwndP);


	virtual	HWND Cwindow()override;

	virtual LRESULT WNDProc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
	bool Init_view();
	void	show_prop();
	void	set_prop(PROP& p);
	void Sethwnd_prop( PROP* prop);
};



