/* Figure 10.13, page 184
 this is the header file for the case study polymorphic tree library
describes data structures and functions for a library of tree manipulation routines */


/* declare node_t type that is used to manage the tree, including the two pointers required
by the tree structure, and a third data pointer of type void* that is used to indicate the
type-anonymous record stored at this node of the tree */
typedef struct node node_t;

struct node {
    void *data;         /* pointer to stored structures */
    node_t *left;       /* left subtree of node */
    node_t *right;      /* right subtree of node */
};


/* define tree_t type that includes a pointer to the root of a whole tree, and a function pointer
cmp that is used to store the comparison function in use in this particular instance of the tree */
typedef struct {
    node_t *root;                   /* root node of the tree */
    int (*cmp)(void*, void*);       /* function pointer */
} tree_t;

/* prototypes for the function in this library */

tree_t *make_empty_tree(int func(void*, void*));
int is_empty_tree(tree_t *tree);
void *search_tree(tree_t *tree, void *key);
tree_t *insert_in_order(tree_t *tree, void *value);
void traverse_tree(tree_t *tree, void action(void*));
void free_tree(tree_t *tree);


/* This is a header file to facilitate the use as a separately compiled module. */
