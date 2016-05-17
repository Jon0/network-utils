#pragma once

#include "file.h"

namespace unix {


filedesc_t listen_port(int port);


class TcpAcceptor : public FileDesc {
public:
	TcpAcceptor(int port);

	filedesc_t acceptfd() const;
};


}
