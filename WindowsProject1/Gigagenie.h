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
	
	//��
	Map& currentMap() {return maps[currentMapIndex];}
	const std::vector<Map>& GetMaps() const { return maps; }// ��ü �� ����Ʈ (�б� ����)
	
	int GetCurrentMapIndex() const { return currentMapIndex; }// ���� �� �ε��� Ȯ��

	bool HasMaps() const { return !maps.empty(); } //�� ���� ����
	/////

	//�÷��̾� ������ �Լ�
	std::shared_ptr<Player> GetPlayer() const {return player;}
	void SetPlayer(std::shared_ptr<Player> p) { player = p; }

	void Update(float deltaTime);
	void Render(HDC hdc);
	
	//�� ����
	void addMap(const std::string& mapName, int width, int heightm, TileType tileType);

	//������Ʈ ���� 
	void addObjectToCurrentMap(const std::string& mapName,	TileType tileType, ObjectType objType, int x, int y,  
			CropType cropType = CropType::None);

	//�÷��̾� ����
	void addPlayer(int x, int y);	

	//��Ż ����
	void addPortal(const std::string& mapName, const RECT& rect, int targetMapIndex);

	//  �� �̸� �˻����� �ش��ϴ� �� �ε����� ��ȯ.
	int GetMapIndexByName(const std::string& mapName);

	void InPortal();

	void PlayerRender(HDC hdc);

	

	void ChangeMapToNext();
	void ChangeMap(int index);

	//������Ʈ
	//void Update(float deltaTime); //������Ʈ

	//void TryHarvestCrop(int x, int y); //�۹� ��Ȯ

	//void OnKeyDown();

private:
	std::vector<Map> maps;
	std::shared_ptr<Player> player;
	int currentMapIndex = 0;
	
};

