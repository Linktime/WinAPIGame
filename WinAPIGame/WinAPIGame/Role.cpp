#include "GameHead.h"
#ifndef ROLE
#define ROLE
class Role{
private:
	int xl,yt,xr,yb;
	boolean fall;
	int life;
public:
	Role(int xl,int yt,int xr,int yb):xl(xl),yt(yt),xr(xr),yb(yb){
		life=1;
		fall=true;
	}

	int getYb(){
		return yb;
	}

	int getXl() {
		return xl;
	}

	int getYt() {
		return yt;
	}

	int getXr() {
		return xr;
	}

	void setFall(boolean f){
		fall = f;
	}

	void draw(HWND ghMainWnd){
		 HDC hdc;
		 hdc = GetDC(ghMainWnd);
		 HBRUSH hBrush;
		 HPEN bPen;
		 hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(120,220,120));
		 bPen = CreatePen(PS_INSIDEFRAME,1,RGB(120,120,120));
		 SelectObject(hdc,hBrush);
		 SelectObject(hdc,bPen);
		 Ellipse(hdc,xl,yt,xr,yb);
		 DeleteObject(hBrush);
		 DeleteObject(bPen);
		 ReleaseDC(ghMainWnd,hdc);	
	}

	int drawUp(HWND ghMainWnd) {
		if (fall&&yb<WINDOW_HEIGHT) {
			yb += 5;
			yt +=5;
			draw(ghMainWnd);
			return 1;
		}
		else {
			if (yb>0) {
				yb -= 5;
				yt -= 5;
				draw(ghMainWnd);
				return 1;
			} else return 0;
		}
	}

	void drawLeft(HWND ghMainWnd) {
		if (xl>0) {
			xl -= 5;
			xr -= 5;
			draw(ghMainWnd);
		}
	}

		void drawRight(HWND ghMainWnd) {
			if (xl<WINDOW_WIDTH) {
			xl += 5;
			xr += 5;
			draw(ghMainWnd);
		}
	}
};

#endif