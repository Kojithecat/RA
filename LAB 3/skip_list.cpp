#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

class Set {
public:
    Set( double q );
    ~Set();

    // non-modifying member functions

    /*
    It prints the key, value, level
    of each node of the skip list.

    Prints two nodes per line.
    */
    void print() const;

    /*
    It searches the skip list and
    returns the element corresponding
    to the searchKey; otherwise it returns
    failure, in the form of null pointer.
    */
    std::string* find(int searchKey) const;

    // modifying member functions

    /*
    It searches the skip list for elements
    with seachKey, if there is an element
    with that key its value is reassigned to the
    newValue, otherwise it creates and splices
    a new node, of random level.
    */
    void insert(int searchKey, const std::string& newValue);

    /*
    It deletes the element containing
    searchKey, if it exists.
    */
    void erase(int searchKey);

    // returns true iff x is in the set
    bool contains ( int searchKey) const ;

    int total_search_cost() const ;
    int number_pointers() ;


private:

    struct Node {
        int key;
        std::string value;

        // pointers to successor nodes
        std::vector<Node*> forward;

        Node(int k, const std::string& v, int level):
            key(k), value(v),forward(level,nullptr)
        {}
    };

    // Generates node levels in the range [1, maxLevel).
    int randomLevel() const;

    //Returns number of incoming and outgoing pointers
    static int nodeLevel(const Node* v);

    //creates a node on the heap and returns a pointer to it.
    static Node* makeNode(int key, std::string val, int level);

    // Returns the first node for which node->key < searchKey is false
    Node* lower_bound(int searchKey) const ;

    /*
    * Returns a collection of Pointers to Nodes
    * result[i] hold the last node of level i+1 for which result[i]->key < searchKey is true
    */
    std::vector<Node*> predecessors(int searchKey) const ;

    // data members
    const float probability;
    const int maxLevel;
    Node* head; // pointer to first node
    Node* NIL;  // last node
};


//==============================================================================
// Class Set member implementations

Set::Set(double q) :
    probability(q),
    maxLevel(128/(1-q))
{
    int headKey = std::numeric_limits<int>::min();
    head = new Node(headKey, "head", maxLevel);

    int nilKey = std::numeric_limits<int>::max();
    NIL = new Node(nilKey, "NIL", maxLevel);

    std::fill(head->forward.begin(), head->forward.end(), NIL);
}

Set::~Set() {
    auto node = head;
    while (node->forward[0]) {
        auto tmp = node;
        node = node->forward[0];
        delete tmp;
    }
    delete node;
}

std::string* Set::find(int searchKey) const {
    std::string* res{};
    if (auto x = lower_bound(searchKey)) {
        if (x->key == searchKey && x!=NIL) {
            res = &(x->value);
        }
    }
    return res;
}

bool Set::contains(int searchKey) const {
    if (auto x = lower_bound(searchKey)) {
        if (x->key == searchKey && x!=NIL) {
            return true;
        }
    }
    return false;
}

void Set::print() const {
    Node* list = head->forward[0];
    int lineLenght = 0;

    std::cout << "{";

    while (list != NIL) {
        std::cout << "value: " << list->value
            << ", key: " << list->key
            << ", level: " << nodeLevel(list);

        list = list->forward[0];

        if (list != NIL) std::cout << " : ";

        if (++lineLenght % 2 == 0) std::cout << "\n";
    }
    std::cout << "}\n";
}

void Set::insert(int searchKey, const std::string& newValue) {
    auto preds = predecessors(searchKey);

    {//reassign value if node exists and return
        auto next = preds[0]->forward[0];
        if (next->key == searchKey && next != NIL) {
            next->value = newValue;
            return;
        }
    }

    // create new node
    const int newNodeLevel = randomLevel();
    auto newNodePtr = makeNode(searchKey, newValue, newNodeLevel);

    // connect pointers of predecessors and new node to respective successors
    for (int i = 0; i < newNodeLevel; ++i) {
        newNodePtr->forward[i] = preds[i]->forward[i];
        preds[i]->forward[i] = newNodePtr;
    }
}


void Set::erase(int searchKey) {
    auto preds = predecessors(searchKey);

    //check if the node exists
    auto node = preds[0]->forward[0];
    if (node->key != searchKey || node == NIL) {
     }

    // update pointers and delete node
       return;
    for (size_t i = 0; i < nodeLevel(node); ++i) {
        preds[i]->forward[i] = node->forward[i];
    }
    delete node;
}

int Set::total_search_cost() const{
    return 1; // no time to implement

}

int Set::number_pointers(){
    Node* x;
    int num_ptrs = 0;

    for (unsigned int i = 0; i < nodeLevel(head); i++) {
        x = head;
        while ( x->forward[i]->key < std::numeric_limits<int>::max()) {
            x = x->forward[i];
            //std::cout << num_ptrs << std::endl;
            num_ptrs += 1;
        }
    }

    return num_ptrs;
}

//###### private member functions ######
int Set::nodeLevel(const Node* v) {
    return v->forward.size();
}

Set::Node* Set::makeNode(int key, std::string val, int level)  {
    return new Node(key, val, level);
}

int Set::randomLevel() const {
    int v = 1;
    while (((double)std::rand() / RAND_MAX) < probability &&
        v < maxLevel) {
        v++;
    }
    return v;
}

Set::Node* Set::lower_bound(int searchKey) const{
    Node* x = head;

    for (unsigned int i = nodeLevel(head); i-- > 0;) {
        while ( x->forward[i]->key < searchKey) {
            x = x->forward[i];
        }
    }
    return x->forward[0];
}

std::vector<Set::Node*> Set::predecessors(int searchKey) const {
    std::vector<Node*> result(nodeLevel(head),nullptr);
    Node* x = head;

    for (unsigned int i = nodeLevel(head); i-- > 0;) {
        while (x->forward[i]->key < searchKey) {
            x = x->forward[i];
        }
        result[i] = x;
    }
    return result;
}



//==================================================
int main() {

    int nmax = 20000;
    int n0 = 2000;
    int delta = 1000;
    int M = 100;

    std::ofstream o;
    o.open("number_pointers.csv");
    for (double q = 0.1; q <= 0.91; q += 0.1001){
        std::cout << q << std::endl;
        for(int n = n0; n<nmax; n+= delta){
            std::cout << n << std::endl;
            int ptrs = 0;
            for(int i = 0; i < M; i++){
                Set s = Set(q);
                for(int el = 0; el<n; el++){
                std::stringstream ss;
                ss << el;
                s.insert(el,ss.str());
            }
            ptrs += s.number_pointers();
            }
            o << ptrs/M << ",";
        }
        o << std::endl;
    }


}

//Code partially from https://codereview.stackexchange.com/questions/116345/skip-list-implementation
