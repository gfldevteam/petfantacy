//
//  Spell.h
//  PetFantacy
//
//  Created by 易 文植 on 5/30/13.
//
//

#ifndef __PetFantacy__Spell__
#define __PetFantacy__Spell__

#include <iostream>
#include "Pet.h"
#include "Demon.h"
#include "SpellEffect.h"

class Spell : public CCObject{
    
public:
    Spell(Pet*);
    ~Spell(){};
    
    int getTicks() {
        return shots;
    };
    
    void attack();
    
    void distroy();
    
private:
    
    /*施法者*/
    Pet* caster;
    
    /*目标*/
    Demon* target;
    
    /*施法时间*/
    float duration;
    
    /*跳数*/
    int shots;
    
    /*每跳造成的伤害*/
    int damage;
    
    bool hasRandomTarget;
};

#endif /* defined(__PetFantacy__Spell__) */
