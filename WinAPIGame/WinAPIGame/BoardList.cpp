#include "GameHead.h"
#include "DrawBoard.cpp"
#include "Role.cpp"
#ifndef BOARDLIST
#define BOARDLIST
class List {
private :
	int max;
	Board * blist[10];
	int top;
	int til;
	int count;
public :
	List():top(0),til(0),count(0) {
		max = 10;
	};

	int getCount(){
		return count;
	}

	int getTil() {
		return til;
	}

	int getMax() {
		return max;
	}

	int empty() {
		return !count;
	}

	void addBoard(Board * b) {
		if (count<max) {
			top = (count+til)%max;
			blist[top] = b;
			count += 1;
		}
		else return;
	}
	void removeTopBoard() {
		if (count>0) {
			delete blist[til];
			til = (til+1)%max;
			count -= 1;
		}
		else return;
	}

	HDC & drawBackground(HDC & memDC){
	HBRUSH bBrush;
	HPEN oPen;
	RECT rt;	
	SelectObject(memDC,GetStockObject(WHITE_BRUSH));
	SelectObject(memDC,GetStockObject(WHITE_PEN));
	Rectangle(memDC,0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	oPen = CreatePen(PS_SOLID,1,RGB(255,204,153));
	bBrush = CreateSolidBrush(RGB(235, 255, 255));
	rt.left = 0;
	rt.right = size.cx;
	rt.top = 0;
	rt.bottom = size.cy;
	SelectObject(memDC, bBrush);
	FillRect(memDC,&rt,NULL);
	SelectObject(memDC, oPen);
	for (int i=0;i<size.cy;i+=15) {
		MoveToEx(memDC,0,i,NULL);
		LineTo(memDC,size.cx,i);
	}
	for (int i=0;i<size.cx;i+=15) {
		MoveToEx(memDC,i,0,NULL);
		LineTo(memDC,i,size.cy);
	}
	DeleteObject(bBrush);
	DeleteObject(oPen);
	return memDC;
};

	void drawAll(Role & role){
		Board * tmpboard;
		HDC memDC,hdc;
		hdc = GetDC(ghMainWnd);
		HBITMAP hBitMapKB = CreateCompatibleBitmap(hdc,WINDOW_WIDTH,WINDOW_HEIGHT);
		memDC = CreateCompatibleDC(GetDC(ghMainWnd));
		SelectObject(memDC,hBitMapKB);
		memDC = drawBackground(memDC);
		for (int i=0;i<getCount();i++) {
			tmpboard = blist[(getTil()+i)%getMax()];
			memDC = tmpboard->draw(memDC);
		}
		BitBlt(GetDC(ghMainWnd),0,0,WINDOW_WIDTH,WINDOW_HEIGHT,memDC,0,0,SRCCOPY);

		for (int i=0;i<getCount();i++) {
			tmpboard = blist[(getTil()+i)%getMax()];
			if (!empty()&&tmpboard->drawUp()==0) {
				removeTopBoard();
			}
			if (abs(tmpboard->getYt()-(role.getYt()+40))<=5) {
				//判断角色脚下是否有木版，有则停留
				if ((tmpboard->getXl()<role.getXl()&&tmpboard->getXr()>role.getXl())||(tmpboard->getXr()>(role.getXl()+40)&&tmpboard->getXl()<role.getXl()+40)){
					    role.setOnBoard(tmpboard->getYb());
						role.setflag(3);						
				        role.setFall(false);
				}
			}
		}
		ReleaseDC(ghMainWnd,memDC);
		ReleaseDC(ghMainWnd,hdc);
	}

	Board * operator[](int i){
		return blist[i];
	}

	void clean() {
		for (int i=til;i<count;i++) {
			delete blist[(i+count)%max];
		}
		til = 0;
		top = 0;
		count = 0;
	}
};

#endif

