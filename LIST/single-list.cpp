/**
*
* ������ʵ�ּ�����
*
*/
#include "single-list.h"

List::List()
{
    HEAD = NULL;
}

List::List(int ls[], int length)
{
    HEAD = NULL;
    for (int i = 0; i < length; i++) {
        node *it = (node*)calloc(1, sizeof(node));
        it->data = ls[i];
        insert(it);
    }
}

List::~List()
{
    demolish(HEAD);
}

void List::insert(node *it)
{
    it->next = HEAD;
    HEAD = it;
}

bool List::removeAt(node *it)
{
    // ��������
    if (!HEAD) {
        return false;
    }
    // ɾ��ͷ��Ԫ��
    if (it == HEAD) {
        HEAD = HEAD->next;
        free(it);
        return true;
    }
    node *head = HEAD;
    while (head->next && head->next != it) {
        head = head->next;
    }
    // �޴˽ڵ�
    if (!head->next) {
        return false;
    }
    head->next = head->next->next;
    free(it);
    return true;
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

    while (current->next) {
        current->next = pre;
        pre = current;
        current = current->next;
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


// ���м�Ԫ��
pair<node*, int> List::search4center()
{
    // ������
    if (!HEAD) {
        return make_pair((node*)NULL, 0);
    }
    node *slow = HEAD;
    node *fast = HEAD;
    while (fast->next) {
        fast = fast->next->next;
        // Ԫ������Ϊ˫��
        if (!fast) {
            return make_pair(slow, 2);
        }
        slow = slow->next;
    }
    // ����
    return make_pair(slow, 1);
}