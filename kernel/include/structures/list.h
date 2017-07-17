/**
 * list.h - Linked list implementation.
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

#ifndef __LIST_H__
#define __LIST_H__

#include <stdint.h>
#include <stddef.h>

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
list_t* ListMerge(list_t* source, list_t* destination);
void ListOutputStructure(list_t* list);

#define foreach(i, list) for (list_node_t* i = (list)->head; i != NULL; i = i->next)
#define foreach_reverse(i, list) for (list_node_t* i = (list)->tail; i != NULL; i = i->prev)

#endif /* __LIST_H__ */
