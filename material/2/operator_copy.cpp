#include <cstdlib>
#include <iostream>

#define UNUSED(value) (void)value

class Message{
    private:
        class Payload{
            int a[1024] {};
        };

        Payload *_value;
    public:
        Message(){
            std::cout << "Constructor default" << std::endl;
            _value = new Payload();
        }

        Message(const Message &rhv) : Message(){
            std::cout << "Constructor copy" << std::endl;
            memcpy(_value,rhv._value,sizeof(Payload));
            
        }

        Message& operator=(const Message &rhv){
            std::cout << "Copy" << std::endl;
            memcpy(_value,rhv._value,sizeof(Payload));
            return *this;
        }

        Message& operator=(Message &&rhv) noexcept{
            std::cout << "Move" << std::endl;
            if(_value) delete _value;
            _value = rhv._value;
            rhv._value = nullptr;
            return *this;
        }

        ~Message(){
            std::cout << "Delete" << std::endl;
            delete _value;
        }

};

int main(int argc, char** argv) {
    
    std::cout << "Creation section --------" << std::endl;
    Message one;
    Message two;

    std::cout << "Copy section --------" << std::endl;
    one=two;

    std::cout << "Move section 1 --------" << std::endl;
    two = Message();

    std::cout << "Move section 2 --------" << std::endl;

    one = std::move(two);

    std::cout << "Destruction section --------" << std::endl;

    UNUSED(argc);
    UNUSED(argv);

    return 0;
}