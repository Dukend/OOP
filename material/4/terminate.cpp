#include <iostream>
using namespace std;

void term_func() {
    cout << "My term_func was called by terminate." << endl;
    exit(-1);
}


int main() {
    set_terminate(term_func);

    //try {
       
        throw "Out of memory!"; // No catch handler for this exception
   // } catch (int) {
   //     cout << "Integer exception raised." << endl;
   // }
    return 0;
}

