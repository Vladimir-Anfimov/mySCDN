#pragma once
#include "Client.h"
#include "TcpCommunication.h"
#include "Print.h"
#include "StandardCommunication.h"

using namespace Utils::Print;

class InitialiseService
{
    int origin_port;
    static void add_to_database(const std::string& response);
public:
    explicit InitialiseService(int origin_port);
    void initialise();
};