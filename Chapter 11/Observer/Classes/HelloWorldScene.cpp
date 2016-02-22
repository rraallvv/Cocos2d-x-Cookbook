#include "HelloWorldScene.h"
#include "Count.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->schedule(schedule_selector(HelloWorld::countUp), 1.0f);
    
    return true;
}


bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    auto countLabel = Count::create();
    this->addChild(countLabel);
    countLabel->setPosition(touch->getLocation());
    
    return true;
}

void HelloWorld::countUp(float dt)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("TimeCount");
}
