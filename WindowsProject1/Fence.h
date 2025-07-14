#pragma once
#include "resource.h"
#include <windows.h>

class Fence
{
public:
	Fence();
	~Fence();
	int GetX() const { return x; }
	int GetY() const { return y; }
	void Render(HDC hdc);
	void Update();
private:
	int image = IDB_BITMAP39;
	int x = 265;
	int y = 165;
	int Fencesize = 10;
	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;
};

