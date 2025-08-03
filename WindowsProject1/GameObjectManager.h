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
	
	//��
	Map& currentMap() { return maps[currentMapIndex]; }

	//���xx
	//const std::vector<Map>& GetMaps() const { return maps; }// ��ü �� ����Ʈ (�б� ����)
	int GetCurrentMapIndex() const { return currentMapIndex; }// ���� �� �ε��� Ȯ��  

	bool HasMaps() const { return !maps.empty(); } //�� ���� ����
	/////
	void InteractWithTile(int tileX, int tileY, Player& player);
		
	//�÷��̾� ������ �Լ�
	//std::shared_ptr<Player> GetPlayer() const {return player;}
	//void SetPlayer(std::shared_ptr<Player> p) { player = p; }

	void LoadMap(const std::string& mapName);

	void Update(float deltaTime);
	void Render(HDC hdc);

	//�� ����
	void addMap(const std::string& mapName, int width, int heightm, TileType tileType);

	//������Ʈ ���� 
	void addObjectToCurrentMap(const std::string& mapName, int x, int y, TileType tileType = TileType::None,
		ObjectType objType = ObjectType::None, CropType cropType = CropType::None);

	//�÷��̾� ����
	void addPlayer(int x, int y);

	//��Ż ����
	void addPortal(const std::string& mapName, const RECT& rect, int targetMapIndex);

	//  �� �̸� �˻����� �ش��ϴ� �� �ε����� ��ȯ.
	int GetMapIndexByName(const std::string& mapName);

	void InPortal(); //��Ż �÷��̾� �浹

	bool CheckTile(int TileX, int TileY, ObjectType type); //Ÿ�� �˻�

	//void ChangeMapToNext();
	void ChangeMap(int index);

	//������Ʈ
	//void Update(float deltaTime); //������Ʈ

	//void TryHarvestCrop(int x, int y); //�۹� ��Ȯ

	//void OnKeyDown();
private:
	std::vector<Map> maps;
	std::shared_ptr<Player> player;

	int playersize = 64;
	int currentMapIndex = 0;
};

