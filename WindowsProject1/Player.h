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
	// 플레이어 좌표
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetPlusX(int dx, int dy)  { x += dx, y += dy;}
	void SetMinusY(int dx, int dy) { x -= dx, y -= dy; }
	RECT GetBoundingBox() const;

	void Render(HDC hdc);	// 플레이어 렌더링

	void SetDirection(Direction dir) { currentDir = dir; }
	Direction  GetDirection() const { return currentDir; }

	std::vector<RECT> GetCollisionRects() const override;

	//플레이어 인벤토리 전달
	InventoryComponent* GetInventory() { return inventory; }


private:
	int x = 39;
	int y = 250;
	int playerSize = 35;
	Direction currentDir = DOWN; // 초기 방향은 아래

	std::map<Direction, std::vector<HBITMAP>> playerSprites; // 플레이어 방향별 이미지
	InventoryComponent* inventory = nullptr;
	

	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;
	void ReleaseResources();  // 필요 시 구현
};
