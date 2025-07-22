#pragma once
#include "resource.h"
#include <windows.h>
#include "CropType.h"
#include "CollisionManager.h"
#include "PlaceableObject.h"
class PlayerController;
class Fence :public PlaceableObject, public CollisionManager{
public:
	Fence();
	~Fence();

	int GetX() const { return x; }  //��Ÿ�� ��ġ x
	int GetY() const { return y; }  //��Ÿ�� ��ġ y
	RECT GetBoundingBox() const;
	std::vector<RECT>GetCollisionRects()const override;

	//PlaceableObject.h
	void Install(int x, int y, InventoryComponent& inventory) override; //��ġ 
	void Remove(int tileX, int tileY, InventoryComponent& inventory) override; //����

	void SetPosition(int x, int y) { this->x = x; this->y = y; }
	void Render(HDC hdc);
private:
	PlayerController* playercon = nullptr;
	int x, y;
	int Fencesize = 10;
	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
};

