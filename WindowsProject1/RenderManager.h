#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include "Crop.h"
#include "Animal.h"
#include "Map.h"
//#include "MyRoomMap.h"
#include "Box.h"
#include "Fence.h"
#include "SingletonT.h"
#include "BitmapManager.h"

//그릴 클래스들 전방 선언
class Player;
class Animal;
class Fence;
class Crop;
class Map;
class Box;

class RenderManager:public SingletonT<RenderManager>//그리기 담당
{
public:
	//업데이트
	 void RenderAll(HDC hdc, HWND hWnd);
	 void UpdateAll();

	//플레이어
	 Player* GetPlayer() { return Instance().player; }
	 void SetPlayer(Player* player);
	 bool playerCollided();  //플레이어 충돌 검사

	//작물
	 Crop* GetCropAt(int tileX, int tileY);
	 void AddCrop(Crop* crop);
	 void RemoveCrop(Crop* crop);

	//동물
	 void AddAnimal(Animal* animal);

	//울타리

	 Fence* GetFenceAt(int tileX, int tileY);
	 void AddFence(Fence* fence);
	 void RemoveFence(Fence* fence);

	////////////////보류
	 void SetMap(Map* map);
	//void SetMyRoomMap(MyRoomMap* mymap);
	 void SetBox(Box* box);
	 Box* GetBox() { return box; }
private:
	bool isMapChanged = TRUE;
	Player* player = nullptr;
	Map* map = nullptr;
	//MyRoomMap* mymap = nullptr;
	Box* box = nullptr;
	std::vector<Animal*> animals;
	std::vector<Fence*> fences;
	std::vector<Crop*> crops;

};

