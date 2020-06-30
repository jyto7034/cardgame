#pragma once
#include "GameSystem.h"
#include "GeneralFunctions.h"

HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& g_hWnd, HINSTANCE& g_hInst) {
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDC_ICON);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("MyApp");
	RegisterClass(&wc);
	g_hInst = hInstance;
	g_hWnd = CreateWindow(TEXT("MyApp"), TEXT("Hi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT
		, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, SW_SHOW);
	return S_OK;
}

void UpdateFPS(HDC& hdc)
{

	static DWORD frameCount = 0;            //프레임 카운트수
	static float timeElapsed = 0.0f;            //흐른 시간
	static DWORD lastTime = timeGetTime();   //마지막 시간(temp변수)

	DWORD curTime = timeGetTime();      //현재 시간
	float timeDelta = (curTime - lastTime) * 0.001f;        //timeDelta(1번생성후 흐른 시간) 1초단위로 바꿔준다.

	timeElapsed += timeDelta;

	frameCount++;

	wchar_t sfps[256];
	if (timeElapsed >= 0.1f)         //흐른시간이 1초이상이면 내가 하고싶은것 처리
	{
		float fps = (float)frameCount / timeElapsed;
		swprintf_s(sfps, TEXT("%f"), fps);     //FPS출력 하는 소스
		TextOut(hdc, 10, 14, sfps, lstrlen(sfps));
		frameCount = 0;
		timeElapsed = 0.0f;
	}
	else
	{
		//흐른 시간이 1초가 안되면 생략함  
		//Sleep() 해도되고 안해도 되구~ 
	}


	lastTime = curTime;
}