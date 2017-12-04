#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "glib-2.0/glib.h"
#define BUFFEr_SIZE 4096

char *base64(const unsigned char *input, int length);

void error(char *msg)
{
    puts(msg);
    perror(msg);
}

void testConnection(){
    char *hostname;   
    struct hostent *hostinfo;

    hostname = "google.com";
    hostinfo = gethostbyname (hostname);

    if (hostinfo == NULL) puts("-> no connection!");
    else puts("-> connection established!\n");
}

void sendServerMessage(char *message[]){

}

int main(int argc, char *argv[])
{
    
    testConnection();
    
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFFEr_SIZE];
    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
    (char *)&serv_addr.sin_addr.s_addr,
    server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
        error("ERROR reading from socket");
    printf("%s\n",buffer);

    bzero(buffer,BUFFEr_SIZE);
/*
 * NECESSARY:
 *      EHLO
 *      MAIL FROM
 *      RCPT TO
 *      DATA
 * OPTIONAL:
 *      RSET (abort current transaction w/ server)
 *      VRFY (verify a mailbox exists)
 *      QUIT (close connection)
 */

    /*------------------------------*/
    
    puts("\nCONNECTION ESTABLISHED\n");
    puts("STARTING EHLO");
    
    strcpy(buffer, "ehlo smtp.gmail.com\n");
    
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,BUFFEr_SIZE);
    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    /*------------------------------*/
    
    /*------------------------------*/
    
    puts("\nDONE EHLO\n");
    puts("STARTING STARTTLS");
    
    strcpy(buffer, "STARTTLS\n");

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,BUFFEr_SIZE);
    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    /*------------------------------*/
    
    /*------------------------------*/
    
    puts("\nDONE STARTTLS\n");
    puts("STARTING EHLO AGAIN");
    
    strcpy(buffer, "ehlo smtp.gmail.com\n");
    
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,BUFFEr_SIZE);
    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    /*------------------------------*/

    // according to RFC 2821 this section CAN be used as a fall back if the SMTP
    // server does not support extended Hello (EHLO), but I don't think this is
    // very common.
    /*------------------------------
     
    
    printf("\DONE EHLO\n");
    printf("STARTING HELO");

    strcpy(buffer,"helo smtp.gmail.com\n");

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,BUFFEr_SIZE);
    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    /*------------------------------*/  

    
    
    
    
    
    /*------------------------------*/
    
    puts("DONE EHLO");
    puts("STARTING AUTH LOGIN");

    strcpy(buffer,"AUTH LOGIN LS1lbiBhbGV4LmRhdmVucG9ydDIxOTQK\n");
    
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,BUFFEr_SIZE);
    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    
    
    strcpy(buffer,"LS1lbiA5ODcyNTk4NzI1Cg=\n");
    
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,BUFFEr_SIZE);
    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    

    /*------------------------------*/
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*------------------------------*/
    
    puts("DONE AUTH LOGIN");
    puts("STARTING MAIL FROM");

    strcpy(buffer,"MAIL FROM: alex.davenport2194@gmail.com");

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,BUFFEr_SIZE);
    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    /*------------------------------*/
    
    /*------------------------------*/
    
    puts("DONE MAIL FROM");
    puts("STARTING RCPT TO");

    strcpy(buffer,"RCPT TO: alex.davenport2194@gmail.com");

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,BUFFEr_SIZE);
    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    /*------------------------------*/       

    /*------------------------------*/
    puts("DONE RCPT TO");
    puts("STARTING DATA\n");

    strcpy(buffer,"DATA\r\n");
    n = write(sockfd,buffer,strlen(buffer));

    strcpy(buffer,"Subject: test\r\n");
    n = write(sockfd,buffer,strlen(buffer));

    strcpy(buffer,"SMTP MAIL TOOL TEST WORKS!!!\r\n");
    n = write(sockfd,buffer,strlen(buffer));

    strcpy(buffer,"\n\n");
    n = write(sockfd,buffer,strlen(buffer));

    strcpy(buffer,".\n");
    n = write(sockfd,buffer,strlen(buffer));


    /*------------------------------*/ 

    /*------------------------------*/ 
    puts("DONE DATA");
    puts("STARTING QUIT");
    strcpy(buffer,"quit\n");

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,BUFFEr_SIZE);
    n = read(sockfd,buffer,BUFFEr_SIZE-1);
    if (n < 0) 
         error("ERROR reading from socket");
    puts(buffer);

    /*------------------------------*/

    return 0;
}
