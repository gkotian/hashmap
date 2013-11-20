#include <iostream>
#include <set>

#include "hashmap.hpp"

#define MASK_16 (((uint64_t)1 << 16) - 1)

// Function to generate a hash value based on the given string. In order to ensure that the
// computed hash value is lesser than 65536, it is xor-folded as described at:
//     http://isthe.com/chongo/tech/comp/fnv/
uint16_t HashMap::generateHash(const std::string& s) const
{
    // Since I am limiting the maximum vector size to 65536, my largest permitted index is 65535.
    // For doing the xor-folding, it would have been better to use a shorter initial digest
    // (maybe 32 bits long). But I have retained the value as requested in the assignment. The
    // upshot of this is more work for the CPU.
    const uint64_t INIT = 0xCBF29CE484222325; // inital digest
    const uint64_t PRIME = 0x00000100000001B3; // prime

    uint64_t digest = INIT;

    for (auto d : s)
    {
        digest = (digest ^ d) * PRIME;
    }

    return (((digest >> 16) ^ digest) & MASK_16);
}

// Constructor of the hash map. Once this function completes, it should be possible to index any
// element upto the maximum hashmap size.
HashMap::HashMap(uint32_t inMaxHashMapSize, bool inSharedKeysAllowed = false) : maxHashMapSize(inMaxHashMapSize),
                                                                                sharedKeysAllowed(inSharedKeysAllowed),
                                                                                numCollisions(0),
                                                                                numElements(0)
{
    // Currently, the maximum allowed size of the hash map is 65536.
    if (maxHashMapSize > 65536)
    {
        maxHashMapSize = 65536;
    }

    // Resize the hashmap vector, so that all internal lists are initialized to their default
    // state. This ensures that all indices of the vector upto the max size are valid.
    vHashMap.resize(maxHashMapSize);
}

uint32_t HashMap::getNumCollisions() const
{
    return numCollisions;
}

uint32_t HashMap::getNumElements() const
{
    return numElements;
}

// Function to insert an element into the hashmap
void HashMap::insertElement(const std::string& key, const std::string& value)
{
    uint16_t hashVal = generateHash(key);

    if (hashVal >= maxHashMapSize)
    {
        std::cout << "Hash function failure (hashVal = " << hashVal << ")" << std::endl;
        return;
    }

    std::list<Node>& listAtHashVal = vHashMap[hashVal];

    if (!listAtHashVal.empty())
    {
        ++numCollisions;

        for (auto& i : listAtHashVal)
        {
            if (i.getKey() == key)
            {
                // Since the key is already present in the list, this really doesn't count as a
                // collision.
                --numCollisions;

                if (sharedKeysAllowed == false)
                {
                    // If multiple entries with the same key are not allowed, then we need to
                    // update the existing value.
                    i.setValue(value);

                    return;
                }

                break;
            }
        }
    }

    // Add a new entry.
    listAtHashVal.push_front(Node(key, value));
    ++numElements;
}

// Function to delete an element from the hashmap
void HashMap::deleteElement(const std::string& key)
{
    uint16_t hashVal = generateHash(key);

    if (hashVal >= maxHashMapSize)
    {
        std::cout << "Element with key '" << key << "' not found." << std::endl;
        return;
    }

    std::list<Node>& listAtHashVal = vHashMap[hashVal];

    if (listAtHashVal.empty())
    {
        std::cout << "Element with key '" << key << "' not found." << std::endl;
        return;
    }

    bool collisionList = false;

    if (listAtHashVal.size() > 1)
    {
        // This means that there had previously been a collision.
        collisionList = true;
    }

    bool elementFound = false;

    for (auto i = listAtHashVal.begin(); i != listAtHashVal.end(); ++i)
    {
        if (i->getKey() == key)
        {
            std::cout << "Deleted : " << *i << std::endl;
            listAtHashVal.erase(i);

            if (collisionList)
            {
                --numCollisions;
            }

            --numElements;
            elementFound = true;
            break;
        }
    }

    if (elementFound == false)
    {
        std::cout << "Operation failure" << std::endl;
    }
}

