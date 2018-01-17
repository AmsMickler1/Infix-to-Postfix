// Amber Mickler
// COP4530
// Assignment 3
// stack.hpp

#include "stack.h"
using namespace cop4530;

template <typename T>
void Stack<T>::init() {
    sList = std::list<T>();
}

template <typename T>
Stack<T>::Stack() {
    init();
}   // default constructor

template <typename T>
Stack<T>::~Stack() {
    clear();
}   // destructor

template <typename T>
Stack<T>::Stack(const Stack<T>& rhs) {
    init();
    sList = rhs.sList;
}   // copy constructor

template <typename T>
Stack<T>::Stack(Stack<T>&& rhs){
    init();
    std::move(sList, rhs.sList);
}   // move constructor

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs) {
    clear();
    sList = rhs.sList;
    return *this;
}   // copy assignment operator

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& rhs) {
    clear();
    sList = rhs.sList;
    return *this;
}   // move assignment operator

template <typename T>
bool Stack<T>::empty() const {
    return sList.empty();
}   // returns true if stack is empty

template <typename T>
void Stack<T>::clear() {
    sList.clear();
}   // delete all stack elements

template <typename T>
void Stack<T>::push(const T& x) {
    sList.push_front(x);
}   // adds x to the stack (copy)

template <typename T>
void Stack<T>::push(T && x) {
    sList.push_front(std::move(x));
}   // adds x to the stack (move)

template <typename T>
void Stack<T>::pop() {
    sList.pop_front();
}   // removes and discards top of stack

template <typename T>
T& Stack<T>::top() {
    return sList.front();
}   // returns a reference to top of stack

template <typename T>
const T& Stack<T>::top() const {
    return sList.front();
}   // returns top of stack as a const reference

template <typename T>
int Stack<T>::size() const {
    return sList.size();
}   // returns number of elements in the stack

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
    for (auto itr = sList.rbegin(); itr != --sList.rend(); itr++) {
        os << *itr << ofc;
    }
    auto itr = --sList.rend();
    os << *itr;
}   // prints elements of stack to stream with delimiter ofc
    // note proper order is bottom -> top of stack

// operator << overload - calls print() function
template <typename T>
std::ostream& operator<<(std::ostream &os, const Stack<T>& s) {
    s.print(os);
    return os;
}

// operator == overload - return true if two stacks are identical
template <typename T>
bool operator==(const Stack<T>& x, const Stack<T>& y) {
    auto a = x;
    auto b = y;
    if (a.size() != b.size())
        return false;
    while (!a.empty()) {
        if (a.top() != b.top())
            return false;
        else {
            a.pop();
            b.pop();
        }
    }
    return true;
}

// operator != overload - opposite of ==
template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b) {
    return !(a == b);
    return true;
}

// operator <= overload - returns true if EVERY element of a is less than the corresponding element of b
template <typename T>
bool operator<=(const Stack<T>& x, const Stack<T>& y) {
    auto a = x;
    auto b = y;

    while (!a.empty()) {
        if (b.empty() || a.top() > b.top())
            return false;
        a.pop();
        b.pop();
    }
    return true;
}
