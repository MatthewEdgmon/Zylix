#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <structures/tree.h>
#include <structures/list.h>

/**
 * Create an empty tree structure with NO children.
 */
tree_t* TreeCreate() {
    tree_t* tree = malloc(sizeof(tree_t));
    tree->node_count = 0;
    tree->root_node = NULL;
    return tree;
}

/**
 * Returns an exact copy of the original.
 */
tree_t* TreeCopy(tree_t* original) {
    tree_t* copy = malloc(sizeof(tree_t));
    return copy;
}

void TreeSetRoot(tree_t* tree, void* value) {

}

void TreeAddNode(tree_t* tree) {

}

/**
 * Destroys the tree structure and all children.
 */
void TreeDestroy(tree_t* tree) {

}

/**
 * NOTE: The node to add the subtree to must have no children.
 */
void TreeAddSubtree(tree_t* base_tree, tree_t* subtree, tree_node_t* at) {

}

void TreeRemoveNode(tree_t* tree) {

}

/**
 * This removes all children of the specified node WITHOUT destryoing the node.
 */
void TreeRemoveSubtree(tree_t* tree, tree_node_t* at) {

}

/**
 * Returns how many children a specified node has.
 */
size_t TreeCountNodeChildren(tree_node_t* node) {
    if(!node)
        return 0;
    if(!node->children)
        return 0;
    size_t node_count = node->children->length;

    return node_count;
}

void TreeOutputStructure(tree_t* tree) {
    if(tree->root_node == NULL) {
        printf("Tree is empty.\n");
    }

    // Start by counting the childeren of the root node.
    for(size_t i = 0; i++; i <= TreeCountNodeChildren(tree->root_node)) {
        // By going in order and counting the "|" characters we have left to print,
        // we can just go in order of children and not worry about spacing for others.

    }
}
