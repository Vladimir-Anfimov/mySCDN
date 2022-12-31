#pragma once
#include "DatabaseContext.h"
#include <stdexcept>
#include "Print.h"
#include <type_traits>
#include "../DTO/ExternalCacheCreateDto.h"
#include "../DTO/ExternalCacheRetrieveDto.h"

using namespace Utils::Print;

class ExternalCacheRepository: public DatabaseContext  {
public:
    void insert(const ExternalCacheCreateDto& cache_item);

    template <class T>
    ExternalCacheRetrieveDto* find_by_value(const std::string& param_name, const T& value);

    void update(const ExternalCacheRetrieveDto& external_cache);
    ExternalCacheRepository();
    ~ExternalCacheRepository();
};


ExternalCacheRepository::ExternalCacheRepository(): DatabaseContext() {
    open_connection();
}

void ExternalCacheRepository::insert(const ExternalCacheCreateDto &cache_item) {
    char sql_command[200];
    sprintf(sql_command,
            "INSERT INTO cache(url, content, available_until, port) "
            "VALUES('%s', '%s', %d, %d);",
            cache_item.url.c_str(),
            cache_item.content.c_str(),
            cache_item.available_until,
            cache_item.port
    );
    execute(sql_command);
}

ExternalCacheRepository::~ExternalCacheRepository() {
    close_connection();
}

void ExternalCacheRepository::update(const ExternalCacheRetrieveDto &external_cache) {

}

template <class T>
ExternalCacheRetrieveDto* ExternalCacheRepository::find_by_value(const std::string& param_name, const T& value) {
    std::string temporary_value;

    if constexpr (!std::is_same_v<T, std::string>) {
        temporary_value = std::to_string(value);
    }
    else
        temporary_value = "'" + value  + "'";

    const std::string sql_command =
            "SELECT id, url, content, available_until, port FROM cache WHERE"
            " " + param_name + " = " + temporary_value + ";";

    sqlite3_stmt *result;
    if(sqlite3_prepare_v2(connection,
                          sql_command.c_str(),
                          -1,
                          &result,
                          nullptr) != SQLITE_OK)
        throw std::runtime_error("Error when trying to execute: " + sql_command);

    if(sqlite3_step(result) == SQLITE_ROW)
    {

        return new ExternalCacheRetrieveDto(sqlite3_column_int(result, 0),
                                    (const char*)sqlite3_column_text(result, 1),
                                    (const char*)sqlite3_column_text(result, 2),
                                    sqlite3_column_int(result, 3),
                                    sqlite3_column_int(result, 4));
    }

    sqlite3_finalize(result);
    return nullptr;
}