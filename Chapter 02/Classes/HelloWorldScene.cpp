#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
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
    
    auto size = Director::getInstance()->getWinSize();
    
    auto layer = LayerColor::create(Color4B::GRAY);
    this->addChild(layer);
    
    auto label = Label::createWithTTF("Shadow", "fonts/Marker Felt.ttf", 40);
    label->setPosition(Vec2(size.width/2, size.height/3*2));
    this->addChild(label);
    label->enableShadow(Color4B::RED, Size(5,5), 0);
    
    auto label2 = Label::createWithTTF("Shadow & Outline", "fonts/Marker Felt.ttf", 40);
    label2->setPosition(Vec2(size.width/2, size.height/3));
    this->addChild(label2);
    
    label2->enableShadow(Color4B::RED, Size(10,-10), 0);
    label2->enableOutline(Color4B::BLACK, 5);
    
    
    /*
    TTFConfig config;
    config.fontFilePath = "fonts/Marker Felt.ttf";
    config.fontSize = 40.0f;
    config.glyphs = GlyphCollection::DYNAMIC;
    config.outlineSize = 1;
    config.customGlyphs = nullptr;
    config.distanceFieldEnabled = false;
    
    auto label = Label::createWithTTF(config, "True Type Font");
    label->setPosition(size/2);
    this->addChild(label);
    label->setColor(Color3B::RED);
    */
    /*
    sec = 0;
    std::string secString = StringUtils::toString(sec);
    auto label = Label::createWithSystemFont(secString, "Arial", 40);
    label->setPosition(size/2);
    this->addChild(label);
    
    this->schedule([=](float dt) {
        sec++;
        std::string secString = StringUtils::toString(sec);
        label->setString(secString);
    }, 1.0f, "myCallbackKey");
    */
    /*
    auto sprite = Sprite::create("res/run_01.png");
    sprite->setPosition(size/2);
    this->addChild(sprite);
    sprite->setScale(0.2f);
    
    auto cache = AnimationCache::getInstance();
    cache->addAnimationsWithFile("res/run_animation.plist");
    auto animation = cache->getAnimation("run");
    auto action = Animate::create(animation);
    sprite->runAction(action);
    */
    /*
    auto sprite = Sprite::create("res/run_01.png");
    sprite->setPosition(Vec2(size.width/2, size.height));
    sprite->setAnchorPoint(Vec2(0.5f, 0.0f));
    this->addChild(sprite);
    sprite->setScale(0.2f);
    
    auto drop = MoveTo::create(3.0f, Vec2(size.width/2, 0));
    auto ease = EaseOut::create(drop, 10.1f);
    sprite->runAction(ease);
    */
    //auto origin = Director::getInstance()->getVisibleOrigin();
    /*
    {
        auto sprite = Sprite::create("res/run_01.png");
        sprite->setPosition(Vec2(300, 200));
        this->addChild(sprite);
        sprite->setScale(0.2f);
    }
    
    {
        auto sprite = Sprite::create("res/run_01.png");
        sprite->setPosition(Vec2(400, 200));
        this->addChild(sprite);
        sprite->setScale(0.2f);
        sprite->setColor(Color3B(255,0,0));
        
    }
    
    int i = 100;
    std::string int_string = StringUtils::toString(i);
    float j = 123.4f;
    std::string float_string = StringUtils::toString(j);
    CCLOG("i=%s, j=%s", int_string.c_str(), float_string.c_str());
    */
     /*
    {
        auto sprite = Sprite::create("res/run_01.png");
        sprite->setPosition(Vec2(500, 200));
        this->addChild(sprite);
        sprite->setScale(0.2f);
        sprite->setScaleY(0.2f*0.5f);
    }
    
    {
        auto sprite = Sprite::create("res/run_01.png");
        sprite->setPosition(Vec2(650, 200));
        this->addChild(sprite);
        sprite->setScale(0.2f);
        sprite->setScale(0.2f*2.0f, 0.2f*0.5f);
    }
    */
    
    /*
    auto delay = DelayTime::create(2.0f);
    auto move = MoveBy::create(2.0f, Vec2(100, 0));
    auto rotate = RotateBy::create(2.0f, 360.0f);
    auto fade = FadeOut::create(2.0f);
    auto spawn = Spawn::create(rotate, fade, nullptr);
    auto action = Sequence::create(move, spawn, nullptr);
    //auto action = Sequence::create(sequence, sequence->reverse(), nullptr);
    //auto action = RepeatForever::create(rotate);
    sprite->runAction(action);
    */
    
    /*auto func = CallFunc::create([](){
        CCLOG("finished actions");
    });*/
    //auto func = CallFunc::create(CC_CALLBACK_0(HelloWorld::finishedAction, this));
    /*auto func = CallFuncN::create([=](Ref* sender){
        CCLOG("callback");
        Sprite* sprite = dynamic_cast<Sprite*>(sender);
        sprite->runAction(move->reverse());
    });
    auto action = Sequence::create(move, rotate, func, nullptr);
    sprite->runAction(action);
    */
    // texture atlas
    /*
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("res/running.plist");
    auto sprite = Sprite::createWithSpriteFrameName("run_01.png");
    sprite->setPosition(size/2);
    sprite->setScale(0.2f);
    this->addChild(sprite);
    */
    
    // batch node
    /*auto batchNode = SpriteBatchNode::create("res/run_01.png");
    this->addChild(batchNode);
    for (int i=0; i<300; i++) {
        auto sprite = Sprite::createWithTexture(batchNode->getTexture());
        sprite->setScale(0.2f);
        float x = CCRANDOM_0_1() * size.width;
        float y = CCRANDOM_0_1() * size.height;
        sprite->setPosition(Vec2(x,y));
        batchNode->addChild(sprite);
    }
    */
    
    //sprite->setColor(Color3B(255, 0, 0));
    /*
    Rect rect = sprite->getBoundingBox();
    Size contentSize = sprite->getContentSize();
    CCLOG("rect size=%f,%f, content size=%f,%f", rect.size.width, rect.size.height, contentSize.width, contentSize.height);
    */
    /*
    auto sprite3d = Sprite3D::create("res/girl.c3b");
    sprite3d->setPosition(Vec2(size.width/2, 100));
    this->addChild(sprite3d);
    
    auto animation3d = Animation3D::create("res/girl.c3b");
    auto animate3d = Animate3D::create(animation3d);
    auto repeat = RepeatForever::create(animate3d);
    sprite3d->runAction(repeat);
    
    sprite3d->setPositionX(size.width);
    auto move1 = MoveBy::create(5.0f, Vec2(-size.width, 0));
    auto move2 = MoveBy::create(5.0f, Vec2(size.width, 0));
    auto seq = Sequence::create(move1, move2, NULL);
    auto loop = RepeatForever::create(seq);
    sprite3d->runAction(loop);
    */
    
    /*{
        auto rect = Rect::ZERO;
        rect.size = sprite->getContentSize();
        Vector<AnimationFrame*> frames;
        
        // animation
        for (int i=1; i<=8; i++) {
            std::string name = StringUtils::format("res/run_%02d.png", i);
            auto frame = SpriteFrame::create(name.c_str(), rect);
            ValueMap info;
            auto animationFrame = AnimationFrame::create(frame, i, info);
            frames.pushBack(animationFrame);
        }
        auto animation = Animation::create(frames, 0.1f);
        animation->setDelayPerUnit(0.1f);
        animation->setRestoreOriginalFrame(true);
        animation->setLoops(-1);
        auto action = Animate::create(animation);
        sprite->runAction(action);
    }*/
    
    
    /*{
        // animation
        auto animation = Animation::create();
        for (int i=1; i<=8; i++) {
            std::string name = StringUtils::format("res/run_%02d.png", i);
            animation->addSpriteFrameWithFile(name.c_str());
        }
        animation->setDelayPerUnit(0.1f);
        animation->setRestoreOriginalFrame(true);
        animation->setLoops(-1);
        auto action = Animate::create(animation);
        sprite->runAction(action);
    }*/
    
    // drawing a shape
    /*
     static const Color4F WHITE;
     static const Color4F YELLOW;
     static const Color4F BLUE;
     static const Color4F GREEN;
     static const Color4F RED;
     static const Color4F MAGENTA;
     static const Color4F BLACK;
     static const Color4F ORANGE;
     static const Color4F GRAY;
    */
    
    /*
    auto size = Director::getInstance()->getWinSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto draw = DrawNode::create();
    this->addChild(draw);
    //draw->drawDot(Vec2(size/2), 10.0f, Color4F::WHITE);
    */
    //draw->drawLine(Vec2(300, 200), Vec2(600, 200), Color4F::WHITE);
    //draw->drawSegment(Vec2(300, 100), Vec2(600, 100), 10.0f, Color4F::WHITE);
    
    // drawing circles
    //draw->drawCircle(Vec2(300, size.height/2), 50.0f, 1.0f, 10, true, 1.0f, 1.0f, Color4F::WHITE);
    //draw->drawCircle(Vec2(450, size.height/2), 50.0f, 1.0f, 100, false, 1.0f, 1.0f, Color4F::WHITE);
    //draw->drawSolidCircle(Vec2(600, size.height/2), 50.0f, 1.0f, 100, 1.0f, 1.0f, Color4F::WHITE);
    
    // drawing rects
    //draw->drawRect(Vec2(240, 100), Vec2(340,200), Color4F::WHITE);
    //draw->drawSolidRect(Vec2(480, 100), Vec2(580, 200), Color4F::WHITE);
    
    // drawing triangle
    //draw->drawTriangle(Vec2(380,100), Vec2(480, 200), Vec2(580, 100), Color4F::WHITE);


    // Bezier curve
    // 第4引き数の数値 segment はカーブの滑らかさ
    //draw->drawQuadBezier(Vec2(240, 200), Vec2(480, 320), Vec2(720, 200), 24, Color4F::WHITE);
    //draw->drawCubicBezier(Vec2(240, 100), Vec2(240, 200), Vec2(720, 200), Vec2(720, 100), 24, Color4F::WHITE);

    // draw a polygon
    /*
    std::vector<Vec2>verts;
    verts.push_back(Vec2(380,100));
    verts.push_back(Vec2(380,200));
    verts.push_back(Vec2(480,250));
    verts.push_back(Vec2(580,200));
    verts.push_back(Vec2(580,100));
    verts.push_back(Vec2(480,50));
    draw->drawPolygon(&verts[0], verts.size(), Color4F::RED, 5.0f, Color4F::GREEN);
    */

    
    /*
    {
        auto points = PointArray::create(10);
        draw->drawCatmullRom(points, 10, Color4F::ORANGE);
    }
    */
    /*
    {
        _points = new PointArray();
        _points->initWithCapacity(10000);
        //_points->addControlPoint(Vec2(0,size.height/2));
        //_points->addControlPoint(Vec2(size.width/2,size.height));
        //_points->addControlPoint(Vec2(size.width,size.height/2));
        //draw->drawCardinalSpline(_points, 10.0f, 100, Color4F::ORANGE);
        _draw = draw;
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        listener->onTouchMoved = [&](Touch* touch, Event* event){
            //if (_points->count()>=1000) {
            //    return;
            //}
            _points->addControlPoint(touch->getLocation());
            //if (_points->count()>3) {
            //    _draw->drawCatmullRom(_points, 100, Color4F::RED);
            _draw->drawCardinalSpline(_points, 10.0f, 100, Color4F::ORANGE);
            //}
        };
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
    }
    */
    return true;
}

void HelloWorld::finishedAction()
{
    CCLOG("finished action");
}

void HelloWorld::callback(Ref* sender)
{
    CCLOG("callback");
}
