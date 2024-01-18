// fight.c
#include <stdio.h>

#include "character.h"
#include "spell.h"
#include "fight.h"

void startCombat(Character *character, Character *enemy) {

    modifyCharacterVitality(character, character->vitality - 1);
    modifyCharacterVitality(enemy, enemy->vitality - 10);

    if (enemy->vitality <= 0) { 
        
        removeEnemy(enemy->index);
        isInFight = 0;
    } else if (character->vitality <= 0)  { 
        destroyCharacter(character);  
        isInFight = 0;
    }    
}