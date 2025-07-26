#pragma once
#include <vector>
#include <memory>
#include <string>
#include <Windows.h>
#include "TileData.h"
#include "WorldObject.h"
#include "Player.h"
class Map
{
public:
	std::string name;
	std::vector<TileData> mapTiles;

	//재확인 필요 코드
	std::shared_ptr<Player> GetPlayer(); 
	void SetPlayer(std::shared_ptr<Player> p) { player = p; }
	//std::vector<std::shared_ptr<Monster>> monsters;
	/// 
	void ResetPlayerCache();
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	//void addBox(std::shared_ptr<WorldObject> box);
	Map();
	void initTiles(int width, int height);
	void Render(HDC hdc);
private:
	std::shared_ptr<Player> player;
	int width = 0;
	int height = 0;
};