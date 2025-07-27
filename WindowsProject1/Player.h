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
	// �÷��̾� ��ǥ 
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
	////void Render(HDC hdc);	// �÷��̾� ������

	//void SetDirection(Direction dir) { currentDir = dir; }
	//Direction  GetDirection() const { return currentDir; }

	//std::vector<RECT> GetCollisionRects() const override;

	////�÷��̾� �κ��丮 ����
	//InventoryComponent* GetInventory() { return inventory; }

	//void SetEquippedTool(Tool t) { equippedTool = t; }
	//Tool GetEquippedTool() const {return equippedTool;}
	//void StartAction();
	private:
	int tileX = 0;  // Ÿ�� ��ġ (����)
	int tileY = 0;
	float pixelX = 0.f;  // ���� �ȼ� ��ġ (�ڿ������� �̵���)
	float pixelY = 0.f;
	//
	float x;
	float y;
	float speed = 5.0f;
	//
	int playerSize = 35;
	//Direction currentDir = Direction::DOWN; // �ʱ� ������ �Ʒ�
	//WateringCan_Action canAction = WateringCan_Action::DOWN;

	//InventoryComponent* inventory = nullptr;
	//Tool equippedTool = Tool::None;

	//std::map<Tool, std::map<Direction, std::vector<HBITMAP>>> playerSprites;

	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
	HDC memDC = nullptr;

	
	//void ReleaseResources();  // �ʿ� �� ����
};
