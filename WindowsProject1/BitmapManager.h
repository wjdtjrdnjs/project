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
     void Load(HINSTANCE hInstance);              // �ʱ� �ε�
     HBITMAP GetBitmap(int resourceId);           // ��Ʈ�� ��������
     void Release();                              // �޸� ����
     HBITMAP GetBitmapForCrop(CropType type);
     const std::vector<HBITMAP>& GetGrowthBitmaps(CropType type);
     const std::map<Direction, std::vector<HBITMAP>>& GetPlayerBitmaps() {
        return PLY;
    }
private:
     std::map<int, HBITMAP> bitmapMap;            // ��Ʈ�� �����
     std::map<CropType, std::vector<HBITMAP>> growthBitmaps;
     std::map<Direction, std::vector<HBITMAP>> PLY;


};