Build procedure (on Linux):
---------------------------
    g++ -std=c++11 *.cpp -o menu_based_app

    to run:
        $> ./menu_based_app

Notes:
------
A chained-hashing strategy has been followed, whereby in case of a collision, the element is added to a linked list anchored at the hash bucket.

The maximum number of hash-buckets has been limited to 65536. This does not by itself limit the number of elements that can be added to the hashmap. However, since the hash value returned by the hash function has to be lesser than or equal to 65535; adding a huge number of elements obviously results in a large number of collisions.

On doing various numbers of insertions of key-value pairs (both being strings of 10 characters generated randomly), the following was observed:

  +--------------------+--------------------------------+--------------+
  |                    |                                |              |
  |                    |  time taken (in milliseconds)  |              |
  |  number of random  |  [random string generation     |  number of   |
  |  strings inserted  |     +                          |  collisions  |
  |                    |   hashmap insertion]           |              |
  |                    |                                |              |
  +--------------------+--------------------------------+--------------+
  |                  1 |                              0 |            0 |
  +--------------------+--------------------------------+--------------+
  |                 10 |                              0 |            0 |
  +--------------------+--------------------------------+--------------+
  |                100 |                              0 |            0 |
  +--------------------+--------------------------------+--------------+
  |               1000 |                              2 |            5 |
  +--------------------+--------------------------------+--------------+
  |              10000 |                             22 |          725 |
  +--------------------+--------------------------------+--------------+
  |             100000 |                            155 |        48710 |
  +--------------------+--------------------------------+--------------+
  |            1000000 |                           3686 |       934464 |
  +--------------------+--------------------------------+--------------+
  |           10000000 |                         311309 |      9934464 |
  +--------------------+--------------------------------+--------------+

