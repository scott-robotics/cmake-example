// Private header
#include "mylib-impl.hpp"

// Public headers
#include <mylib/mylib.hpp>
#include <mylib/ExampleConfig.hpp>

// Private dependencies
#include <Eigen/Core>
#include <boost/make_shared.hpp>

#include <iostream>

MyLib::~MyLib() = default;

MyLib::MyLib()
{
    impl_  = std::make_unique<MyLibImpl>();
    impl_->SetVar1(3);
    impl_->SetVar2(4.3);
}

void MyLib::Method1()
{
    impl_->SetVar2(impl_->Var2() + 4.3);
}

int MyLib::Method2() const
{
    return impl_->Var1() + 4;
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
