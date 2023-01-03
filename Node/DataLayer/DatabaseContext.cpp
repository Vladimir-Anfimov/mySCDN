#include "DatabaseContext.h"
#include "Print.h"
#include <stdexcept>

using namespace Utils::Print;

DatabaseContext::DatabaseContext() {
    if(port == 0)
        handle_error("Set database port first");

    sprintf(db_path, DATABASE_PATH_FORMAT, port);

    if(!std::filesystem::exists(db_path))
    {
        handle_log("Db does not exist so it will be created");
        if(-1 == open(db_path, O_RDWR | O_CREAT | O_TRUNC, 0777))
            throw std::runtime_error("Error when trying to create the database");
        try {
            create_tables_setup();
        }
        catch (const std::exception& ex)
        {
            if(std::filesystem::exists(db_path))
                std::filesystem::remove(db_path);
            handle_error("%s", ex.what());
        }
    }
}

void DatabaseContext::create_tables_setup() {
    open_connection();
    try {
        execute("DROP TABLE cache;");
    }
    catch (std::exception& exp)
    {
        handle_log("Table cache could not be dropped.");
    }
    std::string create_tables = "CREATE TABLE cache(id INTEGER PRIMARY KEY,"
                                "available_until INTEGER NOT NULL,"
                                "url TEXT NOT NULL,"
                                "content TEXT NOT NULL,"
                                "port INTEGER NOT NULL);";
    execute(create_tables);
    close_connection();
}

void DatabaseContext::open_connection() {
    if(sqlite3_open(db_path, &connection) != SQLITE_OK)
    {
        close_connection();
        throw std::runtime_error("Error: Cannot open database: " +
                                 std::string(sqlite3_errmsg(connection)));
    }
    handle_log("Database has opened successfully");
}

void DatabaseContext::close_connection() {
    sqlite3_close(connection);
}

void DatabaseContext::execute(const std::string& command) {
    if(sqlite3_exec(connection, command.c_str(), nullptr, nullptr, &error_message) != SQLITE_OK)
    {
        sqlite3_free(error_message);
        throw std::runtime_error("Command " + command + " failed to execute with error" +
                                 std::string(error_message));
    }

    handle_log("Command %s executed successfully.", command.c_str());
}