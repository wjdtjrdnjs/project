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
    void Load(const std::string& name, int resourceID);// 초기 로딩
    void LoadCropBitmap(const std::string& name, int resourceID);// 초기 로딩
     
     HBITMAP GetBitmap(const std::string& name);           // 비트맵 가져오기

     void LoadAllBitmaps();

     void Release();                              // 메모리 해제

     HBITMAP GetObjectBitmap(const InventoryItem& item);
     HBITMAP GetObjectBitmap(PlaceableType type);;  //설치
     HBITMAP GetCroptBitmap(CropType type);     //작물
     HBITMAP GetTileBitmap(TileType type);  //타일

     //---플레이어 방향--
     HBITMAP GetPlayerBitmap(Direction dir, ToolType toolType, int frame);
     HBITMAP GetPlayerBitmap(Direction  dir);

     HBITMAP GetToolBitmap(ToolType type); //도구
     HBITMAP GetSeedBitmap(SeedType type); //씨앗봉투
     HBITMAP GetCropGrowthBitmap(CropType type, int stage);  //작물 성장
     HBITMAP GetBitmapByName(const std::string& name);  //

    
private:
     std::unordered_map<std::string, HBITMAP> bitmapMap;
     std::map<std::string, HBITMAP> cropbitmapMap;
};

//public
// HBITMAP GetAllBitMap(AllType type);
    // HBITMAP GetBitmapForCrop(InventoryItem type);
    // HBITMAP GetBitmapFence();
     /*const std::vector<HBITMAP>& GetGrowthBitmaps(CropType type);
     const std::map<Direction, std::vector<HBITMAP>>& GetPlayerBitmaps() {
        return PLY;
    }*/

//private
 //std::map<int, HBITMAP> bitmapMap;            // 비트맵 저장소
     //std::map<CropType, std::vector<HBITMAP>> growthBitmaps;
     //std::map<Direction, std::vector<HBITMAP>> PLY;