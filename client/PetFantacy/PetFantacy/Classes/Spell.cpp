//
//  Spell.cpp
//  PetFantacy
//
//  Created by 易 文植 on 5/30/13.
//
//

#include "Spell.h"

USING_NS_CC;

/**
 根据pet计算damage, 创建法术效果（SpellEffect)
 */
Spell::Spell(Pet* pet) {
    shots = 2;
    sprite = CCSprite::create();
    sprite->setAnchorPoint(ccp(0, 0));
    sprite->retain();
    casting = false;
    duration = 0.5;
    spellEffect = SpellEffect::create(3, 1, duration, sprite);
    aoeType = 0;
}

/*
 播放法术效果，并对target产生伤害；
 ticks减一
 */
void Spell::attack(CCArray* demons) {
    if (shots >= 0 && !casting) {
        selectTargets(demons);
        
        spellEffect->play();
        /*
         CCSequence::create的参数中最后一个传NULL，否则会出现莫名错误
         **/
        sprite->runAction(CCSequence::create(CCDelayTime::create(duration),
                                             CCCallFunc::create(spellEffect, callfunc_selector(SpellEffect::playHit)),
                                             CCDelayTime::create(0.2),
                                             CCCallFunc::create(this, callfunc_selector(Spell::stopCasting)), NULL));
        casting = true;
        //todo: 计算伤害，并减少目标血量
    } else {
        return;
    }
    shots--;
}

void Spell::selectTargets(CCArray* demons) {
    switch (aoeType) {
        case 0:
            if (demons->count() > 0) {
                CCPoint target = ((Demon*)demons->randomObject())->getPosition();
                target.x+=0;
                target.y+=220;
                spellEffect->setTarget(target);
            }
            break;
            
        default:
            break;
    }
}