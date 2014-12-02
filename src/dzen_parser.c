#include "dzen_parser.h"

void dzen_token_destroy(struct dzen_token *token) {
    free(token->string_value);
    free(token->parameter_list); //TODO free each parameter separately
    free(token);
}