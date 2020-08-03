#pragma once
#include "GameSystem.h"
#include "GeneralFunctions.h"
#include "Externs.h"
#include "Enum.h"

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


void Vector::Lerp(Vector* obj, Vector dstv, float t)
{
	obj->dx = dstv.x;
	obj->dy = dstv.y;
	obj->t = t;
	obj->calculated_vector = Calc_linear_interpolation(*obj);

	eventHandler.Add(obj, &Vector::_Lerp);
}


void Vector::_Lerp() {
	int _y, _x;
	try {
		_y = this->calculated_vector->find("y")->second.PeekObject();
		_x = this->calculated_vector->find("x")->second.PeekObject();
	}
	catch (...) {
		abort();
	}

	if (_x != -1)
		this->x = _x;
	if (_y != -1)
		this->y = _y;
	if (_x == -1 && _y == -1)
	{
		eventHandler.Remove(this);
		delete this->calculated_vector;
	}
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
		//std::cout << "C";
		this->m_vCardObject.push_back((Card*)obj);
	}

	// Text Class
	case 'T':
	{

	}
	default:
		break;
	}

	this->AllobjectCount++;
}


Card::Card(CardData _data, Vector v, RENDER_PRIORITY _priority) {
	this->data = _data;
	this->position = v;
	this->priority = _priority;
	this->ObjectID = g_objectTable.GetAllObjectCount();
	g_objectTable.Add(this);
}


void Card::DrawCard(HDC& hdc) {
	HBRUSH b, ob;
	HPEN MyPen, OldPen;
	b = CreateSolidBrush(RGB(0, 0, 0));
	MyPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	ob = (HBRUSH)SelectObject(hdc, b);
	OldPen = (HPEN)SelectObject(hdc, MyPen);

	//Vector p1 = this->position - Vector(this->data.szCardX, this->data.szCardY);
	//Vector p2 = this->position + Vector(this->data.szCardX, this->data.szCardY);

	Vector p1 = Vector(this->position.x - this->data.szCardX  * 10, this->position.y - this->data.szCardY * 10);
	Vector p2 = Vector(this->position.x + this->data.szCardX * 10, this->position.y + this->data.szCardY * 10);

	//std::cout << "Card :" << p1.x << ", " << p1.y << std::endl << "Card :" << p2.x << ", " << p2.y << std::endl;
	Vector text = p1;
	Rectangle(hdc, p1.x, p1.y, p2.x, p2.y);

	p1 = Vector(this->position.x + (this->data.szCardX - 1) * 10, this->position.y + this->data.szCardY * 14);
	p2 = Vector(this->position.x + (this->data.szCardX - 4) * 10, this->position.y + (this->data.szCardY - 3) * 14);

	//p1 = this->position - Vector(this->data.szCardX - 1, this->data.szCardY);
	//p2 = this->position + Vector(this->data.szCardX - 4, this->data.szCardY - 3);
	HFONT of, hf;
	hf = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, L"³ª´®°íµñ");
	SetBkMode(hdc, TRANSPARENT);
	of = (HFONT)SelectObject(hdc, hf);
	SetTextColor(hdc, RGB(255, 255, 255));

	if (this->data.Color == CARD_COLOR::BLACK)
		SetTextColor(hdc, RGB(0, 0, 0));
	else
		SetTextColor(hdc, RGB(255, 0, 0));
	
	const int _TRUE = 0;
	 
	wchar_t wid = 0; 

	// If It's string
	if (this->data.id > 11)
	{
		char t = (char)this->data.id;
		mbstowcs(&wid, &t, 1);
	}
	// or It's int
	else if (this->data.id < 11)
	{
		std::cout << "int" << std::endl;
		swprintf(&wid, L"%d", this->data.id);
	}

	if (strcmp(this->data.icon, "¡ß") == _TRUE)
	{
		TextOut(hdc, p1.x - 100, p1.y - 230, L"¡ß", 1);
		TextOut(hdc, p2.x + 6, p2.y - 40, L"¡ß", 1);
	}
	else if (strcmp(this->data.icon, "¢À") == _TRUE)
	{
		TextOut(hdc, p1.x - 100, p1.y - 230, L"¢À", 1);
		TextOut(hdc, p2.x + 6, p2.y - 40, L"¢À", 1);
	}
	else if (strcmp(this->data.icon, "¢¾") == _TRUE)
	{
		TextOut(hdc, p1.x - 100, p1.y - 230, L"¢¾", 1);
		TextOut(hdc, p2.x + 6, p2.y - 40, L"¢¾", 1);
	}
	else if (strcmp(this->data.icon, "¢¼") == _TRUE)
	{
		TextOut(hdc, p1.x - 100, p1.y - 230, L"¢¼", 1);
		TextOut(hdc, p2.x + 6, p2.y - 40, L"¢¼", 1);
	}
	TextOut(hdc, text.x + 50, text.y + 80, &wid, 1);

	SelectObject(hdc, of);
	DeleteObject(hf);
	SelectObject(hdc, OldPen);
	DeleteObject(MyPen);
	SelectObject(hdc, ob);
	DeleteObject(b);
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
