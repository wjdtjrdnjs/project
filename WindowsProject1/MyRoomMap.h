#pragma once
#define map_y 17
#define map_x 36
#include "resource.h"
#include <windows.h>
#include <vector>


enum TileType_1 {
    TILE_Floor,  //바닥
};

class MyRoomMap
{
public:
    MyRoomMap();
    ~MyRoomMap();

    static void Init(); //초기 맵
   
    void Render(HDC hdc);

private:
    static TileType_1 tiles_1[map_y][map_x];
    std::vector<HBITMAP> Tile_1;    // 비트맵 핸들 저장
    std::vector<HDC> TileDCs_1;     // 각 타일 비트맵용 메모리 DC

};





