/**
 * list.c - Linked list implementation.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <structures/double_list.h>

/**
 * Creates an empty list structure with NO nodes.
 */
double_list_t* DoubleListCreate() {
    double_list_t* list = malloc(sizeof(double_list_t));
    list->length = 0;
    return list;
}

/**
 * Returns an exact copy of the original.
 */
double_list_t* DoubleListCopy(double_list_t* original) {
    double_list_t* copy = malloc(sizeof(double_list_t));
    copy->length = original->length;
    return copy;
}

/**
 * Frees every node of the list, and the list structure itself.
 */
void DoubleListDestroy(double_list_t* list) {
    DoubleListDestroyAllNodes(list);
    free(list);
}

/**
 * Frees a specified node from a list.
 */
void DoubleListDestroyNode(double_list_t* list, double_list_node_t* node_destroy) {
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
void DoubleListDestroyIndex(double_list_t* list, size_t index) {
    double_list_node_t* node_destroy = list->head;
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
void DoubleListDestroyAllNodes(double_list_t* list) {
    // Free the values.
    foreach(node, list) {
        free(node->value);
    }
    // Free the nodes themselves.
    double_list_node_t* this_node = list->head;
    while(this_node) {
        double_list_node_t* next_node = this_node->next;
        free(this_node);
        this_node = next_node;
    }
}

/**
 * Puts a node at index, descending from the head. Current node at index
 */
void DoubleListInsertNode(double_list_t* list, double_list_node_t* node, size_t index) {

    /* User just wants to set a new head node. */
    if(index == 0) {
        DoubleListAppendNode(list, node);
    }

    if(index >= list->length) {
        printf("[LIST] Tried to insert node at index %d, but list is only of size %d.\n", index, list->length);
        return;
    }

    /* Create a working node. */
    double_list_node_t* current = list->head;

    for(size_t i = 0; i < index; i++) {
        /* Check if there is a next node. */
        if(current->next == NULL) {
            printf("[LIST] Tried to insert node at index %d, but following list found NULL node.\n", index);
            return;
        }

        /* Set the current working node to the next node in the list. */
        current = current->next;

    }
}

/**
 * Creates new node with value at index, descending from the head.
 */
void DoubleListInsertValue(double_list_t* list, void* value, size_t index) {
    double_list_node_t* new_node;
    new_node->value = value;

    /* Use an existing function to do the hard work. */
    DoubleListInsertNode(list, new_node, index);
}

/**
 * Adds a node to the end of the list.
 */
void DoubleListAppendNode(double_list_t* list, double_list_node_t* node) {
    /* Check if this node already belongs to a list, if not, this list is it's owner. */
    if(node->owner != NULL) {
        printf("[LIST] Tried to append a node to a list but it already belongs to one.\n");
        return;
    } else {
        node->owner = list;
    }

    node->owner = list;

    /* If the list is empty, this is the new head. */
    if(list->length == 0) {
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
void DoubleListPrependNode(double_list_t* list, double_list_node_t* node) {
    /* Check if this node already belongs to a list, if not, this list is it's owner. */
    if(node->owner != NULL) {
        printf("[LIST] Tried to prepend a node to a list but it already belongs to one.\n");
        return;
    } else {
        node->owner = list;
    }

    /* If the list is empty, this is the new head. */
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
void DoubleListAppendValue(double_list_t* list, void* value) {
    double_list_node_t* new_node = malloc(sizeof(double_list_node_t));
    new_node->value = value;
    new_node->owner = list;
    DoubleListAppendNode(list, new_node);
}

/**
 * Adds a new node with the specified value to the start of the list.
 */
void DoubleListPrependValue(double_list_t* list, void* value) {
    double_list_node_t* new_node = malloc(sizeof(double_list_node_t));
    new_node->value = value;
    DoubleListPrependNode(list, new_node);
}

/**
 * Returns the first node in the list which contains the specified value.
 */
double_list_node_t* DoubleListSearchNode(double_list_t* list, void* value) {
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
int DoubleListSearchIndex(double_list_t* list, void* value) {
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
 * Creates a new list from two different lists, the "source" list is put on the
 * end of the "destination" list. Neither list's original structure is saved.
 */
double_list_t* DoubleListMerge(double_list_t* source, double_list_t* destination) {
    double_list_t* merged_list = DoubleListCreate();

    /* The length of the list is now both lengths added. */
    merged_list->length = destination->length + source->length;

    merged_list->head = destination->head;
    merged_list->tail = source->tail;

    foreach(node, destination) {
        node->owner = merged_list;

        /**
         * Once we reach the last node of destination, set it's next node to the
         * head node of source.
         */
        if(node->next == NULL) {
            node->next = source->head;
        }
    }

    foreach(node, source) {
        /* Tell the first node of source it's new prev is the tail of destination. */
        if(node->prev == NULL) {
            node->prev = destination->tail;
        }

        node->owner = merged_list;
    }

    /* The source lists are not saved. */
    DoubleListDestroy(source);
    DoubleListDestroy(destination);

    return merged_list;
}

void DoubleListOutputStructure(double_list_t* list) {
    printf("\nPrinting Double-List Structure. %d Elements.\n", list->length);
    foreach(node, list) {
        if(node == list->tail) {
            printf(" %d", node->value);
        } else {
            printf(" %d ->", node->value);
        }
    }
    printf("\n");
}
