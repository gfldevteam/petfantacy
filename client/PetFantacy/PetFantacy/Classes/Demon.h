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
    
    int getHP() const;
    
    bool isAlive() const;
    
    /*
     @brief 怪物被击中有两个阶段：
     1. 被击中：Demon::hit()，计算hp，hp小于等于0时将不能再被选中成为攻击目标，在Spell::attack时触发；
     2. 播放被击中动画：Demon::playHit()，播放完动画后，如果hp<=0则将alive置为false，等待被移除；
     @param int damage 法术造成的基本伤害
     @param int effectType 特殊法术效果
     */
    void hit(int damage, int effectType = 0);
    
    void playHit();
    
private:
    int hp;
    bool alive;
    int stength;
    float castCD;
    float castDuration;
};

#endif /* defined(__SoulStone__Demon__) */
