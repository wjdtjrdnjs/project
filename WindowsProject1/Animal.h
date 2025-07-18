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
	RECT GetBoundingBox();
	RECT GetDoorBoundingBox();
	void Update();
private:
	int image = IDB_BITMAP38;
	int x = 39;
	int y = 150;
	int Animalsize = 37;
	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;
};

