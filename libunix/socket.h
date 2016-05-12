#pragma once

#include <array>
#include <string>

#include "file.h"

namespace unix {


class NetAddress {
public:
	virtual ~NetAddress() {}
	virtual filedesc_t connect(int port) const = 0;
};


class IPv4 : public NetAddress {
public:
	IPv4(const std::array<unsigned char, 4> &addr);

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
