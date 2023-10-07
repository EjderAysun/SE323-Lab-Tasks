#include <iostream>
#include <string>

using std::string;

// Node struct for Multiset
struct Node {
    string data;
    int number;
    Node* next;
    /*
    The reason why the next node is automatically nullptr every time
    a node is constructed is because I use this as a control condition in some methods.
    @example
        ...
        while(temp != nullptr) {
            ...
        }
    */
    Node(const string s, const int n) : data(s), number(n), next(nullptr) {}
};