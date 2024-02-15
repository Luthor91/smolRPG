// characterMovement.c
#include <stdio.h>

#include "../header/characterMovement.h"


void characterHandleMovement(Character *character, int direction, int distance) {
    
    character->direction = direction;
    printf("\nDirection : %d", mainCharacter->direction);

    switch (direction) {
        case 0:
            if (character->y < distance) break;
            if (isCollidingAgainstObstacles(character->x, character->y - distance) == 1) {
                break;
            }
            character->y -= distance;
            break;
        case 1:
            if (character->x + character->width + distance > WINDOW_WIDTH) break;
            if (isCollidingAgainstObstacles(character->x + distance, character->y) == 1) {
                break;
            }
            character->x += distance;
            break;
        case 2:
            if (character->y + character->height + distance > WINDOW_HEIGHT) break;
            if (isCollidingAgainstObstacles(character->x, character->y + distance) == 1) {
                break;
            }
            character->y += distance;
            break;
        case 3:
            if (character->x < distance) break;
            if (isCollidingAgainstObstacles(character->x - distance, character->y) == 1) {
                break;
            }
            character->x -= distance;
            break;
        default:
            break;
    }
}

void characterMovementRandom(Character *character) {

    int characterStep = getCharacterSteps(character) * TILE_SIZE;
    int randomMovement = generateRandomNumber(4);
    characterHandleMovement(character, randomMovement, characterStep);
    /*
    if (randomMovement == 0) { // LEFT
        if (character->x >=  character->nbstep) {  

            character->x -=  character->nbstep;

        } else {
            randomMovement++;
        }
    }
    if (randomMovement == 1) { // RIGHT
        if (character->x + character->width < WINDOW_WIDTH) {
            character->x +=  character->nbstep;
        } else {
            randomMovement++;
        }
    }
    if (randomMovement == 2) { // UP
        if (character->y >=  character->nbstep) {
            character->y -=  character->nbstep;
        } else {
            randomMovement++;
        }
    }
    if (randomMovement == 3) { // DOWN
        if (character->y + character->height < WINDOW_HEIGHT) {
            characterHandleMovement(character, 2, characterStep);
        }else {
            randomMovement++; // Reboucler au debut ?
        }
    }
    */
}

void characterMovementBorder(Character *character) {

    int randomMovement = generateRandomNumber(1);

    int closestWallX = 0;
    int closestWallY = 0;
    int characterStep = getCharacterSteps(character) * TILE_SIZE;

    if ( (WINDOW_WIDTH - character->x) < character->x ) {
        closestWallX = WINDOW_WIDTH - character->x;
    }

    if ( (WINDOW_HEIGHT - character->y) < character->y ) {
        closestWallY = WINDOW_HEIGHT - character->y;
    }

    if ( closestWallX < closestWallY ) {
        switch (randomMovement) {
            case 0:
                if (character->y <  characterStep) break;
                characterHandleMovement(character, 0, characterStep);
                break;
            case 1:
                if (character->y +  characterStep >= WINDOW_HEIGHT) break;
                characterHandleMovement(character, 2, characterStep);
                break;
        }
    }
    else if ( closestWallX > closestWallY ){
        switch (randomMovement) {
            case 0:
                if (character->x <  characterStep) break;
                characterHandleMovement(character, 3, characterStep);
                break;
            case 1:
                if (character->x +  characterStep >= WINDOW_WIDTH) break;
                characterHandleMovement(character, 1, characterStep);
                break;
        }
    }
    else { characterMovementRandom(character); }

}

