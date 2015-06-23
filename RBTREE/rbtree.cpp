#include "rbtree.h"

RBTREE::RBTREE()
{
    NIL = (node*)malloc(sizeof(node));
    memset(NIL, 0, sizeof(node));
    NIL->color = black;
    ROOT = NIL;
}

RBTREE::~RBTREE()
{
    freeTree(ROOT);
    free(NIL);
}

RBTREE::RBTREE(int list[], int length)
{
    NIL = (node*)malloc(sizeof(node));
    memset(NIL, 0, sizeof(node));
    NIL->color = black;
    ROOT = NIL;
    for (int i = 0; i < length; i++) {
        node *it = (node*)malloc(sizeof(node));
        memset(it, 0, sizeof(node));
        it->key = list[i];
        insertNode(it);
    }
}

void RBTREE::insertNode(node *it)
{
    node *root = ROOT;
    node *parent = NIL;
    while (root != NIL) {
        parent = root;
        if (it->key >= root->key) {
            root = root->right;
        }
        else {
            root = root->left;
        }
    }
    it->parent = parent;
    if (parent == NIL) {
        ROOT = it;
    }
    else {
        if (it->key >= parent->key) {
            parent->right = it;
        }
        else {
            parent->left = it;
        }
    }
    it->left = NIL;
    it->right = NIL;
    it->color = red;
    insertFixup(it);
}

