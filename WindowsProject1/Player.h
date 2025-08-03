#pragma once
#include <vector>
#include <map>
#include <windows.h>
#include "resource.h"
#include "Direction.h" 
#include "PlayerInventory.h"
#include "CollisionManager.h"
constexpr int TILE_SIZE = 32;

class Map;
class Player 
{
 public:
	Player();
	void Render(HDC hdc);
	void SetPosition(float px, float py);
	void SetCollisionManager(CollisionManager* cm) {
		collisionManager = cm;
	}
	// �÷��̾� ��ǥ 
	float GetX() const { return x; }
	float GetY() const { return y; }

	int GetTileX() const { return static_cast<int>(floor(x)); }
	int GetTileY() const { return static_cast<int>(floor(y)); }

	int GetPixelX() const { return static_cast<int>(x * TILE_SIZE); }
	int GetPixelY() const { return static_cast<int>(y * TILE_SIZE); }


	// --- ���� ---
	int GetSize() const { return playerSize; }
	PlayerInventory* GetInventory() { return inventory; }
	bool IsInteracting() const { return isInteracting; }

	// --- �Է� �� ������ ---
	void HandleInput();         // Ű���� �� �Է� ó��
	void MovePlayer(float deltaTime); // �̵� ó��
	void HandleLeftClick();     // ���콺 ��Ŭ��
	void HandleRightClick();    // ���콺 ��Ŭ��

	void SetKeyState(Direction dir, bool pressed);
	void SetDirection(Direction dir);

	// --- ��ȣ�ۿ� ���� �� ���� ---
	std::vector<RECT> GetPlayerPlusRangeRects(int pixelX, int pixelY) const; // ���� ��ġ ���� ���� �ڽ�
	std::pair<int, int> GetFacingTilePos() const;                            // �ٶ󺸴� ���� Ÿ�� ��ǥ
	bool CanInteractAt(int pixelX, int pixelY);                              // �ش� ��ǥ�� ��ȣ�ۿ� ��������

	RECT GetCollisionRects() const; // �浹 ���� (���� ���ο� ���� ���� �ʿ�)

	// --- ��ȣ�ۿ� ���� ---
	void StartInteraction();   // UI ����
	void EndInteraction();     // UI �ݱ�

	// --- ������Ʈ ---
	void Update(float deltaTime);

private:
	// --- ��ġ �� �̵� ---
	float x = 0.0f;
	float y = 0.0f;
	float speed = 1.0f;
	int playerSize = 35;          // �÷��̾� ũ�� (�ȼ� ����)
	//int tileSize = 64;            // ���� ��� ���� Ÿ�� ũ��
	bool isMoving = false;        // �÷��̾� �̵� ����

	// --- ���� �� �Է� ---
	Direction lastPressedDirection = Direction::DOWN; // �⺻ ����
	Direction playerDirection = Direction::DOWN;       // ���� ���� (�ִϸ��̼� ��� ��� ����)

	bool keyUp = false;
	bool keyDown = false;
	bool keyLeft = false;
	bool keyRight = false;

	std::map<Direction, bool> keyStates;  // �� ������ Ű ���� ���� (SetKeyState ���)

	// --- ���� �� ��ȣ�ۿ� ---
	bool isInteracting = false;   // ��ȣ�ۿ� ���̸� true (������ ���� ��)

	int currentMapIndex = 0;      // ���� �� �ε���
	int selectedSlot = 0;         // ���õ� �κ��丮 ���� ��ȣ

	// --- ������Ʈ ---
	PlayerInventory* inventory = nullptr;
	CollisionManager* collisionManager = nullptr;

	// --- ������ �ڿ� ---
	HBITMAP hBmp = nullptr;       // �÷��̾� ��������Ʈ ��Ʈ��
	HDC memDC = nullptr;          // �޸� DC (���� ���۸���)
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