// obstacle.c
#include "../header/obstacle.h"
#include "../header/game.h"
#include <stdio.h>

void initObstacleTexture(Obstacle *obstacle) {
    if (!obstacle->renderer) {
        fprintf(stderr, "Erreur : le rendu n'est pas initialisé pour le obstacle.\n");
        exit(EXIT_FAILURE);
    }

    const char *spritePath = obstacle->spritePaths[obstacle->currentSpriteIndex];
    
    if (!spritePath) {
        fprintf(stderr, "Erreur : le chemin du sprite est NULL.\n");
        exit(EXIT_FAILURE);
    }

    SDL_Surface *obstacleSurface = IMG_Load(spritePath);
    if (!obstacleSurface) {
        fprintf(stderr, "Erreur lors du chargement de l'image du obstacle : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    obstacle->obstacleTexture[obstacle->currentSpriteIndex] = SDL_CreateTextureFromSurface(obstacle->renderer, obstacleSurface);

    SDL_FreeSurface(obstacleSurface);

    if (!obstacle->obstacleTexture[obstacle->currentSpriteIndex]) {
        fprintf(stderr, "Erreur lors de la création de la texture du obstacle : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void initObstacleSize(Obstacle *obstacle, int width, int height) {
    obstacle->width = width;
    obstacle->height = height;
}

void initObstaclePosition(Obstacle *obstacle, int posx, int posy) {
    obstacle->x = posx;
    obstacle->y = posy;
}

void initObstacleType(Obstacle *obstacle, int type) {
    obstacle->type = type;
}

void initObstacleColor(Obstacle *obstacle) {
    SDL_SetTextureColorMod(obstacle->obstacleTexture[obstacle->currentSpriteIndex], 0, 0, 0);
}

void modifyObstacleColor(Obstacle *obstacle, int r, int g, int b) {
    SDL_SetTextureColorMod(obstacle->obstacleTexture[obstacle->currentSpriteIndex], r, g, b);
}

Obstacle *initObstacle(const char *filePath, SDL_Renderer *renderer, int type) {
    
    Obstacle *obstacle = (Obstacle*)calloc(1, sizeof(Obstacle));

    if (obstacle == NULL) {
        fprintf(stderr, "Erreur : échec de l'allocation de mémoire pour Obstacle.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_SPRITES; i++) {
        obstacle->spritePaths[i] = NULL;
    }

    if (filePath && filePath[0] != '\0') { addObstacleSprite(obstacle, filePath); } 
    else { addObstacleSprite(obstacle, "assets/obstacles/obstacle_base.png"); }

    obstacle->renderer = renderer;

    initObstaclePosition(obstacle, 0, 0);
    initObstacleSize(obstacle, 32, 32);
    initObstacleType(obstacle, type);
    initObstacleTexture(obstacle);

    return obstacle;
}

void modifyObstacleSize(Obstacle *obstacle, int width, int height) {
    obstacle->width = width;
    obstacle->height = height;
}

void modifyObstaclePosition(Obstacle *obstacle, int x, int y) {
    obstacle->x = x;
    obstacle->y = y;
}

void modifyObstacleType(Obstacle *obstacle, int type) {
    obstacle->type = type;
}

int getObstaclePositionX(Obstacle *obstacle) {
    return obstacle->x;
}

int getObstaclePositionY(Obstacle *obstacle) {
    return obstacle->y;
}

// Ajouter un sprite au tableau de chemins de fichiers
void addObstacleSprite(Obstacle *obstacle, const char *spritePath) {
    int index = obstacle->currentSpriteIndex;

    if (index < MAX_SPRITES)    { obstacle->spritePaths[index] = spritePath; } 
    else                        { fprintf(stderr, "Impossible d'ajouter plus de sprites. Tableau plein.\n"); }
}

// Changer le sprite actuel en utilisant l'indice fourni
void changeObstacleCurrentSprite(Obstacle *obstacle, int index) {
    if (index >= 0 && index < MAX_SPRITES)  { obstacle->currentSpriteIndex = index; } 
    else                                    { fprintf(stderr, "Indice de sprite invalide.\n"); }
}

// Ajoutez un ennemi à la liste
void addObstacle(Obstacle newObstacle) {
    if (numObstacles < MAX_OBSTACLES) {
        newObstacle.index = numObstacles;
        obstacles[numObstacles] = newObstacle;
        numObstacles++;
    } else {
        fprintf(stderr, "Impossible d'ajouter plus d'obstacle. Tableau plein.\n");
    }
}

// Retirez un ennemi de la liste en fonction de l'indice
void removeObstacle(int index) {
    if (index >= 0 && index < numObstacles) {
        
        destroyObstacle(&obstacles[index]);
        printf("Memory freed for obstacle at index %d\n", index);

        // Déplacez les éléments suivants d'un indice vers le haut pour remplir l'emplacement supprimé
        for (int i = index; i < numObstacles - 1; i++) {
            obstacles[i] = obstacles[i + 1];
        }
        numObstacles--;
    } else {
        fprintf(stderr, "Indice d'obstacle invalide.\n");
    }
}

void printObstacle(Obstacle *obstacle) {
    printf("\nw: %d, h: %d\nx: %d, y: %d\n",  
        obstacle->width, obstacle->height,
        obstacle->x, obstacle->y
    );
}

void destroyObstacle(Obstacle *obstacle) {
    for (size_t i = 0; i < MAX_SPRITES; i++) {
        SDL_DestroyTexture(obstacle->obstacleTexture[i]);
    }
    free(obstacle);
}
