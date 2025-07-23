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
	// 플레이어 좌표
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetPlusX(int dx, int dy)  { x += dx, y += dy;}
	void SetMinusY(int dx, int dy) { x -= dx, y -= dy; }
	RECT GetBoundingBox() const;
	int GetResourceId(Tool toolType, Direction dir);
	void Render(HDC hdc);	// 플레이어 렌더링

	void SetDirection(Direction dir) { currentDir = dir; }
	Direction  GetDirection() const { return currentDir; }

	std::vector<RECT> GetCollisionRects() const override;

	//플레이어 인벤토리 전달
	InventoryComponent* GetInventory() { return inventory; }

	void SetEquippedTool(Tool t) { equippedTool = t; }
	Tool GetEquippedTool() const {return equippedTool;}

	void StartAction();
private:
	int x = 39;
	int y = 250;
	int playerSize = 35;
	Direction currentDir = Direction::DOWN; // 초기 방향은 아래
	WateringCan_Action canAction = WateringCan_Action::DOWN;

	InventoryComponent* inventory = nullptr;
	Tool equippedTool = Tool::None;

	std::map<Tool, std::map<Direction, std::vector<HBITMAP>>> playerSprites;

	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;

	
	void ReleaseResources();  // 필요 시 구현
};
