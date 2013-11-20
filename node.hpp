#pragma once

#include <string>
#include <iostream>

class Node
{
private:
    std::string key;
    std::string value;

public:
    Node(const std::string&, const std::string&);
    std::string getKey() const;
    std::string getValue() const;
    void setValue(const std::string&);
};

std::ostream& operator<<(std::ostream&, const Node&);
