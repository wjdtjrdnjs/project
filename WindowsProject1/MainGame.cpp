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

	BitmapManager::Instance().Load("Player_Down", IDB_BITMAP27);
	BitmapManager::Instance().Load("Player_UP", IDB_BITMAP28);
	BitmapManager::Instance().Load("Player_LEFT", IDB_BITMAP30);
	BitmapManager::Instance().Load("Player_RIGHT", IDB_BITMAP29);

	BitmapManager::Instance().Load("Tree", IDB_BITMAP49);
	////////////////////////////////////////////////////////////////

	//  ex)	addMap(�� �̸�, ���� ����)  << ���߿� �� Ÿ�� Ÿ�Լ����� �־�� ��(��ü Ÿ��)
	//	ex)	addObjectToCurrentMap(Ÿ��Ÿ��::Ÿ���̸�,������ƮŸ��::������Ʈ�̸�, x , y, �۹�Ÿ��::�۹��̸�) �������� ������ƮŸ���� �۹��̸� ���


	//�ʱ� �� ���� Farm��
	genie->addMap("Farm", 40, 19); //�� ����
	genie->addPlayer(15, 10);

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
	if (!genie || !genie->HasMaps())
		return;

	genie->currentMap().Render(hdc);

	genie->PlayerRender(hdc);


}

void MainGame::Update(float deltaTime)
{
	if (genie)
		genie->Update(deltaTime);
}

void MainGame::Run()
{
	//HDC hdc = GetDC(hwnd);

	while (TRUE)
	{
	
	}
	

}

void MainGame::Input(UINT message, WPARAM wParam, LPARAM lParam)
{
	bool pressed = (message == WM_KEYDOWN);

	switch (wParam)
	{
	case 'W': genie->SetKeyState(Direction::UP, pressed); OutputDebugStringA("�÷��̾� �̵�(��)\n"); break;
	case 'S': genie->SetKeyState(Direction::DOWN, pressed); OutputDebugStringA("�÷��̾� �̵�(�Ʒ�)\n"); break;
	case 'A': genie->SetKeyState(Direction::LEFT, pressed); OutputDebugStringA("�÷��̾� �̵�(����)\n"); break;
	case 'D': genie->SetKeyState(Direction::RIGHT, pressed); OutputDebugStringA("�÷��̾� �̵�(������)\n"); break;
	}
	switch (lParam)
	{
	case WM_RBUTTONDOWN:
	{
		int mouseX = LOWORD(lParam);
		int mouseY = HIWORD(lParam);

		int tileSize = 32;
		int tileX = mouseX / tileSize;
		int tileY = mouseY / tileSize;

		//genie->TryHarvestCrop(tileX, tileY);
		break;
	}
	}
		
}

