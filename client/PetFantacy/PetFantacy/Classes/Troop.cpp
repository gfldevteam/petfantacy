//
//  Troop.cpp
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//
//

#include "Troop.h"
#include "Utils.h"

Troop::Troop(const char* type): col(7), row(4), cap(28) {
    init();
}

bool Troop::init() {
    do {
        
        CC_BREAK_IF(!CCLayer::init());
        
        this->autorelease();
        
        removeQueue = CCArray::create();
        removeQueue->retain();
        
        petTypes = Utils::getPetTypes();
        
        //init pets array
        pets = CCArray::createWithCapacity(2 * cap);
        vlinks = CCArray::createWithCapacity(cap);
        hlinks = CCArray::createWithCapacity(cap);
        
        pets->retain();
        vlinks->retain();
        hlinks->retain();
        
        //todo: 可能出现某一个节点没有可用类型的情况，这种情况重新初始化
        for (int i = 0; i < cap; i++) {
            vlinks->addObject(CCArray::create());
            hlinks->addObject(CCArray::create());
            
            CCArray* availTypes = CCArray::createWithArray(petTypes);
            int v = i;
            int h = i;
            
            for (int j = i - col; j >= 0 && j >= i - 2*col; j -= col) {
                CCArray* vlink = (CCArray*)vlinks->objectAtIndex(j);
                
                int size = vlink->count();
                if (size == 0) {
                    continue;
                } else if (size >= 2) {
                    Utils::removeStringFromArray(availTypes, ((Pet*)vlink->objectAtIndex(0))->getType());
                    break;
                }
            }
            
            if (i%col != 0) {
                for (int j = i - 1; j >= 0 && j >= i - 2; j--) {
                    CCArray* hlink = (CCArray*)hlinks->objectAtIndex(j);
                    int size = hlink->count();
                    
                    if (size == 0) {
                        continue;
                    } else if (size >= 2) {
                        Utils::removeStringFromArray(availTypes, ((Pet*)hlink->objectAtIndex(0))->getType());
                        break;
                    }
                    
                }
            }
            
            CCString* petType = (CCString*)availTypes->randomObject();
            
            if (i >= col && petType->isEqual(getPetAtIndex(i - col)->getType())) {
                v -= col;
            }
            if (i > 0 && i % 7 != 0 && petType->isEqual(getPetAtIndex(i - 1)->getType())) {
                h--;
            }
            
            Pet* pet = new Pet(petType, i);
            pet->setVLink(v);
            pet->setHLink(h);
            
            ((CCArray*)vlinks->objectAtIndex(v))->addObject(pet);
            ((CCArray*)hlinks->objectAtIndex(h))->addObject(pet);
            pets->addObject(pet);
            
            int c = i % 7;
            int r = 3 - i / 7;
            
            pet->setPosition(ccp(Unit::GRID_SIZE * c + Unit::GRID_SIZE/2, Unit::GRID_SIZE * r + Unit::GRID_SIZE/2));
            
            addChild(pet);
        }
        
        for (int i = cap; i < 2 * cap; i++) {
            pets->addObject(Pet::createFakePet());
        }
        
        selectedPet = NULL;
        
        return true;
        
    } while (0);
    
    return false;
}

CCString* Troop::randomType() {
    return (CCString*)petTypes->randomObject();
}

void Troop::onEnter() {
    CCLayer::onEnter();
    CCDirector* director = CCDirector::sharedDirector();
    CCTouchDispatcher* dispatcher = director->getTouchDispatcher();
    dispatcher->addTargetedDelegate(this, 0, true);
}

void Troop::onExit() {
    CCDirector* director = CCDirector::sharedDirector();
    CCTouchDispatcher* dispatcher = director->getTouchDispatcher();
    dispatcher->removeDelegate(this);
}

bool Troop::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    selectPet(getPetAtPoint(touch->getLocation().x, touch->getLocation().y));
    return true;
}

void Troop::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    
}

void Troop::ccTouchEnded(CCTouch* touch, CCEvent* event) {
}

