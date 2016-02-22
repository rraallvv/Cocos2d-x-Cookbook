#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    
    cocos2d::Sprite* makeSprite();
    void onEnter();
    void raycast(float dt);
    
    cocos2d::DrawNode* _drawNode;
    float _angle;
    cocos2d::PhysicsWorld* _world;
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    cocos2d::Node* _touchNode;
};

#endif // __HELLOWORLD_SCENE_H__
