
#ifndef LinkedList_H
#define LinkedList_H

#include <algorithm>

class LinkedList {
friend void swap(LinkedList& lhs, LinkedList& rhs) {
    using std::swap;
    swap(lhs.head, rhs.head);
    swap(lhs.length, rhs.length);
}
private:
    struct Node {
        double data;
        Node* next;
        Node(double d):data(d),next(nullptr) {}
        Node():data(0),next(nullptr) {}
    };
    Node* head;
    int length;
    // private utility functions
    void copy_helper(Node*&, Node*);
    Node* find_helper(double, Node*, int&) const;
    Node* find_helper(Node*, int) const;
    void print_rev_helper(Node*) const;
    void reverse_helper(Node*, Node*, Node*);
    void destruct_helper(Node*);
public:
    // constructor - assignment - destructor
    LinkedList();
    LinkedList(const LinkedList&);
    LinkedList& operator=(LinkedList);
    LinkedList(LinkedList&&);
    ~LinkedList();
    // print - find information
    void print_length() const;
    void print_index(double) const;
    void print_data(int) const;
    void print_forward() const;
    void print_reverse() const;
    // updata - add - remove
    void update_node(double, double);
    void add_node_front(double);
    void add_node_middle(double, int);
    void add_node_end(double);
    void rem_node(double);
    void reverse_list_iterate();
    void reverse_list_recurse();
    void splice(int, const LinkedList&);
};

#endif
