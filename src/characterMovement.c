// characterMovement.c
#include <stdio.h>

#include "../header/characterMovement.h"

void characterMovementRandom(Character *character) {

    int randomMovement = generateRandomNumber(4);

    switch (randomMovement) {
        case 0:
            if (character->x < TILE_SIZE) break;
            character->x -= TILE_SIZE;
            break;
        case 1:
            if (character->x + TILE_SIZE >= WINDOW_WIDTH) break;
            character->x += TILE_SIZE;
            break;
        case 2:
            if (character->y < TILE_SIZE) break;
            character->y -= TILE_SIZE;
            break;
        case 3:
            if (character->y + TILE_SIZE >= WINDOW_HEIGHT) break;
            character->y += TILE_SIZE;
            break;
    }
}

void characterMovementBorder(Character *character) {

    int randomMovement = generateRandomNumber(1);

    int closestWallX = 0;
    int closestWallY = 0;

    if ( (WINDOW_WIDTH - character->x) < character->x ) {
        closestWallX = WINDOW_WIDTH - character->x;
    }

    if ( (WINDOW_HEIGHT - character->y) < character->y ) {
        closestWallY = WINDOW_HEIGHT - character->y;
    }

    if ( closestWallX < closestWallY ) {
        switch (randomMovement) {
            case 0:
                if (character->y < TILE_SIZE) break;
                character->y -= TILE_SIZE;
                break;
            case 1:
                if (character->y + TILE_SIZE >= WINDOW_HEIGHT) break;
                character->y += TILE_SIZE;
                break;
        }
    }
    else if ( closestWallX > closestWallY ){
        switch (randomMovement) {
            case 0:
                if (character->x < TILE_SIZE) break;
                character->x -= TILE_SIZE;
                break;
            case 1:
                if (character->x + TILE_SIZE >= WINDOW_WIDTH) break;
                character->x += TILE_SIZE;
                break;
        }
    }
    else { characterMovementRandom(character); }

}

void characterMovementFugitive(Character *character) {
    Character mainCharacter = getMainCharacter();
    int mainCharacterPosX = getCharacterPositionX(&mainCharacter);
    int mainCharacterPosY = getCharacterPositionY(&mainCharacter);

    // Calculer la différence entre les positions du personnage et de l'ennemi
    int deltaX = mainCharacterPosX - character->x;
    int deltaY = mainCharacterPosY - character->y;

    // Si l'ennemi est dans un coin, choisir une direction aléatoire
    if ((character->x <= TILE_SIZE && character->y <= TILE_SIZE) ||
        (character->x + TILE_SIZE >= WINDOW_WIDTH - TILE_SIZE && character->y <= TILE_SIZE) ||
        (character->x <= TILE_SIZE && character->y + TILE_SIZE >= WINDOW_HEIGHT - TILE_SIZE) ||
        (character->x + TILE_SIZE >= WINDOW_WIDTH - TILE_SIZE && character->y + TILE_SIZE >= WINDOW_HEIGHT - TILE_SIZE)) {

        int randomDirection = generateRandomNumber(4);

        switch (randomDirection) {
            case 0:
                if (character->x >= TILE_SIZE) {
                    character->x -= TILE_SIZE;
                }
                break;
            case 1:
                if (character->x + TILE_SIZE < WINDOW_WIDTH) {
                    character->x += TILE_SIZE;
                }
                break;
            case 2:
                if (character->y >= TILE_SIZE) {
                    character->y -= TILE_SIZE;
                }
                break;
            case 3:
                if (character->y + TILE_SIZE < WINDOW_HEIGHT) {
                    character->y += TILE_SIZE;
                }
                break;
            default:
                break;
        }
    } else {
        // Choisir la direction opposée
        if (abs(deltaX) > abs(deltaY)) {
            // Se déplacer horizontalement
            if (deltaX > 0 && character->x >= TILE_SIZE) {
                character->x -= TILE_SIZE;
            } else if (deltaX < 0 && character->x + TILE_SIZE < WINDOW_WIDTH - TILE_SIZE) {
                character->x += TILE_SIZE;
            }
        } else {
            // Se déplacer verticalement
            if (deltaY > 0 && character->y >= TILE_SIZE) {
                character->y -= TILE_SIZE;
            } else if (deltaY < 0 && character->y + TILE_SIZE < WINDOW_HEIGHT - TILE_SIZE) {
                character->y += TILE_SIZE;
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
    if (abs(deltaX) > TILE_SIZE || abs(deltaY) > TILE_SIZE) {
        // Choisir la direction en fonction des différences
        if (abs(deltaX) > abs(deltaY)) {
            // Se déplacer horizontalement
            if (deltaX > 0 && character->x + TILE_SIZE < WINDOW_WIDTH - TILE_SIZE) {
                character->x += TILE_SIZE;
            } else if (deltaX < 0 && character->x >= TILE_SIZE) {
                character->x -= TILE_SIZE;
            }
        } else {
            // Se déplacer verticalement
            if (deltaY > 0 && character->y + TILE_SIZE < WINDOW_HEIGHT - TILE_SIZE) {
                character->y += TILE_SIZE;
            } else if (deltaY < 0 && character->y >= TILE_SIZE) {
                character->y -= TILE_SIZE;
            }
        }
    }
}

void characterMovementLazy(Character *character) {

    int randomMovement = generateRandomNumber(12);

    switch (randomMovement) {
        case 0:
            if (character->x < TILE_SIZE) break;
            character->x -= TILE_SIZE;
            break;
        case 1:
            if (character->x + TILE_SIZE >= WINDOW_WIDTH) break;
            character->x += TILE_SIZE;
            break;
        case 2:
            if (character->y < TILE_SIZE) break;
            character->y -= TILE_SIZE;
            break;
        case 3:
            if (character->y + TILE_SIZE >= WINDOW_HEIGHT) break;
            character->y += TILE_SIZE;
            break;
    }

}

int manualMovement(Character *character) {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
        else if (event.type == SDL_KEYDOWN) {

            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    if (character->x < TILE_SIZE) break;
                    character->x -= TILE_SIZE;
                    return 1;
                case SDLK_RIGHT:
                    if (character->x + TILE_SIZE >= WINDOW_WIDTH) break;
                    character->x += TILE_SIZE;
                    return 1;
                case SDLK_UP:
                    if (character->y < TILE_SIZE) break;
                    character->y -= TILE_SIZE;
                    return 1;
                case SDLK_DOWN:
                    if (character->y + TILE_SIZE >= WINDOW_HEIGHT) break;
                    character->y += TILE_SIZE;
                    return 1;  
            }
            return 0;
        }
        return 0;
    }
}

void characterMovement(Character *character) {
    Character mainCharacter = getMainCharacter();

    if(character->vitality <= 0) { return; }

    int mainCharacterPosX = getCharacterPositionX(&mainCharacter);
    int mainCharacterPosY = getCharacterPositionY(&mainCharacter);

    if( (character->x == mainCharacterPosX) && (character->y == mainCharacterPosY) ) {
        isInFight = 1;
        enemyFighted = *character;
    }
    else {
        isInFight = 0;
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
    }
    return;
}


