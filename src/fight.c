#include <stdio.h>

#include "character.h"
#include "fight.h"

void startCombat(Character *character, Character *enemy) {
    printf("Combat entre le personnage et l'ennemi !\n");

    // Ajoutez ici la logique spécifique au combat, par exemple des attaques, des dégâts, etc.

    // Une fois le combat terminé, vous pouvez mettre à jour les statistiques du personnage et de l'ennemi
    // en fonction du résultat du combat.

    // Exemple :
    character->vitality -= 10;  // Réduire la vitalité du personnage
    enemy->vitality -= 5;       // Réduire la vitalité de l'ennemi

    // Affichez le résultat du combat
    printf("Résultat du combat : Personnage - Vitalité: %d, Ennemi - Vitalité: %d\n", character->vitality, enemy->vitality);
}