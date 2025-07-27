#pragma once
#include <vector>
#include <memory>
#include <string>
#include <Windows.h>
#include "TileData.h"
#include "WorldObject.h"
class Map
{
public:
	std::string name;
	std::vector<TileData> mapTiles;

	//std::vector<std::shared_ptr<Monster>> monsters; 
	/// 
	void getTile(int x, int y);

	void ResetPlayerCache();

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	void Update(float deltaTime);
	//void addBox(std::shared_ptr<WorldObject> box);
	Map();
	void initTiles(int width, int height);
	void Render(HDC hdc);
private:
	int width = 0;
	int height = 0;
};