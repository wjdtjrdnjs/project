#pragma once
#define map_y 17
#define map_x 36
#include "resource.h"
#include <windows.h>
#include <vector>

const int tileSize = 32;

enum TileType {
    TILE_GRASS,  //잔디
    TILE_Path, //경로
    Tile_FarmLand,//밭
    Tile_Water //
};


class Map
{
public:
    Map();
    ~Map();

    static void Init(); //초기 맵
    static void ToggleTile(int x, int y, int i);  //타일 교체
    static TileType GetTile(int x, int y) {
        if (x < 0 || y < 0 || x >= map_x || y >= map_y)
            return TILE_Path;
        return tiles[y][x];
    };
    static bool IsWatered(int x, int y);


    void Render(HDC hdc);

private:
    static TileType tiles[map_y][map_x];
    std::vector<HBITMAP> Tile;    // 비트맵 핸들 저장
    std::vector<HDC> TileDCs;     // 각 타일 비트맵용 메모리 DC

};
