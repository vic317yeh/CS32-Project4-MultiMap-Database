#ifndef __Project_4__MultiMap__
#define __Project_4__MultiMap__

#include <iostream>
#include <string>

using namespace std;

class MultiMap {
public:

//valueNode
struct valueNode{
public:
    valueNode(int num,valueNode* nextNode=NULL, valueNode* prevNode=NULL):m_value(num),m_next(nextNode),m_prev(prevNode){}
    int getValue() const;
    valueNode* getNext() const;
    valueNode* getPrev() const;
    void setNext(valueNode* newNode);
    
private:
    int m_value;
    valueNode* m_next;
    valueNode* m_prev;
};
    
    
//keyNode
struct keyNode{
public:
    keyNode(string newKey, keyNode* ptr=NULL, valueNode* vptr=NULL):m_key(newKey), m_parent(ptr), valueRoot(vptr){}
    void setParent(keyNode* newNode);
    void setLeft(keyNode* newNode);
    void setRight(keyNode* newNode);
    void insertValueNode(int value);
    valueNode* getValueRoot() const;
    string getKey() const;
    keyNode* getParent() const;
    keyNode* getLeft() const;
    keyNode* getRight() const;

private:
    string m_key;
    valueNode* valueRoot;
    keyNode* m_parent;
    keyNode* m_left;
    keyNode* m_right;
};
   
    
//Iterator
class Iterator{
    public:
        Iterator();
        Iterator(MultiMap* map);
        Iterator(keyNode* kNode);
        bool valid() const;
        std::string getKey() const;
        unsigned int getValue() const;
        bool next();
        bool prev();
        
    private:
        keyNode* m_node;
        valueNode* m_vaNode;
};
    
    
    //MultiMap public member functions
    MultiMap();
    ~MultiMap();
    void clear();
    void insert(std::string key, unsigned int value);
    Iterator findEqual(std::string key) const;
    Iterator findEqualOrSuccessor(std::string key) const;
    Iterator findEqualOrPredecessor(std::string key) const;
    
private:
    MultiMap(const MultiMap& other);
    MultiMap& operator=(const MultiMap& rhs);
    void deleteSubTree(keyNode*);
    keyNode* searchEq(keyNode* node, string key) const;
    keyNode* searchEqOrSu(keyNode* node, keyNode* topNode,string key) const;
    keyNode* searchEqOrPr(keyNode* node, keyNode* topNode,string key) const;
    keyNode* m_root;
};
