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
	OutputDebugString(L"객체 생성됨\n");
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	///////////////////나중에 비트맵매니저로 옮겨야할 코드/////////////////
	BitmapManager::Instance().Load("Grass", IDB_BITMAP22);
	BitmapManager::Instance().Load("Path", IDB_BITMAP21);
	BitmapManager::Instance().Load("Farm", IDB_BITMAP42);
	BitmapManager::Instance().Load("Water", IDB_BITMAP43);
	BitmapManager::Instance().Load("Box", IDB_BITMAP24);
	BitmapManager::Instance().Load("Strawberry", IDB_BITMAP10);
	BitmapManager::Instance().Load("Onion", IDB_BITMAP2);

	BitmapManager::Instance().Load("딸기씨앗봉투", IDB_BITMAP18);
	BitmapManager::Instance().Load("양파씨앗봉투", IDB_BITMAP17);

	BitmapManager::Instance().Load("Player_Down", IDB_BITMAP27);
	BitmapManager::Instance().Load("Player_UP", IDB_BITMAP28);
	BitmapManager::Instance().Load("Player_LEFT", IDB_BITMAP30);
	BitmapManager::Instance().Load("Player_RIGHT", IDB_BITMAP29);

	BitmapManager::Instance().Load("Tree", IDB_BITMAP49);
	////////////////////////////////////////////////////////////////

	//  ex)	addMap(맵 이름, 가로 세로)  << 나중에 맵 타일 타입설정도 넣어야 함(전체 타일)
	//	ex)	addObjectToCurrentMap(타일타입::타일이름,오브젝트타입::오브젝트이름, x , y, 작물타입::작물이름) 마지막은 오브젝트타입이 작물이면 사용


	//초기 맵 설정 Farm맵
	genie->addMap("Farm",40, 19); //맵 생성
	// 2. 포탈 위치 설정
	RECT portalToMyroom = { 320, 160, 352, 192 };
	genie->addPortal("Farm", portalToMyroom, 1);


	genie->addPlayer(10, 10);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			genie->addObjectToCurrentMap("Farm",TileType::Farmland, ObjectType::Crop, 10 + i, 9 + j, CropType::Strawberry);
			genie->addObjectToCurrentMap("Farm",TileType::Farmland, ObjectType::Crop, 14 + i, 9 + j, CropType::Onion);
		}
	}
	genie->addObjectToCurrentMap("Farm",TileType::None, ObjectType::Box, 11, 8);
	genie->addObjectToCurrentMap("Farm",TileType::None, ObjectType::Box, 15, 8);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			genie->addObjectToCurrentMap("Farm",TileType::Path, ObjectType::None, 34 +i, 11+j);
			genie->addObjectToCurrentMap("Farm",TileType::Path, ObjectType::None, 35+i, 11+j);
		}
	}
	genie->addMap("Myroom",  40, 19); //맵 생성
	RECT portalToFarm = { 64, 64, 96, 96 };
	genie->addPortal("Myroom", portalToFarm, 0);

	genie->addObjectToCurrentMap("Myroom",TileType::None, ObjectType::Box, 11, 8);
	genie->addObjectToCurrentMap("Myroom",TileType::None, ObjectType::Box, 15, 8);

	
	//genie->addObjectToCurrentMap(TileType::Path, ObjectType::None, 38, 12);
	//genie->addObjectToCurrentMap(TileType::Path, ObjectType::None, 39, 12);

	//genie->addObjectToCurrentMap(TileType::None, ObjectType::Tree, 2, 15);

	//genie->addMap("MyRoom",50, 30);
	OutputDebugStringA("디버겅용\n");

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
	case 'W': genie->SetKeyState(Direction::UP, pressed); OutputDebugStringA("플레이어 이동(위)\n"); break;
	case 'S': genie->SetKeyState(Direction::DOWN, pressed); OutputDebugStringA("플레이어 이동(아래)\n"); break;
	case 'A': genie->SetKeyState(Direction::LEFT, pressed); OutputDebugStringA("플레이어 이동(왼쪽)\n"); break;
	case 'D': genie->SetKeyState(Direction::RIGHT, pressed); OutputDebugStringA("플레이어 이동(오른쪽)\n"); break;
		// 숫자키 1~9: 인벤토리 슬롯 선택
	case '1': case '2': case '3':
	case '4': case '5': case '6':
	case '7': case '8': case '9':
		if (pressed)
		{
			int slotIndex = wParam - '1';
			genie->SelectInventorySlot(slotIndex);
		}
		break;
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

