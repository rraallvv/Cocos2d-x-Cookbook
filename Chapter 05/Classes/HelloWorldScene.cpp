#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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
    /*
    Vector<MenuItem*> menuItems;
    
    for (int i=1; i<=3; i++) {
        std::string name = StringUtils::format("res/item%d.png", i);
        auto normalItem = Sprite::create(name);
        auto selectedItem = Sprite::create(name);
        selectedItem->setColor(Color3B::GRAY);
        auto item = MenuItemSprite::create(normalItem, selectedItem, [](Ref* sender){
            auto node = dynamic_cast<Node*>(sender);
            if (node!=nullptr) {
                CCLOG("tapped item %d", node->getTag());
            }
        });
        item->setTag(i);
        menuItems.pushBack(item);
    }
    
    auto size = Director::getInstance()->getVisibleSize();
    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(size/2);
    menu->alignItemsVertically();
    this->addChild(menu);
    */
    /*
    auto size = Director::getInstance()->getVisibleSize();
    
    auto button = ui::Button::create("res/normal.png", "res/selected.png", "res/disabled.png");
    button->setPosition(size/2);
    this->addChild(button);
    
    button->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("touch began");
                break;
            case ui::Widget::TouchEventType::MOVED:
                CCLOG("touch moved");
                break;
            case ui::Widget::TouchEventType::ENDED:
                CCLOG("touch ended");
                break;
            case ui::Widget::TouchEventType::CANCELED:
                CCLOG("touch canceled");
                break;
                
            default:
                break;
        }
    });
    */
    
    auto size = Director::getInstance()->getVisibleSize();
    /*auto checkbox = ui::CheckBox::create("res/check_box_normal.png",
                                         "res/check_box_normal_press.png",
                                         "res/check_box_active.png",
                                         "res/check_box_normal_disable.png",
                                         "res/check_box_active_disable.png");
    */
    /*auto checkbox = ui::CheckBox::create("res/check_box_normal.png",
                                         "res/check_box_active.png");
    checkbox->setPosition(size/2);
    this->addChild(checkbox);
    
    checkbox->addEventListener([](Ref* sender, ui::CheckBox::EventType type){
        switch (type) {
            case ui::CheckBox::EventType::SELECTED:
                CCLOG("selected checkbox");
                break;
            case ui::CheckBox::EventType::UNSELECTED:
                CCLOG("unselected checkbox");
                break;
            default:
                break;
        }
    });
    */
    
    // loading bar
    /*
    auto loadingbar = ui::LoadingBar::create("res/loadingbar.png");
    loadingbar->setPosition(size/2);
    loadingbar->setPercent(0);
    this->addChild(loadingbar);
    this->schedule([=](float delta){
        float percent = loadingbar->getPercent();
        percent++;
        loadingbar->setPercent(percent);
        if (percent>=100.0f) {
            this->unschedule("updateLoadingBar");
        }
    }, 0.1f, "updateLoadingBar");
    
    loadingbar->setDirection(ui::LoadingBar::Direction::RIGHT);
    */
    
    // slider
    /*
    auto slider = ui::Slider::create("res/sliderTrack.png", "res/sliderThumb.png");
    slider->setPosition(size/2);
    this->addChild(slider);
    slider->addEventListener([](Ref* sender, ui::Slider::EventType type){
        auto slider = dynamic_cast<ui::Slider*>(sender);
        if (type==ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            CCLOG("percentage = %d", slider->getPercent());
        }
    });
    
    slider->loadProgressBarTexture("res/sliderProgress.png");
    */
    
    // text field
    /*
    auto textField = ui::TextField::create("Enter your name", "Arial", 30);
    textField->setPosition(Vec2(size.width/2, size.height*0.75f));
    //textField->setPasswordEnabled(true);
    this->addChild(textField);
    textField->addEventListener([](Ref* sender, ui::TextField::EventType type){
        auto textField = dynamic_cast<ui::TextField*>(sender);
        switch (type) {
            case ui::TextField::EventType::ATTACH_WITH_IME:
                CCLOG("displayed keyboard");
                break;
            case ui::TextField::EventType::DETACH_WITH_IME:
                CCLOG("dismissed keyboard");
                break;
            case ui::TextField::EventType::INSERT_TEXT:
                CCLOG("inserted text : %s", textField->getString().c_str());
                break;
            case ui::TextField::EventType::DELETE_BACKWARD:
                CCLOG("deleted backward");
                break;
            default:
                break;
        }
    });
    */
    
    // scroll view
    /*
    auto scrollView = ui::ScrollView::create();
    scrollView->setPosition(Vec2());
    scrollView->setDirection(ui::ScrollView::Direction::BOTH);
    scrollView->setBounceEnabled(true);
    this->addChild(scrollView);
    
    auto sprite = Sprite::create("res/HelloWorld.png");
    sprite->setScale(2.0f);
    sprite->setPosition(sprite->getBoundingBox().size/2);
    scrollView->addChild(sprite);
    
    scrollView->setInnerContainerSize(sprite->getBoundingBox().size);
    scrollView->setContentSize(sprite->getContentSize());
    */
    
    // page view
    /*
    auto pageView = ui::PageView::create();
    pageView->setPosition(Vec2());
    pageView->setContentSize(size);
    this->addChild(pageView);
    
    for (int i=0; i<3; i++) {
        auto page = ui::Layout::create();
        page->setContentSize(pageView->getContentSize());
        
        auto sprite = Sprite::create("res/HelloWorld.png");
        sprite->setPosition(sprite->getContentSize()/2);
        page->addChild(sprite);
        
        pageView->insertPage(page, i);
    }
    
    pageView->addEventListener([](Ref* sender, ui::PageView::EventType type){
        if (type==ui::PageView::EventType::TURNING) {
            auto pageView = dynamic_cast<ui::PageView*>(sender);
            CCLOG("current page no =%zd", pageView->getCurPageIndex());
        }
    });
    */
    
    // list view
    auto listView = ui::ListView::create();
    listView->setPosition(Vec2(size.width/2 - 200, 0.0f));
    listView->setDirection(ui::ListView::Direction::VERTICAL);
    listView->setBounceEnabled(true);
    listView->setContentSize(size);
    this->addChild(listView);
    
    for (int i=0; i<20; i++) {
        auto layout = ui::Layout::create();
        layout->setContentSize(Size(400, 50));
        layout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
        layout->setBackGroundColor(Color3B::WHITE);
        
        auto button = ui::Button::create();
        button->setPosition(layout->getContentSize()/2);
        std::string name = StringUtils::format("list item %d", i);
        button->setTitleText(name);
        button->setTitleFontSize(30);
        button->setTitleColor(Color3B::BLACK);
        
        layout->addChild(button);
        listView->addChild(layout);
    }
    
    listView->addEventListener([](Ref* sender, ui::ListView::EventType type){
        auto listView = dynamic_cast<ui::ListView*>(sender);
        switch (type) {
            case ui::ListView::EventType::ON_SELECTED_ITEM_START:
                CCLOG("select item started");
                break;
            case ui::ListView::EventType::ON_SELECTED_ITEM_END:
                CCLOG("selected item : %zd", listView->getCurSelectedIndex());
                break;
            default:
                break;
        }
    });
    
    
    return true;
}
