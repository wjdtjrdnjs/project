#include "UIManager.h"
#include "BitmapManager.h"
#include "InventoryItem.h"

void UIManager::OpenBoxUI(Box* box, PlayerInventory* playerInv)
{
    openedBox = box;
    playerInventory = playerInv;
    isBoxUIOpen = true;
}

void UIManager::CloseBoxUI()
{
    openedBox = nullptr;
    isBoxUIOpen = false;
}


void UIManager::Update(float deltaTime) {
    if (!isBoxUIOpen) return;

    // 나중에 드래그, 호버, 툴팁 등을 여기에 추가
}


void UIManager::Render(HDC hdc) {

    playerInventory->InventoryUIRender(hdc);

    if (!isBoxUIOpen) return;
    if (openedBox) {
        RenderBoxUI(hdc, openedBox);
    }
}

void UIManager::RenderInventory(HDC hdc)  //플레이어 툴바
{
   
    
}

void UIManager::HandleClick(int mouseX, int mouseY, bool isRightClick) {
    if (!isBoxUIOpen) return;

    // 클릭한 위치가 슬롯인지 판별 → 아이템 이동 또는 선택 처리
}

void UIManager::SetPlayerInventory(PlayerInventory* inv)
{
        playerInventory = inv;
}

void UIManager::RenderBoxUI(HDC hdc, Box* box)
{
    // Box에서 3x9 아이템 배열과 1x9 툴바 배열을 가져온다.
    InventoryItem* items = box->GetItems();            // 3x9 배열이 1차원 포인터로 리턴된다고 가정
    InventoryItem* toolbar = box->GetPlayerToolbar();  // 1x9 배열

    DrawInventoryGrid(hdc, items, baseX, baseY);
    DrawToolbar(hdc, toolbar, baseX, baseY + 3 * 51 + 10);
    DrawHeldItem(hdc);
}

void UIManager::DrawInventoryGrid(HDC hdc, InventoryItem* items, int baseX, int baseY)
{
    const int slotSize = 50;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 9; col++) {
            int left = baseX + col * (slotSize + 5);
            int top = baseY + row * (slotSize + 1);

            RECT slotRect = { left, top, left + slotSize, top + slotSize };
            HBRUSH brush = CreateSolidBrush(RGB(200, 200, 200));
            FillRect(hdc, &slotRect, brush);
            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            DeleteObject(brush);

            InventoryItem& item = items[row * 9 + col];
            if (item.GetObjectType() != ObjectType::None) {
                // 아이템 그림 불러오기 (예시, BitmapManager 사용 가정)
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

                    // 아이템 개수 출력
                    std::string countText = std::to_string(item.GetCount());
                    TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), (int)countText.length());

                    SelectObject(memDC, oldBmp);
                    DeleteDC(memDC);
                }
            }
        }
    }
}

void UIManager::DrawToolbar(HDC hdc, InventoryItem* toolbar, int baseX, int baseY)
{
    const int slotSize = 50;
    for (int i = 0; i < 9; i++) {
        int left = baseX + i * (slotSize + 5);
        int top = baseY;

        RECT slotRect = { left, top, left + slotSize, top + slotSize };
        HBRUSH brush = CreateSolidBrush(RGB(180, 180, 180));
        FillRect(hdc, &slotRect, brush);
        FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        DeleteObject(brush);

        InventoryItem& item = toolbar[i];
        if (item.GetObjectType() != ObjectType::None) {
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
                TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), (int)countText.length());

                SelectObject(memDC, oldBmp);
                DeleteDC(memDC);
            }
        }
    }
}

