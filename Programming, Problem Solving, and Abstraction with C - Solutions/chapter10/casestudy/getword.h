/* Figure 10.14, 10.15, 10.16, page 184, 185, 186
 this is a library of functions for binary search tree manipulation */


/*-----------------------------------------------------------------------------*/
/* start 10.14 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include "treeops.h"

/* a new tree is created using make_empty_tree, which must be passed a pointer
to the comparison function to be used in all subsequent operations on this tree

The handle passed back to the calling program (main program) is a pointer to The
tree_t structure created by make_empty_tree, and all subsequent acces to the tree
is via that handle. */
tree_t
*make_empty_tree(int func(void*, void*)) {
    tree_t *tree;
    tree = malloc(sizeof(*tree));
    assert(tree != NULL);
    /* initialize tree to empty */
    tree -> root = NULL;
    /* and save the supplied function pointer */
    tree -> cmp = func;
    return tree;
}

int
is_empty_tree(tree_t *tree) {
    assert(tree != NULL);
    return (tree -> root == NULL);
}



/*----------------------------------------------------------------------------*/
/* Add two further operations to the library:
    -searching a tree for an object, using the comparison function to determine the search path at each node
    - and then an insertion routine that adds a new object to an existing tree
as always the comparison function returns a negative value if the first argument
is smaller; zero if the two arguments are equal; and positive if second argument is smaller.

-Both the searching and insertion functions work with a pointer of type void* to the data object
involved, rather than the data object itself. This change is necessary if the structure is to be polymorphic (like what i did in my ass1 to populate arrays)

-Searching and Insertion both make use of an auxiliary recursive functions that step down the levels of the tree.
This is a common structure for tree functions - a public routine presents an interface to the calling program
and sets up some initial values, and then a private recursive function is used to trace the linked data structure.
    -The argument to the public routines is a pointer to a tree_t while the argument to each of the corresponding private routines
    is a pointer to a node_t, a type not used by the main function.

-TO ENSURE THAT THE PRIVATE ROUTINES ARE ONLY ACCESSIBLE FROM WITHIN THIS MODULE USED: static (can only be used in current C source file)


*/
/* start 10.15 */
static void
*recursive_search_tree(node_t *root, void *key, int cmp(void*, void*)) {
    int outcome;

    if (!root) {
        return NULL;
    }

    if ((outcome=cmp(key, root->data)) < 0) {
        return recursive_search_tree(root -> left, key, cmp);
    }

    else if (outcome >0) {
        return recursive_search_tree(root -> right, key, cmp);
    }

    else {
        /* must have found it */
        return root -> data;
    }
}

/* returns a pointer to the tree node sorting object "key", if it exists, otherwise
returns a NULL pointer. ALLOWING THE CALLING PROGRAM TO RE-ACCESS A RECORD IT HAD EARLIER INSERTED*/
void
*search_tree(tree_t *tree, void *key) {
    assert(tree != NULL);
    return recursive_search_tree(tree -> root, key, tree -> cmp);
}


static node_t
*recursive_insert(node_t *root, node_t *new, int cmp(void*, void*)) {
    if (root == NULL) {
        return new;
    }

    else if (cmp(new -> data, root -> data) < 0) {
        root -> left = recursive_insert(root -> left, new, cmp);
    }

    else {
        root -> right = recursive_insert(root -> right, new, cmp);
    }

    return root;
}

/* returns a pointer to an altered tree that now includes the object "value" in
its correct location. WHICH MUST BE ASSIGNED IN THE CALLING FUNCTION IF THE CHANGES TO THE TREE ARE TO BE PROPERLY RECORDED */
tree_t
*insert_in_order(tree_t *tree, void *value) {
    node_t *new;
    /* make the new node */
    new = malloc(sizeof(*new));
    assert(tree != NULL && new != NULL);
    new -> data = value;
    new -> left = new -> right = NULL;
    /* and insert it into the tree */
    tree -> root = recursive_insert(tree -> root, new, tree -> cmp);

    return tree;
}






/*----------------------------------------------------------------------------*/
/*
In a TRAVERSAL every node in the tree is visited and some transformation applied, or output generated.
In the case of a binary search tree, a traversal is again best accomplished recursively,
first of all:
    -traversing the left subtree, then processing the data associated with this node
    -then traversing the right subtree
This in order visitation sequence means that the stored data items are processed in sorted order according
to the cmp function used to build the tree (e.g: IF EACH DATA OBJECT IS PRINTED AS IT IS VISITED THEN THE OUTPUT IS IN SORTED ORDER)

*/
/* start 10.16 */
static void
recursive_traverse(node_t *root, void action(void*)) {
    if (root) {
        recursive_traverse(root -> left, action);
        action(root -> data);
        recursive_traverse(root -> right, action);
    }
}

/* Applies the "action" at every node in the tree, in the order determined by
the cmp function */
void
traverse_tree(tree_t *tree, void action(void*)) {
    assert(tree != NULL);
    recursive_traverse(tree -> root, action);
}

static void
recursive_free_tree(node_t *root) {
    if (root) {
        recursive_free_tree(root -> left);
        recursive_free_tree(root -> right);
        free(root);
    }
}


/* Traverses the tree and Release all memory space associated with the tree structure
Nodes are visited in post-order traversal rather than in-order, since both subtrees
must be deallocated before this root node can be relinquished*/
/* NOTE:
        this function does not and should not release space consumed by the data items themselves,
        since the tree library did not allocate that space in the first instance*/
void
free_tree(tree_t *tree) {
    assert(tree != NULL);
    recursive_free_tree(tree -> root);
    free(tree);
}
