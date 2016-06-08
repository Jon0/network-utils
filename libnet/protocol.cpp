#include "cluster.h"
#include "protocol.h"

namespace net {


ClusterOp::ClusterOp() {}


ClusterOp::ClusterOp(const ClusterOp &c)
    :
    optype(c.optype) {
    init();
}


ClusterOp::ClusterOp(const op_t &t, const std::string &data)
    :
    optype(t) {
    init();
}


ClusterOp::~ClusterOp() {}


ClusterOp::msg_t ClusterOp::apply(Message *src, Cluster *cl) const {
    if (optype == op_t::neighbor_req) {
        auto reply = src->reply(ClusterOp(op_t::neighbor_rsp, cl->neighborstr()));
        return reply;
    }
    return nullptr;
}


std::string ClusterOp::to_string() const {
    switch (optype) {
    case op_t::neighbor_req:
        return "nreq" + msgdata;
    case op_t::neighbor_rsp:
            return "nrsp" + msgdata;
    case op_t::join:
        return "join" + msgdata;
    }
}


void ClusterOp::from_string(const std::string &s) {
    std::string type = s.substr(0, 4);
    msgdata = s.substr(4);
    if (type == "nreq") {
        optype = op_t::neighbor_req;
    }
    else if (type == "nrsp") {
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


Message::msg_t Message::reply(const ClusterOp &newop) {
    return std::make_shared<Message>(source, id.get(), newop);
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
    return std::make_shared<Message>(host, next_id++, ClusterOp(t, ""));
}


}
