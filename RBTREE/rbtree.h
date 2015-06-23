#pragma once
/**
* �����ʵ��
* ����ʾָ���̳з�ʽ����Ĭ��Ϊ˽�м̳�
*/
#include <stdlib.h>
#include <gvc.h>
using namespace std;

enum COLOR{ black, red };

typedef struct node
{
public:
    int key;
    int data;
    COLOR color;
    node *left, *right, *parent;

} node;

class RBTREE
{
private:
    // �ڱ�Ԫ��
    node *NIL;
    // �ͷ�����ռ�õ��ڴ�
    void freeTree(node*);
public:
    node *ROOT;
    RBTREE();
    ~RBTREE();
    // �������ʼ��һ����
    RBTREE(int*, int);
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
    // ����
    void leftRotate(node*);
    // ����
    void rightRotate(node*);
    // ����Ԫ�ر�������
    void insertFixup(node*);
    // ɾ��Ԫ�ر�������
    void deleteFixup(node*);
    // ���������ͼƬ
    void printTree(Agraph_t *graph, Agnode_t *pre, node *root);
    // ��������Ӳ���,���� A < x < B
    RBTREE* linkedIn(RBTREE &A, node* x, RBTREE &B);
    // ȡ�úڸ�
    int getBH(node*);
};