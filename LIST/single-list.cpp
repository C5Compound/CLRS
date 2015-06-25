/**
*
* ������ʵ�ּ�����
*
*/
#include "single-list.h"

List::List(int ls[], int length)
{
    HEAD = NULL;
    for (int i = 0; i < length; i++) {
        node *it = (node*)calloc(1, sizeof(node));
        it->data = ls[i];
        add(it);
    }
}

List::~List()
{
    demolish(HEAD);
}

void List::add(node *it)
{
    it->next = HEAD;
    HEAD = it;
}

void List::demolish(node *head)
{
    if (head->next) {
        demolish(head->next);
        free(head);
    }
}

void List::reverse()
{
    reverse_recur(HEAD);
}

// �ݹ�汾
node* List::reverse_recur(node *head)
{
    // ��������
    if (!head) {
        return NULL;
    }
    if (!head->next) {
        HEAD = head;
        return head;
    }
    node *it = reverse_recur(head->next);
    it->next = head;
    head->next = NULL;    // ���Ӵ˾�����ѭ���������
    return head;
}

// �����汾
// �����汾�������
void List::reverse_iter()
{
    // ����Ԫ�����������򷵻�
    if (!HEAD || !HEAD->next) {
        return;
    }

    node *pre = NULL;
    node *current = HEAD;
    node *next = current->next;

    while (next) {
        current->next = pre;
        pre = current;
        current = next;
        next = next->next;
    }
    current->next = pre;
    HEAD = current;
}

// �������
void List::print()
{
    node *it = HEAD;
    while (it) {
        cout << it->data << "  ";
        it = it->next;
    }
    cout << endl;
}
