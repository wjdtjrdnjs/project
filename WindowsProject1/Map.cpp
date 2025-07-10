#include "Map.h"

TileType Map::tiles[map_y][map_x];

Map::Map()
{
    HBITMAP grassBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP22), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //잔디
    HBITMAP dirtBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP21), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //밭

    Tile.push_back(grassBmp); // TILE_GRASS
    Tile.push_back(dirtBmp);  // TILE_FARMLAND

    // 메모리 DC 생성
    HDC screenDC = GetDC(NULL);

    // 각 비트맵에 대해 별도의 메모리 DC 생성 및 비트맵 선택
    for (auto bmp : Tile) {
        HDC memDC = CreateCompatibleDC(screenDC);
        SelectObject(memDC, bmp);
        TileDCs.push_back(memDC);
    }
    Init();  //초기 맵 상태
    ReleaseDC(NULL, screenDC);
}

Map::~Map()
{
    // 메모리 DC 해제
    for (auto dc : TileDCs) {
        if (dc) DeleteDC(dc);
    }

    // 비트맵 해제
    for (auto bmp : Tile) {
        if (bmp) DeleteObject(bmp);
    }
}

void Map::Render(HDC hdc)  //맵 출력
{
    BITMAP bmp;

    for (int y = 0; y < map_y; y++)
    {
        for (int x = 0; x < map_x; x++)
        {
            int tileType = tiles[y][x];
            HDC tileDC = TileDCs[tileType];

          
            // 비트맵 크기 가져오기
            GetObject(Tile[tileType], sizeof(BITMAP), &bmp);

            TransparentBlt(
                hdc,
                x * tileSize, y * tileSize,
                tileSize, tileSize,
                tileDC,
                0, 0,
                bmp.bmWidth, bmp.bmHeight,
                RGB(255, 255, 255)
            );
        }
    }
}

void Map::ToggleTile(int x, int y)  //타일 교체
{
    if (x < 0 || y < 0 || x >= map_x || y >= map_y) // 범위 체크 수정(map_x, map_y 순서 주의)
        return;

    if (tiles[y][x] == TILE_GRASS)
        tiles[y][x] = TILE_FARMLAND;
    else
        tiles[y][x] = TILE_GRASS;
}

void Map::Init() 
{
    for (int y = 0; y < map_y; ++y)
    {
        for (int x = 0; x < map_x; ++x)
        {          
            if (y >= 6 && y <= 11 && x >= 1 && x < 9) tiles[y][x] = TILE_FARMLAND; //농지,밭           
            else tiles[y][x] = TILE_GRASS; //잔디
                
        }         
    }
       
}
