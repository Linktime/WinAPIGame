#ifndef GAMEHEAD_H
#define GAMEHEAD_H
#include <windows.h>
#include <TCHAR.h>
#pragma comment(lib,"msimg32.lib")
//定义窗口大小
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 480
//计时器ID
#define TIMER 1
#define _UNICODE
//SIZE size;
static HINSTANCE ghInst;
static HWND ghMainWnd;
static SIZE size;
#endif