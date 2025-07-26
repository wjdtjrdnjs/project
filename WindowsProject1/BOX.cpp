#define _CRT_SECURE_NO_WARNINGS
#include "Box.h"
#include "BitmapManager.h"
#include "WorldObject.h"
#include "TileData.h"
#include <string>
//#include "InputManager.h"
//#include "InventoryItem.h"
//#include "GameObjectManager.h"
//#include "WorldMap.h"
//
//#include <string>
//#include <string>
//#include "Global.h" //충돌영역 on/off
//
//Box::Box(int xPos, int yPos) : x(xPos), y(yPos), isOpen(false)
//{
//    //위치
//    iconRect.left = x;
//    iconRect.top = y;
//    iconRect.right = x +  tileSize * 3;
//    iconRect.bottom = y + tileSize * 3;
//
//    // 비트맵 로드 
//    hIconBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL),
//        MAKEINTRESOURCE(IDB_BITMAP24),
//        IMAGE_BITMAP,
//        0, 0,
//        LR_CREATEDIBSECTION);
//    for (int y = 0; y < 3; y++)
//    {
//        for (int i = 0; i < 9; i++) 
//        {
//            items[y][i].itemType = ItemType::NONE;
//            items[y][i].cropType = CropType::None;
//            items[y][i].toolType = Tool::None;
//            items[y][i].count = 0;
//        }
//    }
//    items[0][0].itemType = ItemType::CROP;
//    items[0][0].cropType = CropType::Strawberry_1; //1번 딸기봉투와 5개
//    items[0][0].count = 99;
//
//    items[0][1].itemType = ItemType::CROP;
//    items[0][1].cropType = CropType::Onion_1;      //2번 양파봉투 5개
//    items[0][1].count = 99;
//
//    items[0][2].itemType = ItemType::CROP;
//    items[0][2].cropType = CropType::Fence;        //울타리
//    items[0][2].count = 99;
//
//    items[0][3].itemType = ItemType::TOOL;
//    items[0][3].toolType = Tool::Axe;       //도끼
//    items[0][3].count = 1;
//}
//bool Box::IsPlayerInRange(int playerX, int playerY) {  //플레이어가 박스 타일 주변에 있는 지 확인
//    int playerTileX = playerX / tileSize;
//    int playerTileY = playerY / tileSize;
//    int BoxTileX = x / tileSize;
//    int BoxTileY = y / tileSize;
//
//    return abs(playerTileX - BoxTileX) <= 1 &&   // -1,0,1 범위
//        abs(playerTileY - BoxTileY) <= 1;
//}
//
//
//bool Box::IsMouseOverIcon(int mouseX, int mouseY) { //마우스 커서가 상자아이콘 위에 있는지 확인
//    return mouseX >= iconRect.left && mouseX <= iconRect.right &&
//        mouseY >= iconRect.top && mouseY <= iconRect.bottom;
//}
//void Box::Open() {
//    GameObjectManager::Instance().GetPlayerController()->SetStopped(true);
//    isOpen = true;
//}
//
//void Box::Close() {
//    GameObjectManager::Instance().GetPlayerController()->SetStopped(false);
//    isOpen = false;
//}
//
//bool Box::IsOpen() const {
//    return isOpen;
//}
//
//RECT Box::GetBoundingBox()const //상자 충돌 범위
//{
//    BITMAP bmpInfo;
//    GetObject(hIconBitmap, sizeof(BITMAP), &bmpInfo);
//
//    RECT rect;
//    rect.left = x + 5;  // 왼
//    rect.top = y;        //위
//    rect.right = rect.left + bmpInfo.bmWidth +10; //오른쪽
//    rect.bottom = rect.top + bmpInfo.bmHeight + 10; //아래
//
//    return rect;
//}
//
//void Box::SetPlayerToolbar(InventoryItem* toolbar)
//{
//    for (int i = 0; i < 9; i++)
//    {
//        playerToolbar[i] = &toolbar[i];  //박스 안에서 교환이 이루어지므로 주소값을 가져옴
//    }
//  
//}
//
//void Box::SetPlayerNear(bool ch) //플레이어가 박스 근처에 있을 시
//{
//    playerNear = ch; 
//}
//
//
//void Box::RenderUI(HDC hdc)
//{
//    int startX = 10;
//    int startY = 100;
//    for (int y = 0; y < 3; y++) {
//
//        for (int i = 0; i < 9; i++) {
//            HBRUSH brush = nullptr;
//            brush = CreateSolidBrush(RGB(200, 200, 200)); // 기본 색
//
//            RECT slotRect = { startX + i * (slotSize + 5) + 350, startY + y * 51, startX + i * (slotSize + 5) + slotSize + 350, startY + slotSize + y * 51 };
//
//            FillRect(hdc, &slotRect, brush);
//            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // 테두리
//            if (items[y][i].itemType != ItemType::NONE) {
//                HBITMAP bmp = BitmapManager::Instance().GetBitmapForCrop(items[y][i]);
//                if (!bmp)  return;
//
//                HDC memDC = CreateCompatibleDC(hdc);
//                HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
//                BITMAP bm;
//                GetObject(bmp, sizeof(BITMAP), &bm);
//
//
//                int drawSize = 40;
//                int offsetX = slotRect.left + (slotSize - drawSize) / 2;
//                int offsetY = slotRect.top + (slotSize - drawSize) / 2;
//
//
//                TransparentBlt(hdc,
//                    offsetX, offsetY,
//                    drawSize, drawSize,
//                    memDC,
//                    0, 0,
//                    bm.bmWidth,
//                    bm.bmHeight,
//                    RGB(255, 255, 255));
//                std::string countText = std::to_string(items[y][i].count);
//                TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
//                SelectObject(memDC, oldBmp);
//                DeleteDC(memDC);
//
//            }
//            DeleteObject(brush);
//        }
//    }
//         startX = 10;
//         startY = 100 + 3 * 51 + 10;  // 상자 아래 여백 10
//
//        for (int i = 0; i < 9; i++) {
//            RECT slotRect = {
//                startX + i * (slotSize + 5) + 350,
//                startY,
//                startX + i * (slotSize + 5) + slotSize + 350,
//                startY + slotSize
//            };
//
//            HBRUSH brush = CreateSolidBrush(RGB(180, 180, 180));
//            FillRect(hdc, &slotRect, brush);
//            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
//            DeleteObject(brush);
//            if (playerToolbar[i]->itemType != ItemType::NONE) {
//                HBITMAP bmp = BitmapManager::Instance().GetBitmapForCrop(*playerToolbar[i]);
//
//                if (!bmp) return;
//                if (bmp) {
//                    HDC memDC = CreateCompatibleDC(hdc);
//                    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
//                    BITMAP bm;
//                    GetObject(bmp, sizeof(BITMAP), &bm);
//
//                    int drawSize = 40;
//                    int offsetX = slotRect.left + (slotSize - drawSize) / 2;
//                    int offsetY = slotRect.top + (slotSize - drawSize) / 2;
//
//                    TransparentBlt(hdc, offsetX, offsetY,
//                        drawSize, drawSize,
//                        memDC, 0, 0,
//                        bm.bmWidth, bm.bmHeight,
//                        RGB(255, 255, 255));
//
//                    std::string countText = std::to_string(playerToolbar[i]->count);
//                    TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
//                    SelectObject(memDC, oldBmp);
//                    DeleteDC(memDC);
//                }
//            }
//        }
//        RenderCursorItem(hdc);
//
//    }
// 
////클릭된 아이템이 커서에 붙게 하는 함수
//void Box::RenderCursorItem(HDC hdc) { 
//    if (heldItem.itemType == ItemType::NONE) return; // 아무것도 안 들고 있으면 돌아감
//
//    POINT mouse = InputManager::Instance().GetMousePosition();  //클릭한 좌표를 가져옴
//    HBITMAP bmp = BitmapManager::Instance().GetBitmapForCrop(heldItem);
//    if (!bmp) return;
//  
//    HDC memDC = CreateCompatibleDC(hdc);
//    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
//    BITMAP bm;
//    GetObject(bmp, sizeof(BITMAP), &bm);
//
//    int drawSize = 40;
//    TransparentBlt(
//        hdc,
//        mouse.x-20 , mouse.y -20,
//        drawSize, drawSize,
//        memDC,
//        0, 0,
//        bm.bmWidth, bm.bmHeight,
//        RGB(255, 255, 255)
//    );
//
//    if (heldItem.count > 0) { //아이템 수량이 1개 이상일 때 수량 표시 
//        std::string countText = std::to_string(heldItem.count);
//        TextOutA(hdc, mouse.x + 5, mouse.y + 10, countText.c_str(), countText.length());
//    }
//
//    SelectObject(memDC, oldBmp);
//    DeleteDC(memDC);
//}
//
///////////////////코드 수정////////////////
// //마우스로 클릭한 슬롯과 현재 들고 있는 아이템 처리 함수
//void Box::HandleItemSlotLClick(InventoryItem* slot)  //좌클릭
//{
//
//    if (heldItem.itemType == ItemType::NONE) {
//        // 빈손이면 슬롯의 아이템을 든다
//        heldItem = *slot;
//        slot->itemType = ItemType::NONE;
//        slot->cropType = CropType::None;
//        slot->toolType = Tool::None;
//        slot->count = 0;
//    }
//    else {
//        if (slot->itemType == ItemType::NONE) {
//            // 빈 슬롯이면 아이템을 넣는다
//            *slot = heldItem;
//            heldItem.itemType = ItemType::NONE;
//            heldItem.cropType = CropType::None;
//            heldItem.toolType = Tool::None;
//            heldItem.count = 0;
//        }
//        else if (slot->itemType == heldItem.itemType) {
//            // 같은 아이템이면 합치기
//            if (heldItem.itemType == ItemType::TOOL)
//            {
//                if (slot->toolType == heldItem.toolType)
//                {
//                    slot->count += heldItem.count;
//                    heldItem.itemType = ItemType::NONE;
//                    heldItem.cropType = CropType::None;
//                    heldItem.count = 0;
//                }
//                else {
//                    // 서로 다른 아이템이면 교환
//                    InventoryItem temp = *slot;
//                    *slot = heldItem;
//                    heldItem = temp;
//                }
//            }
//            else if (heldItem.itemType == ItemType::CROP)
//            {
//                if (slot->cropType == heldItem.cropType)
//                {
//                    slot->count += heldItem.count;
//                    heldItem.itemType = ItemType::NONE;
//                    heldItem.toolType = Tool::None;
//                    heldItem.count = 0;
//                }
//                else {
//                    // 서로 다른 아이템이면 교환
//                    InventoryItem temp = *slot;
//                    *slot = heldItem;
//                    heldItem = temp;
//                }
//            }
//        }
//        else {
//            // 서로 다른 아이템이면 교환
//            InventoryItem temp = *slot;
//            *slot = heldItem;
//            heldItem = temp;
//        }
//    }
//  
//}
//
//void Box::HandleItemSlotRClick(InventoryItem* slot) //박스 아이템창에서 우클릭
//{
//    if (heldItem.itemType == ItemType::NONE) return; //손에 아이템이 없으면 리턴
//    else {
//        if (slot->itemType == ItemType::NONE) {
//            // 빈 슬롯이면 아이템을 넣고 수량 +1 들고있는 아이템은 -1
//            slot->itemType = heldItem.itemType;
//            slot->cropType = heldItem.cropType;
//            slot->toolType = heldItem.toolType;
//            slot->count++;
//            heldItem.count--;
//            if (heldItem.count < 1) //들고 있는 아이템 수량이 0개 이하일 때 실행
//            {
//                heldItem.itemType = ItemType::NONE;
//                heldItem.cropType = CropType::None;
//                heldItem.toolType = Tool::None;
//                heldItem.count = 0;
//            }
//
//        }
//        else if (slot->itemType == heldItem.itemType) { // 같은 아이템이면 합치기 슬롯에 있는 아이템은 +1 들고 있는 아이템은 -1
//            if (heldItem.itemType == ItemType::TOOL)
//            {
//                if (slot->toolType == heldItem.toolType)
//                {
//                    slot->count++;
//                    heldItem.count--;
//                }
//                else if (heldItem.itemType == ItemType::CROP)
//                {
//                    if (slot->cropType == heldItem.cropType)
//                    {
//                        slot->count++;
//                        heldItem.count--;
//                    }
//                }
//                if (heldItem.count < 1) //들고 있는 아이템 수량이 0개 이하일 때 실행
//                {
//                    heldItem.itemType = ItemType::NONE;
//                    heldItem.cropType = CropType::None;
//                    heldItem.toolType = Tool::None;
//                    heldItem.count = 0;
//                }
//            }
//        }
//    }
//}
//
//std::vector<RECT> Box::GetCollisionRects() const
//{
//    std::vector<RECT> rect;
//    rect.push_back(GetBoundingBox());
//    return rect;
//}
//
//
//
//
//
//
////마우스 클릭 지점 확인(박스 or 플레이어 툴바)
//void Box::HandleClick(int mouseX, int mouseY, int num)
//{
//    int startX = 10;
//    int startY = 100;
//
//    for (int i = 0; i < 3; ++i)  
//    {
//        for (int j = 0; j < 9; ++j)
//        {
//            //슬롯 위치
//            int left = startX + j * (slotSize + 5) + 350;
//            int top = startY + i * 51;
//            int right = left + slotSize;
//            int bottom = top + slotSize;
//
//            if (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom) //클릭한 곳이 박스 슬롯이면 실행
//            {
//                if(num == 1)
//                    HandleItemSlotLClick(&items[i][j]); //마우스로 클릭한 슬롯과 현재 들고 있는 아이템 처리 함수
//                else
//                    HandleItemSlotRClick(&items[i][j]); //마우스로 클릭한 슬롯과 현재 들고 있는 아이템 처리 함수
//
//                return;
//            }
//        }
//    }
//    if (playerToolbar) {
//        int toolbarY = 100 + 3 * 51 + 10; // 상자 아래 여백 포함
//        int startX = 10;
//
//        for (int i = 0; i < 9; ++i) {  //플레이어 툴바 출력을 위한 반복문
//           
//            //슬롯 위치
//            int left = startX + i * (slotSize + 5) + 350;
//            int top = toolbarY;
//            int right = left + slotSize;
//            int bottom = top + slotSize;
//
//            if (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom) { //클릭한 곳이 플레이어 툴바이면 실행
//                if (num == 1)
//                    HandleItemSlotLClick(playerToolbar[i]); //마우스로 클릭한 슬롯과 현재 들고 있는 아이템 처리 함수
//                else
//                    HandleItemSlotRClick(playerToolbar[i]); //마우스로 클릭한 슬롯과 현재 들고 있는 아이템 처리 함수
//                return;
//            }
//        }
//    }
//  
//}


Box::Box()
{
     bmp = BitmapManager::Instance().GetObjectBitmap(ObjectType::Box);
}

void Box::Render(HDC hdc,  int Tilesize)
{
      if (!bmp) return;
        int px = tileX * Tilesize;
        int py = tileY * Tilesize;


        BITMAP bmpInfo;
        GetObject(bmp, sizeof(bmpInfo), &bmpInfo);

        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

        TransparentBlt(hdc,
            px, py, 
            Tilesize, Tilesize,
            memDC,
            0, 0, 
            bmpInfo.bmWidth, bmpInfo.bmHeight,
            RGB(255, 255, 255)
        );
        SelectObject(memDC, oldBmp);
        DeleteDC(memDC);
}

void Box::SetTilePosition(int px, int py) { x = px; y = py; }

ObjectType Box::GetObjectType() const
{
    return ObjectType::Box;
}


  