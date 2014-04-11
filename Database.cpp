#include "Database.h"
#include "HTTP.h"
#include "Tokenizer.h"
#include <iostream>
#include <fstream>
#include <unordered_set>


Database::Database(){}

Database::~Database(){}

bool Database::specifySchema(const std::vector<FieldDescriptor>& schema){
    
    m_schema.clear();
    m_rows.clear();
    m_fieldIndex.clear();
    
    bool flag=false;
    for (int i=0;i<schema.size();i++){
        std::string temp = schema[i].name.substr(schema[i].name.size()-1,schema[i].name.size());
        if (temp=="*"){
            flag=true;
            break;
        }
    }
    
    if (flag)
        return false;
    
    else{
        m_schema=schema;
    }
    
    for (int i=0;i<m_schema.size();i++){
        m_fieldIndex.push_back(new MultiMap());
    }
    
    return false;
}


bool Database::addRow(const std::vector<std::string>& rowOfData){
        if (m_schema.size()!=rowOfData.size())
            return false;
    
        m_rows.push_back(rowOfData);
    
        for (int i=0; i< m_schema.size(); i++){
            if (m_schema[i].index==it_indexed){
                m_fieldIndex[i]->insert(rowOfData[i],m_rows.size());
            }
        }
        return true;
}


int Database::getNumRows() const{
    return m_rows.size();
}


bool Database::getRow(int rowNum, std::vector<std::string>& row) const{
    if (rowNum<0||rowNum>=m_rows.size())
        return false;
    
    row = m_rows[rowNum];

    return true;
}


bool Database::loadFromURL(std::string url){
    std::string page;
    if (HTTP().get(url, page)){
    
        //get the first line of the input as a token
        std::string delimiters = "\n";
        Tokenizer t(page, delimiters);
        std::string firstLine;
        t.getNextToken(firstLine);
    
        //specify schema
        Tokenizer sch(firstLine,",");
        std::string fName;
        std::vector <FieldDescriptor> vecDes;
        while (sch.getNextToken(fName)){
            FieldDescriptor fdtemp;
            
            if (fName[fName.size()-1]=='*'){
                fName=fName.substr(0,fName.size()-1);
                fdtemp.name=fName;
                fdtemp.index=it_indexed;
                vecDes.push_back(fdtemp);
            }
            
            else {
                fdtemp.name=fName;
                fdtemp.index=it_none;
                vecDes.push_back(fdtemp);
            }
        }
        
        specifySchema(vecDes);
        
        std::string temp2;
        while (t.getNextToken(temp2)){
            std::vector<std::string> line;
            std::string lines;
            Tokenizer t2(temp2,",");
            while (t2.getNextToken(lines)){
                line.push_back(lines);
            }
            addRow(line);
        }
        return true;
    }
    
    else return false;
    
    return false;
}


bool Database::loadFromFile(std::string filename){
    std::string page;
    std::ifstream in(filename);
    
    if (!in)
        return false;
    
    std::string dataLine;
    while (in>>dataLine){
        page+=dataLine;
        page+='\n';
    }
    
    //get the first line of the input as a token
    std::string delimiters="'\n'";
    Tokenizer t(page, delimiters);
    std::string firstLine;
    t.getNextToken(firstLine);
    
    //specify schema
    Tokenizer sch(firstLine,",");
    std::string fName;
    std::vector <FieldDescriptor> vecDes;
    while (sch.getNextToken(fName)){
        FieldDescriptor fdtemp;

        if (fName[fName.size()-1]=='*'){
            fName=fName.substr(0,fName.size()-1);
            fdtemp.name=fName;
            fdtemp.index=it_indexed;
            vecDes.push_back(fdtemp);
        }
        
        else {
            fdtemp.name=fName;
            fdtemp.index=it_none;
            vecDes.push_back(fdtemp);
        }
    }
    
    specifySchema(vecDes);
    
    
    std::string temp2;
    while (t.getNextToken(temp2)){
        std::vector<std::string> line;
        std::string lines;
        Tokenizer t2(temp2,",");
        while (t2.getNextToken(lines)){
            line.push_back(lines);
        }
        addRow(line);
    }
    
    return true;
}


int Database::search(const std::vector<SearchCriterion>& searchCriteria,const std::vector<SortCriterion>& sortCriteria, std::vector<int>& results)
{
  return 0;
}
