#pragma once
#include <vector>
#include <Windows.h>
#include "WorldObject.h"
class CollisionManager
{
public:
    void AddObject(std::shared_ptr<WorldObject> obj) {
        colliders.push_back(obj);
    }

    void RemoveObject(std::shared_ptr<WorldObject> obj) {
        colliders.erase(std::remove(colliders.begin(), colliders.end(), obj), colliders.end());
    }

    bool CheckCollision(const RECT& rect) const {
        RECT temp;
        for (const auto& obj : colliders) {
            if (obj && obj->IsCollidable()) {
                RECT objRect = obj->GetCollisionRect();  // 임시 변수에 저장
                if (IntersectRect(&temp, &rect, &objRect)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    std::vector<std::shared_ptr<WorldObject>> colliders;
};

