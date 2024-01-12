#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Définir la constante pour le nombre maximum de sprites
#define MAX_SPRITES 10
#define CHARACTER_HEIGHT 32
#define CHARACTER_WIDTH 32

// Déclaration de la structure Character
typedef struct {
    int vitality;
    int strength;
    int defense;
    int x;
    int y;
    int width;
    int height;

    const char *spritePaths[MAX_SPRITES];
    SDL_Texture *characterTexture[MAX_SPRITES];
    int currentSpriteIndex;
    SDL_Renderer *renderer;  // Ajouter cette ligne
} Character;


// Fonctions pour initialiser et gérer le personnage
void initCharacter(Character *character, const char *filePath, SDL_Renderer *renderer) ;
void initCharacterTexture(Character *character);
void addSprite(Character *character, const char *spritePath);
void changeCurrentSprite(Character *character, int index);
void destroyCharacter(Character *character);

// Fonctions pour modifier les statistiques du personnage
void modifyVitality(Character *character, int vitality);
void modifyStrength(Character *character, int strength);
void modifyDefense(Character *character, int defense);

// Fonction pour afficher les statistiques du personnage
void printStats(Character *character);

// Fonction pour modifier sa position dans l'espace
void characterMovement(Character *character);
void modifyCharacterSize(Character *character, int x, int y);
void modifyCharacterPosition(Character *character, int width, int height);

#endif
