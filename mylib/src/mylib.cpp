
#include <mylib/mylib.hpp>
#include <mylib/ExampleConfig.hpp>

#include <Eigen/Core>
#include <boost/make_shared.hpp>

#include <iostream>

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

void MyLib::Matrix() const
{
    auto mat = boost::make_shared<Eigen::Matrix2d>();
    *mat << 1.0, 2.0, 3.0, 4.0;

    std::cout << *mat << std::endl;
}

void MyLib::Version() const
{
    std::cout << CMAKE_EXAMPLE_VERSION_MAJOR << "." << CMAKE_EXAMPLE_VERSION_MINOR << std::endl;
}
