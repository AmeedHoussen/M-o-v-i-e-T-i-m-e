

#ifndef DATA_STRUCTURES_1_AVLTREE_H
#define DATA_STRUCTURES_1_AVLTREE_H

#include <iostream>
using std::exception;
using namespace std;
#define ZERO 0

template<class T,class S>
class Node {
public:
    T *key;
    S *data;
    int height;
    int BF;
    Node *right;
    Node *left;
    Node *father;

    Node() ;
    Node(const T& key ,const S& data ,Node* right = nullptr , Node* left = nullptr , Node* father= nullptr ) ;
    ~Node() ;

    bool operator ==(const Node<T,S>& other) ;
    bool operator>(const Node<T,S>& other) ;

    void updateHeight() ;
    int calculateHeightLeft() const ;
    int calculateHeightright() const ;
    void  updatebalancefactor() ;

    void rollLL();
    void rollRR();
    void rollRL();
    void rollLR();
    void check_which_roll_to_do() ;
    int gethight();
    int getBF();
};

template<class T, class S>
Node<T,S>::Node() : key(nullptr) , data(nullptr) ,height(ZERO) , BF(ZERO) , right(nullptr) ,
                    left(nullptr) , father(nullptr) {
}

template<class T , class S>
Node<T,S>::Node(const T& key ,const S& data ,Node* right , Node* left , Node* father) :
        key(new T(key)) , data(new S(data)) , height(ZERO) , BF(ZERO) , right(right) , left (left) , father(father) {
}

template<class T , class S>
Node<T,S>::~Node<T, S>() {
    delete key ;
    delete data ;
}

template<class T, class S>
bool Node<T, S>::operator==(const Node<T,S> &other) {
    if(this->key != other.key){
        return false;
    }
    return true;
}

template<class T, class S>
bool Node<T, S>::operator>(const Node<T,S> &other) {
    if(this->key > other.key){
        return true;
    }
    return false;
}

template<class T, class S>
void Node<T,S>::updateHeight(){
    if(this != nullptr ){
        if(calculateHeightLeft() > calculateHeightright()) {
            this->height = calculateHeightLeft() + 1;
        } else {
            this->height = calculateHeightright() + 1;
        }
    }
}

template<class T, class S>
int Node<T,S>::calculateHeightLeft() const{
    if(left != nullptr){
        return left->height ;
    }
    return -1 ;
}

template<class T, class S>
int Node<T,S>::calculateHeightright() const{
    if(right != nullptr){
        return right->height ;
    }
    return -1 ;
}

template<class T, class S>
void Node<T,S>::updatebalancefactor() {
    if(this != nullptr){
        this->BF = (calculateHeightLeft()+1)- (calculateHeightright()+1) ;
    }
}

template<class T, class S>
void Node<T,S>::rollLL() {
    Node<T,S>* oldFather = this->father; // NODE B
    Node<T,S>* oldLeftSon = this->left; // NODE A
    Node<T,S>* oldLeftRightSon = oldLeftSon->right; // NODE AR
    int IsFather = 0;
    if (oldFather != nullptr) {
        if(oldFather->left == this){
            IsFather = 1 ;
        } else{
            IsFather = 2 ;
            //do_somthing ;
        }
    }
    if (oldLeftRightSon != nullptr) {
        oldLeftRightSon->father = this;
    }
    if(oldLeftSon != nullptr){
        oldLeftSon->right = this ;
    }
    if(oldLeftSon != nullptr){
        oldLeftSon->father = oldFather ;
    }
    //UPDATES THE NODES !!
    if (oldLeftSon != nullptr) {
        oldLeftSon->right = this;
        oldLeftSon->father = oldFather;
    }
    this->father = oldLeftSon;
    this->left =oldLeftRightSon;
    if (IsFather == 1){
        if(oldLeftSon != nullptr){
            oldFather->left = oldLeftSon;
        }
    }
    if(oldLeftSon != nullptr){
        if (IsFather == 2){
            oldFather->right = oldLeftSon;
        }
    }
    this->updateHeight();
    this->updatebalancefactor();
}

