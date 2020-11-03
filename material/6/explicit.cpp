#include "explicit.h"
#include <iostream>
#include <type_traits>

/**
 * Template for pointer deletion
 */
template <class T> 
typename std::enable_if<!std::is_pointer<T>::value,void>::type release(T& value){
    std::cout << "empty delete" << std::endl;
}

template <class T> 
typename std::enable_if<std::is_pointer<T>::value,void>::type release(T& value){
    std::cout << "delete" << std::endl;
    delete value;
}
/**
 * template realization
 */
template <class T> MyStack<T>::MyStack(void) : current(nullptr) {
}

template <class T> void MyStack<T>::push(T item) {
    StackItem *stack_item = new StackItem(item);
    stack_item->next = current;
    stack_item->item = item;
    current = stack_item;
}

template <class T> T    MyStack<T>::top(){
    if (current != nullptr) {
        return current->item;
    } else return T{};
}

template <class T> bool MyStack<T>::empty(){
    return current==nullptr;
}

template <class T> void MyStack<T>::pop(void) {
    if (current != nullptr) {
        StackItem *stack_item = current;
        current = stack_item->next;
        delete stack_item;
    }
}

template <class T> MyStack<T>::~MyStack(void) {
    while (current != nullptr) {
        StackItem *old = current;
        current = current->next;

        //metafunction
        release(old->item);

        delete old;
    }
}

// explicit instantation
template class MyStack<int>;
template class MyStack<int*>;
