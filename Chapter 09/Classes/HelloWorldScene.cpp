#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    
    PhysicsWorld* world = scene->getPhysicsWorld();
    //auto gravity = Vec2(0, 98.0f);
    //world->setGravity(gravity);
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _world = Director::getInstance()->getRunningScene()->getPhysicsWorld();
    // wall
    auto wall = Node::create();
    auto wallBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    wallBody->setContactTestBitmask(true);
    wall->setPhysicsBody(wallBody);
    wall->setPosition(Vec2(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    addChild(wall);
    
    auto sp1 = this->makeSprite();
    sp1->setPosition(visibleSize/2);
    this->addChild(sp1);
    
    auto sp2 = this->makeSprite();
    sp2->setPosition(Vec2(visibleSize.width/2+2, visibleSize.height));
    this->addChild(sp2);
    
    // joint: gear
    {
        auto body1 = sp1->getPhysicsBody();
        auto body2 = sp2->getPhysicsBody();
        auto pin1 = PhysicsJointPin::construct(body1, wallBody, sp1->getPosition());
        _world->addJoint(pin1);
        auto pin2 = PhysicsJointPin::construct(body2, wallBody, sp2->getPosition());
        _world->addJoint(pin2);
        //auto joint = PhysicsJointMotor::construct(body1, body2, 10.0f);
        auto joint = PhysicsJointGear::construct(body1, body2, 0.0f, 2.0f);
        _world->addJoint(joint);
    }
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [](PhysicsContact& contact){
        //CCLOG("contact begin");
        /*auto shapeA = contact.getShapeA();
         auto bodyA = shapeA->getBody();
         
         auto shapeB = contact.getShapeB();
         auto bodyB = shapeA->getBody();*/
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create([=](Acceleration* acc, Event* event){
        CCLOG("x=%f, y=%f, z=%f", acc->x, acc->y, acc->z);
        auto gravity = Vec2(acc->x*100.0f, acc->y*100.0f);
        _world->setGravity(gravity);
    });
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    /*
    PhysicsRayCastCallbackFunc func = [](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)->bool
    {
        CCLOG("ray cast: point %f, %f", info.contact.x, info.contact.y);
        return true;
    };
    
    auto center = Vec2(visibleSize);
    auto endPoint = Vec2(0, 0);
    world->rayCast(func, center, endPoint, nullptr);
    */
    
    _angle = 0.0f;
    //this->schedule(schedule_selector(HelloWorld::raycast), 0.1f);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto shapes = _world->getShapes(location);
    if (shapes.size()<=0) {
        return false;
    }
    
    PhysicsShape* shape = shapes.front();
    PhysicsBody* body = shape->getBody();
    
    if (body != nullptr)
    {
        _touchNode = Node::create();
        auto touchBody = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
        _touchNode->setPhysicsBody(touchBody);
        _touchNode->getPhysicsBody()->setDynamic(false);
        _touchNode->setPosition(location);
        this->addChild(_touchNode);
        PhysicsJointPin* joint = PhysicsJointPin::construct(touchBody, body, location);
        joint->setMaxForce(5000.0f * body->getMass());
        _world->addJoint(joint);
        
        return true;
    }
    
    return false;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    if (_touchNode!=nullptr) {
        _touchNode->setPosition(touch->getLocation());
    }
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    if (_touchNode!=nullptr) {
        _touchNode->removeFromParent();
        _touchNode = nullptr;
    }
}

#define MAX_MULTI_RAYCAST_NUM 5

void HelloWorld::raycast(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(visibleSize/2) + origin;
    Vec2 d(300 * cosf(_angle), 300 * sinf(_angle));
    Vec2 point2 = center + d;
    if (_drawNode)
    {
        removeChild(_drawNode);
    }
    _drawNode = DrawNode::create();
    
    Vec2 points[MAX_MULTI_RAYCAST_NUM];
    int num = 0;
    PhysicsRayCastCallbackFunc func = [&points, &num](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)->bool
    {
        if (num < MAX_MULTI_RAYCAST_NUM)
        {
            points[num++] = info.contact;
        }
        return true;
    };
    
    _world->rayCast(func, center, point2, nullptr);
    
    _drawNode->drawSegment(center, point2, 1, Color4F::RED);
    for (int i = 0; i < num; ++i)
    {
        _drawNode->drawDot(points[i], 3, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
    }
    addChild(_drawNode);
    
    _angle += 1.5f * (float)M_PI / 180.0f;
}

Sprite* HelloWorld::makeSprite()
{
    auto sprite = Sprite::create("CloseNormal.png");
    auto physicsBody = PhysicsBody::createCircle(sprite->getContentSize().width/2);
    physicsBody->setDynamic(true);
    physicsBody->setContactTestBitmask(true);
    sprite->setPhysicsBody(physicsBody);
    
    return sprite;
}
