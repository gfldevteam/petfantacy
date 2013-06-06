//
//  Enemy.h
//  SoulStone
//
//  Created by 易 文植 on 4/12/13.
//
//

#ifndef __SoulStone__Enemy__
#define __SoulStone__Enemy__

#include <iostream>

#include "cocos2d.h"
#include "Demon.h"

USING_NS_CC;

class Enemy : public CCLayer {
    
public:
    Enemy(int);
    ~Enemy();
    
    CCArray* check();
    
private:
    
    const int row;
    const int col;
    const int cap;
    
    /*
     怪物方阵，由row*col＝cap个Demon组成
     **/
    CCArray* demonGrid;
    
    /*
     战斗中的怪物
     **/
    CCArray* demonsInAction;
    
    /*
     怪物波数配置
     **/
    int **waves;
    
    int waveNum;
    int nextWave = 0;
    
    /*
     将下一波怪物加入战斗
     **/
    void sendNextWave();
};

#endif /* defined(__SoulStone__Enemy__) */
