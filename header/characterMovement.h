#ifndef CHARACTERMOVEMENT_H
#define CHARACTERMOVEMENT_H

#include "../header/character.h"
#include "../header/game.h"
#include "../header/functions.h"

extern Character enemyFighted;

void characterMovementRandom(Character *character);
void characterMovementBorder(Character *character);
void characterMovementFugitive(Character *character);
void characterMovementFighter(Character *character);
void characterMovementLazy(Character *character);
void characterMovement(Character *character);

int manualMovement(Character *character);

#endif