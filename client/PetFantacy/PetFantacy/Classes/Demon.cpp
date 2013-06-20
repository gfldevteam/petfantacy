//
//  Demon.cpp
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//
//

#include "Demon.h"

Demon::Demon(CCString* type):Unit(type, 0){
    hp = 1;
    alive = true;
}

int Demon::getHP() const {
    return hp;
}

bool Demon::isAlive() const {
    return alive;
}

void Demon::hit(int damage, int effectType) {
    hp -= damage;
}

void Demon::playHit() {
    //todo: display damage animation
    
    alive = (hp > 0);
    CCLog("%d   %d", hp, alive);
}