#pragma once
#include "headers.h"
#include "AbstractObject.h"

template<typename T>
class EventHandler {
private:
	using pFn = void(T::*)();
	using Handlers = std::map<T*, pFn>;
	Handlers _Handlers;
public:
	void Add(T* obj, pFn pFn) { _Handlers.insert(std::make_pair(obj, pFn)); }
	void Remove(T* obj) {
		typename Handlers::iterator it = _Handlers.find(obj);
		if (it != _Handlers.end())
			_Handlers.erase(it);
	}
	void Call() {
		if (_Handlers.size() != 0) {
			std::cout << _Handlers.size() << std::endl;
			typename Handlers::iterator it = _Handlers.begin();
			while (it != _Handlers.end()) {
				((it->first)->*(it->second))();
				++it;
			}
		}
	}
};

class Game {
public:
	HWND& m_hWnd;
	HBITMAP hBitmap;

	Game(HWND& _hWnd) :m_hWnd(_hWnd), hBitmap(NULL) 
	{
		std::cout << "Construction." << std::endl;
	}

	~Game() 
	{
		std::cout << "Destruction." << std::endl;
	}

	void Update(HDC& _hdc);
	void Render();

};


struct CardData {
	int id, szCardX, szCardY;
	char icon;
	CardData(int _id, char _icon, int szx, int szy) : id(_id), icon(_icon), szCardX(szx), szCardY(szy) {}
	CardData() : id(-1), icon(NULL), szCardX(-1), szCardY(-1) {}
};


class Button : public AbstractObject{
public:

};

class Window : public AbstractObject {
public:

};

class Card : public AbstractObject {
private:
	CardData data;
public:
	void DrawCard(HDC& hdc);
	Card(CardData, Vector, RENDER_PRIORITY);
};

class Text : public AbstractObject {
public:

};


class ObjectTable {
public:
	std::vector<Card*> m_vCardObject;
	std::vector<Window*> m_vWindowObject;
	std::vector<Text*> m_vTextObject;
	std::vector<Button*> m_vButtonObject;

	void Add(AbstractObject* obj);

	ObjectTable() : m_vButtonObject(0), m_vCardObject(0), m_vTextObject(0), m_vWindowObject(0) {}
};