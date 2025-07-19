#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include "Crop.h"
#include "Map.h"
//#include "MyRoomMap.h"
#include "Box.h"
#include "Fence.h"
#include "SingletonT.h"
#include "BitmapManager.h"

//그릴 클래스들 전방 선언
class Player;
class Animal;
class House;
class Fence;
class Crop;
class Map;
class Box;

class RenderManager:public SingletonT<RenderManager>//그리기 담당
{
public:
	//업데이트
	 void RenderAll(HDC hdc, HWND hWnd);
	 void SetHouse(House* house);

	 void SetMap(Map* map);
	//void SetMyRoomMap(MyRoomMap* mymap);
	 void SetBox(Box* box);
	 Box* GetBox() { return box; }
	 House* GetHouse() { return house; }
private:
	bool isMapChanged = TRUE;
	House* house = nullptr;
	Map* map = nullptr;
	Box* box = nullptr;

	//MyRoomMap* mymap = nullptr;


};

