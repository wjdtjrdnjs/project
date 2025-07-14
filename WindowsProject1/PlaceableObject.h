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
    int x_;          // ������Ʈ�� X ��ǥ
    int y_;          // ������Ʈ�� Y ��ǥ
    bool isPlaced_;  // ������Ʈ�� ���� ��ġ�Ǿ� �ִ��� ���� (true: ��ġ��, false: �̼�ġ)
};