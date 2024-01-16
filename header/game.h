// game.h
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../header/character.h"
#include "../header/drawBackground.h"  // Assurez-vous d'inclure le fichier d'en-tête pour drawBackground
#include "../header/fightDraw.h"

// Constantes pour la taille de la fenêtre
#define WINDOW_WIDTH 960  // Remplacez par la largeur souhaitée
#define WINDOW_HEIGHT 640 // Remplacez par la hauteur souhaitée
#define TILE_SIZE 32

// Constantes pour la grille du fond d'écran
#define GRID_ROWS (WINDOW_HEIGHT / TILE_SIZE)
#define GRID_COLS (WINDOW_WIDTH / TILE_SIZE)

// Déclaration des variables globales
extern Character character;
extern Character enemyFighted;
extern SDL_Texture *backgroundTexture;
extern SDL_Rect backgroundRect;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int isGameRunning;
extern int isInFight;

// Fonctions
void mainLoop();
void loadTextures();
void initGame();
void handleEvents();
void handleFightClick(int mouseX, int mouseY);
void handleMovement();
void spawnEnemy();
void renderEnemy(SDL_Renderer *renderer);

void initSDL();
void drawGame();
void drawBackground();
void loadTextures();

void freeResources();

#endif // GAME_H
