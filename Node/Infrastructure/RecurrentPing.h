#pragma once
#include <chrono>
#include "Print.h"
#include <thread>
#include "Client.h"
#include "TcpCommunication.h"
#include "StandardCommunication.h"

using namespace Utils::Print;

void recurrent_ping(int node_port, int proxy_port)
{
    constexpr int interval_seconds = 3;
    std::thread([node_port, proxy_port, interval_seconds]{
        while(true)
        {
            try {
                auto tcp_client = Client(proxy_port);
                auto *communication = new TcpCommunication(tcp_client.get_connection());
                communication->write_message(
                        std::string(StandardCommunication::Ping) + std::to_string(node_port));

                std::string response = communication->read_message();
                handle_log("Node ping response: %s", response.c_str());
                tcp_client.shutdown_connection();
            }
            catch (std::exception& ex)
            {
                handle_warning("Recurrent Ping Task error: %s", ex.what());
            }

            std::this_thread::sleep_for(std::chrono::seconds (interval_seconds));
        }
    }).detach();
}