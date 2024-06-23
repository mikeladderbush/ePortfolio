#ifndef _CSVPARSER_HPP_
#define _CSVPARSER_HPP_

#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>
#include "LinkedList.hpp"
#include "Hashmap.hpp"

/**
 * @brief Convert a string to a double, removing any specified character.
 * @param str The string to convert.
 * @param ch The character to remove.
 * @return The converted double value.
 */
double strToDouble(std::string str, char ch);

/**
 * @brief Load bids from a CSV file into a linked list.
 * @param csvPath The path to the CSV file.
 */
void loadBidsIntoLinkedList(const std::string &csvPath);

/**
 * @brief Load bids from a CSV file into a hashmap.
 * @param csvPath The path to the CSV file.
 */
void loadBidsIntoHashmap(const std::string &csvPath);

/**
 * @brief Custom error class for CSV parser errors.
 */
class Error : public std::runtime_error
{
public:
    /**
     * @brief Construct a new Error object.
     * @param msg The error message.
     */
    Error(const std::string &msg) : std::runtime_error(std::string("CSVparser : ").append(msg)) {}
};

/**
 * @brief Class representing a row in the CSV file.
 */
class Row
{
public:
    /**
     * @brief Construct a new Row object.
     * @param header The header of the CSV file.
     */
    Row(const std::vector<std::string> &header);
    ~Row(void);

public:
    /**
     * @brief Get the number of elements in the row.
     * @return The number of elements.
     */
    unsigned int size(void) const;

    /**
     * @brief Add a value to the row.
     * @param value The value to add.
     */
    void push(const std::string &value);

    /**
     * @brief Set a value in the row.
     * @param headerName The header name of the value.
     * @param value The value to set.
     * @return True if the value was set, otherwise false.
     */
    bool set(const std::string &headerName, const std::string &value);

private:
    const std::vector<std::string> _header;
    std::vector<std::string> _values;

public:
    /**
     * @brief Get a value from the row.
     * @tparam T The type of the value.
     * @param pos The position of the value in the row.
     * @return The value.
     */
    template <typename T>
    const T getValue(unsigned int pos) const
    {
        if (pos < _values.size())
        {
            T res;
            std::stringstream ss;
            ss << _values[pos];
            ss >> res;
            return res;
        }
        throw Error("can't return this value (doesn't exist)");
    }

    /**
     * @brief Access a value in the row by index.
     * @param index The index of the value.
     * @return The value.
     */
    const std::string operator[](unsigned int index) const;

    /**
     * @brief Access a value in the row by header name.
     * @param valueName The header name of the value.
     * @return The value.
     */
    const std::string operator[](const std::string &valueName) const;

    /**
     * @brief Output the row to an ostream.
     * @param os The ostream.
     * @param row The row to output.
     * @return The ostream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Row &row);

    /**
     * @brief Output the row to an ofstream.
     * @param os The ofstream.
     * @param row The row to output.
     * @return The ofstream.
     */
    friend std::ofstream &operator<<(std::ofstream &os, const Row &row);
};

/**
 * @brief Enum representing the type of data source for the parser.
 */
enum DataType
{
    eFILE = 0,
    ePURE = 1
};

/**
 * @brief Class representing a CSV parser.
 */
class Parser
{
public:
    /**
     * @brief Construct a new Parser object.
     * @param file The path to the file or the raw data.
     * @param type The type of data source.
     * @param sep The separator character.
     */
    Parser(const std::string &file, const DataType &type = eFILE, char sep = ',');

    ~Parser(void);

public:
    /**
     * @brief Get a row by its index.
     * @param row The index of the row.
     * @return The row.
     */
    Row &getRow(unsigned int row) const;

    /**
     * @brief Get the number of rows.
     * @return The number of rows.
     */
    unsigned int rowCount(void) const;

    /**
     * @brief Get the number of columns.
     * @return The number of columns.
     */
    unsigned int columnCount(void) const;

    /**
     * @brief Get the header of the CSV file.
     * @return The header.
     */
    std::vector<std::string> getHeader(void) const;

    /**
     * @brief Get a header element by its position.
     * @param pos The position of the header element.
     * @return The header element.
     */
    const std::string getHeaderElement(unsigned int pos) const;

    /**
     * @brief Get the file name.
     * @return The file name.
     */
    const std::string &getFileName(void) const;

public:
    /**
     * @brief Delete a row by its index.
     * @param row The index of the row.
     * @return True if the row was deleted, otherwise false.
     */
    bool deleteRow(unsigned int row);

    /**
     * @brief Add a row at a specified position.
     * @param pos The position to add the row.
     * @param values The values of the new row.
     * @return True if the row was added, otherwise false.
     */
    bool addRow(unsigned int pos, const std::vector<std::string> &values);

    /**
     * @brief Sync the parser with the data source.
     */
    void sync(void) const;

protected:
    /**
     * @brief Parse the header of the CSV file.
     */
    void parseHeader(void);

    /**
     * @brief Parse the content of the CSV file.
     */
    void parseContent(void);

private:
    std::string _file;
    const DataType _type;
    const char _sep;
    std::vector<std::string> _originalFile;
    std::vector<std::string> _header;
    std::vector<Row *> _content;

public:
    /**
     * @brief Access a row by its index.
     * @param row The index of the row.
     * @return The row.
     */
    Row &operator[](unsigned int row) const;
};

#endif /*!_CSVPARSER_HPP_*/
