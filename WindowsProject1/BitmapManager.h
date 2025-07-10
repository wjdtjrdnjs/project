    #pragma once
    #include <windows.h>
    #include <map>
    #include "Crop.h"
    class BitmapManager
    {
    public:
        static void Load(HINSTANCE hInstance);              // �ʱ� �ε�
        static HBITMAP GetBitmap(int resourceId);           // ��Ʈ�� ��������
        static void Release();                              // �޸� ����
        static HBITMAP GetBitmapForCrop(CropType type);
    private:
        static std::map<int, HBITMAP> bitmapMap;            // ��Ʈ�� �����
    };