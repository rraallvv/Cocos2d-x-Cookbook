#include "HelloWorldScene.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"
#include "Platform.h"

USING_NS_CC;

//using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");

    //addChild(rootNode);
    /*
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create([](Acceleration* acc, Event* event){
        CCLOG("x=%f, y=%f, z=%f", acc->x, acc->y, acc->z);
    });
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    Device::setAccelerometerInterval(1.0f);
    */
    Device::setKeepScreenOn(true);
    
    int dpi = Device::getDPI();
    CCLOG("dpi = %d", dpi);
    
    std::string info = Configuration::getInstance()->getInfo();
    CCLOG("info = %s", info.c_str());
    
    int texutureSize = Configuration::getInstance()->getMaxTextureSize();
    CCLOG("max texture size = %d", texutureSize);
    
    const char* version = Platform::getAppVersion();
    CCLOG("application version = %s", version);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLOG("this platform is Android");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLOG("this platform is iOS");
#else 
    CCLOG("this platfomr is others");
#endif
    
    switch (Application::getInstance()->getTargetPlatform()) {
        case Application::Platform::OS_ANDROID:
            CCLOG("this device is Android");
            break;
        case Application::Platform::OS_IPHONE:
            CCLOG("this device is iPhone");
            break;
        case Application::Platform::OS_IPAD:
            CCLOG("this device is iPad");
            break;
        default:
            break;
    }
    
    return true;
}
