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
//#include "Global.h" //�浹���� on/off
//
//Box::Box(int xPos, int yPos) : x(xPos), y(yPos), isOpen(false)
//{
//    //��ġ
//    iconRect.left = x;
//    iconRect.top = y;
//    iconRect.right = x +  tileSize * 3;
//    iconRect.bottom = y + tileSize * 3;
//
//    // ��Ʈ�� �ε� 
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
//    items[0][0].cropType = CropType::Strawberry_1; //1�� ��������� 5��
//    items[0][0].count = 99;
//
//    items[0][1].itemType = ItemType::CROP;
//    items[0][1].cropType = CropType::Onion_1;      //2�� ���ĺ��� 5��
//    items[0][1].count = 99;
//
//    items[0][2].itemType = ItemType::CROP;
//    items[0][2].cropType = CropType::Fence;        //��Ÿ��
//    items[0][2].count = 99;
//
//    items[0][3].itemType = ItemType::TOOL;
//    items[0][3].toolType = Tool::Axe;       //����
//    items[0][3].count = 1;
//}
//bool Box::IsPlayerInRange(int playerX, int playerY) {  //�÷��̾ �ڽ� Ÿ�� �ֺ��� �ִ� �� Ȯ��
//    int playerTileX = playerX / tileSize;
//    int playerTileY = playerY / tileSize;
//    int BoxTileX = x / tileSize;
//    int BoxTileY = y / tileSize;
//
//    return abs(playerTileX - BoxTileX) <= 1 &&   // -1,0,1 ����
//        abs(playerTileY - BoxTileY) <= 1;
//}
//
//
//bool Box::IsMouseOverIcon(int mouseX, int mouseY) { //���콺 Ŀ���� ���ھ����� ���� �ִ��� Ȯ��
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
//RECT Box::GetBoundingBox()const //���� �浹 ����
//{
//    BITMAP bmpInfo;
//    GetObject(hIconBitmap, sizeof(BITMAP), &bmpInfo);
//
//    RECT rect;
//    rect.left = x + 5;  // ��
//    rect.top = y;        //��
//    rect.right = rect.left + bmpInfo.bmWidth +10; //������
//    rect.bottom = rect.top + bmpInfo.bmHeight + 10; //�Ʒ�
//
//    return rect;
//}
//
//void Box::SetPlayerToolbar(InventoryItem* toolbar)
//{
//    for (int i = 0; i < 9; i++)
//    {
//        playerToolbar[i] = &toolbar[i];  //�ڽ� �ȿ��� ��ȯ�� �̷�����Ƿ� �ּҰ��� ������
//    }
//  
//}
//
//void Box::SetPlayerNear(bool ch) //�÷��̾ �ڽ� ��ó�� ���� ��
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
//            brush = CreateSolidBrush(RGB(200, 200, 200)); // �⺻ ��
//
//            RECT slotRect = { startX + i * (slotSize + 5) + 350, startY + y * 51, startX + i * (slotSize + 5) + slotSize + 350, startY + slotSize + y * 51 };
//
//            FillRect(hdc, &slotRect, brush);
//            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // �׵θ�
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
//         startY = 100 + 3 * 51 + 10;  // ���� �Ʒ� ���� 10
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
////Ŭ���� �������� Ŀ���� �ٰ� �ϴ� �Լ�
//void Box::RenderCursorItem(HDC hdc) { 
//    if (heldItem.itemType == ItemType::NONE) return; // �ƹ��͵� �� ��� ������ ���ư�
//
//    POINT mouse = InputManager::Instance().GetMousePosition();  //Ŭ���� ��ǥ�� ������
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
//    if (heldItem.count > 0) { //������ ������ 1�� �̻��� �� ���� ǥ�� 
//        std::string countText = std::to_string(heldItem.count);
//        TextOutA(hdc, mouse.x + 5, mouse.y + 10, countText.c_str(), countText.length());
//    }
//
//    SelectObject(memDC, oldBmp);
//    DeleteDC(memDC);
//}
//
///////////////////�ڵ� ����////////////////
// //���콺�� Ŭ���� ���԰� ���� ��� �ִ� ������ ó�� �Լ�
//void Box::HandleItemSlotLClick(InventoryItem* slot)  //��Ŭ��
//{
//
//    if (heldItem.itemType == ItemType::NONE) {
//        // ����̸� ������ �������� ���
//        heldItem = *slot;
//        slot->itemType = ItemType::NONE;
//        slot->cropType = CropType::None;
//        slot->toolType = Tool::None;
//        slot->count = 0;
//    }
//    else {
//        if (slot->itemType == ItemType::NONE) {
//            // �� �����̸� �������� �ִ´�
//            *slot = heldItem;
//            heldItem.itemType = ItemType::NONE;
//            heldItem.cropType = CropType::None;
//            heldItem.toolType = Tool::None;
//            heldItem.count = 0;
//        }
//        else if (slot->itemType == heldItem.itemType) {
//            // ���� �������̸� ��ġ��
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
//                    // ���� �ٸ� �������̸� ��ȯ
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
//                    // ���� �ٸ� �������̸� ��ȯ
//                    InventoryItem temp = *slot;
//                    *slot = heldItem;
//                    heldItem = temp;
//                }
//            }
//        }
//        else {
//            // ���� �ٸ� �������̸� ��ȯ
//            InventoryItem temp = *slot;
//            *slot = heldItem;
//            heldItem = temp;
//        }
//    }
//  
//}
//
//void Box::HandleItemSlotRClick(InventoryItem* slot) //�ڽ� ������â���� ��Ŭ��
//{
//    if (heldItem.itemType == ItemType::NONE) return; //�տ� �������� ������ ����
//    else {
//        if (slot->itemType == ItemType::NONE) {
//            // �� �����̸� �������� �ְ� ���� +1 ����ִ� �������� -1
//            slot->itemType = heldItem.itemType;
//            slot->cropType = heldItem.cropType;
//            slot->toolType = heldItem.toolType;
//            slot->count++;
//            heldItem.count--;
//            if (heldItem.count < 1) //��� �ִ� ������ ������ 0�� ������ �� ����
//            {
//                heldItem.itemType = ItemType::NONE;
//                heldItem.cropType = CropType::None;
//                heldItem.toolType = Tool::None;
//                heldItem.count = 0;
//            }
//
//        }
//        else if (slot->itemType == heldItem.itemType) { // ���� �������̸� ��ġ�� ���Կ� �ִ� �������� +1 ��� �ִ� �������� -1
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
//                if (heldItem.count < 1) //��� �ִ� ������ ������ 0�� ������ �� ����
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
////���콺 Ŭ�� ���� Ȯ��(�ڽ� or �÷��̾� ����)
//void Box::HandleClick(int mouseX, int mouseY, int num)
//{
//    int startX = 10;
//    int startY = 100;
//
//    for (int i = 0; i < 3; ++i)  
//    {
//        for (int j = 0; j < 9; ++j)
//        {
//            //���� ��ġ
//            int left = startX + j * (slotSize + 5) + 350;
//            int top = startY + i * 51;
//            int right = left + slotSize;
//            int bottom = top + slotSize;
//
//            if (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom) //Ŭ���� ���� �ڽ� �����̸� ����
//            {
//                if(num == 1)
//                    HandleItemSlotLClick(&items[i][j]); //���콺�� Ŭ���� ���԰� ���� ��� �ִ� ������ ó�� �Լ�
//                else
//                    HandleItemSlotRClick(&items[i][j]); //���콺�� Ŭ���� ���԰� ���� ��� �ִ� ������ ó�� �Լ�
//
//                return;
//            }
//        }
//    }
//    if (playerToolbar) {
//        int toolbarY = 100 + 3 * 51 + 10; // ���� �Ʒ� ���� ����
//        int startX = 10;
//
//        for (int i = 0; i < 9; ++i) {  //�÷��̾� ���� ����� ���� �ݺ���
//           
//            //���� ��ġ
//            int left = startX + i * (slotSize + 5) + 350;
//            int top = toolbarY;
//            int right = left + slotSize;
//            int bottom = top + slotSize;
//
//            if (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom) { //Ŭ���� ���� �÷��̾� �����̸� ����
//                if (num == 1)
//                    HandleItemSlotLClick(playerToolbar[i]); //���콺�� Ŭ���� ���԰� ���� ��� �ִ� ������ ó�� �Լ�
//                else
//                    HandleItemSlotRClick(playerToolbar[i]); //���콺�� Ŭ���� ���԰� ���� ��� �ִ� ������ ó�� �Լ�
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


  