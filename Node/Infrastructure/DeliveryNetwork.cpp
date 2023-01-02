#include "DeliveryNetwork.h"
#include <sstream>
#include <cstring>
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

    printf("\033[0;31m");
    handle_log("External network nodes(ports): %s", network_nodes.empty() ?
                    "None" : get_available_nodes_string().c_str());
    printf("\033[0;37m");
}

std::string DeliveryNetwork::get_available_nodes_string() {
    std::string nodes_list_string = "";

    for(const auto& port : network_nodes)
        nodes_list_string+= std::to_string(port) +" ";
    return nodes_list_string;
}

void DeliveryNetwork::delete_network_nodes() {
    std::lock_guard<std::mutex> nodes_lock(network_nodes_mutex);
    network_nodes.clear();
}