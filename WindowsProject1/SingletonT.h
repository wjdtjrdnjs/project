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
        static T instance;  // thread-safe, once-only 생성 (C++11 이상)
        return instance;
    }
};


