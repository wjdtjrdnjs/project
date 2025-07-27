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

void Gigagenie::Update()
{

}

void Gigagenie::Render(HDC hdc)
{

}

void Gigagenie::addMap(const std::string& mapName, int width, int height)
{
    Map newMap;
    newMap.name = mapName;
    newMap.initTiles( width, height);
    maps.push_back(newMap);
    OutputDebugStringA("맵 생성\n");

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
    else {
        OutputDebugStringA(("포탈 추가 실패: " + mapName + " 맵을 찾을 수 없습니다.\n").c_str());
    }
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

        // 포탈 체크
        float px_pixel = player->GetX() * 32;
        float py_pixel = player->GetY() * 32;

        char buffer[256];

        sprintf_s(buffer, "플레이어 위치: (%.2f, %.2f)\n", px_pixel, py_pixel);
        OutputDebugStringA(buffer);

        for (const auto& portal : currentMap().GetPortalRects()) {
            RECT rect = portal.first;
            int targetMapIndex = portal.second;

            sprintf_s(buffer, "포탈 영역: left=%d, top=%d, right=%d, bottom=%d, 목표맵=%d\n",
                rect.left, rect.top, rect.right, rect.bottom, targetMapIndex);
            OutputDebugStringA(buffer);


            if (px_pixel >= rect.left && px_pixel <= rect.right &&
                py_pixel >= rect.top && py_pixel <= rect.bottom) {
                ChangeMap(targetMapIndex);
                OutputDebugStringA("포탈 감지, 맵 변경\n");
                break;
            }
        }

    }
}
void Gigagenie::SelectInventorySlot(int index)
{
    if (player) {
        player->GetInventory()->SetSelectedSlot(index);
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
      


        // 플레이어의 새로운 위치 계산 (이동 벡터 * 속도 * 시간)
        //키 누름이 없으면 dx와 dy는 0을 전달한다.
        float newX = player->GetX() + dx * speed * deltaTime;
        float newY = player->GetY() + dy * speed * deltaTime;



        player->SetPosition(newX, newY);

        for (const auto& portal : currentMap().GetPortalRects()) {
            const RECT& rect = portal.first;
            int targetMap = portal.second;

            RECT playerRect = {
                (LONG)newX, (LONG)newY,
                (LONG)newX + player->GetSize(), (LONG)newY + player->GetSize()
            };

            if (IntersectRect(nullptr, &playerRect, &rect)) {
                ChangeMap(targetMap);
                break;
            }
        }
    }
}

bool Gigagenie::IsPlayerOnPortal(float px, float py)
{
    const int playerWidth = 32;
    const int playerHeight = 32;

    // 플레이어 좌표(px, py)는 중심 기준이라고 가정
    // offsetX, offsetY는 플레이어 충돌박스를 포탈에 맞게 조정하기 위한 보정값

    const int offsetX = 50; // 오른쪽 보정값
    const int offsetY = 50; // 아래 보정값

    RECT playerRect = {
        static_cast<LONG>(px - playerWidth / 2 + offsetX),
        static_cast<LONG>(py - playerHeight / 2 + offsetY),
        static_cast<LONG>(px + playerWidth / 2 + offsetX),
        static_cast<LONG>(py + playerHeight / 2 + offsetY)
    };
    char buffer[128];
    sprintf_s(buffer, "플레이어 위치박스: L=%d, T=%d, R=%d, B=%d\n", playerRect.left, playerRect.top, playerRect.right, playerRect.bottom);
    OutputDebugStringA(buffer);
    // currentMap의 포탈 리스트를 가지고 있다고 가정
    for (const auto& portal : currentMap().GetPortalRects()) {
        const RECT& portalRect = portal.first;
        int targetMap = portal.second;

        if (playerRect.right >= portalRect.left &&
            playerRect.left <= portalRect.right &&
            playerRect.bottom >= portalRect.top &&
            playerRect.top <= portalRect.bottom) {
            OutputDebugStringA("포탈 감지: 충돌 성공!\n");
            return true;
        }
    }
    return false;
}

void Gigagenie::ChangeMap(int index)
{
    if (index >= 0 && index < (int)maps.size()) {
        currentMapIndex = index;
        player->SetPosition(5, 5); // 새 맵에서 시작 위치 설정
        OutputDebugStringA("맵 전환됨\n");
    }
}

void Gigagenie::ChangeMapToNext()
{
    if (currentMapIndex + 1 < (int)maps.size()) {
        currentMapIndex++;
        // 플레이어 시작 위치 재설정
        player->SetPosition(50.f, 50.f); // 적절한 시작 좌표로 바꿔주세요
        OutputDebugStringA("맵 전환 완료\n");
    }
}



void Gigagenie::PlayerRender(HDC hdc)
{
   
    if (player) {      //64를 준 이유는 플레이어 비트맵을 더 키우키 위함이다
        player->Render(hdc, 64, PlayerDirection);
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
