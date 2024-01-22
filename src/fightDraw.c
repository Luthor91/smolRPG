// fightDraw.c
#include "../header/fightDraw.h"
#include "../header/fight.h"
#include "../header/game.h"
#include "../header/character.h"

void drawFightInterface(SDL_Renderer *renderer, Character *character, Character *enemy) {

    printf("\nCréation interface combat");
    
    SDL_Texture *healthBarTexture = NULL;
    SDL_Texture *attackButtonTexture = NULL;

    createHealthBarTexture(renderer, &healthBarTexture);
    createAttackButtonTexture(renderer, &attackButtonTexture);
    
    // Code pour organiser et dessiner l'interface de combat
    // Utilisez SDL functions pour définir les positions relatives
    // des textures et les dessiner sur le renderer

    startCombat(character, enemy);

    // Assurez-vous de libérer la mémoire des textures à la fin
    SDL_DestroyTexture(healthBarTexture);
    SDL_DestroyTexture(attackButtonTexture);
}


void createHealthBarTexture(SDL_Renderer *renderer, SDL_Texture **healthBarTexture) {
    // Code pour créer la texture de la barre de santé
    // Utilisez SDL functions pour dessiner la barre de santé
    // Assurez-vous de libérer la mémoire appropriée à la fin
}

void createAttackButtonTexture(SDL_Renderer *renderer, SDL_Texture **attackButtonTexture) {
    // Code pour créer la texture du bouton d'attaque
    // Utilisez SDL functions pour dessiner le bouton d'attaque
    // Assurez-vous de libérer la mémoire appropriée à la fin
}