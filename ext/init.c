//************************************
//  init.c
//************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ruby.h>
#include "figure_set.h"

//
// initialize
//
void init_root_node(root_node root)
{
    unsigned int i;

    for(i = 0; i < MAX_CHILDREN_SIZE_OF_ROOT_NODE; i++) {
        root->index[i] = (void*)NULL;
    }
    root->size = 0;
    root->children_size = 0;
}

void *init_branch_node()
{
    unsigned int i;
    branch_node branch;

    if (!(branch = (branch_node)malloc(sizeof(struct _branch_node)))) {
        rb_raise(rb_eStandardError, "memory is not enough");
    }

    for(i = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH; i++) {
        branch->index[i] = (void*)NULL;
    }

    branch->children_size = 0;
    branch->children_type = CT_BRANCH;

    return (void*)branch;
}

void *init_leaf_node(unsigned long offset)
{
    leaf_node leaf;

    if(!(leaf = (leaf_node)malloc(sizeof(struct _leaf_node)))) {
        rb_raise(rb_eStandardError, "memory is not enough");
    }

    leaf->offset = offset;
    leaf->data = 0;

    return (void*)leaf;
}

//
// initialize copy
//
void copy_root_node(root_node root, root_node orig)
{
    unsigned int i, count;

    root->children_size = orig->children_size;

    for (i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_ROOT_NODE || count < orig->children_size; i++) {
        if (orig->index[i]) {
            root->index[i] = init_and_copy_brance_node(root, (branch_node)orig->index[i]);
            count++;
        }
    }
}

void copy_branch_node(root_node root, branch_node branch, branch_node orig)
{
    unsigned int i, count;

    branch->children_type = orig->children_type;
    branch->children_size = orig->children_size;

    if (orig->children_type == CT_LEAF) {
        for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH || count < orig->children_size; i++) {
            if (orig->index[i]) {
                branch->index[i] = init_and_copy_leaf_node(root, (leaf_node)orig->index[i]);
                count++;
            }
        }
    } else {
        for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH || count < orig->children_size; i++) {
            if (orig->index[i]) {
                branch->index[i] = init_and_copy_brance_node(root, (branch_node)orig->index[i]);
                count++;
            }
        }
    }
}

void *init_and_copy_brance_node(root_node root, branch_node orig)
{
    branch_node branch;

    branch = (branch_node)init_branch_node();
    copy_branch_node(root, branch, orig);

    return (void*)branch;
}

void *init_and_copy_leaf_node(root_node root, leaf_node orig)
{
    leaf_node leaf;

    leaf = (leaf_node)init_leaf_node(orig->offset);
    leaf->data = orig->data;
    root->size += BIT_COUNT(leaf->data);

    return (void*)leaf;
}

//
// memory free
//
void destroy_all(root_node root)
{
    destroy_all_branches(root);
    free(root);
}

void destroy_all_branches(root_node root)
{
    unsigned int i, count;
    
    for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_ROOT_NODE || count < root->children_size; i++) {
        if (root->index[i]) {
            destroy_branch((branch_node)root->index[i]);
            root->index[i] = (void*)NULL;
            count++;
        }
    }

    root->size = 0;
    root->children_size = 0;
}

void destroy_branch(branch_node branch)
{
    unsigned int i, count;

    if (branch->children_type == CT_LEAF) {
        for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH || count < branch->children_size; i++) {
            if (branch->index[i]) {
                free((leaf_node)branch->index[i]);
                branch->index[i] = (void*)NULL;
                count++;
            }
        }
    } else {
        for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH || count < branch->children_size; i++) {
            if (branch->index[i]) {
                destroy_branch((branch_node)branch->index[i]);
                branch->index[i] = (void*)NULL;
                count++;
            }
        }
    }
    free(branch);
}
