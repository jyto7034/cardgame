#pragma once
#include "GameSystem.h"
#include "GeneralFunctions.h"
#include "Vector.h"

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

	static DWORD frameCount = 0;            
	static float timeElapsed = 0.0f;        
	static DWORD lastTime = timeGetTime();   

	DWORD curTime = timeGetTime(); 
	float timeDelta = (curTime - lastTime) * 0.001f;       

	timeElapsed += timeDelta;

	frameCount++;

	wchar_t sfps[256];
	if (timeElapsed >= 0.1f)      
	{
		float fps = (float)frameCount / timeElapsed;
		swprintf_s(sfps, TEXT("%f"), fps); 
		TextOut(hdc, 10, 14, sfps, lstrlen(sfps));
		frameCount = 0;
		timeElapsed = 0.0f;
	}
	lastTime = curTime;
}


void MigrationVector(std::vector<float>& v, int p) {
	for (int i = 0; i < v.size(); i++)
		v[i] = p - (int)v[i];
}


std::map<const char*, CVector>* Calc_linear_interpolation(Vector &obj) {
	Vector* temp = NULL;
	int x = obj.x;
	int dx = obj.dx;

	int y = obj.y;
	int dy = obj.dy;

	OPPOSITE_TYPE type;

	//if( dx < x ) == 10 -> 0
	//if( x < dx ) == 0 -> 10

	// When both are the opposite
	if (dx < x && dy < y)
	{
		temp = new Vector(obj.dx, obj.dy, obj.x, obj.y);
		type = OPPOSITE_TYPE::OPPOSITE_BOTH;
	}

	// When x is opposite
	else if (dx < x && (y < dy || y == dy))
	{
		temp = new Vector(obj.dx, obj.y, obj.x, obj.dy);
		type = OPPOSITE_TYPE::OPPOSITE_X;
	}

	// When y is opposite
	else if ((x < dx || x == dx) && dy < y) 
	{
		temp = new Vector(obj.x, obj.dy, obj.dx, obj.y);
		type = OPPOSITE_TYPE::OPPOSITE_Y;
	}

	// When both are not the opposite
	else
	{
		temp = new Vector(obj.x, obj.y, obj.dx, obj.dy);
		type = OPPOSITE_TYPE::NO_OPPOSITE;
	}

	std::vector<float> xv;
	std::vector<float> yv;
	linear_interpolation(temp->x, temp->dx, obj.t, &xv);
	linear_interpolation(temp->y, temp->dy, obj.t, &yv);

	switch (type)
	{
	case OPPOSITE_TYPE::OPPOSITE_BOTH:
		MigrationVector(xv, obj.x);
		MigrationVector(yv, obj.y);
		break;
	case OPPOSITE_TYPE::OPPOSITE_X:
		MigrationVector(xv, obj.x);
		break;
	case OPPOSITE_TYPE::OPPOSITE_Y:
		MigrationVector(yv, obj.y);
		break;
	case OPPOSITE_TYPE::NO_OPPOSITE:
		break;
	}


	CVector cxv(xv);
	CVector cyv(yv);

	std::map<const char*, CVector>* rv = new std::map<const char*, CVector>;
	rv->insert(std::make_pair("x", cxv));
	rv->insert(std::make_pair("y", cyv));

	delete temp;

	return rv;
}

void linear_interpolation(float obj, float dstv, float t, std::vector<float> *v)
{
	if (obj >= dstv - 0.1f)
	{
		v->push_back(dstv);
		return;
	}
	float tt = (1 - t) * obj + t * dstv;
	//std::cout << tt << ", " << dstv << std::endl;
	v->push_back(tt);
	linear_interpolation(tt, dstv, t, v);
}

std::optional<Card*> Did_User_Click_The_Card(POINT p, ObjectTable& table) {
	for (const auto& item : table.m_vCardObject)
	{
		int x1 = item->position.x - item->data.szCardX * 10;
		int x2 = item->position.x + item->data.szCardX * 10;

		int y1 = item->position.y - item->data.szCardY * 10;
		int y2 = item->position.y + item->data.szCardY * 10;

		//std::cout << x1 << ", " << y1 << std::endl << x2 << ", " << y2 << std::endl;

		if (x1 < p.x && y1 < p.y &&
			x2 > p.x && y2 > p.y) {
			std::cout << "in" << std::endl;
			return item;
		}
		else
			return {};
	}
}