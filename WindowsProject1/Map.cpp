#include "Map.h"
#include "TileData.h"
//#include "TileData.h"
#include <iostream>
#include <Windows.h>
#include "Global.h"
#include "BitmapManager.h"
#include "WorldObject.h"
#include "Player.h"
#include <windows.h>
#include <algorithm>
#include<functional>
using namespace std;
//void Map::addBox(std::shared_ptr<WorldObject> box) { mapObjects.push_back(box); }



void Map::getTile(int x, int y)
{
}



void Map::Update(float deltaTime)
{
   /* for (auto& obj : objects)
    {
        obj->Update(deltaTime);
    }*/
}

Map::Map()
{
}

void Map::initTiles(int w, int h)
{
    width = w;
    height = h;
	mapTiles.resize(w * h);
    for (auto& tile : mapTiles) {
        tile.tileType = TileType::Grass;
        tile.object = nullptr;
    }
}

void Map::Render(HDC hdc)
{
    int tileSize = 32;
    const int bmpSize = 32;
    HDC memDC = CreateCompatibleDC(hdc);

    // 1) Ÿ�� ���� �׸���
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            auto& tile = mapTiles[index];

            HBITMAP hTileBitmap = BitmapManager::Instance().GetTileBitmap(tile.tileType);
            if (hTileBitmap) {
                HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hTileBitmap);
                StretchBlt(hdc, x * tileSize, y * tileSize, tileSize, tileSize, memDC, 0, 0, bmpSize, bmpSize, SRCCOPY);
                SelectObject(memDC, oldBmp);
            }
        }
    }

    // 2) �۹�(������Ʈ) ������
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            auto& tile = mapTiles[index];

            if (tile.object) {
                // �÷��̾�� ���� Ÿ������ �˻�
                //if (player &&
                //    static_cast<int>(player->GetX()) == x &&
                //    static_cast<int>(player->GetY()) == y)
                //{
                //    // �÷��̾ �ִ� Ÿ���̸� �۹� ������ �н� (���߿� �÷��̾� �Ʒ��� �׸� �Ŷ�)
                //    continue;
                //}
                tile.object->Render(hdc, tileSize);
            }
        }
    }
  

    DeleteDC(memDC);
}
