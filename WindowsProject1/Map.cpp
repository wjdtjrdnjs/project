#include "Map.h"

TileType Map::tiles[map_y][map_x];
std::vector<HBITMAP> Map::Tile;
std::vector<HDC> Map::TileDCs;
Map::Map()
{
    HBITMAP grassBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP22), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //�ܵ�
    HBITMAP dirtBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP21), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //���
    HBITMAP FarmBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP42), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //��
    HBITMAP WatmBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP43), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); //��

    Tile.push_back(grassBmp); // �ܵ�
    Tile.push_back(dirtBmp);  // ���
    Tile.push_back(FarmBmp);  // ��
    Tile.push_back(WatmBmp);  // ��
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

/// �ڵ� ���� �ʿ�
void Map::ToggleTile(int x, int y, int i)  //Ÿ�� ��ü
{
    if (x < 0 || y < 0 || x >= map_x || y >= map_y) // ���� üũ ����(map_x, map_y ���� ����)
        return;

    if (i == 4 && tiles[y][x] == TILE_GRASS)
        tiles[y][x] = TILE_Path;
    else if (i == 4 && tiles[y][x] == TILE_Path || i == 4 && tiles[y][x] == Tile_FarmLand)
        tiles[y][x] = TILE_GRASS;

        
    if(i == 7 && tiles[y][x] == TILE_Path) //���Ѹ����� ���Ÿ�� Ŭ�� �� ������ ����
        tiles[y][x] = Tile_FarmLand;
    

}



bool Map::IsWatered(int x, int y) { //�ش� Ÿ���� ������ Ȯ��
    return tiles[y][x] == TileType::Tile_FarmLand;
}

void Map::Init()
{
    for (int y = 0; y < map_y; ++y)
    {
        for (int x = 0; x < map_x; ++x)
        {
            if (y >= 6 && y <= 10 && x >= 8 && x < 18) tiles[y][x] = TILE_Path; //����,��           
            else tiles[y][x] = TILE_GRASS; //�ܵ�
            if(y == 12 && x == 6)
                tiles[y][x] = Tile_Water;
        }
    }

}
