//
//  SpellEffect.h
//  PetFantacy
//
//  Created by 易 文植 on 5/31/13.
//
//

#ifndef __PetFantacy__SpellEffect__
#define __PetFantacy__SpellEffect__

#include <iostream>

#include "cocos2d.h"
#include "Pet.h"
#include "Demon.h"

USING_NS_CC;


/**
 
 法术效果接口
 
 */
class SpellEffect : public CCObject{
    
    
public:
    /**
     * @brief: 创建SpellEffect对象
     * @param int pet type
     * @param int pet level
     * @param CCPoint origin, position of caster
     */
    SpellEffect(int type, int level, float duration, CCSprite*, CCPoint origin = ccp(0, 0));
    
    static SpellEffect* create(int type, int level, float duration, CCSprite* sprite, CCPoint origin = ccp(0, 0));

    void play();

    void playHit();
    
    void setOrigin(CCPoint o) {
        origin = o;
    }
    
    void setTarget(CCPoint t) {
        target = t;
    }
    
private:
    
    int type;
    
    int level;
    
    CCPoint origin;
    
    /*攻击目标*/
    CCPoint target;
    
    /*aoe攻击目标*/
    CCArray targets;
    
    CCAction* effect;
    
    CCFiniteTimeAction* hitEffect;
    
    CCSprite* sprite;
    
    float duration;
    
};

#define CREATE_SE(type, duration, sprite) new SpellEffect#type();

#endif /* defined(__PetFantacy__SpellEffect__) */
