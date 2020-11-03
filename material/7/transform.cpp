    #include <vector>
    #include <algorithm>
    #include <iostream>

    auto main() -> int
    {

      std::vector<int> vect;
      for (int i = 0; i < 10; ++i)
        vect.push_back(i);


      std::cout << "Original Data:" << std::endl;
      std::for_each(
             std::begin(vect),
             std::end(vect),
             [](int n){
                std::cout << n << " ";
            });
      std::cout << std::endl;

      std::vector<int> vect2;
      vect2.resize(vect.size());
      std::transform(
              std::begin(vect),
              std::end(vect),
              std::begin(vect2),
              [](int n) {
                return n * n;
            });

      std::cout << "Squared Data:" << std::endl;
      std::for_each(
             std::begin(vect2),
             std::end(vect2),
             [](int n) {
                std::cout << n << " ";
            });
      std::cout << std::endl;

      std::vector<double> vect3;
      vect3.resize(vect.size());
      std::transform(
              std::begin(vect2),
              std::end(vect2),
              std::begin(vect3),
              [](int n) -> double {
                return n / 2.0;
            });

      std::cout << "Average Data:" << std::endl;
      std::for_each(
             std::begin(vect3),
             std::end(vect3),
             [](double d) {
                std::cout << d << " ";
            });
      std::cout << std::endl;

      return 0;
     }