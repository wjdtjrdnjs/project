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
	static void RenderAll(HDC hdc, HWND hWnd);
	static void UpdateAll();

	//�÷��̾�
	static Player* GetPlayer() { return player; }
	static void SetPlayer(Player* player);
	
	//�۹�
	static Crop* GetCropAt(int tileX, int tileY);
	static void AddCrop(Crop* crop);
	static void RemoveCrop(Crop* crop);

	//����
	static void AddAnimal(Animal* animal);

	//��Ÿ��

	static Fence* GetFenceAt(int tileX, int tileY);
	static void AddFence(Fence* fence);
	static void RemoveFence(Fence* fence);

	////////////////����
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

