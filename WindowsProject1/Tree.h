#pragma once
#include "WorldObject.h"
#include <Windows.h>

class Tree:public WorldObject
{
public:
	Tree();
	void Render(HDC hdc, int Tilesize) override;
	void SetTilePosition(int px, int py) override;
	ObjectType GetObjectType() const override;
 private:
	 int x;
	int y;
	HBITMAP bmp;
};

