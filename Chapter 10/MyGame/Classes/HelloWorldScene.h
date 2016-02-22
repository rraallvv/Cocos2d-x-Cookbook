#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void update(float dt);
    cocos2d::Vec2 _location;
    cocos2d::TMXTiledMap* _map;
    
    cocos2d::Vec2 getTilePosition(cocos2d::Vec2 point);
};

#endif // __HELLOWORLD_SCENE_H__
