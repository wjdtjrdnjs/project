#pragma once
#include <windows.h>
#include <vector>

#define tileSize 32
#define map_x 36
#define map_y 17
#define full_map_x (map_x * 2)
#define full_map_y (map_y * 2)

enum tile_type {
    tile_grass,
    tile_path,
    tile_farmland,
    tile_water,
    tile_floor
};
class WorldMap 
{
public:
    WorldMap();
    ~WorldMap();

    void Init();                           // 전체 맵 초기화
    void MoveToRegion(int regionIndex);    // 지역 전환 (0~3)
    void Render(HDC hdc);                  // 맵 그리기

    bool IsWatered(int x, int y);
     void ToggleTile(int x, int y, int i);  //타일 교체
     tile_type GetTile(int x, int y) {
        if (x < 0 || y < 0 || x >= full_map_x || y >= full_map_y)
            return tile_grass;
        return tiles[y][x];
    };
private:
    tile_type tiles[full_map_y][full_map_x];  // 전체 맵
    std::vector<HBITMAP> tileBitmaps;
    std::vector<HDC> tileDCs;
    void LoadTileBitmaps();               // 타일 비트맵 로드
    void ReleaseResources();              // 자원 해제

    int cameraX;
    int cameraY;
};
