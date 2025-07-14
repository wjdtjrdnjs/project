#pragma once

class Player;
class InventoryItem;

class PlaceableObject
{
public:
   
    virtual void Install(int tileX, int tileY,  Player* player) = 0;
    virtual void Remove(int tileX, int tileY, Player* player) = 0;
    virtual ~PlaceableObject() = default;
 

protected:
    int x_;          // 오브젝트의 X 좌표
    int y_;          // 오브젝트의 Y 좌표
    bool isPlaced_;  // 오브젝트가 현재 설치되어 있는지 여부 (true: 설치됨, false: 미설치)
};