void Troop::selectPet(Pet* pet) {
    if (pet == NULL || pet->isLocked()) return;
    
    if (selectedPet
        && ((abs(pet->getIndex() - selectedPet->getIndex()) == 1 && pet->getIndex() / col == selectedPet->getIndex() / 7)
            || abs(pet->getIndex() - selectedPet->getIndex()) == col)) {
            
            swap(selectedPet, pet);
            selectedPet = NULL;
        } else {
            selectedPet = pet;
        }
}

bool Troop::tryPosition(int index, Pet* pet) {
    int v = 1;
    int p = pet->getIndex();
    CCString* type = pet->getType();
    
    int detector = index - col;
    Pet* prev = getPetAtIndex(detector);
    
    while (index != p + col && detector >= 0 && !prev->isLocked() && prev->getType()->isEqual(type)) {
        v++;
        if (v > 2) return true;
        
        detector -= col;
        prev = getPetAtIndex(detector);
    }
    
    detector = index + col;
    prev = getPetAtIndex(detector);
    
    while (index != p - col && detector < cap && !prev->isLocked() && prev->getType()->isEqual(type)) {
        v++;
        if (v > 2) return true;
        
        detector += col;
        prev = getPetAtIndex(detector);
    }
    
    v = 1;
    detector = index - 1;
    prev = getPetAtIndex(detector);
    
    while (index != p + 1 && detector >= 0 && detector / col == index / col && !prev->isLocked() && prev->getType()->isEqual(type)) {
        v++;
        if (v > 2) return true;
        
        detector -= 1;
        prev = getPetAtIndex(detector);
    }
    
    detector = index + 1;
    prev = getPetAtIndex(detector);
    
    while (index != p - 1 && detector < cap && !prev->isLocked() && prev->getType()->isEqual(type)) {
        v++;
        if (v > 2) return true;
        
        detector += 1;
        prev = getPetAtIndex(detector);
    }
    
    return false;
}

bool Troop::swap(Pet* pet1, Pet* pet2) {
    if (!pet1 || !pet2) {
        return false;
    }
    
    CCPoint tempPosition1 = pet1->getPosition();
    CCPoint tempPosition2 = pet2->getPosition();
    int index1 = pet1->getIndex();
    int index2 = pet2->getIndex();
    
    pet1->lock();
    pet2->lock();
    
    pet1->runAction(CCMoveTo::create(0.25, tempPosition2));
    pet2->runAction(CCMoveTo::create(0.25, tempPosition1));
    
    if (pet1->getType()->isEqual(pet2->getType())
        || (!tryPosition(index1, pet2) && !tryPosition(index2, pet1))) {
        
        pet1->runAction(CCSequence::create(CCDelayTime::create(0.25), CCMoveTo::create(0.25, tempPosition1), CCCallFunc::create(pet1, callfunc_selector(Pet::unlock)), NULL));
        pet2->runAction(CCSequence::create(CCDelayTime::create(0.25), CCMoveTo::create(0.25, tempPosition2), CCCallFunc::create(pet2, callfunc_selector(Pet::unlock)), NULL));
        
    } else {
        kickOut(pet1);
        kickOut(pet2);
        
        addPetAt(pet1, index2, 0.5);
        addPetAt(pet2, index1, 0.5);
    }
    
    return false;
}

void Troop::kickOut(Pet* pet) {
    int index = pet->getIndex();
    
    if (index >= cap) return;
    
    CCArray* vlink = (CCArray*)vlinks->objectAtIndex(pet->getVLink());
    int v = vlink->indexOfObject(pet);
    
    vlink->removeObject(pet);
    
    while (vlink->count() > v) {
        Pet* p = (Pet*)vlink->lastObject();
        p->setVLink(index + col);
        vlink->removeLastObject();
        ((CCArray*)vlinks->objectAtIndex(index + col))->insertObject(p, 0);
    }
    
    CCArray* hlink = (CCArray*)hlinks->objectAtIndex(pet->getHLink());
    int h = hlink->indexOfObject(pet);
    
    hlink->removeObject(pet);
    
    while (hlink->count() > h) {
        Pet* p = (Pet*)hlink->lastObject();
        p->setHLink(index + 1);
        hlink->removeLastObject();
        ((CCArray*)hlinks->objectAtIndex(index + 1))->insertObject(p, 0);
    }
    
    pets->replaceObjectAtIndex(index, Pet::createFakePet());
}


