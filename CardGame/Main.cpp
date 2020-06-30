#pragma once
#include "GameSystem.h"
#include "GeneralFunctions.h"
#include "Externs.h"

HINSTANCE g_hInst;
HWND g_hWnd = NULL;
PAINTSTRUCT ps;
ObjectTable g_objectTable;
EventHandler<Vector> eventHandler;
static Game* game;



void SwapBitmap(HDC hdc, int x, int y, HBITMAP& hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

int APIENTRY WinMain(HINSTANCE hIns, HINSTANCE PrevIns, LPSTR cmd, int cmdShow)
{
	if (FAILED(InitWindow(hIns, cmdShow, g_hWnd, g_hInst)))
		return 0;

	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, g_hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = NULL, hMemDC;
	static HANDLE hTimer;
	RECT crt;

	switch (iMsg)
	{
	case WM_CREATE:
	{
		game = new Game(g_hWnd);
		hdc = GetDC(hWnd);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, TRANSPARENT);
		AllocConsole();
		freopen("CONOUT$", "wb", stdout);
		hTimer = (HANDLE)SetTimer(hWnd, 1, 2, NULL);
		break;
	}

	case WM_TIMER:
	{
		game->Render();
	}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
		{
			Card* card = new Card(CardData(1, '¡Ú', 6, 7), Vector(15, 15), RENDER_PRIORITY::PRIORITY_HIGH);
			Vector::Forward(&card->position, Vector(100, 15), 2);
		}
		default:
			break;
		}

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		SwapBitmap(hdc, 0, 0, game->hBitmap);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		if(hdc != NULL)
			ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;
	}

	default:
		break;
	}
 	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}