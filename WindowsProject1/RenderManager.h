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

//�׸� Ŭ������ ���� ����
class Player;
class Animal;
class Fence;
class Crop;
class Map;
class Box;

class RenderManager:public SingletonT<RenderManager>//�׸��� ���
{
public:
	//������Ʈ
	 void RenderAll(HDC hdc, HWND hWnd);
	 void UpdateAll();

	//�÷��̾�
	 Player* GetPlayer() { return Instance().player; }
	 void SetPlayer(Player* player);
	 bool playerCollided();  //�÷��̾� �浹 �˻�

	//�۹�
	 Crop* GetCropAt(int tileX, int tileY);
	 void AddCrop(Crop* crop);
	 void RemoveCrop(Crop* crop);

	//����
	 void AddAnimal(Animal* animal);

	//��Ÿ��

	 Fence* GetFenceAt(int tileX, int tileY);
	 void AddFence(Fence* fence);
	 void RemoveFence(Fence* fence);

	////////////////����
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

