#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Constantes pour la taille de la fenêtre
const int MAX_WIDTH = 800;
const int MAX_HEIGHT = 600;

// Déclaration des variables globales
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *solTexture, *personnageTexture;
SDL_Rect solRect, personnageRect;

// Initialisation de SDL
void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
}

// Chargement des textures
void chargerTextures() {
    solTexture = IMG_LoadTexture(renderer, "assets/materials/background/grass_1.png");
    personnageTexture = IMG_LoadTexture(renderer, "assets/characters/main_character/character_idle_1.png");
}

// Initialisation du jeu
void initJeu() {
    window = SDL_CreateWindow("Mon Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAX_WIDTH, MAX_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    solRect.x = 0;
    solRect.y = 0;
    solRect.w = MAX_WIDTH;
    solRect.h = MAX_HEIGHT;

    personnageRect.x = 50;
    personnageRect.y = 350;
    personnageRect.w = 50;
    personnageRect.h = 50;
}

// Gestion des entrées et mise à jour du jeu
void gestionEvenements() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    personnageRect.x -= 5;
                    break;
                case SDLK_RIGHT:
                    personnageRect.x += 5;
                    break;
                case SDLK_UP:
                    personnageRect.y -= 5;
                    break;
                case SDLK_DOWN:
                    personnageRect.y += 5;
                    break;
            }
        }
    }
}

// Affichage des textures
void afficherTextures() {
    SDL_RenderClear(renderer);

    // Dessiner le sol
    SDL_RenderCopy(renderer, solTexture, NULL, &solRect);

    // Dessiner le personnage
    SDL_RenderCopy(renderer, personnageTexture, NULL, &personnageRect);

    SDL_RenderPresent(renderer);
}

// Libération des ressources à la fin du programme
void libererRessources() {
    SDL_DestroyTexture(solTexture);
    SDL_DestroyTexture(personnageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main() {
    initSDL();
    initJeu();
    chargerTextures();

    while (1) {
        gestionEvenements();
        afficherTextures();
        SDL_Delay(16); // Ajoute une légère pause pour contrôler la vitesse du jeu
    }

    libererRessources();
    return 0;
}
