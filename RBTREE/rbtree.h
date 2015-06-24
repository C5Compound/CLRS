#pragma once
/**
* 红黑树实现
* 不显示指定继承方式，则默认为私有继承
*/
#include <stdlib.h>
#include <gvc.h>
using namespace std;

enum COLOR{ black, red };

struct node
{
public:
    int key;
    int data;
    COLOR color;
    node *left, *right, *parent;

};


class RBTREE
{
private:
    // 释放数所占用的内存
    void freeTree(node*);
public:
    // 哨兵元素
    static node *NIL;
    node *ROOT;
    RBTREE();
    ~RBTREE();
    // 用数组初始化一棵树
    RBTREE(int*, int);
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
    // 左旋
    void leftRotate(node*);
    // 右旋
    void rightRotate(node*);
    // 插入元素保持性质
    void insertFixup(node*);
    // 删除元素保持性质
    void deleteFixup(node*);
    // 把数输出成图片
    void printTree(Agraph_t *graph, Agnode_t *pre, node *root);
    /**
     * 红黑树连接操作,满足 key[A] < key[x] < key[B]
     * 13章 练习13-2
     */
    static void linkedIn(RBTREE &A, node* x, RBTREE &B);
    // 取得黑高
    int getBlackHeight();
};