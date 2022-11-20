cmake_minimum_required(VERSION 3.21)
project(epsi_2023_br)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/battleroyale/headers)
include_directories(src/fighters/headers)

add_executable(epsi_2023_br
        src/battleroyale/headers/Action.h
        src/battleroyale/headers/ActionAttack.h
        src/battleroyale/headers/ActionMove.h
        src/battleroyale/headers/Arena.h
        src/battleroyale/headers/BattleRoyale.h
        src/battleroyale/headers/Fighter.h
        src/battleroyale/headers/FighterBot.h
        src/battleroyale/headers/log.h
        src/battleroyale/Action.cpp
        src/battleroyale/ActionAttack.cpp
        src/battleroyale/ActionMove.cpp
        src/battleroyale/Arena.cpp
        src/battleroyale/BattleRoyale.cpp
        src/battleroyale/Fighter.cpp
        src/battleroyale/FighterBot.cpp
        src/battleroyale/log.cpp
        src/fighters/headers/Dumb.h
        src/fighters/headers/Ghislain.h
        src/fighters/headers/Humain.h
        src/fighters/Dumb.cpp
        src/fighters/Ghislain.cpp
        src/fighters/Humain.cpp
        )
