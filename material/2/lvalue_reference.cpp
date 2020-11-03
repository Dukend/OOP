#include <string>
#include <iostream>


void foo(std::string &val){
    val = "I am foo";
}

std::string& boo(std::string val){
    val = "I am boo";
    return val;
}

int main() {
    
    std::string value = "Hello world!";

    std::cout << "value = " << value << std::endl;
    foo(value);
   // std::cout << "value = " << value << std::endl;
   // std::string& val2 = boo(value);
   // std::cout << "value = " << val2 << std::endl;
    return 0;
}