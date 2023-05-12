#include"Import.h"
#include"Game_Init_cpp_macro.h"

#include<map>
#include<vector>
#include<Uxtheme.h>
#include<dwmapi.h>
#pragma comment(lib,"Dwmapi.lib")




#ifndef Game_Init
#define Game_Init 

class Init
{
private: //����
	HINSTANCE hInstance;

	constexpr static TCHAR szClassName[] = L"Init" ;
	constexpr static TCHAR * szClassName_Cid = (TCHAR*)L"InitCid";

	static Init *init;

	


protected://����  ����

	static	std::map<std::wstring, WNDPROC> Proc_map;//�����Ӵ��ڿؼ�  �Ļص�����

	WNDCLASS Init_wndclass();//LRESULT ( Init::*w_Proc)(HWND,UINT,WPARAM,LPARAM) = wndProc);

	virtual bool InitMainWindow();
	virtual LRESULT HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual void KeyDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void KeyDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, HWND &hwndBth,std::map<int, HWND> &hm);
	virtual HRESULT	EnableBlurBehind(HWND);
	

	HRESULT Thumbnail(HWND hwnd);
	

	//LRESULT wndProc(HWND, UINT, WPARAM, LPARAM);


	public:	//����  ����  ������ 
		Init(HINSTANCE h) :hInstance(h) 
		{
			if (init == nullptr)
				init = this;
		};
		
		
		~Init() {};

		virtual	bool Run();
		virtual	LRESULT	msg_Proc(HWND, UINT, WPARAM, LPARAM)=0;
		virtual LRESULT Cid_Proc_init(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)=0;//�Ӵ���
		

		virtual	LRESULT	Cid_System_Proc_init(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;//�Ӵ��ڿؼ�
		
		HINSTANCE GethInstance();
		static Init* GetInit();
		
		WNDPROC GetWndProc();
		TCHAR* GetszClassName_Cid();


		WNDPROC GetwndProc_System_Cid();


};









#endif // !Game_Init


