#include "Map.h"
#include "TileData.h"
//#include "TileData.h"
#include <iostream>
#include <Windows.h>
#include "Global.h"
#include "BitmapManager.h"
#include "WorldObject.h"
#include "TileData.h"
#include "Player.h"
#include <windows.h>
#include <algorithm>
#include<functional>
using namespace std;







void Map::Update(float deltaTime)
{
 
}


void Map::AddPortalRect(const RECT& rect, int targetMapIndex)
{
    portals.emplace_back(rect, targetMapIndex);
}


Map::Map()
{
}

void Map::initTiles( int w, int h, TileType type)
{
    width = w;
    height = h;
    mapTiles.resize(w * h);
    for (auto& tile : mapTiles) {
        tile.tileType = type;
        tile.object = nullptr;
    }

}

TileData& Map::getTile(int x, int y){
    return mapTiles[y * width + x];
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
                tile.object->Render(hdc, tileSize);
            }
        }
    }

    if(g_bFenceRedFrameOn) //포탈 영역
    {
        HBRUSH portalBrush = CreateSolidBrush(RGB(255, 0, 255));  // 보라색 포탈 표시
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, portalBrush);

        for (const auto& portal : portals) {
            const RECT& rect = portal.first;
            FillRect(hdc, &rect, portalBrush);
            FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        }

        SelectObject(hdc, oldBrush);
        DeleteObject(portalBrush);
    }

    DeleteDC(memDC);
}

void Map::SetTile(int tileX, int tileY, TileType type)
{
    //여기는 좌표 타일에 타입을 변경해주는 함수~
}

void Map::GetTile(int tileX, int tileY)
{
    //여기는 좌표 타일을 반환해주는 함수~
}

void Map::WaterTile(int tileX, int tileY) //작물 성장
{
    //여기는 타일 Farmland에 물을 뿌리면 작물이 성장하는 함수~
}

bool Map::HasFenceAt(int tileX, int tileY)
{
    return false;
}

void Map::RemoveFence(int tileX, int tileY)
{
    //울타리 삭제
}
