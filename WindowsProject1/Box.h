#pragma once
#include "WorldObject.h"
#include "InventoryItem.h"
#include <Windows.h>

//#define tileSize 32
class Player;
class Box: public WorldObject
{
public:
    Box();
    void Render(HDC hdc, int Tilesize) override;
    void SetTilePosition(int px, int py) override;
    PlaceableType GetPlaceableType() const override;
    RECT GetCollisionRect();

    void Open(); //열고
    void Close(); //닫기
    bool IsOpen() const;

    void RenderUI(HDC hdc);     // 상자 아이템 칸 UI 

   

   bool HandleClick(int mouseX, int mouseY, int num);//마우스 좌클릭 지점 확인(박스 칸 or 플레이어 툴바)
   void HandleItemSlotLClick(InventoryItem* slot);//마우스 좌클릭으로 슬롯과 현재 들고 있는 아이템 처리 함수
   void HandleItemSlotRClick(InventoryItem* slot);

   void RenderSlot(HDC hdc, int left, int top, const InventoryItem& item);
   void RenderCursorItem(HDC hdc); //클릭된 아이템이 커서에 붙게 하는 함수



    void AddItem(int slotIndex, const InventoryItem& item);
    InventoryItem* GetItems() { return items; }
    void SetPlayerToolbar(InventoryItem* toolbar);
    void OnInteract(Player* player);

private:
    int x, y;                  
    bool isOpen = false;
    int baseX = 360;
    int baseY = 150;
    bool playerNear = false;

    const int SLOT_ROWS = 3;
    const int SLOT_COLS = 9;
    const int SLOT_SIZE = 50;
    const int SLOT_MARGIN = 5;
    const int TOOLBAR_Y = 300;

    HBITMAP bmp;
    InventoryItem items[27];   // 3x9 인벤토리 슬롯(임시)
    InventoryItem* playerToolbar;

    //InventoryItem heldItem;
    //HBITMAP hIconBitmap;
    //RECT iconRect;              // 아이콘 영역 (3x9 타일 크기)
};

//public

// void HandleItemSlotRClick(InventoryItem* slot);//마우스 우클릭으로 슬롯과 현재 들고 있는 아이템 처리 함수

// std::vector<RECT>GetCollisionRects()const override;

// RECT GetBoundingBox() const; //상자 충돌 범위(빨간 테투리)
// 
// void SetPlayerNear(bool ch);
// bool IsPlayerNear() { return playerNear; }

    //std::vector<RECT> GetCollisionRects() const override;

      //void Interact(Player& player) override;

   // PlaceableType GetType() const override { return PlaceableType::Box;}
       // bool IsPlayerInRange(int playerX, int playerY); //플레이어가 박스 주변에 있는 지 확인
   // bool IsMouseOverIcon(int mouseX, int mouseY);//마우스 커서가 상자아이콘 위에 있는지 확인
    //Box(int x, int y);