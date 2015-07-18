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

// �������ʼ��һ����
node* tree_build(int ls[], int length, int i = 1);
// ��ͼ�εķ�ʽ���һ����
void tree_print(Agraph_t *graph, Agnode_t *pre, node *root);
// �Ƚ��������ǲ�����ͬ
bool tree_compare(node *ra, node *rb);
// �ͷ�����ռ�ڴ�
void tree_free(node *root);
// ����������
node* tree_mirror(node *root);