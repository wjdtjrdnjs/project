#pragma once

class Player;
class PlaceableObject
{
public:
   
    virtual void Install(int tileX, int tileY,  Player* player) = 0; //��ġ
    virtual void Remove(int tileX, int tileY, Player* player) = 0;  //����
    virtual ~PlaceableObject() = default;
 

protected:
    int x_;          
    int y_;         
    bool isPlaced_; 
};