#include "Animal.h"
Animal::Animal()
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

Animal::~Animal() //���� �Ҹ���
{
    if (memDC) DeleteDC(memDC);
    if (hBmp) DeleteObject(hBmp);
}



void Animal::Render(HDC hdc)  //���� ����
{
    if (!hBmp || !memDC)
        return;

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

    TransparentBlt(
        hdc,
        x, y,
        bmp.bmWidth+ Animalsize, bmp.bmHeight+ Animalsize,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );
}

void Animal::Update()
{
}

