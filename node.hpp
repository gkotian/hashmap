#pragma once

//---- Headers ------------------------------------------------------------------------------------

#include <string>
#include <iostream>

//---- Class definition(s) ------------------------------------------------------------------------

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

//---- Other global function prototypes -----------------------------------------------------------

std::ostream& operator<<(std::ostream&, const Node&);

