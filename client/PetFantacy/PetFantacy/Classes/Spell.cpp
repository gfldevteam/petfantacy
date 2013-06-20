//
//  Spell.cpp
//  PetFantacy
//
//  Created by 易 文植 on 5/30/13.
//
//

#include "Spell.h"
#include "SpellEffectFactory.h"

USING_NS_CC;

/**
 根据pet计算damage, 创建法术效果（SpellEffect)
 */
Spell::Spell(Pet* pet) {
    //这些属性都需要从配置中读取
    shots = 2;
    duration = 0.5;
    aoeType = 0;
    damage = 1;
    
    spellEffect = SpellEffectFactory::createSpellEffect(3, 1, caster);
}

CCSprite* Spell::getSprite() const {
    return spellEffect->getSprite();
}

bool Spell::stopped() const {
    return shots == 0 && !spellEffect->isCasting();
}

/*
 播放法术效果，并对target产生伤害；
 ticks减一
 */
void Spell::attack(CCArray* demons) {
    if (shots <= 0) return;
    
    if (spellEffect) {
        //如果施法已经停止，则重新选择目标并播放法术效果，否则跳过
        if (!spellEffect->isCasting()) {
            selectTargets(demons);
        
            spellEffect->start();
            
            int c = (targets != NULL)? targets->count() : 0;
            for (int i=0; i < c; i++) {
                Demon* d = (Demon*)targets->objectAtIndex(i);
                d->hit(damage);
            }
            
            shots--;
        } else {
            return;
        }
    } else {
        spellEffect = SpellEffectFactory::createSpellEffect(3, 1, caster);
        return;
    }
}

void Spell::selectTargets(CCArray* demons) {
    switch (aoeType) {
        case 0:
            if (demons->count() > 0) {
                
                target = (Demon*)demons->randomObject();
                
                targets = CCArray::create();
                targets->addObject(target);
                targets->retain();
                
            } else {
                target = NULL;
                targets = NULL;
            }
            break;
            
        default:
            break;
    }
    
    spellEffect->setTarget(target);
    spellEffect->setTargets(targets);
}
