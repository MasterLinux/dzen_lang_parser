#ifndef DZEN_PARSER
#define DZEN_PARSER

#include <stdlib.h>
#include "dzen_list.h"

//------------ START: peg & leg defines ------------//

#define YYSTYPE struct dzen_token

#define YY_INPUT(buf, result, max_size)                          \
                  {                                              \
                    int yyc= dzen_parser_get_next_character();   \
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
    DZEN_TOKEN_TYPE_COORDINATE_PARAMETER,
    DZEN_TOKEN_TYPE_COLOR_KEYWORD,
    DZEN_TOKEN_TYPE_HEX_COLOR,
    DZEN_TOKEN_TYPE_IDENTIFIER,
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
    DZEN_VALUE_MODIFIER_DECREMENT
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
 * Creates a new function token
 */
inline dzen_token *dzen_token_create_function(char *name, dzen_list *parameter_list);

inline dzen_token *dzen_token_create_size_parameter(dzen_token *width, dzen_token *height);

inline dzen_token *dzen_token_create_positioning_parameter(dzen_token_value_modifier value_modifier, char *value);

inline dzen_token *dzen_token_create_coordinate_parameter(dzen_token *x_position, dzen_token *y_position);

inline dzen_token *dzen_token_create_increment_operator();

inline dzen_token *dzen_token_create_decrement_operator();

inline dzen_token *dzen_token_create_color(char *color);

inline dzen_token *dzen_token_create_hex_color(char *color);

inline dzen_token *dzen_token_create_number(char *number);

inline dzen_token *dzen_token_create_constant(char *value);

inline dzen_token *dzen_token_create_file_path(char *path);

inline dzen_token *dzen_token_create_text(char *text);

inline dzen_token *dzen_token_create_identifier(char *id);

/**
 * Makes a copy of the given token.
 *
 * @param token The token to copy
 */
dzen_token *dzen_token_copy(dzen_token *token);

/**
 * Frees the given language token and all of its data.
 *
 * @param token The token to destroy
 */
void dzen_token_destroy(dzen_token *token);

/**
 * Parses the given input string
 * @param input The input string to parse
 */
dzen_list *dzen_parse(char *input);

#endif
