#pragma once

#include <array>
#include <memory>
#include <string>

#include <netinet/in.h>

#include "libutil/hash.h"
#include "file.h"

namespace unix {


enum class AddressType {
	ipv4,
	ipv6
};


class NetAddress {
public:
	virtual ~NetAddress() {}
	virtual AddressType type() const = 0;
	virtual std::unique_ptr<NetAddress> copy() const = 0;
	virtual void connect(filedesc_t sockfd, unsigned short portnum) const = 0;
};


class IPv4 : public NetAddress {
public:
	static constexpr size_t bytesize = 4;
	using addrport_t = sockaddr_in;

	IPv4(const unsigned char addr[bytesize]);
	IPv4(const std::array<unsigned char, bytesize> &addr);
	virtual ~IPv4();

	bool operator==(const IPv4 &ip) const;

	std::array<unsigned char, bytesize> parts() const;
	std::string str() const;
	addrport_t port(unsigned short portnum) const;

	AddressType type() const override;
	std::unique_ptr<NetAddress> copy() const override;
	void connect(filedesc_t sockfd, unsigned short portnum) const override;

private:
	const std::array<unsigned char, bytesize> addr;
};


class IPv6 : public NetAddress {
public:
	static constexpr size_t bytesize = 16;
	using addrport_t = sockaddr_in6;

	IPv6(const unsigned char addr[bytesize]);
	IPv6(const std::array<unsigned char, bytesize> &addr);
	virtual ~IPv6();

	bool operator==(const IPv6 &ip) const;

	std::array<unsigned char, bytesize> parts() const;
	std::string str() const;
	addrport_t port(unsigned short portnum) const;

	AddressType type() const override;
	std::unique_ptr<NetAddress> copy() const override;
	void connect(filedesc_t sockfd, unsigned short portnum) const override;

private:
	const std::array<unsigned char, bytesize> addr;

};


IPv4 parse_ipv4(const std::string &host);


IPv6 parse_ipv6(const std::string &host);


}


namespace std {


template<>
struct hash<unix::IPv4> {
    size_t operator()(const unix::IPv4 &ip) const {
        hash<array<unsigned char, unix::IPv4::bytesize>> hash;
        return hash(ip.parts());
    }
};


template<>
struct hash<unix::IPv6> {
    size_t operator()(const unix::IPv6 &ip) const {
        hash<array<unsigned char, unix::IPv6::bytesize>> hash;
        return hash(ip.parts());
    }
};


}
