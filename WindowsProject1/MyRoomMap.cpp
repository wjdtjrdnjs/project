#include "MyRoomMap.h"
const int tileSize = 32;
TileType_1 MyRoomMap::tiles_1[map_y][map_x];

MyRoomMap::MyRoomMap()
{
	HBITMAP Floor = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP25), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //�ܵ�

    Tile_1.push_back(Floor); // �ܵ�
    HDC screenDC = GetDC(NULL);

    for (auto bmp : Tile_1) {
        HDC memDC = CreateCompatibleDC(screenDC);
        SelectObject(memDC, bmp);
        TileDCs_1.push_back(memDC);
    }
    Init();  //�ʱ� �� ����
    ReleaseDC(NULL, screenDC);
}

MyRoomMap::~MyRoomMap()
{
    // �޸� DC ����
    for (auto dc : TileDCs_1) {
        if (dc) DeleteDC(dc);
    }

    // ��Ʈ�� ����
    for (auto bmp : Tile_1) {
        if (bmp) DeleteObject(bmp);
    }
}

void MyRoomMap::Init()
{
    for (int y = 0; y < map_y; ++y)
    {
        for (int x = 0; x < map_x; ++x)
        {
           tiles_1[y][x] = TILE_Floor; //����,��           
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
            HDC tileDC = TileDCs_1[tileType];


            // ��Ʈ�� ũ�� ��������
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
}
