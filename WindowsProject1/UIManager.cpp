#include "UIManager.h"
#include "BitmapManager.h"
#include "InventoryItem.h"
#include "InputManager.h"

void UIManager::OpenBoxUI(Box* boxItems, int boxSlotCount, PlayerInventory* playerItems, int playerSlotCount)
{
    openedBox = boxItems;
    openedBoxSlotCount = boxSlotCount;

    player = playerItems;
    playerInventorySlotCount = playerSlotCount;

    if (openedBox && player)
        openedBox->SetPlayerToolbar(player->GetInventory());  // �� box ���ο� ������ ����

    isBoxUIOpen = true;
}

void UIManager::OpenNpcUI(NPC* npcItems, int boxSlotCount, PlayerInventory* playerItems, int playerSlotCount)
{
    openednpc = npcItems;
    openedBoxSlotCount = boxSlotCount;

    player = playerItems;
    playerInventorySlotCount = playerSlotCount;

    if (openednpc && player)
        openednpc->SetPlayerToolbar(player->GetInventory());  // �� box ���ο� ������ ����

   isNpcUIOpen = true;
}

void UIManager::CloseNpcUI()
{
    openednpc = nullptr;
    isNpcUIOpen = false;
}

void UIManager::CloseBoxUI()
{
    openedBox = nullptr;
    isBoxUIOpen = false;
}

void UIManager::Update(float deltaTime)
{
    if (!isBoxUIOpen) return;

}

void UIManager::Render(HDC hdc)
{
    if (player)
        player->InventoryUIRender(hdc);  // �׻� ���̴� �÷��̾� �κ��丮 (���� ��)

    if (openedBox)
    {
        RenderBoxUI(hdc, openedBox, player); // �ڽ� UI �� �÷��̾� �κ��丮 �Բ� ������
        RenderHeldItem(hdc); // ���콺 Ŀ���� ��� �ִ� ������ ������
    }
    else if (openednpc)
    {
        OutputDebugStringA("NPC ��ȣ�ۿ���!!!!!!!!\n");
        RenderNpcUI(hdc, openednpc, player); // �ڽ� UI �� �÷��̾� �κ��丮 �Բ� ������
        RenderHeldItem(hdc); // ���콺 Ŀ���� ��� �ִ� ������ ������
    }

}

void UIManager::RenderBoxUI(HDC hdc, Box* box, PlayerInventory* playerInv)  //�ڽ� UI����
{
    box->RenderUI(hdc);
    playerInv->InventoryBoxUIRender(hdc);
}


void UIManager::RenderNpcUI(HDC hdc, NPC* npc, PlayerInventory* playerInv) //NPC UI����
{
    npc->RenderUI(hdc);
    playerInv->InventoryBoxUIRender(hdc);
}

void UIManager::HandleClick(int mouseX, int mouseY, bool isRightClick)
{
    if (!isBoxUIOpen) return;

    // Ŭ�� ��ġ �Ǻ� �� ������ ����, �̵� ó�� ����
}

void UIManager::SetPlayerInventory(PlayerInventory* inv)
{
    player = inv;
}

void UIManager::RenderHeldItem(HDC hdc)
{
    if (!HasHeldItem()) return;

    POINT mouse = InputManager::Instance().GetMousePosition();
    HBITMAP bmp = BitmapManager::Instance().GetObjectBitmap(heldItem);
    if (!bmp) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
    BITMAP bm;
    GetObject(bmp, sizeof(BITMAP), &bm);

    constexpr int drawSize = 40;
    TransparentBlt(
        hdc,
        mouse.x - drawSize / 2, mouse.y - drawSize / 2,
        drawSize, drawSize,
        memDC,
        0, 0,
        bm.bmWidth, bm.bmHeight,
        RGB(255, 255, 255)
    );

    if (heldItem.GetCount() > 0) {
        std::string countText = std::to_string(heldItem.GetCount());
        TextOutA(hdc, mouse.x + 5, mouse.y + 10, countText.c_str(), (int)countText.length());
    }

    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}


//void Box::RenderUI(HDC hdc)
//{
//    int startX = 10;
//    int startY = 100;
//    for (int y = 0; y < 3; y++) {
//
//        for (int i = 0; i < 9; i++) {
//            HBRUSH brush = nullptr;
//            brush = CreateSolidBrush(RGB(200, 200, 200)); // �⺻ ��
//
//            RECT slotRect = { startX + i * (slotSize + 5) + 350, startY + y * 51, startX + i * (slotSize + 5) + slotSize + 350, startY + slotSize + y * 51 };
//
//            FillRect(hdc, &slotRect, brush);
//            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // �׵θ�
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
//         startY = 100 + 3 * 51 + 10;  // ���� �Ʒ� ���� 10
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