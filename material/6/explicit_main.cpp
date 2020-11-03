#include <iostream>
#include "explicit.h"

int main(){

    MyStack<int> stack_int;

    for(int i=0;i<10;i++) stack_int.push(i);
    while(!stack_int.empty()) {
        std::cout << stack_int.top() << ' ';
        stack_int.pop();
    }
    std::cout << std::endl;
    
    MyStack<int*> stack_int_ptr;
    for(int i=0;i<10;i++) stack_int_ptr.push(new int[1]);

    return 1;
}