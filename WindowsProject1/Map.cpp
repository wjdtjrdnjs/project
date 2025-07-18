#include "Map.h"

TileType Map::tiles[map_y][map_x];
std::vector<HBITMAP> Map::Tile;
std::vector<HDC> Map::TileDCs;
Map::Map()
{
    HBITMAP grassBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP22), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //잔디
    HBITMAP dirtBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP21), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //경로
    HBITMAP FarmBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP42), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //밭
    HBITMAP WatmBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP43), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //물

    Tile.push_back(grassBmp); // 잔디
    Tile.push_back(dirtBmp);  // 경로
    Tile.push_back(FarmBmp);  // 밭
    Tile.push_back(WatmBmp);  // 물
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

/// 코드 수정 필요
void Map::ToggleTile(int x, int y, int i)  //타일 교체
{
    if (x < 0 || y < 0 || x >= map_x || y >= map_y) // 범위 체크 수정(map_x, map_y 순서 주의)
        return;

    if (i == 4 && tiles[y][x] == TILE_GRASS)
        tiles[y][x] = TILE_Path;
    else if (i == 4 && tiles[y][x] == TILE_Path || i == 4 && tiles[y][x] == Tile_FarmLand)
        tiles[y][x] = TILE_GRASS;

        
    if(i == 7 && tiles[y][x] == TILE_Path) //물뿌리개로 경로타일 클릭 시 밭으로 변경
        tiles[y][x] = Tile_FarmLand;
    

}



bool Map::IsWatered(int x, int y) { //해당 타일이 밭인지 확인
    return tiles[y][x] == TileType::Tile_FarmLand;
}

void Map::Init()
{
    for (int y = 0; y < map_y; ++y)
    {
        for (int x = 0; x < map_x; ++x)
        {
            if (y >= 6 && y <= 10 && x >= 8 && x < 18) tiles[y][x] = TILE_Path; //농지,밭           
            else tiles[y][x] = TILE_GRASS; //잔디
            if(y == 12 && x == 6)
                tiles[y][x] = Tile_Water;
        }
    }

}
