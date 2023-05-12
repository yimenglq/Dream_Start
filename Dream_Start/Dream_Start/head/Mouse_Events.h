#pragma once
#include"Import.h"

class MouseEvents
{
private:
	static	bool	MouseTracking;//= false;
protected:

public:
	MouseEvents();
	~MouseEvents();

	static	bool	MouseEvents_Track(HWND hwnd, DWORD TME_ = TME_HOVER | TME_LEAVE, DWORD dwHoverTime = 2000);
	static	void Reset(HWND hwnd);
};


