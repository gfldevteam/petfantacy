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
     * @param CCSprite target
     */
    SpellEffect(int, int, CCPoint, CCSprite*);

    void play();

    void playHit();
    
private:
    
    CCPoint origin;
    
    CCSprite* target;
    
    CCAction* effect;
    
    CCAction* hitEffect;
    
};

#endif /* defined(__PetFantacy__SpellEffect__) */
