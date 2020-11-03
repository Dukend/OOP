#include <iostream>

template <class T> class SafeWorker {
public:
    virtual void action() noexcept{
        std::cout << "Begin" << std::endl;
        try {
            T* t = dynamic_cast<T*>(this);
            if(t) t->action_impl();
        } catch (...) {
            std::cout << "Unexpected exception" << std::endl;
            throw;
        }
        std::cout << "End" << std::endl;
    }
};

class GoodWorker : public SafeWorker<GoodWorker> {
protected:
    friend SafeWorker<GoodWorker>;
    void action_impl() {
        std::cout << "Some action ..." << std::endl;
    }
};

class EvilWorker : public SafeWorker<EvilWorker> {
protected:
    friend SafeWorker<EvilWorker>;
    void action_impl() {
        throw *this;
    }
};

int main(int argc, char** argv) {

    SafeWorker<GoodWorker> s;
    s.action();


    GoodWorker g;
    g.action();

    EvilWorker e;
    e.action();
    //e.action_impl();

    return 0;
}

