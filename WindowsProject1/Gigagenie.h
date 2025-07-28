#pragma once
#include "Map.h"
#include <vector>
#include <memory>
#include <string>
#include "TileData.h"
#include "Direction.h"
#include "Renderable.h"
#include "Player.h"

class PlayerData;
class Gigagenie
{
public:
	
	//맵
	Map& currentMap() {return maps[currentMapIndex];}
	const std::vector<Map>& GetMaps() const { return maps; }// 전체 맵 리스트 (읽기 전용)
	
	int GetCurrentMapIndex() const { return currentMapIndex; }// 현재 맵 인덱스 확인

	bool HasMaps() const { return !maps.empty(); } //맵 존재 여부
	/////

	//플레이어 데이터 함수
	std::shared_ptr<Player> GetPlayer() const {return player;}
	void SetPlayer(std::shared_ptr<Player> p) { player = p; }

	void Update(float deltaTime);
	void Render(HDC hdc);
	
	//맵 생성
	void addMap(const std::string& mapName, int width, int heightm, TileType tileType);

	//오브젝트 생성 
	void addObjectToCurrentMap(const std::string& mapName,	TileType tileType, ObjectType objType, int x, int y,  
			CropType cropType = CropType::None);

	//플레이어 생성
	void addPlayer(int x, int y);	

	//포탈 생성
	void addPortal(const std::string& mapName, const RECT& rect, int targetMapIndex);

	//  맵 이름 검색으로 해당하는 맵 인덱스를 반환.
	int GetMapIndexByName(const std::string& mapName);

	void InPortal();

	void PlayerRender(HDC hdc);

	

	void ChangeMapToNext();
	void ChangeMap(int index);

	//업데이트
	//void Update(float deltaTime); //업데이트

	//void TryHarvestCrop(int x, int y); //작물 수확

	//void OnKeyDown();

private:
	std::vector<Map> maps;
	std::shared_ptr<Player> player;
	int currentMapIndex = 0;
	
};

