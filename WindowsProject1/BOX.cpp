#define _CRT_SECURE_NO_WARNINGS
#include "Box.h"
#include "Global.h"
#include "BitmapManager.h"
#include "InputManager.h"
#include "WorldObject.h"
#include "TileData.h"
#include "UIManager.h"
#include "InventoryItem.h"

#include <string>
#include <cstdlib>  // rand()
#include <ctime> 
void Box::RenderUI(HDC hdc)
{
    const int slotSize = 50;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 9; col++) {
            int left = BOX_BASE_X + col * (slotSize + SLOT_MARGIN);
            int top = BOX_BASE_Y + row * (slotSize + 1);

            RECT slotRect = { left, top, left + slotSize, top + slotSize };
            HBRUSH brush = CreateSolidBrush(RGB(200, 200, 200));
            FillRect(hdc, &slotRect, brush);
            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            DeleteObject(brush);

            InventoryItem& item = items[row * 9 + col];
            if (!item.IsEmpty()) {
                HBITMAP bmp = BitmapManager::Instance().GetObjectBitmap(item);
                if (bmp) {
                    HDC memDC = CreateCompatibleDC(hdc);
                    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

                    BITMAP bm;
                    GetObject(bmp, sizeof(BITMAP), &bm);

                    int drawSize = 40;
                    int offsetX = left + (slotSize - drawSize) / 2;
                    int offsetY = top + (slotSize - drawSize) / 2;

                    TransparentBlt(hdc,
                        offsetX, offsetY,
                        drawSize, drawSize,
                        memDC,
                        0, 0,
                        bm.bmWidth, bm.bmHeight,
                        RGB(255, 255, 255));

                    std::string countText = std::to_string(item.GetCount());
                    SetBkMode(hdc, TRANSPARENT);
                    TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), (int)countText.length());

                    SelectObject(memDC, oldBmp);
                    DeleteDC(memDC);
                }
            }
        }
    }

   // RenderCursorItem(hdc);  // 손에 든 아이템은 박스 UI에서도 그리기 유지
}


void Box::RenderSlot(HDC hdc, int left, int top, const InventoryItem& item) {

    RECT slotRect = { left, top, left + SLOT_SIZE, top + SLOT_SIZE };
    HBRUSH brush = CreateSolidBrush(RGB(200, 200, 200));

    FillRect(hdc, &slotRect, brush);
    FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
    DeleteObject(brush);

    if (item.IsEmpty()) return;

    HBITMAP bmp = BitmapManager::Instance().GetObjectBitmap(item);
    if (!bmp) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

    BITMAP bm;
    GetObject(bmp, sizeof(BITMAP), &bm);

    int drawSize = 40;
    int offsetX = left + (SLOT_SIZE - drawSize) / 2;
    int offsetY = top + (SLOT_SIZE - drawSize) / 2;

    TransparentBlt(hdc, offsetX, offsetY, drawSize, drawSize, memDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));

    std::string countText = std::to_string(item.GetCount());
    TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), (int)countText.length());

    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}


void Box::HandleItemSlotLClick(InventoryItem* slot)  //박스를 오픈한 상태에서 좌클릭 
{
    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();

   
    if (heldItem.IsEmpty()) { // 빈손이면 슬롯 아이템을 손에 든다
        UIManager::Instance().SetHeldItem(*slot);
        *slot = InventoryItem();  // 슬롯 비우기
    }
    else {
        
        if (slot->IsEmpty()) {// 손에 아이템 있고 슬롯이 비어 있으면 옮긴다
            *slot = heldItem;
            UIManager::Instance().ClearHeldItem();
        }
        else if (slot->GetCategory() == heldItem.GetCategory()) {// 타입이 같을 때
            
            bool canStack = false;

            switch (heldItem.GetCategory())// 세부 타입 비교 
            {
            case ItemCategory::Tool:   //도구
                canStack = (slot->GetToolType() == heldItem.GetToolType());
                break;
            case ItemCategory::Crop:  //작물
                canStack = (slot->GetCropType() == heldItem.GetCropType());
                break;
            case ItemCategory::Seed:  //씨앗봉투
                canStack = (slot->GetSeedType() == heldItem.GetSeedType());
                break;
            case ItemCategory::Placeable:  //배치 가능한 것들
                canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
                break;
            default:
                canStack = false;
                break;
            }

            if (canStack) {
                slot->SetCount(slot->GetCount() + heldItem.GetCount());
                UIManager::Instance().ClearHeldItem();  //들고있는 아이템 초기화// 손 초기화
            }
            else {
                std::swap(*slot, heldItem);  // 다른 세부 타입이면 교환
            }
        }
        else {
            // 아이템 카테고리가 다르면 그냥 교환
            std::swap(*slot, heldItem);
        }
    }
}


