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

	void Update();
	void Render(HDC hdc);
	
	//�� ����
	void addMap(const std::string& mapName, int width, int height); 

	//������Ʈ ���� 
	void addObjectToCurrentMap(const std::string& mapName,	TileType tileType, ObjectType objType, int x, int y,  
			CropType cropType = CropType::None);

	//�÷��̾� ����
	void addPlayer(int x, int y);	

	//��Ż ����
	void addPortal(const std::string& mapName, const RECT& rect, int targetMapIndex);

	//  �� �̸� �˻����� �ش��ϴ� �� �ε����� ��ȯ.
	int GetMapIndexByName(const std::string& mapName);


	void PlayerRender(HDC hdc);
	void MovePlayer(float deltaTime);  //�÷��̾� ������

	//���� ��ȯ �Լ�
	void SetKeyState(Direction dir, bool pressed); //�÷��̾� ���� ��ȯ
	void SetDirection(Direction dir); //���� �������� ������ ������
	bool IsPlayerOnPortal(float  x, float  y);
	void ChangeMapToNext();
	void ChangeMap(int index);

	//������Ʈ
	void Update(float deltaTime); //������Ʈ
	void SelectInventorySlot(int index);

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

