// drawFight.c
#include <SDL2/SDL_image.h>
#include "../header/drawFight.h"

void initFightSize(SDL_Rect *fightRect, int width, int height) {
    fightRect->w = width;
    fightRect->h = height;
}

void initFightPosition(SDL_Rect *fightRect, int posx, int posy) {
    fightRect->x = posx;
    fightRect->y = posy;
}

void initFight(SDL_Rect *fightRect) {
    initFightSize(fightRect, WINDOW_WIDTH, WINDOW_HEIGHT);
    initFightPosition(fightRect, 0, 0);
}

void fillFightTextures(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *fightTextures[GRID_ROWS][GRID_COLS]) {
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            fightTextures[i][j] = texture;
        }
    }
}

void drawFight(SDL_Renderer *renderer, SDL_Texture *fightTextures[GRID_ROWS][GRID_COLS]) {
    SDL_RenderClear(renderer);

    // Dessiner chaque image de la grille
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            SDL_Rect destRect = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderCopy(renderer, fightTextures[i][j], NULL, &destRect);
        }
    }

    SDL_RenderPresent(renderer);
}

// Charger les textures du fond d'écran
void loadFightTextures(SDL_Renderer *renderer, SDL_Texture *fightTextures[GRID_ROWS][GRID_COLS]) {
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            char filePath[100];  // Ajustez la taille selon vos besoins
            sprintf(filePath, "assets/materials/fight/grass_%d.png", (i * GRID_COLS) + j + 1);
            fightTextures[i][j] = IMG_LoadTexture(renderer, filePath);
            if (!fightTextures[i][j]) {
                // Gérer l'erreur (à adapter selon vos besoins)
                fprintf(stderr, "Erreur lors du chargement de l'image du fond d'écran : %s\n", IMG_GetError());
                exit(EXIT_FAILURE);
            }
        }
    }
}