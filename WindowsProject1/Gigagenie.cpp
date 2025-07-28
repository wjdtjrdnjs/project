#include "Gigagenie.h"
#include "WorldObject.h"
#include "Map.h"
#include "Box.h"
#include "Player.h"
#include "Crop.h"
#include "Tree.h"
#include "House.h"
#include "Direction.h"
#include "House.h"
#include "Renderable.h"
#include "InputManager.h"
#include <string>
#include <iostream>

void Gigagenie::Update(float deltaTime)
{

    if (player)
    {
        player->Update(deltaTime);
        InPortal(); //포탈 입장

        //-------위치 점검-------해야함
        player->HandleLeftClick(currentMap()); //좌클릭
        player->HandleRightClick(currentMap()); //우클릭
    }

}

void Gigagenie::Render(HDC hdc)
{

}

void Gigagenie::addMap(const std::string& mapName, int width, int height, TileType type)
{
    Map newMap;
    newMap.name = mapName;
    newMap.initTiles( width, height , type);
    maps.push_back(newMap);
    OutputDebugStringA(("맵 생성 "+ mapName + "\n").c_str());

    if (maps.size() == 1) //첫맵이면 0으로 초기화
        currentMapIndex = 0;
}

void Gigagenie::addObjectToCurrentMap(const std::string& mapName,TileType tileType, ObjectType objectType, int x, int y, CropType cropType)
{
    int mapIndex = GetMapIndexByName(mapName);
    if (mapIndex == -1) return; // 맵이 없으면 리턴

    Map& map = maps[mapIndex];

    int index = y * map.getWidth() + x;
    TileData& tile = map.mapTiles[index];

    if (tileType != TileType::None)
        tile.tileType = tileType;

    if (objectType != ObjectType::None && !tile.object)
    {
        std::shared_ptr<WorldObject> obj;
        if (objectType == ObjectType::Box)
        {
            obj = std::make_shared<Box>();
        }
        else if (objectType == ObjectType::Crop)
        {
            obj = std::make_shared<Crop>(cropType);
        }
        else if (objectType == ObjectType::Tree)
        {
            obj = std::make_shared<Tree>();
        }
        else if (objectType == ObjectType::House)
        {
            obj = std::make_shared<House>();
        }
        if (obj)
        {
            tile.object = obj;
            obj->SetPosition(x, y);
        }
    }
}

void Gigagenie::addPlayer(int x, int y)
{
    auto newPlayer = std::make_shared<Player>();
    newPlayer->SetPosition(x, y);

    player = newPlayer;

}

int Gigagenie::GetMapIndexByName(const std::string& mapName) {
    for (int i = 0; i < (int)maps.size(); i++) {
        if (maps[i].name == mapName)
            return i;
    }
    return -1; // 못 찾으면 -1 반환
}

void Gigagenie::addPortal(const std::string& mapName, const RECT& rect, int targetMapIndex)
{
    int index = GetMapIndexByName(mapName);
    if (index != -1) {
        maps[index].AddPortalRect(rect, targetMapIndex);
        OutputDebugStringA(("포탈 추가: " + mapName + "\n").c_str());
    }
}

void Gigagenie::ChangeMap(int index) //맵 전환과 플레이어 위치 설정
{
    if (index >= 0 && index < (int)maps.size()) {
        currentMapIndex = index;
        player->SetPosition(5, 5); // 새 맵에서 시작 위치 설정
        OutputDebugStringA("맵 전환됨\n");
    }
}

