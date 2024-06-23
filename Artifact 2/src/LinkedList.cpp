//============================================================================
// Name        : LinkedList.cpp
// Author      : Michael Ladderbush
// Version     : 2.0
//============================================================================

#include <algorithm>
#include <iostream>
#include <ctime>
#include "LinkedList.hpp"

Node *head = nullptr;
Node *tail = nullptr;
int numElements = 0;

/**
 * @brief LinkedList Constructor.
 */
LinkedList::LinkedList() = default;

/**
 * @brief LinkedList Destructor.
 * Deletes all nodes in the list.
 */
LinkedList::~LinkedList()
{
    Node *current = head;
    Node *temp;

    while (current != nullptr)
    {
        temp = current;
        current = current->next;
        delete temp;
    }
}

/**
 * @brief Append a bid to the end of the list.
 * @param bid The bid to append.
 */
void LinkedList::append(const LinkedListBid &bid)
{
    Node *newNode = new Node(bid);

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    numElements++;
}

/**
 * @brief Prepend a bid to the beginning of the list.
 * @param bid The bid to prepend.
 */
void LinkedList::prepend(const LinkedListBid &bid)
{
    Node *newNode = new Node(bid);

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }

    numElements++;
}

/**
 * @brief Remove a bid from the list by its ID.
 * @param bidId The ID of the bid to remove.
 * @return true if the bid was found and removed, false otherwise.
 */
bool LinkedList::remove(const std::string &bidId)
{
    if (head == nullptr)
    {
        return false;
    }

    if (head->bid.bidId == bidId)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        numElements--;
        return true;
    }

    Node *current = head;

    while (current->next != nullptr)
    {
        if (current->next->bid.bidId == bidId)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            delete temp;
            numElements--;
            return true;
        }

        current = current->next;
    }

    return false;
}

/**
 * @brief Search for a bid by its ID.
 * @param bidId The ID of the bid to search for.
 * @param bid The bid data if found.
 * @return true if the bid was found, false otherwise.
 */
bool LinkedList::find(const std::string &bidId, LinkedListBid &bid) const
{
    Node *current = head;

    while (current != nullptr)
    {
        if (current->bid.bidId == bidId)
        {
            bid = current->bid;
            return true; // Bid found
        }
        current = current->next;
    }

    return false; // Bid not found
}

/**
 * @brief Get the size of the list.
 * @return The number of elements in the list.
 */
int LinkedList::size() const
{
    return numElements;
}