void HashMap::printElement(const std::string& key)
{
    uint16_t hashVal = generateHash(key);

    if (hashVal >= maxHashMapSize)
    {
        std::cout << "Element with key '" << key << "' not found." << std::endl;
        return;
    }

    std::list<Node>& listAtHashVal = vHashMap[hashVal];

    if (listAtHashVal.empty())
    {
        std::cout << "Element with key '" << key << "' not found." << std::endl;
        return;
    }

    for (const auto& i : listAtHashVal)
    {
        if (i.getKey() == key)
        {
            std::cout << i << std::endl;
        }
    }
}

void HashMap::deleteAll()
{
    // Save the size before clearing the vector, so that it can be resized to its original size.
    // This resizing ensures that the vector can be successfully indexed upto the maximum
    // hashmap size even after it has been cleared.
    uint32_t s = vHashMap.size();
    vHashMap.clear();
    vHashMap.resize(s);

    numElements = 0;
    numCollisions = 0;
}

void HashMap::printAll() const
{
    if (numElements == 0)
    {
        std::cout << "The hash map is empty." << std::endl;
        return;
    }
    else if (numElements >= 100)
    {
        std::string yesOrNo;

        std::cout << "The hash map has " << numElements << " elements. Really print them all? (y/n): ";
        std::cin >> yesOrNo;

        if ((yesOrNo != "y") && (yesOrNo != "Y"))
        {
            return;
        }
    }

    for (uint32_t i = 0; i < maxHashMapSize; ++i)
    {
        if (!vHashMap[i].empty())
        {
            for (const auto& j : vHashMap[i])
            {
                std::cout << j << std::endl;
            }
        }
    }
}

void HashMap::printDetails() const
{
    std::cout << "Maximum number of hash buckets           : " << maxHashMapSize << std::endl;
    std::cout << "Maximum number of elements               : << not limited by program >>" << std::endl;
    std::cout << "Different elements can have the same key : " << (sharedKeysAllowed ? "Yes" : "No") << std::endl;
    std::cout << "Current number of elements               : " << numElements << std::endl;
    std::cout << "Current number of collisions             : " << numCollisions << std::endl;
}

void HashMap::printCollidingKeys() const
{
    if (numElements == 0)
    {
        std::cout << "The hash map is empty." << std::endl;
        return;
    }

    if (numCollisions == 0)
    {
        std::cout << "The hash map has no collisions." << std::endl;
        return;
    }
    else if (numCollisions >= 500)
    {
        std::string yesOrNo;

        std::cout << "The hash map has " << numCollisions << " collisions. Really print them all? (y/n): ";
        std::cin >> yesOrNo;

        if ((yesOrNo != "y") && (yesOrNo != "Y"))
        {
            return;
        }
    }

    for (uint32_t i = 0; i < maxHashMapSize; ++i)
    {
        if (vHashMap[i].size() > 1)
        {
            // If shared keys are allowed, then just because a list has more than one node doesn't
            // guarantee that a collision had indeed occurred. In this case, only unique keys in
            // the list indicate collision.
            if (sharedKeysAllowed)
            {
                std::set<std::string> setOfKeys;

                for (const auto& j : vHashMap[i])
                {
                    setOfKeys.insert(j.getKey());
                }

                std::cout << "at hash bucket " << i << " : ";

                for (const auto& j : setOfKeys)
                {
                    std::cout << j << ", ";
                }

                std::cout << std::endl;
            }
            else
            {
                std::cout << "at hash bucket " << i << " : ";

                for (const auto& j : vHashMap[i])
                {
                    std::cout << j.getKey() << ", ";
                }

                std::cout << std::endl;
            }
        }
    }
}

uint32_t HashMap::getSize() const
{
    return numElements;
}

bool HashMap::containsKey(const std::string& key) const
{
    uint16_t hashVal = generateHash(key);

    if (hashVal >= maxHashMapSize)
    {
        return false;
    }

    const std::list<Node>& listAtHashVal = vHashMap[hashVal];

    for (const auto& i : listAtHashVal)
    {
        if (i.getKey() == key)
        {
            return true;
        }
    }

    return false;
}
