#ifndef _HASHMAP_HPP_
#define _HASHMAP_HPP_

#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <sstream>

/**
 * @brief Custom exception class for Hashmap-related errors.
 */
class HashmapError : public std::runtime_error
{
public:
    /**
     * @brief Constructor for HashmapError.
     * @param msg Error message.
     */
    HashmapError(const std::string &msg)
        : std::runtime_error(std::string("Hashmap : ").append(msg))
    {
    }
};

/**
 * @brief Structure to represent a bid.
 */
struct HashmapBid
{
    std::string bidId;
    std::string title;
    std::string fund;
    double amount;

    /**
     * @brief Default constructor.
     */
    HashmapBid() : amount(0.0) {}

    /**
     * @brief Parameterized constructor.
     * @param id Bid ID.
     * @param t Title.
     * @param f Fund.
     * @param a Amount.
     */
    HashmapBid(std::string id, std::string t, std::string f, double a)
        : bidId(id), title(t), fund(f), amount(a) {}
};

/**
 * @brief Class for a Hashmap to store bids.
 */
class Hashmap
{
private:
    /**
     * @brief Enum for collision handling methods.
     */
    enum CollisionMethod
    {
        BUCKETS,
        LINEAR_PROBING
    };
    static CollisionMethod method; ///< Collision handling method

    /**
     * @brief Structure to represent a key-value pair in the hashmap.
     */
    struct HashPair
    {
        size_t keyHash;   ///< Hash of the key
        HashmapBid value; ///< Value associated with the key

        /**
         * @brief Default constructor.
         */
        HashPair() : keyHash(0), value() {}

        /**
         * @brief Parameterized constructor.
         * @param key Key as a string.
         * @param bid Value as a HashmapBid.
         */
        HashPair(const std::string &key, const HashmapBid &bid)
            : keyHash(std::hash<std::string>{}(key)), value(bid) {}
    };

    static std::vector<HashPair> table;              ///< Vector for linear probing
    static std::vector<std::list<HashPair>> buckets; ///< Vector of lists for bucket hashing
    static int bucketCount;                          ///< Number of buckets
    static int numElements;                          ///< Number of elements in the hashmap
    static double loadFactor;                        ///< Load factor threshold

    /**
     * @brief Get the bucket index for a given key.
     * @param key The key to hash.
     * @return The index of the bucket.
     */
    size_t getBucketIndex(const std::string &key);

    /**
     * @brief Get the linear probing index for a given key.
     * @param key The key to hash.
     * @return The index in the table.
     */
    size_t getLinearIndex(const std::string &key);

    /**
     * @brief Resize the table for linear probing.
     */
    void resizeTable();

    /**
     * @brief Resize the linear probing table to a new size.
     * @param newSize The new size of the table.
     */
    void resizeLinearTable(int newSize);

    /**
     * @brief Resize the buckets vector to a new size.
     * @param newSize The new size of the buckets vector.
     */
    void resizeBuckets(int newSize);

    /**
     * @brief Transfer elements to bucket hashing.
     */
    void transferToBuckets();

public:
    /**
     * @brief Constructor for Hashmap.
     */
    Hashmap();

    /**
     * @brief Destructor for Hashmap.
     */
    ~Hashmap();

    /**
     * @brief Insert a bid into the hashmap.
     * @param bid The bid to insert.
     */
    void insert(const HashmapBid &bid);

    /**
     * @brief Retrieve a bid from the hashmap.
     * @param key The key of the bid to retrieve.
     * @param bid The bid object to populate if found.
     * @return True if the bid is found, otherwise false.
     */
    bool get(const std::string &key, HashmapBid &bid);

    /**
     * @brief Remove a bid from the hashmap.
     * @param key The key of the bid to remove.
     * @return True if the bid is removed, otherwise false.
     */
    bool remove(const std::string &key);

    /**
     * @brief Get the number of elements in the hashmap.
     * @return The number of elements.
     */
    int size();
};

#endif /*!_HASHMAP_HPP_*/
