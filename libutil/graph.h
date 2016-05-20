#pragma once

#include <functional>
#include <vector>

namespace util {


template<typename Node, typename Edge>
class Graph {
public:
    Graph() {}

    void apply(std::function<void(const Node &)> fn);

private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;

};


template<typename Node, typename Edge>
class Tree : public Graph<Node, Edge> {
public:
    Tree() {}

};


}
