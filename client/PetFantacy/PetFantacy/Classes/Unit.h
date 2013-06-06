//
//  Unit.h
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//

#ifndef __SoulStone__Unit__
#define __SoulStone__Unit__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

/**
 
 @brief 作战单位
 
 */
class Unit : public CCSprite {
public:
    static const int GRID_SIZE = 40;
    
    Unit(CCString*, int);
    virtual ~Unit(){};
    
    bool init();
    
    /**
     @brief 施法，执行施法动作
     */
    void cast();
    
    CCString* getType();
    
    int getIndex();
    
    void setIndex(int);
    
    bool isOfType(char*);
    
private:
    int row;
    int col;
    
protected:
    int index;
    CCString* type;
    CCSprite* sprite;
};

#endif /* defined(__SoulStone__Unit__) */
