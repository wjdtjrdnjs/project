#pragma once
#include "WorldObject.h"
#include <Windows.h>

//#define tileSize 32

class Box: public WorldObject
{
public:
    Box();
    void Render(HDC hdc, int Tilesize) override;
    void SetTilePosition(int px, int py) override;
    ObjectType GetObjectType() const override;
   // ObjectType GetType() const override { return ObjectType::Box;}

    //Box(int x, int y);
   // void RenderUI(HDC hdc);     // 상자 아이템 칸 UI 
   // bool IsPlayerInRange(int playerX, int playerY); //플레이어가 박스 주변에 있는 지 확인
   // bool IsMouseOverIcon(int mouseX, int mouseY);//마우스 커서가 상자아이콘 위에 있는지 확인
   // void Open(); //열고
   // void Close(); //닫기
   // bool IsOpen() const;
   // void HandleClick(int row, int col, int num); //마우스 좌클릭 지점 확인(박스 칸 or 플레이어 툴바)
   // void RenderCursorItem(HDC hdc); //클릭된 아이템이 커서에 붙게 하는 함수

   // void HandleItemSlotLClick(InventoryItem* slot);//마우스 좌클릭으로 슬롯과 현재 들고 있는 아이템 처리 함수
   // void HandleItemSlotRClick(InventoryItem* slot);//마우스 우클릭으로 슬롯과 현재 들고 있는 아이템 처리 함수

   // std::vector<RECT>GetCollisionRects()const override;

   // RECT GetBoundingBox() const; //상자 충돌 범위(빨간 테투리)
   //// InventoryItem* GetItems();
   // void SetPlayerToolbar(InventoryItem* toolbar);
   // 
   // void SetPlayerNear(bool ch);
   // bool IsPlayerNear() { return playerNear; }
       
private:
    int x, y;                  
    bool isOpen = false;
    bool playerNear = false;
    HBITMAP bmp;
    //InventoryItem* playerToolbar[9];
    //InventoryItem items[3][9];    // 3x9 인벤토리 슬롯(임시)
    //InventoryItem heldItem;
    //HBITMAP hIconBitmap;
    //RECT iconRect;              // 아이콘 영역 (3x9 타일 크기)
};
