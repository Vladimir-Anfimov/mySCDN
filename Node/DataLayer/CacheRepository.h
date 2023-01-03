#pragma once
#include "DatabaseContext.h"
#include "../DTO/CacheUpsertDto.h"
#include "../DTO/CacheDto.h"
#include <stdexcept>
#include "Print.h"
#include "vector"

using namespace Utils::Print;

class CacheRepository: public DatabaseContext  {
public:
    void insert(const CacheUpsertDto& cache_item);

    template <class T>
    void remove(const std::string& param_name, const T& value, const std::string& sign = "=");

    template <class T1, class T2 = std::string>
    CacheDto* find_by_value(const std::string& param_name_one, const T1& value_one,
                            const std::string& param_name_two = "", const T2& value_two = "");

    std::vector<ExternalCache> select_all();

    explicit CacheRepository();
    ~CacheRepository();
};


inline CacheRepository::CacheRepository() {
    open_connection();
}

inline void CacheRepository::insert(const CacheUpsertDto &cache_item) {
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


inline CacheRepository::~CacheRepository() {
    close_connection();
}

inline std::vector<ExternalCache> CacheRepository::select_all() {
    std::vector<ExternalCache> all;

    sqlite3_stmt *result;
    constexpr char sql_command[] = "SELECT url, available_until, port FROM cache;";
    if(sqlite3_prepare_v2(connection, sql_command,-1, &result, nullptr) != SQLITE_OK)
        throw std::runtime_error("Error when trying to execute: " + std::string(sql_command));


    handle_log("Executing %s", sql_command);

    while(sqlite3_step(result) != SQLITE_DONE)
    {
        all.emplace_back(
                (const char*)sqlite3_column_text(result, 0),
                sqlite3_column_int(result, 1),
                sqlite3_column_int(result, 2)
                );
    }

    sqlite3_finalize(result);

    return all;
}

template <class T1, class T2>
CacheDto* CacheRepository::find_by_value(
        const std::string& param_name_one, const T1& value_one,
        const std::string& param_name_two, const T2& value_two
        ) {
    std::string temporary_value_one;
    std::string temporary_value_two;

    if constexpr (!std::is_same_v<T1, std::string>) {
        temporary_value_one = std::to_string(value_one);
    }
    else
        temporary_value_one = "'" + value_one  + "'";

    bool seconds_param_exists = false;
    if constexpr (std::is_same_v<T2, std::string>) {
        if(value_two != "")
        {
            temporary_value_two = "'" + value_two  + "'";
            seconds_param_exists = true;
        }
    }
    else {
        temporary_value_two = std::to_string(value_two);
        seconds_param_exists = true;
    }

    const std::string sql_command =
            "SELECT id, url, content, available_until, port FROM cache WHERE"
            " " + param_name_one + " = " + temporary_value_one +
            (seconds_param_exists ?
            " AND " + param_name_two + " = " + temporary_value_two + ";" : ";");

    handle_log("Executing %s", sql_command.c_str());
    sqlite3_stmt *result;
    if(sqlite3_prepare_v2(connection,
                          sql_command.c_str(),
                          -1,
                          &result,
                          nullptr) != SQLITE_OK)
        throw std::runtime_error("Error when trying to execute: " + sql_command);

    CacheDto* dto_result = nullptr;

    if(sqlite3_step(result) == SQLITE_ROW)
    {
        dto_result = new CacheDto(sqlite3_column_int(result, 0),
                                            (const char*)sqlite3_column_text(result, 1),
                                            (const char*)sqlite3_column_text(result, 2),
                                            sqlite3_column_int(result, 3),
                                            sqlite3_column_int(result, 4));
    }

    sqlite3_finalize(result);
    return dto_result;
}

template <class T>
void CacheRepository::remove(const std::string& param_name, const T& value, const std::string& sign) {
    std::string temporary_value;

    if constexpr (!std::is_same_v<T, std::string>) {
        temporary_value = std::to_string(value);
    }
    else
        temporary_value = "'" + value  + "'";

    std::string sql_command = "DELETE FROM cache WHERE " + param_name + sign + temporary_value + ";";
    execute(sql_command);
}