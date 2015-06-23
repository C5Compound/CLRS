#pragma once
#include <stdlib.h>
#include <gvc.h>
using namespace std;

typedef struct node
{
public:
    int key;
    int data;
    node *left, *right, *parent;

} node;

/**
*���������ʵ��
*/
class TREE
{
private:
    // �ͷ�����ռ�õ��ڴ�
    void freeTree(node*);

public:
    node *ROOT;
    TREE();
    // �������ʼ��һ����
    TREE(int*, int);
    ~TREE();
    // ������Ӧ�ؼ��ֵĽڵ�
    node* searchTree(int);
    // �������ؼ��ֽڵ�
    node* maxNode(node*);
    // ������С�ؼ��ֽڵ�
    node* minNode(node*);
    // ���غ�̽ڵ�
    node* successor(node*);
    // ����ǰ���ڵ�
    node* predecessor(node*);
    // ɾ���ڵ�
    void deleteNode(node*);
    // ����ڵ�
    void insertNode(node*);
    // ���������ͼƬ
    void printTree(Agraph_t*, Agnode_t*, node*);
};
