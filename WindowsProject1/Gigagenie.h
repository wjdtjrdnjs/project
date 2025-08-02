#pragma once
#include "Map.h"
#include <vector>
#include <memory>
#include <string>
#include "TileData.h"
#include "Direction.h"
#include "Renderable.h"
#include "Player.h"
#include "GameObjectManager.h"

class Gigagenie
{
public:

	void init();

	void Update(float deltaTime);

	void Render(HDC hdc);

private:
	GameObjectManager objectmanger;
	CollisionManager collisionManager;
	
};

