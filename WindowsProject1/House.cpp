#include "House.h"
#include "BitmapManager.h"
#include "Global.h" //�浹���� on/off
#include "TileData.h"

House::House()
{
    bmp = BitmapManager::Instance().GetObjectBitmap(PlaceableType::House);
}

House::~House() //���� �Ҹ���
{
   
}

void House::Render(HDC hdc, int tileSize)
{
    if (!bmp) return;

    const int drawWidth = 96;   // �׸��� ���� �� (ũ�� ����)
    const int drawHeight = 120;  // �׸��� ���� ����

    int px = tileX * tileSize;
    int py = tileY * tileSize;

    // �߽� ���� ����: Ÿ�� �������� ��Ʈ�� �߽��� �ش� Ÿ�� �߾ӿ� ��ġ�ϰ� ����
    px -= (drawWidth - tileSize) / 2;
    py -= (drawHeight - tileSize);  // �Ʒ��� �� ���� ����

    // �ʿ��ϸ� ��¦ ������ (Ÿ�Ͽ� ���� �Ⱥ��� ��)
    py += 8;

    BITMAP bmpInfo;
    GetObject(bmp, sizeof(bmpInfo), &bmpInfo);

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

    TransparentBlt(
        hdc,
        px, py,
        drawWidth, drawHeight,
        memDC,
        0, 0,
        bmpInfo.bmWidth,
        bmpInfo.bmHeight,
        RGB(255, 255, 255)
    );

    if (g_bFenceRedFrameOn)
    {
        RECT r;
        r.left = px;
        r.top = py;
        r.right = r.left + drawWidth;
        r.bottom = r.top + drawHeight;
        HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hdc, &r, red);
        DeleteObject(red);
        //��ȣ�ۿ�
        r.left = px+47;
        r.top = py+75;
        r.right = r.left + 32;
        r.bottom = r.top + 40;
        HBRUSH green = CreateSolidBrush(RGB(0, 255, 0));
        FrameRect(hdc, &r, green);
        DeleteObject(green);
    }

    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}


void House::SetTilePosition(int tileX, int tileY)
{
    x = tileX;
    y = tileY;
}

PlaceableType House::GetPlaceableType() const
{
    return PlaceableType::House;
}

RECT House::GetCollisionRect()
{
    return RECT();
}


//std::vector<RECT> House::GetCollisionRects()const
//{
//    std::vector<RECT> rects;
//    rects.push_back(GetBoundingBox());     // �� ��ü �浹
//    rects.push_back(GetDoorBoundingBox()); // �� �浹
//    return rects;
//}

//RECT House::GetBoundingBox()const
//{
//    BITMAP bmpInfo;
//    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
//
//    RECT rect;
//    rect.left = x + 8;  // ��
//    rect.top = y + 5;        //��
//    rect.right = rect.left + bmpInfo.bmWidth + 20; //������
//    rect.bottom = rect.top + bmpInfo.bmHeight + 15; //�Ʒ�
//    return rect;
//
//}
//
//RECT House::GetDoorBoundingBox()const
//{
//    BITMAP bmpInfo;
//    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
//
//    RECT rect;
//    rect.left = x + 60;  // ��
//    rect.top = y + 100;        //��
//    rect.right = rect.left + bmpInfo.bmWidth - 48; //������
//    rect.bottom = rect.top + bmpInfo.bmHeight - 80; //�Ʒ�
//    return rect;
//}
//


void House::Update()
{
}

