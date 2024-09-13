
#include <iostream>

#include <mylib/mylib.hpp>
#include <mylib/ExampleConfig.hpp>

int main(int agrc, char* argv[])
{
    std::cout << "\n==========\n";
    
    MyLib testlib;

    testlib.Method1();
    std::cout << "Your test library works! Method2() = "
              << testlib.Method2() << std::endl;
    std::cout << "Version: ";
    testlib.Version();
    testlib.Matrix();

    return 0;
}
