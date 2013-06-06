//
//  BattleScene.h
//  SoulStone
//
//  Created by 易 文植 on 3/6/13.
//
//

#ifndef __SoulStone__BattleScene__
#define __SoulStone__BattleScene__

#include <iostream>
#include "cocos2d.h"
#include "Troop.h"
#include "Pet.h"
#include "Demon.h"
#include "Enemy.h"

USING_NS_CC;


/**
 @brief 对战场景
 */
class BattleScene : public CCLayer {
public:
    BattleScene(const char*);
    virtual ~BattleScene() {};
    
    /**
     @brief 初始化ui、军队、敌方队伍
     @return true 初始化成功
     @return false 初始化失败
     */
    bool init();
    
    /**
     @brief
     */
    void start();
    
    /**
     @brief 每一帧调用
     1. 检查法术队列中是否还有法术，如果有法术则依次施放
     2. Enemy.check，检查是否需要填充
     3. Troop.check 检查是否有自动消除的单位
     */
    void tick();
    
private:
    const char* name;
    Troop* troop;
    Enemy* enemy;
    //正在施放中的法术
    CCArray* spells;
    CCSprite* background;
    
};

#endif /* defined(__SoulStone__BattleScene__) */
