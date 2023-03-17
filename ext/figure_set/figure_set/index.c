//************************************
//  index.c
//************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ruby.h>
#include "figure_set.h"

static unsigned int search_and_insert(branch_node, unsigned long, unsigned long, unsigned long);
static unsigned int search_and_insert_at_leaf(leaf_node, unsigned long);
static unsigned int search_and_remove(branch_node, unsigned long, unsigned long, unsigned long);
static unsigned int search_and_remove_at_leaf(leaf_node, unsigned long);


static unsigned int
search_and_insert(branch_node branch, unsigned long level, unsigned long value, unsigned long original)
{
  unsigned long quotient, remainder;

  quotient = value / OFFSET_SCALE[level];
  remainder = value % OFFSET_SCALE[level];

  if(!(branch->index[quotient])) {
    if(branch->children_type == CT_LEAF) {
      branch->index[quotient] = init_leaf_node((unsigned long)(original / ULONG_BIT_COUNT) * ULONG_BIT_COUNT);
    } else {
      branch->index[quotient] = init_branch_node();
      if ((level + 1) == LAST_BRANCH_LEVEL) {
        ((branch_node)(branch->index[quotient]))->children_type = CT_LEAF;
      }
    }
    branch->children_size++;
  }

  if (branch->children_type == CT_LEAF) {
    return search_and_insert_at_leaf((leaf_node)branch->index[quotient], remainder);
  } else {
    return search_and_insert((branch_node)branch->index[quotient], level + 1, remainder, original);
  }
}

static unsigned int
search_and_insert_at_leaf(leaf_node leaf, unsigned long value)
{
  unsigned int exist_flag = 0;
  unsigned long target_bit;

  target_bit = 1UL << value;

  if (!(leaf->data & target_bit)) {
    leaf->data |= target_bit;
    exist_flag = 1;
  }

  return exist_flag;
}

static unsigned int
search_and_remove(branch_node branch, unsigned long level, unsigned long value, unsigned long original)
{
  unsigned long quotient, remainder;

  quotient = value / OFFSET_SCALE[level];
  remainder = value % OFFSET_SCALE[level];

  if (!(branch->index[quotient])) return 0;

  if (branch->children_type == CT_LEAF) {
    return search_and_remove_at_leaf((leaf_node)branch->index[quotient], remainder);
  } else {
    return search_and_remove((branch_node)branch->index[quotient], level + 1, remainder, original);
  }
}

static unsigned int
search_and_remove_at_leaf(leaf_node leaf, unsigned long value)
{
  unsigned int exist_flag = 0;
  unsigned long target_bit;

  target_bit = 1UL << value; 

  if ((leaf->data & target_bit)) {
    leaf->data ^= target_bit;
    exist_flag = 1;
  }

  return exist_flag;
}

//
// insert element into set
//
void
add_num(root_node root, unsigned long value)
{
  unsigned long quotient, remainder;

  quotient = value / OFFSET_SCALE[0];
  remainder = value % OFFSET_SCALE[0];

  if(!(root->index[quotient])) {
    root->index[quotient] = init_branch_node();
    root->children_size++;
  }

  if (search_and_insert((branch_node)root->index[quotient], 1, remainder, value)) {
    root->size++;
  }
}

//
// remove element from set
//
void
delete_num(root_node root, unsigned long value)
{
  unsigned long quotient, remainder;

  quotient = value / OFFSET_SCALE[0];
  remainder = value % OFFSET_SCALE[0];

  if (!(root->index[quotient])) return;

  if (search_and_remove((branch_node)root->index[quotient], 1, remainder, value)) {
    root->size--;
  }
}
