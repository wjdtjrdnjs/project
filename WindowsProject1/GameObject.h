#pragma once
class GameObject {
public:
    bool active = true;
    bool isInsideHouse = false; // �� ��/�� ���п�

    void SetActive(bool val) { active = val; }
    bool IsActive() const { return active; }
    bool IsInsideHouse() const { return isInsideHouse; }
};