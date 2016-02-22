#include "HelloWorldScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"

#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

#include "SQLiteManager.h"

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
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // parse json
    std::string str = "{\"hello\" : \"word\"}";
    CCLOG("%s\n", str.c_str());
    rapidjson::Document d;
    d.Parse<0>(str.c_str());
    if (d.HasParseError()) {
        CCLOG("GetParseError %s\n",d.GetParseError());
    } else if (d.IsObject() && d.HasMember("hello")) {
        CCLOG("%s\n", d["hello"].GetString());
    }
    
    // create json object
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value object(rapidjson::kObjectType);
    object.AddMember("int", 1, allocator);
    object.AddMember("double", 1.0, allocator);
    object.AddMember("bool", true, allocator);
    object.AddMember("hello", "ハロー", allocator);
    array.PushBack(object, allocator);
    
    document.AddMember("json", "json string", allocator);
    document.AddMember("array", array, allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    CCLOG("%s",buffer.GetString());
    
    // read json from file
    {
        std::string jsonData = FileUtils::getInstance()->getStringFromFile("res/test.json");
        CCLOG("%s\n", jsonData.c_str());
        rapidjson::Document d;
        d.Parse<0>(jsonData.c_str());
        if (d.HasParseError()) {
            CCLOG("GetParseError %s\n",d.GetParseError());
        } else {
            if (d.IsArray()) {
                for (rapidjson::SizeType i = 0; i < d.Size(); ++i) {
                    auto name = d[i]["name"].GetString();
                    auto age = d[i]["age"].GetInt();
                    CCLOG("name-%s, age=%d", name, age);
                }
            }
        }
    }
    
    // read plist
    FileUtils* util = FileUtils::getInstance();
    std::string path = util->fullPathForFilename("res/test.plist");
    ValueMap map = util->getValueMapFromFile(path);
    for (auto element : map) {
        std::string key = element.first;
        Value value = element.second;
        switch (value.getType()) {
            case Value::Type::BOOLEAN:
                CCLOG("%s, %s", key.c_str(), value.asBool()?"true":"false");
                break;
            case Value::Type::INTEGER:
                CCLOG("%s, %d", key.c_str(), value.asInt());
                break;
            case Value::Type::FLOAT:
                CCLOG("%s, %f", key.c_str(), value.asFloat());
                break;
            case Value::Type::DOUBLE:
                CCLOG("%s, %f", key.c_str(), value.asDouble());
                break;
            case Value::Type::STRING:
                CCLOG("%s, %s", key.c_str(), value.asString().c_str());
                break;
            default:
                break;
        }
    }
    
    // make plist
    {
        ValueMap map;
        for (int i=0; i<10; i++) {
            std::string key = StringUtils::format("key_%d", i);
            Value val = Value(i);
            map.insert(std::make_pair(key, val));
        }
        std::string fullpath = util->getWritablePath() + "test.xml";
        FileUtils::getInstance()->writeToFile(map, fullpath);
        CCLOG("%s", fullpath.c_str());
    }
    
    // parse xml
    {
        std::string path = util->fullPathForFilename("res/test.xml");
        XMLDocument *doc = new XMLDocument();
        XMLError error = doc->LoadFile(path.c_str());
        
        if (error == 0) {
            XMLElement *root = doc->RootElement();
            XMLElement *key = root->FirstChildElement("key");
            if (key) {
                CCLOG("key element = %s", key->GetText());
            }
            
            XMLElement *array = key->NextSiblingElement();
            XMLElement *child = array->FirstChildElement();
            while ( child ) {
                CCLOG("child element= %s", child->GetText());
                child = child->NextSiblingElement();
            }
            
            delete doc;
        }
    }
    
    // sqlite
    {
        SQLiteManager::getInstance()->insert("foo", "value1");
        std::string value = SQLiteManager::getInstance()->select("foo");
    }
    
    return true;
}

