#include <iostream>
#include "Print.h"

using namespace Utils::Print;

#include "HttpCommunication.h"
#include "Print.h"
#include "Server.h"

using namespace Utils::Print;

class TcpServer: public Server{
public:
    void process_event(ConnectionType client) {
        auto communication = HttpCommunication(client);
        try {
            std::string message = communication.read_message();
            handle_log("Message %s", message.c_str());
            communication.write_message("hei hei hei\n");
        }
        catch (std::exception& exp)
        {
            handle_warning("%s\n", exp.what());
            communication.write_message(exp.what());
        }
        shutdown(client, SHUT_RDWR);
    }

    TcpServer(int port): Server(port) {
    }
};


#include <iostream>
#include "Print.h"

using namespace Utils::Print;

int main(int argc, char* argv[]) {

    int port = 9990;
    auto server = new TcpServer(port);
    server->start_listening();
}