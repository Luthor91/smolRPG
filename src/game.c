// game.c
#include "../header/fightDraw.h"
#include "../header/game.h"
#include "../header/drawBackground.h"

Character enemies[MAX_ENEMIES];
Character enemyFighted;
Character character;
int numEnemies = 0;

SDL_Texture *backgroundTexture;
SDL_Rect backgroundRect;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture* backgroundTextures[GRID_ROWS][GRID_COLS];  // Déclarez ici

int isGameRunning = 1;
int isInFight = 0;

void initSDL() {
    // Assurez-vous de détruire correctement les ressources ici si nécessaire
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void spawnEnemy() {
    Character enemy = initCharacter("assets/ennemies/enemy_blue.png", renderer, 1);
    Character enemy0 = initCharacter("assets/ennemies/enemy_red.png", renderer, 1);// Lazy
    Character enemy1 = initCharacter("assets/ennemies/enemy_white.png", renderer, 2); // Border
    Character enemy2 = initCharacter("assets/ennemies/enemy_pink.png", renderer, 3); // Fugitive
    Character enemy3 = initCharacter("assets/ennemies/enemy_yellow.png", renderer, 4); // Fighter

    initCharacterPosition(&enemy0, 64, 64);
    initCharacterPosition(&enemy1, 128, 128);
    initCharacterPosition(&enemy2, 256, 256);
    initCharacterPosition(&enemy3, 512, 512);

    addEnemy(enemy);
    addEnemy(enemy0);
    addEnemy(enemy1);
    addEnemy(enemy2);
    addEnemy(enemy3);

}

void initGame() {
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

    fillBackgroundTextures(groundTexture, backgroundTextures);
    character = initCharacter("assets/characters/main_character/default_idle_1.png", renderer, 0);
    printf("spawn enemy");
    spawnEnemy();
    drawGame();

}

void handleMovements() {
    int isMoved = manualMovement(&character);
    if (isMoved == 1) { 

        for (int i = 0; i < numEnemies; i++) {
            characterMovement(&enemies[i]);
        }

        drawGame();
    }
}

void mainLoop() {
  
    while (isGameRunning == 1) {
        printf("tst : %d\n", numEnemies);
        if (isInFight == 1) {
            handleEvents();
            drawFightInterface(renderer, &character, &enemyFighted);
        } else {
            //handleEvents();
            handleMovements();
            SDL_Delay(20);
        }
    }
}

void renderEnemy(SDL_Renderer *renderer) {
    for (int i = 0; i < numEnemies; i++) {
        SDL_Rect enemyRect = {
            .x = enemies[i].x,
            .y = enemies[i].y,
            .w = enemies[i].width,
            .h = enemies[i].height
        };

        SDL_RenderCopy(renderer, enemies[i].characterTexture[enemies[i].currentSpriteIndex], NULL, &enemyRect);
    }
}



void drawGame() {

    SDL_RenderClear(renderer);  // Effacez le rendu au début de chaque itération

    drawBackground(renderer, backgroundTextures);

    SDL_Rect characterRect = {character.x, character.y, character.width, character.height};
    SDL_RenderCopy(renderer, character.characterTexture[character.currentSpriteIndex], NULL, &characterRect);

    renderEnemy(renderer);

    SDL_RenderPresent(renderer);  // Mettez à jour l'écran une seule fois à la fin de chaque itération
    
}

void handleClick(int mouseX, int mouseY) {
    // Supposons que les coordonnées du bouton d'attaque soient entre x=100 et x=200 et y=300 et y=350
    if (mouseX >= 100 && mouseX <= 200 && mouseY >= 300 && mouseY <= 350) {
        // L'utilisateur a cliqué sur le bouton d'attaque
        // Vous pouvez appeler la fonction de combat ici
    
    }
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                // Gérer l'événement de fermeture de fenêtre
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Gérer l'événement de clic de souris
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = 0, mouseY = 0;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    printf("x : %d ; y : %d\n", mouseX, mouseY);
                    handleClick(mouseX, mouseY); // gérer la localisation du clic

                }
                break;
            // ... autres cas d'événements ...
        }
    }
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

