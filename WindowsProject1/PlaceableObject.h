#pragma once

class InventoryComponent;
class InventoryItem;
class PlaceableObject
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