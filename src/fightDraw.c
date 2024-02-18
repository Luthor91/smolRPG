// fightDraw.c
#include "../header/fightDraw.h"
#include "../header/drawBackground.h"
#include "../header/fight.h"
#include "../header/game.h"
#include "../header/character.h"

void drawFightInterface(SDL_Renderer *renderer, Character *character, Character *enemy) {
    while (isInFight == 1) {
        printf("\nCréation interface combat");
        SDL_RenderClear(renderer);
        
        // Charger la texture du background
        SDL_Texture *backgroundTexture = IMG_LoadTexture(renderer, "assets/interfaces/game.png");
        SDL_Texture *characterBacksideTexture = IMG_LoadTexture(renderer, "assets/characters/main_character/character_backside.png");
        SDL_Texture *enemyBacksideTexture = IMG_LoadTexture(renderer, "assets/enemies/enemy_base_backside.png");
        if (!backgroundTexture) {
            fprintf(stderr, "Erreur lors du chargement de la texture du background : %s\n", IMG_GetError());
        }

        if (!characterBacksideTexture) {
            fprintf(stderr, "Erreur lors du chargement de la texture du player : %s\n", IMG_GetError());
        }

        if (!enemyBacksideTexture) {
            fprintf(stderr, "Erreur lors du chargement de la texture du enemy : %s\n", IMG_GetError());
        }

        // Définir la destination du background sur toute la fenêtre
        SDL_Rect destBackground = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_Rect destCharacter = {150, 420, 150, 150};
        SDL_Rect destEnemy = {713, 100, 150, 150};
    


        // Afficher le background
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &destBackground);
        SDL_RenderCopy(renderer, characterBacksideTexture, NULL, &destCharacter);
        SDL_RenderCopy(renderer, enemyBacksideTexture, NULL, &destEnemy);
        // Libérer la texture du background
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyTexture(characterBacksideTexture);
        SDL_DestroyTexture(enemyBacksideTexture);
        
        // Code pour organiser et dessiner le reste de l'interface de combat
        // ...

        startCombat(character, enemy);

        SDL_RenderPresent(renderer);  // Mettre à jour l'écran une seule fois à la fin de chaque itération

    }

}



void createBackgroundTexture(SDL_Renderer *renderer, SDL_Texture **backgroundTexture) {



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