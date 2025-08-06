#pragma once
#include <Windows.h>
#include "InventoryItem.h"
class Map;
class PlayerInventory
{
public:
	//PlayerInventory();
	void InventoryUIRender(HDC hdc); //상시로 그려주는 인벤토리 툴바
	void InventoryBoxUIRender(HDC hdc); //상시로 그려주는 인벤토리 툴바

	void AddItem(int slotIndex, const InventoryItem& item); //아이템 추가 함수
	void DecreaseItem(int delta); //인벤토리 수량 감소

	void SetSelectedSlot(int index) { selectedSlot = index; }
	void MoveSelectedSlot(int dir);
	ToolType GetSelectedTool();//도구반환
	PlaceableType GetSelectedPlaceable();//배치 가능한 것을 반환
	CropType GetSelectedCropType();//작물 반환
	SeedType GetSelectedSeedType(); //씨앗봉투 반환

	InventoryItem GetSelectedItem() const { return inventorySlots[selectedSlot]; }
	InventoryItem* GetInventory() { return inventorySlots; }
private:
	InventoryItem inventorySlots[9];
	int selectedSlot = 0; // 아무것도 선택되지 않은 상태
};

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