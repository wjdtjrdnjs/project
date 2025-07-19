#pragma once
#include "resource.h"
#include <windows.h>

class House
{
public:
	House();
	~House();
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
	int Housesize = 37;
	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
	HDC memDC = nullptr;
};

