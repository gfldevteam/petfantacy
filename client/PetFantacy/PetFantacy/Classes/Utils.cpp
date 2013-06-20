//
//  Utils.cpp
//  SoulStone
//
//  Created by 易 文植 on 3/18/13.
//
//

#include "Utils.h"

#include <stdio.h>

#include "support/zip_support/unzip.h"

using namespace std;

USING_NS_CC;

void Utils::removeStringFromArray(CCArray* array, CCString* str) {
    int size = array->count();
    for (int i = 0; i < size; i++) {
        CCString* s = (CCString*)array->objectAtIndex(i);
        if (Utils::compareString(s, str)) {
            array->removeObject(s);
            break;
        }
    }
}

bool Utils::compareString(CCString* str1, CCString* str2) {
    return strcmp(str1->getCString(), str2->getCString()) == 0;
}

CCArray* Utils::getPetTypes() {
    return CCArray::createWithContentsOfFileThreadSafe("pet_types.plist");
}

CCFiniteTimeAction* Utils::createAnimation(const char *animName, int times) {
    CCLog("create animation: %s", animName);
    
    //CCSpriteFrameCache* cache = CCSpriteFrameCache::addSpriteFramesWithFile()
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    const char* fileName = CCString::createWithFormat("%s_0.png", animName)->getCString();
    CCSpriteFrame* frame = cache->spriteFrameByName(fileName);
    
    if (frame == NULL) {
        return NULL;
    } else {
        CCAnimation* anim = CCAnimation::create();
        anim->setDelayPerUnit(0.1f);
        int i = 0;
        do {
            anim->addSpriteFrame(frame);
            i++;
            fileName = CCString::createWithFormat("%s_%d.png", animName, i)->getCString();
            frame = cache->spriteFrameByName(fileName);
        } while (frame != NULL);
        if (times == 0) {
            return CCRepeatForever::create(CCAnimate::create(anim));
        } else {
            return CCRepeat::create(CCAnimate::create(anim), times);
        }
    }
    return NULL;
}

void Utils::loadTexture(const char* file) {
    
}

bool Utils::isFileExist(const char* pszFileName)
{
    string fullPath(pszFileName);
    
    if ((! pszFileName))
    {
        return false;
    }
    
    if (/*pszFileName[0] != '/'*/ false) /*todo: apk*/
    {
        // read from apk
        fullPath.insert(0, "assets/");
        return Utils::isZipFileExist(string(CCFileUtils::sharedFileUtils()->getResourceDirectory()).c_str(), fullPath.c_str());
    }
    else
    {
        do
        {
            // read rrom other path than user set it
            FILE *fp = fopen(pszFileName, "rb");
            if (fp != NULL)
            {
                fclose(fp);
                return true;
            }
        }
        while (0);
    }
    return false;
}

bool Utils::isZipFileExist(const char* pszZipFilePath, const char* pszFileName)
{
    unzFile pFile = NULL;
    bool res = false;
    do
    {
        CC_BREAK_IF(!pszZipFilePath || !pszFileName);
        CC_BREAK_IF(strlen(pszZipFilePath) == 0);
        
        pFile = unzOpen(pszZipFilePath);
        
        int nRet = unzLocateFile(pFile, pszFileName, 1);
        res = UNZ_OK == nRet;
        
    } while (0);
    
    if (pFile)
    {
        unzClose(pFile);
    }
    return res;
}