//
//  DirectorEx.h
//
//  Created by Akihiro Matsuura on 1/18/15.
//
//

#ifndef __DirectorEx__
#define __DirectorEx__

#include "cocos2d.h"

USING_NS_CC;

class DirectorEx : public Director
{
public:
    Scene* previousScene(void);
    void popScene(Scene* trans);
};

#endif /* defined(__DirectorEx__) */
