/**
*
* 单链表实现及置逆
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
    // 空链表返回
    if (!HEAD) {
        return false;
    }
    // 删除头部元素
    if (it == HEAD) {
        HEAD = HEAD->next;
        free(it);
        return true;
    }
    node *head = HEAD;
    while (head->next && head->next != it) {
        head = head->next;
    }
    // 无此节点
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

// 递归版本
node* List::reverse_recur(node *head)
{
    // 空链表返回
    if (!head) {
        return NULL;
    }
    if (!head->next) {
        HEAD = head;
        return head;
    }
    node *it = reverse_recur(head->next);
    it->next = head;
    head->next = NULL;    // 不加此句会产生循环链表错误
    return head;
}

// 迭代版本
// 迭代版本更好理解
void List::reverse_iter()
{
    // 链表元素少于两个则返回
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

// 输出链表
void List::print()
{
    node *it = HEAD;
    while (it) {
        cout << it->data << "  ";
        it = it->next;
    }
    cout << endl;
}


// 找中间元素
pair<node*, int> List::search4center()
{
    // 空链表
    if (!HEAD) {
        return make_pair((node*)NULL, 0);
    }
    node *slow = HEAD;
    node *fast = HEAD;
    while (fast->next) {
        fast = fast->next->next;
        // 元素总数为双数
        if (!fast) {
            return make_pair(slow, 2);
        }
        slow = slow->next;
    }
    // 单数
    return make_pair(slow, 1);
}