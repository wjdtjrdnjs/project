#pragma once

#include <Windows.h>
#include "Player.h"
#include "Map.h"



class Box {
public:
    Box(int x, int y);
    void Render(HDC hdc);       // 상자 아이콘 그리기
    void RenderUI(HDC hdc);     // 상자 아이템 칸 UI 
    bool IsPlayerInRange(int playerX, int playerY); //플레이어가 박스 주변에 있는 지 확인
    bool IsMouseOverIcon(int mouseX, int mouseY);//마우스 커서가 상자아이콘 위에 있는지 확인
    void Open(); //열고
    void Close(); //닫기
    bool IsOpen() const;

    InventoryItem* GetItems();

private:
    int x, y;                  
    bool isOpen = false;
    InventoryItem items[27];    // 3x9 인벤토리 슬롯(임시)
    HBITMAP hIconBitmap;
    RECT iconRect;              // 아이콘 영역 (3x3 타일 크기)
};
