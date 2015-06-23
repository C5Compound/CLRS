#include "bstree.h"

TREE::TREE()
{
    ROOT = NULL;
}

TREE::TREE(int list[], int length)
{
    for (int i = 0; i < length; i++) {
        node *it = (node*)malloc(sizeof(node));
        memset(it, 0, sizeof(node));
        it->key = list[i];
        insertNode(it);
    }
}

TREE::~TREE()
{
    freeTree(ROOT);
}

node* TREE::searchTree(int key)
{
    node *root = ROOT;
    while (root) {
        if (key == root->key) {
            return root;
        }
        else if (key > root->key) {
            root = root->right;
        }
        else {
            root = root->left;
        }
    }
    return NULL;
}

void TREE::freeTree(node *root)
{
    if (!root) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

node* TREE::maxNode(node *root)
{
    while (root->right) {
        root = root->right;
    }
    return root;
}

node* TREE::minNode(node *root)
{
    while (root->left) {
        root = root->left;
    }
    return root;
}

node* TREE::successor(node *it)
{
    if (it->right) {
        return minNode(it->right);
    }
    while (it->parent && it == it->parent->right) {
        it = it->parent;
    }
    if (!it->parent) {
        return NULL;
    }
    return it->parent;
}

node* TREE::predecessor(node *it)
{
    if (it->left) {
        return maxNode(it->left);
    }
    while (it->parent && it == it->parent->left) {
        it = it->parent;
    }
    if (!it->parent) {
        return NULL;
    }
    return it->parent;
}

void TREE::insertNode(node *it)
{
    node *root = ROOT;
    if (!root) {
        ROOT = it;
        return;
    }
    node *parent = NULL;
    while (root) {
        parent = root;
        if (it->key >= root->key) {
            root = root->right;
        }
        else {
            root = root->left;
        }
    }
    it->parent = parent;
    if (it->key >= parent->key) {
        parent->right = it;
    }
    else {
        parent->left = it;
    }
}

void TREE::deleteNode(node *it)
{
    node *forDelete = NULL;
    /**
    * 根据节点左右孩子的数目决定要删除的节点，
    * 只有一个孩子则删除此节点，有两个孩子则删除后继节点
    * 如果节点有两个孩子，它的后继一定没有左孩子
    * MIN { 节点的孩子数, 后继节点的孩子数 } <= 1
    */
    if (!it->left || !it->right) {
        forDelete = it;
    }
    else {
        forDelete = successor(it);
    }
    /**
    * forCage保存待删节点的指针信息
    */
    node *forCage = NULL;
    if (forDelete->left) {
        forCage = forDelete->left;
    }
    else {
        forCage = forDelete->right;
    }
    if (forCage) {
        forCage->parent = forDelete->parent;
    }
    // 处理根节点的情况
    if (!forDelete->parent) {
        ROOT = forCage;
    }
    // 非根节点，更新其父节点指向新的节点
    else if (forDelete == forDelete->parent->left) {
        forDelete->parent->left = forCage;
    }
    else {
        forDelete->parent->right = forCage;
    }
    // 如果删除的是后继节点，则交换key
    if (forDelete != it) {
        it->key = forDelete->key;
        // 卫星数据转移
    }
    free(forDelete);
}

void TREE::printTree(Agraph_t *graph, Agnode_t *pre, node *root)
{
    if (!root) {
        return;
    }
    Agnode_t *here;
    char buff[5] = { 0 };
    sprintf_s(buff, "%d", root->key);
    here = agnode(graph, buff, 1);
    if (pre) {
        agedge(graph, pre, here, 0, 1);
    }
    printTree(graph, here, root->left);
    printTree(graph, here, root->right);
}