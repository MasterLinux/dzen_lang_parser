#include <string.h>
#include <stdio.h>
#include "dzen_parser.h"

static dzen_parser_cache* parser_cache = NULL;


char *clone_string(char *src_string) {
    char *string_copy = (char *)malloc(sizeof(char) * strlen(src_string));
    strcpy(string_copy, src_string);

    return string_copy;
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

    cache->input = clone_string(input);
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
    token->parameter_list = parameter_list;
    token->value = clone_string(value);
    token->type = type;

    return token;
}

void dzen_token_destroy(dzen_token *token) {
    dzen_list_destroy(token->parameter_list);
    free(token->value);
    free(token);
}
