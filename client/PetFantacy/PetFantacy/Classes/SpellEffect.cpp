//
//  SpellEffect.cpp
//  PetFantacy
//
//  Created by 易 文植 on 5/31/13.
//
//

#include "SpellEffect.h"
#include "Utils.h"


SpellEffect::SpellEffect() {
        //setOrigin(ccp(300, 500));
    sprite = CCSprite::create();
    sprite->retain();
    sprite->setAnchorPoint(ccp(0, 0));
    casting = false;
    
    damage = 1;
    effect = NULL;
}

SpellEffect::~SpellEffect() {
    sprite->removeFromParentAndCleanup(true);
}

void SpellEffect::setCaster(Pet* p) {
    caster = p;
}

void SpellEffect::setTarget(Demon* t) {
    target = t;
}

void SpellEffect::setTargets(CCArray* arr) {
    targets = arr;
}

void SpellEffect::setType(int t) {
    type = t;
}

void SpellEffect::setLevel(int l) {
    level = l;
}

void SpellEffect::setDuration(float d) {
    duration = d;
}

CCSprite* SpellEffect::getSprite() const {
    return sprite;
}

bool SpellEffect::isCasting() const {
    return casting;
}

void SpellEffect::stopCasting() {
    casting = false;
}

void SpellEffect::setOrigin(CCPoint o) {
    origin = o;
}

void SpellEffect::start() {
    play();
    
    sprite->runAction(CCSequence::create(CCDelayTime::create(duration),
                                         CCCallFunc::create(this, callfunc_selector(SpellEffect::playHit)),
                                         CCDelayTime::create(0.2),
                                         CCCallFunc::create(this, callfunc_selector(SpellEffect::stopCasting)), NULL));
    
    casting = true;
}

void SpellEffect::play() {
    if (target == NULL) {
        //todo: choose a random position as target
        return;
    }
    sprite->setPosition(origin);
    sprite->setRotation(0);
    sprite->stopAllActions();
    
    if (effect == NULL) {
        effect = Utils::createAnimation(CCString::createWithFormat("spell%d_l%d_p1",
                        type, level)->getCString());
        
        effect->retain();
    }

    CCPoint t = target->getPosition();
    t.y += 220;
    
    sprite->setRotation(atan((t.x - origin.x)/(t.y - origin.y)) * 180 / 3.14);
    sprite->runAction(effect);
    sprite->runAction(CCMoveTo::create(duration, t));
}

void SpellEffect::playHit() {
    sprite->setRotation(0);
    hitEffect = Utils::createAnimation(CCString::createWithFormat("spell%d_l%d_p2", type, level)->getCString(), 1);
    hitEffect->retain();
    
    sprite->stopAction(effect);
    sprite->runAction(hitEffect);
    
    int c = targets? targets->count() : 0;
    for (int i=0; i < c; i++) {
        Demon* d = (Demon*)targets->objectAtIndex(i);
        d->playHit();
    }
}


