#pragma once

#include <chrono>
#include <memory>

#include "address.h"

namespace unix {


using millisecs = std::chrono::milliseconds;


filedesc_t ipv4_socket(int socket_type = SOCK_STREAM, int protocol = 0);
filedesc_t ipv6_socket(int socket_type = SOCK_STREAM, int protocol = 0);
filedesc_t addr_socket(const NetAddress *r, int socket_type = SOCK_STREAM, int protocol = 0);


class Socket : public FileDesc {
public:
	Socket(const Socket &s);
	Socket(const NetAddress *r, unsigned short portnum);
	Socket(const NetAddress *l, const NetAddress *r, const filedesc_t &fd);
	virtual ~Socket();

	std::string rstr() const;

	NetAddress *local() const;
	NetAddress *remote() const;

	std::streamsize recv(char *buf, std::size_t count);
	std::streamsize send(const char *buf, std::size_t count);

	bool connected() const;
	void shutdown(int how);

	virtual bool open() const override;

private:
	std::unique_ptr<NetAddress> local_addr;
	std::unique_ptr<NetAddress> remote_addr;
	bool active;

};


filedesc_t listen_ipv4(unsigned short portnum);


class TcpAcceptor : public FileDesc {
public:
	TcpAcceptor(const TcpAcceptor &a);
	TcpAcceptor(int port);

	NetAddress *local() const;
	Socket accept() const;
	std::shared_ptr<Socket> accept_shared() const;
	std::pair<IPv4, filedesc_t> acceptfd() const;

private:
	std::unique_ptr<NetAddress> local_addr;

};


millisecs ping(NetAddress *addr);


}
