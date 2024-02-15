// fight.c
#include <stdio.h>

#include "character.h"
#include "spell.h"
#include "fight.h"

void startCombat(Character *character, Character *enemy) {

    
    printf("\nAvant (en) ? %d", enemy->vitality);
    printf("\nAvant (mc) ? %d", character->vitality);
    modifyCharacterVitality(character, -1);
    modifyCharacterVitality(enemy, -10);
    printf("\nApres (en) ? %d", enemy->vitality);
    printf("\nApres (mc) ? %d", character->vitality);


    if (enemy->vitality <= 0) {
        printf("\nCombat gagné");
        removeEnemy(enemy);
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