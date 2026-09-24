cmake_minimum_required(VERSION 3.10)
project(Blackjack C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

set(SOURCES
    src/main.c
    src/card.c
    src/game.c
    src/ui.c)

add_executable(blackjack ${SOURCES})

if(MSVC)
    target_compile_options(blackjack PRIVATE /W4)
else()
    target_compile_options(blackjack PRIVATE -Wall -Wextra)
endif()