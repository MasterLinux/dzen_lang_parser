/**
 * A representation of a double linked list
 * @author Christoph Grundmann
 */
#include "dzen_parser.h"

#ifndef DZEN_TOKEN_LIST
#define DZEN_TOKEN_LIST

/**
 * Creates a new token list
 * @return The list root
 */
struct dzen_token *dzen_make_token_list();

/**
 * Adds a new token to a specific token list. To create a
 * list use `dzen_make_token_list()`
 *
 * @param list The list to extend
 * @param token The token to add
 */
void dzen_add_token(struct dzen_token *list, struct dzen_token token);
//int dzen_get_count(struct dzen_token *list);

#endif