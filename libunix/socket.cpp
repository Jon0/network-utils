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


filedesc_t addr_socket(const NetAddress *r, int socket_type, int protocol) {
	switch (r->type()) {
	case AddressType::ipv4:
		return ipv4_socket(socket_type, protocol);
	case AddressType::ipv6:
		return ipv6_socket(socket_type, protocol);
	}
}



Socket::Socket(const Socket &s)
 	:
	FileDesc(s.id()),
 	local_addr(s.local_addr->copy()),
	remote_addr(s.remote_addr->copy()) {
}


Socket::Socket(const NetAddress *r, unsigned short portnum)
	:
	FileDesc(addr_socket(r)),
 	local_addr(std::make_unique<IPv4>(std::array<unsigned char, 4>({127, 0, 0, 1}))),
	remote_addr(r->copy()),
 	active(true) {
	r->connect(id(), portnum);
}


Socket::Socket(const NetAddress *l, const NetAddress *r, const filedesc_t &fd)
	:
	FileDesc(fd),
 	local_addr(l->copy()),
	remote_addr(r->copy()),
 	active(true) {
}


Socket::~Socket() {}


std::string Socket::rstr() const {
	return remote_addr->str();
}


NetAddress *Socket::local() const {
	return local_addr.get();
}


NetAddress *Socket::remote() const {
	return remote_addr.get();
}


std::streamsize Socket::recv(char *buf, std::size_t count) {
	return 0;
}


std::streamsize Socket::send(const char *buf, std::size_t count) {
	return 0;
}


bool Socket::connected() const {
	return active && !eof();
}


void Socket::shutdown(int how) {
	if (connected()) {
		::shutdown(id(), how);
		active = false;
	}
}


bool Socket::open() const {
	return connected();
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


TcpAcceptor::TcpAcceptor(const TcpAcceptor &a)
	:
	FileDesc(a.id()),
	local_addr(a.local()->copy()) {}


TcpAcceptor::TcpAcceptor(int port)
	:
	FileDesc(listen_ipv4(port)),
 	local_addr(std::make_unique<IPv4>(std::array<unsigned char, 4>({127, 0, 0, 1}))) {}


NetAddress *TcpAcceptor::local() const {
	return local_addr.get();
}


Socket TcpAcceptor::accept() const {
	auto pair = acceptfd();
	return Socket(local_addr.get(), &pair.first, pair.second);
}


std::shared_ptr<Socket> TcpAcceptor::accept_shared() const {
	auto pair = acceptfd();
	return std::make_shared<Socket>(local_addr.get(), &pair.first, pair.second);
}


std::pair<IPv4, filedesc_t> TcpAcceptor::acceptfd() const {
	sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	int newsockfd = ::accept(id(), (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		c_error("ERROR on accept");
	}
	IPv4 remote_addr((const unsigned char *) &cli_addr.sin_addr);
	return std::make_pair(remote_addr, newsockfd);
}


millisecs ping(NetAddress *addr) {
	// TODO
	return millisecs(0);
}


}
