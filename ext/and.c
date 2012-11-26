//************************************
//  and.c
//************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ruby.h>
#include "figure_set.h"

//
// intersection
//
void intersection(root_node result_set, root_node set0, root_node set1)
{
    unsigned int i, count;
    root_node base, other;
    branch_node branch;

    if (set0->size == 0 || set1->size == 0) {
        return;
    } else if (set0->size > set1->size) {
        base = set1;
        other = set0;
    } else {
        base = set0;
        other = set1;
    }

    for (i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_ROOT_NODE || count < base->children_size; i++) {
        if (base->index[i]) {
            count++;
            if (other->index[i]) {
                branch = (branch_node)init_and_intersection_branch_node(result_set, (branch_node)base->index[i], (branch_node)other->index[i]);
                if (branch) {
                    result_set->index[i] = (void*)branch;
                    result_set->children_size++;
                }
            }
        }
    }
}

void *init_and_intersection_branch_node(root_node result_set, branch_node base, branch_node other)
{
    branch_node branch;

    branch = (branch_node)init_branch_node();

    if (base->children_type == CT_LEAF) {
        last_intersection_branch_node(result_set, branch, base, other);
    } else {
        middel_intersection_branch_node(result_set, branch, base, other);
    }

    if (branch->children_size) {
        branch->children_type = base->children_type;
        return (void*)branch;
    } else {
        destroy_branch(branch);
        return (void*)NULL;
    }
}

void middel_intersection_branch_node(root_node result_set, branch_node branch, branch_node base, branch_node other)
{
    unsigned int i, count;
    branch_node middle_branch;

    for (i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH || count < base->children_size; i++) {
        if (base->index[i]) {
            count++;
            if (other->index[i]) {
                middle_branch = (branch_node)init_and_intersection_branch_node(result_set, (branch_node)base->index[i], (branch_node)other->index[i]);
                if (middle_branch) {
                    branch->index[i] = (void*)middle_branch;
                    branch->children_size++;
                }
            }
        }
    }
}

void last_intersection_branch_node(root_node result_set, branch_node branch, branch_node base, branch_node other)
{
    unsigned int i, count;
    leaf_node leaf;

    for (i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH || count < base->children_size; i++) {
        if (base->index[i]) {
            count++;
            if (other->index[i]) {
                leaf = (leaf_node)init_and_intersection_leaf_node(result_set, (leaf_node)base->index[i], (leaf_node)other->index[i]);
                if (leaf) {
                    branch->index[i] = (void*)leaf;
                    branch->children_size++;
                }
            }
        }
    }
}


void *init_and_intersection_leaf_node(root_node result_set, leaf_node base, leaf_node other)
{
    unsigned long data;
    leaf_node leaf;
    
    data = base->data & other->data;

    if (!data) return (void*)NULL;

    leaf = (leaf_node)init_leaf_node(base->offset);
    leaf->data = data;
    result_set->size += BIT_COUNT(leaf->data);

    return (void*)leaf;
}
