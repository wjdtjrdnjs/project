#pragma once
#include "GameObject.h"
class InventoryComponent;
class InventoryItem;
class PlaceableObject:public GameObject
{
public:
   
    virtual void Install(int tileX, int tileY, InventoryComponent& inventory) = 0; //��ġ
    virtual void Remove(int tileX, int tileY, InventoryComponent& inven) = 0;  //����
    virtual ~PlaceableObject() = default;
 

protected:
    int x_;          
    int y_;         
    bool isPlaced_; 
};