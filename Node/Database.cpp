#include "Database.h"
#include "Print.h"

using namespace Utils::Print;

Database::Database() {
    if(!std::filesystem::exists(this->DATABASE_PATH))
    {
        handle_log("Db does not exist so it will be created\n");
        if(-1 == open(this->DATABASE_PATH.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0777))
            std::cout<<"Error: Creating db has failed\n";
    }

    if(sqlite3_open(this->DATABASE_PATH.c_str(), &this->connection))
    {
        handle_error("Error: Cannot open db");
        sqlite3_close(this->connection);
        return;
    }

    handle_log("Db has opened successfully");
    sqlite3_close(this->connection);
}

void Database::create_tables() {

}
