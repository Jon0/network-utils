#include "cluster.h"
#include "protocol.h"

namespace net {


ClusterOp::ClusterOp() {}


ClusterOp::ClusterOp(const ClusterOp &c)
    :
    optype(c.optype) {
    init();
}


ClusterOp::ClusterOp(const op_t &t)
    :
    optype(t) {
    init();
}


ClusterOp::~ClusterOp() {}


ClusterOp::reply_t ClusterOp::apply(Message *src, Cluster *cl) const {
    if (optype == op_t::neighbor_req) {
        auto reply = std::make_shared<Message>();
        reply->init(cl->neighborstr());
        return reply;
    }
    return nullptr;
}


std::string ClusterOp::to_string() const {
    switch (optype) {
    case op_t::neighbor_req:
        return "nreq";
    case op_t::neighbor_rsp:
            return "nrsp";
    case op_t::join:
        return "join";
    }
}


void ClusterOp::from_string(const std::string &s) {
    if (s == "nreq") {
        optype = op_t::neighbor_req;
    }
    else if (s == "nrsp") {
        optype = op_t::neighbor_rsp;
    }
    else {
        optype = op_t::join;
    }
}


Message::Message() {}


Message::Message(const Message &m)
    :
    Message(m.source, m.id.get(), m.msg) {}


Message::Message(const Host &h, int64_t id, const ClusterOp &op)
    :
    source(h),
    id(id),
    msg(op) {
    init();
}


Message::~Message() {}


ClusterOp &Message::op() {
    return msg;
}


std::vector<const util::Stringable *> Message::to_array() const {
    std::vector<const util::Stringable *> result;
    result.push_back(&source);
    result.push_back(&id);
    result.push_back(&msg);
    return result;
}


util::Stringable *Message::at(size_t e) {
    switch (e) {
    case 0:
        return &source;
    case 1:
        return &id;
    case 2:
        return &msg;
    default:
        return nullptr;
    }
}


MessageSrc::MessageSrc()
    :
    host(this_host()),
    next_id(1) {}


MessageSrc::~MessageSrc() {}


MessageSrc::msg_t MessageSrc::create(const op_t &t) {
    return std::make_shared<Message>(host, next_id++, ClusterOp(t));
}


}
