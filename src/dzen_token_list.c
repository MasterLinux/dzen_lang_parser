#include <stdlib.h>
#include "dzen_parser.h"

struct dzen_token *dzen_make_token_list() {
    struct dzen_token *list = (struct dzen_token *) malloc(sizeof(struct dzen_token));

    list->type = DZEN_TOKEN_TYPE_ROOT;
    list->value_modifier = DZEN_VALUE_MODIFIER_NONE;
    list->string_value = NULL;
    list->integer_value = DZEN_NOT_SET;
    list->parameter_list = NULL;

    list->first_token = NULL;
    list->previous_token = NULL;
    list->next_token = NULL;
    list->last_token = NULL;

    return list;
}

void update_last_token(struct dzen_token *list, struct dzen_token *last) {
    list->last_token = last;

    struct dzen_token *next = list->next_token;
    while (next != NULL) {
        next->last_token = last;
        next = next->next_token;
    }
}

void dzen_add_token(struct dzen_token *list, struct dzen_token token) {
    struct dzen_token *next_token = (struct dzen_token *) malloc(sizeof(struct dzen_token));
    struct dzen_token *last_token = list->last_token != NULL ? list->last_token : list;
    // set data
    next_token->type = token.type;
    next_token->value_modifier = token.value_modifier;
    next_token->string_value = token.string_value;
    next_token->integer_value = token.integer_value;
    next_token->parameter_list = token.parameter_list;

    // set iteration pointer
    next_token->previous_token = last_token;
    next_token->next_token = NULL;
    next_token->first_token = list;
    next_token->last_token = NULL;

    // add to end of list
    last_token->next_token = next_token;

    update_last_token(list, next_token);
}



