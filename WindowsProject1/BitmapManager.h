 #pragma once
#include <windows.h>
#include <vector>
#include <map>
#include "CropType.h"
#include "ToolType.h"
#include "InventoryItem.h"
#include "resource.h"
#include "player.h"
#include "SingletonT.h"
#include "Direction.h" 
#include "TileData.h"
#include <unordered_map>
#include <string>
// 
class BitmapManager:public SingletonT<BitmapManager>
{
public:
    BitmapManager();
    ~BitmapManager();
    void Load(const std::string& name, int resourceID);// �ʱ� �ε�
    void LoadCropBitmap(const std::string& name, int resourceID);// �ʱ� �ε�
     
     HBITMAP GetBitmap(const std::string& name);           // ��Ʈ�� ��������

     void LoadAllBitmaps();

     void Release();                              // �޸� ����
     HBITMAP GetTileBitmap(TileType type);

     HBITMAP GetObjectBitmap(const InventoryItem& item);
     HBITMAP GetObjectBitmap(PlaceableType type);;
     HBITMAP GetCroptBitmap(CropType type);
     HBITMAP GetPlayerBitmap(Direction dir, ToolType toolType, int frame);
    HBITMAP GetPlayerBitmap(Direction  dir);

     HBITMAP GetToolBitmap(ToolType type);
     HBITMAP GetSeedBitmap(SeedType type);
     HBITMAP GetCropGrowthBitmap(CropType type, int stage);
     HBITMAP GetBitmapByName(const std::string& name);

    // HBITMAP GetAllBitMap(AllType type);
    // HBITMAP GetBitmapForCrop(InventoryItem type);
    // HBITMAP GetBitmapFence();
     /*const std::vector<HBITMAP>& GetGrowthBitmaps(CropType type);
     const std::map<Direction, std::vector<HBITMAP>>& GetPlayerBitmaps() {
        return PLY;
    }*/
private:
     //std::map<int, HBITMAP> bitmapMap;            // ��Ʈ�� �����
     //std::map<CropType, std::vector<HBITMAP>> growthBitmaps;
     //std::map<Direction, std::vector<HBITMAP>> PLY;
    
     std::unordered_map<std::string, HBITMAP> bitmapMap;
     std::map<std::string, HBITMAP> cropbitmapMap;
};