#include "MyRoomMap.h"
const int tileSize = 32;
TileType_1 MyRoomMap::tiles_1[map_y][map_x];

MyRoomMap::MyRoomMap()
{
    HBITMAP Floor = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP25), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //잔디
    doorBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP26), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    HDC screenDC = GetDC(NULL);

    Tile_1.push_back(Floor); // 잔디

    for (auto bmp : Tile_1) {
        HDC memDC = CreateCompatibleDC(screenDC);
        SelectObject(memDC, bmp);
        TileDCs_1.push_back(memDC);
    }
    doorDC = CreateCompatibleDC(screenDC);
    SelectObject(doorDC, doorBitmap);

    Init();  //초기 맵 상태
    ReleaseDC(NULL, screenDC);


}

MyRoomMap::~MyRoomMap()
{
    // 메모리 DC 해제
    for (auto dc : TileDCs_1) {
        if (dc) DeleteDC(dc);
    }

    // 비트맵 해제
    for (auto bmp : Tile_1) {
        if (bmp) DeleteObject(bmp);
    }

    if (doorDC) DeleteDC(doorDC);
    if (doorBitmap) DeleteObject(doorBitmap);
}

RECT MyRoomMap::GetExitDoorBoundingBox() const
{
    return { exitDoorX, exitDoorY, exitDoorX + tileSize, exitDoorY + tileSize };
}

void MyRoomMap::Init()
{
    for (int y = 0; y < map_y; ++y)
    {
        for (int x = 0; x < map_x; ++x)
        {
           tiles_1[y][x] = TILE_Floor; //농지,밭           
        }
    }
}

void MyRoomMap::Render(HDC hdc)
{
    BITMAP bmp;

    for (int y = 0; y < map_y; y++)
    {
        for (int x = 0; x < map_x; x++)
        {
            int tileType = tiles_1[y][x];
            if (tileType < 0 || tileType >= static_cast<int>(TileDCs_1.size()))
            {
                OutputDebugStringA("tileType 값이 범위를 벗어났습니다!\n");
                continue;  // 혹은 tileType을 기본값으로 처리
            }

            HDC tileDC = TileDCs_1[tileType];
            if (!tileDC)
            {
                OutputDebugStringA("tileDC가 nullptr입니다!\n");
                continue;  // nullptr DC 사용 금지
            }

            GetObject(Tile_1[tileType], sizeof(BITMAP), &bmp);
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
  /*  OutputDebugStringA("문 렌더 중...\n");
    GetObject(doorBitmap, sizeof(BITMAP), &bmp);
    TransparentBlt(
        hdc,
        exitDoorX * tileSize, exitDoorY * tileSize,
        tileSize, tileSize,
        doorDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 255, 255)
    );*/
}