void Box::HandleItemSlotRClick(InventoryItem* slot)  //박스를 오픈한 상태에서 우클릭
{
    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();
    if (slot->IsEmpty()) {// 손에 아이템 있고 슬롯이 비어 있으면 1개를 옮긴다
        /* *slot = heldItem;
         UIManager::Instance().ClearHeldItem();*/
        OutputDebugStringA("아이템 shgrl\n");
        *slot = heldItem;  //아이템 정보를 넘겨주고  개수를 1개로 설정
        if (slot->GetCount() != 0)slot->SetCount(1);
        else   slot->AddCount(1);
        heldItem.DecreaseItem(1);
        if (heldItem.GetCount() <= 0) UIManager::Instance().ClearHeldItem();  //손에 있는 아이템 개수가 0이하로 떨어지면 손 초기화 

    }
    else if (slot->GetCategory() == heldItem.GetCategory())
    {
        bool canStack = false;
        OutputDebugStringA("gkqclrl rksmd\n");

        switch (heldItem.GetCategory())
        {
        case ItemCategory::Tool:   //도구
            canStack = (slot->GetToolType() == heldItem.GetToolType());
            break;
        case ItemCategory::Crop:  //작물
            canStack = (slot->GetCropType() == heldItem.GetCropType());
            break;
        case ItemCategory::Seed:  //씨앗봉투
            canStack = (slot->GetSeedType() == heldItem.GetSeedType());
            break;
        case ItemCategory::Placeable:  //배치 가능한 것들
            canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
            break;
        default:
            canStack = false;
            break;


          
        }
        if (canStack) {
            slot->AddCount(1);
            heldItem.DecreaseItem(1);

            if (heldItem.GetCount() <= 0) UIManager::Instance().ClearHeldItem();  //들고있는 아이템 초기화// 손 초기화
        }

    }
        //else if (slot->GetCategory() == heldItem.GetCategory()) {// 타입이 같을 때

        //    bool canStack = false;

        //    switch (heldItem.GetCategory())// 세부 타입 비교 
        //    {
        //    case ItemCategory::Tool:   //도구
        //        canStack = (slot->GetToolType() == heldItem.GetToolType());
        //        break;
        //    case ItemCategory::Crop:  //작물
        //        canStack = (slot->GetCropType() == heldItem.GetCropType());
        //        break;
        //    case ItemCategory::Seed:  //씨앗봉투
        //        canStack = (slot->GetSeedType() == heldItem.GetSeedType());
        //        break;
        //    case ItemCategory::Placeable:  //배치 가능한 것들
        //        canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
        //        break;
        //    default:
        //        canStack = false;
        //        break;
        //    }

        //    if (canStack) {
        //        slot->SetCount(slot->GetCount() + heldItem.GetCount());
        //        UIManager::Instance().ClearHeldItem();  //들고있는 아이템 초기화// 손 초기화
        //    }
        //    else {
        //        std::swap(*slot, heldItem);  // 다른 세부 타입이면 교환
        //    }
        //}
        //else {
        //    // 아이템 카테고리가 다르면 그냥 교환
        //    std::swap(*slot, heldItem);
        //}
    }

