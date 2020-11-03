#include <iostream>

enum Alphabet {
    a, b, c
};

enum Animal {
    dog, cat, fish
};

enum class Digit : uint64_t {
    one = 1, 
    two = 193, 
    three = 247
};

void foo(int) {
}

void bar(Digit) {
}

void baz(Alphabet) {
}

int main(int, char *[]) {

    foo(42); 
    foo(a); // It works!
    foo(fish); // It works!
    // foo(Digit::one); // no known conversion from 'Digit' to 'int'

    // bar(42); // no known conversion from 'int' to 'Digit'
    // bar(a); // no known conversion from 'Alphabet' to 'Digit'
    // bar(dog); // no known conversion from 'Animal' to 'Digit'
    bar(Digit::two);

    // baz(42); // no known conversion from 'int' to 'Alphabet'
    baz(a);
    // baz(dog); // no known conversion from 'Animal' to 'Alphabet'
    // baz(Digit::two); // no known conversion from 'Digit' to 'Alphabet'

    foo(static_cast<int>(Digit::one));
    bar(Digit::two);

    return 0;
}