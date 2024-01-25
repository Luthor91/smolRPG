// fight.c
#include <stdio.h>

#include "character.h"
#include "spell.h"
#include "fight.h"

void startCombat(Character *character, Character *enemy) {

    printf("\nDébut du combat");
    
    modifyCharacterVitality(character, character->vitality - 1);
    modifyCharacterVitality(enemy, enemy->vitality - 10);

    // Affichez les statistiques de l'ennemi après la modification

    // Vérifiez ensuite les conditions de fin de combat
    if (enemy->vitality <= 0) {
        printf("\nEnnemi mort");
        removeEnemy(enemy->index);
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