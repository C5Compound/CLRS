/**
 *  双链表的两种实现
 */
#pragma once

#include <cstdlib>
#include <iostream>
using namespace std;

struct node
{
    int data;
    node *pre;
    node *next;
};

// 带哨兵的双链表
class GuardDList
{
private:
    node *NIL;
public:
    void insert(node*);
    void remove(node*);
    void print();
    node* search(int);
    GuardDList();
    GuardDList(int[], int);
    ~GuardDList();
};

// 不带哨兵的双链表
class DoubleList
{
private:
    node* HEAD;
public:
    void insert(node*);
    void remove(node*);
    void print();
    node* search(int);
    DoubleList();
    DoubleList(int[], int);
    ~DoubleList();
};