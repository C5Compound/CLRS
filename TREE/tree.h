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

node* tree_build(int ls[], int length, int i = 1);
void tree_print(Agraph_t *graph, Agnode_t *pre, node *root);
bool tree_compare(node *ra, node *rb);
void tree_free(node *root);
node* tree_mirror(node *root);