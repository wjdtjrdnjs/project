 #pragma once
#include <windows.h>
#include <vector>
#include <map>
#include "CropType.h"
#include "resource.h"
#include "player.h"
#include "SingletonT.h"

// 
class BitmapManager:public SingletonT<BitmapManager>
{
public:
     void Load(HINSTANCE hInstance);              // 초기 로딩
     HBITMAP GetBitmap(int resourceId);           // 비트맵 가져오기
     void Release();                              // 메모리 해제
     HBITMAP GetBitmapForCrop(CropType type);
     const std::vector<HBITMAP>& GetGrowthBitmaps(CropType type);
     const std::map<Direction, std::vector<HBITMAP>>& GetPlayerBitmaps() {
        return PLY;
    }
private:
     std::map<int, HBITMAP> bitmapMap;            // 비트맵 저장소
     std::map<CropType, std::vector<HBITMAP>> growthBitmaps;
     std::map<Direction, std::vector<HBITMAP>> PLY;


};