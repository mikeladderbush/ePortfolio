//============================================================================
// Name        : Hashmap.cpp
// Author      : Michael Ladderbush
// Version     : 1.0
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include "Hashmap.hpp"

// Initialize static members
Hashmap::CollisionMethod Hashmap::method;
std::vector<Hashmap::HashPair> Hashmap::table;
std::vector<std::list<Hashmap::HashPair>> Hashmap::buckets;
int Hashmap::bucketCount;
int Hashmap::numElements;
double Hashmap::loadFactor;

/**
 * @brief Get the bucket index for a given key using hashing.
 * @param keyHash The hash of the key.
 * @return The index of the bucket.
 */
size_t Hashmap::getBucketIndex(const std::string &keyHash)
{
    return std::hash<std::string>{}(keyHash) % bucketCount;
}

/**
 * @brief Get the index for a given key using linear probing.
 * @param keyHash The hash of the key.
 * @return The index in the table.
 */
size_t Hashmap::getLinearIndex(const std::string &keyHash)
{
    size_t index = std::hash<std::string>{}(keyHash) % table.size();
    while (table[index].keyHash != 0 && table[index].value.bidId != keyHash)
    {
        index = (index + 1) % table.size(); // Linear probing
    }
    return index;
}

/**
 * @brief Resize the bucket array to a new size.
 * @param newSize The new size of the bucket array.
 */
void Hashmap::resizeBuckets(int newSize)
{
    std::vector<std::list<HashPair>> newBuckets(newSize);
    for (auto &bucket : buckets)
    {
        for (auto &pair : bucket)
        {
            size_t newIndex = pair.keyHash % newSize;
            newBuckets[newIndex].push_back(pair);
        }
    }
    buckets = std::move(newBuckets);
}

/**
 * @brief Resize the table based on the collision method.
 */
void Hashmap::resizeTable()
{
    if (method == LINEAR_PROBING)
    {
        // Resize linear probing table
    }
    else
    {
        int newSize = buckets.size() * 2;
        resizeBuckets(newSize);
    }
}

/**
 * @brief Resize the linear probing table to a new size.
 * @param newSize The new size of the table.
 */
void Hashmap::resizeLinearTable(int newSize)
{
    std::vector<HashPair> newTable(newSize);
    for (const auto &pair : table)
    {
        if (pair.keyHash != 0)
        {
            size_t newIndex = std::hash<std::string>{}(pair.value.bidId) % newSize;
            while (newTable[newIndex].keyHash != 0)
            {
                newIndex = (newIndex + 1) % newSize;
            }
            newTable[newIndex] = pair;
        }
    }
    table = std::move(newTable);
}

/**
 * @brief Transfer elements to bucket hashing.
 */
void Hashmap::transferToBuckets()
{
    int newSize = bucketCount * 2;
    std::vector<std::list<HashPair>> newBuckets(newSize);
    for (const auto &pair : table)
    {
        if (pair.keyHash != 0)
        {
            size_t newIndex = pair.keyHash % newSize;
            newBuckets[newIndex].emplace_back(pair.value.bidId, pair.value);
        }
    }
    buckets = std::move(newBuckets);
    bucketCount = newSize;
    method = BUCKETS;
}

/**
 * @brief Constructor for Hashmap.
 */
Hashmap::Hashmap()
{
    bucketCount = 10;
    buckets.resize(bucketCount);
    numElements = 10;
    loadFactor = 0.75;
}

/**
 * @brief Destructor for Hashmap.
 */
Hashmap::~Hashmap()
{
}

/**
 * @brief Insert a bid into the hashmap.
 * @param bid The bid to insert.
 */
void Hashmap::insert(const HashmapBid &bid)
{
    if (method == LINEAR_PROBING)
    {
        if (numElements >= table.size() * loadFactor)
        {
            if (numElements >= 5000)
            {
                transferToBuckets();
            }
            else
            {
                resizeLinearTable(table.size() * 2);
            }
        }
        size_t index = getLinearIndex(bid.bidId);
        if (table[index].keyHash == 0)
        {
            ++numElements;
        }
        table[index] = {bid.bidId, bid};
    }
    else
    {
        if (numElements >= bucketCount * 2)
        {
            resizeBuckets(bucketCount * 2);
        }

        size_t index = getBucketIndex(bid.bidId);
        buckets[index].emplace_back(bid.bidId, bid);
        ++numElements;
    }
}

/**
 * @brief Retrieve a bid from the hashmap.
 * @param key The key of the bid to retrieve.
 * @param bid The bid object to populate if found.
 * @return True if the bid is found, otherwise false.
 */
bool Hashmap::get(const std::string &key, HashmapBid &bid)
{
    if (method == LINEAR_PROBING)
    {
        size_t index = getLinearIndex(key);
        if (table[index].keyHash != 0)
        {
            bid = table[index].value;
            return true;
        }
    }
    else
    {
        size_t index = getBucketIndex(key);
        for (const auto &pair : buckets[index])
        {
            if (pair.value.bidId == key)
            {
                bid = pair.value;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Remove a bid from the hashmap.
 * @param key The key of the bid to remove.
 * @return True if the bid is removed, otherwise false.
 */
bool Hashmap::remove(const std::string &key)
{
    if (method == LINEAR_PROBING)
    {
        size_t index = getLinearIndex(key);
        if (table[index].keyHash != 0)
        {
            table[index] = {};
            --numElements;
            return true;
        }
    }
    else
    {
        size_t index = getBucketIndex(key);
        auto &bucket = buckets[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->value.bidId == key)
            {
                bucket.erase(it);
                --numElements;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Get the number of elements in the hashmap.
 * @return The number of elements.
 */
int Hashmap::size()
{
    return numElements;
}
