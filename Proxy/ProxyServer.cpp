#include "ProxyServer.h"
#include "HttpCommunication.h"
#include "Print.h"
#include "StandardCommunication.h"
#include "Client.h"
#include "Command.h"
#include <time.h>
#include <chrono>
#include <thread>
#include <iostream>

using namespace Utils::Print;

ProxyServer::ProxyServer(int port): Server(port) {
    recurrent_node_check();
}


void ProxyServer::process_event(ConnectionType client) {
    auto *communication = new TcpCommunication(client);
    try {
        std::string message = communication->read_message();
        handle_log("Message %s", message.c_str());

        bool http = false;
        if(HttpCommunication::is_http_message(message))
        {
            communication = new HttpCommunication(client);
            http = true;
        }

        std::string response = process_command(communication, message, http);
        communication->write_message(response + "\n");
    }
    catch (std::exception& exp)
    {
        handle_warning("%s\n", exp.what());
        communication->write_message(std::string(exp.what()) + "\n");
    }
    shutdown(client, SHUT_RDWR);
}

std::string ProxyServer::process_command(TcpCommunication* communication, std::string command, bool http) {
    if(http)
    {
        auto command_node = std::string(StandardCommunication::Search) +
                HttpCommunication::extract_content(command);
        return round_robin_process(command_node);
    }

    if(Command::is_ping(command))
        return ping_process(command);

    throw std::runtime_error("Command " + command + " not supported.");
}

std::string ProxyServer::round_robin_process(const std::string &command) {
    if(nodes.empty())
        throw std::runtime_error("There are no available nodes.");

    std::unique_lock<std::mutex> nodes_lock(mutex_nodes);
    int node_port = nodes[round_robin_index].port;
    round_robin_index = (round_robin_index + 1) % nodes.size();
    nodes_lock.unlock();

    //communication with a node
    auto tcp_client = Client(node_port);
    auto *tcp_communication = new TcpCommunication(tcp_client.get_connection());
    tcp_communication->write_message(command);

    printf("\033[0;32m");
    handle_log("Writing request(%s) to node(port %d)", command.c_str(), node_port);
    printf("\033[0;37m");

    std::string response = tcp_communication->read_message();

    printf("\033[0;32m");
    handle_log("Reading response(%s) from node(port %d)", response.c_str(), node_port);
    printf("\033[0;37m");

    tcp_client.shutdown_connection();
    return response;
}

std::string ProxyServer::ping_process(const std::string &command) {
    int node_port = Command::get_port_from_command(command);
    bool found = false;
    std::unique_lock<std::mutex> nodes_lock(mutex_nodes);

    for(auto& node : nodes)
    {
        if(node.port == node_port)
        {
            node.last_ping = time(nullptr);
            found = true;
            break;
        }
    }
    if(!found)
        nodes.emplace_back(node_port, time(nullptr));
    nodes_lock.unlock();

    return StandardCommunication::Success;
}

void ProxyServer::recurrent_node_check() {
    constexpr int interval_seconds = 2;
    constexpr int max_approved_interval_without_ping_in_seconds = 4;

    std::thread([&]{
        while(true)
        {
            std::unique_lock<std::mutex> nodes_guard(mutex_nodes);
            nodes.erase(std::remove_if(
                    nodes.begin(), nodes.end(),
                    [](const Node& node) {
                        return time(nullptr) -  node.last_ping > max_approved_interval_without_ping_in_seconds;
                    }), nodes.end());

            nodes_guard.unlock();

            std::string message = "Available nodes: ";
            if(nodes.empty()) message += "None";
            for(const auto& node : nodes)
                message+= std::to_string(node.port) +" ";

            printf("\033[0;31m");
            handle_log("%s", message.c_str());
            printf("\033[0;37m");

            std::this_thread::sleep_for(std::chrono::seconds (interval_seconds));
        }
    }).detach();
}


