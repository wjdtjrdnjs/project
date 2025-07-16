#include "Box.h"
#include "BitmapManager.h"
#include "InputManager.h"

#define slotSize 50
Box::Box(int xPos, int yPos) : x(xPos), y(yPos), isOpen(false)
{
    //��ġ
    iconRect.left = x;
    iconRect.top = y;
    iconRect.right = x + tileSize * 3;
    iconRect.bottom = y + tileSize * 3;

    // ��Ʈ�� �ε� 
    hIconBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDB_BITMAP24),
        IMAGE_BITMAP,
        0, 0,
        LR_CREATEDIBSECTION);
    for (int y = 0; y < 3; y++)
    {
        for (int i = 0; i < 9; i++) 
        {
            items[y][i].type = CropType::None;
            items[y][i].count = 0;
        }
    }
   
    items[0][0].type = CropType::Strawberry_1; //1�� ��������� 5��
    items[0][0].count = 99;
    items[0][1].type = CropType::Onion_1;      //2�� ���ĺ��� 5��
    items[0][1].count = 99;
    items[0][2].type = CropType::Fence;        //��Ÿ��
    items[0][2].count = 99;
    items[0][3].type = CropType::Axe;       //����
    items[0][3].count = 1;
}
bool Box::IsPlayerInRange(int playerX, int playerY) {  //�÷��̾ �ڽ� Ÿ�� �ֺ��� �ִ� �� Ȯ��
    int playerTileX = playerX / tileSize;
    int playerTileY = playerY / tileSize;
    int BoxTileX = x / tileSize;
    int BoxTileY = y / tileSize;

    return abs(playerTileX - BoxTileX) <= 1 &&   // -1,0,1 ����
        abs(playerTileY - BoxTileY) <= 1;
}


bool Box::IsMouseOverIcon(int mouseX, int mouseY) { //���콺 Ŀ���� ���ھ����� ���� �ִ��� Ȯ��
    return mouseX >= iconRect.left && mouseX <= iconRect.right &&
        mouseY >= iconRect.top && mouseY <= iconRect.bottom;
}
void Box::Open() {
    isOpen = true;
}

void Box::Close() {
    isOpen = false;
}

bool Box::IsOpen() const {
    return isOpen;
}



void Box::Render(HDC hdc) {

   
    if (hIconBitmap) {
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hIconBitmap);
        BITMAP bitmap;
        GetObject(hIconBitmap, sizeof(BITMAP), &bitmap);

        int bmpWidth = bitmap.bmWidth;
        int bmpHeight = bitmap.bmHeight;

        // ��� ũ�⸦ ������ �������� ���̱� (����)
        int drawWidth = bmpWidth +20;
        int drawHeight = bmpHeight  + 20;

        TransparentBlt(hdc,
            iconRect.left, iconRect.top,
            drawWidth, drawHeight,        
            memDC,
            0, 0,
            bmpWidth, bmpHeight,           // ���� ũ�� �״�� ����
            RGB(255, 255, 255));

        SelectObject(memDC, oldBitmap);
        DeleteDC(memDC);
    }
    else {
        OutputDebugString(L"[ERROR] Bitmap is NULL\n");
    }
}
void Box::RenderUI(HDC hdc)
{
    int startX = 10;
    int startY = 100;
    for (int y = 0; y < 3; y++) {

        for (int i = 0; i < 9; i++) {
            HBRUSH brush = nullptr;
            brush = CreateSolidBrush(RGB(200, 200, 200)); // �⺻ ��

            RECT slotRect = { startX + i * (slotSize + 5) + 350, startY + y * 51, startX + i * (slotSize + 5) + slotSize + 350, startY + slotSize + y * 51 };

            FillRect(hdc, &slotRect, brush);
            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // �׵θ�
            if (items[y][i].type != CropType::None) {
                HBITMAP bmp = BitmapManager::GetBitmapForCrop(items[y][i].type);
                HDC memDC = CreateCompatibleDC(hdc);
                HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
                BITMAP bm;
                GetObject(bmp, sizeof(BITMAP), &bm);

                int drawSize = 40;
                int offsetX = slotRect.left + (slotSize - drawSize) / 2;
                int offsetY = slotRect.top + (slotSize - drawSize) / 2;


                TransparentBlt(hdc,
                    offsetX, offsetY,
                    drawSize, drawSize,
                    memDC,
                    0, 0,
                    bm.bmWidth,
                    bm.bmHeight,
                    RGB(255, 255, 255));
                std::string countText = std::to_string(items[y][i].count);
                TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
                SelectObject(memDC, oldBmp);
                DeleteDC(memDC);

            }
            DeleteObject(brush);
        }
    }
    if (playerToolbar) {
        int startX = 10;
        int startY = 100 + 3 * 51 + 10;  // ���� �Ʒ� ���� 10

        for (int i = 0; i < 9; i++) {
            RECT slotRect = {
                startX + i * (slotSize + 5) + 350,
                startY,
                startX + i * (slotSize + 5) + slotSize + 350,
                startY + slotSize
            };

            HBRUSH brush = CreateSolidBrush(RGB(180, 180, 180));
            FillRect(hdc, &slotRect, brush);
            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            DeleteObject(brush);

            if (playerToolbar[i].type != CropType::None) {
                HBITMAP bmp = BitmapManager::GetBitmapForCrop(playerToolbar[i].type);
                if (bmp) {
                    HDC memDC = CreateCompatibleDC(hdc);
                    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
                    BITMAP bm;
                    GetObject(bmp, sizeof(BITMAP), &bm);

                    int drawSize = 40;
                    int offsetX = slotRect.left + (slotSize - drawSize) / 2;
                    int offsetY = slotRect.top + (slotSize - drawSize) / 2;

                    TransparentBlt(hdc, offsetX, offsetY,
                        drawSize, drawSize,
                        memDC, 0, 0,
                        bm.bmWidth, bm.bmHeight,
                        RGB(255, 255, 255));

                    std::string countText = std::to_string(playerToolbar[i].count);
                    TextOutA(hdc, offsetX + 25, offsetY + 30, countText.c_str(), countText.length());
                    SelectObject(memDC, oldBmp);
                    DeleteDC(memDC);
                }
            }
        }
    }
    RenderCursorItem(hdc);
 
}
//Ŭ���� �������� Ŀ���� �ٰ� �ϴ� �Լ�
void Box::RenderCursorItem(HDC hdc) { 
    if (heldItem.type == CropType::None) return; // �ƹ��͵� �� ��� ������ ���ư�

    POINT mouse = InputManager::GetMousePosition();  //Ŭ���� ��ǥ�� ������

    HBITMAP bmp = BitmapManager::GetBitmapForCrop(heldItem.type);
    if (!bmp) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
    BITMAP bm;
    GetObject(bmp, sizeof(BITMAP), &bm);

    int drawSize = 40;
    TransparentBlt(
        hdc,
        mouse.x-20 , mouse.y -20,
        drawSize, drawSize,
        memDC,
        0, 0,
        bm.bmWidth, bm.bmHeight,
        RGB(255, 255, 255)
    );

    if (heldItem.count > 0) { //������ ������ 1�� �̻��� �� ���� ǥ�� 
        std::string countText = std::to_string(heldItem.count);
        TextOutA(hdc, mouse.x + 5, mouse.y + 10, countText.c_str(), countText.length());
    }

    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}

