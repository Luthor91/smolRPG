// functions.c
#include <stdlib.h>
#include <time.h>

int generateRandomNumber(int max) {
    srand((unsigned int)time(NULL));
    return rand() % max;
}