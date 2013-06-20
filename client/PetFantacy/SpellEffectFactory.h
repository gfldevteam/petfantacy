//
//  SpellEffectFactory.h
//  PetFantacy
//
//  Created by 易 文植 on 6/17/13.
//
//

#ifndef __PetFantacy__SpellEffectFactory__
#define __PetFantacy__SpellEffectFactory__

#include <iostream>

#include "Pet.h"
#include "Demon.h"

#include "SpellEffect3.h"

//todo: implement c++ reflection

#define CREATE_SE(class_name) new SpellEffect##class_name()

class SpellEffectFactory {
    
public:
    static SpellEffect* createSpellEffect(int type, int level, Pet* caster);
};

#endif /* defined(__PetFantacy__SpellEffectFactory__) */
