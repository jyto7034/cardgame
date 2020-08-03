#pragma once
#include "headers.h"
#include "AbstractObject.h"

template<typename T>
class EventHandler {
private:
	using pFn = void(T::*)();
	using Handlers = std::map<T*, pFn>;
	using pTvector = std::vector<T*>;
	pTvector Objects_Requiring_Delection;
	Handlers _Handlers;

	void _Remove() {
		typename pTvector::iterator it = Objects_Requiring_Delection.begin();
		typename Handlers::iterator hit = _Handlers.find(*it);
		while (hit != _Handlers.end())
		{
			_Handlers.erase(hit);
			if (++it != Objects_Requiring_Delection.end())
				hit = _Handlers.find(*it);
			else
				hit = _Handlers.end();
		}
		Objects_Requiring_Delection.clear();
	}

public:
	void Add(T* obj, pFn pFn) {
		_Handlers.insert(std::make_pair(obj, pFn));
	}

	void Remove(T* obj)
	{
		this->Objects_Requiring_Delection.push_back(obj);
	}

	void Remove_immediately(T* obj) {
		typename Handlers::iterator it = _Handlers.find(obj);
		if (it != _Handlers.end())
			_Handlers.erase(it);
	}

	void Call() {
		if (_Handlers.size() != 0) {
			typename Handlers::iterator it = _Handlers.begin();
			while (it != _Handlers.end()) {
				((it->first)->*(it->second))();
				it++;
			}
			if(Objects_Requiring_Delection.size() > 0)
				this->_Remove();
		}
	}
};

class Game {
public:
	HWND& m_hWnd;
	HBITMAP hBitmap;

	Game(HWND& _hWnd) :m_hWnd(_hWnd), hBitmap(NULL) {}

	void Update(HDC& _hdc);
	void Render();

};


struct CardData {
	int id, szCardX, szCardY;
	CARD_COLOR Color;
	char icon[3];
	CardData(int _id, const char* _icon, CARD_COLOR color, int szx, int szy) : id(_id), szCardX(szx), szCardY(szy), Color(color)/*, icon(_icon)*/ { strcpy(icon, _icon); }
	CardData() : id(-1), szCardX(-1), szCardY(-1), Color(CARD_COLOR::COLOR_NULL)  { icon[0] = '\0'; }
};


class Button : public AbstractObject{
public:

};

class Window : public AbstractObject {
public:

};

class Card : public AbstractObject {
public:
	CardData data;
	void DrawCard(HDC&);
	Card(CardData, Vector, RENDER_PRIORITY);
};

class Text : public AbstractObject {
public:

};


class ObjectTable {
private:
	int AllobjectCount;
public:
	std::vector<Card*> m_vCardObject;
	std::vector<Window*> m_vWindowObject;
	std::vector<Text*> m_vTextObject;
	std::vector<Button*> m_vButtonObject;
	
	int GetAllObjectCount() { return AllobjectCount; }

	void Add(AbstractObject* obj);

	ObjectTable() : m_vButtonObject(0), m_vCardObject(0), m_vTextObject(0), m_vWindowObject(0), AllobjectCount(0) {}
};