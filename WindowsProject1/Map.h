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
	 TileData& getTile(int x, int y);

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	void Update(float deltaTime);
	//

	void AddPortalRect(const RECT& rect, int targetMapIndex);

	const std::vector<std::pair<RECT, int>>& GetPortalRects() const {return portals;}
	//void addBox(std::shared_ptr<WorldObject> box);
	Map();
	void initTiles(int width, int height, TileType type);
	void Render(HDC hdc);

	//진행 증
	TileType SetTile(); //타일 변경
	TileData GetTile(TileData type);

	bool WaterTile(); //땅에 물 뿌림
	void getseed(bool asd) { water = asd; }

	bool HasFenceAt(int tileX, int tileY);  //타일위에 울타리가 있는 지 확인 (나중에 울타리뿐만이 아닌 다른 오브젝트 추가)
	void RemoveFence(int tileX, int tileY); //울타리 삭제

private:
	TileType tiletype;
	std::vector<std::pair<RECT, int>> portals;
	int water = FALSE;
	int width = 0;
	int height = 0;
};