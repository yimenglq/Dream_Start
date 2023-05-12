#include"../head/Mouse_Events.h"

bool	MouseEvents::MouseTracking = false;

MouseEvents::MouseEvents()
{

}

MouseEvents::~MouseEvents()
{


}

 bool MouseEvents::MouseEvents_Track(HWND hwnd, DWORD TME_ , DWORD dwHoverTime)
{
	TRACKMOUSEEVENT Tevent = { 0 };
	Tevent.cbSize = sizeof(TRACKMOUSEEVENT);
	Tevent.hwndTrack = hwnd;
	Tevent.dwFlags = TME_;
	Tevent.dwHoverTime = dwHoverTime;
	TrackMouseEvent(&Tevent);
	MouseTracking = true;

	return 1;
}

 void MouseEvents::Reset(HWND hwnd)
{
	MouseTracking = false;
}