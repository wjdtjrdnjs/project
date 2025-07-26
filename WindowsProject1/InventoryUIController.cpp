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
//void InventoryUIController::UpdateInventory(InventoryItem* items) // 인벤토리 내용 갱신
//{
//    for (int i = 0; i < 9; i++)
//        inventorySlots[i] = items[i];
//}
//
//void InventoryUIController::ToolSelected(int index) // 선택된 툴 표시
//{
//    selectedSlot = index;
//}
//
//void InventoryUIController::Render(HDC hdc)  //인벤토리UI렌더링
//{
//    int slotSize = 50;
//    int startX = 10;
//    int startY = 500;
//
//    for (int i = 0; i < 9; i++) { //9칸
//        HBRUSH brush = nullptr;
//        if (i == selectedSlot)  brush = CreateSolidBrush(RGB(150, 150, 150));
//        else brush = CreateSolidBrush(RGB(200, 200, 200));
//        RECT slotRect = { startX + i * (slotSize + 5) + 350, startY, startX + i * (slotSize + 5) + slotSize + 350, startY + slotSize };
//        HDC memDC = CreateCompatibleDC(hdc);
//        FillRect(hdc, &slotRect, brush);
//        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // 테두리
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
//            //SetBkMode(hdc, TRANSPARENT);  //글자 배경을 투명으로 만든다
//            TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
//            SelectObject(memDC, oldBmp);
//        }
//        DeleteDC(memDC);
//
//    }
//
//}
//  
//RECT InventoryUIController::GetSlotRect(int index) const // 슬롯 좌표 계산 함수
//{
//    RECT rect;
//    rect.left = baseX + index * (slotSize + slotPadding);
//    rect.top = baseY;
//    rect.right = rect.left + slotSize;
//    rect.bottom = rect.top + slotSize;
//    return rect;
//}
//
//int InventoryUIController::ProcessMouseClick(int mouseX, int mouseY) // 마우스 클릭 이벤트 처리, 클릭한 슬롯 인덱스 반환
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
