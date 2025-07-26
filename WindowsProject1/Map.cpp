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
using namespace std;
//void Map::addBox(std::shared_ptr<WorldObject> box) { mapObjects.push_back(box); }

std::shared_ptr<Player> Map::GetPlayer() 
{ if (player) return player;

    for (const TileData& tile : mapTiles) {
        if (tile.object) {
            auto player_1 = std::dynamic_pointer_cast<Player>(tile.object);
            if (player_1) {
                player = player_1;
                return player;
            }
        }
    }

return nullptr;
}

void Map::ResetPlayerCache()
{
    player.reset();
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

    // 2) 타일 위에 있는 오브젝트(플레이어 제외) 그리기
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            auto& tile = mapTiles[index];

            if (tile.object && tile.object->GetObjectType() != ObjectType::Player) {
                tile.object->Render(hdc, tileSize);
            }
        }
    }

    // 3) 플레이어 따로 그리기 (가장 위에)
    auto player = GetPlayer();
    if (player) {
        player->Render(hdc, tileSize);
    }

    DeleteDC(memDC);
}

