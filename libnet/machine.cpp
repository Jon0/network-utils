#include "machine.h"

namespace net {

Machine::Machine(const machine_key &id)
    :
    id(id),
    fd(id.connect(2620)) {}


Machine::~Machine() {}

}
