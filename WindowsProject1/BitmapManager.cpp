#include "BitmapManager.h"
#include "Global.h"
#include "resource.h"
#include "Direction.h" 


BitmapManager::BitmapManager()
{
}

BitmapManager::~BitmapManager()
{
    Release();
}

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


void BitmapManager::LoadCropBitmap(const std::string& name, int resourceID)
{
    if (cropbitmapMap.find(name) != cropbitmapMap.end())
        return;

    HBITMAP bmp = (HBITMAP)LoadImage(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(resourceID),
        IMAGE_BITMAP,
        0, 0,
        LR_CREATEDIBSECTION
    );

    if (bmp) {
        cropbitmapMap[name] = bmp;
    }
}

HBITMAP BitmapManager::GetBitmap(const std::string& name)
{
    if (bitmapMap.find(name) != bitmapMap.end()) {
        return bitmapMap[name];
    }
  
    return nullptr;
}

void BitmapManager::LoadAllBitmaps()
{
    Load("Box", IDB_BITMAP24);
    //딸기
  LoadCropBitmap("Strawberry_0", IDB_BITMAP10);
  LoadCropBitmap("Strawberry_1", IDB_BITMAP11);
  LoadCropBitmap("Strawberry_2", IDB_BITMAP12);
  LoadCropBitmap("Strawberry_3", IDB_BITMAP13);
  LoadCropBitmap("Strawberry_4", IDB_BITMAP14);
  LoadCropBitmap("Strawberry_5", IDB_BITMAP15);
    //양파
  LoadCropBitmap("Onion_0", IDB_BITMAP2);
  LoadCropBitmap("Onion_1", IDB_BITMAP3);
  LoadCropBitmap("Onion_2", IDB_BITMAP4);
  LoadCropBitmap("Onion_3", IDB_BITMAP5);
  LoadCropBitmap("Onion_4", IDB_BITMAP6);
  LoadCropBitmap("Onion_5", IDB_BITMAP7);

    Load("House", IDB_BITMAP38);
    Load("Fence", IDB_BITMAP39);
    //타일
   Load("Grass", IDB_BITMAP22);
   Load("Path", IDB_BITMAP21);
   Load("Farm", IDB_BITMAP42);
   Load("Water", IDB_BITMAP43);
  
   //괭이
   Load("Hoe", IDB_BITMAP16);
   Load("Player_Hoe_Down_0", IDB_BITMAP45);
   Load("Player_Hoe_Down_1", IDB_BITMAP54);
   Load("Player_Hoe_Up_0", IDB_BITMAP46);
   Load("Player_Hoe_Up_1", IDB_BITMAP55);
   Load("Player_Hoe_Right_0", IDB_BITMAP47);
   Load("Player_Hoe_Right_1", IDB_BITMAP56);
   Load("Player_Hoe_Left_0", IDB_BITMAP48);
   Load("Player_Hoe_Left_1", IDB_BITMAP57);
   //도끼
   Load("Axe", IDB_BITMAP40);
   //물뿌리개
   Load("Watering", IDB_BITMAP41);
   Load("Player_Watering_Down_0", IDB_BITMAP31);
   Load("Player_Watering_Down_1", IDB_BITMAP50);
   Load("Player_Watering_Up_0", IDB_BITMAP32);
   Load("Player_Watering_Up_1", IDB_BITMAP51);
   Load("Player_Watering_Right_0", IDB_BITMAP33);
   Load("Player_Watering_Right_1", IDB_BITMAP52);
   Load("Player_Watering_Left_0", IDB_BITMAP34);
   Load("Player_Watering_Left_1", IDB_BITMAP53);


    //씨앗봉투들
   Load("딸기씨앗봉투", IDB_BITMAP18);
   Load("양파씨앗봉투", IDB_BITMAP17);

     //플레이어 비트맵
   Load("Player_Down", IDB_BITMAP27);
   Load("Player_UP", IDB_BITMAP28);
   Load("Player_LEFT", IDB_BITMAP30);
   Load("Player_RIGHT", IDB_BITMAP29);
   //NPC
   Load("Npc", IDB_BITMAP58);

    Load("Tree", IDB_BITMAP49);
}

HBITMAP BitmapManager::GetPlayerBitmap(Direction dir)
{
    switch (dir) {
    case Direction::DOWN:  return GetBitmap("Player_Down");
    case Direction::UP:    return GetBitmap("Player_UP");
    case Direction::LEFT:  return GetBitmap("Player_LEFT");
    case Direction::RIGHT: return GetBitmap("Player_RIGHT");
    default:               return GetBitmap("Player_Down");
    }
}

HBITMAP BitmapManager::GetTileBitmap(TileType type)
{
    switch (type) {
    case TileType::Grass:    return GetBitmap("Grass");
    case TileType::Farmland: return GetBitmap("Farm");
    case TileType::Water:    return GetBitmap("Water");
    case TileType::Path:     return GetBitmap("Path");
    default:                 return nullptr;
    }
    
}

