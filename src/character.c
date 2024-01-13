#include "../header/character.h"
#include "../header/game.h"

// character.c
void initCharacter(Character *character, const char *filePath, SDL_Renderer *renderer) {
    // Utilisez la structure Character pour initialiser les membres
    character->vitality = 100;
    character->strength = 10;
    character->defense = 5;
    character->x = 0;
    character->y = 0;
    character->width = 32;
    character->height = 32;
    character->renderer = renderer;  // Enregistrer le renderer

    for (int i = 0; i < MAX_SPRITES; i++) {
        character->spritePaths[i] = NULL; // Initialiser toutes les entrées à NULL
    }

    if (filePath && filePath[0] != '\0') {
        addSprite(character, filePath);
    } else {
        // Chemin par défaut si filePath est vide
        addSprite(character, "assets/characters/main_character/default_idle_1.png");
    }

    initCharacterTexture(character);
}

void modifyCharacterSize(Character *character, int width, int height) {
    character->width = width;
    character->height = height;
}

void modifyCharacterPosition(Character *character, int x, int y) {
    character->x = x;
    character->y = y;
}

void initCharacterTexture(Character *character) {
    if (!character->renderer) {
        fprintf(stderr, "Erreur : le rendu n'est pas initialisé pour le personnage.\n");
        exit(EXIT_FAILURE);
    }

    const char *spritePath = character->spritePaths[character->currentSpriteIndex];
    
    if (!spritePath) {
        fprintf(stderr, "Erreur : le chemin du sprite est NULL.\n");
        exit(EXIT_FAILURE);
    }

    SDL_Surface *personnageSurface = IMG_Load(spritePath);
    if (!personnageSurface) {
        fprintf(stderr, "Erreur lors du chargement de l'image du personnage : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    character->characterTexture[character->currentSpriteIndex] = SDL_CreateTextureFromSurface(character->renderer, personnageSurface);
    printf("Ajout de sprite : Chemin = %s\n", spritePath);

    SDL_FreeSurface(personnageSurface);

    if (!character->characterTexture[character->currentSpriteIndex]) {
        fprintf(stderr, "Erreur lors de la création de la texture du personnage : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}


// Ajouter un sprite au tableau de chemins de fichiers
void addSprite(Character *character, const char *spritePath) {
    int index = character->currentSpriteIndex;
    
    if (index < MAX_SPRITES) {
        character->spritePaths[index] = spritePath;
    } else {
        // Gérer l'erreur si le tableau est plein (à adapter selon vos besoins)
        fprintf(stderr, "Impossible d'ajouter plus de sprites. Tableau plein.\n");
    }
}




// Changer le sprite actuel en utilisant l'indice fourni
void changeCurrentSprite(Character *character, int index) {
    if (index >= 0 && index < MAX_SPRITES) {
        character->currentSpriteIndex = index;
    } else {
        // Gérer l'erreur si l'indice est invalide (à adapter selon vos besoins)
        fprintf(stderr, "Indice de sprite invalide.\n");
    }
}

// Modifier les statistiques du personnage
void modifyVitality(Character *character, int vitality) {
    character->vitality = vitality;
}

// Modifier les statistiques du personnage
void modifyStrength(Character *character, int strength) {
    character->strength = strength;
}

// Modifier les statistiques du personnage
void modifyDefense(Character *character, int defense) {
    character->defense = defense;
}

void characterMovement(Character *character) {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    if (character->x < TILE_SIZE) break;
                    character->x -= TILE_SIZE;
                    break;
                case SDLK_RIGHT:
                    if (character->x + TILE_SIZE >= WINDOW_WIDTH) break;
                    character->x += TILE_SIZE;
                    break;
                case SDLK_UP:
                    if (character->y < TILE_SIZE) break;
                    character->y -= TILE_SIZE;
                    break;
                case SDLK_DOWN:
                    if (character->y + TILE_SIZE >= WINDOW_HEIGHT) break;
                    character->y += TILE_SIZE;
                    break;
            }
        }
    }
}

void destroyCharacter(Character *character) {
    SDL_DestroyTexture(character->characterTexture[character->currentSpriteIndex]);
}



void printStats(Character *character) {
    /* */
}


// Autres fonctions liées au personnage peuvent être ajoutées ici
