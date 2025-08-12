#include "PlayerInventory.h"
#include "ToolType.h"
#include "TIleData.h"
#include "BitmapManager.h"

void PlayerInventory::InventoryUIRender(HDC hdc)
{
    int slotSize = 50;
    int startX = 10;
    int startY = 500;
    for (int i = 0; i < 9; i++)
    {
        // 슬롯 배경색
        HBRUSH brush = CreateSolidBrush(i == selectedSlot ? RGB(150, 150, 150) : RGB(200, 200, 200));
        RECT slotRect = {
        startX + i * (slotSize + 5) + 350,
        startY,
        startX + i * (slotSize + 5) + slotSize + 350,
        startY + slotSize
        };

        // 슬롯 배경 및 테두리
        FillRect(hdc, &slotRect, brush);
        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        DeleteObject(brush);

        // 아이템 렌더링
        const InventoryItem& item = inventorySlots[i];
            if (item.IsValid())
            {

                HBITMAP bmp = BitmapManager::Instance().GetObjectBitmap(item);
                if (!bmp) continue;

                HDC memDC = CreateCompatibleDC(hdc);
                HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

                BITMAP bm;
                GetObject(bmp, sizeof(BITMAP), &bm);

                int drawSize = 40;
                int offsetX = slotRect.left + (slotSize - drawSize) / 2;
                int offsetY = slotRect.top + (slotSize - drawSize) / 2;

                TransparentBlt(
                    hdc,
                    offsetX, offsetY,
                    drawSize, drawSize,
                    memDC,
                    0, 0,
                    bm.bmWidth,
                    bm.bmHeight,
                    RGB(255, 255, 255)
                );

                SelectObject(memDC, oldBmp);
                DeleteDC(memDC);

                // 수량 텍스트
                std::string countText = std::to_string(item.GetCount());
                SetBkMode(hdc, TRANSPARENT);
                TextOutA(hdc, offsetX + 30, offsetY + 30, countText.c_str(), countText.length());
            }
        }
        
}

void PlayerInventory::InventoryBoxUIRender(HDC hdc)
{
    const int slotSize = 50;
    for (int i = 0; i < 9; i++) {
        int left = 360 + i * (slotSize + 5);
        int top = 310;

        RECT slotRect = { left, top, left + slotSize, top + slotSize };
        HBRUSH brush = CreateSolidBrush(RGB(180, 180, 180));
        FillRect(hdc, &slotRect, brush);
        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        DeleteObject(brush);

        InventoryItem& item = inventorySlots[i];
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




void PlayerInventory::AddItem(int slotIndex, const InventoryItem& item) {
    if (slotIndex >= 0 && slotIndex < 9) {
        inventorySlots[slotIndex] = item;
    }
}

void PlayerInventory::DecreaseItem( int delta)
{
    InventoryItem& item = inventorySlots[selectedSlot];
    item.DecreaseItem(delta);
    if (item.GetCount() <= 0)
    {
        inventorySlots[selectedSlot] = InventoryItem(); //빈슬롯으로 초기화
    }
}


void PlayerInventory::MoveSelectedSlot(int direction)
{
    selectedSlot += direction;

    if (selectedSlot < 0)
        selectedSlot = 8;
    else if (selectedSlot > 8)
        selectedSlot = 0;

    char msg[100];
    snprintf(msg, sizeof(msg), "휠로 선택된 슬롯: %d\n", selectedSlot);
    OutputDebugStringA(msg);
}


// 도구 아이템 반환
ToolType PlayerInventory::GetSelectedTool()
{
    const InventoryItem& item = inventorySlots[selectedSlot];
    if (item.IsValid() && item.GetCategory() == ItemCategory::Tool) {
        return item.GetToolType();
    }
    return ToolType::None;
}

// 작물 반환
CropType PlayerInventory::GetSelectedCropType()
{
    const InventoryItem& item = inventorySlots[selectedSlot];
    if (item.IsValid() && item.GetCategory() == ItemCategory::Crop) {
        return item.GetCropType();
    }
    return CropType::None;
}

//씨앗 반환
SeedType PlayerInventory::GetSelectedSeedType()
{
    const InventoryItem& item = inventorySlots[selectedSlot];
    if (item.IsValid() && item.GetCategory() == ItemCategory::Seed) {
        return item.GetSeedType();
    }
    return SeedType::None;
}




// 설치물 반환
PlaceableType PlayerInventory::GetSelectedPlaceable()
{
    const InventoryItem& item = inventorySlots[selectedSlot];
    if (item.IsValid() && item.GetCategory() == ItemCategory::Placeable) {
        return item.GetPlaceableType();
    }
    return PlaceableType::None;
}