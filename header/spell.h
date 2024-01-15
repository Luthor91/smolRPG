// spell.h
#ifndef SPELL_H
#define SPELL_H

#include "character.h"

// Fonction de sort : Boule de feu
void fireballSpell(Character *character, Character *enemy);

// Fonction de sort : Bouclier de glace
void iceShieldSpell(Character *character, Character *enemy);

// Fonction de sort : Soin
void healSpell(Character *character, Character *enemy);

// Fonction de sort : Nuage empoisonné
void poisonCloudSpell(Character *character, Character *enemy);

// Fonction de sort : Buff de force
void strengthBuffSpell(Character *character, Character *enemy);

// Fonction de sort : Confusion
void confusionSpell(Character *character, Character *enemy);

#endif  // SPELL_H
