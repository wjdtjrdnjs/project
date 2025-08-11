//#define _CRT_SECURE_NO_WARNINGS
//#include "Global.h"
//#include "BitmapManager.h"
//#include "InputManager.h"
//#include "WorldObject.h"
//#include "TileData.h"
//#include "UIManager.h"
//#include "InventoryItem.h"
//
//#include <string>
//void NPC::RenderUI(HDC hdc) {
//    const int slotSize = SLOT_SIZE;
//
//    // NPC 인벤토리 그리기
//    for (int row = 0; row < SLOT_ROWS; ++row) {
//        for (int col = 0; col < SLOT_COLS; ++col) {
//            int left = UI_BASE_X + col * (slotSize + SLOT_MARGIN);
//            int top = UI_BASE_Y + row * (slotSize + SLOT_MARGIN);
//            int index = row * SLOT_COLS + col;
//
//            RenderSlot(hdc, left, top, items[index]);
//        }
//    }
//
//   
//    // 마우스에 든 아이템 그리기
//    RenderCursorItem(hdc);
//}
//
//
//
//void NPC::RenderSlot(HDC hdc, int left, int top, const InventoryItem& item) {
//
//    RECT slotRect = { left, top, left + SLOT_SIZE, top + SLOT_SIZE };
//    HBRUSH brush = CreateSolidBrush(RGB(200, 200, 200));
//
//    FillRect(hdc, &slotRect, brush);
//    FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
//    DeleteObject(brush);
//
//    if (item.IsEmpty()) return;
//
//    HBITMAP bmp = BitmapManager::Instance().GetObjectBitmap(item);
//    if (!bmp) return;
//
//    HDC memDC = CreateCompatibleDC(hdc);
//    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
//
//    BITMAP bm;
//    GetObject(bmp, sizeof(BITMAP), &bm);
//
//    int drawSize = 40;
//    int offsetX = left + (SLOT_SIZE - drawSize) / 2;
//    int offsetY = top + (SLOT_SIZE - drawSize) / 2;
//
//    TransparentBlt(hdc, offsetX, offsetY, drawSize, drawSize, memDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));
//
//    std::string countText = std::to_string(item.GetCount());
//    TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), (int)countText.length());
//
//    SelectObject(memDC, oldBmp);
//    DeleteDC(memDC);
//}
//
//
//void NPC::HandleItemSlotLClick(InventoryItem* slot)  //박스를 오픈한 상태에서 좌클릭 
//{
//    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();
//
//
//    if (heldItem.IsEmpty()) { // 빈손이면 슬롯 아이템을 손에 든다
//        UIManager::Instance().SetHeldItem(*slot);
//        *slot = InventoryItem();  // 슬롯 비우기
//    }
//    else {
//
//        if (slot->IsEmpty()) {// 손에 아이템 있고 슬롯이 비어 있으면 옮긴다
//            *slot = heldItem;
//            UIManager::Instance().ClearHeldItem();
//        }
//        else if (slot->GetCategory() == heldItem.GetCategory()) {// 타입이 같을 때
//
//            bool canStack = false;
//
//            switch (heldItem.GetCategory())// 세부 타입 비교 
//            {
//            case ItemCategory::Tool:   //도구
//                canStack = (slot->GetToolType() == heldItem.GetToolType());
//                break;
//            case ItemCategory::Crop:  //작물
//                canStack = (slot->GetCropType() == heldItem.GetCropType());
//                break;
//            case ItemCategory::Seed:  //씨앗봉투
//                canStack = (slot->GetSeedType() == heldItem.GetSeedType());
//                break;
//            case ItemCategory::Placeable:  //배치 가능한 것들
//                canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
//                break;
//            default:
//                canStack = false;
//                break;
//            }
//
//            if (canStack) {
//                slot->SetCount(slot->GetCount() + heldItem.GetCount());
//                UIManager::Instance().ClearHeldItem();  //들고있는 아이템 초기화// 손 초기화
//            }
//            else {
//                std::swap(*slot, heldItem);  // 다른 세부 타입이면 교환
//            }
//        }
//        else {
//            // 아이템 카테고리가 다르면 그냥 교환
//            std::swap(*slot, heldItem);
//        }
//    }
//}
//
//
//void NPC::HandleItemSlotRClick(InventoryItem* slot)  //박스를 오픈한 상태에서 우클릭
//{
//    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();
//    if (slot->IsEmpty()) {// 손에 아이템 있고 슬롯이 비어 있으면 1개를 옮긴다
//        /* *slot = heldItem;
//         UIManager::Instance().ClearHeldItem();*/
//        OutputDebugStringA("아이템 shgrl\n");
//        *slot = heldItem;  //아이템 정보를 넘겨주고  개수를 1개로 설정
//        if (slot->GetCount() != 0)slot->SetCount(1);
//        else   slot->AddCount(1);
//        heldItem.DecreaseItem(1);
//        if (heldItem.GetCount() <= 0) UIManager::Instance().ClearHeldItem();  //손에 있는 아이템 개수가 0이하로 떨어지면 손 초기화 
//
//    }
//    else if (slot->GetCategory() == heldItem.GetCategory())
//    {
//        bool canStack = false;
//        OutputDebugStringA("gkqclrl rksmd\n");
//
//        switch (heldItem.GetCategory())
//        {
//        case ItemCategory::Tool:   //도구
//            canStack = (slot->GetToolType() == heldItem.GetToolType());
//            break;
//        case ItemCategory::Crop:  //작물
//            canStack = (slot->GetCropType() == heldItem.GetCropType());
//            break;
//        case ItemCategory::Seed:  //씨앗봉투
//            canStack = (slot->GetSeedType() == heldItem.GetSeedType());
//            break;
//        case ItemCategory::Placeable:  //배치 가능한 것들
//            canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
//            break;
//        default:
//            canStack = false;
//            break;
//
//
//
//        }
//        if (canStack) {
//            slot->AddCount(1);
//            heldItem.DecreaseItem(1);
//
//            if (heldItem.GetCount() <= 0) UIManager::Instance().ClearHeldItem();  //들고있는 아이템 초기화// 손 초기화
//        }
//
//    }
//    //else if (slot->GetCategory() == heldItem.GetCategory()) {// 타입이 같을 때
//
//    //    bool canStack = false;
//
//    //    switch (heldItem.GetCategory())// 세부 타입 비교 
//    //    {
//    //    case ItemCategory::Tool:   //도구
//    //        canStack = (slot->GetToolType() == heldItem.GetToolType());
//    //        break;
//    //    case ItemCategory::Crop:  //작물
//    //        canStack = (slot->GetCropType() == heldItem.GetCropType());
//    //        break;
//    //    case ItemCategory::Seed:  //씨앗봉투
//    //        canStack = (slot->GetSeedType() == heldItem.GetSeedType());
//    //        break;
//    //    case ItemCategory::Placeable:  //배치 가능한 것들
//    //        canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
//    //        break;
//    //    default:
//    //        canStack = false;
//    //        break;
//    //    }
//
//    //    if (canStack) {
//    //        slot->SetCount(slot->GetCount() + heldItem.GetCount());
//    //        UIManager::Instance().ClearHeldItem();  //들고있는 아이템 초기화// 손 초기화
//    //    }
//    //    else {
//    //        std::swap(*slot, heldItem);  // 다른 세부 타입이면 교환
//    //    }
//    //}
//    //else {
//    //    // 아이템 카테고리가 다르면 그냥 교환
//    //    std::swap(*slot, heldItem);
//    //}
//}
//
//////클릭된 아이템이 커서에 붙게 하는 함수
//void NPC::RenderCursorItem(HDC hdc) {
//    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();
//    if (heldItem.IsEmpty()) return;
//
//    POINT mouse = InputManager::Instance().GetMousePosition();
//    HBITMAP bmp = BitmapManager::Instance().GetObjectBitmap(heldItem);
//    if (!bmp) return;
//
//    HDC memDC = CreateCompatibleDC(hdc);
//    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
//
//    BITMAP bm;
//    GetObject(bmp, sizeof(BITMAP), &bm);
//
//    int drawSize = 40;
//    TransparentBlt(hdc, mouse.x - 20, mouse.y - 20, drawSize, drawSize,
//        memDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));
//
//    if (heldItem.GetCount() > 1) {
//        std::string countText = std::to_string(heldItem.GetCount());
//        TextOutA(hdc, mouse.x + 5, mouse.y + 10, countText.c_str(), (int)countText.length());
//    }
//
//    SelectObject(memDC, oldBmp);
//    DeleteDC(memDC);
//}
//
//
//bool NPC::HandleClick(int mouseX, int mouseY, int num) //num 1 좌클 2 우클
//{
//    // 박스 슬롯 클릭 처리
//    for (int row = 0; row < 3; ++row) {
//        for (int col = 0; col < 9; ++col) {
//            int left = NPC_BASE_X + col * (SLOT_SIZE + SLOT_MARGIN);
//            int top = NPC_BASE_Y + row * (SLOT_SIZE + 1);
//            int right = left + SLOT_SIZE;
//            int bottom = top + SLOT_SIZE;
//
//            if (mouseX >= left && mouseX <= right &&
//                mouseY >= top && mouseY <= bottom) {
//                int index = row * 9 + col;
//                if (num == 1)
//                    HandleItemSlotLClick(&items[index]);
//                else
//                    HandleItemSlotRClick(&items[index]);
//                return true;
//            }
//        }
//    }
//
//    // 플레이어 툴바 클릭 영역 처리 유지
//    if (playerToolbar) {
//        for (int i = 0; i < 9; ++i) {
//            int left = NPC_BASE_X + i * (SLOT_SIZE + SLOT_MARGIN);
//            int top = TOOLBAR_Y;  // 플레이어 툴바 Y 위치
//            int right = left + SLOT_SIZE;
//            int bottom = top + SLOT_SIZE;
//
//            if (mouseX >= left && mouseX <= right &&
//                mouseY >= top && mouseY <= bottom) {
//                if (num == 1)
//                    HandleItemSlotLClick(&playerToolbar[i]);
//                else
//                    HandleItemSlotRClick(&playerToolbar[i]);
//                return true;
//            }
//        }
//    }
//    return false;
//}
//
//NPC::NPC()
//{
//    bmp = BitmapManager::Instance().GetObjectBitmap(PlaceableType::NPC);
//    std::srand(static_cast<unsigned int>(std::time(nullptr))); // 시드 설정
//
//    for (int i = 0; i < 27; i++)  //아이템 랜덤으로 넣음
//    {
//        int typeIndex = 1 + rand() % 3;     // 1: Tool, 2: Seed, 3: Placeable
//        int count = 1 + rand() % 5;         // 1~5개
//
//        InventoryItem item;
//
//        switch (typeIndex)
//        {
//        case 1: // ToolType
//        {
//            int max = 3; // Hoe, Axe, Watering
//            ToolType tool = static_cast<ToolType>(1 + rand() % max); // 1~3
//            item = InventoryItem(tool, count);
//            break;
//        }
//        case 2: // SeedType
//        {
//            int max = 2; // StrawberrySeed, OnionSeed
//            SeedType seed = static_cast<SeedType>(1 + rand() % max); // 1~2
//            item = InventoryItem(seed, count);
//            break;
//        }
//        case 3: // PlaceableType
//        {
//            int max = 5; // NPC ~ Crop (None 제외)
//            PlaceableType placeable = static_cast<PlaceableType>(1 + rand() % max); // 1~5
//            item = InventoryItem(placeable, count);
//            break;
//        }
//        }
//
//        AddItem(i, item);
//    }
//}
//
//
//void NPC::Render(HDC hdc, int Tilesize)
//{
//    if (!bmp) return;
//    int px = tileX * Tilesize;
//    int py = tileY * Tilesize;
//
//
//    BITMAP bmpInfo;
//    GetObject(bmp, sizeof(bmpInfo), &bmpInfo);
//
//    HDC memDC = CreateCompatibleDC(hdc);
//    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
//
//    TransparentBlt(hdc,
//        px, py,
//        Tilesize, Tilesize,
//        memDC,
//        0, 0,
//        bmpInfo.bmWidth, bmpInfo.bmHeight,
//        RGB(255, 255, 255)
//    );
//    //박스 충돌영역
//    if (g_bFenceRedFrameOn)
//    {
//        RECT r;
//        r.left = px + 5;
//        r.top = py + 5;
//        r.right = r.left + 20;
//        r.bottom = r.top + 20;
//        HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
//        FrameRect(hdc, &r, red);
//        DeleteObject(red);
//        //상호작용
//        r.left = px;
//        r.top = py;
//        r.right = r.left + 32;
//        r.bottom = r.top + 32;
//        HBRUSH green = CreateSolidBrush(RGB(0, 255, 0));
//        FrameRect(hdc, &r, green);
//        DeleteObject(green);
//    }
//
//
//
//    SelectObject(memDC, oldBmp);
//    DeleteDC(memDC);
//}
//
//void NPC::SetTilePosition(int px, int py) { x = px; y = py; }
//
//PlaceableType NPC::GetPlaceableType() const
//{
//    return PlaceableType::NPC;
//}
//
//RECT NPC::GetCollisionRect()
//{
//    return RECT();
//}
//
//
//
//
//void NPC::AddItem(int slotIndex, const InventoryItem& item) {
//    if (slotIndex >= 0 && slotIndex < 27) {  // 27 슬롯 범위 검사
//        items[slotIndex] = item;
//    }
//}
//
//void NPC::SetPlayerToolbar(InventoryItem* toolbar)
//{
//    playerToolbar = toolbar;
//}
//
//void NPC::OnInteract(Player* player)
//{
//
//    UIManager::Instance().OpenNPCUI(this, 27, player->GetInventory(), 9);  //  UIManager는 표현만 담당
//}
//
//void NPC::Open()
//{
//    isOpen = TRUE;
//}
//
//void NPC::Close()
//{
//    isOpen = FALSE;
//
//}
//
//bool NPC::IsOpen() const
//{
//    return isOpen;
//}
//
