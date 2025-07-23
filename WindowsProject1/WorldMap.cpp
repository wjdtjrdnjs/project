#include "WorldMap.h"
#include "resource.h" // 비트맵 리소스 ID 정의된 헤더

WorldMap::WorldMap() : cameraX(0), cameraY(0) {
    LoadTileBitmaps();
    Init();
}

WorldMap::~WorldMap() {
}

void WorldMap::LoadTileBitmaps() {
    HMODULE hModule = GetModuleHandle(NULL);
    HBITMAP grassBmp = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BITMAP22), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    HBITMAP pathBmp = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BITMAP21), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    HBITMAP farmBmp = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BITMAP42), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    HBITMAP waterBmp = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BITMAP43), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    HBITMAP floorBmp = (HBITMAP)LoadImage(hModule, MAKEINTRESOURCE(IDB_BITMAP25), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if (!grassBmp || !pathBmp || !farmBmp || !waterBmp, !floorBmp) {
        MessageBox(NULL, L"Bitmap load failed!", L"Error", MB_OK);
        return;
    }

    tileBitmaps = { grassBmp, pathBmp, farmBmp, waterBmp,floorBmp };

    HDC screenDC = GetDC(NULL);
    for (auto bmp : tileBitmaps) {
        HDC memDC = CreateCompatibleDC(screenDC);
        SelectObject(memDC, bmp);
        tileDCs.push_back(memDC);
    }
    ReleaseDC(NULL, screenDC);
}

void WorldMap::ReleaseResources()
{
    ReleaseResources();

}

void WorldMap::Init() {
    for (int y = 0; y < full_map_y; ++y) {
        for (int x = 0; x < full_map_x; ++x) {
            tiles[y][x] = tile_grass;
        }
    }

    // 월드맵 구간 (예: 왼쪽 위 0~35 x 0~16)
    for (int y = 6; y <= 10; ++y) {
        for (int x = 8; x < 18; ++x) {
            tiles[y][x] = tile_path;
        }
    }

    // 물 웅덩이 하나
    tiles[12][6] = tile_water;

    // 추가로 지역별 맵 구조 (예: 집 내부는 36~71, 0~16에 그린다)
    // region 1: 집 내부
    for (int y = 0; y < map_y; ++y) {
        for (int x = 0; x < map_x; ++x) {
            tiles[y][x + map_x] = tile_floor;  // region 1은 x좌표 오프셋
        }
    }

    // region 2: 상점
    for (int y = 0; y < map_y; ++y) {
        for (int x = 0; x < map_x; ++x) {
            tiles[y + map_y][x] = tile_farmland;  // y 오프셋
        }
    }

    // region 3: 던전
    for (int y = 0; y < map_y; ++y) {
        for (int x = 0; x < map_x; ++x) {
            tiles[y + map_y][x + map_x] = tile_path;
        }
    }
}


void WorldMap::MoveToRegion(int regionIndex) {
    switch (regionIndex) {
    case 0: // 월드맵
        cameraX = 0;
        cameraY = 0;
        break;
    case 1: // 마이룸
        cameraX = map_x;
        cameraY = 0;
        break;
    case 2: // 던전
        cameraX = 0;
        cameraY = map_y;
        break;
    case 3: // 상점
        cameraX = map_x;
        cameraY = map_y;
        break;
    }
}

void WorldMap::Render(HDC hdc) {
    BITMAP bmp;

    for (int y = 0; y < map_y; ++y) {
        for (int x = 0; x < map_x; ++x) {
            int worldX = x + cameraX;
            int worldY = y + cameraY;

            tile_type tile = tiles[worldY][worldX];
            HDC tileDC = tileDCs[tile];
            GetObject(tileBitmaps[tile], sizeof(BITMAP), &bmp);

            TransparentBlt(
                hdc,
                x * tileSize, y * tileSize,
                tileSize, tileSize,
                tileDC,
                0, 0,
                bmp.bmWidth, bmp.bmHeight,
                RGB(255, 255, 255)  // 투명색
            );
        }
    }
}


void WorldMap::ToggleTile(int x, int y, int i)  //타일 교체
{
    if (x < 0 || y < 0 || x >= map_x || y >= map_y) // 범위 체크 수정(map_x, map_y 순서 주의)
        return;

    if (i == 4 && tiles[y][x] == tile_grass)
        tiles[y][x] = tile_path;
    else if (i == 4 && tiles[y][x] == tile_path || i == 4 && tiles[y][x] == tile_farmland)
        tiles[y][x] = tile_grass;


    if (i == 7 && tiles[y][x] == tile_path) //물뿌리개로 경로타일 클릭 시 밭으로 변경
        tiles[y][x] = tile_farmland;


}



bool WorldMap::IsWatered(int x, int y) { //해당 타일이 밭인지 확인
    return tiles[y][x] == tile_type::tile_farmland;
}
