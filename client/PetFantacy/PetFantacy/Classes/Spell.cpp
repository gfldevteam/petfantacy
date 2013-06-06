//
//  Spell.cpp
//  PetFantacy
//
//  Created by 易 文植 on 5/30/13.
//
//

#include "Spell.h"

/**
 根据pet计算damage, 创建法术效果（SpellEffect）,如果该法术有固定target，调用SpellEffect::init(caster, target)，产生对target的影响效果，如在头上挂朵云
 否则 Spell::init(caster, NULL);
 */
Spell::Spell(Pet* pet) {
    
}

/*
 播放法术效果，并对target产生伤害；
 ticks减一
 */
void Spell::attack() {
    if (shots >= 0) {
        CCLog("Shot");
    }
    shots--;
}