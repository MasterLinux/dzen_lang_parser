/**
 * A double linked list used to store
 * each found token
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
 * Creates a new double linked list.
 *
 * @return The created list
 */
dzen_list *dzen_list_create();

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
 * Iterates through the given list starting from
 * the first token to the last token.
 *
 * @param list The list to iterate through
 * @param on_next The callback function which is called for each token
 */
void dzen_list_iterate_forward(dzen_list *list, void (*on_next)(dzen_list_node *node, struct dzen_token *token));

/**
* Iterates through the given list starting from
* the last token to the first token.
*
* @param list The list to iterate through
* @param on_next The callback function which is called for each token
*/
void dzen_list_iterate_backward(dzen_list *list, void (*on_previous)(dzen_list_node *node, struct dzen_token *token));

#endif
