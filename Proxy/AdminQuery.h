#pragma once

#include <string>
#include "DTO/CacheUploadRequest.h"
#include "DTO/CacheUpsertDto.h"
#include "Print.h"

using namespace Utils::Print;

class AdminQuery {
    constexpr static char ADMIN_QUERY_PATTERN[] = "admin?";
    CacheUploadRequest* upload_request;
public:
    explicit AdminQuery(std::string query_string)
    {
        query_string.erase(query_string.begin(), query_string.begin() + strlen(ADMIN_QUERY_PATTERN));
        upload_request = new CacheUploadRequest(query_string);
    }

    int get_port()
    {
        return upload_request->port;
    }

    std::string send_upload_request()
    {
        auto tcp_client = Client(upload_request->port);
        auto *tcp_communication = new TcpCommunication(tcp_client.get_connection());
        auto upsert_command = StandardCommunication::Upload +
                                    CacheUpsertDto(*upload_request).to_query_string();

        handle_logG("Writing request(%s) to node(port %d)", upsert_command.c_str(), upload_request->port);
        tcp_communication->write_message(upsert_command);

        std::string response = tcp_communication->read_message();

        handle_logG("Reading response(%s) from node(port %d)", response.c_str(), upload_request->port);

        tcp_client.shutdown_connection();
        return response;
    }

    static bool is_admin_query(const std::string& query)
    {
        return query.find(ADMIN_QUERY_PATTERN) == 0;
    }
};