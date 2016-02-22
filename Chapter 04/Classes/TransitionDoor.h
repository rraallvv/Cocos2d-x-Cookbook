//
//  TransitionDoor.h
//
//  Created by Akihiro Matsuura on 5/29/14.
//
//

#ifndef __TRANSITIONDOOR_H__
#define __TRANSITIONDOOR_H__

#include "cocos2d.h"

NS_CC_BEGIN

class CC_DLL TransitionDoor : public TransitionScene , public TransitionEaseScene
{
public:
    static TransitionDoor* create(float t, Scene* scene);
    
    virtual ActionInterval* action();
    virtual void onEnter() override;
    virtual ActionInterval * easeActionWithAction(ActionInterval * action) override;
    virtual void onExit() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
CC_CONSTRUCTOR_ACCESS:
    TransitionDoor();
    virtual ~TransitionDoor();
    
protected:
    NodeGrid* _gridProxy;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionDoor);
};

class CC_DLL SplitDoor : public TiledGrid3DAction
{
public:
    /**
     * creates the action with the number of columns to split and the duration
     * @param duration in seconds
     */
    static SplitDoor* create(float duration, unsigned int cols);
    
    // Overrides
    virtual SplitDoor* clone() const override;
    /**
     * @param time in seconds
     */
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitDoor() {}
    virtual ~SplitDoor() {}
    
    /** initializes the action with the number of columns to split and the duration */
    bool initWithDuration(float duration, unsigned int cols);
    
protected:
    unsigned int _cols;
    Size _winSize;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(SplitDoor);
};

NS_CC_END

#endif /* defined(__TRANSITIONDOOR_H__) */
