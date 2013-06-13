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

USING_NS_CC;


/**
 
 法术效果接口
 
 */
class SpellEffect {
    
    
public:
    /**
     * @brief: 创建SpellEffect对象
     * @param int pet type
     * @param int pet level
     * @param CCPoint origin, position of caster
     * @param CCPoint target position
     */
    SpellEffect(int, int, CCPoint, CCPoint, CCSprite*);
    
    static SpellEffect* create(int, int, CCPoint, CCPoint);

    void play();

    void playHit();
    
    void setTarget(CCPoint t) {
        target = t;
    }
    
private:
    
    int type;
    
    int level;
    
    CCPoint origin;
    
    CCPoint target;
    
    CCAction* effect;
    
    CCAction* hitEffect;
    
    CCSprite* sprite;
    
    float duration;
    
};

#define CREATE_SU(type) new SpellEffect##type();

#endif /* defined(__PetFantacy__SpellEffect__) */
