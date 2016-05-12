#pragma once

#include <string>

#include "file.h"

namespace unix {


filedesc_t listen_port(int port);


class TcpAcceptor {
public:
	TcpAcceptor(int port);

	filedesc_t acceptfd() const;

private:
	const FileDesc sockfd;

};


}
