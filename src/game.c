// game.c
#include "../header/game.h"
#include "../header/drawBackground.h"

Character character;
Character enemy;
Character enemy0;
Character enemy1;
Character enemy2;
Character enemy3;
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

void spawnEnemy() {
    initCharacter(&enemy, "assets/ennemies/enemy_blue.png", renderer, 1);

    // Lazy
    initCharacter(&enemy0, "assets/ennemies/enemy_red.png", renderer, 1);
    initCharacterPosition(&enemy0, 64, 64);

    // Border
    initCharacter(&enemy1, "assets/ennemies/enemy_white.png", renderer, 2);
    initCharacterPosition(&enemy1, 128, 128);

    // Fugitive
    initCharacter(&enemy2, "assets/ennemies/enemy_pink.png", renderer, 3);
    initCharacterPosition(&enemy2, 256, 256);

    // Fighter
    initCharacter(&enemy3, "assets/ennemies/enemy_yellow.png", renderer, 4);
    initCharacterPosition(&enemy3, 512, 512);

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

    SDL_Texture *groundTexture = IMG_LoadTexture(renderer, "assets/materials/background/grass_1.png");
    if (!groundTexture) {
        fprintf(stderr, "Erreur lors du chargement de la texture du sol : %s\n", IMG_GetError());
    }

    initBackground(&backgroundRect);

    fillBackgroundTextures(renderer, groundTexture, backgroundTextures);

    initCharacter(&character, "assets/characters/main_character/default_idle_1.png", renderer, 0);
    spawnEnemy();
    drawGame();

}

void handleMovements() {
    int isMoved = manualMovement(&character);
    if (isMoved == 1) { 
        //enemyMovement(&enemy); 
        characterMovement(&enemy0); 
        characterMovement(&enemy1); 
        characterMovement(&enemy2); 
        characterMovement(&enemy3); 
        drawGame();
    }
}

void mainLoop() {
    while (1) {

        handleEvents();
        handleMovements();

        SDL_Delay(20);

    }
}

void renderEnemy(SDL_Renderer *renderer) {
    SDL_Rect enemyRect;

    // Render enemy
    enemyRect = (SDL_Rect){enemy.x, enemy.y, enemy.width, enemy.height};
    SDL_RenderCopy(renderer, enemy.characterTexture[enemy.currentSpriteIndex], NULL, &enemyRect);

    // Render enemy0
    enemyRect = (SDL_Rect){enemy0.x, enemy0.y, enemy0.width, enemy0.height};
    SDL_RenderCopy(renderer, enemy0.characterTexture[enemy0.currentSpriteIndex], NULL, &enemyRect);

    // Render enemy1
    enemyRect = (SDL_Rect){enemy1.x, enemy1.y, enemy1.width, enemy1.height};
    SDL_RenderCopy(renderer, enemy1.characterTexture[enemy1.currentSpriteIndex], NULL, &enemyRect);

    // Render enemy2
    enemyRect = (SDL_Rect){enemy2.x, enemy2.y, enemy2.width, enemy2.height};
    SDL_RenderCopy(renderer, enemy2.characterTexture[enemy2.currentSpriteIndex], NULL, &enemyRect);

    // Render enemy3
    enemyRect = (SDL_Rect){enemy3.x, enemy3.y, enemy3.width, enemy3.height};
    SDL_RenderCopy(renderer, enemy3.characterTexture[enemy3.currentSpriteIndex], NULL, &enemyRect);
}


void drawGame() {

    SDL_RenderClear(renderer);  // Effacez le rendu au début de chaque itération

    drawBackground(renderer, backgroundTextures);

    SDL_Rect characterRect = {character.x, character.y, character.width, character.height};
    SDL_RenderCopy(renderer, character.characterTexture[character.currentSpriteIndex], NULL, &characterRect);

    renderEnemy(renderer);

    SDL_RenderPresent(renderer);  // Mettez à jour l'écran une seule fois à la fin de chaque itération
    
}

void handleEvents() {
    //
}

void freeResources() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = NULL;
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

