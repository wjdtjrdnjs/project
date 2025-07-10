#pragma once
#include "resource.h"
#include "Crop.h"
#include <windows.h>
#include <vector>
#include <algorithm>
enum Direction { //플레이어 방향
	DOWN = 0,
	UP = 1,
	RIGHT = 2,
	LEFT = 3
};
struct InventoryItem {  //플레이어 인벤토리 (아래 9칸)
	CropType type = CropType::None;  //아이템 타입
	int count = 0;		//아이테 개수 
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

	static bool IsInPlayerRange(int tileX, int tileY, int playerX, int playerY);  //플레이어 범위 확인용
	void RenderInventory(HDC hdc, int screenWidth, int screenHeight);  //플레이어 아래 인벤창(툴바) 함수
	void AddItem(CropType type); //인벤토리 아이템 추가
	
	void Render(HDC hdc); //플레이어 그림
	void PlayerUpdate(); //플레이어 행동

	///PlayerUpdate()에서 확인 가능
	void SetSelectedCrop(CropType type) { selectedCrop = type; }  //SetSelectedCrop 선택된 아이템 타입을 가져옴 
	CropType GetSelectedCrop() const { return selectedCrop; } //GetSelectedCrop 선택된 아이템 타입 리턴
	void SetSelectedTool(int t) { selectedTool = t; } //SetSelectedTool 선택된 번호를 가져옴
	int GetSelectedTool()  { return selectedTool; }  //GetSelectedTool 선택된 번호를 리턴해줌
	
	//인벤토리 정보 리턴
	InventoryItem* GetInventory() { return inventory; }

	void SetBoxOpen(bool open) { isBoxOpen = open; } //open은 true 또는 false
	bool IsBoxOpen() const { return isBoxOpen; }
private:
	std::vector<HBITMAP>PLY; 
	bool isBoxOpen = false;
	
	CropType selectedCrop = CropType::Strawberry; //처음은 딸기를 들고있는다
	Direction currentDir = DOWN;	  //처음 방향은 아래이다
	InventoryItem inventory[9];
	int selectedTool = 4; //
	int x = 100;
	int y = 100;
	int playersize = 35;
	HBITMAP hBmp = nullptr; // 비트맵 핸들 저장용
	HDC memDC = nullptr;
};

