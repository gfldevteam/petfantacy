//
//  Background.cpp
//  SoulStone
//
//  Created by 易 文植 on 3/7/13.
//
//

#include "Background.h"

#include "reslist.h"

CCSprite* Background::create(const char* sname) {
    char bgname[50] = "r_background_";
    strcat(bgname, sname);
    strcat(bgname, ".jpg");
    CCSprite* bg = CCSprite::create(bgname);
    bg->setAnchorPoint(ccp(0, 0));
    return bg;
}