#include <Windows.h>
#include <Winuser.h>
#include <gdiplus.h>
#include <string>

#include "MainClassPrototypes.h"
#include "mswa.h"
#pragma comment(lib,"gdiplus.lib")

mswa::Map map;

enum MainWindowParams {
	X = 630,
	Y = 300,
	HEIGHT = 500,
	WIDTH = 500
};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{

	hasGameStarted = false;

	Gdiplus::GdiplusStartupInput gdiStartIn;
	ULONG_PTR gdiToken;
	Gdiplus::GdiplusStartup(&gdiToken, &gdiStartIn, nullptr);

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

	Gdiplus::GdiplusShutdown(gdiToken);
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

	short mapHeight;
	short mapWidth;

	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg)
	{
	case WM_COMMAND:
		switch (wparam)
		{
		case Start:
			hasGameStarted = true;
			HideMainMenuWidgets();
			break;
		case Exit:
			result = MessageBox(hwnd, L"Are you sure you want to exit the game?", L"Exit", MB_YESNO);
			if (result == YES) PostQuitMessage(0);
			break;
		}
		break;
	case WM_CREATE:
		AddMainWindowMenu(hwnd);
		AddMainWindowWidgets(hwnd);
		//ShowMainMenuWidgets();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		mapHeight = map.getSize().height;
		mapWidth = map.getSize().width;
		for (int i = 0; i < mapHeight; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				short cell = map.getCell(i, j);
				switch(cell)
				{
				default: drawImage(L"C:\\Users\\rost1\\source\\repos\\MinesweeperWA\\images\\covered.jpg", hdc, j * 32, i * 32);
				};
			}
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONUP:
		POINT p;
		GetCursorPos(&p);
		if (ScreenToClient(hwnd, &p))
		{


			SetWindowTextW(forTests, std::to_wstring(p.x).c_str());
		}
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
	GameSettings = CreateWindowA("button", "Settings", WS_CHILD, WIDTH * 3 / 8, 3 * HEIGHT / 8, WIDTH / 4, HEIGHT / 8, hwnd, (HMENU)Settings, NULL, NULL);
	ExitGame = CreateWindowA("button", "Exit", WS_CHILD, WIDTH * 3 / 8, HEIGHT / 2, WIDTH / 4, HEIGHT / 8, hwnd, (HMENU)Exit, NULL, NULL);
	forTests = CreateWindowA("static", "a", WS_CHILD | WS_VISIBLE, WIDTH - 55, HEIGHT - 60, 25, 20, hwnd, NULL, NULL, NULL);

}

void ShowMainMenuWidgets()
{
	ShowWindow(StartGame, SW_SHOW);
	ShowWindow(GameSettings, SW_SHOW);
	ShowWindow(ExitGame, SW_SHOW);
}

void HideMainMenuWidgets()
{
	ShowWindow(StartGame, SW_HIDE);
	ShowWindow(GameSettings, SW_HIDE);
	ShowWindow(ExitGame, SW_HIDE);
}

void drawImage(LPCWSTR filepath, HDC hdc, INT x, INT y)
{

	Gdiplus::Graphics graphics(hdc);
	
	Gdiplus::Bitmap img(filepath);
	graphics.DrawImage(&img, x, y);

}

