// spell.c
#include "spell.h"
#include "character.h"

void fireballSpell(Character *character, Character *enemy) {
    printf("Le personnage lance une boule de feu sur l'ennemi !\n");

    // Effets du sort
    enemy->vitality -= 15;  // Réduit la vitalité de l'ennemi
}

void iceShieldSpell(Character *character, Character *enemy) {
    printf("Le personnage crée un bouclier de glace !\n");

    // Effets du sort
    character->defense += 5;  // Augmente la défense du personnage
}

void healSpell(Character *character, Character *enemy) {
    printf("Le personnage se soigne !\n");

    // Effets du sort
    character->vitality += 20;  // Augmente la vitalité du personnage
}

void poisonCloudSpell(Character *character, Character *enemy) {
    printf("Le personnage crée un nuage empoisonné autour de l'ennemi !\n");

    // Effets du sort
    enemy->vitality -= 10;  // Réduit la vitalité de l'ennemi
    character->vitality -= 5;  // Inflige des dégâts collatéraux au personnage
}

void strengthBuffSpell(Character *character, Character *enemy) {
    printf("Le personnage renforce sa force !\n");

    // Effets du sort
    character->strength += 5;  // Augmente la force du personnage
}

void confusionSpell(Character *character, Character *enemy) {
    printf("Le personnage lance un sort de confusion sur l'ennemi !\n");

    // Effets du sort
    enemy->strength -= 3;  // Réduit la force de l'ennemi
    enemy->defense -= 3;   // Réduit la défense de l'ennemi
}
