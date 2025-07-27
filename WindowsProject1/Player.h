#pragma once
#include <vector>
#include <map>
#include <windows.h>
#include "resource.h"
#include "Direction.h" 
class Player 
{
 public:
	Player();
	void Render(HDC hdc, int Tilesize, Direction dir);
	//void SetTilePosition(int px, int py) override;
	void SetPosition(float px, float py);
	//~Player();
	//ObjectType GetObjectType() const override;
	//void LoadSprites();
	// 플레이어 좌표 
	float GetX() const { return x; }
	float GetY() const { return y; }
	int GetTileX()const { return tileX; }
	int GetTileY()const { return tileY; }
	std::vector<RECT> GetCollisionRects() const;

	void Update(float deltaTime, bool up, bool down, bool left, bool right);
	//Player* GetPlayer() { return this; }
	//void SetPlusX(int dx, int dy)  { x += dx, y += dy;}
	//void SetMinusY(int dx, int dy) { x -= dx, y -= dy; }
	//RECT GetBoundingBox() const;
	//int GetResourceId(Tool toolType, Direction dir);
	////void Render(HDC hdc);	// 플레이어 렌더링

	//void SetDirection(Direction dir) { currentDir = dir; }
	//Direction  GetDirection() const { return currentDir; }

	//std::vector<RECT> GetCollisionRects() const override;

	////플레이어 인벤토리 전달
	//InventoryComponent* GetInventory() { return inventory; }

	//void SetEquippedTool(Tool t) { equippedTool = t; }
	//Tool GetEquippedTool() const {return equippedTool;}
	//void StartAction();
	private:
	int tileX = 0;  // 타일 위치 (정수)
	int tileY = 0;
	float pixelX = 0.f;  // 실제 픽셀 위치 (자연스러운 이동용)
	float pixelY = 0.f;
	//
	float x;
	float y;
	float speed = 5.0f;
	//
	int playerSize = 35;
	//Direction currentDir = Direction::DOWN; // 초기 방향은 아래
	//WateringCan_Action canAction = WateringCan_Action::DOWN;

	//InventoryComponent* inventory = nullptr;
	//Tool equippedTool = Tool::None;

	//std::map<Tool, std::map<Direction, std::vector<HBITMAP>>> playerSprites;

	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;

	
	//void ReleaseResources();  // 필요 시 구현
};
