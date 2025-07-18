#pragma once
#define map_y 17
#define map_x 36
#include "resource.h"
#include <windows.h>
#include <vector>


enum TileType_1 {
    TILE_Floor,  //�ٴ�
};

class MyRoomMap
{
public:
    MyRoomMap();
    ~MyRoomMap();

    static void Init(); //�ʱ� ��
   
    void Render(HDC hdc);

private:
    static TileType_1 tiles_1[map_y][map_x];
    std::vector<HBITMAP> Tile_1;    // ��Ʈ�� �ڵ� ����
    std::vector<HDC> TileDCs_1;     // �� Ÿ�� ��Ʈ�ʿ� �޸� DC

};





