#pragma once
#define map_y 17
#define map_x 36

#include "resource.h"
#include <windows.h>
#include <vector>

const int tileSize = 32;

enum TileType {
    TILE_GRASS,  //�ܵ�
    TILE_FARMLAND //��(����)
};


class Map
{
public:
    Map();
    ~Map();

    static void Init(); //�ʱ� ��
    static void ToggleTile(int x, int y);  //Ÿ�� ��ü
    static TileType GetTile(int x, int y) {
        if (x < 0 || y < 0 || x >= map_x || y >= map_y)
            return TILE_FARMLAND;
        return tiles[y][x];
    };


    void Render(HDC hdc);

private:
    static TileType tiles[map_y][map_x];
    std::vector<HBITMAP> Tile;    // ��Ʈ�� �ڵ� ����
    std::vector<HDC> TileDCs;     // �� Ÿ�� ��Ʈ�ʿ� �޸� DC

};
