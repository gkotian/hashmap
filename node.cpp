//---- Headers ------------------------------------------------------------------------------------

#include <iostream>

#include "node.hpp"

//---- Constructor(s) -----------------------------------------------------------------------------

Node::Node(const std::string& k, const std::string& v) : key(k), value(v)
{
}

//---- Public member functions --------------------------------------------------------------------

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

//---- Other global functions ---------------------------------------------------------------------

std::ostream& operator<<(std::ostream& out, const Node& node)
{
    out << "    " << node.getKey() << " --> " << node.getValue();

    return out;
}

