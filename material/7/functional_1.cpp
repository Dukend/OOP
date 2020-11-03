#include <iostream>
#include <string>
#include <vector>

enum class person_sex_t{
    Male = 0,
    Female = 1
};

struct Person{
    std::string  name;
    person_sex_t sex;
};


template <class T,class FILTER>
void transorm(std::vector<T> &input,
              std::vector<T> &output,FILTER filter){
    for(auto a: input)
        if(filter(a)) output.push_back(a);
};

template <class T,class ACTION>
void applay(std::vector<T> &input,ACTION action){
    for(auto a: input) action(a);
};

int main(){

    std::vector<Person> persons;

    persons.push_back(Person {"Peter",person_sex_t::Male});
    persons.push_back(Person {"Jane",person_sex_t::Female});
    persons.push_back(Person {"Tom",person_sex_t::Male});
    persons.push_back(Person {"Martha",person_sex_t::Female});
    persons.push_back(Person {"David",person_sex_t::Male});
    persons.push_back(Person {"Rose",person_sex_t::Female});

    std::vector<Person> females;
    transorm(persons,females,[]( const Person &person){
                                if(person.sex==person_sex_t::Female) return true;
                                    else return false;
                            });

    applay(females, [](const Person& person){
                std::cout << "[" << person.name << "]" << std::endl;
            });


    return 1;
}