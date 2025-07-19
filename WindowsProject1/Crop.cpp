#include "Crop.h"
#include "RenderManager.h"
#include "GameObjectManager.h"

Crop::Crop(CropType type) : type(type), growthStage(0), growthTimer(0) {
    growthBitmaps = BitmapManager::Instance().GetGrowthBitmaps(type);

    if (!growthBitmaps.empty())
        bitmap = growthBitmaps[0]; // ù �ܰ� ��Ʈ��
}
Crop::~Crop()
{
   
}
void Crop::Update()  //���� ����
{
    int tileX = GetX() / tileSize;;
    int tileY = GetY() / tileSize;;
    if (!Map::IsWatered(tileX, tileY)) { //���� ���� �Ѹ��� ������ �۹� ����X
        return;
    }
    growthTimer += 16; 
    if (growthTimer >= growthInterval && growthStage < maxGrowthStage - 1)
    {
        growthStage++; //�۹� ���� �ܰ� +1
        growthTimer = 0;
        bitmap = growthBitmaps[growthStage]; // ���� �ܰ�� ���� ::�̹��� �ٲ��ֱ�
    }
}

void Crop::Install(int tileX, int tileY, Player* player)
{
    int tool = player->GetSelectedTool();
    InventoryItem* inv = player->GetInventory();
    if ((Map::GetTile(tileX, tileY) == TILE_Path || Map::GetTile(tileX, tileY) == Tile_FarmLand )&&!GameObjectManager::Instance().GetCropAt(tileX, tileY)) //�ߺ���ġ �ȵǰ�


    {

        if (inv[tool].count > 0) // 1�� �̻��� ��
        {
            CropType baseCropType = CropType::None; //ó���� ���
            if (inv[tool].type == CropType::Strawberry_1) baseCropType = CropType::Strawberry; //���⾾�� ������ ���� 
            else if (inv[tool].type == CropType::Onion_1) baseCropType = CropType::Onion;     //���ľ��� ������ ���� 

            if (baseCropType != CropType::None) { //����� �ƴ� ��
                Crop* crop = new Crop(baseCropType);  //���õ� �۹� ���� ������
                crop->SetPosition(tileX * tileSize, tileY * tileSize); //��ġ�� ��ġ
                GameObjectManager::Instance().AddCrop(crop);  //�۹� �߰�
                inv[tool].count--;  // ����ִ� ������ -1
                if (inv[tool].count == 0) //����ִ� ������ ������ 0���̴�
                    inv[tool].type = CropType::None; //�������� 0���� �� ����
            }
        }
    }
}
void Crop::Remove(int tileX, int tileY, Player* player)
{
    Crop* crop = GameObjectManager::Instance().GetCropAt(tileX, tileY); //���õ� Ÿ�� ���� ������ �ִ��� Ȯ�� 
    if (crop && crop->IsFullyGrown()) { //�۹��� �ְ� ������ ������ ��
        CropType type = crop->GetType();  //�۹� ���� ������
        GameObjectManager::Instance().RemoveCrop(crop);  //�۹� ����
        delete crop;  //�۹� ����
        player->AddItem(type);  //�κ��丮�� �߰�
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

