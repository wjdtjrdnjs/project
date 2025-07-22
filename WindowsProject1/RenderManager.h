#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include "MyRoomMap.h"
#include "SingletonT.h"
#include "WorldMap.h"
#include "BitmapManager.h"
#include "InventoryUIController.h"
#include "Box.h"
#include "House.h"
#include "Fence.h"

class InventoryComponent;
class PlayerController;
class InventoryUIController;


class RenderManager:public SingletonT<RenderManager>//그리기 담당
{
public:
	//업데이트
	 void RenderAll(HDC hdc, HWND hWnd);
	 void SetHouse(House* house);

	 void SetisMapChanged() { isMapChanged = FALSE;}
	 void SetMyRoomMap(MyRoomMap* mymap);
	 void SetBox(Box* box);
	 void SetWorldMap(WorldMap* map);
	 Box* GetBox() { return box; }
	 House* GetHouse() { return house; }
private:
	bool isMapChanged = TRUE;
	House* house = nullptr;
	InventoryComponent* inventory;
	PlayerController* plyercon;
	InventoryUIController inventoryUIControlle;
	Box* box = nullptr;
	WorldMap* worldMap = nullptr;
	MyRoomMap* mymap = nullptr;


};

