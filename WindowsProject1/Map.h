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

	//���� ��
	TileType SetTile(); //Ÿ�� ����
	TileData GetTile(TileData type);

	bool WaterTile(); //���� �� �Ѹ�
	void getseed(bool asd) { water = asd; }

	bool HasFenceAt(int tileX, int tileY);  //Ÿ������ ��Ÿ���� �ִ� �� Ȯ�� (���߿� ��Ÿ���Ӹ��� �ƴ� �ٸ� ������Ʈ �߰�)
	void RemoveFence(int tileX, int tileY); //��Ÿ�� ����

private:
	TileType tiletype;
	std::vector<std::pair<RECT, int>> portals;
	int water = FALSE;
	int width = 0;
	int height = 0;
};