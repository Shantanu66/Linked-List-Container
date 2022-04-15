
#include "LinkedList.h"
#include <iostream>


// constructor - assignment - destructor - - - - - - - - - - - - - - - - - - -

// constructor
LinkedList::LinkedList():head(nullptr),length(0) {}

// copy constructor
LinkedList::LinkedList(const LinkedList& rhs):head(new Node),length(rhs.length) {
    if (rhs.head) {copy_helper(head,rhs.head);}
}

// assignment operator (copy/move)
LinkedList& LinkedList::operator=(LinkedList rhs) {
    swap(*this, rhs);
    return *this;
}

// move constructor
LinkedList::LinkedList(LinkedList&& rhs):LinkedList() {swap(*this, rhs);}

// destructor
LinkedList::~LinkedList() {if (head != nullptr) {destruct_helper(head);}}

// public member functions: - - - - - - - - - - - - - - - - - - - - - - - - - -

// print the list length
void LinkedList::print_length() const {
    std::cout << "length: " << length << std::endl;
}

// print the index and data of the node (search by data)
void LinkedList::print_index(double data) const {
    int index = 0;
    Node* ans = find_helper(data, head, index);
    if (ans) {
        std::cout << ans->data << " is at index " << index;
        std::cout << std::endl;
    }
}

// print the index and data of the node (search by index)
void LinkedList::print_data(int index) const {
    Node* ans = find_helper(head, index);
    if (ans) {
        std::cout << ans->data << " is at index " << index;
        std::cout << std::endl;
    }
}

// print the content of the linked list (front to end)
void LinkedList::print_forward() const {
    Node* p = head;
    if (!p) {
        std::cout << "the list is empty !" << std::endl;
    } else {
        while (p->next) {
            std::cout << p->data << " - ";
            p = p->next;
        }
        std::cout << p->data << " - ";
        std::cout << "\n - - - - - - - - - - - - - - - - - \n";
    }
}

// print the content of the linked list (end to front)
void LinkedList::print_reverse() const {
    if (!head) {
        std::cout << "the list is empty !" << std::endl;
    } else {
        print_rev_helper(head);
        std::cout << "\n - - - - - - - - - - - - - - - - - \n";
    }
}

// update the data of an existing node
void LinkedList::update_node(double old_val, double new_val) {
        int position = 0;
        Node* ans = find_helper(old_val, head, position);
        if (ans) {ans->data = new_val;}
}

// add a new node to the beginning of the linked list
void LinkedList::add_node_front(double data) {
    Node* new_node = new Node(data);
    if (!head) {
        head = new_node;
    } else {
        new_node->next = head;
        head = new_node;
    }
    ++length;
}

// add a new node to the middle of the linked list
void LinkedList::add_node_middle(double data, int n) {
    Node* new_node = new Node(data);
    if (!head) {
        head = new_node;
        ++length;
    } else if (n == 0) {
        add_node_front(data);
    } else {
        Node* ans = find_helper(head, n-1);
        Node* temp = ans->next;
        ans->next = new_node;
        new_node->next = temp;
        ++length;
    }
}

// add a new node to the end of the linked list
void LinkedList::add_node_end(double data) {
    Node* new_node = new Node(data);
    if (!head) {
        head = new_node;
    } else {
        Node* ans = find_helper(head, length-1);
        ans->next = new_node;
    }
    ++length;
}

// remove an existing node from the linked list
void LinkedList::rem_node(double data) {
    Node* delPtr = nullptr;
    bool exist = false;
    if (!head) {
        std::cout << "the list is empty!" << std::endl;
    } else if (head->data == data) {
        delPtr = head;
        head = head->next;
        delete delPtr;
        --length;
    } else {
        Node* p1 = head;
        Node* p2 = head->next;
        while (p2 && p2->data != data ) {
            p1 = p2;
            p2 = p2->next;
        }
        if (!p2) {
            std::cout << data << " is not in the list!";
            std::cout << std::endl;
        } else {
            delPtr = p2;
            p1->next = p2->next;
            delete p2;
            --length;
        }
    }
}

// reverse the list through iteration
void LinkedList::reverse_list_iterate() {
    if (head && head->next) {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = head->next;
        while (next) {
            curr->next = prev;
            prev = curr;
            curr = next;
            next = next->next;
        }
        curr->next = prev;
        head = curr;
    }
}

// reverse the list through recursion
void LinkedList::reverse_list_recurse() {
    if (head && head->next) {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = head->next;
        reverse_helper(prev, curr, next);
    }
}

// make a deep copy of input list to the index n of the current list
void LinkedList::splice(int n, const LinkedList& obj) {
    if (!head) {
        copy_helper(head, obj.head);
    } else {
        Node* new_head = new Node;
        copy_helper(new_head, obj.head);
        Node* new_end = find_helper(new_head, obj.length-1);
        if (n == 0) {
            Node* temp = head;
            head = new_head;
            new_end->next = temp;
        } else {
            Node* temp1 = find_helper(head, n-1);
            Node* temp2 = temp1->next;
            temp1->next = new_head;
            new_end->next = temp2;
        }
    }
    length += obj.length;
}

// private utility functions: - - - - - - - - - - - - - - - - - - - - - - - -

// used by copy constructor. performs deep copy from 'source' to 'target'
void LinkedList::copy_helper(Node*& target, Node* source) {
    Node* creator = new Node(source->data);
    target = creator;
    Node* iterator = source->next;
    while (iterator != nullptr) {
        creator->next = new Node;
        creator = creator->next;
        creator->data = iterator->data;
        iterator = iterator->next;
    }
    creator->next = nullptr;
}

// used by print_index() and update_node(). 
// look for the node with data starting at 'search' to the end of the list
LinkedList::Node* LinkedList::find_helper(double data, Node* search,
                                          int& index) const {
    if (!search) {
        std::cout << data << " is not in the list!" << std::endl;
        return nullptr;
    } else {
        while (search->data != data && search->next) {
            search = search->next;
            ++index;
        }
        if (search->data == data) {
            return search;
        } else {
            std::cout << data << " is not in the list!" << std::endl;
            return nullptr;
        }
    }
}

// used by print_data(), add_node_middle(), add_node_end(), splice()
// look for the node with index starting at search to the end of the list
LinkedList::Node* LinkedList::find_helper(Node* search, int index) const {
    if (!search) {
        std::cout << "index: " << index << " not in the list!" << std::endl;
        return nullptr;
    } else {
        int n = 0;
        while (n != index && search->next) {
            search = search->next;
            ++n;
        }
        if (n == index) {
            return search;
        } else {
            std::cout << "index: " << index << " not in the list!" << std::endl;
            return nullptr;
        }
    }
}

// used by print_reverse()
void LinkedList::print_rev_helper(Node* temp) const {
    if (!temp) {return;}
    print_rev_helper(temp->next);
    std::cout << temp->data << " - ";
}

// used by reverse_list_recurse()
void LinkedList::reverse_helper(Node* prev, Node* curr, Node* next) {
    if (!next) {
        curr->next = prev;
        head = curr;
        return;
    }
    curr->next = prev;
    prev = curr;
    curr = next;
    next = next->next;
    reverse_helper(prev, curr, next);
}

// used by destructor. destroys all the nodes from temp to the end 
void LinkedList::destruct_helper(Node* temp) {
    while (temp) {
        Node* delPtr = temp;
        temp = temp->next;
        delete delPtr;
    }
}


