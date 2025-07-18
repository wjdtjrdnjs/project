#pragma once

template <typename T>
class SingletonT
{
protected:
    SingletonT() = default;
    virtual ~SingletonT() = default;

    SingletonT(const SingletonT&) = delete;
    SingletonT& operator=(const SingletonT&) = delete;

public:
    static T& Instance()
    {
        static T instance;  // thread-safe, once-only ���� (C++11 �̻�)
        return instance;
    }
};


