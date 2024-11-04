#pragma once


/// MyLibImpl: Private Header
class MyLibImpl
{
public:
    void SetVar1(int v){var1_ = v;}
    void SetVar2(double v){var2_ = v;}
    int Var1() const {return var1_;}
    double Var2() const {return var2_;}

private:
    int var1_;
    double var2_;
};
