#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <libutil/strings.h>

#include "socket.h"

namespace unix {


std::array<unsigned char, 4> parse_addr(const std::string &str) {

}

IPv4::IPv4(const std::array<unsigned char, 4> &addr)
	:
	addr(addr) {}


IPv4::~IPv4() {}


std::string IPv4::str() const {
	std::vector<std::string> arr;
	for (auto &e: addr) {
		arr.push_back(std::to_string(e));
	}
	return util::concat(util::intersperse(std::string("."), arr));
}


filedesc_t IPv4::connect(int port) const {
	// open socket
	int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		c_error("ERROR opening socket");
	}

	// connect to remote
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if(inet_pton(AF_INET, str().c_str(), &serv_addr.sin_addr) <= 0) {
        c_error("ERROR on inet_pton");
    }


	if (::connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		c_error("ERROR on connecting");
	}
}


filedesc_t listen_port(int port) {
	// open socket
	int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		c_error("ERROR opening socket");
	}

	// bind and listen on socket
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		c_error("ERROR on binding");
	}
	::listen(sockfd, 5);
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
