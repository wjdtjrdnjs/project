 #pragma once
#include <windows.h>
#include <vector>
#include <map>
#include "CropType.h"
#include "resource.h"
#include "player.h"
class BitmapManager
{
public:
    static void Load(HINSTANCE hInstance);              // 초기 로딩
    static HBITMAP GetBitmap(int resourceId);           // 비트맵 가져오기
    static void Release();                              // 메모리 해제
    static HBITMAP GetBitmapForCrop(CropType type);
    static const std::vector<HBITMAP>& GetGrowthBitmaps(CropType type);
    static const std::map<Direction, std::vector<HBITMAP>>& GetPlayerBitmaps() {
        return PLY;
    }
private:
    static std::map<int, HBITMAP> bitmapMap;            // 비트맵 저장소
    static std::map<CropType, std::vector<HBITMAP>> growthBitmaps;
    static std::map<Direction, std::vector<HBITMAP>> PLY;


};