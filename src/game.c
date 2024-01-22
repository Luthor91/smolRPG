// game.c
#include "../header/fightDraw.h"
#include "../header/game.h"
#include "../header/drawBackground.h"

Character enemies[MAX_ENEMIES];
Character enemyFighted;
Character *mainCharacter;

SDL_Texture *backgroundTexture;
SDL_Rect backgroundRect;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture* backgroundTextures[GRID_ROWS][GRID_COLS];  // Déclarez ici

int numEnemies = 0;
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

    size_t i = 0;
    for (i = 0; i <= 4; i++) {
        char spritePath[50];
        snprintf(spritePath, sizeof(spritePath), "assets/ennemies/enemy_%d.png", i);
        Character *enemy = initCharacter(spritePath, renderer, i);

        addEnemy(*enemy);
        initCharacterPosition(&enemies[i], i*2*32, i*2*32);
        initCharacterSize(&enemies[i], i*16, i*16);
    }
    numEnemies = i;
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
    mainCharacter = initCharacter("assets/characters/main_character/default_idle_1.png", renderer, -1);
    initCharacterPosition(mainCharacter, 512, 512);
    spawnEnemy();
    drawGame();

}

void handleMovements() {
    int isMoved = manualMovement(mainCharacter);
    if (isMoved == 1) { 
        for (int i = 0; i < numEnemies; i++) {
            characterMovement(&enemies[i]);
        }
        drawGame();
    }
}

void handleEnemyCollision() {
    
    if (isCollidingAgainstEnemies(mainCharacter->x, mainCharacter->y) == 1) {
        printf("\nPlayer collision avec Ennemi");
        enemyFighted = *getCollidingEnemy(mainCharacter, mainCharacter->x, mainCharacter->y);
        isInFight = 1;
    } 
}

void mainLoop() {
  
    while (isGameRunning == 1) {
        if (isInFight == 1) {
            
            handleEvents();
            drawFightInterface(renderer, mainCharacter, &enemyFighted);

        } else {
            //handleEvents();
            handleMovements();
            handleEnemyCollision();
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

    SDL_Rect characterRect = {mainCharacter->x, mainCharacter->y, mainCharacter->width, mainCharacter->height};
    SDL_RenderCopy(renderer, mainCharacter->characterTexture[mainCharacter->currentSpriteIndex], NULL, &characterRect);

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
            default:
                break;
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