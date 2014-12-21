#include <string.h>
#include <stdio.h>
#include "dzen_parser.h"

static dzen_parser_cache* parser_cache = NULL;


char *string_copy(char *str) {
    char *copy = NULL;

    if(str != NULL) {
        copy = (char *)malloc(sizeof(char) * strlen(str));
        strcpy(copy, str);
    }

    return copy;
}

dzen_list *dzen_parse(char *input) {
    parser_cache = dzen_parser_cache_create(input);

    //parse input
    while (yyparse());

    dzen_parser_cache_destroy(parser_cache);
    parser_cache = NULL;

    return dzen_parser_token_list;
}

dzen_parser_cache *dzen_parser_cache_create(char *input) {
    dzen_parser_cache *cache = calloc(1, sizeof(dzen_parser_cache));

    cache->input = string_copy(input);
    cache->read_pos = 0;

    return cache;
}

void dzen_parser_cache_destroy(dzen_parser_cache *cache) {
    free(cache->input);
    free(cache);
}

int dzen_parser_get_next_character() {
    char next_char = EOF;

    if (parser_cache != NULL &&
            parser_cache->input != NULL &&
            strlen(parser_cache->input) > parser_cache->read_pos) {
        next_char = parser_cache->input[parser_cache->read_pos];
        parser_cache->read_pos++;
    }

    return next_char;
}

dzen_token *dzen_token_create(dzen_token_type type, dzen_token_value_modifier value_modifier, dzen_list *parameter_list, char *value) {
    dzen_token *token = calloc(1, sizeof(dzen_token));

    token->value_modifier = value_modifier;
    token->parameter_list = dzen_list_copy(parameter_list);
    token->value = string_copy(value);
    token->type = type;

    return token;
}

dzen_token *dzen_token_copy(dzen_token *token) {
    dzen_token *copy = NULL;

    if(token != NULL) {
        copy = calloc(1, sizeof(dzen_token));

        token->value_modifier = token->value_modifier;
        token->parameter_list = dzen_list_copy(token->parameter_list);
        token->value = string_copy(token->value);
        token->type = token->type;
    }

    return copy;
}

void dzen_token_destroy(dzen_token *token) {
    dzen_list_destroy(token->parameter_list);
    free(token->value);
    free(token);
}
