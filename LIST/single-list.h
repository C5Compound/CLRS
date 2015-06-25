#pragma once
#include <stdlib.h>
#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;

} ;

class List
{
    node *HEAD;
    void insert();
    void add(node*);
    void remove();
    void demolish(node *head);
    void reverse_iter();
    node* reverse_recur(node*);
public:
    List(int*, int);
    ~List();
    void reverse();
    void print();
};