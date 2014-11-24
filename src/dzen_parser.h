#ifndef DZEN_PARSER
#define DZEN_PARSER

#define DZEN_NOT_SET -1

/**
 * Collection of each existing token type
 */
typedef enum dzen_token_type {
    DZEN_TOKEN_TYPE_UNDEFINED,
    DZEN_TOKEN_TYPE_ROOT,
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
    DZEN_TOKEN_TYPE_PLUS_OPERATOR,
    DZEN_TOKEN_TYPE_MINUS_OPERATOR
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
 * or a parameter
 */
struct dzen_token {
    dzen_token_type type;
    dzen_token_value_modifier value_modifier;
    char *string_value;
    int integer_value;
    struct dzen_token *parameter_list;
};

#endif