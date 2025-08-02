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

    // Ÿ�� ���� ��ġ ���
    int px = tileX * Tilesize;
    int py = tileY * Tilesize;

    // ��� ��ġ ����
    // ��Ʈ���� Ÿ�Ϻ��� ũ�� �߽��� ��߳��� ������ ���� �ʿ�
    // �߽� ����: ��Ʈ�� �߽��� Ÿ�� �߾ӿ� ������
    px -= (drawSize - Tilesize) / 2;
    py -= (drawSize - Tilesize);  // ���� Ÿ�� �Ʒ��ʿ� �°�

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
        //��ȣ�ۿ�
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
