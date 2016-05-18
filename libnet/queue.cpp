#include "queue.h"

namespace net {


Queue::Queue() {}
Queue::~Queue() {}


Queue Queue::operator+(const Queue &q) const {
    return *this;
}


}
