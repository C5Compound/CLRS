/**
 *  ˫���������ʵ��
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

// ���ڱ���˫����
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

// �����ڱ���˫����
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