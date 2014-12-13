#ifndef DZEN_PARSER
#define DZEN_PARSER

#include <stdlib.h>
#include "dzen_list.h"

//------------ START: peg & leg defines ------------//

#define YYSTYPE struct dzen_token

#define YY_INPUT(buf, result, max_size)                          \
                  {                                              \
                    int yyc= dzen_parser_get_next_character();       \
                    result= (EOF == yyc) ? 0 : (*(buf)= yyc, 1); \
                  }

//------------ END: peg & leg defines ------------//


struct dzen_parser_cache;
struct dzen_token;
struct dzen_list;

/**
 * A parser cache required to read
 * the input string
 */
typedef struct dzen_parser_cache {
    int read_pos;
    char *input;
} dzen_parser_cache;

/**
 * Gets the next character of the input string
 */
int dzen_parser_get_next_character();

/**
 * Creates a new parser cache
 * @param input The input string to parse
 */
dzen_parser_cache *dzen_parser_cache_create(char *input);

/**
 * Frees the given parser cache
 */
void dzen_parser_cache_destroy(dzen_parser_cache *cache);

/**
 * Collection of each existing token type
 */
typedef enum dzen_token_type {
    DZEN_TOKEN_TYPE_UNDEFINED,
    DZEN_TOKEN_TYPE_TEXT,
    DZEN_TOKEN_TYPE_FILE_PATH,
    DZEN_TOKEN_TYPE_FUNCTION,
    DZEN_TOKEN_TYPE_CONSTANT,
    DZEN_TOKEN_TYPE_NUMBER,
    DZEN_TOKEN_TYPE_SIZE_PARAMETER,
    DZEN_TOKEN_TYPE_POSITIONING_PARAMETER,
    DZEN_TOKEN_TYPE_POSITIONING_PARAMETER_LIST,
    DZEN_TOKEN_TYPE_COLOR_KEYWORD,
    DZEN_TOKEN_TYPE_HEX_COLOR,
    DZEN_TOKEN_TYPE_NAME_IDENTIFIER,
    DZEN_TOKEN_TYPE_INCREMENT_OPERATOR,
    DZEN_TOKEN_TYPE_DECREMENT_OPERATOR
} dzen_token_type;

/**
 * A collection of modifier usually
 * used by a positioning parameter
 * token
 */
typedef enum dzen_token_value_modifier {
    DZEN_VALUE_MODIFIER_NONE,
    DZEN_VALUE_MODIFIER_INCREMENT,
    DZEN_VALUE_MODIFIER_DECREMNT
} dzen_token_value_modifier;

/**
 * A token which represents
 * a logical unit like a function
 * or a parameter.
 */
typedef struct dzen_token {
    dzen_token_type type;
    dzen_token_value_modifier value_modifier;
    dzen_list *parameter_list;
    char *value;
} dzen_token;

/**
 * Creates a new language token.
 */
dzen_token *dzen_token_create(
        dzen_token_type type,
        dzen_token_value_modifier value_modifier,
        dzen_list *parameter_list,
        char *value);

/**
 * Frees the given language token and all its data.
 */
void dzen_token_destroy(dzen_token *token);

#endif