void Gigagenie::InPortal() //플레이어 포탈 입장
{
    float px_pixel = player->GetX() * 32;
    float py_pixel = player->GetY() * 32;

    for (const auto& portal : currentMap().GetPortalRects()) {
        RECT rect = portal.first;
        int targetMapIndex = portal.second;


        if (px_pixel >= rect.left && px_pixel <= rect.right &&
            py_pixel >= rect.top && py_pixel <= rect.bottom) {
            ChangeMap(targetMapIndex);
            OutputDebugStringA("포탈 감지, 맵 변경\n");
            break;
        }
    }
}
//void Gigagenie::Update(float deltaTime)
//{
//    currentMap().Update(deltaTime);
//    if (player)  //생성안딤
//    {
//        player->Update(deltaTime, keyUp, keyDown, keyLeft, keyRight); //움직임 갱신
//        MovePlayer(deltaTime); //플레이어 움직임
//
//        // 포탈 체크
//        float px_pixel = player->GetX() * 32;
//        float py_pixel = player->GetY() * 32;
//
//        char buffer[256];
//
//        sprintf_s(buffer, "플레이어 위치: (%.2f, %.2f)\n", px_pixel, py_pixel);
//        OutputDebugStringA(buffer);
//
//        for (const auto& portal : currentMap().GetPortalRects()) {
//            RECT rect = portal.first;
//            int targetMapIndex = portal.second;
//
//            sprintf_s(buffer, "포탈 영역: left=%d, top=%d, right=%d, bottom=%d, 목표맵=%d\n",
//                rect.left, rect.top, rect.right, rect.bottom, targetMapIndex);
//            OutputDebugStringA(buffer);
//
//
//            if (px_pixel >= rect.left && px_pixel <= rect.right &&
//                py_pixel >= rect.top && py_pixel <= rect.bottom) {
//                ChangeMap(targetMapIndex);
//                OutputDebugStringA("포탈 감지, 맵 변경\n");
//                break;
//            }
//        }
//
//    }
//}

//
//void Gigagenie::OnKeyDown()
//{
//    if (key == 'E') {
//        auto& map = currentMap();
//        auto player = map.GetPlayer();
//
//        int px = static_cast<int>(player->GetX());
//        int py = static_cast<int>(player->GetY());
//
//        // 4방향 상호작용 범위 확인
//        for (auto [dx, dy] : directions) {
//            int tx = px + dx;
//            int ty = py + dy;
//
//            auto& tile = map.GetTile(tx, ty);
//            if (tile.object) {
//                tile.object->Interact(*player);
//                break;
//            }
//        }
//    }
//}



//
//void Gigagenie::ChangeMapToNext()
//{
//    if (currentMapIndex + 1 < (int)maps.size()) {
//        currentMapIndex++;
//        // 플레이어 시작 위치 재설정
//        player->SetPosition(50.f, 50.f); // 적절한 시작 좌표로 바꿔주세요
//        OutputDebugStringA("맵 전환 완료\n");
//    }
//}



void Gigagenie::PlayerRender(HDC hdc)
{
   
    if (player) {      //64를 준 이유는 플레이어 비트맵을 더 키우키 위함이다
        player->Render(hdc, 64);
        player->GetInventory()->InventoryUIRender(hdc);
    }
        
}



//void Gigagenie::TryHarvestCrop(int x, int y)
//{
//    Map& map = currentMap();
//    if (x < 0 || y < 0 || x >= map.getWidth() || y >= map.getHeight())
//        return;
//
//    TileData& tile = map.getTile(x, y);
//    if (tile.object && tile.object->GetObjectType() == ObjectType::Crop)
//    {
//        auto crop = std::dynamic_pointer_cast<Crop>(tile.object);
//        if (crop && crop->IsRipe()) {
//            crop->Harvest(); // 수확 처리 (인벤토리에 추가 등)
//            tile.object = nullptr; // 맵에서 제거
//        }
//    }
//}

//void Gigagenie::MovePlayer(Direction dir)
//{
//    Map& map = currentMap();
//    std::shared_ptr<Player> player = map.GetPlayer();
//
//    if (!player) return;
//
//    int tileX = player->GetTileX();
//    int tileY = player->GetTileY();
//
//    int dx = 0, dy = 0;
//    switch (dir)
//    {
//    case Direction::UP:    dy = -1; break;
//    case Direction::DOWN:  dy = 1;  break;
//    case Direction::LEFT:  dx = -1; break;
//    case Direction::RIGHT: dx = 1;  break;
//    default: return;
//    }
//
//    int newTileX = tileX + dx;
//    int newTileY = tileY + dy;
//
//    // 충돌검사 또는 맵 경계 체크는 여기에 추가 가능
//
//    player->SetTilePosition(newTileX, newTileY);
//}
