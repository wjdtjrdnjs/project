#include "Gigagenie.h"
#include "WorldObject.h"
#include "Map.h"
#include "Box.h"
#include "Player.h"
#include "Crop.h"
#include "Tree.h"
#include "Direction.h"
#include "Renderable.h"
#include <string>
#include <iostream>

void Gigagenie::addMap(const std::string& mapName, int width, int height)
{
    Map newMap;
    newMap.name = mapName;
    newMap.initTiles(width, height);
    maps.push_back(newMap);
    OutputDebugStringA("맵 생성\n");

    if (maps.size() == 1) //첫맵이면 0으로 초기화
        currentMapIndex = 0;
}

void Gigagenie::addObjectToCurrentMap(TileType tileType, ObjectType objectType, int x, int y, CropType cropType)
{
    Map& map = currentMap();

    int index = y * map.getWidth() + x;
    TileData& tile = map.mapTiles[index];

    if (tileType != TileType::None)
        tile.tileType = tileType;

    if (objectType != ObjectType::None && !tile.object)
    {
        std::shared_ptr<WorldObject> obj;
        if (objectType == ObjectType::Box)
        {
            obj = std::make_shared<Box>();  //객체생성과 스마트포인터 생성
        }
        else if (objectType == ObjectType::Crop)
        {
            obj = std::make_shared<Crop>(cropType); //작물 타입과 함께 객체생성과 스마트포인터 생성
        }
        else if (objectType == ObjectType::Tree)
        {
            obj = std::make_shared<Tree>();  //객체생성과 스마트포인터 생성
        }

        /*else if (objectType == ObjectType::Crop)
            obj = std::make_shared<Crop>();*/
        // ... 다른 객체도 이어서

        if (obj)
        {
            tile.object = obj;
            obj->SetPosition(x, y);  // 필요 시 위치 설정
        }

    }
}

void Gigagenie::addPlayer(int x, int y)
{
    auto newPlayer = std::make_shared<Player>();
    newPlayer->SetPosition(x, y);

    player = newPlayer;

}

void Gigagenie::SetKeyState(Direction dir, bool pressed)
{

    keyStates[dir] = pressed;

    if (pressed)
        lastPressedDirection = dir;

    SetDirection(lastPressedDirection);  // 방향 갱신

}
void Gigagenie::SetDirection(Direction dir)//플레이어 방향 전환을 위한 함수
{
    PlayerDirection = dir;

}
void Gigagenie::Update(float deltaTime)
{
    currentMap().Update(deltaTime);
    if (player)  //생성안딤
    {
        player->Update(deltaTime, keyUp, keyDown, keyLeft, keyRight); //움직임 갱신
        MovePlayer(deltaTime); //플레이어 움직임
    }
}
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

void Gigagenie::MovePlayer(float deltaTime)
{
  
    if (player) {
        float speed = 5.0f;
        float dx = 0, dy = 0;

        if (keyStates[lastPressedDirection]) { // 마지막으로 눌린 방향이 현재 눌려있는지  확인
            switch (lastPressedDirection) {
            case Direction::UP: dy = -1; break;
            case Direction::DOWN: dy = 1; break;
            case Direction::LEFT: dx = -1; break;
            case Direction::RIGHT: dx = 1; break;
            }

        }
        if(dx== 0 && dy == 0)
            OutputDebugStringA("플레이어 이동x\n");
        else 
            OutputDebugStringA("플레이어 이동o\n");


        // 플레이어의 새로운 위치 계산 (이동 벡터 * 속도 * 시간)
        //키 누름이 없으면 dx와 dy는 0을 전달한다.
        float newX = player->GetX() + dx * speed * deltaTime;
        float newY = player->GetY() + dy * speed * deltaTime;



        player->SetPosition(newX, newY);
    }

   
}

void Gigagenie::PlayerRender(HDC hdc)
{
   
    if (player)  //64를 준 이유는 플레이어 비트맵을 더 키우키 위함이다
            player->Render(hdc, 64 , PlayerDirection);

    
        
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
