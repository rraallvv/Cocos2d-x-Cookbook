#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace experimental::ui;
using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto videoPlayer = VideoPlayer::create();
    
    videoPlayer->setContentSize(visibleSize);
    videoPlayer->setPosition(visibleSize/2);
    videoPlayer->setKeepAspectRatioEnabled(true);
    this->addChild(videoPlayer);
    
    videoPlayer->addEventListener([](Ref *sender, VideoPlayer::EventType eventType) {
        switch (eventType) {
            case VideoPlayer::EventType::PLAYING:
                CCLOG("PLAYING");
                break;
            case VideoPlayer::EventType::PAUSED:
                CCLOG("PAUSED");
                break;
            case VideoPlayer::EventType::STOPPED:
                CCLOG("STOPPED");
                break;
            case VideoPlayer::EventType::COMPLETED:
                CCLOG("COMPLETED");
                break;
            default:
                break;
        }
    });
    
    videoPlayer->setFileName("res/splash.mp4");
    videoPlayer->play();

    return true;
}
