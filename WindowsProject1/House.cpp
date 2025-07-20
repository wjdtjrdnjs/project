#include "House.h"
House::House()
{
    // 생성자에서 한 번만 비트맵 로드
    hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(image), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBmp)
    {
        // 메모리 DC 생성 후 비트맵 선택
        HDC screenDC = GetDC(NULL);
        memDC = CreateCompatibleDC(screenDC);
        ReleaseDC(NULL, screenDC);

        SelectObject(memDC, hBmp);
    }
}

House::~House() //동물 소멸자
{
    if (memDC) DeleteDC(memDC);
    if (hBmp) DeleteObject(hBmp);
}



void House::Render(HDC hdc)  //동물 생성
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
    //문
    r = GetDoorBoundingBox();
    b = CreateSolidBrush(RGB(0, 255, 255));
    FrameRect(hdc, &r, b);
    DeleteObject(b);
}

std::vector<RECT> House::GetCollisionRects()const
{
    std::vector<RECT> rects;
    rects.push_back(GetBoundingBox());     // 집 본체 충돌
    rects.push_back(GetDoorBoundingBox()); // 문 충돌
    return rects;
}

RECT House::GetBoundingBox()const
{
    BITMAP bmpInfo;
    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

    RECT rect;
    rect.left = x + 8;  // 왼
    rect.top = y + 5;        //위
    rect.right = rect.left + bmpInfo.bmWidth + 20; //오른쪽
    rect.bottom = rect.top + bmpInfo.bmHeight + 15; //아래
    return rect;

}

RECT House::GetDoorBoundingBox()const
{
    BITMAP bmpInfo;
    GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

    RECT rect;
    rect.left = x + 60;  // 왼
    rect.top = y + 100;        //위
    rect.right = rect.left + bmpInfo.bmWidth - 48; //오른쪽
    rect.bottom = rect.top + bmpInfo.bmHeight - 80; //아래
    return rect;
}



void House::Update()
{
}

