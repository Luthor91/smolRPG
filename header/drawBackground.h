// drawBackground.h
#ifndef DRAW_BACKGROUND_H
#define DRAW_BACKGROUND_H

#include <SDL2/SDL.h>
#include "../header/game.h"

// Déclaration des fonctions
void initBackground(SDL_Rect *backgroundRect);
void fillBackgroundTextures(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *backgroundTextures[10][15]);
void drawBackground(SDL_Renderer *renderer, SDL_Texture *backgroundTextures[10][15]);
void loadBackgroundTextures(SDL_Renderer *renderer, SDL_Texture *backgroundTextures[10][15]);

#endif // DRAW_BACKGROUND_H
