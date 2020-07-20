/*
Page187, 188
Use a binary search tree to count words, and print a sorted list of words
 and their frequencies


Main program that makes use of the tree library to perform the required processing.

-2 auxiliary functions are required
    -the first: compare_string_parts compares the word components of the two records passed
    -the second: print_then_free is used when the end of input is reached, at which time the
                contents of each of the data items is printed. Once a word and its frequency
                have been printed, that data is no longer required, so the space used by it can
                be released. Word at each node freed before the node itself.

*/



/*-----------------------------------------------------------------------------*/
/* start 10.17 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "treeops.h"
#include "getword.h"


/*------------------------------page 122 fig 7.14-----------------------------*/
#include <ctype.h>
#define MAXCHARS 10
#define MAXWORDS 1000 /* max distinc words  */
typedef char word_t[MAXCHARS + 1];
int getword(word_t W, int limit);
/*----------------------------------------------------------------------------*/


typedef struct {
    char *word;         /* pointer to a word */
    int freq;           /* frequency of that word */
} data_t;

int
compare_string_parts(void *x1, void *x2) {
    data_t *p1=x1, *p2=x2;
    return strcmp(p1->word, p2->word);
}

void
print_then_free(void *x) {
    data_t *p=x;
    printf("%4d %s\n", p->freq, p->word);
    free(p->word);
    free(p);
}


/*-----------------------------------------------------------------------------*/
/* start 10.18 */
int
main (int argc, char *argv[]) {
    data_t *new, *locn;
    tree_t *tree;
    word_t oneword;
    tree = make_empty_tree(compare_string_parts);

    /* loop that once each word is read, it is searched for in the tree.
        If search yields NULL result, the object is not in the tree and must be inserted, if so a permanent
        array is for the string is created using malloc, a pointer to that space placed into the new record and the string copied to it

        However if search returns a pointer to the struct describing the object, then the freq for that word is incremented using the pointer
        and the space used by new can be freed*/
    while (getword(oneword, MAXCHARS) != EOF) {
        new = malloc(sizeof(*new));
        assert(new != NULL);
        new->word = oneword;
        new->freq = 1;
        locn = search_tree(tree, new);
        if (!locn) {
            /* not in tree, so create a new string */
            new->word = malloc(1+strlen(oneword));
            assert(new->word != NULL);
            strcpy(new->word, oneword);
            /* and insert into tree */
            tree = insert_in_order(tree, new);
        }
        else {
            /* already in tree, so increment count */
            locn->freq += 1;
            /* and release the temporary node */
            free(new);
        }
    }
    /* now print all the words, freeing on the way */
    traverse_tree(tree, print_then_free);
    /* and release the tree itself */
    free_tree(tree);
    tree = NULL;
    /* ta daa! */
    return 0;
}


/*--------------------page 121 definition------------------------------------*/
int getword(char W[], int limit) {
  int c, len =0;
  /* first, skip over any non alphabetics */
  while ((c=getchar()) != EOF && !isalpha(c)) {
    /* do nothing more */
  }

  if (c == EOF) {
    return EOF;
  }

  /* ok, first character of next word has been found */
  W[len++] = c;
  while (len < limit && (c = getchar()) != EOF && isalpha(c)) {
    /* another character to be stored */
    W[len++] = c;
  }
  /* now close off the string */
  W[len] = '\0';

  return 0;
}

/*-----------------------------------------------------------------------------*/
