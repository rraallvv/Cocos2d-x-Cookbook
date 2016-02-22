#include "HelloWorldScene.h"
#include "external/unzip/unzip.h"
#include "sqlite3.h"

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
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // use ecrypted texture
    ZipUtils::setPvrEncryptionKey(0x5f2c492e, 0x635eaaf8, 0xe5a4ee49, 0x32ffe0cf);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/encrypted.plist");
    auto sprite = Sprite::createWithSpriteFrameName("run_01.png");
    sprite->setPosition(Vec2(visibleSize/2)+origin);
    this->addChild(sprite);
    
    this->uncompress("cocos2d-x");
    
    std::string dbname = "data.db";
    std::string path = FileUtils::getInstance()->getWritablePath() + dbname;
    CCLOG("%s", path.c_str());
    
    sqlite3 *database = nullptr;
    if ((sqlite3_open(path.c_str(), &database) != SQLITE_OK)) {
        sqlite3_close(database);
        CCLOG("open error");
    } else {
        const char* key = "pass_phrase";
        sqlite3_key(database, key, (int)strlen(key));
        
        // sql: create table
        char create_sql[] = "CREATE TABLE sample ( "
        "               id     INTEGER PRIMARY KEY, "
        "               key    TEXT    NOT NULL,    "
        "               value  INTEGER NOT NULL     "
        "             )                             ";
        
        // create table
        sqlite3_exec(database, create_sql, 0, 0, NULL);
        
        // insert data
        char insert_sql[] = "INSERT INTO sample ( id, key, value )"
        "            values (%d, '%s', '%d')     ";
        
        char insert_record[3][256];
        sprintf( insert_record[0], insert_sql, 0, "test" , 300 );
        sprintf( insert_record[1], insert_sql, 1, "hoge" , 100 );
        sprintf( insert_record[2], insert_sql, 2, "foo" , 200 );
        
        for(int i = 0; i < 3; i++ ) {
            sqlite3_exec(database, insert_record[i], 0, 0, NULL);
        }
        
        // select data
        sqlite3_stmt *stmt = nullptr;
        
        std::string sql = "SELECT value FROM sample WHERE key='test'";
        if (sqlite3_prepare_v2(database, sql.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                int value = sqlite3_column_int(stmt, 0);
                CCLOG("value = %d", value);
            } else {
                CCLOG("error , error=%s", sqlite3_errmsg(database));
            }
        }
        
        sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
        sqlite3_close(database);
    }
    
    return true;
}



#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

bool HelloWorld::uncompress(const char* password)
{
    // Open the zip file
    std::string outFileName = FileUtils::getInstance()->fullPathForFilename("encrypt.zip");
    unzFile zipfile = unzOpen(outFileName.c_str());
    int ret = unzOpenCurrentFilePassword(zipfile, password);
    if (ret!=UNZ_OK)
    {
        CCLOG("can not open zip file %s", outFileName.c_str());
        return false;
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("can not read file global info of %s", outFileName.c_str());
        unzClose(zipfile);
        return false;
    }
    
    CCLOG("start uncompressing");
    
    // Loop to extract all files.
    uLong i;
    for (i = 0; i < global_info.number_entry; ++i)
    {
        // Get info about current file.
        unz_file_info fileInfo;
        char fileName[MAX_FILENAME];
        if (unzGetCurrentFileInfo(zipfile,
                                  &fileInfo,
                                  fileName,
                                  MAX_FILENAME,
                                  nullptr,
                                  0,
                                  nullptr,
                                  0) != UNZ_OK)
        {
            CCLOG("can not read file info");
            unzClose(zipfile);
            return false;
        }
        
        CCLOG("filename = %s", fileName);
        
        unzCloseCurrentFile(zipfile);
        
        // Goto next entry listed in the zip file.
        if ((i+1) < global_info.number_entry)
        {
            if (unzGoToNextFile(zipfile) != UNZ_OK)
            {
                CCLOG("can not read next file");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    CCLOG("end uncompressing");
    unzClose(zipfile);
    
    return true;
}