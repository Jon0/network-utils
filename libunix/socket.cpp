#include <iostream>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "socket.h"

namespace unix {


filedesc_t listen_port(int port) {
	// open socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		c_error("ERROR opening socket");
	}

	// bind and listen on socket
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		c_error("ERROR on binding");
	}
	listen(sockfd, 5);
	return sockfd;
}


TcpAcceptor::TcpAcceptor(int port)
	:
	sockfd(listen_port(port)) {
}


int TcpAcceptor::acceptfd() const {
	sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	int newsockfd = accept(sockfd.id(), (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		c_error("ERROR on accept");
	}
	return newsockfd;
}


}