////클릭된 아이템이 커서에 붙게 하는 함수
void Box::RenderCursorItem(HDC hdc) {
    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();
    if (heldItem.IsEmpty()) return;

    POINT mouse = InputManager::Instance().GetMousePosition();
    HBITMAP bmp = BitmapManager::Instance().GetObjectBitmap(heldItem);
    if (!bmp) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

    BITMAP bm;
    GetObject(bmp, sizeof(BITMAP), &bm);

    int drawSize = 40;
    TransparentBlt(hdc, mouse.x - 20, mouse.y - 20, drawSize, drawSize,
        memDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));

    if (heldItem.GetCount() > 1) {
        std::string countText = std::to_string(heldItem.GetCount());
        TextOutA(hdc, mouse.x + 5, mouse.y + 10, countText.c_str(), (int)countText.length());
    }

    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}


bool Box::HandleClick(int mouseX, int mouseY, int num) //num 1 좌클 2 우클
{
    // 박스 슬롯 클릭 처리
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 9; ++col) {
            int left = BOX_BASE_X + col * (SLOT_SIZE + SLOT_MARGIN);
            int top = BOX_BASE_Y + row * (SLOT_SIZE + 1);
            int right = left + SLOT_SIZE;
            int bottom = top + SLOT_SIZE;

            if (mouseX >= left && mouseX <= right &&
                mouseY >= top && mouseY <= bottom) {
                int index = row * 9 + col;
                if (num == 1)
                    HandleItemSlotLClick(&items[index]);
                else
                    HandleItemSlotRClick(&items[index]);
                return true;
            }
        }
    }

    // 플레이어 툴바 클릭 영역 처리 유지
    if (playerToolbar) {
        for (int i = 0; i < 9; ++i) {
            int left = BOX_BASE_X + i * (SLOT_SIZE + SLOT_MARGIN);
            int top = TOOLBAR_Y;  // 플레이어 툴바 Y 위치
            int right = left + SLOT_SIZE;
            int bottom = top + SLOT_SIZE;

            if (mouseX >= left && mouseX <= right &&
                mouseY >= top && mouseY <= bottom) {
                if (num == 1)
                    HandleItemSlotLClick(&playerToolbar[i]);
                else
                    HandleItemSlotRClick(&playerToolbar[i]);
                return true;
            }
        }
    }
    return false;
}

Box::Box()
{
    bmp = BitmapManager::Instance().GetObjectBitmap(PlaceableType::Box);
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // 시드 설정

    for (int i = 0; i < 27; i++)  //아이템 랜덤으로 넣음
    {
        int typeIndex = 1 + rand() % 3;     // 1: Tool, 2: Seed, 3: Placeable
        int count = 1 + rand() % 5;         // 1~5개

        InventoryItem item;

        switch (typeIndex)
        {
        case 1: // ToolType
        {
            int max = 3; // Hoe, Axe, Watering
            ToolType tool = static_cast<ToolType>(1 + rand() % max); // 1~3
            item = InventoryItem(tool, count);
            break;
        }
        case 2: // SeedType
        {
            int max = 2; // StrawberrySeed, OnionSeed
            SeedType seed = static_cast<SeedType>(1 + rand() % max); // 1~2
            item = InventoryItem(seed, count);
            break;
        }
        case 3: // PlaceableType
        {
            int max = 6; // Box ~ Crop (None 제외)
            PlaceableType placeable = static_cast<PlaceableType>(1 + rand() % max); // 1~5
            item = InventoryItem(placeable, count);
            break;
        }
        }

        AddItem(i, item);
    }
}


void Box::Render(HDC hdc, int Tilesize)
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
    //박스 충돌영역
    if (g_bFenceRedFrameOn)
    {
        RECT r;
        r.left = px + 5;
        r.top = py + 5;
        r.right = r.left + 20;
        r.bottom = r.top + 20;
        HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hdc, &r, red);
        DeleteObject(red);
        //상호작용
        r.left = px;
        r.top = py;
        r.right = r.left + 32;
        r.bottom = r.top + 32;
        HBRUSH green = CreateSolidBrush(RGB(0, 255, 0));
        FrameRect(hdc, &r, green);
        DeleteObject(green);
    }



    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}

