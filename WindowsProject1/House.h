#pragma once
#include "resource.h"
#include "CollisionManager.h"
#include "WorldObject.h"
#include <windows.h>
#include <vector>
#include "GameObject.h"

class House: public WorldObject
{
public:
	House();
	~House();
	int GetX() const { return x; }
	int GetY() const { return y; }

	void Render(HDC hdc, int tilesize) override;
	void SetTilePosition(int tileX, int tileY) override;
	ObjectType GetObjectType() const override;
	RECT GetCollisionRect();

	//std::vector<RECT>GetCollisionRects()const override;
	//RECT GetBoundingBox() const;
	//RECT GetDoorBoundingBox()const;
	void Update();
private:
	int x = 39;
	int y = 150;
	int Housesize = 37;
	HBITMAP bmp;
	HDC memDC = nullptr;
};

