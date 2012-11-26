//************************************
//  sample.c
//************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ruby.h>
#include "figure_set.h"

//
// output Array object from sample set
//
void sample(root_node root, VALUE array, unsigned long sample_count)
{
    unsigned int start_sample, sample_now, i, count, target_point;

    srand((unsigned) time(NULL));

    start_sample = RARRAY_LEN(array);

    for(sample_now = start_sample; sample_now < sample_count; sample_now++) {
        target_point = rand() % root->children_size;
        for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_ROOT_NODE || count < root->children_size; i++) {
            if (root->index[i]) {
                if (count == target_point) {
                    search_and_sample_array((branch_node)root->index[i], array);
                }
                count++;
            }
        }
    }

    if (RARRAY_LEN(array) < sample_count) {
        sample(root, array, sample_count);
    }

    rb_funcall(array, rb_intern("uniq!"), 0);
    if (RARRAY_LEN(array) < sample_count) {
        sample(root, array, sample_count);
    }
}

void search_and_sample_array(branch_node branch, VALUE array)
{
    unsigned int i, count, target_point;

    if (!branch->children_size) return;

    target_point = rand() % branch->children_size;

    for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH || count < branch->children_size; i++) {
        if (branch->index[i]) {
            if (count == target_point) {
                if (branch->children_type == CT_LEAF) {
                    search_and_sample_array_at_leaf((leaf_node)branch->index[i], array);
                } else {
                    search_and_sample_array((branch_node)branch->index[i], array);
                }
            }
            count++;
        }
    }
}

void search_and_sample_array_at_leaf(leaf_node leaf, VALUE array)
{
    unsigned long i = 0, hit_count = 0;
    unsigned long bit_count, target_point;
    unsigned long x;

    x = leaf->data;
    bit_count = BIT_COUNT(leaf->data);
    if (!bit_count) return;

    target_point = rand() % bit_count;

    while(x) {
        if (x & 1UL) {
            if (hit_count == target_point) {
                rb_ary_push(array, ULONG2NUM(leaf->offset + i));
            }
            hit_count++;
        }
        x = x >> 1UL;
        i++;
    }
}
