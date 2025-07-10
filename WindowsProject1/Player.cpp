#include "Player.h"
#include "Map.h"
#include "InputManager.h" 
#include <iostream>
#include <string>
#include "RenderManager.h"
#include "BitmapManager.h"
Player::Player() : x(0), y(0), selectedCrop(CropType::Strawberry) 
{
    selectedCrop = CropType::Strawberry_1;
    selectedTool = -1;

    // 생성자에서 한 번만 비트맵 로드
    for (int i = 0; i < 4; ++i) {
        HBITMAP player = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_IDLE + i), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR); //플레이어 벙향
        PLY.push_back(player);  //4장

    }
    hBmp = PLY[currentDir];
    for (int i = 0; i < 9; i++) {
        inventory[i].type = CropType::None;
        inventory[i].count = 0;
    }
    inventory[0].type = CropType::Strawberry_1; //1번 딸기봉투와 5개
    inventory[0].count = 5;
    inventory[1].type = CropType::Onion_1;      //2번 양파봉투 5개
    inventory[1].count = 5;
    inventory[2].type = CropType::Stone;        //괭이
    inventory[2].count = 1;
    if (hBmp)
    {
        // 메모리 DC 생성 후 비트맵 선택
        HDC screenDC = GetDC(NULL);
        memDC = CreateCompatibleDC(screenDC);
        ReleaseDC(NULL, screenDC);

        SelectObject(memDC, hBmp);
    }
}

Player::~Player()
{
    if (memDC) DeleteDC(memDC);
    if (hBmp) DeleteObject(hBmp);
}

bool Player::IsInPlayerRange(int tileX, int tileY, int playerX, int playerY)  //플레이어 사거리
{
    int playerTileX = playerX / tileSize;
    int playerTileY = playerY / tileSize;

    return abs(tileX - playerTileX) <= 1 && abs(tileY - playerTileY) <= 1;

}

void Player::RenderInventory(HDC hdc, int screenWidth, int screenHeight)  //플레이어 아래 인벤창(툴바)
{
    int slotSize = 50;
    int startX = 10;
    int startY = screenHeight - slotSize - 10;

    for (int i = 0; i < 9; i++) { //9칸
        HBRUSH brush = nullptr;
        if (i == selectedTool - 1)   //선택된 번호
            brush = CreateSolidBrush(RGB(150, 150, 150)); // 선택된 슬롯 강조
        else
            brush = CreateSolidBrush(RGB(200, 200, 200)); // 기본 색
        
        RECT slotRect = { startX + i * (slotSize + 5)+350, startY, startX + i * (slotSize + 5) + slotSize+350, startY + slotSize };

        FillRect(hdc, &slotRect, brush);
        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // 테두리

        DeleteObject(brush);

        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        if (inventory[i].type != CropType::None) {
            HBITMAP bmp = BitmapManager::GetBitmapForCrop(inventory[i].type);

           

            HDC memDC = CreateCompatibleDC(hdc);
            HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
            BITMAP bm;
            GetObject(bmp, sizeof(BITMAP), &bm);

            int drawSize = 40;
            int offsetX = slotRect.left + (slotSize - drawSize) / 2;
            int offsetY = slotRect.top + (slotSize - drawSize) / 2;
          
            
            TransparentBlt(hdc,
                offsetX, offsetY,
                drawSize, drawSize, 
                memDC,
                0, 0, 
                bm.bmWidth,
                bm.bmHeight,
                RGB(255, 255, 255));
            std::string countText = std::to_string(inventory[i].count);
            TextOutA(hdc, offsetX + 30, offsetY + 30, countText.c_str(), countText.length());
            SelectObject(memDC, oldBmp);
            DeleteDC(memDC);
        }

    }
}

void Player::AddItem(CropType type) {
    // 이미 존재하는 아이템이면 count 증가
    for (auto& slot : inventory) {
        if (slot.type == type) {
            slot.count++;
            return;
        }
    }

    // 빈 슬롯에 새로 추가
    for (auto& slot : inventory) {
        if (slot.type == CropType::None) {
            slot.type = type;
            slot.count = 1;
            return;
        }
    }

}

void Player::Render(HDC hdc)
{
    if (!hBmp || !memDC)
        return;

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

    TransparentBlt(
        hdc,
        x, y,
        bmp.bmWidth+ playersize, bmp.bmHeight+ playersize,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );
}

void Player::PlayerUpdate()
{
    if (isBoxOpen) return;
    // 이동 처리
    if (GetKeyState('A') & 0x8000) {
        x -= 5;
        currentDir = LEFT;
    }
    else if (GetKeyState('D') & 0x8000) {
        x += 5;
        currentDir = RIGHT;
    }
    else if (GetKeyState('W') & 0x8000) {
        y -= 5;
        currentDir = UP;
    }
    else if (GetKeyState('S') & 0x8000) {
        y += 5;
        currentDir = DOWN;
    }

    // 작물 선택 (1, 2)
    if (GetKeyState('1') & 0x8000) {
        selectedTool = 1; // 딸기 선택
        selectedCrop = CropType::Strawberry_1;
    }
    else if (GetKeyState('2') & 0x8000) {
        selectedTool = 2; // 양파 선택
        selectedCrop = CropType::Onion_1;
    }
    else if (GetKeyState('3') & 0x8000) {
        selectedTool = 3; // 괭이
    }
    else if (GetKeyState('4') & 0x8000) {
        selectedTool = 4; // 맨손
    }
    else if (GetKeyState('5') & 0x8000) {
        selectedTool = 5; // 맨손
    }
    else if (GetKeyState('6') & 0x8000) {
        selectedTool = 6; // 맨손
    }
    else if (GetKeyState('7') & 0x8000) {
        selectedTool = 7; // 맨손
    }
    else if (GetKeyState('8') & 0x8000) {
        selectedTool = 8; // 맨손
    }

  

    // 이미지 핸들 업데이트
    hBmp = PLY[currentDir];
    if (memDC && hBmp) {
        SelectObject(memDC, hBmp);
    }
}
