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

//�׸� Ŭ������ ���� ����
class Player;
class Animal;
class House;
class Fence;
class Crop;
class Map;
class Box;

class RenderManager:public SingletonT<RenderManager>//�׸��� ���
{
public:
	//������Ʈ
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

