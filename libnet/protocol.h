#pragma once

#include <memory>
#include <string>
#include <vector>

#include "libprot/message.h"

#include "host.h"

namespace net {


class Cluster;
class Message;


enum class op_t {
    neighbor_req,
    neighbor_rsp,
    join
};


class ClusterOp : public util::Stringable {
public:
    using msg_t = std::shared_ptr<Message>;

    ClusterOp();
    ClusterOp(const ClusterOp &c);
    ClusterOp(const op_t &t, const std::string &data);
    virtual ~ClusterOp();

    msg_t apply(Message *src, Cluster *cl) const;

    std::string to_string() const override;
    void from_string(const std::string &s) override;

private:
    op_t optype;
    std::string msgdata;

};


class Message : public util::StringList {
public:
    using msg_t = std::shared_ptr<Message>;

    Message();
    Message(const Message &m);
    Message(const Host &h, int64_t id, const ClusterOp &op);
    virtual ~Message();

    ClusterOp &op();
    msg_t reply(const ClusterOp &newop);

    std::vector<const util::Stringable *> to_array() const override;
    util::Stringable *at(size_t e) override;

private:
    Host source;
    util::Block<int64_t> id;
    ClusterOp msg;

};


class MessageSrc {
public:
    using msg_t = std::shared_ptr<Message>;

    MessageSrc();
    virtual ~MessageSrc();

    msg_t create(const op_t &t);

private:
    Host host;
    int64_t next_id;

};


}
