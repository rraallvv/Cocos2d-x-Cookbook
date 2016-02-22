#include "HelloWorldScene.h"

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
    
    auto size = Director::getInstance()->getWinSize();
    auto label = Label::createWithSystemFont("HelloWorld", "Arial", 40);
    label->setPosition(size/2);
    this->addChild(label);

    
    return true;
}

