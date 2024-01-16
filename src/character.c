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
    printf("Ajout de sprite : Chemin = %s\n", spritePath);

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

Character initCharacter(const char *filePath, SDL_Renderer *renderer, int archetype) {
    Character *character = (Character*)malloc(sizeof(Character));

    initCharacterPosition(character, 0, 0);
    initCharacterSize(character, 32, 32);
    initCharacterStats(character, 100, 10, 5);
    initCharacterArchetype(character, archetype);

    character->renderer = renderer;

    for (int i = 0; i < MAX_SPRITES; i++) {
        character->spritePaths[i] = NULL;
    }

    if (filePath && filePath[0] != '\0') { addCharacterSprite(character, filePath); } 
    else { addCharacterSprite(character, "assets/characters/main_character/default_idle_1.png"); }

    initCharacterTexture(character);

    return *character;
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
    if(vitality <= 0) {
        destroyCharacter(character);
        isInFight = 0;
    }
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

Character getCharacter() {
    return character;
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
        enemies[numEnemies] = newEnemy;
        numEnemies++;
    } else {
        fprintf(stderr, "Impossible d'ajouter plus d'ennemis. Tableau plein.\n");
    }
}

// Retirez un ennemi de la liste en fonction de l'indice
void removeEnemy(int index) {
    if (index >= 0 && index < numEnemies) {
        // Déplacez les éléments suivants d'un indice vers le haut pour remplir l'emplacement supprimé
        for (int i = index; i < numEnemies - 1; i++) {
            enemies[i] = enemies[i + 1];
        }
        numEnemies--;
    } else {
        fprintf(stderr, "Indice d'ennemi invalide.\n");
    }
}


void destroyCharacter(Character *character) {
    for (int i = 0; i < MAX_SPRITES; i++) {
        SDL_DestroyTexture(character->characterTexture[i]);
    }

    free(character);
}
