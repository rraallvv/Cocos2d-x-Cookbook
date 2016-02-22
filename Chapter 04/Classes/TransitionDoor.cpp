//
//  TransitionDoor.cpp
//
//  Created by Akihiro Matsuura on 5/29/14.
//
//

#include "TransitionDoor.h"

NS_CC_BEGIN

TransitionDoor::TransitionDoor()
{
    _gridProxy = NodeGrid::create();
    _gridProxy->retain();
}
TransitionDoor::~TransitionDoor()
{
    CC_SAFE_RELEASE(_gridProxy);
}

TransitionDoor* TransitionDoor::create(float t, Scene* scene)
{
    TransitionDoor* newScene = new (std::nothrow) TransitionDoor();
    if(newScene && newScene->initWithDuration(t, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionDoor::onEnter()
{
    TransitionScene::onEnter();
    
    _inScene->setVisible(true);
    
    _gridProxy->setTarget(_outScene);
    _gridProxy->onEnter();
    
    ActionInterval* split = action();
    ActionInterval* seq = (ActionInterval*)Sequence::create
    (
     split,
     CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
     StopGrid::create(),
     nullptr
     );
    
    _gridProxy->runAction(seq);
}

void TransitionDoor::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Scene::draw(renderer, transform, flags);
    _inScene->visit();
    _gridProxy->visit(renderer, transform, flags);
}

void TransitionDoor::onExit()
{
    _gridProxy->setTarget(nullptr);
    _gridProxy->onExit();
    TransitionScene::onExit();
}

ActionInterval* TransitionDoor:: action()
{
    return SplitDoor::create(_duration, 3);
}


ActionInterval* TransitionDoor::easeActionWithAction(ActionInterval * action)
{
    return EaseInOut::create(action, 3.0f);
}

SplitDoor* SplitDoor::create(float duration, unsigned int cols)
{
    SplitDoor *action = new (std::nothrow) SplitDoor();
    
    if (action)
    {
        if (action->initWithDuration(duration, cols))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }
    
    return action;
}

bool SplitDoor::initWithDuration(float duration, unsigned int cols)
{
    _cols = cols;
    return TiledGrid3DAction::initWithDuration(duration, Size(cols, 1));
}

SplitDoor* SplitDoor::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) SplitDoor();
    a->initWithDuration(_duration, _cols);
    a->autorelease();
    return a;
}

void SplitDoor::startWithTarget(Node *target)
{
    TiledGrid3DAction::startWithTarget(target);
    _winSize = Director::getInstance()->getWinSizeInPixels();
}

void SplitDoor::update(float time)
{
    for (unsigned int i = 0; i < _gridSize.width; ++i)
    {
        Quad3 coords = getOriginalTile(Vec2(i, 0));
        float    direction = 1;
        
        if ( (i % 2 ) == 0 )
        {
            direction = -1;
        }
        
        coords.bl.x += direction * _winSize.width/2 * time;
        coords.br.x += direction * _winSize.width/2 * time;
        coords.tl.x += direction * _winSize.width/2 * time;
        coords.tr.x += direction * _winSize.width/2 * time;
        
        setTile(Vec2(i, 0), coords);
    }
}
NS_CC_END