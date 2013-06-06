//
//  Enemy.cpp
//  SoulStone
//
//  Created by 易 文植 on 4/12/13.
//
//

#include "Enemy.h"

Enemy::Enemy(int sceneIndex):row(3), col(7), cap(21) {
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        demonGrid = CCArray::createWithCapacity(cap);
        demonsInAction = CCArray::create();
        demonGrid->retain();
        demonsInAction->retain();
        
        //read wave infomation from configure file;
        /*模拟一波怪物*/
        waveNum = 1;
        
        waves = new int *[1];
        int w[] = {0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1,
            -1, -1, -1, -1, -1, -1, -1};
        waves[0] = w;
        
    } while (0);
    
}

Enemy::~Enemy() {
    for (int i = 0; i < waveNum; i++) {
        delete [] waves[i];
    }
    delete waves;
    
    demonGrid->release();
    demonsInAction->release();
}

CCArray* Enemy::check() {
    CCArray* rd = CCArray::create();
    
    if (demonsInAction->count() == 0) {
        sendNextWave();
    }
    return rd;
}

void Enemy::sendNextWave() {
    if (nextWave >= waveNum) return;
    
    int *w = waves[nextWave];
    nextWave++;
    
    int i = 0;
    
    for (i = 0; i < cap; i++) {
        Demon* demon = new Demon(CCString::createWithFormat("demon%d", 0));
        
        int c = i % 7;
        int r = 3 - i / 7;
        demon->setPosition(ccp(Unit::GRID_SIZE * c + Unit::GRID_SIZE/2, Unit::GRID_SIZE * r + Unit::GRID_SIZE/2));
        addChild(demon);
    }
    
}