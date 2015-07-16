/**
 *
 *  双链表（带哨兵元素）和不带哨兵元素的版本的实现
 *
 */

#include "double-list.h"

// 带哨兵元素的实现
GuardDList::GuardDList()
{
    NIL = (node*)calloc(1, sizeof(node));
    NIL->next = NIL;
    NIL->pre = NIL;
}

GuardDList::GuardDList(int ls[], int length)
{
    NIL = (node*)calloc(1, sizeof(node));
    NIL->next = NIL;
    NIL->pre = NIL;
    for (int i = length - 1; i >= 0; i--) {
        node *it = (node*)calloc(1, sizeof(node));
        it->data = ls[i];
        insert(it);
    }
}

void GuardDList::insert(node *it)
{
    it->next = NIL->next;
    it->pre = NIL;
    NIL->next->pre = it;
    NIL->next = it;
}

void GuardDList::remove(node *it)
{
    it->pre->next = it->next;
    it->next->pre = it->pre;
    free(it);
}

node* GuardDList::search(int data)
{
    node *it = NIL->next;
    while (it != NIL) {
        if (it->data == data) {
            return it;
        }
        it = it->next;
    }
    return NULL;
}

void GuardDList::print()
{
    node *it = NIL->next;
    while (it != NIL) {
        cout << it->data << " ";
        it = it->next;
    }
    cout << endl;
}

GuardDList::~GuardDList()
{
    node *it = NIL->next;
    while (it != NIL) {
        node *tmp = it;
        it = it->next;
        free(tmp);
    }
    free(NIL);
}

// 不带哨兵元素的实现
DoubleList::DoubleList()
{
    HEAD = NULL;
}

DoubleList::DoubleList(int ls[], int length)
{
    HEAD = NULL;
    for (int i = length - 1; i >= 0; i--) {
        node *it = (node*)calloc(1, sizeof(node));
        it->data = ls[i];
        insert(it);
    }
}

void DoubleList::insert(node *it)
{
    if (!HEAD) {
        HEAD = it;
        return;
    }
    it->next = HEAD;
    HEAD->pre = it;
    HEAD = it;
}

node* DoubleList::search(int data)
{
    node *it = HEAD;
    while (it) {
        if (it->data == data) {
            return it;
        }
        it = it->next;
    }
    return NULL;
}

void DoubleList::remove(node *it)
{
    if (it == HEAD) {
        HEAD = HEAD->next;
        HEAD->pre = NULL;
        free(it);
        return;
    }
    it->pre->next = it->next;
    it->next->pre = it->pre;
    free(it);
}

void DoubleList::print()
{
    node *it = HEAD;
    while (it) {
        cout << it->data << " ";
        it = it->next;
    }
    cout << endl;
}

DoubleList::~DoubleList()
{
    node *it = HEAD;
    while (it) {
        node *tmp = it;
        it = it->next;
        free(tmp);
    }
}