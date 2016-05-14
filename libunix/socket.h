#pragma once

#include <array>
#include <chrono>
#include <string>

#include "libutil/hash.h"
#include "file.h"

namespace unix {


using millisecs = std::chrono::milliseconds;


enum class AddressType {
	ipv4,
	ipv6
};


std::array<unsigned char, 4> parse_addr(const std::string &str);


filedesc_t listen_port(int port);


class NetAddress {
public:
	virtual ~NetAddress() {}
	virtual AddressType type() const = 0;
	virtual millisecs ping(size_t blocksize) const = 0;
	virtual filedesc_t connect(int port) const = 0;
};


class IPv4 : public NetAddress {
public:
	IPv4(const std::array<unsigned char, 4> &addr);
	virtual ~IPv4();

	bool operator==(const IPv4 &ip) const;

	std::array<unsigned char, 4> parts() const;
	std::string str() const;

	AddressType type() const override;
	millisecs ping(size_t blocksize) const override;
	filedesc_t connect(int port) const override;

private:
	const std::array<unsigned char, 4> addr;
};


class IPv6 : public NetAddress {
public:
	IPv6(const std::array<unsigned char, 12> &addr);
	virtual ~IPv6();

	bool operator==(const IPv6 &ip) const;

	std::array<unsigned char, 12> parts() const;
	std::string str() const;

	AddressType type() const override;
	millisecs ping(size_t blocksize) const override;
	filedesc_t connect(int port) const override;

private:
	const std::array<unsigned char, 12> addr;

};


class TcpAcceptor : public FileDesc {
public:
	TcpAcceptor(int port);

	filedesc_t acceptfd() const;
};


}


namespace std {

template<>
struct hash<unix::IPv4> {
    size_t operator()(const unix::IPv4 &ip) const {
        hash<array<unsigned char, 4>> hash;
        return hash(ip.parts());
    }
};

}
