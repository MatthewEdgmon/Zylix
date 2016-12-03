#ifndef __LIST_H__
#define __LIST_H__

typedef struct list_node {
    struct list_node* next;
    struct list_node* prev;
    void* value;
    void* owner;
} __attribute__((__packed__)) list_node_t;

typedef struct list {
    list_node_t* head;
    list_node_t* tail;
    size_t length;
} __attribute__((__packed__)) list_t;

list_t* ListCreate();
list_t* ListCopy(list_t* original);

void ListDestroy(list_t* list);
void ListDestroyNode(list_t* list, list_node_t* node);
void ListDestroyIndex(list_t* list, size_t index);
void ListDestroyAllNodes(list_t* list);
void ListInsertNode(list_t* list, list_node_t* node, size_t index);
void ListInsertValue(list_t* list, void* value, size_t index);
void ListAppendNode(list_t* list, list_node_t* node);
void ListPrependNode(list_t* list, list_node_t* node);
void ListAppendValue(list_t* list, void* value);
void ListPrependValue(list_t* list, void* value);
list_node_t* ListSearchNode(list_t* list, void* value);
int ListSearchIndex(list_t* list, void* value);
void ListMerge(list_t* source, list_t* destination);
void ListOutputStructure(list_t* list);

#define foreach(i, list) for (list_node_t* i = (list)->head; i != NULL; i = i->next)
#define foreach_reverse(i, list) for (list_node_t* i = (list)->tail; i != NULL; i = i->prev)

#endif /* __LIST_H__ */
