//
//  Count.cpp
//  Observer
//
//  Created by iOS on 2015/01/19.
//
//

#include "Count.h"

USING_NS_CC;

Count::~Count()
{
    this->getEventDispatcher()->removeCustomEventListeners("TimeCount");
}

bool Count::init()
{
    if (!Label::init()) {
        return false;
    }
    
    _count = 0;
    
    this->setString("0");
    this->setFontScale(2.0f);
    this->schedule(schedule_selector(Count::countUp), 1.0f);
    
    this->getEventDispatcher()->addCustomEventListener("TimeCount", [=](EventCustom* event) {
        this->countUp(0);
    });
    
    return true;
}

void Count::countUp(float dt)
{
    _count++;
    this->setString(StringUtils::format("%d", _count));
}