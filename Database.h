#ifndef __Project_4__Database__
#define __Project_4__Database__

#include <iostream>
#include <vector>
#include "MultiMap.h"


class Database {
public:
   enum IndexType { it_none, it_indexed };

   struct FieldDescriptor {
        std::string name;
        IndexType index;
    };
    
    static const int ERROR_RESULT = -1;
    
public:
    Database();
    ~Database();
    bool specifySchema(const std::vector<FieldDescriptor>& schema);
    bool addRow(const std::vector<std::string>& rowOfData);
    bool loadFromURL(std::string url);
    bool loadFromFile(std::string filename);
    int getNumRows() const;
    bool getRow(int rowNum, std::vector<std::string>& row) const;

    
private:
    Database(const Database& other);
    Database& operator=(const Database& rhs);
    std::vector<FieldDescriptor> m_schema;
    std::vector<std::vector<std::string>> m_rows;
    std::vector<MultiMap*> m_fieldIndex;
};



#endif /* defined(__Project_4__Database__) */
