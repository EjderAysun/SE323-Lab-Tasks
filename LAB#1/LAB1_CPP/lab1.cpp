#include <iostream>
#include <string>
#include <optional>

using std::string;
using std::cout;
using std::endl;
using std::optional;
using std::nullopt;

// Node struct for Multiset
struct Node {
    string data;
    int number;
    Node* next;
    /*
    @note
        The reason why the next node is automatically nullptr every time
        a node is constructed is because I use this as a control condition in some methods.
        @example
            ...
            while(temp != nullptr) {
                ...
            }
   @note
        This method cannot change the value of the parameters entered,
        but it can change the data members of the structure.
   */
    Node(const string element, const int n) : data(element), number(n), next(nullptr) {}
};

struct Multiset {
    private:
        // The "head" is the first node added and the "curr" is the last node added. \
        Both are not nullptr.
        Node *head, *curr;

        /*
        @note
            helper method for add(element)
        @note
            This method cannot change the value of the parameters entered and data members of the structure.
        @note
            I used the "optional" feature added in C++17.
            The traditional way can also be used:
            @example
                Node* tryReturnNode(const string& element) const {
                for(Node *temp = head; temp != nullptr; temp = temp->next) {
                    if(temp->data == element) return temp;
                }
                return nullptr;
        }
        */
        optional<Node*> tryReturnNode(const string& element) const {
            // Check for "element" data from "head" to next to "curr" node.
            for(Node *temp = head; temp != nullptr; temp = temp->next) {
                // If data "element" is found, then return the node where it was found.
                if(temp->data == element) return temp;
            }
            // If data "element" is not found in the for loop, then return nullopt.
            return nullopt;
        }

    public:
        /*
        
        @note
            This method cannot change the value of the parameters entered,
            but it can change the data members of the structure.
        */
        void add(const string element) {
            // Assign returned optional node pointer to x.
            optional<Node*> x = tryReturnNode(element);
            // If x is not nullopt then,
            if(x.has_value()) {
                // assign node pointer to node_ptr,
                Node* nodePtr = x.value();
                // and increase the number of data by 1 because the data already exists.
                nodePtr->number++;
            }
            // If x is nullopt then,
            else {
                // create a new node and assign 1 to the number of the data \
                since this is the first time the data is added.
                Node *newNode = new Node(element, 1);

                // if head is NULL then,
                if(head == NULL) {
                    // assign the new node to both "head" and "curr" \
                    since the first node created in the multiset \
                    will be both the first and the current node.
                    head = curr = newNode;
                }
                // if head is not NULL then,
                else {
                    // Multiset has at least 1 element, which means it has a "head" node. \
                    Therefore assign the "curr" node to the next node of the "curr" node, \
                    and then assign the new node to the "curr" node.
                    curr = curr->next = newNode;
                }
            }
        }
};