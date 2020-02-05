#include "dvr_sender.hpp"



int main(int argc, char *argv[])
{
    cDvrSender* pDvrSender = new cDvrSender();

    if(pDvrSender->initConnection())
    {
        pDvrSender->sendStopDvr();
    }

    

    return 0;
}








/*
int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char buffer[1024];
    struct sockaddr_in serv_addr; 



    memset(buffer, '0',sizeof(buffer));
    sprintf(buffer,"%c%c%c%c%c%c{\"droneId\":\"777\",\"action\":\"start\",\"message\":\"start\"}",232,7,0x34,0,0,0);
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5055); 

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
    
    write(sockfd, buffer, 63); 

    return 0;
}
*/