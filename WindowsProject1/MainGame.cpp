#include "MainGame.h"
#include "Gigagenie.h"
#include "BitmapManager.h"
#include "InputManager.h"
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
	

	//  ex)	addMap(맵 이름, 가로 세로, 전체 타일타입)  
	//	ex)	addObjectToCurrentMap(타일타입::타일이름,오브젝트타입::오브젝트이름, x , y, 작물타입::작물이름) 마지막은 오브젝트타입이 작물이면 사용
	genie->addPlayer(10, 10);


	//초기 맵 설정 Farm맵
	//0번 맵
	genie->addMap("Farm",40, 19, TileType::Grass); //맵 생성
	RECT portalToMyroom = { 1260, 350, 1280, 416 }; //포탈 위치 지정
	genie->addPortal("Farm", portalToMyroom, 1); //포탈 생성
	

	//(포탈이름, x,y) 포탈 입장 후 플레이어 위치 설정 -진행 중-
	//포탈에 입장했을 때 플레이어 위치 설정 -- 나중에 추가 현재 



	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			genie->addObjectToCurrentMap("Farm",TileType::Farmland, ObjectType::Crop, 10 + i, 7 + j, CropType::Strawberry);
			genie->addObjectToCurrentMap("Farm",TileType::Farmland, ObjectType::Crop, 15 + i, 7 + j, CropType::Onion);
		}
	}

	genie->addObjectToCurrentMap("Farm",TileType::None, ObjectType::Box, 11, 6);
	genie->addObjectToCurrentMap("Farm", TileType::None, ObjectType::Box, 16, 6);
	genie->addObjectToCurrentMap("Farm", TileType::None, ObjectType::Tree, 5, 3);
	genie->addObjectToCurrentMap("Farm",TileType::None, ObjectType::House, 3, 10);

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			genie->addObjectToCurrentMap("Farm",TileType::Path, ObjectType::None, 8+i, 11+j);
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			genie->addObjectToCurrentMap("Farm", TileType::Path, ObjectType::None, 13+j, 10 - i);

		}
	}
	for (int i = 0; i < 6; i++)
	{
		genie->addObjectToCurrentMap("Farm", TileType::Path, ObjectType::None, 12 - i, 13 + i);
		genie->addObjectToCurrentMap("Farm", TileType::Path, ObjectType::None, 13 - i, 13 + i);
		genie->addObjectToCurrentMap("Farm", TileType::Path, ObjectType::None, 14 - i, 13 + i);

	}
			

	//1번맵
	genie->addMap("Myroom",  40, 19, TileType::Grass); //맵 생성
	RECT portalToFarm = { -10, 350, 5, 416 };
	genie->addPortal("Myroom", portalToFarm, 0);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			genie->addObjectToCurrentMap("Myroom", TileType::Path, ObjectType::None, 0 + i, 11 + j);
			genie->addObjectToCurrentMap("Myroom", TileType::Path, ObjectType::None, 0 + i, 11 + j);
		}
	}
	genie->addObjectToCurrentMap("Myroom",TileType::None, ObjectType::Box, 5, 8);
	genie->addObjectToCurrentMap("Myroom",TileType::None, ObjectType::Box, 25, 8);
	
	
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
	genie->Update(deltaTime);
}

//void MainGame::Update(float deltaTime)
//{
//	if (genie)
//		genie->Update(deltaTime);
//}

void MainGame::Run()
{
	//HDC hdc = GetDC(hwnd);

	while (TRUE)
	{
	
	}
	

}

void MainGame::Input(UINT message, WPARAM wParam, LPARAM lParam)
{

		
}

