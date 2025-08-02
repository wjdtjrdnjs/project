#include "Tree.h"
#include "BitmapManager.h"
#include "TileData.h"
#include "Global.h"
Tree::Tree()
{
	bmp = BitmapManager::Instance().GetObjectBitmap(ObjectType::Tree);
}

void Tree::Render(HDC hdc, int Tilesize)
{
    if (!bmp) return;
   

    int drawSize = 128;

    // 타일 기준 위치 계산
    int px = tileX * Tilesize;
    int py = tileY * Tilesize;

    // 출력 위치 보정
    // 비트맵이 타일보다 크면 중심이 어긋나기 때문에 보정 필요
    // 중심 정렬: 비트맵 중심이 타일 중앙에 오도록
    px -= (drawSize - Tilesize) / 2;
    py -= (drawSize - Tilesize);  // 발이 타일 아래쪽에 맞게

    BITMAP bmpInfo;
    GetObject(bmp, sizeof(bmpInfo), &bmpInfo);


    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

    TransparentBlt(hdc, px, py, drawSize, drawSize, memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));


    if (g_bFenceRedFrameOn)
    {
        RECT r;
        r.left = px;
        r.top = py;
        r.right = r.left + Tilesize;
        r.bottom = r.top + Tilesize;
        HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hdc, &r, red);
        DeleteObject(red);
        //상호작용
        r.left = px + 47;
        r.top = py + 75;
        r.right = r.left + 32;
        r.bottom = r.top + 40;
        HBRUSH green = CreateSolidBrush(RGB(0, 255, 0));
        FrameRect(hdc, &r, green);
        DeleteObject(green);
    }

   

  /*  TransparentBlt(hdc,
        px, py,
        Tilesize+35, Tilesize+35,
        memDC,
        0, 0,
        bmpInfo.bmWidth, bmpInfo.bmHeight,
        RGB(255, 255, 255)
    );*/
    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}

void Tree::SetTilePosition(int px, int py) { x = px; y = py; }

ObjectType Tree::GetObjectType() const
{
    return ObjectType::Tree;
}

RECT Tree::GetCollisionRect()
{
    return RECT();
}
