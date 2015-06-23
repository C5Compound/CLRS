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
*二叉查找树实现
*/
class TREE
{
private:
    // 释放数所占用的内存
    void freeTree(node*);

public:
    node *ROOT;
    TREE();
    // 用数组初始化一棵树
    TREE(int*, int);
    ~TREE();
    // 返回相应关键字的节点
    node* searchTree(int);
    // 返回最大关键字节点
    node* maxNode(node*);
    // 返回最小关键字节点
    node* minNode(node*);
    // 返回后继节点
    node* successor(node*);
    // 返回前驱节点
    node* predecessor(node*);
    // 删除节点
    void deleteNode(node*);
    // 插入节点
    void insertNode(node*);
    // 把数输出成图片
    void printTree(Agraph_t*, Agnode_t*, node*);
};
