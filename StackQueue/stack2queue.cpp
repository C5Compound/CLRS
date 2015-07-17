/**
 *  
 */
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

class Queue
{
private:
    stack<int> A;
    stack<int> B;
    size_t count;
public:
    Queue();
    ~Queue();
    void enqueue1(int);
    int dequeue1();
    void enqueue2(int);
    int dequeue2();
    size_t size();
};

Queue::Queue() : count(0)
{
}

Queue::~Queue()
{
}

size_t Queue::size()
{
    return count;
}

/**
 *  方式一：入队时使用队A，出队时先把A倒到B，弹出最后一个，再把数据从B倒出来
 *  方式一可以衍生出方式三，入队再把B倒过去，这两种方法都不如方式二
 */
void Queue::enqueue1(int data)
{
    A.push(data);
    count += 1;
}

int Queue::dequeue1()
{
    assert(count > 0);
    while (A.size() > 1) {
        B.push(A.top());
        A.pop();
    }
    int data = A.top();
    A.pop();
    while (!B.empty()) {
        A.push(B.top());
        B.pop();
    }
    count -= 1;
    return data;
}

/**
 *  方式二：入队时使用A，出队时使用B，如果B为空则把A中数据弹到B
 */
void Queue::enqueue2(int data)
{
    A.push(data);
    count += 1;
}

int Queue::dequeue2()
{
    assert(count > 0);
    int data;
    if (!B.empty()) {
        data = B.top();
        B.pop();
    } else {
        while (A.size() > 1) {
            B.push(A.top());
            A.pop();
        }
        data = A.top();
        A.pop();
    }
    count -= 1;
    return data;
}

int main()
{
    Queue q;
    for (int i = 0; i < 30; i++) {
        q.enqueue2(i);
    }
    while (q.size() > 0) {
        cout << q.dequeue1() << endl;
    }
    return 0;
}