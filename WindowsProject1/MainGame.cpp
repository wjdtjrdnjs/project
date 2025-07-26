#include "MainGame.h"
#include "Gigagenie.h"
#include "BitmapManager.h"
#include "resource.h"
#include "Global.h"
#include "Map.h"
#include "Player.h"
#include "InputManager.h"
#include <Windows.h>
#include <optional>
MainGame::MainGame()
{
	genie = std::make_unique<Gigagenie>();
	OutputDebugString(L"��ü ������\n");
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	///////////////////���߿� ��Ʈ�ʸŴ����� �Űܾ��� �ڵ�/////////////////
	BitmapManager::Instance().Load("Grass", IDB_BITMAP22);
	BitmapManager::Instance().Load("Farm", IDB_BITMAP42);
	BitmapManager::Instance().Load("Water", IDB_BITMAP43);
	BitmapManager::Instance().Load("Box", IDB_BITMAP24);
	BitmapManager::Instance().Load("Strawberry", IDB_BITMAP10);
	BitmapManager::Instance().Load("Onion", IDB_BITMAP2);
	BitmapManager::Instance().Load("Player", IDB_BITMAP27);
	BitmapManager::Instance().Load("Tree", IDB_BITMAP49);
	////////////////////////////////////////////////////////////////

	//  ex)	addMap(�� �̸�, ���� ����)  << ���߿� �� Ÿ�� Ÿ�Լ����� �־�� ��(��ü Ÿ��)
	//	ex)	addObjectToCurrentMap(Ÿ��Ÿ��::Ÿ���̸�,������ƮŸ��::������Ʈ�̸�, x , y, �۹�Ÿ��::�۹��̸�) �������� ������ƮŸ���� �۹��̸� ���


	//�ʱ� �� ���� Farm��
	genie->addMap("Farm", 40, 19); //�� ����
	genie->addObjectToCurrentMap(TileType::None, ObjectType::Player, 8, 8); //Ÿ��Ÿ��, ��ġ�� ������Ʈ Ÿ��, ��ǥ(x,y)

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			genie->addObjectToCurrentMap(TileType::Farmland, ObjectType::Crop, 10 + i, 9 + j, CropType::Strawberry); 
			genie->addObjectToCurrentMap(TileType::Farmland, ObjectType::Crop, 14 + i, 9 + j, CropType::Onion); 
		}
	}
	genie->addObjectToCurrentMap(TileType::None, ObjectType::Box, 11, 8); 
	genie->addObjectToCurrentMap(TileType::None, ObjectType::Box, 15, 8);
	//genie->addObjectToCurrentMap(TileType::None, ObjectType::Tree, 2, 15);

	//genie->addMap("MyRoom",50, 30);
	OutputDebugStringA("����Ͽ�\n");

}

void MainGame::Render(HDC hdc)
{
	if (!genie || genie->maps.empty())
		return;

	genie->currentMap().Render(hdc);

}

void MainGame::Update()
{
}

void MainGame::Run()
{
	//HDC hdc = GetDC(hwnd);

	while (TRUE)
	{
		// Windows �޽��� ť���� �޽����� ������ �����´� (������ ���� ��� ����)
		//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//{
		//	// �޽����� WM_QUIT�̸� ���α׷� ����
		//	if (msg.message == WM_QUIT)
		//		break;

		//	// Ű���� Ű�� ������ ���� �޽��� ó��
		//	if (msg.message == WM_KEYDOWN) {
		//		Input(msg.wParam); // ���� Ű ������ Input �Լ��� ���� (��: VK_LEFT ��)
		//	}

		//	// Ű �Է� �� �޽����� �ؽ�Ʈ�� ���� (��: WM_KEYDOWN �� ����)
		//	TranslateMessage(&msg);

		//	// �޽����� ������ ���ν���(WndProc)�� �����ؼ� �⺻ ó��
		//	DispatchMessage(&msg);
		//}
		//Update();
	}
	
}

void MainGame::Input(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_LEFT:  genie->MovePlayer(Direction::LEFT);  break;
		case VK_RIGHT: genie->MovePlayer(Direction::RIGHT); break;
		case VK_UP:    genie->MovePlayer(Direction::UP);    break;
		case VK_DOWN:  genie->MovePlayer(Direction::DOWN);  break;
		}
	}
}
