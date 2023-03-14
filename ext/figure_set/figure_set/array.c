//************************************
//  array.c
//************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ruby.h>
#include "figure_set.h"

static void
search_and_get_array_at_leaf(leaf_node leaf, VALUE array)
{
  unsigned long i = 0;
  unsigned long x;

  x = leaf->data;

  while(x) {
    i = BIT_COUNT((x & (-x))-1);
    rb_ary_push(array, ULONG2NUM(leaf->offset + i));
    x = x ^ (1UL << i);
  }
}

static void
search_and_get_array(branch_node branch, VALUE array)
{
  unsigned int i, count;

  if (branch->children_type == CT_LEAF) {
    for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH || count < branch->children_size; i++) {
      if (branch->index[i]) {
        search_and_get_array_at_leaf((leaf_node)branch->index[i], array);
        count++;
      }
    }
  } else {
    for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH || count < branch->children_size; i++) {
      if (branch->index[i]) {
        search_and_get_array((branch_node)branch->index[i], array);
        count++;
      }
    }
  }
}

//
// bit count
//

// 32 bit
unsigned long
bit32_count(unsigned long x)
{
  x = x - ((x >> 1UL) & 0x55555555UL);
  x = (x & 0x33333333UL) + ((x >> 2UL) & 0x33333333UL);
  x = (x + (x >> 4UL)) & 0x0f0f0f0fUL;
  x = x + (x >> 8UL);
  x = x + (x >> 16UL);
  return x & 0x0000003FUL;
}

// 64 bit
unsigned long
bit64_count(unsigned long x)
{
  x = x - ((x >> 1UL) & 0x5555555555555555UL);
  x = (x & 0x3333333333333333UL) + ((x >> 2UL) & 0x3333333333333333UL);
  x = (x & 0x0f0f0f0f0f0f0f0fUL) + ((x >> 4UL) & 0x0f0f0f0f0f0f0f0fUL);
  x = (x + (x >> 8UL)) & 0x00ff00ff00ff00ffUL;
  x = x + (x >> 16UL);
  x = x + (x >> 32UL);
  return x & 0x000000000000007FUL;
}

//
// output Array object from internal set
//
void
to_array(root_node root, VALUE array)
{
  unsigned int i, count;

  for(i = 0, count = 0; i < MAX_CHILDREN_SIZE_OF_ROOT_NODE || count < root->children_size; i++) {
    if (root->index[i]) {
      search_and_get_array((branch_node)root->index[i], array);
      count++;
    }
  }
}
