// character.c
#include "../header/functions.h"
#include "../header/character.h"
#include "../header/characterMovement.h"
#include "../header/game.h"
#include "../header/fight.h"
#include <stdio.h>

void initCharacterTexture(Character *character) {
    if (!character->renderer) {
        fprintf(stderr, "Erreur : le rendu n'est pas initialisé pour le personnage.\n");
        exit(EXIT_FAILURE);
    }

    const char *spritePath = character->spritePaths[character->currentSpriteIndex];
    
    if (!spritePath) {
        fprintf(stderr, "Erreur : le chemin du sprite est NULL.\n");
        exit(EXIT_FAILURE);
    }

    SDL_Surface *personnageSurface = IMG_Load(spritePath);
    if (!personnageSurface) {
        fprintf(stderr, "Erreur lors du chargement de l'image du personnage : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    character->characterTexture[character->currentSpriteIndex] = SDL_CreateTextureFromSurface(character->renderer, personnageSurface);

    SDL_FreeSurface(personnageSurface);

    if (!character->characterTexture[character->currentSpriteIndex]) {
        fprintf(stderr, "Erreur lors de la création de la texture du personnage : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void initCharacterStats(Character *character, int vitality, int strength, int defense) {
    character->vitality = vitality;
    character->strength = strength;
    character->defense = defense;
}

void initCharacterSize(Character *character, int width, int height) {
    character->width = width;
    character->height = height;
}

void initCharacterPosition(Character *character, int posx, int posy) {
    character->x = posx;
    character->y = posy;
}

void initCharacterArchetype(Character *character, int archetype) {
    character->archetype = archetype;
}

Character *initCharacter(const char *filePath, SDL_Renderer *renderer, int archetype) {
    
    Character *charac = (Character*)calloc(1, sizeof(Character));

    if (charac == NULL) {
        fprintf(stderr, "Erreur : échec de l'allocation de mémoire pour Character.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_SPRITES; i++) {
        charac->spritePaths[i] = NULL;
    }

    if (filePath && filePath[0] != '\0') { addCharacterSprite(charac, filePath); } 
    else { addCharacterSprite(charac, "assets/characters/main_character/default_idle_1.png"); }

    charac->renderer = renderer;


    initCharacterPosition(charac, 0, 0);
    initCharacterSize(charac, 32, 32);
    initCharacterStats(charac, 100, 10, 5);
    initCharacterArchetype(charac, archetype);
    initCharacterTexture(charac);

    return charac;
}

void modifyCharacterSize(Character *character, int width, int height) {
    character->width = width;
    character->height = height;
}

void modifyCharacterPosition(Character *character, int x, int y) {
    character->x = x;
    character->y = y;
}

void modifyCharacterVitality(Character *character, int vitality) {
    character->vitality = vitality;
}

void modifyCharacterStrength(Character *character, int strength) {
    character->strength = strength;
}

void modifyCharacterDefense(Character *character, int defense) {
    character->defense = defense;
}

void modifyCharacterArchetype(Character *character, int archetype) {
    character->archetype = archetype;
}

Character getMainCharacter() {
    return *mainCharacter;
}

int getCharacterPositionX(Character *character) {
    return character->x;
}

int getCharacterPositionY(Character *character) {
    return character->y;
}

// Ajouter un sprite au tableau de chemins de fichiers
void addCharacterSprite(Character *character, const char *spritePath) {
    int index = character->currentSpriteIndex;

    if (index < MAX_SPRITES)    { character->spritePaths[index] = spritePath; } 
    else                        { fprintf(stderr, "Impossible d'ajouter plus de sprites. Tableau plein.\n"); }
}

// Changer le sprite actuel en utilisant l'indice fourni
void changeCharacterCurrentSprite(Character *character, int index) {
    if (index >= 0 && index < MAX_SPRITES)  { character->currentSpriteIndex = index; } 
    else                                    { fprintf(stderr, "Indice de sprite invalide.\n"); }
}

// Ajoutez un ennemi à la liste
void addEnemy(Character newEnemy) {
    if (numEnemies < MAX_ENEMIES) {
        newEnemy.index = numEnemies;
        enemies[numEnemies] = newEnemy;
        numEnemies++;
    } else {
        fprintf(stderr, "Impossible d'ajouter plus d'ennemis. Tableau plein.\n");
    }
}

// Retirez un ennemi de la liste en fonction de l'indice
void removeEnemy(int index) {
    if (index >= 0 && index < numEnemies) {
        
        destroyCharacter(&enemies[index]);
        printf("Memory freed for enemy at index %d\n", index);

        // Déplacez les éléments suivants d'un indice vers le haut pour remplir l'emplacement supprimé
        for (int i = index; i < numEnemies - 1; i++) {
            enemies[i] = enemies[i + 1];
        }
        numEnemies--;
    } else {
        fprintf(stderr, "Indice d'ennemi invalide.\n");
    }
}

void printCharacter(Character *character) {
    printf("\nvit: %d, str: %d, def: %d\nw: %d, h: %d\nx: %d, y: %d\n", 
        character->vitality, character->strength, 
        character->defense, character->width, 
        character->x, character->y
    );
}

void destroyCharacter(Character *charac) {
    for (size_t i = 0; i < MAX_SPRITES; i++) {
        SDL_DestroyTexture(charac->characterTexture[i]);
    }
    free(charac);
}

int isCollidingAgainstEnemies(int posx, int posy) {
    for (size_t i = 0; i < numEnemies; i++) {
        //printf("\nX : %d => %d", enemies[i].x, enemies[i].x);
        printf("\nW : %d ; H : %d, nbcase : %d", enemies[i].width, enemies[i].height, enemies[i].width/32);

        for (size_t j = 0; j < enemies[i].width/32; j++)
        {
            if (
                ((posx > enemies[i].x * j) && (posx < (enemies[i].x * j) + enemies[i].width))
                &&
                ((posy > enemies[i].y) && (posx < enemies[i].y + enemies[i].height))
            ) {
                printf("\nCollision avec un enemi");
                return 1;
            }
        }
        
    }
    return 0;
}

            

Character* getCollidingEnemy(Character* player, int posx, int posy) {
    for (size_t i = 0; i < numEnemies; i++) {
        //printf("\nX : %d => %d", enemies[i].x, enemies[i].x+enemies[i].width);
        //printf("\nY : %d => %d", enemies[i].y, enemies[i].y+enemies[i].height);

        for (size_t j = 0; j < enemies[i].width/32; j++)
        {
            if (
                ((posx > enemies[i].x * j) && (posx < (enemies[i].x * j) + enemies[i].width))
                &&
                ((posy > enemies[i].y) && (posx < enemies[i].y + enemies[i].height))
            ) {
                printf("\nCollision avec un enemi");
                return &enemies[i];
            }
        }
       
    }
    return 0;
}
