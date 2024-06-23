#include <iostream>
#include <string>
#include "CSVparser.hpp"
#include "LinkedList.hpp"
#include "Hashmap.hpp"

/**
 * @brief Main function to load bids into data structures based on user input.
 *
 * @param argc Number of arguments.
 * @param argv Argument values.
 * @return int Exit status.
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <structure_type>" << std::endl;
        std::cerr << "structure_type: 1 for Linked List, 2 for Hashmap" << std::endl;
        return 1;
    }

    std::string csvPath = "C:\\Users\\Michael Ladderbush\\Desktop\\CS-300\\Module 3 Assignment\\src\\eBid_Monthly_Sales_Dec_2016.csv";
    int structure = std::stoi(argv[1]);

    if (structure == 1)
    {
        loadBidsIntoLinkedList(csvPath);
    }
    else if (structure == 2)
    {
        loadBidsIntoHashmap(csvPath);
    }
    else
    {
        std::cerr << "Invalid structure. Please specify '1' for Linked List or '2' for Hashmap." << std::endl;
        return 1;
    }

    return 0;
}
