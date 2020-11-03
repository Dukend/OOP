#ifndef EXPLICIT_H
#define	EXPLICIT_H

template <class T> class MyStack {
private:
    struct StackItem {
        StackItem *next;
        T          item;
        StackItem(T value) : item(value), next(nullptr){};
    };

    StackItem* current;

public:
    MyStack(void);
    void push(T item);
    void pop(void);
    T    top();
    bool empty();

    ~MyStack(void);
};

#endif	

