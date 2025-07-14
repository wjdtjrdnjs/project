#pragma once
#include "resource.h"
#include <windows.h>
#include "PlaceableObject.h"
#include "CropType.h"

class Fence :public PlaceableObject{
public:
	Fence();
	~Fence();

	int GetX() const { return x; }  //작물 위치 x
	int GetY() const { return y; }  //작물 위치 y

	void Install(int x, int y, Player* player) override;
	void Remove(int tileX, int tileY, Player* player) override;
	void SetPosition(int x, int y) { this->x = x; this->y = y; }
	void Render(HDC hdc);
	void Update();
private:
	int image = IDB_BITMAP39;
	int x;
	int y;
	int Fencesize = 10;
	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;
};

