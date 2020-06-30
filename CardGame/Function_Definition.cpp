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

	static DWORD frameCount = 0;            //������ ī��Ʈ��
	static float timeElapsed = 0.0f;            //�帥 �ð�
	static DWORD lastTime = timeGetTime();   //������ �ð�(temp����)

	DWORD curTime = timeGetTime();      //���� �ð�
	float timeDelta = (curTime - lastTime) * 0.001f;        //timeDelta(1�������� �帥 �ð�) 1�ʴ����� �ٲ��ش�.

	timeElapsed += timeDelta;

	frameCount++;

	wchar_t sfps[256];
	if (timeElapsed >= 0.1f)         //�帥�ð��� 1���̻��̸� ���� �ϰ������ ó��
	{
		float fps = (float)frameCount / timeElapsed;
		swprintf_s(sfps, TEXT("%f"), fps);     //FPS��� �ϴ� �ҽ�
		TextOut(hdc, 10, 14, sfps, lstrlen(sfps));
		frameCount = 0;
		timeElapsed = 0.0f;
	}
	else
	{
		//�帥 �ð��� 1�ʰ� �ȵǸ� ������  
		//Sleep() �ص��ǰ� ���ص� �Ǳ�~ 
	}


	lastTime = curTime;
}