#include <iostream>

#include "node.hpp"

Node::Node(const std::string& k, const std::string& v) : key(k), value(v)
{
}

std::string Node::getKey() const
{
    return key;
}

std::string Node::getValue() const
{
    return value;
}

void Node::setValue(const std::string& v)
{
    value = v;
}

std::ostream& operator<<(std::ostream& out, const Node& node)
{
    out << node.getKey() << " --> " << node.getValue();

    return out;
}
