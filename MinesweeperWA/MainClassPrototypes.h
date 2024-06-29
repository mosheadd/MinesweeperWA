#pragma once
#include <Windows.h>

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


LRESULT CALLBACK MainClassProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

WNDCLASS CreateWindowClass(HBRUSH color, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);

void AddMainWindowMenu(HWND hwnd);
void AddMainWindowWidgets(HWND hwnd);
void ShowMainMenuWidgets();
