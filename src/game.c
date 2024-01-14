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

void drawFPS(float fps, SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Color textColor = {255, 0, 0}; // Couleur du texte (rouge ici)
    char fpsText[20]; // Chaîne pour stocker le texte des FPS

    // Formatez le texte des FPS
    snprintf(fpsText, sizeof(fpsText), "FPS: %.2f", fps);

    // Utilisez votre fonction de rendu de texte pour afficher le texte à l'écran
    renderText(fpsText, WINDOW_WIDTH - 100, 10, renderer, font, textColor);
}

void renderText(const char *text, int x, int y, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    
    surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        fprintf(stderr, "Erreur lors de la création de la surface du texte : %s\n", TTF_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Erreur lors de la création de la texture du texte : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dstRect = {x, y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void mainLoop() {
    while (1) {
        Uint32 startTime = SDL_GetTicks(); // Enregistrez le temps de début de la boucle

        handleEvents();

        SDL_RenderClear(renderer);  // Effacez le rendu au début de chaque itération

        drawBackground(renderer, backgroundTextures);
        draw();  // Assurez-vous de dessiner le personnage à chaque itération

        SDL_RenderPresent(renderer);  // Mettez à jour l'écran une seule fois à la fin de chaque itération

        Uint32 endTime = SDL_GetTicks(); // Enregistrez le temps de fin de la boucle
        float frameTime = endTime - startTime;
        float framesPerSecond = 0.0;

        if (frameTime > 0) { 
            framesPerSecond = 1000.0f / frameTime; 
        } else { 
            framesPerSecond = 0.0f; 
        }

        SDL_Delay(16); // Ajoute une légère pause pour contrôler la vitesse du jeu
    }
}


void draw() {
    // Dessiner le sol
    drawBackground(renderer, backgroundTextures);

    // Dessiner le personnage
    SDL_Rect characterRect = {character.x, character.y, character.width, character.height};
    SDL_RenderCopy(renderer, character.characterTexture[character.currentSpriteIndex], NULL, &characterRect);
    
    // Retirez l'appel à SDL_RenderPresent ici
}



void handleEvents() {
    characterMovement(&character);
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


