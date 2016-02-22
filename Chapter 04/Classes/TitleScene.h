#ifndef __TitleScene_SCENE_H__
#define __TitleScene_SCENE_H__

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TitleScene);
};

#endif // __TitleScene_SCENE_H__
