// game.c
#include "../header/game.h"
#include "../header/drawBackground.h"

Character character;
SDL_Texture *backgroundTexture;
SDL_Rect backgroundRect;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture* backgroundTextures[GRID_ROWS][GRID_COLS];  // Déclarez ici

void initSDL() {
    // Assurez-vous de détruire correctement les ressources ici si nécessaire
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void initGame() {
    // Constantes pour la grille du fond d'écran

    window = SDL_CreateWindow("Mon Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Erreur lors de la création du rendu : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    initBackground(&backgroundRect);  // Appel à la fonction initBackground

    SDL_Texture *groundTexture = IMG_LoadTexture(renderer, "assets/materials/background/grass_1.png");
    if (!groundTexture) {
        fprintf(stderr, "Erreur lors du chargement de la texture du sol : %s\n", IMG_GetError());
    }

    fillBackgroundTextures(renderer, groundTexture, backgroundTextures);

    initCharacter(&character, "assets/characters/main_character/default_idle_1.png", renderer);
}

void mainLoop() {
    while (1) {
        handleEvents();
        draw();
        SDL_Delay(16); // Ajoute une légère pause pour contrôler la vitesse du jeu
    }
}

void draw() {
    // Dessiner le sol
    drawBackground(renderer, backgroundTextures);

    // Dessiner le personnage
    SDL_Rect characterRect = {character.x, character.y, character.width, character.height};
    SDL_RenderCopy(renderer, character.characterTexture[character.currentSpriteIndex], NULL, &characterRect);
    SDL_RenderPresent(renderer);
}

void handleEvents() {
    characterMovement(&character);
}

void freeResources() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = NULL;  // Remettre à NULL après la destruction pour éviter les erreurs éventuelles
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}