node* RBTREE::searchTree(int key)
{
    node *root = ROOT;
    while (root != NIL) {
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

void RBTREE::freeTree(node *root)
{
    if (root == NIL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

node* RBTREE::maxNode(node *root)
{
    while (root->right != NIL) {
        root = root->right;
    }
    return root;
}

node* RBTREE::minNode(node *root)
{
    while (root->left != NIL) {
        root = root->left;
    }
    return root;
}

node* RBTREE::successor(node *it)
{
    if (it->right != NIL) {
        return minNode(it->right);
    }
    while (it->parent != NIL && it == it->parent->right) {
        it = it->parent;
    }
    if (it->parent == NIL) {
        return NULL;
    }
    return it->parent;
}

node* RBTREE::predecessor(node *it)
{
    if (it->left != NIL) {
        return maxNode(it->left);
    }
    while (it->parent != NIL && it == it->parent->left) {
        it = it->parent;
    }
    if (it->parent == NIL) {
        return NULL;
    }
    return it->parent;
}

void RBTREE::deleteNode(node *it)
{
    node *forDelete = NULL;
    if (it->left == NIL || it->right == NIL) {
        forDelete = it;
    }
    else {
        forDelete = successor(it);
    }
    node *forCage = NULL;
    if (forDelete->left != NIL) {
        forCage = forDelete->left;
    }
    else {
        forCage = forDelete->right;
    }
    forCage->parent = forDelete->parent;
    if (forDelete->parent == NIL) {
        ROOT = forCage;
    }
    else if (forDelete == forDelete->parent->left) {
        forDelete->parent->left = forCage;
    }
    else {
        forDelete->parent->right = forCage;
    }
    if (it != forDelete) {
        it->key = forDelete->key;
    }
    if (forDelete->color == black) {
        deleteFixup(forCage);
    }
    free(forDelete);
}

void RBTREE::leftRotate(node *it)
{
    node *y = it->right;
    y->parent = it->parent;
    it->right = y->left;
    if (y->left != NIL) {
        y->left->parent = it;
    }
    y->left = it;
    if (it->parent != NIL) {
        if (it == it->parent->left) {
            it->parent->left = y;
        }
        else {
            it->parent->right = y;
        }
    }
    else {
        ROOT = y;
    }
    it->parent = y;
}

void RBTREE::rightRotate(node *it)
{
    node *y = it->left;
    y->parent = it->parent;
    it->left = y->right;
    if (y->right != NIL) {
        y->right->parent = it;
    }
    y->right = it;
    if (it->parent != NIL) {
        if (it == it->parent->left) {
            it->parent->left = y;
        }
        else {
            it->parent->right = y;
        }
    }
    else {
        ROOT = y;
    }
    it->parent = y;
}

void RBTREE::insertFixup(node *it)
{
    while (it->parent->color == red) {
        node *uncle = NULL;
        /**
        * 分为几种情况（隐含了it他爸是左节点和右节点两大类）
        * 1）叔叔是红色节点
        * 2）叔叔是黑节点，it为右孩子
        * 3）叔叔是黑节点，it为左孩子；情况二通过左旋变为情况三
        * 注：进入二三种情况后循环结束，此时树已经满足全部性质，叔叔不存在对应于黑节点nil
        */
        if (it->parent == it->parent->parent->left) {
            uncle = it->parent->parent->right;
            // case 1
            if (uncle->color == red) {
                uncle->color = black;
                it->parent->color = black;
                it = it->parent->parent;
                it->color = red;
                continue;
            }
            // case 2 to case 3
            if (it == it->parent->right) {
                it = it->parent;
                leftRotate(it);
            }
            // case 3
            it->parent->parent->color = red;
            it->parent->color = black;
            rightRotate(it->parent->parent);
        }
        else {
            uncle = it->parent->parent->left;
            // case 1
            if (uncle->color == red) {
                uncle->color = black;
                it->parent->color = black;
                it = it->parent->parent;
                it->color = red;
                continue;
            }
            // case 2 to case 3
            if (it == it->parent->left) {
                it = it->parent;
                rightRotate(it);
            }
            // case 3
            it->parent->parent->color = red;
            it->parent->color = black;
            leftRotate(it->parent->parent);
        }
    }
    ROOT->color = black;
}

void RBTREE::deleteFixup(node *it)
{
    while (it != ROOT && it->color == black) {
        node *brother = NULL;
        if (it == it->parent->left) {
            brother = it->parent->right;
            // transform case 1 to 2 3 or 4
            if (brother->color == red) {
                it->parent->color = red;
                brother->color = black;
                leftRotate(it->parent);
                brother = it->parent->right;
            }
            // case 2 then continue
            if (brother->left->color == black &&
                brother->right->color == black) {
                brother->color = red;
                it = it->parent;
                continue;
            }
            // case 3 to case 4
            if (brother->right->color == black) {
                brother->color = red;
                brother->left->color = black;
                rightRotate(brother);
                brother = it->parent->right;
            }
            // case 4 the end
            brother->color = it->parent->color;
            it->parent->color = black;
            brother->right->color = black;
            leftRotate(it->parent);
            break;
        }
        else {
            brother = it->parent->left;
            // transform case 1 to 2 3 or 4
            if (brother->color == red) {
                it->parent->color = red;
                brother->color = black;
                rightRotate(it->parent);
                brother = it->parent->left;
            }
            // case 2 then continue
            if (brother->left->color == black &&
                brother->right->color == black) {
                brother->color = red;
                it = it->parent;
                continue;
            }
            // case 3 to case 4
            if (brother->left->color == black) {
                brother->color = red;
                brother->right->color = black;
                leftRotate(brother);
                brother = it->parent->left;
            }
            // case 4 the end
            brother->color = it->parent->color;
            it->parent->color = black;
            brother->left->color = black;
            rightRotate(it->parent);
            break;
        }
    }
    it->color = black;
}

void RBTREE::printTree(Agraph_t *graph, Agnode_t *pre, node *root)
{
    if (root == NIL) {
        return;
    }
    Agnode_t *here;
    char buff[5] = { 0 };
    sprintf_s(buff, "%d", root->key);
    here = agnode(graph, buff, 1);
    // 颜色选项
    agsafeset(here, "color", (root->color == red ? "red" : "black"), "");
    if (pre) {
        agedge(graph, pre, here, 0, 1);
    }
    printTree(graph, here, root->left);
    printTree(graph, here, root->right);
}

RBTREE* RBTREE::linkedIn(RBTREE &A, node* x, RBTREE &B)
{
    return NULL;
}

int RBTREE::getBH(node *root)
{
    int height = 0;
    while (root != NIL) {
        height++;
        root = root->right;
    }
    return 0;
}