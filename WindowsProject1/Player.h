#pragma once
#include <vector>
#include <map>
#include <windows.h>
#include "resource.h"
#include "Direction.h" 
#include "PlayerInventory.h" 
class Player 
{
 public:
	Player();
	void Render(HDC hdc, int Tilesize, Direction dir);
	void SetPosition(float px, float py);
	
	// �÷��̾� ��ǥ 
	float GetX() const { return x; }
	float GetY() const { return y; }




	std::vector<RECT> GetCollisionRects() const;
	PlayerInventory* GetInventory() { return inventory; }; //�κ��丮�� ������

	void Update(float deltaTime, bool up, bool down, bool left, bool right); //�÷��̾� ������Ʈ (������ȯ)
	int GetSize() const { return playerSize; } //�÷��̾� ������





	private:
	//
	float x;
	float y;
	float speed = 5.0f;
	//
	int playerSize = 35;

	PlayerInventory* inventory = nullptr;
	

	HBITMAP hBmp = nullptr; // ��Ʈ�� �ڵ� �����
	HDC memDC = nullptr;

	
};

//void ReleaseResources();  // �ʿ� �� ����
	//void SetTilePosition(int px, int py) override;


//~Player();
	//ObjectType GetObjectType() const override;
	//void LoadSprites();

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

//Direction currentDir = Direction::DOWN; // �ʱ� ������ �Ʒ�
	//WateringCan_Action canAction = WateringCan_Action::DOWN;

	//InventoryComponent* inventory = nullptr;
	//Tool equippedTool = Tool::None;

	//std::map<Tool, std::map<Direction, std::vector<HBITMAP>>> playerSprites;