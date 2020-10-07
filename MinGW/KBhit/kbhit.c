#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <strsafe.h>
#pragma comment(lib,"user32.lib")
COORD  max_xy;
void remove_scrollbar()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size = 
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
	max_xy=new_size;
    SetConsoleScreenBufferSize(handle, new_size);
}
 
void setwindow(){
	HWND console = GetConsoleWindow();
	ShowWindow(console,SW_SHOWMAXIMIZED);
	RECT rect;
	GetWindowRect(console, &rect);
	printf("%i %i %i %i\n",rect.top,rect.left,rect.bottom,rect.right);
	COORD coord={rect.right+rect.left,rect.bottom+rect.top};
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	
}
void settitle(){
	 TCHAR szOldTitle[MAX_PATH];
   TCHAR szNewTitle[MAX_PATH];

   // Save current console title.

   if( GetConsoleTitle(szOldTitle, MAX_PATH) )
   {
      // Build new console title string.

      StringCchPrintf(szNewTitle, MAX_PATH, TEXT("Snake Game"));

      // Set console title to new title
      if( !SetConsoleTitle(szNewTitle) )
      {
         _tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
         return;
      }
      else
      {
         _tprintf(TEXT("SetConsoleTitle succeeded.\n"));
      }
   }
}
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 1;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void gotoxy(int x,int y){
	COORD coord={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void checkinput(){	
	char ch='d';
	int delay=2,fx=1,fy=0,x=2,y=2,px=1,py=1;
	while(ch!='q')
	{
		if(kbhit()){
			ch=getche();
		}
		if(ch==119){
			fx=0;
			fy=-1;
		}else
		if(ch==100){
			fx=2;
			fy=0;
		}else
		if(ch==97){
			fx=-2;
			fy=0;
		}else
		if(ch==115){
			fx=0;
			fy=1;
		}
		px=x;
		py=y;
		if(x<max_xy.X&&x>0){
			x=x+fx;
			if(x<=0)x=1;
			if(x>=max_xy.X)x=max_xy.X-1;
		}
		if(y<max_xy.Y&&y>0){
			y=y+fy;
			if(y<=0)y=1;
			if(y>=max_xy.Y)y=max_xy.Y-1;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1515);
		gotoxy(x,y);
		printf("O");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),00);
		gotoxy(px,py);
		printf("O");
		Sleep(90);
	}
}

int main(){
	settitle();
	setwindow();
	remove_scrollbar();
	hidecursor();
	system("CLS");
	checkinput();
	return 0;
}
