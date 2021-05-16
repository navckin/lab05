[![Build Status](https://travis-ci.com/navckin/lab04.svg?branch=main)](https://travis-ci.com/navckin/lab04)

## Laboratory work V

Данная лабораторная работа посвещена изучению фреймворков для тестирования на примере **GTest**

```sh
$ open https://github.com/google/googletest
```

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab05** на сервисе **GitHub**
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Ознакомиться со ссылками учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**


## Homework

### Задание
1. Создайте `CMakeList.txt` для библиотеки *banking*.
2. Создайте модульные тесты на классы `Transaction` и `Account`.
    * Используйте mock-объекты.
    * Покрытие кода должно составлять 100%.
3. Настройте сборочную процедуру на **TravisCI**.
4. Настройте [Coveralls.io](https://coveralls.io/).

Cоздаем стандартный файл CMakeLists.txt. Для удобства дальнейшего подключения тестов расположим его в корне репозитория

```
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(banking)

add_library(banking STATIC banking/Account.cpp banking/Transaction.cpp)
target_include_directories(banking PUBLIC banking/)
```

Указываем имя проекта, какую версию симейка и какой стандарт языка нужно использовать. Затем, добавляем в нашу "библиотеку" два .cpp файла, указываем папку, где проект будет искать включаемые файлы.

```
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TEST "Build tests" OFF)

project(banking)

add_library(banking STATIC banking/Account.cpp banking/Transaction.cpp)
target_include_directories(banking PUBLIC banking/)

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(submodules/gtest)
	add_executable(check tests/tests.cpp)
	target_link_libraries(check banking gtest_main gmock_main)
	add_test(NAME check COMMAND check)
endif()
```
Файл с тестами:

```
#include "Account.h"
#include "Transaction.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class AccountMock : public Account {
public:
	AccountMock(int id, int balance) : Account(id, balance) {}
	MOCK_CONST_METHOD0(GetBalance, int());
	MOCK_METHOD1(ChangeBalance, void(int diff));
	MOCK_METHOD0(Lock, void());
	MOCK_METHOD0(Unlock, void());
};
class TransactionMock : public Transaction {
public:
	MOCK_METHOD3(Make, bool(Account& from, Account& to, int sum));
};

TEST(Account, Mock) {
	AccountMock acc(1, 100);
	EXPECT_CALL(acc, GetBalance()).Times(1);
	EXPECT_CALL(acc, ChangeBalance(testing::_)).Times(2);
	EXPECT_CALL(acc, Lock()).Times(2);
	EXPECT_CALL(acc, Unlock()).Times(1);
	acc.GetBalance();
	acc.ChangeBalance(100); // throw
	acc.Lock();
	acc.ChangeBalance(100);
	acc.Lock(); // throw
	acc.Unlock();
}

TEST(Account, SimpleTest) {
	Account acc(1, 100);
	EXPECT_EQ(acc.id(), 1);
	EXPECT_EQ(acc.GetBalance(), 100);
	EXPECT_THROW(acc.ChangeBalance(100), std::runtime_error);
	EXPECT_NO_THROW(acc.Lock());
	acc.ChangeBalance(100);
	EXPECT_EQ(acc.GetBalance(), 200);
	EXPECT_THROW(acc.Lock(), std::runtime_error);
}

TEST(Transaction, Mock) {
	TransactionMock tr;
	Account ac1(1, 50);
	Account ac2(2, 500);
	EXPECT_CALL(tr, Make(testing::_, testing::_, testing::_))
	.Times(6);
	tr.set_fee(100);
	tr.Make(ac1, ac2, 199);
	tr.Make(ac2, ac1, 500);
	tr.Make(ac2, ac1, 300);
	tr.Make(ac1, ac1, 0); // throw
	tr.Make(ac1, ac2, -1); // throw
	tr.Make(ac1, ac2, 99); // throw
}

TEST(Transaction, SimpleTest) {
	Transaction tr;
	Account ac1(1, 50);
	Account ac2(2, 500);
	tr.set_fee(100);
	EXPECT_EQ(tr.fee(), 100);
	EXPECT_THROW(tr.Make(ac1, ac1, 0), std::logic_error);
	EXPECT_THROW(tr.Make(ac1, ac2, -1), std::invalid_argument);
	EXPECT_THROW(tr.Make(ac1, ac2, 99), std::logic_error);
	EXPECT_FALSE(tr.Make(ac1, ac2, 199));
	EXPECT_FALSE(tr.Make(ac2, ac1, 500));
	EXPECT_TRUE(tr.Make(ac2, ac1, 300));
}
```
Создаем .travis.yml
```
language: cpp

os:
  - linux

addons:
  apt:
    sources:
    - george-edison55-precise-backports
    packages:
    - cmake
    - cmake-data

script:
- cmake -H. -B_build -DBUILD_TESTS=ON
- cmake --build _build
- cmake --build _build --target test -- ARGS=--verbose
```
Создаем Coveralls.io

```                              
service_name: travis-pro
repo_token: 9X9fZnF0HJEKcmgbhe4BNkBvjydYrZRCS
```
Добавляем в симэйк:

```
option(COVERAGE "Check coverage" ON)
...
if (COVERAGE)
	target_compile_options(check PRIVATE --coverage)
	target_link_libraries(check --coverage)
endif()
```
Добавляем в .travis.yml:

```
before_install:
- pip install --user cpp-coveralls
...
after_success:
- coveralls --root . -E ".*gtest.*" -E ".*CMakeFiles.*"
```

## Links

- [C++ CI: Travis, CMake, GTest, Coveralls & Appveyor](http://david-grs.github.io/cpp-clang-travis-cmake-gtest-coveralls-appveyor/)
- [Boost.Tests](http://www.boost.org/doc/libs/1_63_0/libs/test/doc/html/)
- [Catch](https://github.com/catchorg/Catch2)

```
Copyright (c) 2015-2021 The ISC Authors
```
```
