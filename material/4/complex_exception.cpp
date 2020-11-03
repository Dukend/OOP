#include <iostream>
#include <exception>

struct MyException : public std::exception {
    int payload; // some value

    MyException(int a) : std::exception(), payload(a) {
        std::cout << "Exception constructed\n";
    }
//*
    MyException(const MyException & other) : std::exception(other) {
        payload = other.payload;
        std::cout << "Copy exception constructed" << std::endl;
    }
//*/
     ~MyException() {
        std::cout << "Exception destructed" << std::endl;
    };
};

void proc2(void) {
    try {

        std::cout << "Proc2 called" << std::endl;
        //std::string().at(1); // this generates an std::out_of_range
        throw 42; //custom class
        //throw MyException(100);

    } catch (int ex1) {
        std::cout << "int in Proc2" << std::endl;

    } catch (MyException ex) {
        std::cout << "MyException in Proc2: " << ex.payload << std::endl;
        //std::exception_ptr currentException = std::make_exception_ptr(ex);
       // std::rethrow_exception(currentException);
        throw;
       // std::cout << "end handler" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Unknown exception" << std::endl;
    }
}

void proc1(void) {
    try {
        std::cout << "Proc1 called" << std::endl;
        proc2();
    } catch (const std::exception& e) {
        std::cout << "Exception in Proc1:" << e.what() << std::endl;

    }
}

int main() {
    proc1();
    return 0;
}

