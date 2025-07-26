#pragma once
#include <string>
#include <Windows.h>
#include "TileData.h"
class WorldObject
{
public:
	virtual void Render(HDC hdc, int Tilesize) = 0;
	virtual void SetTilePosition(int tileX, int tileY) = 0;
	virtual ObjectType GetObjectType() const = 0;
	
	virtual ~WorldObject() = default;
	void SetPosition(int x, int y) { tileX = x, tileY = y; }
	std::string name;
protected:
	int tileX = 0, tileY = 0;
};

