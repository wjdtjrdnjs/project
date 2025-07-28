#pragma once
#include <vector>
#include <map>
#include <windows.h>
#include "resource.h"
#include "Direction.h" 
#include "PlayerInventory.h"

class Map;
class Player 
{
 public:
	Player();
	void Render(HDC hdc, int Tilesize);
	void SetPosition(float px, float py);
	
	// 플레이어 좌표 
	float GetX() const { return x; }
	float GetY() const { return y; }

	void MovePlayer(float deltaTime);  //플레이어 움직임

	void HandleInput(); //플레이어 입력 처리

	//좌클릭 우클릭
	void HandleLeftClick(Map& map);
	void HandleRightClick(Map& map);
	
	std::vector<RECT> GetCollisionRects() const;
	PlayerInventory* GetInventory() { return inventory; }; //인벤토리를 가져옴

	void Update(float deltaTime); //플레이어 업데이트 (방향전환)
	int GetSize() const { return playerSize; } //플래이어 사이즈

	//방향 전환 함수
	void SetKeyState(Direction dir, bool pressed); //플레이어 방향 전환

	void SetDirection(Direction dir); //무슨 방향인지 데이터 가져옴

	bool IsPlayerOnPortal(float  x, float  y);



	private:
	//
	float x;
	float y;
	float speed = 1.0f;
	//
	int playerSize = 35;
	bool move = FALSE;
	PlayerInventory* inventory = nullptr;
	//현재 4개밖에 map 없으니 사용
	std::map<Direction, bool> keyStates;// 각 방향키의 눌림 상태를 저장하는 코드 , true면 방향키가 눌림 상태, false면 눌리지 않은 상태

	Direction lastPressedDirection = Direction::DOWN; //플레이어 방향 저장 처음은 Down

	int currentMapIndex = 0;
	int selectedSlot = 0;

	Direction PlayerDirection;
	//키 누름 상태 감지 변수
	bool keyUp = false;
	bool keyDown = false;
	bool keyLeft = false;
	bool keyRight = false;

	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;

	
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