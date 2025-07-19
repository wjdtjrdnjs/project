#include "Crop.h"
#include "RenderManager.h"
#include "GameObjectManager.h"

Crop::Crop(CropType type) : type(type), growthStage(0), growthTimer(0) {
    growthBitmaps = BitmapManager::Instance().GetGrowthBitmaps(type);

    if (!growthBitmaps.empty())
        bitmap = growthBitmaps[0]; // 첫 단계 비트맵
}
Crop::~Crop()
{
   
}
void Crop::Update()  //성관 관리
{
    int tileX = GetX() / tileSize;;
    int tileY = GetY() / tileSize;;
    if (!Map::IsWatered(tileX, tileY)) { //땅에 물을 뿌리지 않으면 작물 성장X
        return;
    }
    growthTimer += 16; 
    if (growthTimer >= growthInterval && growthStage < maxGrowthStage - 1)
    {
        growthStage++; //작물 성장 단계 +1
        growthTimer = 0;
        bitmap = growthBitmaps[growthStage]; // 다음 단계로 성장 ::이미지 바꿔주기
    }
}

void Crop::Install(int tileX, int tileY, Player* player)
{
    int tool = player->GetSelectedTool();
    InventoryItem* inv = player->GetInventory();
    if ((Map::GetTile(tileX, tileY) == TILE_Path || Map::GetTile(tileX, tileY) == Tile_FarmLand )&&!GameObjectManager::Instance().GetCropAt(tileX, tileY)) //중복설치 안되게


    {

        if (inv[tool].count > 0) // 1개 이상일 때
        {
            CropType baseCropType = CropType::None; //처음은 빈손
            if (inv[tool].type == CropType::Strawberry_1) baseCropType = CropType::Strawberry; //딸기씨앗 봉투면 딸기 
            else if (inv[tool].type == CropType::Onion_1) baseCropType = CropType::Onion;     //양파씨앗 봉투면 양파 

            if (baseCropType != CropType::None) { //빈손이 아닐 때
                Crop* crop = new Crop(baseCropType);  //선택된 작물 정보 가져옴
                crop->SetPosition(tileX * tileSize, tileY * tileSize); //설치할 위치
                GameObjectManager::Instance().AddCrop(crop);  //작물 추가
                inv[tool].count--;  // 들고있는 아이템 -1
                if (inv[tool].count == 0) //들고있는 아이템 개수가 0개이다
                    inv[tool].type = CropType::None; //아이템이 0개면 빈 슬롯
            }
        }
    }
}
void Crop::Remove(int tileX, int tileY, Player* player)
{
    Crop* crop = GameObjectManager::Instance().GetCropAt(tileX, tileY); //선택된 타일 위에 무엇이 있는지 확인 
    if (crop && crop->IsFullyGrown()) { //작물이 있고 성장이 끝았을 때
        CropType type = crop->GetType();  //작물 정보 가져옴
        GameObjectManager::Instance().RemoveCrop(crop);  //작물 삭제
        delete crop;  //작물 삭제
        player->AddItem(type);  //인벤토리에 추가
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
        drawX-2, drawY-5,
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

