#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
//#include "Player.h"
#include "Crop.h"
#include "Animal.h"
#include "Map.h"
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
	static void RenderAll(HDC hdc, HWND hWnd);
	static void UpdateAll();

	//플레이어
	static Player* GetPlayer() { return player; }
	static void SetPlayer(Player* player);
	
	//작물
	static Crop* GetCropAt(int tileX, int tileY);
	static void AddCrop(Crop* crop);
	static void RemoveCrop(Crop* crop);

	//동물
	static void AddAnimal(Animal* animal);

	//울타리

	static Fence* GetFenceAt(int tileX, int tileY);
	static void AddFence(Fence* fence);
	static void RemoveFence(Fence* fence);

	////////////////보류
	static void SetMap(Map* map);
	static void SetBox(Box* box);
	static Box* GetBox() { return box; }
private:
	static Player* player;
	static Map* map;
	static Box* box;
	static std::vector<Animal*> animals;
	static std::vector<Fence*> fences;
	static std::vector<Crop*> crops;
};

