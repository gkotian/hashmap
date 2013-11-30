#pragma once

//---- Headers ------------------------------------------------------------------------------------

#include <vector>
#include <list>
#include <cstdint>

#include "node.hpp"

//---- Class definition(s) ------------------------------------------------------------------------

class HashMap
{
private:
    uint32_t maxHashMapSize;
    bool sharedKeysAllowed;
    std::vector< std::list<Node> > vHashMap;
    uint32_t numCollisions;
    uint32_t numElements;
    uint32_t numOccupiedBuckets;
    uint16_t generateHash(const std::string&) const;

public:
    HashMap(uint32_t, bool);
    uint32_t getNumCollisions() const;
    uint32_t getNumElements() const;
    void insertElement(const std::string&, const std::string&);
    void deleteElement(const std::string&);
    void printElement(const std::string&);
    void deleteAll();
    void printAll() const;
    void printDetails() const;
    void printCollidingKeys() const;

    // Additional functions as requested in point # 3 of the assignment.
    uint32_t getSize() const;
    bool containsKey(const std::string&) const;
};

