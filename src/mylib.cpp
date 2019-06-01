
#include <mylib/mylib.h>


MyLib::MyLib() : var1_(3)
{
    var2_ = 4.3;
}

void MyLib::Method1()
{
    var2_ += 1.1;
}

int MyLib::Method2() const
{
    return var1_ + 4;
}