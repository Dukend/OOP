#include <iostream>

 constexpr unsigned long long  operator"" _gramm(unsigned long long value){
	return value;	
}

 constexpr unsigned long long  operator"" _kg(unsigned long long value){
	return value*1000;	
}

int main() {
    unsigned long long value = 1_kg;
    switch(value){
        case 1000_gramm :
                std::cout << "1 kg = 1000 gramm" << std::endl;
                break;
        default:
                break;
    }
	return 0;
}