#pragma once

#include <array>
#include <string>

#include "libutil/hash.h"
#include "file.h"

namespace unix {


std::array<unsigned char, 4> parse_addr(const std::string &str);


class NetAddress {
public:
	virtual ~NetAddress() {}
	virtual filedesc_t connect(int port) const = 0;
};


class IPv4 : public NetAddress {
public:
	IPv4(const std::array<unsigned char, 4> &addr);
	virtual ~IPv4();

	std::array<unsigned char, 4> parts() const;
	std::string str() const;


	filedesc_t connect(int port) const override;

private:
	const std::array<unsigned char, 4> addr;
};


filedesc_t listen_port(int port);


class TcpAcceptor {
public:
	TcpAcceptor(int port);

	filedesc_t acceptfd() const;

private:
	const FileDesc sockfd;

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
