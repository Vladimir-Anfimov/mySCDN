set(FIND_TINYHELP_PATHS /media/vladimir/Volum\ nou/Teme/ANUL\ II/Retele/mySCDN/tinyhelp)

find_path(LIBHELP_INCLUDE_DIR
        HttpCommunication.h
        Print.h
        Server.h
        ServerConfig.h
        ThreadPool.h
        TcpCommunication.h
        Client.h
        PATH_SUFFIXES include
        PATHS ${FIND_TINYHELP_PATHS})

find_library(TINYHELP_LIBRARY
        NAMES tinyhelp.a
        PATH_SUFFIXES lib
        PATHS ${FIND_TINYHELP_PATHS})