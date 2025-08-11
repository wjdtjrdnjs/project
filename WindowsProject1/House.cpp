#include "House.h"
#include "BitmapManager.h"
#include "Global.h" //충돌영역 on/off
#include "TileData.h"

House::House()
{
    bmp = BitmapManager::Instance().GetObjectBitmap(PlaceableType::House);
}

House::~House() //동물 소멸자
{
   
}

void House::Render(HDC hdc, int tileSize)
{
    if (!bmp) return;

    const int drawWidth = 96;   // 그리고 싶은 폭 (크게 설정)
    const int drawHeight = 120;  // 그리고 싶은 높이

    int px = tileX * tileSize;
    int py = tileY * tileSize;

    // 중심 정렬 보정: 타일 기준으로 비트맵 중심이 해당 타일 중앙에 위치하게 조정
    px -= (drawWidth - tileSize) / 2;
    py -= (drawHeight - tileSize);  // 아래쪽 발 기준 정렬

    // 필요하면 살짝 내리기 (타일에 발이 안붙을 때)
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
        //상호작용
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
//    rects.push_back(GetBoundingBox());     // 집 본체 충돌
//    rects.push_back(GetDoorBoundingBox()); // 문 충돌
//    return rects;
//}

//RECT House::GetBoundingBox()const
//{
//    BITMAP bmpInfo;
//    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
//
//    RECT rect;
//    rect.left = x + 8;  // 왼
//    rect.top = y + 5;        //위
//    rect.right = rect.left + bmpInfo.bmWidth + 20; //오른쪽
//    rect.bottom = rect.top + bmpInfo.bmHeight + 15; //아래
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
//    rect.left = x + 60;  // 왼
//    rect.top = y + 100;        //위
//    rect.right = rect.left + bmpInfo.bmWidth - 48; //오른쪽
//    rect.bottom = rect.top + bmpInfo.bmHeight - 80; //아래
//    return rect;
//}
//


void House::Update()
{
}

