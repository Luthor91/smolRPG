cmake_minimum_required(VERSION 3.10)
project(my_project)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-O3")

set(SOURCES
  src/main.c
  src/game.c
  src/character.c
  src/characterMovement.c
  src/obstacle.c
  src/spell.c
  src/fight.c
  src/drawBackground.c
  src/fightDraw.c
  src/functions.c
)

set(INCLUDE_DIRS
  header
  /usr/include/SDL2
  /usr/include/SDL2_image
)

set(LIBRARIES
  SDL2
  SDL2_image
)

add_executable(my_project ${SOURCES})

target_include_directories(my_project PRIVATE ${INCLUDE_DIRS})
target_link_libraries(my_project PRIVATE ${LIBRARIES})