#include "NPC.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "TileData.h"
#include "WorldObject.h"
#include "Global.h" //충돌영역 on/off

NPC::NPC()
{
    hBmp = BitmapManager::Instance().GetObjectBitmap(PlaceableType::NPC);
}

void NPC::SetTilePosition(int tileX, int tileY)
{
    x = tileX;
    y = tileY;
}

void NPC::Render(HDC hdc, int tilesize)
{
    if (!hBmp) return;
    // 임시 메모리 DC 생성
    int px = tileX * tilesize;
    int py = tileY * tilesize;

    HDC memDC = CreateCompatibleDC(hdc);
    HGDIOBJ oldBmp = SelectObject(memDC, hBmp);

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);
    TransparentBlt(hdc,
        px + 8, py + 10,
        32, 32,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );

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

    // DC 정리
    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}

PlaceableType NPC::GetPlaceableType() const
{
    return PlaceableType::NPC;
}

RECT NPC::GetCollisionRect()
{

    int px = x * 32;
    int py = y * 32;

    RECT r;
    r.left = px + 5;
    r.top = py + 5;
    r.right = r.left + 20;
    r.bottom = r.top + 20;
    return RECT(r);
}

void NPC::OnInteract(Player* player)  //ui매니저와 NPC를 연결
{
    UIManager::Instance().OpenNpcUI(this, 27, player->GetInventory(), 9);  //  UIManager는 표현만 담당
}


void NPC::SetPlayerToolbar(InventoryItem* toolbar)
{
    playerToolbar = toolbar;
}

void NPC::RenderUI(HDC hdc)
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



bool NPC::HandleClick(int mouseX, int mouseY, int num) //num 1 좌클 2 우클
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




void NPC::HandleItemSlotLClick(InventoryItem* slot)  //박스를 오픈한 상태에서 좌클릭 
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


void NPC::HandleItemSlotRClick(InventoryItem* slot)  //박스를 오픈한 상태에서 우클릭
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

}
