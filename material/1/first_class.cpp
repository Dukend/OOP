#include <cstdlib>
#include <iostream>

#define UNUSED(variable) (void)variable

class MyClass {
//	public:
    int Number;
    void doSomething();
};


void  MyClass::doSomething(){
    ((std::cout << "Number:" )<< Number) << std::endl;
}

int main(int argc, char** argv) {

    MyClass a,b;  // Create object by Value
    a.Number = 3;
	b.Number = 17;
	a.doSomething();
	b.doSomething();
//*
	MyClass *a_ptr; // Pointer to the object

	a_ptr = new MyClass(); //malloc
	a_ptr->Number = 10;
	a_ptr->doSomething();
	delete a_ptr; //free
//*/

	UNUSED(argc);
	UNUSED(argv);

    return 0;
}

