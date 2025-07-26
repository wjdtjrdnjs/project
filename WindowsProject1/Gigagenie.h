#pragma once
#include "Map.h"
#include <vector>
#include <memory>
#include <string>
#include "TileData.h"
#include "Direction.h"

class Gigagenie
{
public:
	std::vector<Map> maps;
	int currentMapIndex = 0;
	
	Map& currentMap() {
		return maps[currentMapIndex];
	}

	void addMap(const std::string& mapName, int width, int height); //맵 생성
	void addObjectToCurrentMap(	//오브젝트 생성
		TileType tileType, ObjectType objType,
		int x, int y, 
		CropType cropType = CropType::None);
	void MovePlayer(Direction dir);

};

