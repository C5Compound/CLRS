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
    // �������б�ͷ
    void insert(node*);
    // �Ƴ�ĳ���ڵ�
    bool removeAt(node*);
    // �ͷ�������ڴ�ռ�
    void demolish(node*);
    void reverse_iter();
    node* reverse_recur(node*);
public:
    List();
    List(int*, int);
    ~List();
    void reverse();
    void print();
    // Ѱ�������м�Ԫ��,ż����Ԫ���򷵻�����
    pair<node*, int> search4center();
};