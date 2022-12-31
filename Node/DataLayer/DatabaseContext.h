#pragma once

#include <iostream>
#include <sqlite3.h>
#include <memory>
#include <filesystem>
#include <fcntl.h>

class DatabaseContext {
private:
    char *error_message = nullptr;
    inline const static std::string DATABASE_PATH = "./node_sql.db";
    void create_tables_setup();
protected:
    sqlite3* connection;
    void open_connection();
    void close_connection();
    void execute(const std::string& command);
public:
    DatabaseContext();
};


