/*------------------------------------------------------------
   Ϳѻ����
  ------------------------------------------------------------*/

#include "GameHead.h"
//���Դ�ļ�
#include "DrawBoard.cpp"
//���Ӷ���Դ�ļ�
#include "BoardList.cpp"
//���������Դ�ļ�
#include "RandHelper.cpp"
//����
#include "Role.cpp"

//ȫ�ֱ���
HWND ghMainWnd;
SIZE size;
static HPEN		blackPen;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
void drawBackground();

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("Ϳѻ����") ;
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
                          TEXT ("Ϳѻ����"), // window caption
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
		//�ػ汳��
		drawBackground();

		//�������ľ��
		if (rh.randCreate()==1) {
			tmpX = rh.randX();
			tmpY = WINDOW_HEIGHT;
			//��������ľ��֮��������
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
		
		//ľ������
		for (int i=0;i<blist.getCount();i++) {
			tmpboard = blist[(blist.getTil()+i)%blist.getMax()];
			if (!blist.empty()&&tmpboard->drawUp(ghMainWnd)==0) {
				blist.removeTopBoard();
			}
			if (abs(tmpboard->getYt()-(role.getYt()+40))<=5) {
				//�жϽ�ɫ�����Ƿ���ľ�棬����ͣ��
				
				if ((tmpboard->getXl()<role.getXl()&&tmpboard->getXr()>role.getXl())||(tmpboard->getXr()>(role.getXl()+40)&&tmpboard->getXl()<role.getXl()+40)){
				        //tyb = tmpboard->getYt()-role.getYb();
						//tyt = role.getYt()-tyb;
					    
					    role.setOnBoard(tmpboard->getYb());
						
				        role.setFall(false);
				}
			}
		}
		//���ƽ�ɫ
		if(role.getFall()){
		
		laycount += 5;
		}
		role.drawUp(ghMainWnd);
		hdc = GetDC(ghMainWnd);
		wsprintf(buf, " %d", laycount);
		TextOut(hdc, 300, 300, buf, strlen(buf));
	    return 0;

	 case WM_CHAR:
		 tmpfall = true;
		 drawBackground();
		 for (int i=0;i<blist.getCount();i++) {
			if (!blist.empty()) {
				tmpboard = blist[(blist.getTil()+i)%blist.getMax()];
				tmpboard->draw(ghMainWnd);
			}
		}

		 switch (wParam) {
			case 'a':
				role.drawLeft(ghMainWnd);
				break;
			case 'd':
				role.drawRight(ghMainWnd);
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

void drawBackground(){
	HBRUSH bBrush;
	HPEN oPen;
	RECT rt;
	HDC hdc;
	hdc = GetDC(ghMainWnd);
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
	ReleaseDC(ghMainWnd,hdc);
};

