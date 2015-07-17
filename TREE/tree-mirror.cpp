#include "tree.h"

// 用数组建立树，从索引为1的位置开始
node* tree_build(int ls[], int length, int i)
{
    if (i > length - 1) {
        return NULL;
    }
    node* root = (node*)malloc(sizeof(node));
    root->data = ls[i];
    root->left = tree_build(ls, length, 2 * i);
    root->right = tree_build(ls, length, 2 * i + 1);
    return root;
}

void tree_free(node *root)
{
    if (root == NULL) {
        return;
    }
    tree_free(root->left);
    tree_free(root->right);
    free(root);
}

node* tree_mirror(node *root)
{
    if (root == NULL) {
        return NULL;
    }
    node *it = (node*)malloc(sizeof(node));
    it->left = tree_mirror(root->right);
    it->right = tree_mirror(root->left);
    return it;
}

void tree_print(Agraph_t *graph, Agnode_t *pre, node *root)
{
    if (root == NULL) {
        return;
    }
    Agnode_t *here;
    char buff[6] = { 0 };
    sprintf_s(buff, "%d", root->data);
    here = agnode(graph, buff, 1);
    // 颜色选项
    agsafeset(here, "color", "green", "");
    if (pre) {
        agedge(graph, pre, here, 0, 1);
    }
    tree_print(graph, here, root->left);
    tree_print(graph, here, root->right);
}