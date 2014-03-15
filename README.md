CS32-Project4-MultiMap-Database
===============================
MutiMap - 1) implemented using a binary search tree & 2) key/value pair = string/int



public functions:

 void clear()
 
 void insert(std::string key, unsigned int value)
 
 Iterator findEqual(std::string key) const
 
 Iterator findEqualOrSuccessor(std::string key) const
 
 Iterator findEqualOrPredecessor(std::string key) const
 

===============================
MultiMap::Iterator



public functions:

 bool valid() const
 
 std::string getKey() const
 
 unsigned int getValue() const
 
 bool next()
 
 bool prev()

===============================
Database



public functions:

 bool specifySchema(const std::vector<FieldDescriptor>& schema)
 
 bool addRow(const std::vector<std::string>& rowOfData)
 
 bool loadFromURL(std::string url)
 
 bool loadFromFile(std::string filename)
 
 int getNumRows() const
 
 bool getRow(int rowNum, std::vector<std::string>& row) const
 
 int search(const std::vector<SearchCriterion>& searchCriteria,
const std::vector<SortCriterion>& sortCriteria, std::vector<int>& results)

===============================
Note: Tokenizer.h and HTTP.h are provided by the professor
