#include "MultiMap.h"

//////////////////////////////////////MultiMap class

//constructor
MultiMap::MultiMap(){
    m_root=NULL;
}


//destructor
MultiMap::~MultiMap(){
    clear();
}


//public functions
void MultiMap::deleteSubTree(keyNode* ptr){
    if (ptr==NULL)
        return;
    
    deleteSubTree(ptr->getLeft());
    deleteSubTree(ptr->getRight());
    
    valueNode* vNode=ptr->getValueRoot();
    while (vNode!=NULL){
        valueNode* temp=vNode->getNext();
        delete vNode;
        vNode=temp;
    }
    delete ptr;
}


void MultiMap::clear(){
    if (m_root!=NULL)
        deleteSubTree(m_root);
}


//recursive sub-function for findEqual()
MultiMap::keyNode* MultiMap::searchEq(keyNode* node, std::string key) const{
    if (node->getKey()==key)
        return node;
    
    //if key is less than the root
    if (node->getKey()>key){
        if (node->getLeft()!=NULL){
            if (node->getLeft()->getKey()<key){
                return NULL;
            }
            else {
                return searchEq(node->getLeft(), key);
            }
        }
        else return NULL;
    }
    
    //if key is greater than the root
    else {
        if (node->getRight()!=NULL){
            if (node->getRight()->getKey()<key){
                return NULL;
            }
            else {
                return searchEq(node->getRight(), key);
            }
        }
        else return NULL;
    }
    
    return NULL;
}

MultiMap::Iterator MultiMap::findEqual(std::string key) const{
    Iterator it(searchEq(m_root,key));
    
    return it;
}


//recursive sub-function for findEqualOrSuccessor()
MultiMap::keyNode* MultiMap::searchEqOrSu(keyNode* node,keyNode* topNode, string key) const{
    if (node->getKey()==key)
        return node;
    
    //if key is less than the root
    if (node->getKey()>key){
        if (node->getLeft()!=NULL){
            
            return searchEqOrSu(node->getLeft(), node, key);
        }
        else return node;
    }
    
    //if key is greater than the root
    else {
        if (node->getRight()!=NULL&&node->getRight()->getKey()>=topNode->getKey()){
            return searchEqOrSu(node->getRight(),node->getRight(),key);
        }
        
        else if (node->getRight()!=NULL&&node->getRight()->getKey()<topNode->getKey()){
            return searchEqOrSu(node->getRight(),topNode,key);
        }
        
        else {
            if (node->getKey()<node->getParent()->getKey()){
                return node->getParent();
            }
            else if (key < topNode->getKey()){
                return topNode;
            }
            else return NULL;
        }
    }
    return NULL;
}


MultiMap::Iterator MultiMap::findEqualOrSuccessor(std::string key) const{
    Iterator it(searchEqOrSu(m_root, m_root,key));
    
    return it;
}


//recursive sub-function for findEqualOrPredecessor()
MultiMap::keyNode* MultiMap::searchEqOrPr(keyNode* node, keyNode* topNode,string key) const{
    if (node->getKey()==key)
        return node;
    
    //if key is greater than the root
    if (node->getKey()<key||node->getKey()==key){
        if (node->getRight()!=NULL){
            return searchEqOrPr(node->getRight(), node, key);
        }
        else return node;
    }
    
    
    //if key is less than the root
    else {
        if (node->getLeft()!=NULL&&node->getLeft()->getKey()<=topNode->getKey()){
            return searchEqOrPr(node->getLeft(),node->getLeft(),key);
        }
        
        else if (node->getLeft()!=NULL&&node->getLeft()->getKey()>topNode->getKey()){
            return searchEqOrPr(node->getLeft(),topNode,key);
        }
        
        else {
            if (node->getKey()>node->getParent()->getKey()){
                return node->getParent();
            }
            else if (key>topNode->getKey()){
                return topNode;
            }
            else return NULL;
        }
    }
    
    return NULL;
}


MultiMap::Iterator MultiMap::findEqualOrPredecessor(std::string key) const{
    Iterator it(searchEqOrPr(m_root, m_root,key));
    
    return it;
}


//insert a new node into the BST
void MultiMap::insert(std::string key, unsigned int value){
    keyNode* ptr=m_root;
    
    //check root node
    if (ptr==NULL){
        m_root=new keyNode(key,NULL,new valueNode(value));
    }
    
    while (ptr!=NULL){
        if (key==ptr->getKey()){
            ptr->insertValueNode(value);
            break;
        }
        
        if (key<ptr->getKey()){
            if (ptr->getLeft()==NULL){
                ptr->setLeft(new keyNode(key,ptr,new valueNode(value)));
                break;
            }
        
            else
                ptr=ptr->getLeft();
        }
        else {
            if (ptr->getRight()==NULL){
                ptr->setRight(new keyNode(key,ptr,new valueNode(value)));
                break;
            }
        
            else
                ptr=ptr->getRight();
        }
    }
}


/////////////////////////////////////MultiMap::Iterator class

//constructor
MultiMap::Iterator::Iterator(){}

