#include "GameHead.h"
#include "resource.h"

#ifndef ROLE
#define ROLE
class Role{
private:
	int xl,yt;
	boolean fall;
	int laycount;
	int life;
	int width, height;
	int l;
	int r;
	int d;
	int flag;
	int k;


public:

	Role(int xl,int yt):xl(xl),yt(yt), width(40), height(37){
		life=1;
		l=1;
		r=1;
		d=1;
		k=1;
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
	int getflag(){
		return flag;
	}
	void setFall(boolean f){
		fall = f;
	}

	int getLife(){
		return life;
	}

	boolean getFall(){
		return fall;
	}
	void setOnBoard(int yb1){
	
		yt = yb1-40;

	}

	//void draw(HWND & ghMainWnd){
	//	 HDC hdc, memDC;
	//	 hdc = GetDC(ghMainWnd);
	//	 HBITMAP l1, tmpBitmap, cBitmap;
	//	 memDC = CreateCompatibleDC(hdc);
	//	 //cBitmap = CreateCompatibleBitmap(memDC, 120,120);
	//	 //SelectObject(memDC, cBitmap);
	//	 l1 = LoadBitmap(ghInst, "L1");
	//	// SelectObject(memDC, db);
	//	 tmpBitmap = (HBITMAP)SelectObject(memDC, l1);
	//	 // BitBlt(hdc, 50, 50, 120, 120, memDC, 0 ,0 ,SRCCOPY);
	//	 TransparentBlt(hdc,xl,yt,40,40,memDC,0,0,width,height,RGB(0,0,255));
	//	 SelectObject(hdc, tmpBitmap);
	//	 DeleteObject(l1);
	//	 /* HBRUSH hBrush;
	//	 HPEN bPen;
	//	 hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(120,220,120));
	//	 bPen = CreatePen(PS_INSIDEFRAME,1,RGB(120,120,120));
	//	 SelectObject(hdc,hBrush);
	//	 SelectObject(hdc,bPen);
	//	 Ellipse(hdc,xl,yt,xr,yb);
	//	 DeleteObject(hBrush);
	//	 DeleteObject(bPen);
	//	 ReleaseDC(ghMainWnd,hdc);	*/
	//}
	

	void drawl(HWND & ghMainWnd,int i)
	{
		HDC hdc, memDC;
		 hdc = GetDC(ghMainWnd);
		 HBITMAP l[8], tmpBitmap, cBitmap;
		 memDC = CreateCompatibleDC(hdc);
		 //cBitmap = CreateCompatibleBitmap(memDC, 120,120);
		 //SelectObject(memDC, cBitmap);
		 l[1] = LoadBitmap(ghInst, "L1");
		 l[2] = LoadBitmap(ghInst, "L2");
		 l[3] = LoadBitmap(ghInst, "L3");
		 l[4] = LoadBitmap(ghInst, "L4");
		 l[5] = LoadBitmap(ghInst, "L5");
		 l[6] = LoadBitmap(ghInst, "L6");
		// SelectObject(memDC, db);

		 tmpBitmap = (HBITMAP)SelectObject(memDC, l[i]);
		 // BitBlt(hdc, 50, 50, 120, 120, memDC, 0 ,0 ,SRCCOPY);
		 TransparentBlt(hdc,xl,yt,40,40,memDC,0,0,width,height,RGB(0,0,255));
		 SelectObject(hdc, tmpBitmap);
		 for(int i=1;i<=6;i++)
		 {
		 DeleteObject(l[i]);
		 }
		 
	}

	void drawr(HWND & ghMainWnd,int i)
	{
		HDC hdc, memDC;
		 hdc = GetDC(ghMainWnd);
		 HBITMAP r[6], tmpBitmap, cBitmap;
		 memDC = CreateCompatibleDC(hdc);
		 r[1] = LoadBitmap(ghInst, "R1");
		 r[2] = LoadBitmap(ghInst, "R2");
		 r[3] = LoadBitmap(ghInst, "R3");
		 r[4] = LoadBitmap(ghInst, "R4");

		 tmpBitmap = (HBITMAP)SelectObject(memDC, r[i]);
		 TransparentBlt(hdc,xl,yt,40,40,memDC,0,0,width,height,RGB(0,0,255));
		 SelectObject(hdc, tmpBitmap);
		 for(int i=1;i<=4;i++)
		 {
		 DeleteObject(r[i]);
		 }
	}
	void drawd(HWND & ghMainWnd,int i)
	{
		if (yt<0) {
			life=0;
			return;
		}
		else if ((yt+40)>WINDOW_HEIGHT) {
			life=0;
			return ;
		}
		HDC hdc, memDC;
		 hdc = GetDC(ghMainWnd);
		 HBITMAP d[6], tmpBitmap, cBitmap;
		 memDC = CreateCompatibleDC(hdc);
		 //cBitmap = CreateCompatibleBitmap(memDC, 120,120);
		 //SelectObject(memDC, cBitmap);
		 d[1] = LoadBitmap(ghInst, "D1");
		 d[2] = LoadBitmap(ghInst, "D2");
		 d[3] = LoadBitmap(ghInst, "D3");
		 d[4] = LoadBitmap(ghInst, "D4");
		 
		 
		// SelectObject(memDC, db);

		 tmpBitmap = (HBITMAP)SelectObject(memDC, d[i]);
		 // BitBlt(hdc, 50, 50, 120, 120, memDC, 0 ,0 ,SRCCOPY);
		 TransparentBlt(hdc,xl,yt,40,40,memDC,0,0,width,height,RGB(0,0,255));
		 SelectObject(hdc, tmpBitmap);
		 for(int i=1;i<=4;i++)
		 {
		 DeleteObject(d[i]);
		 }
	}

	int drawDown(HWND ghMainWnd,int i) 
	{
		if (fall) 
		{
			if ((yt+40)<WINDOW_HEIGHT) {
			yt +=10;
			drawd(ghMainWnd,i);
			return 1;
			}
			else return 0;
		}
		else 
		{
			if (yt>0) 
			{
				
				yt -= 5;
				drawd(ghMainWnd,i);
				return 1;
			} else return 0;
		}
	}

	void drawLeft(HWND ghMainWnd,int i) 
	{
		
		if (xl>0&&!fall) 
		{
			xl -= 10;
			drawl(ghMainWnd,i);
		}		
		else
		{
			xl -= 10;
			if(k>4)
			{
				k=1;
				drawd(ghMainWnd,k);
				k++;
			}
			else
			{
				drawd(ghMainWnd,k);
				k++;
			}
		}

	}


	void drawRight(HWND ghMainWnd,int i) 
	{
		if (xl<WINDOW_WIDTH&&!fall) 
		{
			xl += 10;
			
			drawr(ghMainWnd,i);
		}
		else
		{
			xl += 10;
			
			drawd(ghMainWnd,i);
		}
	}

	void draws(HWND ghMainWnd) 
	{
		xl=WINDOW_WIDTH/2;
		yt=0;
		life=1;
	}
	/*void mytimel(HWND ghMainWnd,int lnum){
		if(lnum=1){
			if(l<=6){
				drawLeft(ghMainWnd,l);
				l++;
			}
			else {
				l=1;
				drawLeft(ghMainWnd,l);
			}
		}
		
	}

		void mytimer(HWND ghMainWnd,int rnum){
		if(rnum=1){
			if(r<=4){
				drawRight(ghMainWnd,r);
				r++;
			}
			else {
				r=1;
				drawRight(ghMainWnd,r);
			}
		}
		
	}

*/

	int setflag(int num)
	{
		//if(num==0)flag=0;
		//else if(num==1)flag=1;
		//else if(num==2)flag=2;
		//else if(num==3)flag=3;
		flag = num;
		return flag;
	}
	void mytime(HWND ghMainWnd)
	{
		if(flag==2)
		{
			if (fall&&(yt+40)<WINDOW_HEIGHT)
			{ 
				yt +=10;
			}
			else{
			yt-=5;
			}
			if(r<=4)
			{
				drawRight(ghMainWnd,r);
				r++;
			}
			else 
			{
				r=1;
				drawRight(ghMainWnd,r);
			}
		}

		else if(flag==1)
		{
			if (fall&&(yt+40)<WINDOW_HEIGHT)
			{ 
				yt +=10;
			}
			else{
			yt-=5;
			}
			if(l<=6)
			{
				drawLeft(ghMainWnd,l);
				l++;
			}
			else 
			{
				l=1;
				drawLeft(ghMainWnd,l);
			}
					
		}
		else if(flag==0)
		{
			if(d<=4)
			{
				drawDown(ghMainWnd,d);
				d++;
			}
			else 
			{
				d=1;
				drawDown(ghMainWnd,d);
			}
		}

		else if(flag==3)
		{
			if (fall&&(yt+40)<WINDOW_HEIGHT)
			{ 
				yt +=10;
			}
			else{
			yt-=5;
			}
			drawd(ghMainWnd,2);
		}
		else if(flag==4)
		{
			draws(ghMainWnd);
		}
		
	}

};

#endif