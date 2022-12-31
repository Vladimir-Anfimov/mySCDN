#include <iostream>
#include "Client.h"
#include "Print.h"
#include "TcpCommunication.h"

using namespace Utils::Print;

int main(int argc, char* argv[]) {
    if(argc < 2)
        handle_error("Port is missing from arguments");
    int port = atoi(argv[1]);
    auto client = new Client(port);
    auto tcp_communication = TcpCommunication(client->get_connection());
    std::cout<<"Write a message...\n";
    std::string msg;
    std::cin>>msg;
    tcp_communication.write_message(msg);
    std::string msg_back = tcp_communication.read_message();
    std::cout<<msg_back<<"\n";
}
