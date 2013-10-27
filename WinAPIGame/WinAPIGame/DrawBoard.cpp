#include "GameHead.h"
#ifndef DRAWBOARD
#define DRAWBOARD
class Board {
private:
	int xl,yt,xr,yb;
public :
	Board(int xl,int yt,int xr,int yb) : xl(xl),yt(yt),xr(xr),yb(yb){};
	int getXl(){
		return xl;
	}
	int getYt() {
		return yt;
	}
	int getXr(){
		return xr;
	}
	int getYb() {
		return yb;
	}

	void draw(HWND & ghMainWnd) {
		 HDC hdc;
		 hdc = GetDC(ghMainWnd);
		 HBRUSH hBrush;
		 HPEN bPen;
		 hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(120,220,120));
		 bPen = CreatePen(PS_INSIDEFRAME,1,RGB(120,120,120));
		 SelectObject(hdc,hBrush);
		 SelectObject(hdc,bPen);
		 RoundRect(hdc,xl,yt,xr,yb,10,10);
		 DeleteObject(hBrush);
		 DeleteObject(bPen);
		 ReleaseDC(ghMainWnd,hdc);
	}
	int drawUp(HWND & ghMainWnd) {
		if (yb>-5) {
			yb -= 5;
			yt -= 5;
			draw(ghMainWnd);
			return 1;
		} else return 0;
	}
};

#endif