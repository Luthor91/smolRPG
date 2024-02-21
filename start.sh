#!/bin/bash

sudo gcc -o main ./src/main.c ./src/game.c ./src/character.c ./src/characterMovement.c ./src/obstacle.c ./src/spell.c ./src/fight.c ./src/drawBackground.c ./src/fightDraw.c ./src/functions.c -I ./header -I /usr/include/SDL2 -I /usr/include/SDL2_image -L /usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image && sudo chmod 777 ./main && ./main
