//
//  SpellEffect.cpp
//  PetFantacy
//
//  Created by 易 文植 on 5/31/13.
//
//

#include "SpellEffect.h"
#include "Utils.h"


SpellEffect::SpellEffect(int type, int level, float duration, CCSprite* sprite, CCPoint origin)
: type(type), level(level), origin(origin), targets(NULL), effect(NULL), hitEffect(NULL), duration(duration), sprite(sprite) {
        setOrigin(ccp(300, 500));
}

SpellEffect* SpellEffect::create(int type, int level, float duration, CCSprite* sprite, CCPoint origin) {
    SpellEffect* se = new SpellEffect(type, level, duration, sprite, origin);
    return se;
}

void SpellEffect::play() {
    sprite->setPosition(origin);
    sprite->setRotation(0);
    sprite->stopAllActions();
    
    if (effect == NULL) {
        effect = Utils::createAnimation(CCString::createWithFormat("spell%d_l%d_p1",
                        type, level)->getCString());
        effect->retain();
    }

    sprite->setRotation(atan((target.x - origin.x)/(target.y - origin.y)) * 180 / 3.14);
    sprite->runAction(effect);
    sprite->runAction(CCMoveTo::create(duration, target));
}

void SpellEffect::playHit() {
    sprite->setRotation(0);
    hitEffect = Utils::createAnimation(CCString::createWithFormat("spell%d_l%d_p2", type, level)->getCString(), 1);
    hitEffect->retain();
    
    sprite->stopAction(effect);
    sprite->runAction(hitEffect);
}


