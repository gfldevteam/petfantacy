//
//  Unit.cpp
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//
//

#include "Unit.h"

Unit::Unit(CCString* type, int index): type(type), index(index){
    init();
}

bool Unit::init() {
    do {
        CC_BREAK_IF(!CCSprite::init());
        
        type->retain();
        
        if (strcmp(type->getCString(), "") == 0) return false;
        
        CCString* fileName = CCString::createWithFormat("%s.png", type->getCString());
        sprite = CCSprite::createWithTexture((CCTextureCache::sharedTextureCache())->addImage(fileName->getCString()));
        addChild(sprite, 0, 0);
        
        return true;
        
    } while (0);
    
    return false;
}

void Unit::cast() {
}

bool Unit::isOfType(char* t) {
    return strcmp(t, type->getCString()) == 0;
}

CCString* Unit::getType() {
    return type;
}

int Unit::getIndex() {
    return index;
}

void Unit::setIndex(int index) {
    this->index = index;
    //CCLog("set index: %d", index);
}