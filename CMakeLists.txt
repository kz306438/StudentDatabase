cmake_minimum_required(VERSION 3.10)

# Название вашего проекта
project(Database)

# Установка версии C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Папки с исходниками
include_directories(src src/Menu src/Widgets consoleGUI)

# Поиск всех .cpp и .h файлов в папке src и ее подкаталогах
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
    "src/Menu/*.cpp"
    "src/Menu/*.h"
    "src/Widgets/*.cpp"
    "src/Widgets/*.h"
    "consoleGUI/*.cpp"
    "consoleGUI/*.h"
    "main.cpp"
)

set(ICON_RC ${CMAKE_CURRENT_SOURCE_DIR}/icon.rc)
set(ICON_RES ${CMAKE_CURRENT_SOURCE_DIR}/res/icon.ico)

# Создание исполняемого файла с ресурсами
add_executable(Database ${SOURCES} ${ICON_RC} ${ICON_RES})


