/**
* ѭ������
* 
* ����������
* ��֪n����Χ����Բ����Χ���ӱ��Ϊk���˿�ʼ����
* ����m���Ǹ��˳��У�������һ�����ִ�k��ʼ������
* ����m���˳��У��ظ���ȥֱ��Բ����Χ����ȫ������
*
*/
#include "single-list.h"

void func(int n, int k, int m)
{
    node *HEAD = NULL;
    node *it = NULL;
    // ��ʼ������
    for (int i = 1; i <= n; i++) {
        it = (node*)calloc(1, sizeof(node));
        it->data = n + 1 - i;
        it->next = HEAD;
        HEAD = it;
    }
    // ����
    it = HEAD;
    while (it->next) {
        it = it->next;
    }
    it->next = HEAD;
    // ȡ��λ��K��ָ��
    it = HEAD;
    for (int i = 0; i < k - 1; i++) {
        it = it->next;
    }
    // �������
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