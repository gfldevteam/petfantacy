//
//  SpellEffect.cpp
//  PetFantacy
//
//  Created by 易 文植 on 5/31/13.
//
//

#include "SpellEffect.h"
#include "Utils.h"


SpellEffect::SpellEffect(int type, int level, CCPoint origin, CCPoint target, CCSprite* sprite)
: type(type), level(level), origin(origin), target(target), effect(NULL), hitEffect(NULL), duration(0.5), sprite(sprite) {
        CCLog("the angle is %f, %f", target.x, target.y);
    sprite->setPosition(origin);
}

SpellEffect* SpellEffect::create(int type, int level, CCPoint origin, CCPoint target) {
    SpellEffect* se = NULL;
    
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
    //sprite->runAction(CCSequence::create(CCDelayTime::create(duration), CCCallFunc::create(this, callfunc_selector(SpellEffect::playHit))));
}

void SpellEffect::playHit() {}