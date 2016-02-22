#include "HelloWorldScene.h"
#include "ZipUtils.h"
#include "PhysicsShapeCache.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = HelloWorld::create();
    PhysicsWorld* world = scene->getPhysicsWorld();
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*
    // use ecrypted texture
    ZipUtils::setPvrEncryptionKey(0x5f2c492e, 0x635eaaf8, 0xe5a4ee49, 0x32ffe0cf);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/encrypted.plist");
    auto sprite = Sprite::createWithSpriteFrameName("run_01.png");
    sprite->setPosition(Vec2(visibleSize/2)+origin);
    this->addChild(sprite);
    */
    
    /*
    // tiled map
    _map = TMXTiledMap::create("res/desert.tmx");
    _map->setPosition(Vec2()+origin);
    this->addChild(_map);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    */
    
    /*
    // use bitmap fonts
    auto label = Label::createWithBMFont("fonts/arcade.fnt", "Cocos2d-x");
    label->setPosition(Vec2(visibleSize/2)+origin);
    this->addChild(label);
    */
    
    // use physics editor
    auto wall = Node::create();
    auto wallBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    wallBody->setContactTestBitmask(true);
    wall->setPhysicsBody(wallBody);
    wall->setPosition(Vec2(visibleSize/2)+origin);
    this->addChild(wall);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    PhysicsShapeCache::getInstance()->addShapesWithFile("res/gear.plist");

    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    /*
    auto touchPoint = touch->getLocation();
    auto tilePoint = this->getTilePosition(touchPoint);
    TMXLayer* groundLayer = _map->getLayer("Ground");
    int gid = groundLayer->getTileGIDAt(tilePoint);
    if (gid!=0) {
        auto properties = _map->getPropertiesForGID(gid).asValueMap();
        if (properties.find("isTree")!=properties.end()) {
            if(properties.at("isTree").asBool()) {
                CCLOG("it's tree!");
            }
        }
    }
     */
    
    auto touchPoint = touch->getLocation();
    auto body = PhysicsShapeCache::getInstance()->createBodyWithName("gear");
    auto sprite = Sprite::create("res/gear.png");
    sprite->setPhysicsBody(body);
    sprite->setPosition(touchPoint);
    this->addChild(sprite);
    
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto center = Vec2(size/2)+origin;
    _location = touch->getLocation() - center;
    _location.x = floorf(_location.x);
    _location.y = floorf(_location.y);
    this->scheduleUpdate();
}

void HelloWorld::update(float dt)
{
    auto mapSize = _map->getContentSize();
    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto currentLocation = _map->getPosition();
    if (_location.x > 0) {
        currentLocation.x--;
        _location.x--;
    } else if (_location.x < 0) {
        currentLocation.x++;
        _location.x++;
    }
    if (_location.y > 0) {
        currentLocation.y--;
        _location.y--;
    } else if (_location.y < 0) {
        currentLocation.y++;
        _location.y++;
    }
    
    if (currentLocation.x > origin.x) {
        currentLocation.x = origin.x;
    } else if (currentLocation.x < winSize.width + origin.x - mapSize.width) {
        currentLocation.x = winSize.width + origin.x - mapSize.width;
    }
    if (currentLocation.y > origin.y) {
        currentLocation.y = origin.y;
    } else if (currentLocation.y < winSize.height + origin.y - mapSize.height) {
        currentLocation.y = winSize.height + origin.y - mapSize.height;
    }
    
    _map->setPosition(currentLocation);
    if (fabsf(_location.x)<1.0f && fabsf(_location.y)<1.0f) {
        this->unscheduleUpdate();
    }
}

Vec2 HelloWorld::getTilePosition(Vec2 point)
{
    auto mapContentSize = _map->getContentSize();
    auto tilePoint = point - _map->getPosition();
    auto tileSize = _map->getTileSize();
    auto mapRowCol = _map->getMapSize();
    auto scale = mapContentSize.width / (mapRowCol.width * tileSize.width);
    tilePoint.x = floorf(tilePoint.x / (tileSize.width * scale));
    //tilePoint.y = floorf(tilePoint.y / (tileSize.height * scale));
    tilePoint.y = floorf((mapContentSize.height - tilePoint.y)/(tileSize.height*scale));
    return tilePoint;
}