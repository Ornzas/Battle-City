cmake_minimum_required(VERSION 3.12)
project(BattleCity)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(BattleCity
    main.cpp
    src/Game.cpp
    src/Map.cpp
    src/Tank.cpp
    src/UI.cpp
)

# путь к SFML
set(SFML_DIR "C:/libs/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)
target_link_libraries(BattleCity sfml-system sfml-window sfml-graphics)
