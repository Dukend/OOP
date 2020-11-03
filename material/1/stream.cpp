#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#define UNUSED(variable) (void)variable

int main(int argc, char **argv){
    std::string file_name;
    std::string file_text;

    std::cout << "Please enter file name:";
    std::cin >> file_name;

    std::ofstream out_file(file_name, std::ofstream::out);

    std::cout << "Please enter file text:";
    while (std::cin >> file_text)
        out_file << file_text << std::endl;
    out_file.close();

    std::cout << "Result:" << std::endl;
    std::ifstream in_file(file_name);
    while (in_file >> file_text)
        std::cout << file_text << std::endl;
    in_file.close();

    UNUSED(argc);
    UNUSED(argv);

    return 0;
}
