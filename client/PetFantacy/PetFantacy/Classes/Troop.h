//
//  Troop.h
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//
//

#ifndef __SoulStone__Troop__
#define __SoulStone__Troop__

#include <iostream>
#include "cocos2d.h"
#include "Unit.h"
#include "Pet.h"

USING_NS_CC;


/**
 @brief 己方军队，完成消除／补充等功能
 */
class Troop : public CCLayer {
    
public:
    
    //todo: new constructor with pet types
    Troop(const char*);
    virtual ~Troop(){
        pets->release();
        vlinks->release();
        hlinks->release();
    };
    
    void onEnter();
    void onExit();
    bool ccTouchBegan(CCTouch*, CCEvent*);
    void ccTouchMoved(CCTouch*, CCEvent*);
    void ccTouchEnded(CCTouch*, CCEvent*);
    
    
    /**
     @brief 初始化，创建并渲染军队阵型
     */
    bool init();
    
    /**
     @brief 检查是否有可以消除的单位，如果有则依次执行施法、消除和补充动作
     @return 被消除的单位
     */
    CCArray* check();
    
private:
    //pet types
    //todo: create this array from a configuration file
    CCArray* petTypes;
    
    //colums
    int col;
    
    //rows
    int row;
    
    int cap;
    
    //pets
    CCArray* pets;
    
    //vertical adjacent nodes
    CCArray* vlinks;
    
    //horizontal adjacent nodes
    CCArray* hlinks;
    
    //selected pet
    Pet* selectedPet;
    
    CCArray* removeQueue;
    
    /* functions begin */
    
    CCString* randomType();
    
    Pet* getPetAtPoint(float, float);
    
    Pet* getPetAtIndex(int);
    
    /*
     * select a pet, if there is already one selected, swap it with the current
     * one, else show the circle under it
     **/
    void selectPet(Pet*);
    
    bool tryPosition(int, Pet*);
    
    /*
     * swap two pets, swap them back if fail to create a expunction
     * @return bool, success or not
     **/
    bool swap(Pet*, Pet*);
    
    /**
     @brief check if position can be expunged given a specific type
     @param index to be checked
     @param type to be set to that index
     @return bool
     */
    bool checkPosition(int, CCString*);
    
    /**
     @brief set index of pet, move pet to the right position
     @param Pet*
     @param int index
     @param float 延迟rebuildlink的时间
     */
    void addPetAt(Pet*, int, float);
    
    /**
     @brief
     */
    void removePet(Pet*);
    
    /**
     @brief
     */
    void rebuildLinkAt(Pet*);
    
    
    void kickOut(Pet*);
    
    /**
     将一个Pet移至填充队列中
     */
    void recycle(Pet*);
    
    /**
     从填充队列中取出一个Pet，将其初始化后返回
     */
    Pet* getBackUpFor(int);
};
#endif /* defined(__SoulStone__Troop__) */
