#pragma once
#include <windows.h>
#include "Global.h" //충돌영역 on/off
#include "WorldObject.h"
#include "InventoryItem.h"
class Player;
class NPC :public WorldObject
{
public:
	NPC();
	void SetTilePosition(int tileX, int tileY) override;
	void Render(HDC hdc, int tilesize) override;
	void RenderUI(HDC hdc);
	PlaceableType GetPlaceableType()const override;
	void SetPlayerToolbar(InventoryItem* toolbar);
	void OnInteract(Player* player);
	RECT GetCollisionRect();

	bool HandleClick(int mouseX, int mouseY, int num);//마우스 좌클릭 지점 확인(박스 칸 or 플레이어 툴바)
	void HandleItemSlotLClick(InventoryItem* slot);//마우스 좌클릭으로 슬롯과 현재 들고 있는 아이템 처리 함수
	void HandleItemSlotRClick(InventoryItem* slot);

private:
	int x, y;
	int Fencesize = 10;
	InventoryItem items[27];   // 3x9 인벤토리 슬롯(임시)
	InventoryItem* playerToolbar;

	HBITMAP hBmp; // 비트맵 핸들 저장용
};