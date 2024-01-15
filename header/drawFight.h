// drawFight.h
#ifndef DRAW_BACKGROUND_H
#define DRAW_BACKGROUND_H

#include <SDL2/SDL.h>
#include "../header/game.h"

// Déclaration des fonctions
void initFight(SDL_Rect *backgroundRect);
void initFightSize(SDL_Rect *backgroundRect, int width, int height);
void initFightPosition(SDL_Rect *backgroundRect, int posx, int posy);
void fillFightTextures(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *backgroundTextures[20][30]);
void drawFight(SDL_Renderer *renderer, SDL_Texture *backgroundTextures[20][30]);
void loadFightTextures(SDL_Renderer *renderer, SDL_Texture *backgroundTextures[20][30]);

#endif // DRAW_BACKGROUND_H