void Box::SetTilePosition(int px, int py) { x = px; y = py; }

PlaceableType Box::GetPlaceableType() const
{
    return PlaceableType::Box;
}

RECT Box::GetCollisionRect()
{
    return RECT();
}




void Box::AddItem(int slotIndex, const InventoryItem& item) {
    if (slotIndex >= 0 && slotIndex < 27) {  // 27 슬롯 범위 검사
        items[slotIndex] = item;
    }
}

void Box::SetPlayerToolbar(InventoryItem* toolbar)
{
    playerToolbar = toolbar;
}

void Box::OnInteract(Player* player)
{
    UIManager::Instance().OpenBoxUI(this, 27, player->GetInventory(), 9);  //  UIManager는 표현만 담당
}

void Box::Open()
{
    isOpen = TRUE;
}

void Box::Close()
{
    isOpen = FALSE;

}

bool Box::IsOpen() const
{
    return isOpen;
}

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
//InventoryItem& UIManager::GetHeldItem() {
//    return heldItem; // heldItem은 InventoryItem 타입
//}
//
//void UIManager::SetHeldItem(const InventoryItem& item) {
//    heldItem = item;
//}
//
//void UIManager::ClearHeldItem() {
//    heldItem = InventoryItem(); // 기본 생성자로 비우기
//}


        // startX = 10;
        // startY = 100 + 3 * 51 + 10;  // 상자 아래 여백 10

        //for (int i = 0; i < 9; i++) {
        //    RECT slotRect = {
        //        startX + i * (slotSize + 5) + 350,
        //        startY,
        //        startX + i * (slotSize + 5) + slotSize + 350,
        //        startY + slotSize
        //    };

        //    HBRUSH brush = CreateSolidBrush(RGB(180, 180, 180));
        //    FillRect(hdc, &slotRect, brush);
        //    FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        //    DeleteObject(brush);
        //    if (playerToolbar[i]->itemType != ItemType::NONE) {
        //        HBITMAP bmp = BitmapManager::Instance().GetBitmapForCrop(*playerToolbar[i]);

        //        if (!bmp) return;
        //        if (bmp) {
        //            HDC memDC = CreateCompatibleDC(hdc);
        //            HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
        //            BITMAP bm;
        //            GetObject(bmp, sizeof(BITMAP), &bm);

        //            int drawSize = 40;
        //            int offsetX = slotRect.left + (slotSize - drawSize) / 2;
        //            int offsetY = slotRect.top + (slotSize - drawSize) / 2;

        //            TransparentBlt(hdc, offsetX, offsetY,
        //                drawSize, drawSize,
        //                memDC, 0, 0,
        //                bm.bmWidth, bm.bmHeight,
        //                RGB(255, 255, 255));

        //            std::string countText = std::to_string(playerToolbar[i]->count);
        //            TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
        //            SelectObject(memDC, oldBmp);
        //            DeleteDC(memDC);
        //        }
        //    }
        //}
        //RenderCursorItem(hdc);


// 
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
//마우스 클릭 지점 확인(박스 or 플레이어 툴바)


//std::vector<RECT> Box::GetCollisionRects() const
//{
//    RECT r;
//    r.left = tileX * 32 + 5;
//    r.top = tileY * 32 + 5;
//    r.right = r.left + 20;
//    r.bottom = r.top + 20;
//    return { r };
//}

//std::vector<RECT> Box::GetCollisionRects() const
//{
//        RECT r;
//        r.left = static_cast<int>(x * 32);
//        r.top = static_cast<int>(y * 32);
//        r.right = r.left + 32;
//        r.bottom = r.top + 32;
//        return { r };
//}

//void Box::Interact(Player& player)  {
//    if (isOpen) Close();
//    else Open();
//}
