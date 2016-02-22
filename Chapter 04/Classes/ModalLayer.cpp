//
//  DirectorEx.cpp
//
//  Created by Akihiro Matsuura on 1/18/15.
//
//

#include "ModalLayer.h"

USING_NS_CC;

ModalLayer::ModalLayer()
{
}

ModalLayer::~ModalLayer()
{
}

bool ModalLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch *touch,Event*event)->bool{ return true; };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void ModalLayer::close(Ref* sender)
{
    this->removeFromParentAndCleanup(true);
}
