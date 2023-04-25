#pragma once

#include"Game_Init.h"
#include"erro.h"

class Game_Enty:public Init
{
private:


protected:
	



public:
	Game_Enty(HINSTANCE hInstance);
	
	~Game_Enty() {};
	virtual bool InitMainWindow()override;
	

};
