#pragma once
#include <vector>
#include <windows.h>
#include <algorithm>
#include "resource.h"
#include "CropType.h"
#include "Crop.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "PlaceableObject.h"

enum Direction { //플레이어 방향
	DOWN = 0,
	UP = 1,
	RIGHT = 2,
	LEFT = 3
};

class Player
{
public:
	Player();
	~Player();
	//플레이어 좌표
	int GetX()  { return x; }
	int GetY()  { return y; }
	void SetPosition(int newX, int newY) {
		x = newX;
		y = newY;
	}

	static bool IsInPlayerRange(int tileX, int tileY, int playerX, int playerY);  //플레이어 범위 
	void RenderInventory(HDC hdc, int screenWidth, int screenHeight);  //플레이어 아래 인벤창(툴바) 렌더링
	void AddItem(CropType type);		//인벤토리에 아이템 추가
	
	void Render(HDC hdc);	//플레이어 렌더링
	void PlayerUpdate();	//플레이어 업데이트(이동 처리, 툴바 번호 선택, 좌클릭 or 우클릭, 방향 이미지 갱신)
	void Playermove();		//플레이어 이동 처리
	void HandleToolSelection();		// 툴바 번호 선택
	void HandleLeftClickAction();	// 좌클릭 
	void HandleRightClickAction();  // 우클릭 
	void UpdateBitmap();			//방향 이미지 갱신

	///PlayerUpdate()에서 확인 가능
	void SetSelectedCrop(CropType type) { selectedCrop = type; }  //SetSelectedCrop 선택된 아이템 타입을 가져옴 
	CropType GetSelectedCrop() const { return selectedCrop; } //GetSelectedCrop 선택된 아이템 타입 리턴  //현재 사용x
	void SetSelectedTool(int t) { selectedTool = t; } //SetSelectedTool 선택된 번호를 가져옴
	int GetSelectedTool()  { return selectedTool; }  //GetSelectedTool 선택된 번호를 리턴해줌

	//void RenderFullInventory(HDC hdc) {  //인벤토리 전체 렌더링 Inventory.h에 사용됨
	//	fullInventory.Render(hdc, 360, 100);  // 원하는 위치에 UI 출력
	//}

	void SetInventoryOpen(bool open) { isInventoryOpen = open; }
	bool IsInventoryOpen() const { return isInventoryOpen; }

	//인벤토리 정보 리턴
	InventoryItem* GetInventory() { return inventory; }

	void SetBoxOpen(bool open) { isBoxOpen = open; } //open은 true 또는 false
	bool IsBoxOpen() const { return isBoxOpen; }
private:
	std::vector<HBITMAP>PLY; 
	bool isBoxOpen = false;
	bool isInventoryOpen = false;
	CropType selectedCrop = CropType::None; //빈손
	Direction currentDir = DOWN;	  //처음 방향은 아래이다
	InventoryItem inventory[9];
	//Inventory fullInventory;
	int selectedTool = 4; //
	int x = 39;
	int y = 170;
	int playersize = 35;
	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;
};

