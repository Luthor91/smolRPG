#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define MAX_SPRITES 10
#define CHARACTER_HEIGHT 32
#define CHARACTER_WIDTH 32

#define MAX_ENEMIES 50

typedef struct {
    SDL_Renderer *renderer;
    SDL_Texture *characterTexture[MAX_SPRITES];
    const char *spritePaths[MAX_SPRITES];
    int currentSpriteIndex;
    int width;
    int height;
    int x;
    int y;
    int vitality;
    int strength;
    int defense;
    int archetype;
} Character;

extern Character enemies[MAX_ENEMIES];
extern Character enemyFighted;
extern Character character;

extern int numEnemies; 


// Initialiser la texture du personnage
void initCharacterTexture(Character *character);

// Initialiser les statistiques du personnage
void initCharacterStats(Character *character, int vitality, int strength, int defense);

// Initialiser la taille du personnage
void initCharacterSize(Character *character, int width, int height);

// Initialiser la position du personnage
void initCharacterPosition(Character *character, int posx, int posy);

// Initialiser l'archétype du personnage
void initCharacterArchetype(Character *character, int archetype);

// Initialiser le personnage avec des valeurs par défaut
Character initCharacter(const char *filePath, SDL_Renderer *renderer, int archetype);

// Modifier la taille du personnage
void modifyCharacterCharacterSize(Character *character, int width, int height);

// Modifier la position du personnage
void modifyCharacterCharacterPosition(Character *character, int x, int y);

// Modifier la vitalité du personnage
void modifyCharacterVitality(Character *character, int vitality);

// Modifier la force du personnage
void modifyCharacterStrength(Character *character, int strength);

// Modifier la défense du personnage
void modifyCharacterDefense(Character *character, int defense);

// Modifier l'archétype du personnage
void modifyCharacterArchetype(Character *character, int archetype);

// Obtenir le personnage
Character getCharacter();
int getCharacterPositionY(Character *character);
int getCharacterPositionX(Character *character);
// Ajouter un sprite au tableau de chemins de fichiers
void addCharacterSprite(Character *character, const char *spritePath);

void addEnemy(Character newEnemy);
void removeEnemy(int index);

// Changer le sprite actuel en utilisant l'indice fourni
void changeCharacterCurrentSprite(Character *character, int index);

// Mouvement aléatoire du personnage
void characterMovementRandom(Character *character);

// Mouvement du personnage en restant près du bord
void characterMovementBorder(Character *character);

// Mouvement du personnage pour fuir
void characterMovementFugitive(Character *character);

// Mouvement du personnage comme un combattant
void characterMovementFighter(Character *character);

// Mouvement paresseux du personnage
void characterMovementLazy(Character *character);

// Mouvement manuel du personnage
int manualMovement(Character *character);

// Mouvement général du personnage
void characterMovement(Character *character);

// Détruire la texture du personnage
void destroyCharacter(Character *character);

#endif
