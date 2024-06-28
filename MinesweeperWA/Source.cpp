#include <Windows.h>
#include <Winuser.h>

#include "MainClassPrototypes.h"

enum MainWindowParams {
	X = 630,
	Y = 300,
	HEIGHT = 500,
	WIDTH = 500
};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{

	WNDCLASS MainClass = CreateWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, IDI_EXCLAMATION),
		L"MainWindow", MainClassProcedure);

	if (!RegisterClass(&MainClass)) return -1;

	MSG MainMessage = { 0 };

	CreateWindow(MainClass.lpszClassName, L"Window", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, X, Y, WIDTH, HEIGHT, NULL,
		NULL, NULL, NULL);

	while (GetMessage(&MainMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&MainMessage);
		DispatchMessageW(&MainMessage);
	}

	return 0;
}

WNDCLASS CreateWindowClass(HBRUSH color, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure)
{

	WNDCLASS wndclass = { 0 };

	wndclass.hCursor = cursor;
	wndclass.hIcon = icon;
	wndclass.lpszClassName = name;
	wndclass.hInstance = hInst;
	wndclass.hbrBackground = color;
	wndclass.lpfnWndProc = procedure;

	return wndclass;
}

LRESULT CALLBACK MainClassProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	int result = 0;

	switch (msg)
	{
	case WM_COMMAND:
		switch (wparam)
		{
		case Exit:
			result = MessageBox(hwnd, L"Are you sure you want to exit the game?", L"Exit", MB_YESNO);
			if (result == YES) PostQuitMessage(0);
			break;
		}
		break;
	case WM_CREATE:
		AddMainWindowMenu(hwnd);
		AddMainWindowWidgets(hwnd);
		ShowMainMenuWidgets();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

}

void AddMainWindowMenu(HWND hwnd)
{

}

void AddMainWindowWidgets(HWND hwnd)
{

	StartGame = CreateWindowA("button", "Start", WS_CHILD, WIDTH * 3 / 8, HEIGHT / 4, WIDTH / 4, HEIGHT / 8, hwnd, (HMENU)Start, NULL, NULL);
	ExitGame = CreateWindowA("button", "Exit", WS_CHILD, WIDTH * 3 / 8, 3 * HEIGHT / 8, WIDTH / 4, HEIGHT / 8, hwnd, (HMENU)Exit, NULL, NULL);

}

void ShowMainMenuWidgets()
{
	ShowWindow(StartGame, SW_SHOW);
	ShowWindow(ExitGame, SW_SHOW);
}