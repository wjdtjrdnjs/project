#pragma once
#include <vector>
#include <Windows.h>
class CollisionManager
{
public:
	bool playerCollided( );  //플레이어 충돌 검사
	virtual std::vector<RECT> GetCollisionRects() const = 0;
	virtual ~CollisionManager() = default;
	bool IsNearBox(const RECT& playerBox, const RECT& boxBox, int distance = 10);
	bool IsTouching(const RECT& a, const RECT& b);
};

