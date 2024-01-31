#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../header/obstacle.h"

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
    int index;
    int direction;
    int nbstep;
} Character;

extern Character enemies[MAX_ENEMIES];
extern Character enemyFighted;
extern Character *mainCharacter;

extern int numEnemies;

void initCharacterTexture(Character *character);
void initCharacterStats(Character *character, int vitality, int strength, int defense);
void initCharacterSize(Character *character, int width, int height);
void initCharacterPosition(Character *character, int posx, int posy);
void initCharacterArchetype(Character *character, int archetype);
void initCharacterColor(Character *character);
void initCharacterStep(Character *character);
void initCharacterDirection(Character *character);

Character *initCharacter(const char *filePath, SDL_Renderer *renderer, int archetype);

void modifyCharacterStep(Character *character, int step);
void modifyCharacterCharacterSize(Character *character, int width, int height);
void modifyCharacterCharacterPosition(Character *character, int x, int y);
void modifyCharacterVitality(Character *character, int vitality);
void modifyCharacterStrength(Character *character, int strength);
void modifyCharacterDefense(Character *character, int defense);
void modifyCharacterArchetype(Character *character, int archetype);
void modifyCharacterColor(Character *character, int r, int g, int b);
void changeCharacterCurrentSprite(Character *character, int index);

Character getMainCharacter();
void printCharacter(Character *character);
void addCharacterSprite(Character *character, const char *spritePath);
void addEnemy(Character newEnemy);
void removeEnemy(int index);
void destroyCharacter(Character *character);

// MOVEMENT HANDLER
int manualMovement(Character *character);
void characterMovement(Character *character);

void characterMovementRandom(Character *character);
void characterMovementBorder(Character *character);
void characterMovementFugitive(Character *character);
void characterMovementFighter(Character *character);
void characterMovementLazy(Character *character);

int getCharacterPositionY(Character *character);
int getCharacterPositionX(Character *character);
int getCharacterSteps(Character *character);

int isCollidingAgainstEnemies(int posx, int posy);
Character* getCollidingEnemy(Character* player, int posx, int posy);

int isCollidingAgainstObstacles(int posx, int posy);
Obstacle* getCollidingObstacle(Character* player, int posx, int posy);
 
#endif
