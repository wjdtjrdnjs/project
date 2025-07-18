#pragma once
#include "resource.h"
#include <windows.h>
#include "PlaceableObject.h"
#include "CropType.h"

class Fence :public PlaceableObject{
public:
	Fence();
	~Fence();

	int GetX() const { return x; }  //울타리 위치 x
	int GetY() const { return y; }  //울타리 위치 y
	RECT GetBoundingBox();
	//PlaceableObject.h
	void Install(int x, int y, Player* player) override; //설치 
	void Remove(int tileX, int tileY, Player* player) override; //삭제

	void SetPosition(int x, int y) { this->x = x; this->y = y; }
	void Render(HDC hdc);
private:
	int x, y;
	int Fencesize = 10;
	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
};

