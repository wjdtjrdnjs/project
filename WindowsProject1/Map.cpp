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

    // 1) 타일 전부 그리기
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

    // 2) 작물(오브젝트) 렌더링
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            auto& tile = mapTiles[index];

            if (tile.object) {
                // 플레이어와 같은 타일인지 검사
                //if (player &&
                //    static_cast<int>(player->GetX()) == x &&
                //    static_cast<int>(player->GetY()) == y)
                //{
                //    // 플레이어가 있는 타일이면 작물 렌더링 패스 (나중에 플레이어 아래에 그릴 거라서)
                //    continue;
                //}
                tile.object->Render(hdc, tileSize);
            }
        }
    }
  

    DeleteDC(memDC);
}
