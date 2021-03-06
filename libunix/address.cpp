#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <libutil/array.h>
#include <libutil/strings.h>

#include "address.h"

namespace unix {


IPv4 parse_ipv4(const std::string &host) {
    unsigned char buf[sizeof(struct in_addr)];
	if (inet_pton(AF_INET, host.c_str(), &buf) <= 0) {
        c_error("ERROR on inet_pton");
    }
	return IPv4(buf);
}


IPv6 parse_ipv6(const std::string &host) {
    unsigned char buf[sizeof(struct in6_addr)];
	if (inet_pton(AF_INET6, host.c_str(), &buf) <= 0) {
        c_error("ERROR on inet_pton");
    }
	return IPv6(buf);
}


std::unique_ptr<NetAddress> nullcpy(NetAddress *a) {
    if (a) {
        return a->copy();
    }
    else {
        return nullptr;
    }
}


IPv4::IPv4(const unsigned char addr[IPv4::bytesize])
    :
    addr(util::to_array<unsigned char, IPv4::bytesize>(addr)) {}


IPv4::IPv4(const std::array<unsigned char, IPv4::bytesize> &addr)
	:
	addr(addr) {}


IPv4::~IPv4() {}


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


IPv4::addrport_t IPv4::port(unsigned short portnum) const {
	IPv4::addrport_t serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portnum);
    std::memcpy(&serv_addr.sin_addr, &addr.at(0), IPv4::bytesize);
    return serv_addr;
}


bool IPv4::operator==(const NetAddress &a) const {
    if (a.type() == AddressType::ipv4) {
        return addr == reinterpret_cast<const IPv4 &>(a).addr;
    }
	return false;
}


AddressType IPv4::type() const {
	return AddressType::ipv4;
}


std::unique_ptr<NetAddress> IPv4::copy() const {
    return std::make_unique<IPv4>(*this);
}


void IPv4::connect(filedesc_t sockfd, unsigned short portnum) const {

	// connect to remote
    auto addrport = port(portnum);
	if (::connect(sockfd, (struct sockaddr *) &addrport, sizeof(IPv4::addrport_t)) < 0) {
		c_error("ERROR on connecting");
	}
}


IPv6::IPv6(const unsigned char addr[bytesize])
    :
    addr(util::to_array<unsigned char, IPv6::bytesize>(addr)) {}


IPv6::IPv6(const std::array<unsigned char, IPv6::bytesize> &addr)
	:
	addr(addr) {}


IPv6::~IPv6() {}


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


IPv6::addrport_t IPv6::port(unsigned short portnum) const {
	IPv6::addrport_t serv_addr;
    serv_addr.sin6_family = AF_INET6;
    serv_addr.sin6_port = htons(portnum);
    std::memcpy(&serv_addr.sin6_addr, &addr.at(0), IPv6::bytesize);
    return serv_addr;
}


bool IPv6::operator==(const NetAddress &a) const {
    if (a.type() == AddressType::ipv6) {
        return addr == reinterpret_cast<const IPv6 &>(a).addr;
    }
    return false;
}


AddressType IPv6::type() const {
	return AddressType::ipv6;
}


std::unique_ptr<NetAddress> IPv6::copy() const {
    return std::make_unique<IPv6>(*this);
}


void IPv6::connect(filedesc_t sockfd, unsigned short portnum) const {

	// connect to remote
    auto addrport = port(portnum);
	if (::connect(sockfd, (struct sockaddr *) &addrport, sizeof(IPv6::addrport_t)) < 0) {
		c_error("ERROR on connecting");
	}
}


}
