#include <iostream>

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


std::string ClusterOp::desc() const {
    switch (optype) {
    case op_t::neighbor_req:
        return "neighbors request (" + msgdata + ")";
    case op_t::neighbor_rsp:
            return "neighbors response (" + msgdata + ")";
    case op_t::join_req:
        return "join request (" + msgdata + ")";
    case op_t::join_rsp:
        return "join response (" + msgdata + ")";
    }
}


ClusterOp::msg_t ClusterOp::apply(Message *src, Cluster *cl) const {
    std::cout << src->desc() << " applied\n";
    if (optype == op_t::neighbor_req) {
        return src->reply(ClusterOp(op_t::neighbor_rsp, cl->neighborstr()));
    }
    else if (optype == op_t::join_req) {
        return src->reply(ClusterOp(op_t::join_rsp, ""));
    }
    return nullptr;
}


std::string ClusterOp::to_string() const {
    switch (optype) {
    case op_t::neighbor_req:
        return "nreq" + msgdata;
    case op_t::neighbor_rsp:
            return "nrsp" + msgdata;
    case op_t::join_req:
        return "join" + msgdata;
    case op_t::join_rsp:
        return "jrsp" + msgdata;
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
    else if (type == "join") {
        optype = op_t::join_req;
    }
    else {
        optype = op_t::join_rsp;
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


std::string Message::desc() const {
    return "[" + source.desc() + ", " + std::to_string(id.get()) + "] " + msg.desc();
 }


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


MessageSrc::msg_t MessageSrc::create(const ClusterOp &o) {
    return std::make_shared<Message>(host, next_id++, o);
}


}
