#pragma once
class GameObject {
public:
    bool active = true;
    bool isInsideHouse = false; // 집 안/밖 구분용

    void SetActive(bool val) { active = val; }
    bool IsActive() const { return active; }
    bool IsInsideHouse() const { return isInsideHouse; }
};