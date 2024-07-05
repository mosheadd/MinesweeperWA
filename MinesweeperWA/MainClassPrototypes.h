#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <ctime>

//Definitions

//Handlers
#define Start 1
#define Exit 2
#define Settings 3
#define ChooseEasy 4
#define ChooseMedium 5
#define ChooseHard 6
#define Back 7

//Others
#define YES IDYES
#define NO IDNO

#define TIMER1 1

int nTimerID;

//Widgets

//Main menu
HWND StartGame;
HWND ExitGame;
HWND GameSettings;

//Difficulties
HWND Easy;
HWND Medium;
HWND Hard;

HWND BackButton;

//Texts
HWND Time;
HWND Flags;

HWND forTests;

//Conditions
bool hasGameStarted;
bool hasGameEnded;
bool firstMoveDone;

//Clock
clock_t clockStart;

//Functions 
LRESULT CALLBACK MainClassProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

WNDCLASS CreateWindowClass(HBRUSH color, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);

void AddMainWindowMenu(HWND hwnd);
void AddMainWindowWidgets(HWND hwnd);
void ShowMainMenuWidgets();
void HideMainMenuWidgets();
void ShowDifficultiesWidgets();
void HideDifficultiesWidgets();
void drawImage(LPCWSTR filepath, HDC hdc, INT x, INT y);
void initGame(short width, short height, HWND hwnd);