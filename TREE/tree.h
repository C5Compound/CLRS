#pragma once
#include <cstdlib>
#include <gvc.h>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;
};

// 用数组初始化一棵树
node* tree_build(int ls[], int length, int i = 1);
// 以图形的方式输出一棵树
void tree_print(Agraph_t *graph, Agnode_t *pre, node *root);
// 比较两棵树是不是相同
bool tree_compare(node *ra, node *rb);
// 释放树所占内存
void tree_free(node *root);
// 对树作镜像
node* tree_mirror(node *root);