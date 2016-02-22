//
//  SQLiteManager.h
//
//  Created by Akihiro Matsuura on 6/21/15.
//  Copyright (c) 2015 Syuhari, Inc. All rights reserved.
//

#ifndef __Syuhari__SQLiteManager__
#define __Syuhari__SQLiteManager__

#include "cocos2d.h"
#include "sqlite/sqlite3.h"

class SQLiteManager {
private:
    SQLiteManager();
    static SQLiteManager* instance;
    sqlite3 *_db;
    bool open();
    void close();
public:
    virtual ~SQLiteManager();
    static SQLiteManager* getInstance();
    
    void insert(std::string key, std::string value);
    std::string select(std::string key);
};

#endif /* defined(__Syuhari__SQLiteManager__) */
