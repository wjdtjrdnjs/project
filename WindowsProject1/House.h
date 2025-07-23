#pragma once
#include "resource.h"
#include "CollisionManager.h"
#include <windows.h>
#include <vector>
#include "GameObject.h"

class House:public CollisionManager, public GameObject
{
public:
	House();
	~House();
	int GetX() const { return x; }
	int GetY() const { return y; }
	void Render(HDC hdc);
	std::vector<RECT>GetCollisionRects()const override;
	RECT GetBoundingBox() const;
	RECT GetDoorBoundingBox()const;
	void Update();
private:
	int image = IDB_BITMAP38;
	int x = 39;
	int y = 150;
	int Housesize = 37;
	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
	HDC memDC = nullptr;
};

