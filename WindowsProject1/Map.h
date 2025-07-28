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
	void SetTile(int tileX, int tileY, TileType type); //Ÿ�� ����
	void GetTile(int tileX, int tileY);
	void WaterTile(int tileX, int tileY); //���� �� �Ѹ�

	bool HasFenceAt(int tileX, int tileY);  //Ÿ������ ��Ÿ���� �ִ� �� Ȯ�� (���߿� ��Ÿ���Ӹ��� �ƴ� �ٸ� ������Ʈ �߰�)
	void RemoveFence(int tileX, int tileY); //��Ÿ�� ����

private:
	TileType tiletype;
	std::vector<std::pair<RECT, int>> portals;
	int width = 0;
	int height = 0;
};