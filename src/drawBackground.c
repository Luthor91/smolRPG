// drawBackground.c
#include <SDL2/SDL_image.h>
#include "../header/game.h"
#include "../header/drawBackground.h"

void initBackgroundSize(SDL_Rect *backgroundRect, int width, int height) {
    backgroundRect->w = width;
    backgroundRect->h = height;
}

void initBackgroundPosition(SDL_Rect *backgroundRect, int posx, int posy) {
    backgroundRect->x = posx;
    backgroundRect->y = posy;
}

void initBackground(SDL_Rect *backgroundRect) {
    initBackgroundSize(backgroundRect, WINDOW_WIDTH, WINDOW_HEIGHT);
    initBackgroundPosition(backgroundRect, 0, 0);
}

void fillBackgroundTextures(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *backgroundTextures[GRID_ROWS][GRID_COLS]) {
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            backgroundTextures[i][j] = texture;
        }
    }
}

void drawBackground(SDL_Renderer *renderer, SDL_Texture *backgroundTextures[GRID_ROWS][GRID_COLS]) {
    SDL_RenderClear(renderer);

    // Dessiner chaque image de la grille
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            SDL_Rect destRect = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderCopy(renderer, backgroundTextures[i][j], NULL, &destRect);
        }
    }

    SDL_RenderPresent(renderer);
}

// Charger les textures du fond d'écran
void loadBackgroundTextures(SDL_Renderer *renderer, SDL_Texture *backgroundTextures[GRID_ROWS][GRID_COLS]) {
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            char filePath[100];  // Ajustez la taille selon vos besoins
            sprintf(filePath, "assets/materials/background/grass_%d.png", (i * GRID_COLS) + j + 1);
            backgroundTextures[i][j] = IMG_LoadTexture(renderer, filePath);
            if (!backgroundTextures[i][j]) {
                // Gérer l'erreur (à adapter selon vos besoins)
                fprintf(stderr, "Erreur lors du chargement de l'image du fond d'écran : %s\n", IMG_GetError());
                exit(EXIT_FAILURE);
            }
        }
    }
}