template<class T, class S>
void Node<T,S>::rollRR() {
    Node<T,S>* oldFather = this->father ; // NODE B
    Node<T,S>* oldRightSon = this->right ; // NODE  A
    Node<T,S>* oldRightLeft = oldRightSon->left ; // NODE AL
    int IsFather = 0;
    if (oldFather != nullptr){
        if(oldFather->left == this){
            IsFather = 1 ;
        }else {
            IsFather = 2;
            //do_somthing ;
        }
    }
    if (oldRightLeft != nullptr) {
        oldRightLeft->father = this;
    }
    //UPDATES THE NODES !!
    if (oldRightSon != nullptr) {
        oldRightSon->left = this;
        oldRightSon->father = oldFather;
    }
    this->father = oldRightSon;
    this->right =oldRightLeft;
    if (IsFather == 1){
        if(oldRightSon != nullptr){
            oldFather->left = oldRightSon;
        }
    }
    if(oldRightSon != nullptr){
        if (IsFather == 2){
            oldFather->right = oldRightSon;
        }
    }
    this->updateHeight();
    this->updatebalancefactor();
}

template<class T, class S>
void Node<T,S>::rollRL() {
    right->rollLL() ;
    rollRR() ;
}

template<class T, class S>
void Node<T,S>::rollLR() {
    left->rollRR();
    rollLL() ;
}

