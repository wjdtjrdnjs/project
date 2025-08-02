#include "Crop.h"
#include "RenderManager.h"
#include "GameObjectManager.h"
#include "PlayerController.h"
#include "InventoryComponent.h"
#include "InventoryItem.h"
#include "InputManager.h"
#include "WorldMap.h"
#include "TileData.h"
#include "Global.h"
#include <string>

Crop::Crop(CropType type) //: type(type), growthStage(0), growthTimer(0)
{

    bitmap = BitmapManager::Instance().GetCroptBitmap(type);

    //if (!growthBitmaps.empty())
    //    bitmap = growthBitmaps[0]; // 첫 단계 비트맵
}
void Crop::Render(HDC hdc, int Tilesize)
{

   if (!bitmap) return;

    int px = tileX * Tilesize;
    int py = tileY * Tilesize;

    BITMAP bmpInfo;
    GetObject(bitmap, sizeof(bmpInfo), &bmpInfo);

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bitmap);

    TransparentBlt(hdc,
        px, py,
        Tilesize, Tilesize,
        memDC,
        0, 0,
        bmpInfo.bmWidth, bmpInfo.bmHeight,
        RGB(255, 255, 255)
    );
    //상호작용
    if (g_bFenceRedFrameOn)
    {
        RECT r;
        r.left = px;
        r.top = py;
        r.right = r.left + 32;
        r.bottom = r.top + 32;
        HBRUSH b = CreateSolidBrush(RGB(0, 255, 0));
        FrameRect(hdc, &r, b);
        DeleteObject(b);
    }
 

    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
}
void Crop::SetTilePosition(int px, int py) { x = px; y = py; }

ObjectType Crop::GetObjectType() const
{
    return ObjectType::Crop;
}

RECT Crop::GetCollisionRect()
{
    return RECT();
}


//void Crop::Interact(Player& player)  {
//   // if (isRipe) {
//       // player.AddInventory(cropType);
//     //   RemoveFromMap();
//    }
//}


//Crop::~Crop()
//{
//   
//}
//
//void Crop::Update()  //성관 관리
//{
//    int tileX = GetX() / tileSize;;
//    int tileY = GetY() / tileSize;;
//    WorldMap* worldMap = GameObjectManager::Instance().GetWorldMap();
//    if (!worldMap->IsWatered(tileX, tileY)) { //땅에 물을 뿌리지 않으면 작물 성장X
//        return;
//    }
//    growthTimer += 16; 
//    if (growthTimer >= growthInterval && growthStage < maxGrowthStage - 1)
//    {
//        growthStage++; //작물 성장 단계 +1
//        growthTimer = 0;
//        bitmap = growthBitmaps[growthStage]; // 다음 단계로 성장 ::이미지 바꿔주기
//    }
//}
//
//void Crop::Install(int tileX, int tileY, InventoryComponent& inventory)
//{
//    WorldMap* worldMap = GameObjectManager::Instance().GetWorldMap();
//
//    if ((worldMap->GetTile(tileX, tileY) == tile_path || worldMap->GetTile(tileX, tileY) == tile_farmland)&&!GameObjectManager::Instance().GetCropAt(tileX, tileY)) //중복설치 안되게
//    {
//        int tool = inventory.GetSelectedTool();
//        if (inventory[tool].count > 0) // 1개 이상일 때
//        {
//            CropType baseCropType = CropType::None; //처음은 빈손
//            if (inventory[tool].cropType == CropType::Strawberry_1) baseCropType = CropType::Strawberry; //딸기씨앗 봉투면 딸기 
//            else if (inventory[tool].cropType == CropType::Onion_1) baseCropType = CropType::Onion;     //양파씨앗 봉투면 양파 
//
//            if (baseCropType != CropType::None) { //빈손이 아닐 때
//                Crop* crop = new Crop(baseCropType);  //선택된 작물 정보 가져옴
//                crop->SetPosition(tileX * tileSize, tileY * tileSize); //설치할 위치
//                GameObjectManager::Instance().AddCrop(crop);  //작물 추가
//                inventory[tool].count--;  // 들고있는 아이템 -1
//                if (inventory[tool].count == 0) //들고있는 아이템 개수가 0개이다
//                    inventory[tool].itemType = ItemType::NONE; //아이템이 0개면 빈 슬롯
//            }
//        }
//    }
//}
//void Crop::Remove(int tileX, int tileY, InventoryComponent& inventory)
//{
//
//    Crop* crop = GameObjectManager::Instance().GetCropAt(tileX, tileY); //선택된 타일 위에 무엇이 있는지 확인 
//    if (!IsActive())
//    {
//        OutputDebugStringA("작물 수확 안됨(다른 맵)\n");
//        return;
//    }
//    if (crop && crop->IsFullyGrown()) //작물이 있고 성장이 끝았을 때
//    { 
//        CropType type = crop->GetType();  //작물 정보 가져옴
//        GameObjectManager::Instance().RemoveCrop(crop);  //작물 삭제
//        delete crop;  //작물 삭제
//        inventory.AddItem(type);  //인벤토리에 추가
//        OutputDebugStringA("작물 수확");
//    }
//}
//void Crop::Render(HDC hdc)
//{
//    if (!bitmap)  //등록된 비트맵이 없으면 리턴
//        return;
//
//    HDC memDC = CreateCompatibleDC(hdc);
//    SelectObject(memDC, bitmap);
//
//    BITMAP bmp;
//    GetObject(bitmap, sizeof(bmp), &bmp);
//
//    // 중앙 정렬을 위해 x, y를 타일 중앙 기준으로 조정
//    int drawX = x + (tileSize - bmp.bmWidth) / 2;
//    int drawY = y + (tileSize - bmp.bmHeight) / 2;
//
//    TransparentBlt(hdc,
//        drawX-2, drawY-5,
//        bmp.bmWidth+10, bmp.bmHeight+10,
//        memDC,
//        0, 0,
//        bmp.bmWidth, bmp.bmHeight,
//        RGB(255, 255, 255));
//
//    DeleteDC(memDC);
//}
//
//void Crop::Harvest()
//{
//    growthStage = 0;
//}
//
