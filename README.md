CS32-Project4-MultiMap-Database
===============================
MutiMap functions:

void clear()

void insert(std::string key, unsigned int value)

Iterator findEqual(std::string key) const

Iterator findEqualOrSuccessor(std::string key) const

Iterator findEqualOrPredecessor(std::string key) const

===============================
MultiMap::Iterator functions:

bool valid() const

std::string getKey() const

unsigned int getValue() const

bool next()

bool prev()

===============================
