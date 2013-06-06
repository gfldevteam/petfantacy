//
//  Background.h
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//
//

#ifndef __SoulStone__Background__
#define __SoulStone__Background__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

/**
 @brief Background factory
 
 */

class Background {
public:
    /**
     @brief create a background for corresponding scenes
     @return CCLayer*
     */
    static CCSprite* create(const char*);
    
};

#endif /* defined(__SoulStone__Background__) */
