// main.c
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../header/game.h"

// Fonction à appeler lors de la réception du signal SIGINT
void handleSignal(int sig) {
    if (sig == SIGINT) {
        // Libérer les ressources et quitter le programme proprement
        freeResources();
        exit(0);
    }
}

int main() {
    srand((unsigned int)time(NULL));
    initSDL();
    initGame();

    signal(SIGINT, handleSignal);
    printf("\nDébut du jeu");
    mainLoop();

    freeResources();
    
    return 0;
}