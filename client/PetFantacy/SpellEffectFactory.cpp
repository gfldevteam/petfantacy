//
//  SpellEffectFactory.cpp
//  PetFantacy
//
//  Created by 易 文植 on 6/17/13.
//
//

#include "SpellEffectFactory.h"

SpellEffect* SpellEffectFactory::createSpellEffect(int type, int level, Pet* caster) {
    char className[15];
    sprintf(className, "%d", type);
    SpellEffect* spell = CREATE_SE(3);
    spell->setType(type);
    spell->setLevel(level);
    spell->setCaster(caster);
    return spell;
}
