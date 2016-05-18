#pragma once

#include <chrono>
#include <memory>

#include "address.h"

namespace unix {


using millisecs = std::chrono::milliseconds;


filedesc_t ipv4_socket(int socket_type = SOCK_STREAM, int protocol = 0);
filedesc_t ipv6_socket(int socket_type = SOCK_STREAM, int protocol = 0);


class Socket : public FileDesc {
public:
	Socket(const Socket &s);
	Socket(const NetAddress *l, const NetAddress *r, const filedesc_t &fd);

	NetAddress *local() const;
	NetAddress *remote() const;

	std::streamsize recv(char *buf, std::size_t count);
	std::streamsize send(const char *buf, std::size_t count);

private:
	std::unique_ptr<NetAddress> local_addr;
	std::unique_ptr<NetAddress> remote_addr;

};


filedesc_t listen_ipv4(unsigned short portnum);


class TcpAcceptor : public FileDesc {
public:
	TcpAcceptor(int port);

	Socket accept() const;

private:
	std::unique_ptr<NetAddress> local_addr;

};


millisecs ping(NetAddress *addr);


}
