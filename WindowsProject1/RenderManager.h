#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include "Map.h"
#include "MyRoomMap.h"
#include "SingletonT.h"
#include "BitmapManager.h"
#include "Box.h"
#include "House.h"
#include "Fence.h"

class RenderManager:public SingletonT<RenderManager>//그리기 담당
{
public:
	//업데이트
	 void RenderAll(HDC hdc, HWND hWnd);
	 void SetHouse(House* house);

	 void SetMap(Map* map);
	 void SetisMapChanged() { isMapChanged = FALSE;}
	 void SetMyRoomMap(MyRoomMap* mymap);
	 void SetBox(Box* box);
	 Box* GetBox() { return box; }
	 House* GetHouse() { return house; }
private:
	bool isMapChanged = TRUE;
	House* house = nullptr;

	Box* box = nullptr;

	Map* map = nullptr;
	MyRoomMap* mymap = nullptr;


};

