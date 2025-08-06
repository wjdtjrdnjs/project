#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include "TileData.h"
class WorldObject
{
public:
	virtual void Render(HDC hdc, int Tilesize) = 0;
	virtual void SetTilePosition(int tileX, int tileY) = 0;  // ���� �� ���� ���� �Լ� (���� ����) 
	virtual std::vector<RECT> GetCollisionRects() const { return {}; }  // �⺻�� �浹 ����
	virtual void Update(float deltaTime) {}
	virtual RECT GetCollisionRect() { return RECT{ 0, 0, 0, 0 }; }


	virtual bool IsCollidable() const { return false; }
	//virtual void Interact(Player& player) {}		

	virtual PlaceableType GetPlaceableType() const = 0;
	
	virtual ~WorldObject() = default;
	void SetPosition(int x, int y) { tileX = x, tileY = y; }
	std::string name;
protected:
	int tileX = 0, tileY = 0;
};

