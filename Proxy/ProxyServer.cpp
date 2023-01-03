#include "ProxyServer.h"
#include "HttpCommunication.h"
#include "Print.h"
#include "StandardCommunication.h"
#include "Client.h"
#include "Command.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>
#include "AdminQuery.h"

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
        command = HttpCommunication::extract_content(command);

        if(AdminQuery::is_admin_query(command))
        {
            auto admin_query = AdminQuery(command);
            if(!check_node_existence(admin_query.get_port()))
                throw std::runtime_error("Node with port "+
                      std::to_string(admin_query.get_port()) +" does not exists in the network.");
            return admin_query.send_upload_request();
        }
        else // in this case is a simple query search for an url
            command = std::string(StandardCommunication::Search) + command;

        return round_robin_process(command);
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
    auto tcp_client = new Client(node_port);
    auto *tcp_communication = new TcpCommunication(tcp_client->get_connection());
    tcp_communication->write_message(command);

    handle_logG("Writing request(%s) to node(port %d)", command.c_str(), node_port);
    std::string response = tcp_communication->read_message();

    handle_logG("Reading response(%s) from node(port %d)", response.c_str(), node_port);

    return response;
}

std::string ProxyServer::ping_process(const std::string &command) {
    int node_port = Command::get_port_from_command(command);
    bool found = false;
    std::lock_guard<std::mutex> nodes_lock(mutex_nodes);

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

    std::string available_nodes_string = get_available_nodes_string();

    return StandardCommunication::Success + available_nodes_string;
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
            if(nodes.empty())
                message += "None";
            else
                message += get_available_nodes_string();

            handle_logR("%s", message.c_str());

            std::this_thread::sleep_for(std::chrono::seconds (interval_seconds));
        }
    }).detach();
}

std::string ProxyServer::get_available_nodes_string() {
    std::string nodes_list_string = "";

    for(const auto& node : nodes)
        nodes_list_string+= std::to_string(node.port) +" ";
    return nodes_list_string;
}

bool ProxyServer::check_node_existence(int search_port) {
    bool exists = false;
    std::lock_guard<std::mutex> lock_guard(mutex_nodes);
    for(const auto& node : nodes)
    {
        if(node.port == search_port)
        {
            exists = true;
            break;
        }
    }
    return exists;
}


