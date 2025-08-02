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
    //    bitmap = growthBitmaps[0]; // ù �ܰ� ��Ʈ��
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
    //��ȣ�ۿ�
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
//void Crop::Update()  //���� ����
//{
//    int tileX = GetX() / tileSize;;
//    int tileY = GetY() / tileSize;;
//    WorldMap* worldMap = GameObjectManager::Instance().GetWorldMap();
//    if (!worldMap->IsWatered(tileX, tileY)) { //���� ���� �Ѹ��� ������ �۹� ����X
//        return;
//    }
//    growthTimer += 16; 
//    if (growthTimer >= growthInterval && growthStage < maxGrowthStage - 1)
//    {
//        growthStage++; //�۹� ���� �ܰ� +1
//        growthTimer = 0;
//        bitmap = growthBitmaps[growthStage]; // ���� �ܰ�� ���� ::�̹��� �ٲ��ֱ�
//    }
//}
//
//void Crop::Install(int tileX, int tileY, InventoryComponent& inventory)
//{
//    WorldMap* worldMap = GameObjectManager::Instance().GetWorldMap();
//
//    if ((worldMap->GetTile(tileX, tileY) == tile_path || worldMap->GetTile(tileX, tileY) == tile_farmland)&&!GameObjectManager::Instance().GetCropAt(tileX, tileY)) //�ߺ���ġ �ȵǰ�
//    {
//        int tool = inventory.GetSelectedTool();
//        if (inventory[tool].count > 0) // 1�� �̻��� ��
//        {
//            CropType baseCropType = CropType::None; //ó���� ���
//            if (inventory[tool].cropType == CropType::Strawberry_1) baseCropType = CropType::Strawberry; //���⾾�� ������ ���� 
//            else if (inventory[tool].cropType == CropType::Onion_1) baseCropType = CropType::Onion;     //���ľ��� ������ ���� 
//
//            if (baseCropType != CropType::None) { //����� �ƴ� ��
//                Crop* crop = new Crop(baseCropType);  //���õ� �۹� ���� ������
//                crop->SetPosition(tileX * tileSize, tileY * tileSize); //��ġ�� ��ġ
//                GameObjectManager::Instance().AddCrop(crop);  //�۹� �߰�
//                inventory[tool].count--;  // ����ִ� ������ -1
//                if (inventory[tool].count == 0) //����ִ� ������ ������ 0���̴�
//                    inventory[tool].itemType = ItemType::NONE; //�������� 0���� �� ����
//            }
//        }
//    }
//}
//void Crop::Remove(int tileX, int tileY, InventoryComponent& inventory)
//{
//
//    Crop* crop = GameObjectManager::Instance().GetCropAt(tileX, tileY); //���õ� Ÿ�� ���� ������ �ִ��� Ȯ�� 
//    if (!IsActive())
//    {
//        OutputDebugStringA("�۹� ��Ȯ �ȵ�(�ٸ� ��)\n");
//        return;
//    }
//    if (crop && crop->IsFullyGrown()) //�۹��� �ְ� ������ ������ ��
//    { 
//        CropType type = crop->GetType();  //�۹� ���� ������
//        GameObjectManager::Instance().RemoveCrop(crop);  //�۹� ����
//        delete crop;  //�۹� ����
//        inventory.AddItem(type);  //�κ��丮�� �߰�
//        OutputDebugStringA("�۹� ��Ȯ");
//    }
//}
//void Crop::Render(HDC hdc)
//{
//    if (!bitmap)  //��ϵ� ��Ʈ���� ������ ����
//        return;
//
//    HDC memDC = CreateCompatibleDC(hdc);
//    SelectObject(memDC, bitmap);
//
//    BITMAP bmp;
//    GetObject(bitmap, sizeof(bmp), &bmp);
//
//    // �߾� ������ ���� x, y�� Ÿ�� �߾� �������� ����
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
