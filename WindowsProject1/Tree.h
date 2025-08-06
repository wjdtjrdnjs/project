#pragma once
#include "WorldObject.h"
#include <Windows.h>

class Tree:public WorldObject
{
public:
	Tree();
	void Render(HDC hdc, int Tilesize) override;
	void SetTilePosition(int px, int py) override;
	PlaceableType GetPlaceableType() const override;
	RECT GetCollisionRect();
 private:
	 int x;
	int y;
	HBITMAP bmp;
};

