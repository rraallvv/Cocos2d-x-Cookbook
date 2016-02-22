//
//  Count.h
//  Observer
//
//  Created by iOS on 2015/01/19.
//
//

#ifndef __Observer__Count__
#define __Observer__Count__

#include "cocos2d.h"

class Count : public cocos2d::Label
{
private:
    int _count;
    void countUp(float dt);
public:
    ~Count();
    virtual bool init();
    CREATE_FUNC(Count);
};

#endif /* defined(__Observer__Count__) */
