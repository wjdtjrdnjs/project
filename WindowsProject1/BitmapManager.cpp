#include "BitmapManager.h"
#include "Global.h"
#include "resource.h"
#include "Direction.h" 
//
// 
// extern HINSTANCE hModule;  // 인스턴스 핸들
//void BitmapManager::Load(HINSTANCE hInstance)
//{
//    std::vector<HBITMAP> onionStages;
//    std::vector<HBITMAP> strawberryStages;
//    std::vector<HBITMAP> playerBitmaps;
//
//    for (int i = 0; i < 6; ++i) { // IDB_BITMAP10 ~ IDB_BITMAP15까지 딸기 씨앗~성숙
//        
//        HBITMAP bmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP10 + i), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
//        strawberryStages.push_back(bmp);
//    }
//    growthBitmaps[CropType::Strawberry] = strawberryStages;
//    for (int i = 0; i < 6; ++i) { // IDB_BITMAP2 ~ IDB_BITMAP7까지 양파 씨앗~성숙
//        HBITMAP bmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2 + i), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
//        onionStages.push_back(bmp);
//    }
//    growthBitmaps[CropType::Onion] = onionStages;
//    
//    //사용자
//    for (int i = 0; i < 16; ++i) {
//        HBITMAP playerBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP27 + i), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//        Direction dir = static_cast<Direction>(i);
//        PLY[dir].push_back(playerBmp);
//        playerBitmaps.push_back(playerBmp);  //4장
//    }
//    bitmapMap[IDB_Tile] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_Tile), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//
//    // 작물 비트맵 추가 딸기(1)양파(9) 
//    bitmapMap[IDB_BITMAP1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//    bitmapMap[IDB_BITMAP9] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP9), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//    //딸기씨앗(18)과 양파씨앗(17) 봉투
//    bitmapMap[IDB_BITMAP18] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP18), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//    bitmapMap[IDB_BITMAP17] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP17), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//    //임시 괭이16 도끼40 물뿌리개41
//    bitmapMap[IDB_BITMAP16] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP16), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//    bitmapMap[IDB_BITMAP40] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP40), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//    bitmapMap[IDB_BITMAP41] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP41), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//    //울타리
//    bitmapMap[IDB_BITMAP39] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP39), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
//    //문
//    bitmapMap[IDB_BITMAP26] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP26), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
// 
//   
//}

//const std::vector<HBITMAP>& BitmapManager::GetGrowthBitmaps(CropType type) {
//    static std::vector<HBITMAP> empty;  // 빈 벡터 (예외 방지용)
//    if (growthBitmaps.count(type))
//        return growthBitmaps[type];
//    return empty;
//}

BitmapManager::BitmapManager()
{
}

BitmapManager::~BitmapManager()
{
    Release();
}


//HBITMAP BitmapManager::GetBitmap(int resourceId)
//{
//    auto it = bitmapMap.find(resourceId);
//    if (it != bitmapMap.end()) {
//        return it->second;
//    }
//
//    OutputDebugString(L"[BitmapManager] Bitmap NOT FOUND for resourceId\n");
//    return nullptr;
//}

//HBITMAP BitmapManager::GetBitmapForCrop(InventoryItem item) { //가져온 타입으로 그림 돌려줌
//    if (item.itemType == ItemType::CROP)
//    {
//        switch (item.cropType)
//        {
//        case CropType::Strawberry: //딸기
//            return GetBitmap(IDB_BITMAP1);
//        case CropType::Onion: //양파
//            return GetBitmap(IDB_BITMAP9);
//        case CropType::Strawberry_1: //딸기봉투
//            return GetBitmap(IDB_BITMAP18);
//        case CropType::Onion_1: //양파봉투
//            return GetBitmap(IDB_BITMAP17);
//        case CropType::Fence: //울타리
//            return GetBitmap(IDB_BITMAP39);
//        default: //없음
//            return nullptr;
//        }
//    }
//    else if (item.itemType == ItemType::TOOL)
//    {
//        switch (item.toolType)
//        {
//        case Tool::hoe:  //괭이
//            return GetBitmap(IDB_BITMAP16);
//        case Tool::Axe:  //도끼
//            return GetBitmap(IDB_BITMAP40);
//        case Tool::watering:  //물뿌리개
//            return GetBitmap(IDB_BITMAP41);
//        default: //없음
//            return nullptr;
//        }
//    }
//    
//         
//}

//HBITMAP BitmapManager::GetBitmapFence()
//{
//    
//    return bitmapMap[IDB_BITMAP39];
//}

void BitmapManager::Load(const std::string& name, int resourceID)
{
    if (bitmapMap.find(name) != bitmapMap.end())
        return; // 이미 있음
    HBITMAP bmp = (HBITMAP)LoadImage(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(resourceID),
        IMAGE_BITMAP,
        0, 0,
        LR_CREATEDIBSECTION
    );

   
    if (bmp) {

        bitmapMap[name] = bmp;
    }
}

HBITMAP BitmapManager::GetBitmap(const std::string& name)
{
    if (bitmapMap.find(name) != bitmapMap.end())
        return bitmapMap[name];
  
    return nullptr;
}

HBITMAP BitmapManager::GetTileBitmap(TileType type)
{
    switch (type) {
    case TileType::Grass:
        return GetBitmap("Grass");
    case TileType::Farmland:
        return GetBitmap("Farm");
    case TileType::Water:
        return GetBitmap("Water");
    case TileType::Path:
        return GetBitmap("Path");
    }
    return nullptr;
}

HBITMAP BitmapManager::GetObjectBitmap(ObjectType type)
{
    switch (type) {
    case ObjectType::Box:
        return GetBitmap("Box");
    case ObjectType::Crop:
        return GetBitmap("Crop");
    case ObjectType::Tree:
        return GetBitmap("Tree");
    }
    return nullptr;
}

HBITMAP BitmapManager::GetCroptBitmap(CropType type)
{
    switch (type) {
    case CropType::Strawberry:
        return GetBitmap("Strawberry");
    case CropType::Onion:
        return GetBitmap("Onion");
    case CropType::strawberryseed:
        return GetBitmap("딸기씨앗봉투");
    case CropType::onionseed:
        return GetBitmap("양파씨앗봉투");
    }
    return nullptr;
}
HBITMAP BitmapManager::GetPlayerBitmap(Direction dir)
{
    switch (dir) {
    case Direction::DOWN:
        return GetBitmap("Player_Down");
    case Direction::UP:
        return GetBitmap("Player_UP");
    case Direction::LEFT:
        return GetBitmap("Player_LEFT");
    case Direction::RIGHT:
        return GetBitmap("Player_RIGHT");
    }
    return GetBitmap("Player_Down"); ;
}
void BitmapManager::Release()
{
    for (auto& pair : bitmapMap) {
        DeleteObject(pair.second);
    }
    bitmapMap.clear();
}