void UIManager::DrawHeldItem(HDC hdc)
{
    // heldItem이 있다면 현재 커서 위치에 그리기 (예시 좌표 사용)
    //if (heldItem.itemType == ItemType::NONE) return;

    //POINT cursorPos;
    //GetCursorPos(&cursorPos);
    //ScreenToClient(WindowHandle, &cursorPos);  // WindowHandle은 UI가 그려지는 윈도우 핸들

    //HBITMAP bmp = BitmapManager::Instance().GetObjectBitmap(heldItem);
    //if (!bmp) return;

    //HDC memDC = CreateCompatibleDC(hdc);
    //HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

    //BITMAP bm;
    //GetObject(bmp, sizeof(BITMAP), &bm);

    //int drawSize = 40;
    //int offsetX = cursorPos.x - drawSize / 2;
    //int offsetY = cursorPos.y - drawSize / 2;

    //TransparentBlt(hdc,
    //    offsetX, offsetY,
    //    drawSize, drawSize,
    //    memDC,
    //    0, 0,
    //    bm.bmWidth, bm.bmHeight,
    //    RGB(255, 255, 255));

    //SelectObject(memDC, oldBmp);
    //DeleteDC(memDC);
}

//void Box::RenderUI(HDC hdc)
//{
//    int startX = 10;
//    int startY = 100;
//    for (int y = 0; y < 3; y++) {
//
//        for (int i = 0; i < 9; i++) {
//            HBRUSH brush = nullptr;
//            brush = CreateSolidBrush(RGB(200, 200, 200)); // 기본 색
//
//            RECT slotRect = { startX + i * (slotSize + 5) + 350, startY + y * 51, startX + i * (slotSize + 5) + slotSize + 350, startY + slotSize + y * 51 };
//
//            FillRect(hdc, &slotRect, brush);
//            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // 테두리
//            if (items[y][i].itemType != ItemType::NONE) {
//                HBITMAP bmp = 
// .GetBitmapForCrop(items[y][i]);
//                if (!bmp)  return;
//
//                HDC memDC = CreateCompatibleDC(hdc);
//                HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
//                BITMAP bm;
//                GetObject(bmp, sizeof(BITMAP), &bm);
//
//
//                int drawSize = 40;
//                int offsetX = slotRect.left + (slotSize - drawSize) / 2;
//                int offsetY = slotRect.top + (slotSize - drawSize) / 2;
//
//
//                TransparentBlt(hdc,
//                    offsetX, offsetY,
//                    drawSize, drawSize,
//                    memDC,
//                    0, 0,
//                    bm.bmWidth,
//                    bm.bmHeight,
//                    RGB(255, 255, 255));
//                std::string countText = std::to_string(items[y][i].count);
//                TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
//                SelectObject(memDC, oldBmp);
//                DeleteDC(memDC);
//
//            }
//            DeleteObject(brush);
//        }
//    }
//         startX = 10;
//         startY = 100 + 3 * 51 + 10;  // 상자 아래 여백 10
//
//        for (int i = 0; i < 9; i++) {
//            RECT slotRect = {
//                startX + i * (slotSize + 5) + 350,
//                startY,
//                startX + i * (slotSize + 5) + slotSize + 350,
//                startY + slotSize
//            };
//
//            HBRUSH brush = CreateSolidBrush(RGB(180, 180, 180));
//            FillRect(hdc, &slotRect, brush);
//            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
//            DeleteObject(brush);
//            if (playerToolbar[i]->itemType != ItemType::NONE) {
//                HBITMAP bmp = BitmapManager::Instance().GetBitmapForCrop(*playerToolbar[i]);
//
//                if (!bmp) return;
//                if (bmp) {
//                    HDC memDC = CreateCompatibleDC(hdc);
//                    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
//                    BITMAP bm;
//                    GetObject(bmp, sizeof(BITMAP), &bm);
//
//                    int drawSize = 40;
//                    int offsetX = slotRect.left + (slotSize - drawSize) / 2;
//                    int offsetY = slotRect.top + (slotSize - drawSize) / 2;
//
//                    TransparentBlt(hdc, offsetX, offsetY,
//                        drawSize, drawSize,
//                        memDC, 0, 0,
//                        bm.bmWidth, bm.bmHeight,
//                        RGB(255, 255, 255));
//
//                    std::string countText = std::to_string(playerToolbar[i]->count);
//                    TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
//                    SelectObject(memDC, oldBmp);
//                    DeleteDC(memDC);
//                }
//            }
//        }
//        RenderCursorItem(hdc);
//
//    }