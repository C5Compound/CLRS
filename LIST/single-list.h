#pragma once
#include <cstdlib>
#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;

} ;

class List
{
private:
    node *HEAD;
    // 插入在列表头
    void insert(node*);
    // 移除某个节点
    bool removeAt(node*);
    // 释放链表的内存空间
    void demolish(node*);
    void reverse_iter();
    node* reverse_recur(node*);
public:
    List();
    List(int*, int);
    ~List();
    void reverse();
    void print();
    // 寻找链表中间元素,偶数个元素则返回两个
    pair<node*, int> search4center();
};