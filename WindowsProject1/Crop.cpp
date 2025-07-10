#include "Crop.h"

Crop::Crop(CropType type) : type(type), bitmap(nullptr), growthStage(0), growthTimer(0)
{
    switch (type) {  //타입에 따라 비트맵 적용
    case CropType::Strawberry:  //딸기
        for (int i = 0; i < maxGrowthStage; ++i) { // IDB_BITMAP10 ~ IDB_BITMAP15까지 딸기 씨앗~성숙
            HBITMAP bmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP10 + i),IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
            growthBitmaps.push_back(bmp);
        }
        break;
    case CropType::Onion:   //양파
        for (int i = 0; i < maxGrowthStage ; ++i) { // IDB_BITMAP2 ~ IDB_BITMAP7까지 양파 씨앗~성숙
            HBITMAP bmp = (HBITMAP)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_BITMAP2 + i),IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
            growthBitmaps.push_back(bmp);
        }
        break;
    }

    if (!growthBitmaps.empty())
        bitmap = growthBitmaps[0];  // 초기 비트맵 세팅
}

Crop::~Crop()
{
    for (auto bmp : growthBitmaps) { // 등록된 비트맵 삭제
        if (bmp) DeleteObject(bmp);
    }
}
void Crop::Update()  //성관 관리
{
    growthTimer += 16;

    if (growthTimer >= growthInterval && growthStage < maxGrowthStage - 1)
    {
        growthStage++; //작물 성장 단계 +1
        growthTimer = 0;
        bitmap = growthBitmaps[growthStage]; // 다음 단계로 성장 ::이미지 바꿔주기
    }
}
void Crop::Render(HDC hdc)
{
    if (!bitmap)  //등록된 비트맵이 없으면 리턴
        return;

    HDC memDC = CreateCompatibleDC(hdc);
    SelectObject(memDC, bitmap);

    BITMAP bmp;
    GetObject(bitmap, sizeof(bmp), &bmp);

    // 중앙 정렬을 위해 x, y를 타일 중앙 기준으로 조정
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
