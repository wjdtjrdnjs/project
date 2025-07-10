#pragma once
#include "resource.h"
#include <windows.h>

class Animal
{
public:
	Animal();
	~Animal();
	int GetX() const { return x; }
	int GetY() const { return y; }
	void Render(HDC hdc);
	void Update();
private:
	int image = IDB_BITMAP19;
	int x = 350;
	int y = 300;
	int Animalsize = 8;
	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;
};

