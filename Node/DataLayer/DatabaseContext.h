#pragma once

#include <iostream>
#include <sqlite3.h>
#include <memory>
#include <filesystem>
#include <fcntl.h>
#include <climits>

class DatabaseContext {
private:
    char *error_message = nullptr;
    inline const static char *const DATABASE_PATH_FORMAT = "./node_sql_port_%d.db";
    void create_tables_setup();
    char db_path[PATH_MAX];
protected:
    sqlite3* connection;
    void open_connection();
    void close_connection();
    void execute(const std::string& command);
public:
    DatabaseContext();
    inline static int port = 0;
};
