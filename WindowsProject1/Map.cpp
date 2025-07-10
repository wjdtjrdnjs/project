#include "Map.h"

TileType Map::tiles[map_y][map_x];

Map::Map()
{
    HBITMAP grassBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP22), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //�ܵ�
    HBITMAP dirtBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP21), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //��

    Tile.push_back(grassBmp); // TILE_GRASS
    Tile.push_back(dirtBmp);  // TILE_FARMLAND

    // �޸� DC ����
    HDC screenDC = GetDC(NULL);

    // �� ��Ʈ�ʿ� ���� ������ �޸� DC ���� �� ��Ʈ�� ����
    for (auto bmp : Tile) {
        HDC memDC = CreateCompatibleDC(screenDC);
        SelectObject(memDC, bmp);
        TileDCs.push_back(memDC);
    }
    Init();  //�ʱ� �� ����
    ReleaseDC(NULL, screenDC);
}

Map::~Map()
{
    // �޸� DC ����
    for (auto dc : TileDCs) {
        if (dc) DeleteDC(dc);
    }

    // ��Ʈ�� ����
    for (auto bmp : Tile) {
        if (bmp) DeleteObject(bmp);
    }
}

void Map::Render(HDC hdc)  //�� ���
{
    BITMAP bmp;

    for (int y = 0; y < map_y; y++)
    {
        for (int x = 0; x < map_x; x++)
        {
            int tileType = tiles[y][x];
            HDC tileDC = TileDCs[tileType];

          
            // ��Ʈ�� ũ�� ��������
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

void Map::ToggleTile(int x, int y)  //Ÿ�� ��ü
{
    if (x < 0 || y < 0 || x >= map_x || y >= map_y) // ���� üũ ����(map_x, map_y ���� ����)
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
            if (y >= 6 && y <= 11 && x >= 1 && x < 9) tiles[y][x] = TILE_FARMLAND; //����,��           
            else tiles[y][x] = TILE_GRASS; //�ܵ�
                
        }         
    }
       
}
