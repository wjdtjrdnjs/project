#include "WorldMap.h"
#include "resource.h" // ��Ʈ�� ���ҽ� ID ���ǵ� ���

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

    // ����� ���� (��: ���� �� 0~35 x 0~16)
    for (int y = 6; y <= 10; ++y) {
        for (int x = 8; x < 18; ++x) {
            tiles[y][x] = tile_path;
        }
    }

    // �� ������ �ϳ�
    tiles[12][6] = tile_water;

    // �߰��� ������ �� ���� (��: �� ���δ� 36~71, 0~16�� �׸���)
    // region 1: �� ����
    for (int y = 0; y < map_y; ++y) {
        for (int x = 0; x < map_x; ++x) {
            tiles[y][x + map_x] = tile_floor;  // region 1�� x��ǥ ������
        }
    }

    // region 2: ����
    for (int y = 0; y < map_y; ++y) {
        for (int x = 0; x < map_x; ++x) {
            tiles[y + map_y][x] = tile_farmland;  // y ������
        }
    }

    // region 3: ����
    for (int y = 0; y < map_y; ++y) {
        for (int x = 0; x < map_x; ++x) {
            tiles[y + map_y][x + map_x] = tile_path;
        }
    }
}


void WorldMap::MoveToRegion(int regionIndex) {
    switch (regionIndex) {
    case 0: // �����
        cameraX = 0;
        cameraY = 0;
        break;
    case 1: // ���̷�
        cameraX = map_x;
        cameraY = 0;
        break;
    case 2: // ����
        cameraX = 0;
        cameraY = map_y;
        break;
    case 3: // ����
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
                RGB(255, 255, 255)  // �����
            );
        }
    }
}


void WorldMap::ToggleTile(int x, int y, int i)  //Ÿ�� ��ü
{
    if (x < 0 || y < 0 || x >= map_x || y >= map_y) // ���� üũ ����(map_x, map_y ���� ����)
        return;

    if (i == 4 && tiles[y][x] == tile_grass)
        tiles[y][x] = tile_path;
    else if (i == 4 && tiles[y][x] == tile_path || i == 4 && tiles[y][x] == tile_farmland)
        tiles[y][x] = tile_grass;


    if (i == 7 && tiles[y][x] == tile_path) //���Ѹ����� ���Ÿ�� Ŭ�� �� ������ ����
        tiles[y][x] = tile_farmland;


}



bool WorldMap::IsWatered(int x, int y) { //�ش� Ÿ���� ������ Ȯ��
    return tiles[y][x] == tile_type::tile_farmland;
}
