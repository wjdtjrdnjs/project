#include "BitmapManager.h"

void BitmapManager::Load(HINSTANCE hInstance)
{
    std::vector<HBITMAP> onionStages;
    std::vector<HBITMAP> strawberryStages;
    std::vector<HBITMAP> playerBitmaps;

    for (int i = 0; i < 6; ++i) { // IDB_BITMAP10 ~ IDB_BITMAP15까지 딸기 씨앗~성숙
        
        HBITMAP bmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP10 + i), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        strawberryStages.push_back(bmp);
    }
    growthBitmaps[CropType::Strawberry] = strawberryStages;
    for (int i = 0; i < 6; ++i) { // IDB_BITMAP2 ~ IDB_BITMAP7까지 양파 씨앗~성숙
        HBITMAP bmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2 + i), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        onionStages.push_back(bmp);
    }
    growthBitmaps[CropType::Onion] = onionStages;
    
    //사용자
    for (int i = 0; i < 4; ++i) {
        HBITMAP playerBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_IDLE + i), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
        Direction dir = static_cast<Direction>(i);
        PLY[dir].push_back(playerBmp);
        playerBitmaps.push_back(playerBmp);  //4장
    }
    bitmapMap[IDB_Tile] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_Tile), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

    // 작물 비트맵 추가 딸기(1)양파(9) 
    bitmapMap[IDB_BITMAP1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    bitmapMap[IDB_BITMAP9] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP9), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    //딸기씨앗(18)과 양파씨앗(17) 봉투
    bitmapMap[IDB_BITMAP18] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP18), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    bitmapMap[IDB_BITMAP17] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP17), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    //임시 괭이16 도끼40 물뿌리개41
    bitmapMap[IDB_BITMAP16] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP16), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    bitmapMap[IDB_BITMAP40] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP40), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    bitmapMap[IDB_BITMAP41] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP41), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    //울타리
    bitmapMap[IDB_BITMAP39] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP39), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
 
   
}

const std::vector<HBITMAP>& BitmapManager::GetGrowthBitmaps(CropType type) {
    static std::vector<HBITMAP> empty;  // 빈 벡터 (예외 방지용)
    if (growthBitmaps.count(type))
        return growthBitmaps[type];
    return empty;
}


HBITMAP BitmapManager::GetBitmap(int resourceId)
{
    auto it = bitmapMap.find(resourceId);
    if (it != bitmapMap.end()) {
        return it->second;
    }

    OutputDebugString(L"[BitmapManager] Bitmap NOT FOUND for resourceId\n");
    return nullptr;
}

HBITMAP BitmapManager::GetBitmapForCrop(CropType type) { //가져온 타입으로 그림 돌려줌
    switch (type) {
    case CropType::Strawberry: //딸기
        return GetBitmap(IDB_BITMAP1);
    case CropType::Onion: //양파
        return GetBitmap(IDB_BITMAP9);
    case CropType::hoe:  //괭이
        return GetBitmap(IDB_BITMAP16);
    case CropType::Axe:  //도끼
        return GetBitmap(IDB_BITMAP40);
    case CropType::watering:  //물뿌리개
        return GetBitmap(IDB_BITMAP41);
    case CropType::Strawberry_1: //딸기봉투
        return GetBitmap(IDB_BITMAP18);
    case CropType::Onion_1: //양파봉투
        return GetBitmap(IDB_BITMAP17);
    case CropType::Fence: //울타리
        return GetBitmap(IDB_BITMAP39);
    default: //없음
        return nullptr;
    }
}

HBITMAP BitmapManager::GetBitmapFence()
{
    
    return bitmapMap[IDB_BITMAP39];
}

void BitmapManager::Release()
{
    for (auto& pair : bitmapMap)
        DeleteObject(pair.second);
    bitmapMap.clear();

    for (auto& pair : growthBitmaps) {
        for (auto& bmp : pair.second) {
            if (bmp) DeleteObject(bmp);
        }
    }
    growthBitmaps.clear();
}