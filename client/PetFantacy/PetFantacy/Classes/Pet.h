//
//  Pet.h
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//
//

#ifndef __SoulStone__Pet__
#define __SoulStone__Pet__

#include <iostream>
#include "Unit.h"


/**
 @brief 宠物，己方作战单位
 */
class Pet : public Unit {
    
public:
    Pet(CCString*, int);
    Pet(bool);
    
    void setPower (int);
    int getPower ();
    
    void setVLink (int vlink) {
        v = vlink;
    }
    
    int getVLink () {
        return v;
    }
    
    void setHLink (int hlink) {
        h = hlink;
    }
    
    int getHLink () {
        return h;
    }
    
    void setIndex(int);
    
    void setType(CCString*);
    
    bool isLocked() {
        return locked;
    }
    
    void lock() {
        locked = true;
    }
    
    void unlock() {
        locked = false;
    }
    
    void cast();
    
    static Pet* createFakePet();
    
    float getCastDuration() {
        return castDuration;
    }
    
    bool isFake() {
        return isOfType("");
    }
    
private:
    int power;
    
    //纵向相邻数
    int v;
    
    //横向相邻数
    int h;
    
    //
    bool locked;
    
    //
    float castDuration;
    
    /*casting animation*/
    CCAction* castAnim;
    
    
    CCLabelTTF* lb;
};

#endif /* defined(__SoulStone__Pet__) */
