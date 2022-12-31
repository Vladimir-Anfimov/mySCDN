#include "DatabaseContext.h"
#include "Print.h"
#include <stdexcept>

using namespace Utils::Print;

DatabaseContext::DatabaseContext() {
    if(!std::filesystem::exists(this->DATABASE_PATH))
    {
        handle_log("Db does not exist so it will be created");
        if(-1 == open(this->DATABASE_PATH.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0777))
            throw std::runtime_error("Error when trying to create the database");
        try {
            create_tables_setup();
        }
        catch (const std::exception& ex)
        {
            if(std::filesystem::exists(this->DATABASE_PATH))
                std::filesystem::remove(this->DATABASE_PATH);
            handle_error("%s", ex.what());
        }
    }
}

void DatabaseContext::create_tables_setup() {
    open_connection();
    std::string create_tables = "CREATE TABLE cache(id INTEGER PRIMARY KEY,"
                                         "available_until INTEGER NOT NULL,"
                                         "url TEXT NOT NULL,"
                                         "content TEXT,"
                                         "port INTEGER)";
    execute(create_tables);
    close_connection();
}

void DatabaseContext::open_connection() {
    if(sqlite3_open(this->DATABASE_PATH.c_str(), &this->connection) != SQLITE_OK)
    {
        close_connection();
        throw std::runtime_error("Error: Cannot open database: " +
                                 std::string(sqlite3_errmsg(this->connection)));
    }
    handle_log("Database has opened successfully");
}

void DatabaseContext::close_connection() {
    sqlite3_close(this->connection);
}

void DatabaseContext::execute(const std::string& command) {
    if(sqlite3_exec(this->connection, command.c_str(), nullptr, nullptr, &this->error_message) != SQLITE_OK)
    {
        sqlite3_free(this->error_message);
        close_connection();
        throw std::runtime_error("Command " + command + " failed to execute with error" +
                                std::string(error_message));
    }

    handle_log("Command %s executed successfully.", command.c_str());
}
