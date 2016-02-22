#include "HelloWorldScene.h"
#include "network/HttpClient.h"

USING_NS_CC;

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
    
    auto request = new network::HttpRequest();
    request->setUrl("https://www.google.com/images/srpr/logo11w.png");
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback([](network::HttpClient* sender, network::HttpResponse* response){
        if (!response->isSucceed()) {
            CCLOG("error");
            return;
        }
        
        std::vector<char>* buffer = response->getResponseData();
        for (unsigned int i = 0; i <buffer-> size (); i ++)
        {
            printf("%c", (* buffer)[i]);
        }
        printf("\n");
    });
    
    network::HttpClient::getInstance()->send(request);
    request->release();
    
    {
        auto request = new network::HttpRequest();
        request->setUrl("https://www.google.com/images/srpr/logo11w.png");
        request->setRequestType(network::HttpRequest::Type::GET);
        request->setResponseCallback([&](network::HttpClient* sender, network::HttpResponse* response){
            if (!response->isSucceed()) {
                CCLOG("error");
                return;
            }
            
            std::vector<char>* buffer = response->getResponseData();
            std::string path = FileUtils::getInstance()->getWritablePath() + "image.png";
            FILE* fp = fopen(path.c_str(), "wb");
            fwrite(buffer->data(), 1, buffer->size(), fp);
            fclose(fp);
            
            auto size = Director::getInstance()->getWinSize();
            auto sprite = Sprite::create(path);
            sprite->setPosition(size/2);
            this->addChild(sprite);
        });
        
        network::HttpClient::getInstance()->send(request);
        request->release();
    }
    
    return true;
}

