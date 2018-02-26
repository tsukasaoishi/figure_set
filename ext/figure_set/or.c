//************************************
//  or.c
//************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ruby.h>
#include "figure_set.h"

static leaf_node init_and_join_leaf_node(root_node, leaf_node, leaf_node);
static branch_node init_and_join_brance_node(root_node, branch_node, branch_node);
static void last_join_branch_node(root_node, branch_node, branch_node, branch_node);
static void middle_join_branch_node(root_node, branch_node, branch_node, branch_node);

//
// join
//
void
join(root_node result_set, root_node set0, root_node set1)
{
  unsigned int i;

  if (set0->size == 0 && set1->size == 0) {
    return;
  } else if (set0->size == 0) {
    copy_root_node(result_set, set1);
    return;
  } else if (set1->size == 0) {
    copy_root_node(result_set, set0);
    return;
  }

  for (i = 0; i < MAX_CHILDREN_SIZE_OF_ROOT_NODE; i++) {
    if (set0->index[i] && set1->index[i]) {
      result_set->index[i] = init_and_join_brance_node(result_set, (branch_node)set0->index[i], (branch_node)set1->index[i]);
      result_set->children_size++;
    } else if(set0->index[i]) {
      result_set->index[i] = init_and_copy_brance_node(result_set, (branch_node)set0->index[i]);
      result_set->children_size++;
    } else if (set1->index[i]) {
      result_set->index[i] = init_and_copy_brance_node(result_set, (branch_node)set1->index[i]);
      result_set->children_size++;
    }
  }
}

static branch_node
init_and_join_brance_node(root_node result_set, branch_node set0, branch_node set1)
{
  branch_node branch;

  branch = (branch_node)init_branch_node();

  if (set0->children_type == CT_LEAF) {
    branch->children_type = CT_LEAF;
    last_join_branch_node(result_set, branch, set0, set1);
  } else {
    middle_join_branch_node(result_set, branch, set0, set1);
  }

  return branch;
}

static void
middle_join_branch_node(root_node result_set, branch_node branch, branch_node set0, branch_node set1)
{
  unsigned int i;

  for (i = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH; i++) {
    if (set0->index[i] && set1->index[i]) {
      branch->index[i] = init_and_join_brance_node(result_set, (branch_node)set0->index[i], (branch_node)set1->index[i]);
      branch->children_size++;
    } else if (set0->index[i]) {
      branch->index[i] = init_and_copy_brance_node(result_set, (branch_node)set0->index[i]);
      branch->children_size++;
    } else if (set1->index[i]) {
      branch->index[i] = init_and_copy_brance_node(result_set, (branch_node)set1->index[i]);
      branch->children_size++;
    }
  }
}

static void
last_join_branch_node(root_node result_set, branch_node branch, branch_node set0, branch_node set1)
{
  unsigned int i;

  for (i = 0; i < MAX_CHILDREN_SIZE_OF_BRANCH; i++) {
    if (set0->index[i] && set1->index[i]) {
      branch->index[i] = init_and_join_leaf_node(result_set, (leaf_node)set0->index[i], (leaf_node)set1->index[i]);
      branch->children_size++;
    } else if (set0->index[i]) {
      branch->index[i] = init_and_copy_leaf_node(result_set, (leaf_node)set0->index[i]);
      branch->children_size++;
    } else if (set1->index[i]) {
      branch->index[i] = init_and_copy_leaf_node(result_set, (leaf_node)set1->index[i]);
      branch->children_size++;
    }
  }
}

static leaf_node
init_and_join_leaf_node(root_node result_set, leaf_node set0, leaf_node set1)
{
  leaf_node leaf;

  leaf = (leaf_node)init_leaf_node(set0->offset);

  leaf->data = set0->data | set1->data;
  result_set->size += BIT_COUNT(leaf->data);

  return leaf;
}
