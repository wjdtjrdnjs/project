#pragma once
#include "resource.h"
#include <windows.h>
#include "CropType.h"
#include "CollisionManager.h"
#include "PlaceableObject.h"

class Fence :public PlaceableObject, public CollisionManager{
public:
	Fence();
	~Fence();

	int GetX() const { return x; }  //��Ÿ�� ��ġ x
	int GetY() const { return y; }  //��Ÿ�� ��ġ y
	RECT GetBoundingBox() const;
	std::vector<RECT>GetCollisionRects()const override;

	//PlaceableObject.h
	void Install(int x, int y, Player* player) override; //��ġ 
	void Remove(int tileX, int tileY, Player* player) override; //����

	void SetPosition(int x, int y) { this->x = x; this->y = y; }
	void Render(HDC hdc);
private:
	int x, y;
	int Fencesize = 10;
	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
};

