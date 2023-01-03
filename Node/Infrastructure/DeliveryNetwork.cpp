#include "DeliveryNetwork.h"
#include <sstream>
#include <cstring>
#include <Client.h>
#include <TcpCommunication.h>
#include "StandardCommunication.h"
#include "Print.h"

using namespace Utils::Print;

DeliveryNetwork *DeliveryNetwork::get_instance() {
    if(instance == nullptr)
        instance = new DeliveryNetwork();
    return instance;
}

void DeliveryNetwork::update_network_nodes(std::string &ports) {
    ports.erase(ports.begin(), ports.begin() + strlen(StandardCommunication::Success));
    ports.erase(ports.begin() + ports.find_last_of("0123456789")+1, ports.end());

    std::istringstream stream(ports);
    std::string str_port;
    std::vector<PortType> new_network_nodes;

    while(getline(stream, str_port, ' '))
    {
        try {
            int new_port = stoi(str_port);
            if(current_node_port != new_port)
                new_network_nodes.push_back(new_port);
        }
        catch(std::exception& exp)
        {
            handle_warning("Error when trying to update network nodes: %s", exp.what());
        }
    }
    std::lock_guard<std::mutex> nodes_lock(network_nodes_mutex);
    network_nodes = new_network_nodes;

    handle_logR("External network nodes(ports): %s", network_nodes.empty() ?
                    "None" : get_available_nodes_string().c_str());
}

std::string DeliveryNetwork::get_available_nodes_string() {
    std::string nodes_list_string;

    for(const auto& port : network_nodes)
        nodes_list_string+= std::to_string(port) +" ";
    return nodes_list_string;
}

void DeliveryNetwork::delete_network_nodes() {
    std::lock_guard<std::mutex> nodes_lock(network_nodes_mutex);
    network_nodes.clear();
}

void DeliveryNetwork::publish_new_information(const std::string &command) {
    std::lock_guard<std::mutex> lock_guard(network_nodes_mutex);
    for(const auto& port_node : network_nodes)
    {
        auto client = new Client(port_node);
        auto communication = TcpCommunication(client->get_connection());
        communication.write_message(command);
        handle_logB("Writing information to node %d: %s", port_node, command.c_str());

        std::string response = communication.read_message();
        handle_logB("Reading information from node %d: %s", port_node, response.c_str());
    }
}