template<class T, class S>
void Node<T,S>::check_which_roll_to_do() {
    if(this->BF == -2){
        if(this->right->BF <= 0){
            rollRR() ;
        } else{
            rollRL() ;
        }
        return;
    }
    if(this->BF == 2){
        if(this->left->BF >= 0){
            rollLL() ;
        } else{
            rollLR() ;
        }
    }
}
template<class T, class S>
int Node<T,S>::gethight(){
    if(this!= nullptr){
        return this->height;
    }
    return 0;
}
template<class T, class S>
int Node<T,S>::getBF(){
    if(this!= nullptr){
        return this->BF;
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------
template<class T, class S>
class AVLTree{
public:
    Node<T,S>* tree_root;
    int AVLTree_size;
    //friend class Node<T,S>;

    AVLTree();
    //AVLTree(const AVLTree<T,S>* other) ;
    ~AVLTree();
    //void copy(Node<T,S>* temp) ;
    void destroy(Node<T,S>* tree_nodes) ;
    void remove(T& keytodelete);
    void remove2(T& keytodelete) ;
    Node<T,S>* find2(const T &key) ;

    void remove_Node(Node<T,S>* todelete) ;

    void insert(const T& Addkey, const S& AddInfo) ;
    bool isNodeExists(const Node<T,S>* node)const ;
    Node<T,S>* where_to_add_the_node(const T& key) const ;
    void rotateTheTree(Node<T,S>* leaf) ;

    Node<T,S>* find(const T& key) ;
    Node<T,S>* lookforNode(Node<T,S>* root,const T &key) const ;
    /*void inorder(Node<T,S>* p ,int* const array ,int& i) ;
    void do_somthing(const Node<T,S>*p ,int* const array,int& i) ;*/
    void inorder(Node<T,S>* p ,T*&array) ;
    void inorder2(Node<T,S>* p ,int* const array ,int& i) ;
    void do_somthing2(const Node<T,S>*p ,int* const array,int& i) ;
    Node<T,S>* lookforNode2(Node<T,S>* root,const T &key) const ;
    S findMaxRightmostLeaf(const Node<T,S>* root) ;

    void getAllNode(Node<T,S>* p ,S*& dataArray) ;
    void pushInDataArray(Node<T,S>* p, S*& dataArray) ;

    void removeData(S& datatodelete);
    Node<T,S>* findData(const S &data) ;
    Node<T,S>* lookforNodeData(Node<T,S>* root,const S &data) const ;
   // class Node_Already_Exists_Exception : public exception {};
   // class Node_Not_Exists_Exception : public exception {};
};

template<class T, class S>
AVLTree<T,S>::AVLTree() :
        tree_root(nullptr) , AVLTree_size(ZERO){
}
/*
template<class T, class S>
AVLTree<T,S>::AVLTree(const AVLTree<T,S>* other): tree_root(new Node<T,S>()),AVLTree_size(ZERO){
    Node<T,S>* ptr = other->tree_root;
    ptr = ptr->left;
    this->copy(ptr);
}

template<class T, class S>
void AVLTree<T,S>::copy(Node<T,S>* temp){
    if (temp->left) {
        Copy(temp->left);
    }
    insert(*temp->key,*(temp->data));
    if (temp->right) {
        Copy(temp->right);
    }
}
*/
template<class T, class S>
AVLTree<T,S>::~AVLTree(){
    destroy(this->tree_root)  ;
}

template<class T, class S>
void AVLTree<T,S>::destroy(Node<T,S> *tree_nodes){
    if(!tree_nodes)
        return;
    destroy(tree_nodes->left);
    destroy(tree_nodes->right);
    delete tree_nodes ;
    this->AVLTree_size -- ;
}

template<class T, class S>
void AVLTree<T,S>::remove(T& keytodelete) {
    Node<T, S> *todelete = find(keytodelete);
    if (todelete == nullptr)
        return;
        //throw Node_Not_Exists_Exception();
    remove_Node(todelete) ;
}

template<class T, class S>
void AVLTree<T,S>::remove2(T& keytodelete) {
    Node<T, S> *todelete = find2(keytodelete);
    if (todelete == nullptr)
        return;
    //throw Node_Not_Exists_Exception();
    remove_Node(todelete) ;
}

template<class T, class S>
Node<T,S>* AVLTree<T,S>::find2(const T &key) {
    Node<T,S>* found = lookforNode2(this->tree_root , key );
    if(this->tree_root == nullptr ){
        return nullptr ;
    }
    if(*(found->key) == key) {
        return found ;
    }
    return nullptr ;
}

template<class T, class S>
Node<T,S>* AVLTree<T,S>::lookforNode2(Node<T,S>* root,const T &key) const {
    if(root == nullptr)
        return nullptr;
    /* if(*(root->key) == key)
         return root ;*/
    if(*(root->key) > key){
        if (root->right != nullptr) {
            return lookforNode(root->right,key) ;
        } else{
            return root;
        }
    }
    if(*(root->key) < key){
        if (root->left != nullptr) {
            return lookforNode(root->left, key);
        }else{
            return root;
        }
    }
    return root ;
}

template<class T, class S>
void AVLTree<T,S>::remove_Node(Node<T,S>* todelete){/*
    Node<T,S>* todelete= find(keytodelete);
    if(todelete == nullptr)
        throw Node_Not_Exists_Exception() ;*/
    if(todelete->left == nullptr && todelete->right == nullptr ){
        Node<T,S>* parent = todelete->father ;
        if(parent == nullptr){
            this->tree_root = nullptr ;
            delete todelete ;
            this->AVLTree_size--;
        } else {
            if (parent->right == todelete) {
                parent->right = nullptr;
            } else {
                parent->left = nullptr;
            }
            delete todelete;
            this->AVLTree_size--;
            rotateTheTree(parent);
        }
    } else {
        if (todelete->right == nullptr) {
            Node<T,S>* parent = todelete->father;
            if(parent == nullptr){
                this->tree_root = todelete->left ;
                todelete->left->father = nullptr ;
                delete todelete ;
                this->AVLTree_size--;
            }else {
                if (parent->right == todelete) {
                    parent->right = todelete->left;
                    todelete->left->father = parent;
                } else {
                    parent->left = todelete->left;
                    todelete->left->father = parent;
                }
                delete todelete;
                this->AVLTree_size--;
                rotateTheTree(parent);
            }
        } else {
            if (todelete->left == nullptr) {
                Node<T, S> *parent = todelete->father;
                if(parent == nullptr){
                    this->tree_root = todelete->right ;
                    todelete->right->father = nullptr ;
                    delete todelete ;
                    this->AVLTree_size--;
                } else {
                    if (parent->right == todelete) {
                        parent->right = todelete->right;
                        todelete->right->father = parent;
                    } else {
                        parent->left = todelete->right;
                        todelete->right->father = parent;
                    }
                    delete todelete;
                    this->AVLTree_size--;
                    rotateTheTree(parent);
                }
            } else {/*
                Node<T, S> *parent = todelete->father;
                if (parent == nullptr) {
                    Node<T, S> *son = todelete->right;
                   // Node<T, S> *lastleft = son->left;
                    while (son->left != nullptr) {
                        //lastleft = son;
                        son = son->left;
                    }
                    if (lastleft != nullptr) {
                        lastleft->left = nullptr;
                    }
                    son->father = nullptr;
                    son->father->left =nullptr ;
                    this->tree_root = son;
                    son->left = todelete->left;
                    todelete->left->father = son;
                    delete todelete;
                    this->AVLTree_size--;
                    rotateTheTree(son);
                } else {*/
                    Node<T, S> *son = todelete->right;
                    while (son->left != nullptr) {
                        son = son->left;
                    }
                    T *savekey = son->key;
                    S *saveinfo = son->data;
                    son->key = todelete->key;
                    son->data = todelete->data;
                    todelete->key = savekey;
                    todelete->data = saveinfo;
                    remove_Node(son);
                //}
            }
        }
    }
}

template<class T, class S>
void AVLTree<T,S>::insert(const T& Addkey, const S& AddInfo) {
    Node<T,S>* NewNode = new Node<T,S>(Addkey,AddInfo) ;
    if(NewNode== nullptr){
        return;
    }
    if(AVLTree_size == ZERO){
        this->tree_root = NewNode ;
        this->AVLTree_size ++ ;
        return;
    }
    if(isNodeExists(NewNode)){
        delete NewNode ;
        return;
        //throw Node_Already_Exists_Exception() ;
    }
    Node<T,S>* leaf=where_to_add_the_node(Addkey) ;
    if(*(leaf->key) > Addkey){
        leaf->left = NewNode ;
        NewNode->father = leaf ;
    } else {
        leaf->right = NewNode;
        NewNode->father = leaf;
    }
    this->AVLTree_size ++;
    rotateTheTree(NewNode);
}

template<class T, class S>
bool AVLTree<T,S>::isNodeExists(const Node<T,S>* node) const {
    if(!node)
        return false ;
    Node<T,S>* root = tree_root ;
    while (root) {
        if(*(root->key) == *(node->key))
            return true ;
        if (*(root->key) > *(node->key)) {
            root = root->left ;
        } else {
            root = root->right ;
        }
    }
    return false ;
}

template<class T, class S>
Node<T,S>* AVLTree<T,S>::where_to_add_the_node(const T &key) const {
    Node<T,S>* tree = tree_root ;
    while (tree) {
       /* if (tree->right == nullptr && tree->left == nullptr)
            return tree;*/
        if(*(tree->key) > key) {
            if (tree->left == nullptr) {
                return tree;
            }
            tree = tree->left ;
        } else {
            if (tree->right == nullptr) {
                return tree;
            }
            tree = tree->right ;
        }
    }
    return nullptr ;
}

template<class T, class S>
void AVLTree<T,S>::rotateTheTree(Node<T,S>* leaf){
    Node<T,S>* temp_node=leaf;
    while(temp_node != nullptr ){
        temp_node->updateHeight() ;
        temp_node->updatebalancefactor() ;
        temp_node->check_which_roll_to_do() ;
        if (temp_node->father == nullptr)
                this->tree_root = temp_node ;
        temp_node = temp_node->father;
    }
}

template<class T, class S>
Node<T,S>* AVLTree<T,S>::find(const T &key) {
    Node<T,S>* found = lookforNode(this->tree_root , key );
    if(this->tree_root == nullptr ){
        return nullptr ;
    }
    if(*(found->key) == key) {
        return found ;
    }
    return nullptr ;
}

template<class T, class S>
Node<T,S>* AVLTree<T,S>::lookforNode(Node<T,S>* root,const T &key) const {
    if(root == nullptr)
        return nullptr;
   /* if(*(root->key) == key)
        return root ;*/
    if(*(root->key) > key){
        if (root->left != nullptr) {
            return lookforNode(root->left,key) ;
        } else{
            return root;
        }
    }
    if(*(root->key) < key){
        if (root->right != nullptr) {
            return lookforNode(root->right, key);
        }else{
            return root;
        }
    }
    return root ;
}


/*
template<class T, class S>
void AVLTree<T,S>::inorder(Node<T,S>* p ,int* const array , int& i){
    if(p == NULL){
        return  ;
    }
    inorder(p->left , array , i) ;
    do_somthing(p,array,i) ;
    inorder(p->right , array , i) ;
}

template<class T, class S>
void AVLTree<T,S>::do_somthing(const Node<T, S> *p, int* const array, int& i) {
    array[i] = *(p->data) ;
    if(i+1 != AVLTree_size) {
        i++;
    }
}
*/

template<class T, class S>
void AVLTree<T,S>::inorder(Node<T,S>* p,T*& array) {
    if(p == nullptr){
        return;
    }
    inorder(p->left,array) ;
    *array = *(p->key) ;
    array++ ;
    inorder(p->right,array) ;
}

template<class T, class S>
void AVLTree<T,S>::inorder2(Node<T,S>* p ,int* const array , int& i){
    if(p == NULL){
        return  ;
    }
    inorder2(p->left , array , i) ;
    do_somthing2(p,array,i) ;
    inorder2(p->right , array , i) ;
}


template<class T, class S>
void AVLTree<T,S>::do_somthing2(const Node<T, S> *p, int* const array, int& i) {
    array[i] = *(p->key) ;
    i++ ;
}

template<class T, class S>
S AVLTree<T,S>::findMaxRightmostLeaf(const Node<T,S>* root) {
    if (root == nullptr)
        return -1;
    if (root->left != nullptr)
        return findMaxRightmostLeaf(root->left);
    return *(root->data);
}

template<class T, class S>
void AVLTree<T,S>::getAllNode(Node<T,S>* p ,S*& dataArray){
    if(p == NULL){
        return  ;
    }
    getAllNode(p->left , dataArray ) ;
    pushInDataArray(p,dataArray) ;
    getAllNode(p->right , dataArray) ;
}

template<class T, class S>
void AVLTree<T,S>::pushInDataArray(Node<T,S>* p ,S*& dataArray){
    *dataArray = *(p->data) ;
    dataArray ++ ;
}

template<class T, class S>
void AVLTree<T,S>::removeData(S &datatodelete)  {
    Node<T, S> *todelete = findData(datatodelete);
    if (todelete == nullptr)
        return;
    //throw Node_Not_Exists_Exception();
    remove_Node(todelete) ;
}

template<class T, class S>
Node<T,S>* AVLTree<T,S>::findData(const S &data) {
    Node<T,S>* found = lookforNodeData(this->tree_root , data );
    if(this->tree_root == nullptr ){
        return nullptr ;
    }
    if(*(found->data) == data) {
        return found ;
    }
    return nullptr ;
}

template<class T, class S>
Node<T,S>* AVLTree<T,S>::lookforNodeData(Node<T,S>* root,const S &data) const {
    if(root == nullptr)
        return nullptr;
    /* if(*(root->key) == key)
         return root ;*/
    if(*(root->data) > data){
        if (root->left != nullptr) {
            return lookforNodeData(root->left,data) ;
        } else{
            return root;
        }
    }
    if(*(root->data) < data){
        if (root->right != nullptr) {
            return lookforNodeData(root->right, data);
        }else{
            return root;
        }
    }
    return root ;
}

#endif //DATA_STRUCTURES_1_AVLTREE_H
