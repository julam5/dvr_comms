#ifndef DVRSENDER_HPP_
#define DVRSENDER_HPP_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <sstream>

class cDvrSender
{
    private:
        int sockfd, n;
        struct sockaddr_in serv_addr;

        // byte[1],byte[2]
        unsigned char jsonSignatureByte1;
        unsigned char jsonSignatureByte2;

        // byte[1],byte[2],byte[3],byte[4]
        unsigned char dataLenghtByte1;
        unsigned char dataLenghtByte2;
        unsigned char dataLenghtByte3;
        unsigned char dataLenghtByte4;

    public:
        cDvrSender();
        ~cDvrSender();

        bool initConnection();

        void sendStartDvr();
        void sendStopDvr();
    
        void Reverse32(uint32_t value); 
};

#endif //DVRSENDER_HPP_