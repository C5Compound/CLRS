/**
 *  基于Trie的词频统计
 */
#define ALPHABET 26
struct node
{
    int count;
    node *next[ALPHABET];
    node() : count(0) { memset(next, 0, ALPHABET * sizeof(node*)); }
};

node* trieInitial()
{
    return new node();
}

void trieInsert(node *trie, const char *src)
{
    if (src == NULL) {
        return;
    }
    if (*src == '\0') {
        ++trie->count;
        return;
    }
    if (trie->next[*src - 'a'] == NULL) {
        trie->next[*src - 'a'] = new node();
    }
    trieInsert(trie->next[*src - 'a'], src + 1);
}

node* trieFind(node *trie, const char *src)
{
    if (src == NULL ) {
        return NULL;
    }
    if (*src == '\0' || trie == NULL) {
        return trie;
    }
    return trieFind(trie->next[*src - 'a'], src + 1);
}

void trieFree(node *trie) {
    if (trie == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET; ++i) {
        trieFree(trie->next[i]);
    }
    delete trie;
}

void trieDelete(node *trie, const char *src)
{
    node *toDel = trieFind(trie, src);
    if (toDel == NULL) {
        return;
    }
    toDel->count = max(0, toDel->count - 1);
}
// 先序遍历
void trieTravel(node *trie, string path)
{
    if (trie->count > 0) {
        printf("COUNT:%d   %s\n", trie->count, path.c_str());
    }
    for (int i = 0; i < ALPHABET; ++i) {
        if (trie->next[i] != NULL) {
            trieTravel(trie->next[i], path + (char)(i + 'a'));
        }
    }
}