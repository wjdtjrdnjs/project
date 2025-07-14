    #pragma once
#include <windows.h>
#include <vector>
    #include <map>
    #include "CropType.h"
    #include "resource.h"

    class BitmapManager
    {
    public:
        static void Load(HINSTANCE hInstance);              // �ʱ� �ε�
        static HBITMAP GetBitmap(int resourceId);           // ��Ʈ�� ��������
        static void Release();                              // �޸� ����
        static HBITMAP GetBitmapForCrop(CropType type);
        static const std::vector<HBITMAP>& GetGrowthBitmaps(CropType type);

    private:
        static std::map<int, HBITMAP> bitmapMap;            // ��Ʈ�� �����
        static std::map<CropType, std::vector<HBITMAP>> growthBitmaps;

    };