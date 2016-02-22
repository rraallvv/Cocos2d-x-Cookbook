//
//  ModalLayer.h
//
//  Created by Akihiro Matsuura on 1/18/15.
//
//

#ifndef __ModalLayer__
#define __ModalLayer__

#include "cocos2d.h"

USING_NS_CC;

class ModalLayer : public Layer
{
public:
    ModalLayer();
    ~ModalLayer();
    bool init();
    CREATE_FUNC(ModalLayer);
    void close(Ref* sender=nullptr);
};

#endif /* defined(__ModalLayer__) */
