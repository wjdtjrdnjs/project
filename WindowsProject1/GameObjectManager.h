#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include "SingletonT.h"
#include "Map.h"
#include "Player.h"
#include "CollisionManager.h"

class GameObjectManager:public SingletonT<GameObjectManager>
{
public:

	void Init();
	std::vector<Map>& getMaps() { return maps; }
	std::shared_ptr<Player>& getPlayer() { return player; }
	
	//맵
	Map& currentMap() { return maps[currentMapIndex]; }

	//사용xx
	//const std::vector<Map>& GetMaps() const { return maps; }// 전체 맵 리스트 (읽기 전용)
	int GetCurrentMapIndex() const { return currentMapIndex; }// 현재 맵 인덱스 확인  

	bool HasMaps() const { return !maps.empty(); } //맵 존재 여부
	/////
	void InteractWithTile(int tileX, int tileY, Player& player);
		
	//플레이어 데이터 함수
	//std::shared_ptr<Player> GetPlayer() const {return player;}
	//void SetPlayer(std::shared_ptr<Player> p) { player = p; }

	void LoadMap(const std::string& mapName);

	void Update(float deltaTime);
	void Render(HDC hdc);
	bool IsFarmlandTile(int x, int y);
	//맵 생성
	void addMap(const std::string& mapName, int width, int heightm, TileType tileType);

	//오브젝트 생성 
	void addObjectToCurrentMap(const std::string& mapName, int x, int y, TileType tileType = TileType::None,
		PlaceableType objType = PlaceableType::None, CropType cropType = CropType::None);

	//플레이어 생성
	void addPlayer(int x, int y);

	//포탈 생성
	void addPortal(const std::string& mapName, const RECT& rect, int targetMapIndex);

	//  맵 이름 검색으로 해당하는 맵 인덱스를 반환.
	int GetMapIndexByName(const std::string& mapName);

	void InPortal(); //포탈 플레이어 충돌

	bool CheckTile(int TileX, int TileY, ItemCategory type = ItemCategory::None, ToolType tooltype = ToolType::None); //타일 검사

	//void ChangeMapToNext();
	void ChangeMap(int index);
	void ChangeTile(int TIleX, int TileY);
	void  WaterTile(int x, int y);
	
	//업데이트
	//void Update(float deltaTime); //업데이트

	//void TryHarvestCrop(int x, int y); //작물 수확

	//void OnKeyDown();
private:
	std::vector<Map> maps;
	std::shared_ptr<Player> player;

	bool water = false;
	int playersize = 64;
	int currentMapIndex = 0;
};

