 /* lambda_tiny_func.cpp */
    #include <vector>
    #include <algorithm>
    #include <iostream>
    #include <string>

  

    struct Vehicle{
        std::string name;
        size_t size;
    };

    auto main() -> int
    {
      std::vector<Vehicle> vehicles = { {"car", 4}, {"motorcycle", 2}, {"bicycle", 2}, {"bus", 6} };

      std::cout << "All vehicles:" << std::endl;
      std::for_each(
             std::begin(vehicles),
             std::end(vehicles),
             [](const Vehicle &vehicle){
                 std::cout << vehicle.name << std::endl;
            });

      return 0;
    }