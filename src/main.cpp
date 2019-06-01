
#include <iostream>
#include <Eigen/Core>

#include <mylib/mylib.h>
#include "ExampleConfig.h"

int main(int agrc, char* argv[])
{
    MyLib testlib;

    testlib.Method1();
    std::cout << "Your test library works! Method2() = "
              << testlib.Method2() << std::endl;
    std::cout << "Version: " <<
                  CMAKE_EXAMPLE_VERSION_MAJOR << "." <<
                  CMAKE_EXAMPLE_VERSION_MINOR << std::endl;

    return 0;
}