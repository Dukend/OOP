#include <exception>

int func() throw() {
    return 42;
}

int func_with_specification() throw(std::exception) {
    return 142;
}

int func_noexcept() noexcept {
    return 1420;
}

int main() {
    func();
    func_with_specification();
    func_noexcept();
    return 0;
}