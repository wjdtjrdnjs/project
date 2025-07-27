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
	void MovePlayer(float deltaTime);  //�÷��̾� ������
	void PlayerRender(HDC hdc);
	//
	
	
	//�� ����, ������Ʈ ����, �÷��̾� ���� �Լ�
	void addMap(const std::string& mapName, int width, int height); //�� ����
	void addObjectToCurrentMap(	TileType tileType, ObjectType objType, int x, int y,  //������Ʈ ���� 
			CropType cropType = CropType::None);
	void addPlayer(int x, int y); //�÷��̾� ����

	//���� ��ȯ �Լ�
	void SetKeyState(Direction dir, bool pressed); //�÷��̾� ���� ��ȯ
	void SetDirection(Direction dir); //���� �������� ������ ������

	//������Ʈ
	void Update(float deltaTime); //������Ʈ
	//void TryHarvestCrop(int x, int y); //�۹� ��Ȯ

	//void OnKeyDown();

private:
	std::vector<Map> maps;
	std::shared_ptr<Player> player;

	//���� 4���ۿ� map ������ ���
	std::map<Direction, bool> keyStates;// �� ����Ű�� ���� ���¸� �����ϴ� �ڵ� , true�� ����Ű�� ���� ����, false�� ������ ���� ����

	Direction lastPressedDirection = Direction::DOWN; //�÷��̾� ���� ���� ó���� Down

	int currentMapIndex = 0;

	Direction PlayerDirection;

	//Ű ���� ���� ���� ����
	bool keyUp = false;
	bool keyDown = false;
	bool keyLeft = false;
	bool keyRight = false;
};