HBITMAP BitmapManager::GetObjectBitmap(const InventoryItem& item)
{
    // 1. Crop
    switch (item.GetCategory())
    {
    case ItemCategory::Tool:      return GetToolBitmap(item.GetToolType());
    case ItemCategory::Crop:      return GetCroptBitmap(item.GetCropType());
    case ItemCategory::Seed:      return GetSeedBitmap(item.GetSeedType());
    case ItemCategory::Placeable: return GetObjectBitmap(item.GetPlaceableType());
    default:                      break;
    }
}

HBITMAP BitmapManager::GetObjectBitmap(PlaceableType type) {
    switch (type) {
    case PlaceableType::Box:     return GetBitmap("Box");
    case PlaceableType::Tree:    return GetBitmap("Tree");
    case PlaceableType::Fence:   return GetBitmap("Fence");
    case PlaceableType::House:   return GetBitmap("House");
    case PlaceableType::NPC:     return GetBitmap("Npc");
    default:                     return nullptr;
    }
}

HBITMAP BitmapManager::GetToolBitmap(ToolType type) {
    switch (type) {
    case ToolType::Hoe:         return GetBitmap("Hoe");
    case ToolType::Axe:         return GetBitmap("Axe");
    case ToolType::Watering:    return GetBitmap("Watering");
    default:                    return nullptr;
    }
}


HBITMAP BitmapManager::GetCroptBitmap(CropType type) 
{
    switch (type) {
    case CropType::Strawberry:   return GetBitmap("Strawberry");
    case CropType::Onion:        return GetBitmap("Onion");
    default:                     return nullptr;
    }
}

HBITMAP BitmapManager::GetSeedBitmap(SeedType type)
{
    switch (type) {
    case SeedType::StrawberrySeed:  return GetBitmap("딸기씨앗봉투");
    case SeedType::OnionSeed:       return GetBitmap("양파씨앗봉투");
    default:                        return nullptr;
    }
}

HBITMAP BitmapManager::GetCropGrowthBitmap(CropType type, int stage)
{
    std::string name;
    switch (type) {
    case CropType::Strawberry:  name = "Strawberry"; break;
    case CropType::Onion:       name = "Onion"; break;
    default:                    return nullptr;
    }

    std::string key = name + "_" + std::to_string(stage);
    return GetBitmapByName(key); // Load할 때 사용한 이름
}

HBITMAP BitmapManager::GetBitmapByName(const std::string& name)
{
    auto it = cropbitmapMap.find(name);
    if (it != cropbitmapMap.end()) {
        return it->second;
    }
    return nullptr;
}

HBITMAP BitmapManager::GetPlayerBitmap(Direction dir, ToolType toolType, int frame)
{
    std::string directionStr;
    switch (dir) {
    case Direction::DOWN:  directionStr = "Down"; break;
    case Direction::UP:    directionStr = "Up"; break;
    case Direction::LEFT:  directionStr = "Left"; break;
    case Direction::RIGHT: directionStr = "Right"; break;
    }

    std::string toolStr;
    switch (toolType) {
    case ToolType::Hoe:      toolStr = "Hoe"; break;
    case ToolType::Axe:      toolStr = "Axe"; break;
    case ToolType::Watering: toolStr = "Watering"; break;
    default:                 toolStr = "Hoe"; break;
    }

    std::string key = "Player_" + toolStr + "_" + directionStr + "_" + std::to_string(frame);

    HBITMAP bmp = GetBitmap(key);

    return bmp;
}

void BitmapManager::Release()
{
    for (auto& pair : bitmapMap) {
        DeleteObject(pair.second);
    }
    bitmapMap.clear();

    for (auto& pair : cropbitmapMap) {
        DeleteObject(pair.second);
    }
    cropbitmapMap.clear();
    
}

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

//HBITMAP BitmapManager::GetAllBitMap(AllType type)
//{
//
//    //switch (type) {
//    //case AllType::None:
//    //    break;
//    //case AllType::Crop:
//    //    return GetBitmap("Crop");
//    //case AllType::Object:
//    //    return GetCroptBitmap(item.GetCropType());
//    //case AllType::Tool:
//    //    return GetBitmap("Tool");
//
// /*   case AllType::Tree:
//        return GetBitmap("Tree");
//    case AllType::House:
//        return GetBitmap("House");
//    case AllType::Fence:
//        return GetBitmap("Fence");
//    case AllType::Strawberry:
//        return GetBitmap("Strawberry");
//    case AllType::Onion:
//        return GetBitmap("Onion");
//    case AllType::strawberryseed:
//        return GetBitmap("딸기씨앗봉투");
//    case AllType::onionseed:
//        return GetBitmap("양파씨앗봉투");*/
//    }
//    return nullptr;
//}
