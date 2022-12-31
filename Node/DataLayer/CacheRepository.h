#pragma once
#include "DatabaseContext.h"
#include "../DTO/CacheCreateDto.h"
#include "../DTO/CacheRetrieveDto.h"
#include <stdexcept>
#include "Print.h"
#include <type_traits>

using namespace Utils::Print;

class CacheRepository: public DatabaseContext  {
public:
    void insert(const CacheCreateDto& cache_item);

    template <class T>
    void remove(const std::string& param_name, const T& value);

    template <class T>
    CacheRetrieveDto* find_by_value(const std::string& param_name, const T& value);
    CacheRepository();
    ~CacheRepository();
};


CacheRepository::CacheRepository(): DatabaseContext() {
    open_connection();
}

void CacheRepository::insert(const CacheCreateDto &cache_item) {
    char sql_command[200];
    sprintf(sql_command,
            "INSERT INTO cache(url, content, available_until) "
            "VALUES('%s', '%s', %d);",
            cache_item.url.c_str(), cache_item.content.c_str(), cache_item.available_until
    );
    execute(sql_command);
}

CacheRepository::~CacheRepository() {
    close_connection();
}

template <class T>
CacheRetrieveDto* CacheRepository::find_by_value(const std::string& param_name, const T& value) {
    std::string temporary_value;

    if constexpr (!std::is_same_v<T, std::string>) {
        temporary_value = std::to_string(value);
    }
    else
        temporary_value = "'" + value  + "'";

    const std::string sql_command =
            "SELECT id, url, content, available_until FROM cache WHERE port is NULL and"
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

        return new CacheRetrieveDto(sqlite3_column_int(result, 0),
                                           (const char*)sqlite3_column_text(result, 1),
                                           (const char*)sqlite3_column_text(result, 2),
                                           sqlite3_column_int(result, 3));
    }

    sqlite3_finalize(result);
    return nullptr;
}

template <class T>
void CacheRepository::remove(const std::string& param_name, const T& value) {
    std::string temporary_value;

    if constexpr (!std::is_same_v<T, std::string>) {
        temporary_value = std::to_string(value);
    }
    else
        temporary_value = "'" + value  + "'";


    if(find_by_value(param_name, value) == nullptr)
        throw std::runtime_error("Cache item with value " + temporary_value + " does not exist.");

    std::string sql_command = "DELETE FROM cache WHERE " + param_name + "=" + temporary_value + ";";
    execute(sql_command);
    handle_log("Cache item with value %s has been deleted successfully.", temporary_value.c_str());
}