void Troop::addPetAt(Pet* pet, int index, float t) {
    pet->setIndex(index);
    pets->replaceObjectAtIndex(index, pet, true);
    
    runAction(CCSequence::create(CCDelayTime::create(t),
                                 CCCallFuncO::create(this, callfuncO_selector(Troop::rebuildLinkAt), pet)));
}

void Troop::recycle(Pet* pet) {
    //if already recycled
    if (pet->getIndex() >= cap) return;
    
    kickOut(pet);
    removeChild(pet, false);
    
    //todo: use a function in pet to reset the properties
    int newIndex = pet->getIndex() + cap;
    pet->setType(randomType());
    pet->setIndex(newIndex);
    int c = newIndex % 7;
    int r = 3 - newIndex / 7;
    
    pet->setPosition(ccp(Unit::GRID_SIZE * c + Unit::GRID_SIZE/2, Unit::GRID_SIZE * r + Unit::GRID_SIZE/2));
    
    pets->replaceObjectAtIndex(newIndex, pet);
}

void Troop::removePet(Pet* pet) {
    pet->lock();
    pet-> cast();
    pet->runAction(CCSequence::create(CCDelayTime::create(pet->getCastDuration()),
                                      CCCallFuncND::create(this, callfuncND_selector(Troop::recycle), pet),
                                      NULL));
    
}


/**
 重构消除链
 */
void Troop::rebuildLinkAt(Pet* pet) {
    int index = pet->getIndex();
    CCString* type = pet->getType();
    
    pet->unlock();
    
    Pet* prev = getPetAtIndex(index - col);
    int v = index;
    //纵向比较前一个对象，满足：1. 不为空，2. 非锁定，3. 类型相同
    if (prev != NULL && !prev->isLocked() && prev->getType()->isEqual(type)) {
        v = prev->getVLink();
    }
    
    int org = pet->getVLink();
    //将当前对象从原vlink中移除
    if (org >= 0 && org != v && org < vlinks->count()) {
        CCArray* link = (CCArray*)vlinks->objectAtIndex(org);
        if (link != NULL) link->removeObject(pet);
    }
    
    //将当前对象加入到新的vlink中
    ((CCArray*)vlinks->objectAtIndex(v))->addObject(pet);
    pet->setVLink(v);
    
    Pet* next = (index + col < cap)? getPetAtIndex(index + col) : NULL;
    //纵向比较如果有后一对象，且后一对象和当前对象有相同类型，则将属于后一对象所在vlink的对象全部移至
    //当前对象所属vlink
    if (next != NULL) {
        
        int norig = next->getVLink();
        if (!next->isLocked()
            && next->getType()->isEqual(type) && norig >= 0 && norig != v
            && next->getIndex() >= 0) {
            CCArray* nlink = (CCArray*)vlinks->objectAtIndex(norig);
            CCArray* link = (CCArray*)vlinks->objectAtIndex(v);
            
            for (int i = 0; i < nlink->count(); i++) {
                Pet* p = (Pet*)nlink->objectAtIndex(i);
                link->addObject(p);
                p->setVLink(v);
            }
            nlink->removeAllObjects();
        }
    }
    
    prev = getPetAtIndex(index - 1);
    v = index;
    //横向比较前一个对象，满足：1. 不为空，2. 非锁定，3. 类型相同，4. 和当前对象在同一行
    if (prev != NULL && !prev->isLocked() && index / col == prev->getIndex() / col && prev->getType()->isEqual(type)) {
        v = prev->getHLink();
    }
    
    org = pet->getHLink();
    //将当前对象从原hlink中移除
    if (org >= 0 && org != v && org < hlinks->count()) {
        CCArray* link = (CCArray*)hlinks->objectAtIndex(org);
        if (link != NULL) link->removeObject(pet);
    }
    
    //将当前对象加入到新的hlink中
    ((CCArray*)hlinks->objectAtIndex(v))->addObject(pet);
    pet->setHLink(v);
    
    next = (index + 1 < cap && index % col != col - 1)? getPetAtIndex(index + 1) : NULL;
    //横向比较如果有后一对象，且后一对象和当前对象有相同类型，则将属于后一对象所在hlink的对象全部移至
    //当前对象所属hlink
    if (next != NULL) {
        
        int norig = next->getHLink();
        if (norig >= 0 && !next->isLocked()
            && next->getType()->isEqual(type) && next->getIndex() >= 0) {
            CCArray* nlink = (CCArray*)hlinks->objectAtIndex(norig);
            CCArray* link = (CCArray*)hlinks->objectAtIndex(v);
            for (int i = 0; i < nlink->count(); i++) {
                Pet* p = (Pet*)nlink->objectAtIndex(i);
                link->addObject(p);
                p->setHLink(v);
            }
            nlink->removeAllObjects();
        }
    }
    
    //如果横向或纵向的link长度大于2，将其加入remove队列
    CCArray* vlink = (CCArray*)vlinks->objectAtIndex(pet->getVLink());
    CCArray* hlink = (CCArray*)hlinks->objectAtIndex(pet->getHLink());
    int power = 1;
    if (vlink->count() > 2) {
        for (int i = 0; i < vlink->count(); i++) {
            removeQueue->addObject(vlink->objectAtIndex(i));
        }
        power += vlink->count() - 1;
    }
    if (hlink->count() > 2) {
        for (int i = 0; i < hlink->count(); i++) {
            removeQueue->addObject(hlink->objectAtIndex(i));
        }
        power += hlink->count() - 1;
    }
    pet->setPower(power);
}

