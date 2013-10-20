/*------------------------------------------------------------
   Í¿Ñ»ÌÓÍö
  ------------------------------------------------------------*/

#include <windows.h>
#include <TCHAR.h>
#include "draw.cpp"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 960

#define _UNICODE

//È«¾Ö±äÁ¿
HWND ghMainWnd;
static SIZE size;
static HPEN		blackPen;

class Board {
private:
	int xl,yt,xr,yb;
public:
	Board(int xl,int yt,int xr,int yb):xl(xl),yt(yt),xr(xr),yb(yb){}
	void up(){
		yt+=10;
		yb+=10;
	}
	void draw(HDC & hdc) {
	Ellipse(hdc,xl,yt,xr,yb);
	}
};

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
void drawBackground(HDC & hdc);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("Í¿Ñ»ÌÓÍö") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;
	 int x,y;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     
	 x=(GetSystemMetrics(SM_CXSCREEN)-WINDOW_WIDTH)/2;
	 y=(GetSystemMetrics(SM_CXSCREEN)-WINDOW_HEIGHT)/8;

     hwnd = CreateWindow (szAppName,                  // window class name
                          TEXT ("Í¿Ñ»ÌÓÍö"), // window caption
                          WS_OVERLAPPEDWINDOW,        // window style
                          x,              // initial x position
                          y,              // initial y position
						  WINDOW_WIDTH,              // initial x size
						  WINDOW_HEIGHT,              // initial y size
                          NULL,                       // parent window handle
                          NULL,                       // window menu handle
                          hInstance,                  // program instance handle
                          NULL) ;                     // creation parameters
     ghMainWnd = hwnd;
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
	 HINSTANCE   hInstance;
	 static HBRUSH pBrush;
	
	      
     switch (message)
     {
     case WM_CREATE:
		  blackPen = CreatePen(PS_SOLID,20,RGB(0,0,0));
		  pBrush = CreateSolidBrush(RGB(255, 213, 213));
		  return 0 ;
          
	case WM_SIZE:
		  size.cx  = LOWORD(lParam);
		  size.cy  = HIWORD(lParam);
		    
		  return 0;

     case WM_PAINT:
          //hdc = BeginPaint (hwnd, &ps) ;
		  
		  //Ellipse(hdc,100,200,300,450);
          //EndPaint (hwnd, &ps) ;
          return 0 ;

	 case WM_CHAR:
		 hdc = GetDC(hwnd);
		 drawBackground(hdc);
		 //TODO
		 //Board b1 =new Board(100,100,200,200);
		 //b1.draw(hdc);
		 ReleaseDC(hwnd,hdc);
          return 0;

     case WM_DESTROY:
		 DeleteObject(pBrush);
		 DeleteObject(blackPen);
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

void drawBackground(HDC & hdc){
	HBRUSH bBrush;
	HPEN oPen;
	RECT rt;
	oPen = CreatePen(PS_SOLID,1,RGB(255,204,153));
	bBrush = CreateSolidBrush(RGB(235, 255, 255));
	rt.left = 0;
	rt.right = size.cx;
	rt.top = 0;
	rt.bottom = size.cy;
	SelectObject(hdc, bBrush);
	FillRect(hdc,&rt,NULL);
	SelectObject(hdc, oPen);
	for (int i=0;i<size.cy;i+=15) {
		MoveToEx(hdc,0,i,NULL);
		LineTo(hdc,size.cx,i);
	}
	for (int i=0;i<size.cx;i+=15) {
		MoveToEx(hdc,i,0,NULL);
		LineTo(hdc,i,size.cy);
	}
	DeleteObject(bBrush);
	DeleteObject(oPen);
};