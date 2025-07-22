#pragma once
#include <vector>
#include <map>
#include <windows.h>
#include <algorithm>
#include "resource.h"
#include "CollisionManager.h"
#include "Direction.h"

class InventoryComponent;
class Player : public CollisionManager
{
public:
	Player(InventoryComponent* inventoryComponent);
	~Player();
	void LoadSprites();
	// �÷��̾� ��ǥ
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetPlusX(int dx, int dy)  { x += dx, y += dy;}
	void SetMinusY(int dx, int dy) { x -= dx, y -= dy; }
	RECT GetBoundingBox() const;

	void Render(HDC hdc);	// �÷��̾� ������

	void SetDirection(Direction dir) { currentDir = dir; }
	Direction  GetDirection() const { return currentDir; }

	std::vector<RECT> GetCollisionRects() const override;

	//�÷��̾� �κ��丮 ����
	InventoryComponent* GetInventory() { return inventory; }


private:
	int x = 39;
	int y = 250;
	int playerSize = 35;
	Direction currentDir = DOWN; // �ʱ� ������ �Ʒ�

	std::map<Direction, std::vector<HBITMAP>> playerSprites; // �÷��̾� ���⺰ �̹���
	InventoryComponent* inventory = nullptr;
	

	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
	HDC memDC = nullptr;
	void ReleaseResources();  // �ʿ� �� ����
};