MultiMap::Iterator::Iterator(MultiMap* map) {
    m_node=map->m_root;
    m_vaNode=m_node->getValueRoot();
}

MultiMap::Iterator::Iterator(keyNode* kNode){
    m_node = kNode;
    m_vaNode=kNode->getValueRoot();
}


//public functions
bool MultiMap::Iterator::valid() const{
    return m_node!=NULL;
}

std::string MultiMap::Iterator::getKey() const{
    return m_node->getKey();
}


unsigned int MultiMap::Iterator::getValue() const{
    return m_vaNode->getValue();
}


bool MultiMap::Iterator::next(){
    //check the initial condition
    if (!valid())
        return false;

    //get the next value node if it exists
    if (m_vaNode->getNext()!=NULL){
            m_vaNode=m_vaNode->getNext();
            return true;
    }
    
    //get to the least node in the right subtree if there is a right node
    if (m_node->getRight()!=NULL){
        //find the most smallest node
        keyNode* ptr=m_node->getRight();
        
        while (ptr->getLeft()!=NULL){
            ptr=ptr->getLeft();
        }
        
        m_node=ptr;
        m_vaNode=m_node->getValueRoot();
        return true;
    }
    
    else {
        //condition: if the node is less than the node that ptr points to
        if (m_node->getKey()<m_node->getParent()->getKey()){
            m_node=m_node->getParent();
            m_vaNode=m_node->getValueRoot();
            return true;
        }
        
        keyNode* ptr=m_node;
        
        while (ptr->getParent()!=NULL&&m_node->getKey()>ptr->getParent()->getKey())
            ptr=ptr->getParent();
        
        //check if the parent of ptr is root
        if (ptr->getParent()!=NULL){
            ptr=ptr->getParent();
        }
        
        //condition: if the node is less than the node that ptr points to
        if (m_node->getKey()<ptr->getKey()){
            m_node=ptr;
            m_vaNode=m_node->getValueRoot();
            return true;
        }
        else return false;
    }
    
    return false;
}


bool MultiMap::Iterator::prev(){
    //check the initial condition
    if (!valid())
        return false;

    //get the next value node if it exists
    if (m_vaNode->getNext()!=NULL){
        m_vaNode=m_vaNode->getNext();
        return true;
    }

    //get to the greatest node in the left subtree if there is a left node
    if (m_node->getLeft()!=NULL){
        //find the most greatest node
        keyNode* ptr=m_node->getLeft();
    
        while (ptr->getRight()!=NULL){
            ptr=ptr->getRight();
        }
    
    m_node=ptr;
    m_vaNode=m_node->getValueRoot();
    return true;
  }

    else {
    //condition: if the node is greater than the node that ptr points to
    if (m_node->getKey()>m_node->getParent()->getKey()){
        m_node=m_node->getParent();
        m_vaNode=m_node->getValueRoot();
        return true;
    }
    
    keyNode* ptr=m_node;
    
    while (ptr->getParent()!=NULL&&m_node->getKey()<ptr->getParent()->getKey())
        ptr=ptr->getParent();
        
        //check if the parent of ptr is root
        if (ptr->getParent()!=NULL){
            ptr=ptr->getParent();
        }
    
    //condition: if the node is greater than the node that ptr points to
    if (m_node->getKey()>ptr->getKey()){
        m_node=ptr;
        m_vaNode=m_node->getValueRoot();
        return true;
    }
    
    else return false;
    }

    return false;
}



/////////////////////////////////////MultiMap::valueNode class
int MultiMap::valueNode::getValue() const{
    return m_value;
}

MultiMap::valueNode* MultiMap::valueNode::getNext() const{
    return m_next;
}


MultiMap::valueNode* MultiMap::valueNode::getPrev() const{
    return m_prev;
}

void MultiMap::valueNode::setNext(valueNode* newNode){
    m_next=newNode;
    m_next->m_prev=this;
}



/////////////////////////////////////MultiMap::keyNode class
MultiMap::valueNode* MultiMap::keyNode::getValueRoot() const{
    return valueRoot;
}


void MultiMap::keyNode::insertValueNode(int value){
    if (valueRoot==NULL){
        valueRoot=new valueNode(value);
    }
    
    valueNode* ptr=valueRoot;
    
    while (ptr!=NULL){
        valueNode* temp=ptr;
        ptr=ptr->getNext();
        if (ptr==NULL){
            ptr=new valueNode(value);
            temp->setNext(ptr);
            break;
        }
    }
}


void MultiMap::keyNode::setParent(keyNode* newNode){
    m_parent=newNode;
}

void MultiMap::keyNode::setLeft(keyNode* newNode){
    m_left=newNode;
}

void MultiMap::keyNode::setRight(keyNode* newNode){
    m_right=newNode;
}

string MultiMap::keyNode::getKey() const{
    return m_key;
}

MultiMap::keyNode* MultiMap::keyNode::getParent() const{
    return m_parent;
}

MultiMap::keyNode* MultiMap::keyNode::getLeft() const{
    return m_left;
}

MultiMap::keyNode* MultiMap::keyNode::getRight() const{
    return m_right;
}
