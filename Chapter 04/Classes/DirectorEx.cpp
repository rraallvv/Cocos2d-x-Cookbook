//
//  DirectorEx.cpp
//
//  Created by Akihiro Matsuura on 1/18/15.
//
//

#include "DirectorEx.h"

Scene* DirectorEx::previousScene()
{
    ssize_t sceneCount = _scenesStack.size();
    if (sceneCount <= 1) {
        return nullptr;
    }
    return _scenesStack.at(sceneCount-2);
}

void DirectorEx::popScene(Scene* trans)
{
    _scenesStack.popBack();
    ssize_t sceneCount = _scenesStack.size();
    if (sceneCount==0) {
        end();
    } else {
        _sendCleanupToScene = true;
        _nextScene = trans;
    }
}