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
	//int GetX() const { return x; }  //��Ÿ�� ��ġ x
	//int GetY() const { return y; }  //��Ÿ�� ��ġ y
	//RECT GetBoundingBox() const;
	//std::vector<RECT>GetCollisionRects()const override;

	////PlaceableObject.h
	//void Install(int x, int y, InventoryComponent& inventory) override; //��ġ 
	//void Remove(int tileX, int tileY, InventoryComponent& inventory) override; //����

	

private:
	int x, y;
	int Fencesize = 10;
	HBITMAP hBmp; // ��Ʈ�� �ڵ� �����
};

