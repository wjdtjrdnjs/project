#include "BitmapManager.h"
#include "resource.h"
#include "Crop.h"  // CropType enum 선언 위치

std::map<int, HBITMAP> BitmapManager::bitmapMap;

void BitmapManager::Load(HINSTANCE hInstance)
{
    bitmapMap[IDB_IDLE] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_IDLE), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    bitmapMap[IDB_BITMAP2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    bitmapMap[IDB_BITMAP3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    bitmapMap[IDB_Tile] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_Tile), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

    // 작물 비트맵 추가 딸기(1)양파(9) 
    bitmapMap[IDB_BITMAP1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    bitmapMap[IDB_BITMAP9] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP9), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    //딸기씨앗(18)과 양파씨앗(17) 봉투
    bitmapMap[IDB_BITMAP18] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP18), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    bitmapMap[IDB_BITMAP17] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP17), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    //임시 괭이
    bitmapMap[IDB_BITMAP16] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP16), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

 
}

HBITMAP BitmapManager::GetBitmap(int resourceId)
{
    if (bitmapMap.count(resourceId))
        return bitmapMap[resourceId];
    return nullptr;
}

HBITMAP BitmapManager::GetBitmapForCrop(CropType type) { //가져온 타입으로 그림 돌려줌
    switch (type) {
    case CropType::Strawberry: //딸기
        return GetBitmap(IDB_BITMAP1);
    case CropType::Onion: //양파
        return GetBitmap(IDB_BITMAP9);
    case CropType::Stone:  //괭이
        return GetBitmap(IDB_BITMAP16);
    case CropType::Strawberry_1: //딸기봉투
        return GetBitmap(IDB_BITMAP18);
    case CropType::Onion_1: //양파봉투
        return GetBitmap(IDB_BITMAP17);
    default: //없음
        return nullptr;
    }
}

void BitmapManager::Release()
{
    for (auto& pair : bitmapMap)
        DeleteObject(pair.second);
    bitmapMap.clear();
}
