#include"../head/Game_Entry.h"

#include<Windows.h>



int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	try
	{
		Game_Enty game_enty(hInstance);
		
		if (!game_enty.InitMainWindow())
			return 0;
	
		return game_enty.Run();
	}
	catch (MyClaMyExceptionss &e)
	{
		cout<< e.toSing() << endl;
	}
	
}


Game_Enty::Game_Enty(HINSTANCE hInstance) :Init::Init(hInstance) {};


bool Game_Enty::InitMainWindow()
	{

	if (!Init::InitMainWindow())
		return 0;
	return 1;
	}


