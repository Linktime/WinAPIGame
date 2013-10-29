#include "GameHead.h"
#ifndef ROLE
#define ROLE
class Role{
private:
	int xl,yt;
	boolean fall;
	int laycount;
	int life;
	int width, height;

public:
	Role(int xl,int yt):xl(xl),yt(yt), width(40), height(40){
		life=1;
		fall=true;
	}


	int getXl() {
		return xl;
	}

	int getYt() {
		return yt;
	}

	int getWidth() {
		return width;
	} 

	int getHeight(){
		return height;
	}
	int getLaycount(){
		return laycount; 
	}
	void setFall(boolean f){
		fall = f;
	}
	boolean getFall(){
		return fall;
	}
	void setOnBoard(int yb1){
	
		yt = yb1-40;

	}

	void draw(HWND & ghMainWnd){
		 HDC hdc, memDC;
		 hdc = GetDC(ghMainWnd);
		 HBITMAP db, tmpBitmap, cBitmap;
		 memDC = CreateCompatibleDC(hdc);
		 //cBitmap = CreateCompatibleBitmap(memDC, 120,120);
		 //SelectObject(memDC, cBitmap);
		 db = LoadBitmap(ghInst, "db");
		// SelectObject(memDC, db);
		 tmpBitmap = (HBITMAP)SelectObject(memDC, db);
        // BitBlt(hdc, 50, 50, 120, 120, memDC, 0 ,0 ,SRCCOPY);
		 TransparentBlt(hdc,xl,yt,40,40,memDC,0,0,width,height,RGB(0,0,255));
		SelectObject(hdc, tmpBitmap);
		 DeleteObject(db);
		 /* HBRUSH hBrush;
		 HPEN bPen;
		 hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(120,220,120));
		 bPen = CreatePen(PS_INSIDEFRAME,1,RGB(120,120,120));
		 SelectObject(hdc,hBrush);
		 SelectObject(hdc,bPen);
		 Ellipse(hdc,xl,yt,xr,yb);
		 DeleteObject(hBrush);
		 DeleteObject(bPen);
		 ReleaseDC(ghMainWnd,hdc);	*/
	}

	int drawUp(HWND ghMainWnd) {
		if (fall&&(yt+40)<WINDOW_HEIGHT) {
			
			yt +=5;
			draw(ghMainWnd);
			return 1;
		}
		else {
			if ((yt+40)>0) {
				
				yt -= 5;
				draw(ghMainWnd);
				return 1;
			} else return 0;
		}
	}

	void drawLeft(HWND ghMainWnd) {
		if (xl>0) {
			xl -= 5;
			
			draw(ghMainWnd);
		}
	}

		void drawRight(HWND ghMainWnd) {
			if (xl<WINDOW_WIDTH) {
			xl += 5;
			
			draw(ghMainWnd);
		}
	}
};

#endif