Pet* Troop::getPetAtPoint(float x, float y) {
    CCPoint location = this->getPosition();
    int c = floor((x - location.x) / Unit::GRID_SIZE);
    int r = row - ceil((y - location.y) / Unit::GRID_SIZE);
    int index = c + r * col;
    return getPetAtIndex(index);
}

Pet* Troop::getPetAtIndex(int index) {
    return (index >= 0 && index < pets->count())? (Pet*)pets->objectAtIndex(index) : NULL;
}


/**
 
 执行顺序：
 1. 从removeQueue中取出待清除对象执行清除操作；
 2. 检查是否有空缺位置（被fake pet占据），如果有则填补空缺；
 */
CCArray* Troop::check() {
    CCArray* removedPets = CCArray::create();
    removedPets->addObjectsFromArray(removeQueue);
    
    //清除
    while (removeQueue->count() > 0) {
        removePet((Pet*)removeQueue->lastObject());
        removeQueue->removeLastObject();
    }
    
    //填充
    for (int i = 0; i < cap; i++) {
        
        Pet* pet = (Pet*)pets->objectAtIndex(i);
        if (!pet->isFake()) continue;
        
        Pet* p = getBackUpFor(i);
        
        if (p == NULL || p->isFake()) continue;
        
        if (p->getIndex() >= cap) {
            addChild(p);
        }
        kickOut(p);
        int c = i % 7;
        int r = 3 - i / 7;
        //float t = 0.01 * (p->getIndex() - i);
        float t = 0.2;
        
        p->runAction(CCSequence::create(CCMoveTo::create(t, ccp(Unit::GRID_SIZE * c + Unit::GRID_SIZE/2, Unit::GRID_SIZE * r + Unit::GRID_SIZE/2)), NULL));
        addPetAt(p, i, t);
    }
    
    return removedPets;
}

Pet* Troop::getBackUpFor(int index) {
    index += col;
    Pet* next = getPetAtIndex(index);
    while (index < pets->count()) {
        bool isFake = next->isFake();
        if (!isFake) {
            if (index >= cap) {
                pets->replaceObjectAtIndex(index, Pet::createFakePet());
            }
            return next;
        }
        index += col;
        next = getPetAtIndex(index);
    }
    return NULL;
}