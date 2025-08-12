#include "NPC.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "TileData.h"
#include "WorldObject.h"
#include "Global.h" //�浹���� on/off

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
    // �ӽ� �޸� DC ����
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
        //��ȣ�ۿ�
        r.left = px;
        r.top = py;
        r.right = r.left + 32;
        r.bottom = r.top + 32;
        HBRUSH green = CreateSolidBrush(RGB(0, 255, 0));
        FrameRect(hdc, &r, green);
        DeleteObject(green);
    }

    // DC ����
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

void NPC::OnInteract(Player* player)  //ui�Ŵ����� NPC�� ����
{
    UIManager::Instance().OpenNpcUI(this, 27, player->GetInventory(), 9);  //  UIManager�� ǥ���� ���
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

    // RenderCursorItem(hdc);  // �տ� �� �������� �ڽ� UI������ �׸��� ����
}



bool NPC::HandleClick(int mouseX, int mouseY, int num) //num 1 ��Ŭ 2 ��Ŭ
{
    // �ڽ� ���� Ŭ�� ó��
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

    // �÷��̾� ���� Ŭ�� ���� ó�� ����
    if (playerToolbar) {
        for (int i = 0; i < 9; ++i) {
            int left = BOX_BASE_X + i * (SLOT_SIZE + SLOT_MARGIN);
            int top = TOOLBAR_Y;  // �÷��̾� ���� Y ��ġ
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




void NPC::HandleItemSlotLClick(InventoryItem* slot)  //�ڽ��� ������ ���¿��� ��Ŭ�� 
{
    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();


    if (heldItem.IsEmpty()) { // ����̸� ���� �������� �տ� ���
        UIManager::Instance().SetHeldItem(*slot);
        *slot = InventoryItem();  // ���� ����
    }
    else {

        if (slot->IsEmpty()) {// �տ� ������ �ְ� ������ ��� ������ �ű��
            *slot = heldItem;
            UIManager::Instance().ClearHeldItem();
        }
        else if (slot->GetCategory() == heldItem.GetCategory()) {// Ÿ���� ���� ��

            bool canStack = false;

            switch (heldItem.GetCategory())// ���� Ÿ�� �� 
            {
            case ItemCategory::Tool:   //����
                canStack = (slot->GetToolType() == heldItem.GetToolType());
                break;
            case ItemCategory::Crop:  //�۹�
                canStack = (slot->GetCropType() == heldItem.GetCropType());
                break;
            case ItemCategory::Seed:  //���Ѻ���
                canStack = (slot->GetSeedType() == heldItem.GetSeedType());
                break;
            case ItemCategory::Placeable:  //��ġ ������ �͵�
                canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
                break;
            default:
                canStack = false;
                break;
            }

            if (canStack) {
                slot->SetCount(slot->GetCount() + heldItem.GetCount());
                UIManager::Instance().ClearHeldItem();  //����ִ� ������ �ʱ�ȭ// �� �ʱ�ȭ
            }
            else {
                std::swap(*slot, heldItem);  // �ٸ� ���� Ÿ���̸� ��ȯ
            }
        }
        else {
            // ������ ī�װ��� �ٸ��� �׳� ��ȯ
            std::swap(*slot, heldItem);
        }
    }
}


void NPC::HandleItemSlotRClick(InventoryItem* slot)  //�ڽ��� ������ ���¿��� ��Ŭ��
{
    InventoryItem& heldItem = UIManager::Instance().GetHeldItem();
    if (slot->IsEmpty()) {// �տ� ������ �ְ� ������ ��� ������ 1���� �ű��
        /* *slot = heldItem;
         UIManager::Instance().ClearHeldItem();*/
        OutputDebugStringA("������ shgrl\n");
        *slot = heldItem;  //������ ������ �Ѱ��ְ�  ������ 1���� ����
        if (slot->GetCount() != 0)slot->SetCount(1);
        else   slot->AddCount(1);
        heldItem.DecreaseItem(1);
        if (heldItem.GetCount() <= 0) UIManager::Instance().ClearHeldItem();  //�տ� �ִ� ������ ������ 0���Ϸ� �������� �� �ʱ�ȭ 

    }
    else if (slot->GetCategory() == heldItem.GetCategory())
    {
        bool canStack = false;
        OutputDebugStringA("gkqclrl rksmd\n");

        switch (heldItem.GetCategory())
        {
        case ItemCategory::Tool:   //����
            canStack = (slot->GetToolType() == heldItem.GetToolType());
            break;
        case ItemCategory::Crop:  //�۹�
            canStack = (slot->GetCropType() == heldItem.GetCropType());
            break;
        case ItemCategory::Seed:  //���Ѻ���
            canStack = (slot->GetSeedType() == heldItem.GetSeedType());
            break;
        case ItemCategory::Placeable:  //��ġ ������ �͵�
            canStack = (slot->GetPlaceableType() == heldItem.GetPlaceableType());
            break;
        default:
            canStack = false;
            break;



        }
        if (canStack) {
            slot->AddCount(1);
            heldItem.DecreaseItem(1);

            if (heldItem.GetCount() <= 0) UIManager::Instance().ClearHeldItem();  //����ִ� ������ �ʱ�ȭ// �� �ʱ�ȭ
        }

    }

}
