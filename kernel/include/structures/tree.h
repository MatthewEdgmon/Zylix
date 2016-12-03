#ifndef __TREE_H__
#define __TREE_H__

#include <structures/list.h>

typedef struct tree_node {
    void* value;
    list_t* children;
    struct tree_node* parent;
} tree_node_t;

typedef struct tree {
    size_t node_count;
    tree_node_t* root_node;
} tree_t;

tree_t* TreeCreate();
tree_t* TreeCopy(tree_t* original);
void TreeSetRoot(tree_t* tree, void* value);
void TreeDestroy();

void TreeOutputStructure(tree_t* tree);

#endif /* __TREE_H__ */
