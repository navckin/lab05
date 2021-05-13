[![Build Status](https://travis-ci.com/navckin/lab04.svg?branch=main)](https://travis-ci.com/navckin/lab04)
<фрагмент_вставки_значка>
## Laboratory work III


Данная лабораторная работа посвещена изучению систем автоматизации сборки проекта на примере **CMake**



## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab03** на сервисе **GitHub**
- [x] 2. Ознакомиться со ссылками учебного материала
- [x] 3. Выполнить инструкцию учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**


## Report

```sh
$ popd
$ export LAB_NUMBER=03
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Homework

Представьте, что вы стажер в компании "Formatter Inc.".
### Задание 1
Вам поручили перейти на систему автоматизированной сборки **CMake**.
Исходные файлы находятся в директории [formatter_lib](formatter_lib).
В этой директории находятся файлы для статической библиотеки *formatter*.
Создайте `CMakeList.txt` в директории [formatter_lib](formatter_lib),
с помощью которого можно будет собирать статическую библиотеку *formatter*.

```sh
1. Скчаиваем лаб-ую работу lab03 при помощи команды git clone https://github.com/tp-labs/lab03
2. Создаем файл CMakeLists.txt ( CMakeLists.txt - это файл, в котором описана процедура сборки файлов)

cat > CMakeLists.txt <<EOF
> cmake_minimum_required(VERSION 3.4) ---> минимально необходимая версия для работы файлов
> add_library(formatter STATIC formatter.h formatter.cpp) ---> делаем статическую библиотеку из файлов
> EOF

3. Подключили к симэйку файлы
cmake ~/navckin/workspace/tasks/lab03/lab03/formatter_lib
4. Используем команду make ---> создаем биб-ку
5. Появился файл formatter.a

```


### Задание 2
У компании "Formatter Inc." есть перспективная библиотека,
которая является расширением предыдущей библиотеки. Т.к. вы уже овладели
навыком созданием `CMakeList.txt` для статической библиотеки *formatter*, ваш 
руководитель поручает заняться созданием `CMakeList.txt` для библиотеки 
*formatter_ex*, которая в свою очередь использует библиотеку *formatter*.
```sh
1. Копируем содержимое папки formatter_lib в formatter_ex_lib.
Используем команду:
cp -r formatter_lib formatter_ex_lib/
2.
Заполняем биб-ку
cat > CMakeLists.txt <<EOF
>cmake_minimum_required(VERSION 3.4)---> минимально необходимая версия для работы файлов
>project(formatter_ex)
>include_directories(formatter_lib) ---> пдключили дир-ию с заголовочными файлами
>add_subdirectory(formatter_lib) ---> подключили дир-рию с библиотекой, в которой уже есть СиМэйкЛистс.ткст, который и "собирает" ее.
>add_library(formatter_ex STATIC formatter_ex.h formatter_ex.cpp) ---> делаем статическую библиотеку из файлов
>target_link_libraries(formatter_ex formatter) ---> для компиляции форматтер_екс будем использовать биб-ку форматтер

```

### Задание 3
Конечно же ваша компания предоставляет примеры использования своих библиотек.
Чтобы продемонстрировать как работать с библиотекой *formatter_ex*,
вам необходимо создать два `CMakeList.txt` для двух простых приложений:
* *hello_world*, которое использует библиотеку *formatter_ex*;
* *solver*, приложение которое испольует статические библиотеки *formatter_ex* и *solver_lib*.

```sh
ПЕРВОЕ:
1. Необходимо переместить форматтер_екс в папку с хеллоу_ворлд.
Используем команду:
mv formatter_ex_lib/ hello_world_application/
2. Создаем Симэйк со след. начинкой:
cat > CMakeLists.txt <<EOF
>cmake_minimum_required(VERSION 3.4)
>project(hello_world)
>include_directories(formatter_ex_lib)
>add_subdirectory(formatter_ex_lib)
>add_executable(hello_world hello_world.cpp)
>target_link_libraries(hello_world formatter_ex)
>EOF
3. Используем cmake 
~/navckin/workspace/tasks/lab03/lab03/hello_world_application$ cmake ~/navckin/workspace/tasks/lab03/lab03/hello_world_application
-- Configuring done
-- Generating done
-- Build files have been written to: /home/anya/navckin/workspace/tasks/lab03/lab03/hello_world_application
4. make
5. После комнды make в дир-рии hello_world_application появился файл hello_world
```

```sh
ВТОРОЕ:
1. Необходимо создать Симэйки для солвер_либ и солвер_аппликатион
2. Создание происходит аналогично пунктами выше, начинка для солвер_либ такая:
cmake_minimum_required(VERSION 3.4) 
add_library(solver_lib STATIC solver.h solver.cpp)

Начинка для солвер_аппликатион такая:
cmake_minimum_required(VERSION 3.4)
project(solver)
add_executable(solver equation.cpp)
include_directories(formatter_ex_lib)
add_subdirectory(formatter_ex_lib)
include_directories(solver_lib)
add_subdirectory(solver_lib)
target_link_libraries(solver formatter_ex)
target_link_libraries(solver solver_lib)

3. Повторяем те же команды: сборка, запуск.
4. Предварительно переместив при помощи команды mv солвер_либ,форматтер_ех_либ в солвер.аппплекатион
5. При использовании команды make выяснилось, что в файле solver.cpp
есть опечатки: исправлем. при помощи текстового редактора дописали нужную биб-ку (cmath) и исправили команду корня (sqrt)
6. Появился файл solver
```
**Удачной стажировки!**

```
Copyright (c) 2015-2020 The ISC Authors & navckin
```
