/**
 *  两树的比较，镜像也算作一致
 */
#include "tree.h"

bool tree_compare(node *ra, node *rb)
{
    if (ra == NULL && rb == NULL) {
        return true;
    }
    if (ra == NULL || rb == NULL) {
        return false;
    }
    if (ra->data = rb->data) {
        return (tree_compare(ra->left, rb->left) && tree_compare(ra->right, rb->right)) ||
            (tree_compare(ra->left, rb->right) && tree_compare(ra->right, rb->left));
    }
    return false;
}