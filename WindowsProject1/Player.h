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
	// 플레이어 좌표 
	float GetX() const { return x; }
	float GetY() const { return y; }

	int GetTileX() const { return static_cast<int>(floor(x)); }
	int GetTileY() const { return static_cast<int>(floor(y)); }

	int GetPixelX() const { return static_cast<int>(x * TILE_SIZE); }
	int GetPixelY() const { return static_cast<int>(y * TILE_SIZE); }


	// --- 상태 ---
	int GetSize() const { return playerSize; }
	PlayerInventory* GetInventory() { return inventory; }
	bool IsInteracting() const { return isInteracting; }

	// --- 입력 및 움직임 ---
	void HandleInput();         // 키보드 및 입력 처리
	void MovePlayer(float deltaTime); // 이동 처리
	void HandleLeftClick();     // 마우스 좌클릭
	void HandleRightClick();    // 마우스 우클릭

	void SetKeyState(Direction dir, bool pressed);
	void SetDirection(Direction dir);

	// --- 상호작용 범위 및 조건 ---
	std::vector<RECT> GetPlayerPlusRangeRects(int pixelX, int pixelY) const; // 현재 위치 기준 범위 박스
	std::pair<int, int> GetFacingTilePos() const;                            // 바라보는 방향 타일 좌표
	bool CanInteractAt(int pixelX, int pixelY);                              // 해당 좌표에 상호작용 가능한지

	RECT GetCollisionRects() const; // 충돌 영역 (구현 여부에 따라 정리 필요)

	// --- 상호작용 상태 ---
	void StartInteraction();   // UI 열기
	void EndInteraction();     // UI 닫기

	// --- 업데이트 ---
	void Update(float deltaTime);

private:
	// --- 위치 및 이동 ---
	float x = 0.0f;
	float y = 0.0f;
	float speed = 1.0f;
	int playerSize = 35;          // 플레이어 크기 (픽셀 단위)
	//int tileSize = 64;            // 현재 사용 중인 타일 크기
	bool isMoving = false;        // 플레이어 이동 상태

	// --- 방향 및 입력 ---
	Direction lastPressedDirection = Direction::DOWN; // 기본 방향
	Direction playerDirection = Direction::DOWN;       // 현재 방향 (애니메이션 등에서 사용 가능)

	bool keyUp = false;
	bool keyDown = false;
	bool keyLeft = false;
	bool keyRight = false;

	std::map<Direction, bool> keyStates;  // 각 방향의 키 상태 저장 (SetKeyState 사용)

	// --- 상태 및 상호작용 ---
	bool isInteracting = false;   // 상호작용 중이면 true (움직임 제한 등)

	int currentMapIndex = 0;      // 현재 맵 인덱스
	int selectedSlot = 0;         // 선택된 인벤토리 슬롯 번호

	// --- 컴포넌트 ---
	PlayerInventory* inventory = nullptr;
	CollisionManager* collisionManager = nullptr;

	// --- 렌더링 자원 ---
	HBITMAP hBmp = nullptr;       // 플레이어 스프라이트 비트맵
	HDC memDC = nullptr;          // 메모리 DC (더블 버퍼링용)
};

//void ReleaseResources();  // 필요 시 구현
	//void SetTilePosition(int px, int py) override;


//~Player();
	//ObjectType GetObjectType() const override;
	//void LoadSprites();

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

//Direction currentDir = Direction::DOWN; // 초기 방향은 아래
	//WateringCan_Action canAction = WateringCan_Action::DOWN;

	//InventoryComponent* inventory = nullptr;
	//Tool equippedTool = Tool::None;

	//std::map<Tool, std::map<Direction, std::vector<HBITMAP>>> playerSprites;