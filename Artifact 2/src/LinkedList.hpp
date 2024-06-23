#ifndef _LINKEDLIST_HPP_
#define _LINKEDLIST_HPP_

#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <sstream>

/**
 * @brief Custom error class for LinkedList-related errors.
 */
class LinkedListError : public std::runtime_error
{
public:
    /**
     * @brief Constructor for LinkedListError.
     * @param msg Error message.
     */
    LinkedListError(const std::string &msg)
        : std::runtime_error(std::string("LinkedList : ").append(msg))
    {
    }
};

/**
 * @brief Structure to hold bid information.
 */
struct LinkedListBid
{
    std::string bidId; ///< Unique identifier for the bid
    std::string title; ///< Title of the bid
    std::string fund;  ///< Fund associated with the bid
    double amount;     ///< Amount of the bid

    /**
     * @brief Default constructor.
     */
    LinkedListBid() : amount(0.0) {}

    /**
     * @brief Parameterized constructor.
     * @param id Bid ID.
     * @param t Title.
     * @param f Fund.
     * @param a Amount.
     */
    LinkedListBid(std::string id, std::string t, std::string f, double a)
        : bidId(id), title(t), fund(f), amount(a) {}
};

/**
 * @brief Structure for linked list node.
 */
struct Node
{
    LinkedListBid bid; ///< The bid data
    Node *next;        ///< Pointer to the next node

    /**
     * @brief Default constructor.
     */
    Node() : next(nullptr) {}

    /**
     * @brief Parameterized constructor.
     * @param aBid Bid data.
     */
    Node(LinkedListBid aBid) : bid(aBid), next(nullptr) {}
};

/**
 * @brief Linked list class for storing bids.
 */
class LinkedList
{
private:
    Node *head;      ///< Pointer to the head node
    Node *tail;      ///< Pointer to the tail node
    int numElements; ///< Number of elements in the list

public:
    /**
     * @brief Constructor.
     */
    LinkedList();

    /**
     * @brief Destructor.
     */
    ~LinkedList();

    /**
     * @brief Append a bid to the end of the list.
     * @param bid The bid to append.
     */
    void append(const LinkedListBid &bid);

    /**
     * @brief Prepend a bid to the beginning of the list.
     * @param bid The bid to prepend.
     */
    void prepend(const LinkedListBid &bid);

    /**
     * @brief Print all bids in the list.
     */
    void printList() const;

    /**
     * @brief Remove a bid from the list by its ID.
     * @param bidId The ID of the bid to remove.
     * @return true if the bid was found and removed, false otherwise.
     */
    bool remove(const std::string &bidId);

    /**
     * @brief Search for a bid by its ID.
     * @param bidId The ID of the bid to search for.
     * @param bid The bid data if found.
     * @return true if the bid was found, false otherwise.
     */
    bool find(const std::string &bidId, LinkedListBid &bid) const;

    /**
     * @brief Get the size of the list.
     * @return The number of elements in the list.
     */
    int size() const;
};

#endif /*!_LINKEDLIST_HPP_*/
