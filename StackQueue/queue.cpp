/**
 *  单链表、双链表和数组三种队列实现
 */

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

struct node
{
    int data;
    node *next;
};

class ListQueue
{
private:
    node *HEAD;
    size_t count;
public:
    ListQueue();
    ~ListQueue();
    void enqueue(int);
    int dequeue();
    size_t Count();
};

ListQueue::ListQueue() : HEAD(NULL), count(0)
{
}

ListQueue::~ListQueue()
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

void ListQueue::enqueue(int data)
{
    node *it = (node*)calloc(1, sizeof(node));
    it->data = data;
    it->next = HEAD;
    HEAD = it;
    count += 1;
}

int ListQueue::dequeue()
{
    assert(count > 0);
    int data;
    if (count == 1) {
        data = HEAD->data;
        free(HEAD);
        HEAD = NULL;
    } else {
        node *it = HEAD;
        while (it->next->next != NULL) {
            it = it->next;
        }
        data = it->next->data;
        free(it->next);
        it->next = NULL;
    }
    count -= 1;
    return data;
}

size_t ListQueue::Count()
{
    return count;
}


struct dnode
{
    int data;
    dnode *pre;
    dnode *next;
};

class DListQueue
{
private:
    dnode* HEAD;
    dnode* TAIL;
    size_t count;
public:
    DListQueue();
    ~DListQueue();
    size_t Count();
    void enqueue(int);
    int dequeue();
};

DListQueue::DListQueue() : HEAD(NULL), TAIL(NULL), count(0)
{
}

DListQueue::~DListQueue()
{
    dnode *it = HEAD;
    while (it != NULL) {
        dnode* tmp = it;
        it = it->next;
        free(tmp);
    }
}

size_t DListQueue::Count()
{
    return count;
}

void DListQueue::enqueue(int data)
{
    dnode *it = (dnode*)calloc(1, sizeof(dnode));
    it->data = data;
    it->next = HEAD;
    it->pre = NULL;
    if (count == 0) {
        HEAD = TAIL = it;
    }
    else {
        HEAD->pre = it;
        HEAD = it;
    }
    count += 1;
}

int DListQueue::dequeue()
{
    assert(count > 0);
    int data = TAIL->data;
    if (count == 1) {
        free(TAIL);
        HEAD = TAIL = NULL;
    } else {
        TAIL->pre->next = NULL;
        dnode *tmp = TAIL;
        TAIL = TAIL->pre;
        free(tmp);
    }
    count -= 1;
    return data;
}

#define QUEUE_MAX 1024

class ArrayQueue
{
private:
    int buf[QUEUE_MAX];
    int head;
    int tail;
    size_t count;
public:
    ArrayQueue();
    ~ArrayQueue();
    void enqueue(int);
    int dequeue();
    size_t Count();
};

ArrayQueue::ArrayQueue() : head(0), tail(0), count(0)
{
    memset(buf, 0, QUEUE_MAX * sizeof(int));
}

ArrayQueue::~ArrayQueue()
{
}

void ArrayQueue::enqueue(int data)
{
    assert(count < QUEUE_MAX);
    buf[head] = data;
    head = (head == QUEUE_MAX - 1) ? 0 : head + 1;
    count += 1;
}

int ArrayQueue::dequeue()
{
    assert(count > 0);
    int data = buf[tail];
    tail = (tail == QUEUE_MAX - 1) ? 0 : tail + 1;
    count -= 1;
    return data;
}

size_t ArrayQueue::Count()
{
    return count;
}

int main()
{
    ListQueue lq;
    for (int i = 0; i < 30; i++) {
        lq.enqueue(i);
    }
    while (lq.Count() > 0) {
        cout << lq.dequeue() << endl;
    }
    return 0;
}