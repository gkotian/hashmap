#include <iostream>
#include <algorithm>
#include <sys/time.h>

#include "hashmap.hpp"

const uint32_t MAX_HASHMAP_SIZE = 65536;
const bool     SHARED_KEYS_ALLOWED = false;

uint64_t getCurTimeInMS()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    uint64_t ret = tv.tv_usec;

    // Convert microseconds to milliseconds.
    ret /= 1000;

    // Convert seconds to milliseconds, and add to previous value.
    ret += (tv.tv_sec * 1000);

    return ret;
}

std::string getRandomString(size_t length)
{
    auto randchar = []() -> char
                    {
                        const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                        const size_t max_index = (sizeof(charset) - 1);
                        return charset[ rand() % max_index ];
                    };

    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

void showMenu()
{
    std::cout << "1. Insert an element" << std::endl;
    std::cout << "2. Delete an element" << std::endl;
    std::cout << "3. Print element(s)" << std::endl;
    std::cout << "4. Print the entire hash map" << std::endl;
    std::cout << "5. Delete the entire hash map" << std::endl;
    std::cout << "6. Print details about the hash map" << std::endl;
    std::cout << "7. Generate random key-value pairs, and insert them" << std::endl;
    std::cout << "8. List colliding keys" << std::endl;
    std::cout << "9. Exit" << std::endl;
}

int main()
{
    uint8_t option;
    HashMap hashMap(MAX_HASHMAP_SIZE, SHARED_KEYS_ALLOWED);

    srand(time(0));

    showMenu();

    do
    {
        std::cout << "Enter menu option here: ";
        std::cin >> option;

        switch (option)
        {
            case '1':
            {
                std::string key, value;

                std::cout << "    Enter the key: ";
                std::cin >> key;

                std::cout << "    Enter the value: ";
                std::cin >> value;

                hashMap.insertElement(key, value);
                std::cout << "    Done" << std::endl;

                break;
            }

            case '2':
            {
                std::string key;

                std::cout << "    Enter the key: ";
                std::cin >> key;

                hashMap.deleteElement(key);

                break;
            }

            case '3':
            {
                std::string key;

                std::cout << "    Enter the key: ";
                std::cin >> key;

                hashMap.printElement(key);

                break;
            }

            case '4':
            {
                hashMap.printAll();
                break;
            }

            case '5':
            {
                hashMap.deleteAll();
                std::cout << "    Done" << std::endl;
                break;
            }

            case '6':
            {
                hashMap.printDetails();
                break;
            }

            case '7':
            {
                uint64_t numRandomPairs;

                std::cout << "    How many key-value pairs to generate? ";
                std::cin >> numRandomPairs;

                uint64_t startTime = getCurTimeInMS();

                for (uint64_t i = 0; i < numRandomPairs; ++i)
                {
                    hashMap.insertElement(getRandomString(10), getRandomString(10));
                }

                uint64_t endTime = getCurTimeInMS();
                std::cout << "    Done in approximately " << (endTime - startTime) << " milliseconds" << std::endl;

                break;
            }

            case '8':
            {
                hashMap.printCollidingKeys();
                break;
            }

            case '9':
            {
                std::cout << "Thank you!!" << std::endl;
                break;
            }

            default:
            {
                std::cout << "Invalid option, here's the menu again..." << std::endl;
                showMenu();
                break;
            }
        }
    }
    while (option != '9');
}
