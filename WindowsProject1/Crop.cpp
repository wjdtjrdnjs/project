#include "Crop.h"

Crop::Crop(CropType type) : type(type), bitmap(nullptr), growthStage(0), growthTimer(0)
{
    switch (type) {  //Ÿ�Կ� ���� ��Ʈ�� ����
    case CropType::Strawberry:  //����
        for (int i = 0; i < maxGrowthStage; ++i) { // IDB_BITMAP10 ~ IDB_BITMAP15���� ���� ����~����
            HBITMAP bmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP10 + i),IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
            growthBitmaps.push_back(bmp);
        }
        break;
    case CropType::Onion:   //����
        for (int i = 0; i < maxGrowthStage ; ++i) { // IDB_BITMAP2 ~ IDB_BITMAP7���� ���� ����~����
            HBITMAP bmp = (HBITMAP)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_BITMAP2 + i),IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
            growthBitmaps.push_back(bmp);
        }
        break;
    }

    if (!growthBitmaps.empty())
        bitmap = growthBitmaps[0];  // �ʱ� ��Ʈ�� ����
}

Crop::~Crop()
{
    for (auto bmp : growthBitmaps) { // ��ϵ� ��Ʈ�� ����
        if (bmp) DeleteObject(bmp);
    }
}
void Crop::Update()  //���� ����
{
    growthTimer += 16;

    if (growthTimer >= growthInterval && growthStage < maxGrowthStage - 1)
    {
        growthStage++; //�۹� ���� �ܰ� +1
        growthTimer = 0;
        bitmap = growthBitmaps[growthStage]; // ���� �ܰ�� ���� ::�̹��� �ٲ��ֱ�
    }
}
void Crop::Render(HDC hdc)
{
    if (!bitmap)  //��ϵ� ��Ʈ���� ������ ����
        return;

    HDC memDC = CreateCompatibleDC(hdc);
    SelectObject(memDC, bitmap);

    BITMAP bmp;
    GetObject(bitmap, sizeof(bmp), &bmp);

    // �߾� ������ ���� x, y�� Ÿ�� �߾� �������� ����
    int drawX = x + (tileSize - bmp.bmWidth) / 2;
    int drawY = y + (tileSize - bmp.bmHeight) / 2;

    TransparentBlt(hdc,
        drawX, drawY,
        bmp.bmWidth+10, bmp.bmHeight+10,
        memDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255));

    DeleteDC(memDC);
}

void Crop::Harvest()
{
    growthStage = 0;
}
