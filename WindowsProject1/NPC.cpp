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
//    // NPC �κ��丮 �׸���
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
//    // ���콺�� �� ������ �׸���
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
//void NPC::HandleItemSlotLClick(InventoryItem* slot)  //�ڽ��� ������ ���¿��� ��Ŭ�� 
//{
//    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();
//
//
//    if (heldItem.IsEmpty()) { // ����̸� ���� �������� �տ� ���
//        UIManager::Instance().SetHeldItem(*slot);
//        *slot = InventoryItem();  // ���� ����
//    }
//    else {
//
//        if (slot->IsEmpty()) {// �տ� ������ �ְ� ������ ��� ������ �ű��
//            *slot = heldItem;
//            UIManager::Instance().ClearHeldItem();
//        }
//        else if (slot->GetCategory() == heldItem.GetCategory()) {// Ÿ���� ���� ��
//
//            bool canStack = false;
//
//            switch (heldItem.GetCategory())// ���� Ÿ�� �� 
//            {
//            case ItemCategory::Tool:   //����
//                canStack = (slot->GetToolType() == heldItem.GetToolType());
//                break;
//            case ItemCategory::Crop:  //�۹�
//                canStack = (slot->GetCropType() == heldItem.GetCropType());
//                break;
//            case ItemCategory::Seed:  //���Ѻ���
//                canStack = (slot->GetSeedType() == heldItem.GetSeedType());
//                break;
//            case ItemCategory::Placeable:  //��ġ ������ �͵�
//                canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
//                break;
//            default:
//                canStack = false;
//                break;
//            }
//
//            if (canStack) {
//                slot->SetCount(slot->GetCount() + heldItem.GetCount());
//                UIManager::Instance().ClearHeldItem();  //����ִ� ������ �ʱ�ȭ// �� �ʱ�ȭ
//            }
//            else {
//                std::swap(*slot, heldItem);  // �ٸ� ���� Ÿ���̸� ��ȯ
//            }
//        }
//        else {
//            // ������ ī�װ��� �ٸ��� �׳� ��ȯ
//            std::swap(*slot, heldItem);
//        }
//    }
//}
//
//
//void NPC::HandleItemSlotRClick(InventoryItem* slot)  //�ڽ��� ������ ���¿��� ��Ŭ��
//{
//    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();
//    if (slot->IsEmpty()) {// �տ� ������ �ְ� ������ ��� ������ 1���� �ű��
//        /* *slot = heldItem;
//         UIManager::Instance().ClearHeldItem();*/
//        OutputDebugStringA("������ shgrl\n");
//        *slot = heldItem;  //������ ������ �Ѱ��ְ�  ������ 1���� ����
//        if (slot->GetCount() != 0)slot->SetCount(1);
//        else   slot->AddCount(1);
//        heldItem.DecreaseItem(1);
//        if (heldItem.GetCount() <= 0) UIManager::Instance().ClearHeldItem();  //�տ� �ִ� ������ ������ 0���Ϸ� �������� �� �ʱ�ȭ 
//
//    }
//    else if (slot->GetCategory() == heldItem.GetCategory())
//    {
//        bool canStack = false;
//        OutputDebugStringA("gkqclrl rksmd\n");
//
//        switch (heldItem.GetCategory())
//        {
//        case ItemCategory::Tool:   //����
//            canStack = (slot->GetToolType() == heldItem.GetToolType());
//            break;
//        case ItemCategory::Crop:  //�۹�
//            canStack = (slot->GetCropType() == heldItem.GetCropType());
//            break;
//        case ItemCategory::Seed:  //���Ѻ���
//            canStack = (slot->GetSeedType() == heldItem.GetSeedType());
//            break;
//        case ItemCategory::Placeable:  //��ġ ������ �͵�
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
//            if (heldItem.GetCount() <= 0) UIManager::Instance().ClearHeldItem();  //����ִ� ������ �ʱ�ȭ// �� �ʱ�ȭ
//        }
//
//    }
//    //else if (slot->GetCategory() == heldItem.GetCategory()) {// Ÿ���� ���� ��
//
//    //    bool canStack = false;
//
//    //    switch (heldItem.GetCategory())// ���� Ÿ�� �� 
//    //    {
//    //    case ItemCategory::Tool:   //����
//    //        canStack = (slot->GetToolType() == heldItem.GetToolType());
//    //        break;
//    //    case ItemCategory::Crop:  //�۹�
//    //        canStack = (slot->GetCropType() == heldItem.GetCropType());
//    //        break;
//    //    case ItemCategory::Seed:  //���Ѻ���
//    //        canStack = (slot->GetSeedType() == heldItem.GetSeedType());
//    //        break;
//    //    case ItemCategory::Placeable:  //��ġ ������ �͵�
//    //        canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
//    //        break;
//    //    default:
//    //        canStack = false;
//    //        break;
//    //    }
//
//    //    if (canStack) {
//    //        slot->SetCount(slot->GetCount() + heldItem.GetCount());
//    //        UIManager::Instance().ClearHeldItem();  //����ִ� ������ �ʱ�ȭ// �� �ʱ�ȭ
//    //    }
//    //    else {
//    //        std::swap(*slot, heldItem);  // �ٸ� ���� Ÿ���̸� ��ȯ
//    //    }
//    //}
//    //else {
//    //    // ������ ī�װ��� �ٸ��� �׳� ��ȯ
//    //    std::swap(*slot, heldItem);
//    //}
//}
//
//////Ŭ���� �������� Ŀ���� �ٰ� �ϴ� �Լ�
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
//bool NPC::HandleClick(int mouseX, int mouseY, int num) //num 1 ��Ŭ 2 ��Ŭ
//{
//    // �ڽ� ���� Ŭ�� ó��
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
//    // �÷��̾� ���� Ŭ�� ���� ó�� ����
//    if (playerToolbar) {
//        for (int i = 0; i < 9; ++i) {
//            int left = NPC_BASE_X + i * (SLOT_SIZE + SLOT_MARGIN);
//            int top = TOOLBAR_Y;  // �÷��̾� ���� Y ��ġ
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
//    std::srand(static_cast<unsigned int>(std::time(nullptr))); // �õ� ����
//
//    for (int i = 0; i < 27; i++)  //������ �������� ����
//    {
//        int typeIndex = 1 + rand() % 3;     // 1: Tool, 2: Seed, 3: Placeable
//        int count = 1 + rand() % 5;         // 1~5��
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
//            int max = 5; // NPC ~ Crop (None ����)
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
//    //�ڽ� �浹����
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
//        //��ȣ�ۿ�
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
//    if (slotIndex >= 0 && slotIndex < 27) {  // 27 ���� ���� �˻�
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
//    UIManager::Instance().OpenNPCUI(this, 27, player->GetInventory(), 9);  //  UIManager�� ǥ���� ���
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