void characterMovementFugitive(Character *character) {
    Character mainCharacter = getMainCharacter();
    int mainCharacterPosX = getCharacterPositionX(&mainCharacter);
    int mainCharacterPosY = getCharacterPositionY(&mainCharacter);
    int characterStep = getCharacterSteps(character) * TILE_SIZE;
    // Calculer la différence entre les positions du personnage et de l'ennemi
    int deltaX = mainCharacterPosX - character->x;
    int deltaY = mainCharacterPosY - character->y;

    // Si l'ennemi est dans un coin, choisir une direction aléatoire
    if ((character->x <=  characterStep && character->y <=  characterStep) ||
        (character->x +  characterStep >= WINDOW_WIDTH -  characterStep && character->y <=  characterStep) ||
        (character->x <=  characterStep && character->y +  characterStep >= WINDOW_HEIGHT -  characterStep) ||
        (character->x +  characterStep >= WINDOW_WIDTH -  characterStep && character->y +  characterStep >= WINDOW_HEIGHT -  characterStep)) {

        int randomDirection = generateRandomNumber(4);
        characterHandleMovement(character, randomDirection, characterStep);

    } else {
        // Choisir la direction opposée
        if (abs(deltaX) > abs(deltaY)) {
            // Se déplacer horizontalement
            if (deltaX > 0 && character->x >=  characterStep) {
                characterHandleMovement(character, 3, characterStep);
            } else if (deltaX < 0 && character->x +  characterStep < WINDOW_WIDTH -  characterStep) {
                characterHandleMovement(character, 1, characterStep);
            }
        } else {
            // Se déplacer verticalement
            if (deltaY > 0 && character->y >=  characterStep) {
                characterHandleMovement(character, 0, characterStep);
            } else if (deltaY < 0 && character->y +  characterStep < WINDOW_HEIGHT -  characterStep) {
                characterHandleMovement(character, 2, characterStep);
            }
        }
    }
}

void characterMovementFighter(Character *character) {
    Character mainCharacter = getMainCharacter();
    int mainCharacterPosX = getCharacterPositionX(&mainCharacter);
    int mainCharacterPosY = getCharacterPositionY(&mainCharacter);

    // Calculer la différence entre les positions du personnage et de l'ennemi
    int deltaX = mainCharacterPosX - character->x;
    int deltaY = mainCharacterPosY - character->y;

    // S'assurer que l'ennemi est à plus d'une case de distance du personnage
    if (abs(deltaX) >  character->nbstep || abs(deltaY) >  character->nbstep) {
        // Choisir la direction en fonction des différences
        if (abs(deltaX) > abs(deltaY)) {
            // Se déplacer horizontalement
            if (deltaX > 0 && character->x +  character->nbstep < WINDOW_WIDTH -  character->nbstep) {
                characterHandleMovement(character, 1, character->nbstep);
            } else if (deltaX < 0 && character->x >=  character->nbstep) {
                characterHandleMovement(character, 3, character->nbstep);
            }
        } else {
            // Se déplacer verticalement
            if (deltaY > 0 && character->y +  character->nbstep < WINDOW_HEIGHT -  character->nbstep) {
                characterHandleMovement(character, 2, character->nbstep);
            } else if (deltaY < 0 && character->y >=  character->nbstep) {
                characterHandleMovement(character, 0, character->nbstep);
            }
        }
    }
}

void characterMovementLazy(Character *character) {

    int randomMovement = generateRandomNumber(12);
    characterHandleMovement(character, randomMovement, character->nbstep);

}

int manualMovement(Character *character) {

    SDL_Event event;
    int characterStep = getCharacterSteps(character) * TILE_SIZE;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            exit(0);
        } else if (event.type == SDL_KEYDOWN) {
            if(event.key.keysym.sym == SDLK_LEFT) {
                characterHandleMovement(character, 3, characterStep);
                return 1;
            } else if(event.key.keysym.sym == SDLK_RIGHT) {
                characterHandleMovement(character, 1, characterStep);
                return 1;
            } else if(event.key.keysym.sym == SDLK_UP) {
                characterHandleMovement(character, 0, characterStep);
                return 1;
            } else if(event.key.keysym.sym == SDLK_DOWN) {
                characterHandleMovement(character, 2, characterStep);
                return 1;
            } else if (event.key.keysym.sym == SDLK_SPACE) {
                characterSpecialMovementDash(character);
                return 1;
            }
            return 0;
        }
        return 0;
    }
}

void characterSpecialMovementDash(Character *character) {

    int dashLength = TILE_SIZE * getCharacterSteps(character) * 2;
    characterHandleMovement(character, character->direction, dashLength);

}

void characterMovementManager(Character *character) {
    Character mainCharacter = getMainCharacter();

    if(character->vitality <= 0) { return; }

    int mainCharacterPosX = getCharacterPositionX(&mainCharacter);
    int mainCharacterPosY = getCharacterPositionY(&mainCharacter);

    switch (character->archetype) {
        case 0:
            characterMovementRandom(character);
            break;
        case 1:
            characterMovementLazy(character);
            break;
        case 2:
            characterMovementBorder(character);
            break;
        case 3:
            characterMovementFugitive(character);
            break;
        case 4:
            characterMovementFighter(character);
            break;
    } 
    return;
}
