#include "PlayerInventory.h"
#include "ToolType.h"
#include "TIleData.h"

void PlayerInventory::InventoryUIRender(HDC hdc)
{
    int slotSize = 50;
    int startX = 10;
    int startY = 500;
    for (int i = 0; i < 9; i++)
    {
        // ���� ����
        HBRUSH brush = CreateSolidBrush(i == selectedSlot ? RGB(150, 150, 150) : RGB(200, 200, 200));
        RECT slotRect = {
        startX + i * (slotSize + 5) + 350,
        startY,
        startX + i * (slotSize + 5) + slotSize + 350,
        startY + slotSize
        };

        // ���� ��� �� �׵θ�
        FillRect(hdc, &slotRect, brush);
        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        DeleteObject(brush);

        // ������ ������
        const InventoryItem& item = inventorySlots[i];
            if (item.IsValid())
            {

                HBITMAP bmp = item.GetBitmap();
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

                // ���� �ؽ�Ʈ
                std::string countText = std::to_string(item.GetCount());
                SetBkMode(hdc, TRANSPARENT);
                TextOutA(hdc, offsetX + 30, offsetY + 30, countText.c_str(), countText.length());
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
        inventorySlots[selectedSlot] = InventoryItem(); //�󽽷����� �ʱ�ȭ
    }
}





ToolType PlayerInventory::GetSelectedTool()
{
    const InventoryItem& item = inventorySlots[selectedSlot];

    // ���� �����۸� �Ǵ��ϰ� ��ȯ
    if (item.IsValid() && item.GetToolType() != ToolType::None) {
        return item.GetToolType(); // ��: Tool::hoe
    }

    return ToolType::None; // ���õ� ���Կ� ������ ���� ��
}

ObjectType PlayerInventory::GetSelectedObjectType()
{
    const InventoryItem& item = inventorySlots[selectedSlot];

    if (item.IsValid() && item.GetObjectType() != ObjectType::None) {
        return item.GetObjectType();
    }

    return ObjectType::None;
}

CropType PlayerInventory::GetSelectedCropType()
{
    const InventoryItem& item = inventorySlots[selectedSlot];
    if (item.IsValid() && item.GetCropType() != CropType::None) {
        return item.GetCropType();
    }
    return CropType::None;
}
