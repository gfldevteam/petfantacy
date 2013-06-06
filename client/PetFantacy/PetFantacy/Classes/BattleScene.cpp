//
//  BattleScene.cpp
//  SoulStone
//
//  Created by 易 文植 on 3/6/13.
//
//

#include "BattleScene.h"
#include "Background.h"
#include "Pet.h"
#include "Spell.h"

BattleScene::BattleScene (const char* name) : name(name) {
    init();
}

bool BattleScene::init() {
    do{
        CC_BREAK_IF(!CCLayer::init());
        
        this->autorelease();
        
        //create background
        background = Background::create(name);
        addChild(background);
        
        //init troop
        troop = new Troop("");
        troop->setPosition(ccp(20, 65));
        addChild(troop);
        
        enemy = new Enemy(0);
        enemy->setPosition(ccp(20, 240));
        addChild(enemy);
        
        spells = CCArray::create();
        spells->retain();
        
        start();
        
        return true;
        
    } while (0);
    
    return false;
}

void BattleScene::start() {
    schedule(schedule_selector(BattleScene::tick));
}

void BattleScene::tick() {
    CCArray* pets = troop->check();
    if (pets->count() > 0) {
        int c = pets->count(), i = 0;
        for (; i < c; i++) {
            spells->addObject(new Spell(NULL));
        }
    }
    
    int i = 0, c = spells->count();
    for (; i < c; i++) {
        Spell* spell = (Spell*)spells->objectAtIndex(i);
        if (spell->getTicks() > 0) {
            spell->attack();
        }
    }
    CCArray* demons = enemy->check();
}