/**
 * A representation of a double linked list
 *
 * @author Christoph Grundmann
 */
#ifndef DZEN_TOKEN_LIST
#define DZEN_TOKEN_LIST

#include <stdlib.h>
#include "dzen_parser.h"

struct dzen_list_node;

/**
 * An iterable list node containing a token.
 */
typedef struct dzen_list_node {
    struct dzen_list_node *next;
    struct dzen_list_node *previous;
    struct dzen_token *token;
    int position;
} dzen_list_node;

/**
 * Representation of a double linked list
 */
typedef struct dzen_list {
    dzen_list_node *first;
    dzen_list_node *last;
    int count;
} dzen_list;

/**
 * Iterator used to iterate through a list
 */
typedef struct dzen_list_iterator {
    int position;
    dzen_list *list;
    struct dzen_token *token;
    dzen_list_node *current;
} dzen_list_iterator;

/**
 * Creates a new double linked list.
 *
 * @return The created list
 */
dzen_list *dzen_list_create();

/**
 * Makes a copy of the given list
 *
 * @param list The list to copy
 */
dzen_list *dzen_list_copy(dzen_list *list);

/**
 * Destroys the given list. It de-allocates
 * the given list and its data.
 *
 * @param list The list to destroy
 */
void dzen_list_destroy(dzen_list *list);

/**
 * Adds a new token to a specific list
 *
 * @param list The list in which the token will be added
 * @param token The token to add
 */
void dzen_list_add(dzen_list *list, struct dzen_token *token);

/**
 * Creates a new list iterator.
 *
 * @param list The list to iterate through
 */
dzen_list_iterator *dzen_list_iterator_create(dzen_list *list);

/**
 *  Destroys the given list iterator. The list must inside it must
 *  be destroyed separately.
 *
 *  @param iterator The list iterator to destroy
 */
void dzen_list_iterator_destroy(dzen_list_iterator *iterator);

/**
 * Iterates through the given list starting from
 * the first token to the last token.
 *
 * @param iterator The iterator which contains the list to iterate
 * @return Returns 0 if the iteration is done, otherwise 1
 */
int dzen_list_iterate_forward(dzen_list_iterator *iterator);

/**
* Iterates through the given list starting from
* the last token to the first token.
*
* @param iterator The iterator which contains the list to iterate
* @return Returns 0 if the iteration is done, otherwise 1
*/
int dzen_list_iterate_backward(dzen_list_iterator *iterator);

#endif
