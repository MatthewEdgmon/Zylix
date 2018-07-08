/**
 * tree.c - Tree implementation.
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
