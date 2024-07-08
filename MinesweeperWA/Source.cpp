#include "iostream"
#include <Windows.h>
#include <Winuser.h>
#include <gdiplus.h>
#include <string>
#include <fstream>

#include "MainClassPrototypes.h"
#include "mswa.h"
#pragma comment(lib,"gdiplus.lib")

mswa::Map gamemap;

enum MainWindowParams {
	X = 630,
	Y = 300,
	HEIGHT = 640,
	WIDTH = 640
};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	std::srand(std::time(0));
	hasGameStarted = false;
	hasGameEnded = false;
	firstMoveDone = false;

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
	int duration;

	short mapHeight = gamemap.getSize().height;
	short mapWidth = gamemap.getSize().width;

	HDC hdc;
	PAINTSTRUCT ps;
	POINT p;

	switch (msg)
	{
	case WM_COMMAND:
		switch (wparam)
		{
		case Start:
			HideMainMenuWidgets();
			ShowDifficultiesWidgets();
			break;
		case Settings:
			
			break;
		case Back:
			ShowMainMenuWidgets();
			HideDifficultiesWidgets();
			break;
		case ChooseEasy:
			initGame(5, 5, hwnd);
			break;
		case ChooseMedium:
			initGame(10, 10, hwnd);
			break;
		case ChooseHard:
			initGame(15, 15, hwnd);
			break;
		case Exit:
			result = MessageBox(hwnd, L"Are you sure you want to exit the game?", L"Exit", MB_YESNO);
			if (result == YES)
			{
				if(hasGameStarted) KillTimer(hwnd, TIMER1);
				PostQuitMessage(0);
			}
			break;
		}
		break;
	case WM_TIMER:
		switch (wparam)
		{
		case TIMER1:
			if (hasGameStarted && !hasGameEnded)
			{
				duration = (clock() - clockStart) / CLOCKS_PER_SEC;
				SetWindowText(Time, std::to_wstring(duration + 1).c_str());
			}
			break;
		}
		break;
	case WM_CREATE:
		AddMainWindowMenu(hwnd);
		AddMainWindowWidgets(hwnd);
		ShowMainMenuWidgets();
		
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (hasGameStarted)
		{

			for (int i = 0; i < mapHeight; i++)
			{
				for (int j = 0; j < mapWidth; j++)
				{
					short cell = gamemap.getCell(i, j);

					short minescount = 0;
					std::wstring wstrMinescount;

					if (!hasGameEnded)
					{
						switch (cell)
						{
						case mswa::Map::UNCOVERED:
							minescount = gamemap.getMinesCount(i, j);
							if (!minescount)
							{
								drawImage(L"C:\\Users\\rost1\\source\\repos\\MinesweeperWA\\images\\uncovered.jpg", hdc, j * 32 + (WIDTH - mapWidth * 32) / 2, i * 32);
							}
							else
							{
								wstrMinescount = L"C:\\Users\\rost1\\source\\repos\\MinesweeperWA\\images\\" + std::to_wstring(minescount) + L".jpg";
								drawImage(wstrMinescount.c_str(), hdc, j * 32 + (WIDTH - mapWidth * 32) / 2, i * 32);
							}
							break;
						case mswa::Map::FLAGGED:
							drawImage(L"C:\\Users\\rost1\\source\\repos\\MinesweeperWA\\images\\flag.jpg", hdc, j * 32 + (WIDTH - mapWidth * 32) / 2, i * 32);
							break;
						case mswa::Map::FLAGGED_MINE:
							drawImage(L"C:\\Users\\rost1\\source\\repos\\MinesweeperWA\\images\\flag.jpg", hdc, j * 32 + (WIDTH - mapWidth * 32) / 2, i * 32);
							break;
						default:
							drawImage(L"C:\\Users\\rost1\\source\\repos\\MinesweeperWA\\images\\covered.jpg", hdc, j * 32 + (WIDTH - mapWidth * 32) / 2, i * 32);
						};
					}
					else
					{
						if(cell == mswa::Map::MINE || cell == mswa::Map::FLAGGED_MINE)
							drawImage(L"C:\\Users\\rost1\\source\\repos\\MinesweeperWA\\images\\mine.jpg", hdc, j * 32 + (WIDTH - mapWidth * 32) / 2, i * 32);
						else
						{
							minescount = gamemap.getMinesCount(i, j);
							if (!minescount)
							{
								drawImage(L"C:\\Users\\rost1\\source\\repos\\MinesweeperWA\\images\\uncovered.jpg", hdc, j * 32 + (WIDTH - mapWidth * 32) / 2, i * 32);
							}
							else
							{
								wstrMinescount = L"C:\\Users\\rost1\\source\\repos\\MinesweeperWA\\images\\" + std::to_wstring(minescount) + L".jpg";
								drawImage(wstrMinescount.c_str(), hdc, j * 32 + (WIDTH - mapWidth * 32) / 2, i * 32);
							}
						}
					}
				}
			}
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONUP:
		if (hasGameStarted && !hasGameEnded)
		{
			GetCursorPos(&p);
			if (ScreenToClient(hwnd, &p))
			{

				if (!firstMoveDone && p.x >= (WIDTH - mapWidth * 32) / 2 && p.x <= (WIDTH + mapWidth * 32) / 2 && p.y <= 32 * mapHeight)
				{
					firstMoveDone = true;
					gamemap.initMines(p.x - (WIDTH - mapWidth * 32) / 2, p.y);
				}

				if (!gamemap.action(p.x - (WIDTH - mapWidth * 32) / 2, p.y))
				{
					result = MessageBox(hwnd, L"You lost! Try again?", L"Game lost", MB_ICONEXCLAMATION | MB_YESNO);
					if(result == NO)
						hasGameEnded = true;
					else
					{
						gamemap.reinit();
						firstMoveDone = false;
					}
				}

				if (gamemap.checkWinCondition())
				{
					result = MessageBox(hwnd, L"You won! Play again?", L"Game won", MB_ICONEXCLAMATION | MB_YESNO);
					if (result == NO)
						hasGameEnded = true;
					else
					{
						gamemap.reinit();
						firstMoveDone = false;
					}
				}

				InvalidateRect(hwnd, NULL, FALSE);

			}
		}
		break;
	case WM_RBUTTONUP:
		if (!firstMoveDone || hasGameEnded) break;
		GetCursorPos(&p);
		if (ScreenToClient(hwnd, &p))
		{

			gamemap.action(p.x - (WIDTH - mapWidth * 32) / 2, p.y, true);
			if (firstMoveDone)
				SetWindowText(Flags, std::to_wstring(gamemap.getFlagsCount()).c_str());

		}

		InvalidateRect(hwnd, NULL, FALSE);

		break;
	case WM_DESTROY:
		if (hasGameStarted) KillTimer(hwnd, TIMER1);
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

	Easy = CreateWindowA("button", "Easy", WS_CHILD, WIDTH * 3 / 8, HEIGHT / 4, WIDTH / 4, HEIGHT / 8, hwnd, (HMENU)ChooseEasy, NULL, NULL);
	Medium = CreateWindowA("button", "Medium", WS_CHILD, WIDTH * 3 / 8, 3 * HEIGHT / 8, WIDTH / 4, HEIGHT / 8, hwnd, (HMENU)ChooseMedium, NULL, NULL);
	Hard = CreateWindowA("button", "Hard", WS_CHILD, WIDTH * 3 / 8, HEIGHT / 2, WIDTH / 4, HEIGHT / 8, hwnd, (HMENU)ChooseHard, NULL, NULL);

	BackButton = CreateWindowA("button", "Back", WS_CHILD, WIDTH * 3 / 8, 3 * HEIGHT / 4, WIDTH / 4, HEIGHT / 8, hwnd, (HMENU)Back, NULL, NULL);

	Time = CreateWindowA("static", "", WS_CHILD, 0, 0, 40, 25, hwnd, NULL, NULL, NULL);
	Flags = CreateWindowA("static", "", WS_CHILD, 595, 0, 40, 25, hwnd, NULL, NULL, NULL);

	forTests = CreateWindowA("static", "", WS_CHILD, 0, 0, 300, 300, hwnd, NULL, NULL, NULL);

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

void ShowDifficultiesWidgets()
{
	ShowWindow(Easy, SW_SHOW);
	ShowWindow(Medium, SW_SHOW);
	ShowWindow(Hard, SW_SHOW);
	ShowWindow(BackButton, SW_SHOW);
}

void HideDifficultiesWidgets()
{
	ShowWindow(Easy, SW_HIDE);
	ShowWindow(Medium, SW_HIDE);
	ShowWindow(Hard, SW_HIDE);
	ShowWindow(BackButton, SW_HIDE);
}

void drawImage(LPCWSTR filepath, HDC hdc, INT x, INT y)
{

	Gdiplus::Graphics graphics(hdc);
	
	Gdiplus::Bitmap img(filepath);
	graphics.DrawImage(&img, x, y);

}

void initGame(short width, short height, HWND hwnd)
{
	gamemap = mswa::Map(width, height);
	HideDifficultiesWidgets();
	InvalidateRect(hwnd, NULL, FALSE);
	hasGameStarted = true;
	SetWindowPos(ExitGame, NULL, WIDTH * 3 / 8, 3 * HEIGHT / 4, NULL, NULL, SWP_NOSIZE);
	ShowWindow(ExitGame, SW_SHOW);
	ShowWindow(Time, SW_SHOW);
	ShowWindow(Flags, SW_SHOW);
	clockStart = clock();
	nTimerID = SetTimer(hwnd, TIMER1, 1000, NULL);
}
