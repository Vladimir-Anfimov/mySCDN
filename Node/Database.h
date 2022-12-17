#ifndef NODE_DATABASE_H
#define NODE_DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <memory>
#include <filesystem>
#include <fcntl.h>

class Database {
    sqlite3* connection;
    inline const static std::string DATABASE_PATH = "../node_sql.db";
public:
    Database();
};


#endif //NODE_DATABASE_H
