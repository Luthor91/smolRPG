// main.c
#include <signal.h>
#include <stdlib.h>

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
    initSDL();
    initGame();

    signal(SIGINT, handleSignal);

    mainLoop();

    freeResources();
    
    return 0;
}