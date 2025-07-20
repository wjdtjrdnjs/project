#include "House.h"
House::House()
{
    // �����ڿ��� �� ���� ��Ʈ�� �ε�
    hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(image), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBmp)
    {
        // �޸� DC ���� �� ��Ʈ�� ����
        HDC screenDC = GetDC(NULL);
        memDC = CreateCompatibleDC(screenDC);
        ReleaseDC(NULL, screenDC);

        SelectObject(memDC, hBmp);
    }
}

House::~House() //���� �Ҹ���
{
    if (memDC) DeleteDC(memDC);
    if (hBmp) DeleteObject(hBmp);
}



void House::Render(HDC hdc)  //���� ����
{
    if (!hBmp || !memDC)
        return;

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);



    TransparentBlt(
        hdc,
        x, y,
        bmp.bmWidth + Housesize, bmp.bmHeight + Housesize,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );
    RECT r = GetBoundingBox();
    HBRUSH b = CreateSolidBrush(RGB(255, 0, 0));
    FrameRect(hdc, &r, b);
    DeleteObject(b);
    //��
    r = GetDoorBoundingBox();
    b = CreateSolidBrush(RGB(0, 255, 255));
    FrameRect(hdc, &r, b);
    DeleteObject(b);
}

std::vector<RECT> House::GetCollisionRects()const
{
    std::vector<RECT> rects;
    rects.push_back(GetBoundingBox());     // �� ��ü �浹
    rects.push_back(GetDoorBoundingBox()); // �� �浹
    return rects;
}

RECT House::GetBoundingBox()const
{
    BITMAP bmpInfo;
    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

    RECT rect;
    rect.left = x + 8;  // ��
    rect.top = y + 5;        //��
    rect.right = rect.left + bmpInfo.bmWidth + 20; //������
    rect.bottom = rect.top + bmpInfo.bmHeight + 15; //�Ʒ�
    return rect;

}

RECT House::GetDoorBoundingBox()const
{
    BITMAP bmpInfo;
    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

    RECT rect;
    rect.left = x + 60;  // ��
    rect.top = y + 100;        //��
    rect.right = rect.left + bmpInfo.bmWidth - 48; //������
    rect.bottom = rect.top + bmpInfo.bmHeight - 80; //�Ʒ�
    return rect;
}



void House::Update()
{
}

