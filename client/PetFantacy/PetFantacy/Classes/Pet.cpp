//
//  Pet.cpp
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//
//

#include "Pet.h"
#include "Utils.h"

Pet::Pet(CCString* type, int index):power(1), locked(false), castDuration(1), castAnim(NULL), Unit(type, index) {
    char str[] = "";
    sprintf(str, "%d", this->index);
    
    const char* fileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(CCString::createWithFormat("%s_l1.plist", type->getCString())->getCString());
    if (type->boolValue() && Utils::isFileExist(fileName)) {
        try {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(fileName);
        } catch (int e) {
            CCLog("An exception occurred. Exception Nr. %d", e);
        }
        
    }
    //lb = CCLabelTTF::create(str, "Arial", 12);
    //addChild(lb, 100000);
}

void Pet::setPower(int b) {
    power = b;
}

int Pet::getPower() {
    return power;
}

void Pet::setIndex(int i) {
    //lb->setString(CCString::createWithFormat("%d %d", index, i)->getCString());
    Unit::setIndex(i);
}

void Pet::setType(CCString* t) {
    type = t;
    CCString* fileName = CCString::createWithFormat("%s.png", type->getCString());
    removeChild(sprite, true);
    sprite = CCSprite::createWithTexture((CCTextureCache::sharedTextureCache())->addImage(fileName->getCString()));
    addChild(sprite, 0, 0);
    
    castAnim = NULL;
}

Pet* Pet::createFakePet() {
    return new Pet(CCString::create(""), -1);
}

void Pet::cast() {
    if (castAnim != NULL) {
        sprite->runAction(castAnim);
        return;
    } else {
        castAnim = Utils::createAnimation(
                    CCString::createWithFormat("%s_l1", type->getCString())->getCString()
                   );
        
        if (castAnim == NULL) {
            castAnim = CCFadeOut::create(castDuration);
        }
        
        
    }
    
    sprite->runAction(castAnim);
}