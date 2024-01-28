// game.c
#include "../header/fightDraw.h"
#include "../header/obstacle.h"
#include "../header/game.h"
#include "../header/drawBackground.h"
#include "../header/characterMovement.h"

Character enemies[MAX_ENEMIES];
Character enemyFighted;
Character *mainCharacter;

Obstacle obstacles[MAX_OBSTACLES];

SDL_Texture *backgroundTexture;
SDL_Rect backgroundRect;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture* backgroundTextures[GRID_ROWS][GRID_COLS];  // Déclarez ici

int numEnemies = 0;
int numObstacles = 0;
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
    for (i = 0; i <= 3; i++) {
        char spritePath[50];
        Character *enemy = initCharacter("assets/ennemies/enemy_base.png", renderer, 0);
        addEnemy(*enemy);
        initCharacterPosition(&enemies[i], 32+i*2*64, 32+i*2*64);
        initCharacterSize(&enemies[i], 32+i*32, 32+i*32);
        initCharacterStep(&enemies[i]);
        modifyCharacterColor(&enemies[i], 255 - (1+10*i), 255 - (1+20*i), 255 - (1+40*i));
    }
    numEnemies = i;
}

void spawnObstacle() {
    size_t i = 0;
    for (i = 0; i <= 3; i++) {
        char spritePath[50];
        Obstacle *obstacle = initObstacle("assets/obstacles/obstacle_base.png", renderer, 0);
        addObstacle(*obstacle);
        initObstaclePosition(&obstacles[i], (32*8) + 128 * i, 128 * i);
        initObstacleSize(&obstacles[i], 32, 32);
        modifyObstacleColor(&obstacles[i], 0, 0, 0);
        printObstacle(&obstacles[i]);
    }
    numObstacles = i;
}

void spawnPlayer() {
    mainCharacter = initCharacter("assets/characters/main_character/default_idle_1.png", renderer, -1);
    initCharacterPosition(mainCharacter, 0, 0);
    initCharacterSize(mainCharacter, 32, 32);
    printCharacter(mainCharacter);
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

    spawnPlayer();
    spawnObstacle(); 
    spawnEnemy();
    drawGame();

}

void handleMovements() {
    int isMoved = manualMovement(mainCharacter);
    if (isMoved == 1) { 
        for (int i = 0; i < numEnemies; i++) {
            characterMovementManager(&enemies[i]);
        }
        drawGame();
    }
}

void handleEnemyCollision() {
    
    if (isCollidingAgainstEnemies(mainCharacter->x, mainCharacter->y) == 1) {
        enemyFighted = *getCollidingEnemy(mainCharacter, mainCharacter->x, mainCharacter->y);
        isInFight = 1;
    } 
}

void mainLoop() {
  
    while (isGameRunning == 1) {
        if (isInFight == 1) {
            
            //handleEvents();
            //drawFightInterface(renderer, mainCharacter, &enemyFighted);
            isInFight = 0;
        } else {
            //handleEvents();
            handleMovements();
            handleEnemyCollision();
            SDL_Delay(1);
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

void renderObstacle(SDL_Renderer *renderer) {
    for (int i = 0; i < numObstacles; i++) {
        SDL_Rect obstacleRect = {
            .x = obstacles[i].x,
            .y = obstacles[i].y,
            .w = obstacles[i].width,
            .h = obstacles[i].height
        };
        SDL_RenderCopy(renderer, obstacles[i].obstacleTexture[obstacles[i].currentSpriteIndex], NULL, &obstacleRect);
    }
}

void drawGame() {

    SDL_RenderClear(renderer);  // Effacez le rendu au début de chaque itération

    drawBackground(renderer, backgroundTextures);

    SDL_Rect characterRect = {mainCharacter->x, mainCharacter->y, mainCharacter->width, mainCharacter->height};
    SDL_RenderCopy(renderer, mainCharacter->characterTexture[mainCharacter->currentSpriteIndex], NULL, &characterRect);

    renderEnemy(renderer);
    renderObstacle(renderer);

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