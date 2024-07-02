#pragma once
#include <Windows.h>
#include <gdiplus.h>

//Definitions
#define Start 1
#define Exit 2
#define Settings 3
#define YES IDYES
#define NO IDNO

//Widgets

//Main menu
HWND StartGame;
HWND ExitGame;
HWND GameSettings;

HWND forTests;

//Conditions
bool hasGameStarted;
bool firstMoveDone;

//Functions 
LRESULT CALLBACK MainClassProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

WNDCLASS CreateWindowClass(HBRUSH color, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);

void AddMainWindowMenu(HWND hwnd);
void AddMainWindowWidgets(HWND hwnd);
void ShowMainMenuWidgets();
void HideMainMenuWidgets();
void drawImage(LPCWSTR filepath, HDC hdc, INT x, INT y);