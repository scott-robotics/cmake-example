#pragma once

#include <memory>

class MyLibImpl;

class MyLib
{
public:
    MyLib();
    ~MyLib();

    void Method1();
    int Method2() const;
    void Version() const;
    void Matrix() const;

private:
    std::unique_ptr<MyLibImpl> impl_;
};
