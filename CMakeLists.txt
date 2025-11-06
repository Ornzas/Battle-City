cmake_minimum_required(VERSION 3.12)
project(BattleCity)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(BattleCity
    main.cpp
    src/Game.cpp
    src/Map.cpp
    src/UI.cpp
    src/PlayerTank.cpp
    src/EnemyTank.cpp
    src/TankBase.cpp
    src/Resources.cpp
)

# путь к SFML
set(SFML_DIR "C:/libs/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)
target_link_libraries(BattleCity sfml-system sfml-window sfml-graphics)
# --- копируем SFML dll рядом с exe ---
if (WIN32)
    # путь к SFML bin (измени под свой)
    set(SFML_DLL_DIR "C:/libs/SFML-2.6.2/bin")

    add_custom_command(TARGET BattleCity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL_DIR}/sfml-system-d-2.dll"
            "${SFML_DLL_DIR}/sfml-window-d-2.dll"
            "${SFML_DLL_DIR}/sfml-graphics-d-2.dll"
            $<TARGET_FILE_DIR:BattleCity>)
endif()
