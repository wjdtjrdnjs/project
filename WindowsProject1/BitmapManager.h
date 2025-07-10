    #pragma once
    #include <windows.h>
    #include <map>
    #include "Crop.h"
    class BitmapManager
    {
    public:
        static void Load(HINSTANCE hInstance);              // 초기 로딩
        static HBITMAP GetBitmap(int resourceId);           // 비트맵 가져오기
        static void Release();                              // 메모리 해제
        static HBITMAP GetBitmapForCrop(CropType type);
    private:
        static std::map<int, HBITMAP> bitmapMap;            // 비트맵 저장소
    };