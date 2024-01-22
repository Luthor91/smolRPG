// fightEvent.c
#include "fightEvent.h"
#include "fight.h"

void handleFightClick(int mouseX, int mouseY, Character *character, Character *enemy) {
    // Supposons que les coordonnées du bouton d'attaque soient entre x=100 et x=200 et y=300 et y=350
    if (mouseX >= 100 && mouseX <= 200 && mouseY >= 300 && mouseY <= 350) {
        printf("cliqué");
        // L'utilisateur a cliqué sur le bouton d'attaque
        // Vous pouvez appeler la fonction de combat ici
        startCombat(character, enemy); // Assurez-vous d'avoir un ennemi défini
    }
}
