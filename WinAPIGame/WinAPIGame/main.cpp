/*------------------------------------------------------------
   涂鸦逃亡
  ------------------------------------------------------------*/

#include "GameHead.h"
//绘板源文件
#include "DrawBoard.cpp"
//板子队列源文件
#include "BoardList.cpp"
//随机数帮助源文件
#include "RandHelper.cpp"
//人物
#include "Role.cpp"
//全局变量

static HPEN		blackPen;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
void drawBackground();

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("涂鸦逃亡") ;
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
                          TEXT ("涂鸦逃亡"), // window caption
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
     ghInst = hInstance;
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
	 int tmpX;
	 int tmpY;
	 static HBRUSH pBrush;
	 boolean tmpfall;
	 static Role role(WINDOW_WIDTH/2,0);
	 static Board * lastboard;
	 Board * tmpboard;
	 static List blist;
	 randhelper rh;
	 static int flag1= 1,flag2=0; 
	 static char buf[50]; 
	 static int laycount;
	 static int num=0;
	 //int nKey;
	 

	 static int tyb, tyt;
     switch (message)
     {
     case WM_CREATE:
		  blackPen = CreatePen(PS_SOLID,20,RGB(0,0,0));
		  pBrush = CreateSolidBrush(RGB(255, 213, 213));
		  SetTimer(hwnd,TIMER,100,(TIMERPROC) NULL);
		  lastboard = NULL;
		  return 0 ;
          
	case WM_SIZE:
		  size.cx  = LOWORD(lParam);
		  size.cy  = HIWORD(lParam);
		  //pb->draw(ghMainWnd);
		  return 0;

	case WM_TIMER:
		if (!role.getLife()) {
			return 0;
		}

		//随机生成木块
		if (rh.randCreate()==1) {
			tmpX = rh.randX();
			tmpY = WINDOW_HEIGHT;
			//避免两块木板之间距离过近
			if (lastboard){
				if (abs(lastboard->getXl()-tmpX)<100) {
					tmpX = lastboard->getXl()>tmpX?tmpX-100:tmpX+100;
				}
				if (abs(lastboard->getYb()-0)<50) {
					tmpY = lastboard->getYb() - 50;
				}

			}
			tmpboard = new Board(tmpX,tmpY,tmpX+100,tmpY+10);
			lastboard = tmpboard;
			blist.addBoard(tmpboard);
		}
		
		//木板上升
		blist.drawAll(role);
		
		//设置角色状态
		if(role.getFall())
		{
			laycount += 10;	
		}
		
		if(role.getFall()&&role.getflag()==0)
		{
			role.setflag(0);
		}
		else if(!role.getFall()&&role.getflag()==0)
		{
			role.setflag(3);
		}


		role.mytime(ghMainWnd);

		hdc = GetDC(ghMainWnd);
		wsprintf(buf, "分数： %d", laycount);
		TextOut(hdc, 10, 10, buf, strlen(buf));
		ReleaseDC(ghMainWnd,hdc);
	    return 0;


	    case WM_KEYUP:
			 role.setflag(0);
		return 0;

	 case WM_CHAR:

		 tmpfall = true;
		 switch (wParam) {
			case 'a':
				role.setflag(1);
				break;
			case 'd':
				role.setflag(2);
				break;
			case 'w':
				role.setFall(false);
				break;
			case 's':
				role.setFall(true);
				break;
		 }

		 	for (int i=0;i<blist.getCount();i++) {
			if (!blist.empty()) {
				tmpboard = blist[(blist.getTil()+i)%blist.getMax()];
				if (abs(tmpboard->getYt()-(role.getYt()+40))<=5)
					if ((tmpboard->getXl()<role.getXl()&&tmpboard->getXr()>role.getXl())||(tmpboard->getXr()>(role.getXl()+40)&&tmpboard->getXl()<(role.getXl()+40))){
						
						tmpfall=false;
					}
			}
		}
			role.setFall(tmpfall);

          return 0;
		  
	 case WM_LBUTTONDOWN:
		 
		 return 0;
	
     case WM_DESTROY:
		 blist.clean();
		 DeleteObject(pBrush);
		 DeleteObject(blackPen);
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

