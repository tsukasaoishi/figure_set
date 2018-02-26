//************************************
// method.c
//************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ruby.h>
#include <time.h>
#include "figure_set.h"

//-----------------------------------------------------------
// Ruby Methods
// ----------------------------------------------------------

/**
 * allocate
**/
static VALUE t_allocate(VALUE klass)
{
    VALUE obj;
    root_node root;

    obj = Data_Make_Struct(klass, struct _root_node, NULL, destroy_all, root);
    init_root_node(root);

    return obj;
}

/**
 * initialize
**/
static VALUE t_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE ary_element;
    root_node root;
    unsigned long i, len;

    Data_Get_Struct(self, struct _root_node, root);

    if (argc == 1 && TYPE(argv[0]) == T_ARRAY) {
        len = RARRAY_LEN(argv[0]);
        for(i = 0; i < len; i++) {
            ary_element = rb_ary_entry(argv[0], i);
            if ((TYPE(ary_element) == T_FIXNUM) && VALID_MIN_VALUE <= ary_element && VALID_MAX_VALUE >= ary_element) {
                add_num(root, NUM2ULONG(ary_element));
            }
        }
    }

    return self;
}

/**
 * initialize_copy
**/
static VALUE t_initialize_copy(VALUE self, VALUE orig)
{
    root_node root, orig_set;

    Data_Get_Struct(self, struct _root_node, root);
    Data_Get_Struct(orig, struct _root_node, orig_set);
    copy_root_node(root, orig_set);

    return self;
}

/**
 * add
**/
static VALUE t_add(VALUE self, VALUE value)
{
    root_node root;

    if (TYPE(value) != T_FIXNUM) return self;
    if (VALID_MIN_VALUE > value || VALID_MAX_VALUE < value) return self;

    Data_Get_Struct(self, struct _root_node, root);
    add_num(root, NUM2ULONG(value));

    return self;
}

/**
 * delete
 **/
static VALUE t_delete(VALUE self, VALUE value)
{
    root_node root;

    if (TYPE(value) != T_FIXNUM) return self;
    if (VALID_MIN_VALUE > value || VALID_MAX_VALUE < value) return self;

    Data_Get_Struct(self, struct _root_node, root);
    delete_num(root, NUM2ULONG(value));

    return self;
}

/**
 * intersection
**/
static VALUE t_intersection(VALUE self, VALUE other)
{
    VALUE obj;
    root_node result_set, set0, set1;

    obj = Data_Make_Struct(rb_cFigureSet, struct _root_node, NULL, destroy_all, result_set);
    init_root_node(result_set);

    Data_Get_Struct(self, struct _root_node, set0);
    Data_Get_Struct(other, struct _root_node, set1);

    intersection(result_set, set0, set1);

    return obj;
}

/**
 * union
**/
static VALUE t_union(VALUE self, VALUE other)
{
    VALUE obj;
    root_node result_set, set0, set1;

    obj = Data_Make_Struct(rb_cFigureSet, struct _root_node, NULL, destroy_all, result_set);
    init_root_node(result_set);

    Data_Get_Struct(self, struct _root_node, set0);
    Data_Get_Struct(other, struct _root_node, set1);

    join(result_set, set0, set1);

    return obj;
}

/**
 * to_a
**/ 
static VALUE t_to_a(VALUE self)
{
    root_node root;
    VALUE array;

    Data_Get_Struct(self, struct _root_node, root);
    array = rb_ary_new2(root->size);

    to_array(root, array);

    return array;
}

/**
 * sample
**/ 
static VALUE t_sample(int argc, VALUE *argv, VALUE self)
{
    root_node root;
    VALUE array;
    unsigned long sample_count = 1UL;

    Data_Get_Struct(self, struct _root_node, root);

    if (argc == 1 && TYPE(argv[0]) == T_FIXNUM) {
        sample_count = NUM2ULONG(argv[0]);
        if (sample_count < 1UL || sample_count > root->size) sample_count = 1UL;
    }

    array = rb_ary_new2(sample_count);
    if (sample_count == root->size) {
        to_array(root, array);
    } else if (root->size) {
        sample(root, array, sample_count);
    }

    return array;
}

/**
 * size
**/
static VALUE t_size(VALUE self)
{
    root_node root;

    Data_Get_Struct(self, struct _root_node, root);

    return ULONG2NUM(root->size);
}

/**
 * empty?
**/
static VALUE t_empty(VALUE self)
{
    root_node root;

    Data_Get_Struct(self, struct _root_node, root);

    if (root->size == 0) {
        return Qtrue;
    } else {
        return Qfalse;
    }
}

/**
 * cler
**/
static VALUE t_clear(VALUE self)
{
    root_node root;

    Data_Get_Struct(self, struct _root_node, root);

    if (root->size) {
        destroy_all_branches(root);
    }

    return self;
}


/**
 * define class
**/
void Init_figure_set(void) {
    rb_cFigureSet = rb_define_class("FigureSet", rb_cObject);
    rb_define_alloc_func(rb_cFigureSet, t_allocate);
    rb_define_private_method(rb_cFigureSet, "initialize", t_initialize, -1);
    rb_define_method(rb_cFigureSet, "initialize_copy", t_initialize_copy, 1);
    rb_define_method(rb_cFigureSet, "add", t_add, 1);
    rb_define_method(rb_cFigureSet, "delete", t_delete, 1);
    rb_define_method(rb_cFigureSet, "intersection", t_intersection, 1);
    rb_define_method(rb_cFigureSet, "union", t_union, 1);
    rb_define_method(rb_cFigureSet, "to_a", t_to_a, 0);
    rb_define_method(rb_cFigureSet, "sample", t_sample, -1);
    rb_define_method(rb_cFigureSet, "size", t_size, 0);
    rb_define_method(rb_cFigureSet, "empty?", t_empty, 0);
    rb_define_method(rb_cFigureSet, "clear", t_clear, 0);
    rb_define_alias(rb_cFigureSet, "<<", "add");
    rb_define_alias(rb_cFigureSet, "&", "intersection");
    rb_define_alias(rb_cFigureSet, "|", "union");
    rb_define_alias(rb_cFigureSet, "length", "size");

    // for sample method
    srand((unsigned) time(NULL));
}
