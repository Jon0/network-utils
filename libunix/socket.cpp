#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "socket.h"

namespace unix {


filedesc_t ipv4_socket(int socket_type, int protocol) {

	// open socket
	int sockfd = ::socket(AF_INET, socket_type, protocol);
	if (sockfd < 0) {
		c_error("ERROR opening socket");
	}
	return sockfd;
}


filedesc_t ipv6_socket(int socket_type, int protocol) {

	// open socket
	int sockfd = ::socket(AF_INET6, socket_type, protocol);
	if (sockfd < 0) {
		c_error("ERROR opening socket");
	}
	return sockfd;
}


Socket::Socket(const NetAddress *l, const NetAddress *r, const filedesc_t &fd)
	:
	FileDesc(fd),
 	local_addr(l->copy()),
	remote_addr(r->copy()) {
}


NetAddress *Socket::local() const {
	return local_addr.get();
}


NetAddress *Socket::remote() const {
	return remote_addr.get();
}


std::streamsize Socket::recv(char *buf, std::size_t count) const{
	return 0;
}


std::streamsize Socket::send(const char *buf, std::size_t count) const {
	return 0;
}


filedesc_t listen_ipv4(unsigned short portnum) {
	// open socket
	int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		c_error("ERROR opening socket");
	}

	// bind and listen on socket
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portnum);
	if (::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		c_error("ERROR on binding");
	}
	::listen(sockfd, 5);
	return sockfd;
}


TcpAcceptor::TcpAcceptor(int port)
	:
	FileDesc(listen_ipv4(port)),
 	local_addr(std::make_unique<IPv4>(std::array<unsigned char, 4>({127, 0, 0, 1}))) {}


Socket TcpAcceptor::accept() const {
	sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	int newsockfd = ::accept(id(), (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		c_error("ERROR on accept");
	}
	IPv4 remote_addr((const unsigned char *) &cli_addr.sin_addr);
	return Socket(local_addr.get(), &remote_addr, newsockfd);
}


millisecs ping(NetAddress *addr) {
	// TODO
	return millisecs(0);
}


}
