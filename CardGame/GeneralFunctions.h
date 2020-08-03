#pragma once
#include "headers.h"
#include "GameSystem.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& g_hWnd, HINSTANCE& g_hInst);
std::map<const char*, CVector>* Calc_linear_interpolation(Vector&);
void linear_interpolation(float obj, float dstv, float t, std::vector<float>* v);
std::optional<Card*> Did_User_Click_The_Card(POINT, ObjectTable&);
void MigrationVector(std::vector<float>&, int);
void UpdateFPS(HDC&);