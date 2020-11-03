
namespace foo_namespace{
    void foo(){

    }
}

int main(){
    foo_namespace::foo();

    using namespace foo_namespace;
    foo();
    
    return 0;
}