#include "Gigagenie.h"
#include "WorldObject.h"
#include "Map.h"
#include "Box.h"
#include "Player.h"
#include "Crop.h"
#include "Tree.h"
#include "House.h"
#include "Direction.h"
#include "House.h"
#include "Renderable.h"
#include "Fence.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include <string>
#include <iostream>

void Gigagenie::init()
{
	auto& objectManager = GameObjectManager::Instance();  // �̱��� ����
	objectManager.addPlayer(10, 10);


	//�ʱ� �� ���� Farm��
	//0�� ��
	objectManager.addMap("Farm", 40, 19, TileType::Grass); //�� ����
	RECT portalToMyroom = { 1260, 350, 1280, 416 }; //��Ż z��ġ ����
	objectManager.addPortal("Farm", portalToMyroom, 1); //��Ż ����


	// 230, 580, 320, 600
	// 
	//(��Ż�̸�, x,y) ��Ż ���� �� �÷��̾� ��ġ ���� -���� ��-
	//��Ż�� �������� �� �÷��̾� ��ġ ���� -- ���߿� �߰� ���� 

	objectManager.addObjectToCurrentMap("Farm", 20, 6, TileType::None, PlaceableType::NPC);


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			objectManager.addObjectToCurrentMap("Farm", 10 + i, 7 + j, TileType::Farmland, PlaceableType::Crop, CropType::Strawberry);
			objectManager.addObjectToCurrentMap("Farm", 15 + i, 7 + j, TileType::Farmland, PlaceableType::Crop, CropType::Onion);
		}
	}

	objectManager.addObjectToCurrentMap("Farm", 11, 6, TileType::None, PlaceableType::Box);
	objectManager.addObjectToCurrentMap("Farm", 16, 6, TileType::None, PlaceableType::Box);
	objectManager.addObjectToCurrentMap("Farm", 5, 3, TileType::None, PlaceableType::Tree);
	objectManager.addObjectToCurrentMap("Farm", 3, 10, TileType::None, PlaceableType::House);
	objectManager.addObjectToCurrentMap("Farm", 1, 1, TileType::None, PlaceableType::Fence);

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			objectManager.addObjectToCurrentMap("Farm", 8 + i, 11 + j, TileType::Path);
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			objectManager.addObjectToCurrentMap("Farm", 13 + j, 10 - i, TileType::Path);

		}
	}
	for (int i = 0; i < 6; i++)
	{
		objectManager.addObjectToCurrentMap("Farm", 12 - i, 13 + i, TileType::Path);
		objectManager.addObjectToCurrentMap("Farm", 13 - i, 13 + i, TileType::Path);
		objectManager.addObjectToCurrentMap("Farm", 14 - i, 13 + i, TileType::Path);

	}
	objectManager.addMap("MyRoom", 40, 19, TileType::Grass); //�� ����



}
void Gigagenie::Render(HDC hdc)
{
	auto& objectManager = GameObjectManager::Instance();
	objectManager.Render(hdc);
}

void Gigagenie::Update(float deltaTime)
{
	auto& objectManager = GameObjectManager::Instance();
	objectManager.Update(deltaTime);  // ��, ������Ʈ, �÷��̾�  ����
	
}



//void Gigagenie::Update(float deltaTime)
//{
//    currentMap().Update(deltaTime);
//    if (player)  //�����ȵ�
//    {
//        player->Update(deltaTime, keyUp, keyDown, keyLeft, keyRight); //������ ����
//        MovePlayer(deltaTime); //�÷��̾� ������
//
//        // ��Ż üũ
//        float px_pixel = player->GetX() * 32;
//        float py_pixel = player->GetY() * 32;
//
//        char buffer[256];
//
//        sprintf_s(buffer, "�÷��̾� ��ġ: (%.2f, %.2f)\n", px_pixel, py_pixel);
//        OutputDebugStringA(buffer);
//
//        for (const auto& portal : currentMap().GetPortalRects()) {
//            RECT rect = portal.first;
//            int targetMapIndex = portal.second;
//
//            sprintf_s(buffer, "��Ż ����: left=%d, top=%d, right=%d, bottom=%d, ��ǥ��=%d\n",
//                rect.left, rect.top, rect.right, rect.bottom, targetMapIndex);
//            OutputDebugStringA(buffer);
//
//
//            if (px_pixel >= rect.left && px_pixel <= rect.right &&
//                py_pixel >= rect.top && py_pixel <= rect.bottom) {
//                ChangeMap(targetMapIndex);
//                OutputDebugStringA("��Ż ����, �� ����\n");
//                break;
//            }
//        }
//
//    }
//}




//
//void Gigagenie::ChangeMapToNext()
//{
//    if (currentMapIndex + 1 < (int)maps.size()) {
//        currentMapIndex++;
//        // �÷��̾� ���� ��ġ �缳��
//        player->SetPosition(50.f, 50.f); // ������ ���� ��ǥ�� �ٲ��ּ���
//        OutputDebugStringA("�� ��ȯ �Ϸ�\n");
//    }
//}


