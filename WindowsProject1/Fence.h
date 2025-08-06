#pragma once
#include <windows.h>
#include "WorldObject.h"

class Fence :public WorldObject
{
public:
	Fence();
	void SetTilePosition(int tileX, int tileY) override;
	void Render(HDC hdc, int tilesize) override;
	PlaceableType GetPlaceableType()const override;
	RECT GetCollisionRect();
	//int GetX() const { return x; }  //울타리 위치 x
	//int GetY() const { return y; }  //울타리 위치 y
	//RECT GetBoundingBox() const;
	//std::vector<RECT>GetCollisionRects()const override;

	////PlaceableObject.h
	//void Install(int x, int y, InventoryComponent& inventory) override; //설치 
	//void Remove(int tileX, int tileY, InventoryComponent& inventory) override; //삭제

	

private:
	int x, y;
	int Fencesize = 10;
	HBITMAP hBmp; // 비트맵 핸들 저장용
};

