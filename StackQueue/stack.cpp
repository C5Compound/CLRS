/**
 *  用数组和链表两种方式实现栈
 */

#include <cstdlib>
#include <iostream>
#include <cassert>
using namespace std;

struct node
{
    int data;
    node *next;
};

class ListStack
{
private:
    node *HEAD;
    size_t count;
public:
    ListStack();
    ~ListStack();
    void push(int);
    size_t Count();
    int pop();
};

ListStack::ListStack() : HEAD(NULL), count(0)
{
}

ListStack::~ListStack()
{
    if (count > 0) {
        node *it = HEAD;
        while (it != NULL) {
            node *tmp = it;
            it = it->next;
            free(tmp);
        }
    }
}

void ListStack::push(int x)
{
    node *it = (node*)calloc(1, sizeof(node));
    it->data = x;
    it->next = HEAD;
    HEAD = it;
    count += 1;
}

size_t ListStack::Count()
{
    return count;
}

int ListStack::pop()
{
    assert(count > 0);
    int data = HEAD->data;
    node *it = HEAD->next;
    free(HEAD);
    HEAD = it;
    count -= 1;
    return data;
}

#define STACK_SIZE 10

class ArrayStack
{
private:
    static const size_t step = 10;
    size_t cap;
    size_t count;
    int *buf;
    void re_capacity(size_t);
public:
    ArrayStack();
    ~ArrayStack();
    void push(int);
    int pop();
    size_t Count();
};

ArrayStack::ArrayStack() : cap(STACK_SIZE), count(0), buf(NULL)
{
    buf = (int*)calloc(STACK_SIZE, sizeof(int));
    assert(buf != NULL);
}

ArrayStack::~ArrayStack()
{
    if (count > 0) {
        free(buf);
    }
}

void ArrayStack::push(int data)
{
    if (count >= cap) {
        re_capacity(cap += step);
    }
    buf[count ++] = data;
}

int ArrayStack::pop()
{
    assert(count > 0);
    int tmp = buf[count-1];
    count -= 1;
    return tmp;
}

size_t ArrayStack::Count()
{
    return count;
}

void ArrayStack::re_capacity(size_t cap)
{
    buf = (int*)realloc(buf, cap * sizeof(int));
    assert(buf != NULL);
}

// int main()
// {
//     ArrayStack as;
//     for (int i = 0; i < 30; i++) {
//         as.push(i);
//     }
//     while (as.Count() > 0) {
//         cout << as.pop() << endl;
//     }
//     return 0;
// }