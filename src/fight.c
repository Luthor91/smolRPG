// fight.c
#include <stdio.h>

#include "character.h"
#include "game.h"
#include "spell.h"
#include "fight.h"

void startCombat(Character *character, Character *enemy) {

    modifyCharacterVitality(character, -1);
    modifyCharacterVitality(enemy, -10);

    if (enemy->vitality <= 0) {
        printf("\nCombat gagné");
        reIndexEnemies();
        isInFight = 0;
        return;
    } else if (character->vitality <= 0)  { 
        printf("\nCombat perdu");
        destroyCharacter(character);  
        isInFight = 0;
        return;
    } else {
        return;
    }
}