// Amber Mickler
// COP4530
// Assignment 3
// stack.h

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <list>

namespace cop4530 {

    template <typename T>
    class Stack{

    private:
        std::list<T> sList;
        void init();

    public:
        Stack();                        // default constructor
        ~Stack();                       // destructor
        Stack(const Stack<T>&);         // copy constructor
        Stack(Stack<T>&&);              // move constructor

        Stack<T>& operator=(const Stack<T>&);   // copy assignment operator
        Stack<T>& operator=(Stack<T>&&);        // move assignment operator

        bool empty() const;             // returns true if stack is empty
        void clear();                   // delete all stack elements
        void push(const T& x);          // adds x to the stack (copy)
        void push(T && x);              // adds x to the stack (move)
        void pop();                     // removes and discards top of stack
        T& top();                       // returns a reference to top of stack
        const T& top() const;           // returns top of stack as a const reference
        int size() const;               // returns number of elements in the stack

        void print(std::ostream& os, char ofc = ' ') const;
        // prints elements of stack to stream with delimiter ofc
        // note proper order is bottom -> top of stack



    };   // end of class Stack

    // operator << overload - calls print() function
    template <typename T>
    std::ostream& operator<<(std::ostream &os, const Stack<T>& s);
    // operator == overload - return true if two stacks are identical
    template <typename T>
    bool operator==(const Stack<T>&, const Stack<T>&);
    // operator != overload - opposite of ==
    template <typename T>
    bool operator!=(const Stack<T>&, const Stack<T>&);
    // operator <= overload - returns true if EVERY element of a is less than the corresponding element of b
    template <typename T>
    bool operator<=(const Stack<T>& a, const Stack<T>& b);

    #include "stack.hpp"
}   // end of namespace cop4530

#endif
