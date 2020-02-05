#include "dvr_sender.hpp"

cDvrSender::cDvrSender()
{
    sockfd = 0, n = 0;

    //JSONTCPSOCKET.PACKET_SIGNATURE = 2024 (signature from json-tcp-socket source code) [2 bytes]
    jsonSignatureByte1 = 0xe8;
    jsonSignatureByte2 = 0x07;


    dataLenghtByte1 = 0x00;
    dataLenghtByte2 = 0x00;
    dataLenghtByte3 = 0x00;
    dataLenghtByte4 = 0x00;
}


cDvrSender::~cDvrSender()
{

}



bool cDvrSender::initConnection()
{
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return false;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5055); 

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return false;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return false;
    } 

    return true;
}

void cDvrSender::sendStartDvr()
{
    std::stringstream headerStream, dataStream;
    std::string dataString, startString;

    dataStream << "{\"droneId\":\"" << 12155643 << "\",\"action\":\"start\",\"message\":\"start\"}";
    dataString = dataStream.str();

    Reverse32(dataString.length());

    headerStream << jsonSignatureByte1 << jsonSignatureByte2;
    headerStream << dataLenghtByte1 
                 << dataLenghtByte2
                 << dataLenghtByte3
                 << dataLenghtByte4;  //length of data being sent [4 bytes]
    
    //sprintf(buffer,"%c%c%c%c%c%c{\"droneId\":\"777\",\"action\":\"start\",\"message\":\"start\"}",232,7,0x34,0,0,0);

    startString = headerStream.str() + dataString;
    write(sockfd, startString.c_str(), startString.length()); 
}



void cDvrSender::sendStopDvr()
{

    std::stringstream headerStream, dataStream;
    std::string dataString, stopString;

    dataStream << "{\"droneId\":\"" << 12155643 << "\",\"action\":\"stop\",\"message\":\"dronelanded\"}";
    dataString = dataStream.str();

    Reverse32(dataString.length());

    headerStream << jsonSignatureByte1 << jsonSignatureByte2;
    headerStream << dataLenghtByte1 
                 << dataLenghtByte2
                 << dataLenghtByte3
                 << dataLenghtByte4;  //length of data being sent [4 bytes]

    stopString = headerStream.str() + dataString;
    write(sockfd, stopString.c_str(), stopString.length()); 

}

void cDvrSender::Reverse32(uint32_t value)
{
    dataLenghtByte1 = value & 0x000000FF; 
    dataLenghtByte2 = value & 0x0000FF00;
    dataLenghtByte3 = value & 0x00FF0000;
    dataLenghtByte4 = value & 0xFF000000;

}