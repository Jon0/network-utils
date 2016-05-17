#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <libutil/strings.h>

#include "address.h"

namespace unix {


std::array<unsigned char, 4> parse_addr(const std::string &str) {
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = 0;
	if(inet_pton(AF_INET, str.c_str(), &serv_addr.sin_addr) <= 0) {
	    c_error("ERROR on inet_pton");
	}
	return {0, 0, 0, 0};
}


IPv4::IPv4(const std::array<unsigned char, IPv4::bytesize> &addr)
	:
	addr(addr) {}


IPv4::~IPv4() {}


bool IPv4::operator==(const IPv4 &ip) const {
	return addr == ip.addr;
}


std::array<unsigned char, IPv4::bytesize> IPv4::parts() const {
	return addr;
}


std::string IPv4::str() const {
	std::vector<std::string> arr;
	for (auto &e: addr) {
		arr.push_back(std::to_string(e));
	}
	return util::concat(util::intersperse(std::string("."), arr));
}


AddressType IPv4::type() const {
	return AddressType::ipv4;
}


millisecs IPv4::ping(size_t blocksize) const {
	return millisecs(0);
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


IPv6::IPv6(const std::array<unsigned char, IPv6::bytesize> &addr)
	:
	addr(addr) {}


IPv6::~IPv6() {}


bool IPv6::operator==(const IPv6 &ip) const {
	return addr == ip.addr;
}


std::array<unsigned char, IPv6::bytesize> IPv6::parts() const {
	return addr;
}


std::string IPv6::str() const {
	std::vector<std::string> arr;
	for (auto &e: addr) {
		arr.push_back(std::to_string(e));
	}
	return util::concat(util::intersperse(std::string("::"), arr));
}


AddressType IPv6::type() const {
	return AddressType::ipv4;
}


millisecs IPv6::ping(size_t blocksize) const {
	return millisecs(0);
}


filedesc_t IPv6::connect(int port) const {
	// open socket
	int sockfd = ::socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd < 0) {
		c_error("ERROR opening socket");
	}

	// connect to remote
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET6;
	serv_addr.sin_port = htons(port);
	if(inet_pton(AF_INET6, str().c_str(), &serv_addr.sin_addr) <= 0) {
        c_error("ERROR on inet_pton");
    }


	if (::connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		c_error("ERROR on connecting");
	}
}


}
