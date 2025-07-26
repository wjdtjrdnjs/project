//#include "InventoryUIController.h"
//#include "BitmapManager.h"
//#include <windows.h>
//#include <string>
//
//InventoryUIController::InventoryUIController()
//    : selectedSlot(-1)
//{
//}
//
//void InventoryUIController::Initialize(int slotCount)
//{
// 
//}
//
//void InventoryUIController::UpdateInventory(InventoryItem* items) // �κ��丮 ���� ����
//{
//    for (int i = 0; i < 9; i++)
//        inventorySlots[i] = items[i];
//}
//
//void InventoryUIController::ToolSelected(int index) // ���õ� �� ǥ��
//{
//    selectedSlot = index;
//}
//
//void InventoryUIController::Render(HDC hdc)  //�κ��丮UI������
//{
//    int slotSize = 50;
//    int startX = 10;
//    int startY = 500;
//
//    for (int i = 0; i < 9; i++) { //9ĭ
//        HBRUSH brush = nullptr;
//        if (i == selectedSlot)  brush = CreateSolidBrush(RGB(150, 150, 150));
//        else brush = CreateSolidBrush(RGB(200, 200, 200));
//        RECT slotRect = { startX + i * (slotSize + 5) + 350, startY, startX + i * (slotSize + 5) + slotSize + 350, startY + slotSize };
//        HDC memDC = CreateCompatibleDC(hdc);
//        FillRect(hdc, &slotRect, brush);
//        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // �׵θ�
//        DeleteObject(brush);
//
//        InventoryItem* item = inventorySlots;
//        if (item[i].itemType != ItemType::NONE) {
//            HBITMAP bmp = BitmapManager::Instance().GetBitmapForCrop(item[i]);
//            HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
//            BITMAP bm;
//            GetObject(bmp, sizeof(BITMAP), &bm);
//
//            int drawSize = 40;
//            int offsetX = slotRect.left + (slotSize - drawSize) / 2;
//            int offsetY = slotRect.top + (slotSize - drawSize) / 2;
//
//         
//
//            TransparentBlt(hdc,
//                offsetX, offsetY,
//                drawSize, drawSize,
//                memDC,
//                0, 0,
//                bm.bmWidth,
//                bm.bmHeight,
//                RGB(255, 255, 255));
//            std::string countText = std::to_string(item[i].count);
//            //SetBkMode(hdc, TRANSPARENT);  //���� ����� �������� �����
//            TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
//            SelectObject(memDC, oldBmp);
//        }
//        DeleteDC(memDC);
//
//    }
//
//}
//  
//RECT InventoryUIController::GetSlotRect(int index) const // ���� ��ǥ ��� �Լ�
//{
//    RECT rect;
//    rect.left = baseX + index * (slotSize + slotPadding);
//    rect.top = baseY;
//    rect.right = rect.left + slotSize;
//    rect.bottom = rect.top + slotSize;
//    return rect;
//}
//
//int InventoryUIController::ProcessMouseClick(int mouseX, int mouseY) // ���콺 Ŭ�� �̺�Ʈ ó��, Ŭ���� ���� �ε��� ��ȯ
//{
//    for (int i = 0; i < 9; ++i) {
//        RECT r = GetSlotRect(i);
//        if (mouseX >= r.left && mouseX <= r.right &&
//            mouseY >= r.top && mouseY <= r.bottom) {
//            return i;
//        }
//    }
//    return -1;
//}
//
