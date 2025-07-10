
#include "Box.h"

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
    int slotSize = 50;
    int startX = 10;
    int startY = 100;
    for (int y = 0; y < 3; y++) {

        for (int i = 0; i < 9; i++) {
            HBRUSH brush = nullptr;
            brush = CreateSolidBrush(RGB(200, 200, 200)); // �⺻ ��

            RECT slotRect = { startX + i * (slotSize + 5) + 350, startY + y* 51, startX + i * (slotSize + 5) + slotSize + 350, startY + slotSize + y * 51 };

            FillRect(hdc, &slotRect, brush);
            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));  // �׵θ�

            DeleteObject(brush);

            FrameRect(hdc, &slotRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

        }
    }
}

InventoryItem* Box::GetItems() {
    return items;
}