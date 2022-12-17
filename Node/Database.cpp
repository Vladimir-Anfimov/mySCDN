#include "Database.h"

Database::Database() {
    if(!std::filesystem::exists(this->DATABASE_PATH))
    {
        std::cout<<"Db does not exist so it will be created\n";
        if(-1 == open(this->DATABASE_PATH.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0777))
            std::cout<<"Error: Creating db has failed\n";
    }

    if(sqlite3_open(this->DATABASE_PATH.c_str(), &this->connection))
    {
        std::cout<<"Error: Cannot open db";
        sqlite3_close(this->connection);
        return;
    }

    std::cout<<"Db has opened successfully";
    sqlite3_close(this->connection);
}
