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
	using addr_t = typename util::Channel::addr_t;
	static constexpr addr_t attr_id = 3;

	Socket(const Socket &s);
	Socket(const NetAddress *l, const NetAddress *r, const filedesc_t &fd);
	virtual ~Socket();

    virtual addr_t type() const override;

	NetAddress *local() const;
	NetAddress *remote() const;

	std::streamsize recv(char *buf, std::size_t count);
	std::streamsize send(const char *buf, std::size_t count);

	bool connected() const;
	void shutdown(int how);

private:
	std::unique_ptr<NetAddress> local_addr;
	std::unique_ptr<NetAddress> remote_addr;
	bool active;

};


filedesc_t listen_ipv4(unsigned short portnum);


class TcpAcceptor : public FileDesc {
public:
	using addr_t = typename util::Channel::addr_t;
	static constexpr addr_t attr_id = 5;

	TcpAcceptor(const TcpAcceptor &a);
	TcpAcceptor(int port);

	virtual addr_t type() const override;

	NetAddress *local() const;
	Socket accept() const;
	std::shared_ptr<Socket> accept_shared() const;
	std::pair<IPv4, filedesc_t> acceptfd() const;

private:
	std::unique_ptr<NetAddress> local_addr;

};


millisecs ping(NetAddress *addr);


}
