//
//  Demon.h
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//
//

#ifndef __SoulStone__Demon__
#define __SoulStone__Demon__

#include <iostream>

#include "Unit.h"


/**
 @brief 恶魔，敌方施法单位
 */
class Demon : public Unit {
public:
    Demon(CCString*);
private:
    int hp;
    int stength;
    float castInterval;
};

#endif /* defined(__SoulStone__Demon__) */
