#include <fstream>
#include <sstream>
#include <iomanip>
#include "CSVparser.hpp"

/**
 * @brief Converts a string to a double, removing a specified character.
 *
 * @param str The string to convert.
 * @param ch The character to remove.
 * @return double The converted double.
 */
double strToDouble(std::string str, char ch)
{
  str.erase(remove(str.begin(), str.end(), ch), str.end());
  return atof(str.c_str());
}

/**
 * @brief Load bids from a CSV file into a linked list.
 *
 * @param csvPath The path to the CSV file.
 */
void loadBidsIntoLinkedList(const std::string &csvPath)
{
  std::cout << "Loading CSV file " << csvPath << " into linked list." << std::endl;

  // Create a Parser object for the CSV file
  Parser file = Parser(csvPath);
  LinkedList list;

  try
  {
    // Iterate through each row in the CSV file
    for (int i = 0; i < file.rowCount(); i++)
    {
      // Create a LinkedListBid object to store bid data
      LinkedListBid bid;
      // Assign values from CSV to bid attributes
      bid.bidId = file[i][1];
      bid.title = file[i][0];
      bid.fund = file[i][8];
      bid.amount = strToDouble(file[i][4], '$');

      // Append bid to linked list
      list.append(bid);
    }

    std::cout << "Loading bids into the linked list..." << std::endl;

    // Print the number of bids loaded into the linked list
    std::cout << "Number of bids loaded into the linked list: " << list.size() << std::endl;

    // Find a bid in the linked list by ID
    std::string bidIdToFind = "97990";
    LinkedListBid foundBid;
    if (list.find(bidIdToFind, foundBid))
    {
      std::cout << "Bid with ID " << bidIdToFind << " found in the linked list." << std::endl;
    }
    else
    {
      std::cout << "Bid with ID " << bidIdToFind << " not found in the linked list." << std::endl;
    }
  }
  catch (Error &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

/**
 * @brief Load bids from a CSV file into a hashmap.
 *
 * @param csvPath The path to the CSV file.
 */
void loadBidsIntoHashmap(const std::string &csvPath)
{
  std::cout << "Loading CSV file " << csvPath << " into hashmap." << std::endl;

  // Create a Parser object for the CSV file
  Parser file = Parser(csvPath);
  Hashmap hashmap = Hashmap();

  try
  {
    // Iterate through each row in the CSV file
    for (int i = 0; i < file.rowCount(); i++)
    {
      // Create a HashmapBid object to store bid data
      HashmapBid bid;
      // Assign values from CSV to bid attributes
      bid.bidId = file[i][1];
      bid.title = file[i][0];
      bid.fund = file[i][8];
      bid.amount = strToDouble(file[i][4], '$');
      // Insert bid into hashmap
      hashmap.insert(bid);
    }
  }
  catch (Error &e)
  {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "Loading bids into the hashmap..." << std::endl;

  // Print the number of bids loaded into the hashmap
  std::cout << "Number of bids loaded into the hashmap: " << hashmap.size() << std::endl;

  // Retrieve a bid from the hashmap by ID
  HashmapBid retrievedBid;
  std::string bidIdToRetrieve = "97990";
  if (hashmap.get(bidIdToRetrieve, retrievedBid))
  {
    std::cout << "Bid with ID " << bidIdToRetrieve << " found in the hashmap." << std::endl;
  }
  else
  {
    std::cout << "Bid with ID " << bidIdToRetrieve << " not found in the hashmap." << std::endl;
  }

  // Remove a bid from the hashmap by ID
  std::string bidIdToRemove = "97990";
  if (hashmap.remove(bidIdToRemove))
  {
    std::cout << "Bid with ID " << bidIdToRemove << " removed from the hashmap." << std::endl;
  }
  else
  {
    std::cout << "Bid with ID " << bidIdToRemove << " not found in the hashmap." << std::endl;
  }
}

/**
 * @brief Constructor for Parser class.
 *
 * @param data The data source (file path or pure content).
 * @param type The type of data source (file or pure).
 * @param sep The separator used in the CSV file.
 */
Parser::Parser(const std::string &data, const DataType &type, char sep)
    : _type(type), _sep(sep)
{
  std::string line;
  if (type == eFILE)
  {
    // Read data from file
    _file = data;
    std::ifstream ifile(_file.c_str());
    if (ifile.is_open())
    {
      // Read lines from file
      while (ifile.good())
      {
        getline(ifile, line);
        if (line != "")
          _originalFile.push_back(line);
      }
      ifile.close();

      if (_originalFile.size() == 0)
        throw Error(std::string("No Data in ").append(_file));

      // Parse header and content
      parseHeader();
      parseContent();
    }
    else
      throw Error(std::string("Failed to open ").append(_file));
  }
  else
  {
    // Read data from pure content
    std::istringstream stream(data);
    while (std::getline(stream, line))
      if (line != "")
        _originalFile.push_back(line);
    if (_originalFile.size() == 0)
      throw Error(std::string("No Data in pure content"));

    // Parse header and content
    parseHeader();
    parseContent();
  }
}

/**
 * @brief Destructor for Parser class.
 */
Parser::~Parser(void)
{
  // Cleanup allocated memory for rows
  std::vector<Row *>::iterator it;
  for (it = _content.begin(); it != _content.end(); it++)
    delete *it;
}

/**
 * @brief Parses the header of the CSV file.
 */
void Parser::parseHeader(void)
{
  std::stringstream ss(_originalFile[0]);
  std::string item;

  // Extract header elements
  while (std::getline(ss, item, _sep))
    _header.push_back(item);
}

/**
 * @brief Parses the content of the CSV file.
 */
void Parser::parseContent(void)
{
  std::vector<std::string>::iterator it;

  it = _originalFile.begin();
  it++; // skip header

  // Iterate through content lines
  for (; it != _originalFile.end(); it++)
  {
    bool quoted = false;
    int tokenStart = 0;
    unsigned int i = 0;

    Row *row = new Row(_header);

    // Parse each line into row values
    for (; i != it->length(); i++)
    {
      if (it->at(i) == '"')
        quoted = ((quoted) ? (false) : (true));
      else if (it->at(i) == ',' && !quoted)
      {
        row->push(it->substr(tokenStart, i - tokenStart));
        tokenStart = i + 1;
      }
    }

    // Add remaining value
    row->push(it->substr(tokenStart, it->length() - tokenStart));

    // Check for missing values
    if (row->size() != _header.size())
      throw Error("corrupted data !");
    _content.push_back(row);
  }
}

/**
 * @brief Get a row from the parser by its position.
 *
 * @param rowPosition The position of the row.
 * @return Row& Reference to the row object.
 */
Row &Parser::getRow(unsigned int rowPosition) const
{
  if (rowPosition < _content.size())
    return *(_content[rowPosition]);
  throw Error("can't return this row (doesn't exist)");
}

/**
 * @brief Overloaded [] operator to get a row by its position.
 *
 * @param rowPosition The position of the row.
 * @return Row& Reference to the row object.
 */
Row &Parser::operator[](unsigned int rowPosition) const
{
  return Parser::getRow(rowPosition);
}

/**
 * @brief Get the number of rows in the parser.
 *
 * @return unsigned int The number of rows.
 */
unsigned int Parser::rowCount(void) const
{
  return _content.size();
}

/**
 * @brief Get the number of columns in the parser.
 *
 * @return unsigned int The number of columns.
 */
unsigned int Parser::columnCount(void) const
{
  return _header.size();
}

/**
 * @brief Get the header of the CSV file.
 *
 * @return std::vector<std::string> The header elements.
 */
std::vector<std::string> Parser::getHeader(void) const
{
  return _header;
}

/**
 * @brief Get a specific element from the header by its position.
 *
 * @param pos The position of the element.
 * @return const std::string The header element.
 */
const std::string Parser::getHeaderElement(unsigned int pos) const
{
  if (pos >= _header.size())
    throw Error("can't return this header (doesn't exist)");
  return _header[pos];
}

/**
 * @brief Delete a row from the parser by its position.
 *
 * @param pos The position of the row to delete.
 * @return true If the row was successfully deleted.
 * @return false If the row position is invalid.
 */
bool Parser::deleteRow(unsigned int pos)
{
  if (pos < _content.size())
  {
    delete *(_content.begin() + pos);
    _content.erase(_content.begin() + pos);
    return true;
  }
  return false;
}

/**
 * @brief Add a row to the parser at a specific position.
 *
 * @param pos The position to insert the row.
 * @param r The vector containing the row values.
 * @return true If the row was successfully added.
 * @return false If the specified position is invalid.
 */
bool Parser::addRow(unsigned int pos, const std::vector<std::string> &r)
{
  Row *row = new Row(_header);

  // Push values into the row
  for (auto it = r.begin(); it != r.end(); it++)
    row->push(*it);

  // Insert row into content
  if (pos <= _content.size())
  {
    _content.insert(_content.begin() + pos, row);
    return true;
  }
  return false;
}

/**
 * @brief Write changes back to the original file (if it was a file-based parser).
 */
void Parser::sync(void) const
{
  if (_type == DataType::eFILE)
  {
    std::ofstream f;
    f.open(_file, std::ios::out | std::ios::trunc);

    // Write header
    unsigned int i = 0;
    for (auto it = _header.begin(); it != _header.end(); it++)
    {
      f << *it;
      if (i < _header.size() - 1)
        f << ",";
      else
        f << std::endl;
      i++;
    }

    // Write content
    for (auto it = _content.begin(); it != _content.end(); it++)
      f << **it << std::endl;
    f.close();
  }
}

/**
 * @brief Get the file name of the parser.
 *
 * @return const std::string& The file name.
 */
const std::string &Parser::getFileName(void) const
{
  return _file;
}

/*
** ROW
*/

/**
 * @brief Constructor for Row class.
 *
 * @param header The header of the CSV file.
 */
Row::Row(const std::vector<std::string> &header)
    : _header(header) {}

/**
 * @brief Destructor for Row class.
 */
Row::~Row(void) {}

/**
 * @brief Get the number of values in the row.
 *
 * @return unsigned int The number of values.
 */
unsigned int Row::size(void) const
{
  return _values.size();
}

/**
 * @brief Add a value to the row.
 *
 * @param value The value to add.
 */
void Row::push(const std::string &value)
{
  _values.push_back(value);
}

/**
 * @brief Set a value in the row by its key (header element).
 *
 * @param key The key (header element) of the value.
 * @param value The new value to set.
 * @return true If the value was successfully set.
 * @return false If the specified key does not exist in the row.
 */
bool Row::set(const std::string &key, const std::string &value)
{
  std::vector<std::string>::const_iterator it;
  int pos = 0;

  // Find the position of the key in the header
  for (it = _header.begin(); it != _header.end(); it++)
  {
    if (key == *it)
    {
      _values[pos] = value;
      return true;
    }
    pos++;
  }
  return false;
}

/**
 * @brief Overloaded [] operator to get a value from the row by its position.
 *
 * @param valuePosition The position of the value.
 * @return const std::string The value at the specified position.
 */
const std::string Row::operator[](unsigned int valuePosition) const
{
  if (valuePosition < _values.size())
    return _values[valuePosition];
  throw Error("can't return this value (doesn't exist)");
}

/**
 * @brief Overloaded [] operator to get a value from the row by its key (header element).
 *
 * @param key The key (header element) of the value.
 * @return const std::string The value corresponding to the key.
 */
const std::string Row::operator[](const std::string &key) const
{
  std::vector<std::string>::const_iterator it;
  int pos = 0;

  // Find the position of the key in the header
  for (it = _header.begin(); it != _header.end(); it++)
  {
    if (key == *it)
      return _values[pos];
    pos++;
  }

  throw Error("can't return this value (doesn't exist)");
}

/**
 * @brief Overloaded << operator to output the row values.
 *
 * @param os The output stream.
 * @param row The row object to output.
 * @return std::ostream& Reference to the output stream.
 */
std::ostream &operator<<(std::ostream &os, const Row &row)
{
  for (unsigned int i = 0; i != row._values.size(); i++)
    os << row._values[i] << " | ";

  return os;
}

/**
 * @brief Overloaded << operator to output the row values to a file.
 *
 * @param os The output file stream.
 * @param row The row object to output.
 * @return std::ofstream& Reference to the output file stream.
 */
std::ofstream &operator<<(std::ofstream &os, const Row &row)
{
  for (unsigned int i = 0; i != row._values.size(); i++)
  {
    os << row._values[i];
    if (i < row._values.size() - 1)
      os << ",";
  }
  return os;
}
