#pragma once
#include "GameSystem.h"
#include "GeneralFunctions.h"
#include "Externs.h"

void Vector::Forward(Vector* obj, Vector dstv, int speed) {
	obj->dx = dstv.x;
	obj->dy = dstv.y;
	obj->speed = speed;
	eventHandler.Add(obj, &Vector::_Forward);
}

void Vector::_Forward() {
	//if (dx <= x && dy <= y)
	//	eventHandler.Remove(this);
	if (dx >= x) {
		x += speed / 2;
	}
	if (dy >= y) {
		y += speed / 2;
	}
	//showData();
	//std::cout << dx << " : " << dy << std::endl;
}

void ObjectTable::Add(AbstractObject* obj) {
	char type = typeid(*obj).name()[6];
	switch (type)
	{
	// Button Class 
	case 'B':
	{

	}

	// Window Class
	case 'W':
	{

	}

	// Card Class
	case 'C':
	{
		std::cout << "C";
		this->m_vCardObject.push_back((Card*)obj);
	}

	// Text Class
	case 'T':
	{

	}
	default:
		break;
	}
}


Card::Card(CardData _data, Vector v, RENDER_PRIORITY _priority) {
	this->data = _data;
	this->position = v;
	this->priority = _priority;
	g_objectTable.Add(this);
}

void Card::DrawCard(HDC& hdc) {
	Vector p1 = this->position - Vector(this->data.szCardX, this->data.szCardY);
	Vector p2 = this->position + Vector(this->data.szCardX, this->data.szCardY);
	Rectangle(hdc, p1.x, p1.y, p2.x, p2.y);
}

void Game::Update(HDC& _hdc) {
	auto vCards = g_objectTable.m_vCardObject;
	int size = vCards.size();

	eventHandler.Call();

	for (int i = 0; i < size; i++) {
		vCards[i]->DrawCard(_hdc);
	}
	
}

static DWORD dwNextTick = 0;

void Game::Render() {
	HBRUSH hBrush, hOldBrush;
	HDC hdc, hMemDC;
	HBITMAP OldBit;
	RECT crt;
	
	hdc = GetDC(m_hWnd);
	GetClientRect(m_hWnd, &crt); 

	if (hBitmap == NULL)
		hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	
	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBitmap);
	FillRect(hMemDC, &crt, reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
	SelectObject(hMemDC, GetStockObject(NULL_PEN));

	// TODO
	Update(hMemDC);
	UpdateFPS(hMemDC);

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(m_hWnd, hdc);
	InvalidateRect(m_hWnd, NULL, FALSE);

	DWORD dwInterval = 1000 / 60;
	if (dwNextTick >= GetTickCount64())
		Sleep(dwNextTick - GetTickCount64());
	dwNextTick = GetTickCount64() + dwInterval;
}
