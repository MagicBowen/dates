# dates

***

## Introduction

`dates` is a FT(functional test) framework for message based system in C++! It afford a convenient way for faking the interactive systems of the SUT(system under test) and the msgs between the fake systems and SUT! You can test your SUT in dates very easily by describing the msg content and order between the faking systems and SUT !

`dates` is decoupled with any UT test framework! You can integrate dates with any C++ xUnit test framework for tests government such as  [gtest](https://github.com/google/googletest).

To learn more, visit the doc folder! You can also view the source code of tests of dates in the test folder for learning how to use in details!

## Install and Test

- Get dates

dates independs on msgcc and ccinfra, they are setted as the git submodule of dates, so you can update them together.

~~~ bash
git clone git@github.com:MagicBowen/dates.git
git submodule update --init --recursive
~~~

- Build dates

~~~ bash
cd dates
mkdir build
cd build
cmake ..
make
~~~

- Install dates

~~~ bash
sudo make install
~~~

dates will install the ccinfra and msgcc to your system at the same time.

- Test dates

To test dates itself, you need install [gtest](https://github.com/google/googletest). Gtest do not support auto installation now, so you need compile gtest, and manually put the include folder and lib like below:

> 1. Download gtest source code, and compile to generate the gtest library.
> 2. Select a path for manually installation of gtest. For example choose to manually install gtest to folder "/home/shared", enter "/home/shared" and create a folder named "gtest";
> 3. Copy the "gtest/incude" to "/home/shared/gtest", the folder will like "/home/shared/gtest/include/gtest";
> 4. Copy the "libgtest.a" which you compiled out before to "/home/shared/gtest/lib"
> 5. Now the path "/home/shared/gtest" will be your gtest root path.

~~~ bash
cd build
cmake -DGTEST_ROOT="/home/shared/gtest" ..
make
./test/dates-test
~~~

The "/home/shared/gtest" should be replaced to your gtest installed path.

## Finally

The dates now only be supported on Linux platform, all the tests run passed on Unbuntu14.04. Other OS such as Windows or Mac has not been tested! Otherwise, dates need some C++11 features suport, be sure you opened the comppile option in your makefile!