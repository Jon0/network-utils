#include "queue.h"

namespace net {


Queue::Queue() {}
Queue::~Queue() {}


Queue Queue::operator+(const Queue &q) const {
    return *this;
}


void Queue::socket_open(const unix::Socket &s) {

}


}
