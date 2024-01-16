// fightDraw.h
#ifndef FIGHT_DRAW_H
#define FIGHT_DRAW_H

#include <SDL2/SDL.h>
#include "../header/character.h"

// Déclaration des fonctions
void drawFightInterface(SDL_Renderer *renderer, Character *character, Character *enemy);
void createHealthBarTexture(SDL_Renderer *renderer, SDL_Texture **healthBarTexture);
void createAttackButtonTexture(SDL_Renderer *renderer, SDL_Texture **attackButtonTexture);
// Ajoutez d'autres fonctions pour créer des textures supplémentaires

#endif // DRAW_FIGHT_H
