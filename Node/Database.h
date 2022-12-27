#pragma once

#include <iostream>
#include <sqlite3.h>
#include <memory>
#include <filesystem>
#include <fcntl.h>

class Database {
private:
    sqlite3* connection;
    inline const static std::string DATABASE_PATH = "../node_sql.db";
    void create_tables();
public:
    Database();
};


