//************************************
//  figure_set.h
//
//  Tsukasa OISHI
//  http://www.kaeruspoon.net
//************************************

#include <math.h>

// max children size of branch
#define MAX_CHILDREN_SIZE_OF_BRANCH (unsigned long)16
#define LAST_BRANCH_LEVEL (unsigned long)6

#if ULLONG_MAX == 0xffffffffffffffff
#define ULONG_BIT_COUNT (unsigned long)64
#define MAX_CHILDREN_SIZE_OF_ROOT_NODE (unsigned long)4
#define BIT_COUNT(x) bit64_count(x)
static unsigned long OFFSET_SCALE[] = {0x40000000, 0x4000000, 0x400000, 0x40000, 0x4000, 0x400, 0x40};
#else
#define ULONG_BIT_COUNT (unsigned long)32
#define MAX_CHILDREN_SIZE_OF_ROOT_NODE (unsigned long)8
#define BIT_COUNT(x) bit32_count(x)
static unsigned long OFFSET_SCALE[] = {0x20000000, 0x2000000, 0x200000, 0x20000, 0x2000, 0x200, 0x20};
#endif

// branch node children type
#define CT_BRANCH 0
#define CT_LEAF 1

// valid valie range
#define VALID_MIN_VALUE UINT2NUM(0)
#define VALID_MAX_VALUE UINT2NUM(0xffffffff)

// leaf node
// example:
//   data = 5  # (bit is 0...0101) exist bit numbers is (2, 0) 
//   offset = 640
// 
// set is
//  [offset + 2, offset + 0]
//   = [642, 640]
//  
typedef struct _leaf_node {
    unsigned long offset;   // offset number
    unsigned long data;  // each bit is exist flag(1:exist 0:none) of member
} *leaf_node;

// branch node
typedef struct _branch_node {
    unsigned char children_type; // children type
    unsigned char children_size;
    void *index[MAX_CHILDREN_SIZE_OF_BRANCH];  // children pointer
} *branch_node;

typedef struct _root_node {
    unsigned char children_size;
    unsigned long size;              // number of elements in set
    void *index[MAX_CHILDREN_SIZE_OF_ROOT_NODE];    // children pointer
} *root_node;

// bit count
unsigned long bit32_count(unsigned long);
unsigned long bit64_count(unsigned long);

// initialize
void init_root_node(root_node);
branch_node init_branch_node();
leaf_node init_leaf_node(unsigned long);

// init_copy
void copy_root_node(root_node, root_node);
branch_node init_and_copy_brance_node(root_node, branch_node);
leaf_node init_and_copy_leaf_node(root_node, leaf_node);

// memory free
void destroy_all(root_node);
void destroy_all_branches(root_node);
void destroy_branch(branch_node);

// insert element into set
void add_num(root_node, unsigned long);

// remove element from set
void delete_num(root_node, unsigned long);

// output Array object from internal set
void to_array(root_node, VALUE);

// join
void join(root_node, root_node, root_node);

// intersection
void intersection(root_node, root_node, root_node);

// sample
void sample(root_node, VALUE, unsigned long);
