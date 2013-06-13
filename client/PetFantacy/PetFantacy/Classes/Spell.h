//
//  Spell.h
//  PetFantacy
//
//  Created by 易 文植 on 5/30/13.
//
//

#ifndef __PetFantacy__Spell__
#define __PetFantacy__Spell__

#include <iostream>
#include "Pet.h"
#include "Demon.h"
#include "SpellEffect.h"

class Spell : public CCObject{
    
public:
    Spell(Pet*);
    ~Spell(){};
    
    int getTicks() {
        return shots;
    };
    
    /**
     @brief 攻击目标，1. 如果目标随机，并且每次攻击的目标不同（aoeType＝0），则从demons参数
            中随机选择目标；2. 如果目标随机，并且每次攻击目标固定（aoeType=1），则首先判断
            targets是否已经初始化，如果是则攻击targets，否则从demons中随机选择目标并初始化
            targets；3. 如果由固定方式计算，则按规则计算；4. 如果demons为空，则可选择范围
            扩大至所有网格
     @param Demon*[] demons
     */
    void attack(CCArray* demons);
    
    void distroy();
    
    CCSprite* getSprite() {
        return sprite;
    };
    
private:
    
    /*施法者*/
    Pet* caster;
    
    /*目标*/
    Demon* targets;//todo:这应该是一个数组，由aoe type决定
    
    /*施法时间*/
    float duration;
    
    /*法术效果*/
    SpellEffect* spellEffect;
    
    /*跳数*/
    int shots;
    
    /*每跳造成的伤害*/
    int damage;
    
    /*aoe type*/
    int aoeType;
    
    bool hasRandomTarget;
    
    CCSprite* sprite;
    
    /*是否在施法中*/
    bool casting;
    
    /*
     
     */
    void stopCasting() {
        casting = false;
    };
};

#endif /* defined(__PetFantacy__Spell__) */
