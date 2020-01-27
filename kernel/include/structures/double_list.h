/**
 * list.h - Doubly linked list implementation.
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

#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__

#include <stdint.h>
#include <stddef.h>

typedef struct double_list_node {
    struct double_list_node* next;
    struct double_list_node* prev;
    void* value;
    void* owner;
} __attribute__((__packed__)) double_list_node_t;

typedef struct double_list {
    double_list_node_t* head;
    double_list_node_t* tail;
    size_t length;
} __attribute__((__packed__)) double_list_t;

double_list_t* DoubleListCreate();
double_list_t* DoubleListCopy(double_list_t* original);
void DoubleListDestroy(double_list_t* list);
void DoubleListDestroyNode(double_list_t* list, double_list_node_t* node);
void DoubleListDestroyIndex(double_list_t* list, size_t index);
void DoubleListDestroyAllNodes(double_list_t* list);
void DoubleListInsertNode(double_list_t* list, double_list_node_t* node, size_t index);
void DoubleListInsertValue(double_list_t* list, void* value, size_t index);
void DoubleListAppendNode(double_list_t* list, double_list_node_t* node);
void DoubleListPrependNode(double_list_t* list, double_list_node_t* node);
void DoubleListAppendValue(double_list_t* list, void* value);
void DoubleListPrependValue(double_list_t* list, void* value);
double_list_node_t* DoubleListSearchNode(double_list_t* list, void* value);
int DoubleListSearchIndex(double_list_t* list, void* value);
double_list_t* DoubleListMerge(double_list_t* source, double_list_t* destination);
void DoubleListOutputStructure(double_list_t* list);

#define foreach(i, list) for (double_list_node_t* i = (list)->head; i != NULL; i = i->next)
#define foreach_reverse(i, list) for (double_list_node_t* i = (list)->tail; i != NULL; i = i->prev)

#endif /* __DOUBLE_LIST_H__ */
