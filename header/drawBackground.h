// drawBackground.h
#ifndef DRAW_BACKGROUND_H
#define DRAW_BACKGROUND_H

#include <SDL2/SDL.h>
#include "../header/game.h"

// Déclaration des fonctions
void initBackground(SDL_Rect *backgroundRect);
void initBackgroundSize(SDL_Rect *backgroundRect, int width, int height);
void initBackgroundPosition(SDL_Rect *backgroundRect, int posx, int posy);
void fillBackgroundTextures(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *backgroundTextures[20][30]);
void drawBackground(SDL_Renderer *renderer, SDL_Texture *backgroundTextures[20][30]);
void loadBackgroundTextures(SDL_Renderer *renderer, SDL_Texture *backgroundTextures[20][30]);

#endif // DRAW_BACKGROUND_H
