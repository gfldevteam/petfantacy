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
    
    SpellEffect();
    
    ~SpellEffect();
    
    void start();
    
    void setCaster(Pet* p);
    
    void setTarget(Demon* t);
    
    void setTargets(CCArray* arr);
    
    void setType(int type);
    
    void setLevel(int level);
    
    void setDuration(float d);
    
    CCSprite* getSprite() const;
    
    bool isCasting() const;
    
    
private:
    
    int type;
    
    int level;
    
    CCPoint origin;
    
    Pet* caster;
    
    /*攻击目标*/
    Demon* target;
    
    /*aoe攻击目标*/
    CCArray* targets;
    
    CCAction* effect;
    
    CCFiniteTimeAction* hitEffect;
    
    CCSprite* sprite;
    
    float duration;
    
    int damage;
    
    bool casting;
    
    void stopCasting();

protected:
    
    void setOrigin(CCPoint o);
    
    virtual void play();
    
    virtual void playHit();
    
};


#endif /* defined(__PetFantacy__SpellEffect__) */
