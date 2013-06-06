//
//  Utils.h
//  SoulStone
//
//  Created by 易 文植 on 3/18/13.
//
//

#ifndef __SoulStone__Utils__
#define __SoulStone__Utils__

#include <iostream>


#include "cocos2d.h"

USING_NS_CC;

class Utils {
public:
    static void removeStringFromArray(CCArray*, CCString*);
    
    static bool compareString(CCString*, CCString*);
    
    static CCArray* getPetTypes();
    
    static void loadTexture(const char*);
    
    static bool isFileExist(const char*);
    
    static bool isZipFileExist(const char*, const char*);
    
    static CCAction* createAnimation(const char*);
};

#endif /* defined(__SoulStone__Utils__) */
