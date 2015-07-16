/**
* 循环链表
* 
* 问题描述：
* 已知n个人围坐在圆桌周围，从编号为k的人开始报数
* 数到m的那个人出列；他的下一个人又从k开始报数，
* 数到m的人出列；重复下去直到圆桌周围的人全部出列
*
*/
#include "single-list.h"

void func(int n, int k, int m)
{
    node *HEAD = NULL;
    node *it = NULL;
    // 初始化链表
    for (int i = 1; i <= n; i++) {
        it = (node*)calloc(1, sizeof(node));
        it->data = n + 1 - i;
        it->next = HEAD;
        HEAD = it;
    }
    // 卷绕
    it = HEAD;
    while (it->next) {
        it = it->next;
    }
    it->next = HEAD;
    // 取得位置K的指针
    it = HEAD;
    for (int i = 0; i < k - 1; i++) {
        it = it->next;
    }
    // 序列输出
    while (it->next != it) {
        for (int i = 0; i < m - 2; it = it->next, i += 1);
        node *tmp = it->next;
        it->next = it->next->next;
        cout << tmp->data << endl;
        free(tmp);
        it = it->next;
    }
    cout << it->data << endl;
}