/////////////////�ڵ� ����////////////////
 //���콺�� Ŭ���� ���԰� ���� ��� �ִ� ������ ó�� �Լ�
void Box::HandleItemSlotClick(InventoryItem& slot) 
{
    if (heldItem.type == CropType::None) {
        // ����̸� ������ �������� ���
        heldItem = slot;
        slot.type = CropType::None;
        slot.count = 0;
    }
    else {
        if (slot.type == CropType::None) {
            // �� �����̸� �������� �ִ´�
            slot = heldItem;
            heldItem.type = CropType::None;
            heldItem.count = 0;
        }
        else if (slot.type == heldItem.type) {
            // ���� �������̸� ��ġ��
            slot.count += heldItem.count;
            heldItem.type = CropType::None;
            heldItem.count = 0;
        }
        else {
            // ���� �ٸ� �������̸� ��ȯ
            InventoryItem temp = heldItem;
            heldItem = slot;
            slot = temp;
        }
    }
}

//���콺 Ŭ�� ���� Ȯ��(�ڽ� or �÷��̾� ����)
void Box::HandleClick(int mouseX, int mouseY)
{
    int startX = 10;
    int startY = 100;

    for (int i = 0; i < 3; ++i)  
    {
        for (int j = 0; j < 9; ++j)
        {
            //���� ��ġ
            int left = startX + j * (slotSize + 5) + 350;
            int top = startY + i * 51;
            int right = left + slotSize;
            int bottom = top + slotSize;

            if (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom) //Ŭ���� ���� �ڽ� �����̸� ����
            {
                HandleItemSlotClick(items[i][j]); //���콺�� Ŭ���� ���԰� ���� ��� �ִ� ������ ó�� �Լ�
                return;
            }
        }
    }
    if (playerToolbar) {
        int toolbarY = 100 + 3 * 51 + 10; // ���� �Ʒ� ���� ����
        int startX = 10;

        for (int i = 0; i < 9; ++i) {  //�÷��̾� ���� ����� ���� �ݺ���
           
            //���� ��ġ
            int left = startX + i * (slotSize + 5) + 350;
            int top = toolbarY;
            int right = left + slotSize;
            int bottom = top + slotSize;

            if (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom) { //Ŭ���� ���� �÷��̾� �����̸� ����
                HandleItemSlotClick(playerToolbar[i]); //���콺�� Ŭ���� ���԰� ���� ��� �ִ� ������ ó�� �Լ�
                return;
            }
        }
    }
  
}




