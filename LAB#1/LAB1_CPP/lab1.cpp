#include <iostream>
#include <string>
#include <optional>
#include <limits>

using std::string;
using std::cout;
using std::endl;
using std::optional;
using std::nullopt;
using std::cerr;
using std::cin;
using std::numeric_limits;
using std::streamsize;

// Node struct for Multiset
struct Node {
    string data;
    int number;
    Node *next, *prev;

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
    Node(const string element, const int n) : data(element), number(n), next(nullptr), prev(nullptr) {}
};

struct Multiset {
    private:
        // The "head" is the first node added and the "curr" is the last node added. \
        Both are not nullptr.
        Node *head, *curr;

        /*
        @note
            helper method for add(element) method and count(element) method
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

        /*
        @note
            helper method for remove(element)
        @note
            This method cannot change the value of the parameters entered and data members of the structure.
        @note
            A template for printing errors after catching.
        */
        template<typename T>
        void CatchExceptions(const T& e) const {
            cerr << e;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                // If "head" node is nullptr then,
                if(head == nullptr) {
                    // assign the new node to both "head" and "curr" \
                    since the first node created in the multiset \
                    will be both the first and the current node.
                    head = curr = newNode;
                }
                // If "head" node is not nullptr then,
                else {
                    // assign the current node to the prev of the new node.
                    newNode->prev = curr;
                    // Multiset has at least 1 element, which means it has a "head" node. \
                    Therefore assign the "curr" node to the next node of the "curr" node, \
                    and then assign the new node to the "curr" node.
                    curr = curr->next = newNode;
                }
            }
        }

        /*
        @note
            This method cannot change the value of the parameters entered,
            but it can change the data members of the structure.
        */
        void remove(const string element) {
            // try-throw-catch struct
            try {
                // If "head" node is nullptr then, throw this.
                if(head == nullptr) {
                    throw "Multiset is empty, this element already does not exist: " + element;
                }
                // Assign returned optional node pointer to x.
                optional<Node*> x = tryReturnNode(element);
                // If x is not nullopt then,
                if(x.has_value()) {
                    // assign node pointer to node_ptr.
                    Node* nodePtr = x.value();
                    // If there is only 1 instance of the element then,
                    if(nodePtr->number == 1) {
                        // if nodePtr is "head" node then,
                        if(nodePtr == head) {
                            // if the next node of the "head" node is nullptr then,
                            if(head->next == nullptr) {
                                // both "head" and "curr" node will be nullptr, so we are back to square one.
                                head = curr = nullptr;
                            }
                            // if the next node of the "head" node is not nullptr then,
                            else {
                                // the "head" node assigns to the its next node,
                                head = head->next;
                                // and nullptr is assigned to the prev node of the "head" node.
                                head->prev = nullptr;
                            }
                        }
                        // if nodePtr is curr then,
                        else if (nodePtr == curr) {
                            // the "curr" node assigns to the its prev node,
                            curr = curr->prev;
                            // and nullptr is assigned to the next node of the "curr" node.
                            curr->next = nullptr;
                        } else {
                            // The next node of the node to be deleted is assigned to \
                            the next node of the prev node of the node to be deleted.
                            nodePtr->prev->next=nodePtr->next;
                            // The prev node of the node to be deleted is assigned to \
                            the prev node of the next node of the node to be deleted.
                            nodePtr->next->prev=nodePtr->prev;
                            // Finally, the empty node is deleted.
                        }
                        // Finally, the idle node needs to be deleted.
                        delete nodePtr;
                    }
                    // If there is more than one instance of the data then, \
                    reduce the number of instances of the data by 1.
                    else nodePtr->number--;
                }
                // If x is nullopt then, throw this.
                else throw "Multiset does not have such an element: " + element;

            } catch(const string& e) {
                CatchExceptions(e);
            }
        }

        /*
        @note
            This method cannot change the value of the parameters entered and data members of the structure.
        */
        int count(const string element) const{
            // If "head" node is nullptr then, throw this.
            if(head == nullptr) {
                return 0;
            }
            // Assign returned optional node pointer to x.
            optional<Node*> x = tryReturnNode(element);
            // If x is not nullopt then,
            if(x.has_value()) {
                // assign node pointer to node_ptr.
                Node* nodePtr = x.value();
                // Then return the number of data.
                return nodePtr->number;
            }
            // If x is nullopt then, throw this.
            else return 0;
        }

        /*
        @note
            This method cannot change the data members of the structure.
        */
        int distinctElements() const {
            int numberOfDistinctElements = 0;
            // Count all nodes from head node to current node.
            for(Node *temp = head; temp != nullptr; temp = temp->next) {
                // Add 1 to the number of distinct elements in each loop.
                numberOfDistinctElements++;
            }
            // Then return numberOfDistinctElements.
            return numberOfDistinctElements;
        }
};