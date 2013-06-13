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
    spellEffect = new SpellEffect(3, 1, ccp(300, 500), ccp(20 + CCRANDOM_0_1() * 280, 300 + 180 * CCRANDOM_0_1()), sprite);
    duration = 0.5;
    aoeType = 0;
}

/*
 播放法术效果，并对target产生伤害；
 ticks减一
 */
void Spell::attack(CCArray* demons) {
    if (shots >= 0 && !casting) {
        if (demons->count() > 0) {
            CCPoint target = ((Demon*)demons->randomObject())->getPosition();
            target.x+=10;
            target.y+=230;
            spellEffect->setTarget(target);
        }
        
        spellEffect->play();
        sprite->runAction(CCSequence::create(CCDelayTime::create(duration),
                                             CCCallFunc::create(this, callfunc_selector(Spell::stopCasting))));
        casting = true;
        //todo: 计算伤害，并减少目标血量
    } else {
        return;
    }
    shots--;
    
}