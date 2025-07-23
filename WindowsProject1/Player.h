#pragma once
#include <vector>
#include <map>
#include <windows.h>
#include <algorithm>
#include "resource.h"
#include "CollisionManager.h"
#include "Direction.h"
#include "GameObject.h"
#include "ToolType.h" 

class InventoryComponent;
class Player : public CollisionManager, public GameObject
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
	int GetResourceId(Tool toolType, Direction dir);
	void Render(HDC hdc);	// �÷��̾� ������

	void SetDirection(Direction dir) { currentDir = dir; }
	Direction  GetDirection() const { return currentDir; }

	std::vector<RECT> GetCollisionRects() const override;

	//�÷��̾� �κ��丮 ����
	InventoryComponent* GetInventory() { return inventory; }

	void SetEquippedTool(Tool t) { equippedTool = t; }
	Tool GetEquippedTool() const {return equippedTool;}

	void StartAction();
private:
	int x = 39;
	int y = 250;
	int playerSize = 35;
	Direction currentDir = Direction::DOWN; // �ʱ� ������ �Ʒ�
	WateringCan_Action canAction = WateringCan_Action::DOWN;

	InventoryComponent* inventory = nullptr;
	Tool equippedTool = Tool::None;

	std::map<Tool, std::map<Direction, std::vector<HBITMAP>>> playerSprites;

	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
	HDC memDC = nullptr;

	
	void ReleaseResources();  // �ʿ� �� ����
};
