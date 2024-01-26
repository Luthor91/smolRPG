#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define MAX_SPRITES 10
#define OBSTACLE_HEIGHT 32
#define OBSTACLE_WIDTH 32

#define MAX_OBSTACLES 50

typedef struct {
    SDL_Renderer *renderer;
    SDL_Texture *obstacleTexture[MAX_SPRITES];
    const char *spritePaths[MAX_SPRITES];
    int currentSpriteIndex;
    int width;
    int height;
    int x;
    int y;
    int index;
    int type;
} Obstacle;

extern Obstacle obstacles[MAX_OBSTACLES];

extern int numObstacles;

void initObstacleTexture(Obstacle *obstacle);
void initObstacleSize(Obstacle *obstacle, int width, int height);
void initObstaclePosition(Obstacle *obstacle, int posx, int posy);
void initObstacleType(Obstacle *obstacle, int type);
void initObstacleColor(Obstacle *obstacle);

Obstacle *initObstacle(const char *filePath, SDL_Renderer *renderer, int type);

void modifyObstacleObstacleSize(Obstacle *obstacle, int width, int height);
void modifyObstacleObstaclePosition(Obstacle *obstacle, int x, int y);
void modifyObstacleType(Obstacle *obstacle, int type);
void modifyObstacleColor(Obstacle *obstacle, int r, int g, int b);
void changeObstacleCurrentSprite(Obstacle *obstacle, int index);

Obstacle getMainObstacle();
void printObstacle(Obstacle *obstacle);
void addObstacleSprite(Obstacle *obstacle, const char *spritePath);
void addObstacle(Obstacle newObstacle);
void removeObject(int index);
void destroyObstacle(Obstacle *obstacle);

int getObstaclePositionY(Obstacle *obstacle);
int getObstaclePositionX(Obstacle *obstacle);

#endif
