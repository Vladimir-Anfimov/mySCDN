#include <string>
#include <mutex>
#include <vector>

using PortType = int;

class DeliveryNetwork {
    static inline std::vector<PortType> network_nodes;
    static inline DeliveryNetwork* instance = nullptr;
    DeliveryNetwork() = default;
    static inline std::mutex network_nodes_mutex;

    std::string get_available_nodes_string();

public:
    static DeliveryNetwork* get_instance();
    void delete_network_nodes();
    DeliveryNetwork(DeliveryNetwork&) = delete;
    void operator=(const DeliveryNetwork&) = delete;
    void update_network_nodes(std::string& ports);
    static inline PortType current_node_port = 0;
    void publish_new_information(const std::string& command);
};
