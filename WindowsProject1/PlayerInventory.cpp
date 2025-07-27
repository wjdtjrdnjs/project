#include "PlayerInventory.h"

void PlayerInventory::InventoryUIRender(HDC hdc)
{
    int slotSize = 50;
    int startX = 10;
    int startY = 500;

    HBRUSH grayBrush = CreateSolidBrush(RGB(200, 200, 200));
    HBRUSH darkGrayBrush = CreateSolidBrush(RGB(100, 100, 100));
    HBRUSH blackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);

    for (int i = 0; i < 9; i++) {
        RECT slotRect = {
            startX + i * (slotSize + 5) + 350,
            startY,
            startX + i * (slotSize + 5) + slotSize + 350,
            startY + slotSize
        };

        HBRUSH bgBrush = (i == selectedSlot) ? darkGrayBrush : grayBrush;
        FillRect(hdc, &slotRect, bgBrush);

        if (inventorySlots[i].IsValid()) {
            HBITMAP hBitmap = inventorySlots[i].GetBitmap();
            if (hBitmap) {
                BITMAP bmpInfo;
                GetObject(hBitmap, sizeof(BITMAP), &bmpInfo);

                int bmpWidth = bmpInfo.bmWidth;
                int bmpHeight = bmpInfo.bmHeight;

                HDC memDC = CreateCompatibleDC(hdc);
                HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hBitmap);

                // 투명색 지정 (예: 핑크색을 투명 처리)
                COLORREF transparentColor = RGB(255, 255, 255);

                // 슬롯 크기에 딱 맞게 확대해서 그리기
                TransparentBlt(
                    hdc,
                    slotRect.left, slotRect.top,
                    slotSize, slotSize,
                    memDC,
                    0, 0,
                    bmpWidth, bmpHeight,
                    transparentColor
                );

                SelectObject(memDC, oldBmp);
                DeleteDC(memDC);
            }
        }

        FrameRect(hdc, &slotRect, blackBrush);
    }

    DeleteObject(grayBrush);
    DeleteObject(darkGrayBrush);
}




void PlayerInventory::AddItem(int slotIndex, const InventoryItem& item) {
    if (slotIndex >= 0 && slotIndex < 9) {
        inventorySlots[slotIndex] = item;
    }
}
