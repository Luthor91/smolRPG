// drawBackground.c
#include <SDL2/SDL_image.h>
#include "../header/game.h"
#include "../header/drawBackground.h"

void initBackground(SDL_Rect *backgroundRect) {
    backgroundRect->x = 0;
    backgroundRect->y = 0;
    backgroundRect->w = WINDOW_WIDTH;
    backgroundRect->h = WINDOW_HEIGHT;
}


void fillBackgroundTextures(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *backgroundTextures[GRID_ROWS][GRID_COLS]) {
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            backgroundTextures[i][j] = texture;
            // Assurez-vous que la texture a été correctement créée avant l'appel de cette fonction
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