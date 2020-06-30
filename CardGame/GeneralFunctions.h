#pragma once
#include "headers.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& g_hWnd, HINSTANCE& g_hInst);
void UpdateFPS(HDC&);