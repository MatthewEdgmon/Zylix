#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include <structures/list.h>

/**
 * Creates an empty list structure with NO nodes.
 */
list_t* ListCreate() {
    list_t* list = malloc(sizeof(list_t));
    list->length = 0;
    return list;
}

/**
 * Returns an exact copy of the original.
 */
list_t* ListCopy(list_t* original) {
    list_t* copy = malloc(sizeof(list_t));
    copy->length = original->length;
    return copy;
}

/**
 * Frees every node of the list, and the list structure itself.
 */
void ListDestroy(list_t* list) {
    ListDestroyAllNodes(list);
    free(list);
}

/**
 * Frees a specified node from a list.
 */
void ListDestroyNode(list_t* list, list_node_t* node_destroy) {
    foreach(node, list) {
        if(node == node_destroy) {
            // Tell each of the surronding nodes we're disappearing.
            node->prev->next = node->next;
            node->next->prev = node->prev;
            free(node->value);
            free(node);
        }
    }
}

/**
 * Frees a node at the index.
 */
void ListDestroyIndex(list_t* list, size_t index) {
    list_node_t* node_destroy = list->head;
    for(size_t i = 0; i <= list->length; i++) {
        node_destroy = node_destroy->next;
        if(i == index) {
            // Tell each of the surronding nodes we're disappearing.
            node_destroy->prev->next = node_destroy->next;
            node_destroy->next->prev = node_destroy->prev;
            free(node_destroy->value);
            free(node_destroy);
        }
    }
}

/**
 * Frees all the nodes in a list, but not the structure.
 */
void ListDestroyAllNodes(list_t* list) {
    // Free the values.
    foreach(node, list) {
        free(node->value);
    }
    // Free the nodes themselves.
    list_node_t* this_node = list->head;
    while(this_node) {
        list_node_t* next_node = this_node->next;
        free(this_node);
        this_node = next_node;
    }
}

/**
 * Puts a node at index.
 */
void ListInsertNode(list_t* list, list_node_t* node, size_t index) {

}

/**
 * Creates new node with value at index.
 */
void ListInsertValue(list_t* list, void* value, size_t index) {

}

/**
 * Adds a node to the end of the list.
 */
void ListAppendNode(list_t* list, list_node_t* node) {
    if(node->prev || node->next) {
        printf("Tried to append a node to a list but it already belongs to one.\n");
    }
    node->owner = list;
    // If the list is empty, this is the new head.
    if(!list->length) {
        node->prev = NULL;
        node->next = NULL;
        list->head = node;
        list->tail = node;
        list->length++;
    } else {
        node->prev = list->tail;
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
        list->length++;
    }
}

/**
 * Adds a node to the start of a list.
 */
void ListPrependNode(list_t* list, list_node_t* node) {
    if(node->prev || node->next) {
        printf("Tried to append a node to a list but it already belongs to one.\n");
    }
    node->owner = list;
    // If the list is empty, this is the new head.
    if(!list->length) {
        node->prev = NULL;
        node->next = NULL;
        list->head = node;
        list->tail = node;
        list->length++;
    } else {
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
        list->length++;
    }
}

/**
 * Adds a new node with the specified value to the end of the list.
 */
void ListAppendValue(list_t* list, void* value) {
    list_node_t* new_node = malloc(sizeof(list_node_t));
    new_node->value = value;
    new_node->owner = list;
    // If the list is empty, this is the new head.
    if(!list->length) {
        new_node->prev = NULL;
        new_node->next = NULL;
        list->head = new_node;
        list->tail = new_node;
        list->length++;
    } else {
        new_node->prev = list->tail;
        new_node->next = NULL;
        list->tail->next = new_node;
        list->tail = new_node;
        list->length++;
    }
}

/**
 * Adds a new node with the specified value to the start of the list.
 */
void ListPrependValue(list_t* list, void* value) {
    list_node_t* new_node = malloc(sizeof(list_node_t));
    new_node->value = value;
    new_node->owner = list;
    // If the list is empty, this is the new head.
    if(!list->length) {
        new_node->prev = NULL;
        new_node->next = NULL;
        list->head = new_node;
        list->tail = new_node;
        list->length++;
    } else {
        new_node->prev = NULL;
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
        list->length++;
    }
}

/**
 * Returns the first node in the list which contains the specified value.
 */
list_node_t* ListSearchNode(list_t* list, void* value) {
    foreach(node, list) {
        if(node->value == value) {
            return node;
        }
    }
    return NULL;
}

/**
 * Returns the first index of the specified value.
 */
int ListSearchIndex(list_t* list, void* value) {
    int index = 0;
    foreach(node, list) {
        if(node->value == value) {
            return index;
        }
        index++;
    }
    // Not found.
    return -1;
}

/**
 * Moves the souce list to the end of the destination list, source is not saved.
 */
void ListMerge(list_t* source, list_t* destination) {
    // First set the owner for each node to the new list.
    foreach(node, source) {
        node->owner = destination;
    }
    // Then set the head node of the source list as the tail node of the target.
    if(source->head) {
        source->head = destination->tail;
    }
    // The length of the list is now both lengths added.
    destination->length += source->length;
    // Your services are no longer required.
    free(source);
}

void ListOutputStructure(list_t* list) {
    printf("Printing List Structure. %d Elements.\n", list->length);
    foreach(node, list) {
        printf(" %d ->", node->value);
    }
    printf("\n");
}
