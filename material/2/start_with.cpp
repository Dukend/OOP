#include <string>
#include <iostream>

class starts_with {
    std::string prefix;
public:
    starts_with(std::string prefix) : prefix(prefix) {}

    friend bool operator|(const std::string& lhv, starts_with const& rhv) {
        return lhv.size() >= rhv.prefix.length() && lhv.substr(0, rhv.prefix.length()) == rhv.prefix;
    }
};

int main() {
    std::string value("hello world!");

    std::cout << (value | starts_with(std::string("hello")));
    return 1;
}